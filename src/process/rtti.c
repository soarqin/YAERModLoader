/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "rtti.h"

#include "pe.h"
#include "undname.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define kcalloc(N,Z)  LocalAlloc(LPTR, (N)*(Z))
#define kmalloc(Z)    LocalAlloc(0, (Z))
#define krealloc(P,Z) ((P) ? LocalReAlloc((P), (Z), LMEM_MOVEABLE) : LocalAlloc(0, (Z)))
#define kfree(P)      LocalFree(P)
#include "khash.h"

typedef struct rtti_complete_object_locator_s {
    uint32_t signature;
    uint32_t offset;
    uint32_t cd_offset;
    uint32_t type_descriptor;
    uint32_t class_descriptor;
    uint32_t self;
} rtti_complete_object_locator_t;

typedef struct rtti_type_descriptor_s {
    uintptr_t vftable;
    uintptr_t spare;
    char name[1];
} rtti_type_descriptor_t;

typedef struct rtti_vtable_entry_s {
    void *vtable;
    uint32_t offset;
    struct rtti_vtable_entry_s *next;
} rtti_vtable_entry_t;

KHASH_MAP_INIT_STR(rtti_vtables, rtti_vtable_entry_t)

static INIT_ONCE rtti_once = INIT_ONCE_STATIC_INIT;
static khash_t(rtti_vtables) *rtti_map = NULL;

void rtti_vtable_list_insert(rtti_vtable_list_t *list, void *vtable, uint32_t offset, uint32_t *offsets) {
    size_t index;
    if (list == NULL || vtable == NULL || offsets == NULL) return;
    for (index = 0; index < list->count; index++) {
        if (list->items[index] == vtable) return;
        if (offset < offsets[index]) break;
    }
    if (list->count == list->capacity) return;
    memmove(&list->items[index + 1], &list->items[index], (list->count - index) * sizeof(*list->items));
    memmove(&offsets[index + 1], &offsets[index], (list->count - index) * sizeof(*offsets));
    list->items[index] = vtable;
    offsets[index] = offset;
    list->count++;
}

static char *local_strdup_a(const char *s) {
    size_t len;
    char *copy;

    if (s == NULL) {
        return NULL;
    }

    len = strlen(s);
    copy = (char *)LocalAlloc(0, len + 1);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, s, len + 1);
    return copy;
}

static bool read_bounded_cstr(const char *s, const char *end, char *out, size_t out_size) {
    size_t len = 0;

    if (s == NULL || end == NULL || out == NULL || out_size == 0 || s >= end) {
        return false;
    }

    while (s + len < end && s[len] != '\0') {
        len++;
    }
    if (s + len >= end || len >= out_size) {
        return false;
    }

    memcpy(out, s, len);
    out[len] = '\0';
    return true;
}

static void rtti_insert(const char *class_name, void *vtable, uint32_t offset) {
    khiter_t k;
    int ret;

    if (rtti_map == NULL || class_name == NULL || vtable == NULL) {
        return;
    }

    k = kh_put(rtti_vtables, rtti_map, class_name, &ret);
    if (ret < 0) {
        return;
    }

    if (ret == 0) {
        rtti_vtable_entry_t *entry = &kh_value(rtti_map, k);
        rtti_vtable_entry_t *next;
        for (next = entry; next != NULL; next = next->next) {
            if (next->vtable == vtable) return;
        }
        next = (rtti_vtable_entry_t *)LocalAlloc(0, sizeof(*next));
        if (next == NULL) return;
        next->vtable = vtable;
        next->offset = offset;
        next->next = NULL;
        if (offset < entry->offset) {
            next->vtable = entry->vtable;
            next->offset = entry->offset;
            next->next = entry->next;
            entry->offset = offset;
            entry->vtable = vtable;
        } else {
            while (entry->next != NULL && entry->next->offset <= offset) entry = entry->next;
            next->next = entry->next;
            entry->next = next;
        }
        return;
    }

    kh_key(rtti_map, k) = local_strdup_a(class_name);
    if (kh_key(rtti_map, k) == NULL) {
        kh_del(rtti_vtables, rtti_map, k);
        return;
    }
    kh_value(rtti_map, k).vtable = vtable;
    kh_value(rtti_map, k).offset = offset;
    kh_value(rtti_map, k).next = NULL;
}

static void rtti_build_for_image(void *image_base) {
    const IMAGE_SECTION_HEADER *text;
    const IMAGE_SECTION_HEADER *data;
    const IMAGE_SECTION_HEADER *rdata;
    uintptr_t *ptrs;
    size_t rdata_size = 0;
    size_t ptr_count;
    const char *data_end;

    if (image_base == NULL) {
        return;
    }

    text = pe_section_by_name(image_base, ".text");
    data = pe_section_by_name(image_base, ".data");
    rdata = pe_section_by_name(image_base, ".rdata");
    if (text == NULL || data == NULL || rdata == NULL) {
        return;
    }

    ptrs = (uintptr_t *)pe_section_data(image_base, rdata, &rdata_size);
    if (ptrs == NULL || rdata_size < sizeof(uintptr_t) * 2) {
        return;
    }

    ptr_count = rdata_size / sizeof(uintptr_t);
    data_end = (const char *)image_base + pe_section_rva_end(data);

    for (size_t i = 0; i + 1 < ptr_count; i++) {
        const uintptr_t col_va = ptrs[i];
        const uintptr_t first_fn_va = ptrs[i + 1];
        const rtti_complete_object_locator_t *col;
        const rtti_type_descriptor_t *td;
        char mangled[512];
        char demangled[512];

        if (!pe_section_contains_va(image_base, rdata, (const void *)col_va) ||
            !pe_section_contains_va(image_base, text, (const void *)first_fn_va)) {
            continue;
        }

        col = (const rtti_complete_object_locator_t *)col_va;
        if (col->signature != 1 || !pe_section_contains_rva(data, col->type_descriptor)) {
            continue;
        }

        td = (const rtti_type_descriptor_t *)((const uint8_t *)image_base + col->type_descriptor);
        if (!read_bounded_cstr(td->name, data_end, mangled, sizeof(mangled))) {
            continue;
        }

        if (!undname_class(mangled, demangled, sizeof(demangled))) {
            continue;
        }

        rtti_insert(demangled, &ptrs[i + 1], col->offset);
    }
}

static BOOL CALLBACK rtti_init_once(PINIT_ONCE init_once, PVOID parameter, PVOID *context) {
    (void)init_once;
    (void)parameter;
    (void)context;

    rtti_map = kh_init(rtti_vtables);
    if (rtti_map != NULL) {
        rtti_build_for_image(GetModuleHandleW(NULL));
    }

    return TRUE;
}

void *rtti_find_vtable(const char *class_name) {
    return rtti_find_vtable_at(class_name, 0);
}

size_t rtti_vtable_count(const char *class_name) {
    khiter_t k;
    size_t count = 0;

    if (class_name == NULL) {
        return 0;
    }

    if (!InitOnceExecuteOnce(&rtti_once, rtti_init_once, NULL, NULL) || rtti_map == NULL) {
        return 0;
    }

    k = kh_get(rtti_vtables, rtti_map, class_name);
    if (k == kh_end(rtti_map)) {
        return 0;
    }

    for (rtti_vtable_entry_t *entry = &kh_value(rtti_map, k); entry != NULL; entry = entry->next) count++;
    return count;
}

void *rtti_find_vtable_at(const char *class_name, size_t index) {
    khiter_t k;
    rtti_vtable_entry_t *entry;

    if (class_name == NULL) return NULL;
    if (!InitOnceExecuteOnce(&rtti_once, rtti_init_once, NULL, NULL) || rtti_map == NULL) return NULL;
    k = kh_get(rtti_vtables, rtti_map, class_name);
    if (k == kh_end(rtti_map)) return NULL;

    entry = &kh_value(rtti_map, k);
    while (entry != NULL && index-- != 0) entry = entry->next;
    return entry != NULL ? entry->vtable : NULL;
}
