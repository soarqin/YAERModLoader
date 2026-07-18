/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "dl_allocator.h"

#include "process/image.h"
#include "process/pe.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef dl_allocator_t *(__cdecl *dl_allocator_for_object_fn_t)(const void *object);

static dl_allocator_for_object_fn_t find_for_object_fn(void);

static dl_allocator_for_object_fn_t for_object_fn = NULL;

static BOOL CALLBACK init_for_object_fn_once(PINIT_ONCE init_once, PVOID parameter, PVOID *context) {
    (void)init_once;
    (void)parameter;
    (void)context;
    for_object_fn = find_for_object_fn();
    return TRUE;
}

static bool match_optional_xor_rdx(const uint8_t *base, size_t size, size_t *offset) {
    if (*offset + 2 <= size && base[*offset] == 0x33 && base[*offset + 1] == 0xD2) {
        *offset += 2;
    }
    return true;
}

static bool match_for_object_pattern(const uint8_t *base, size_t size) {
    size_t off = 0;
    if (size < 24) return false;
    if ((base[0] == 0x44 && base[1] == 0x8B && base[2] == 0x05) ||
        (base[0] == 0x4C && base[1] == 0x63 && base[2] == 0x05)) {
        off = 7;
    } else {
        return false;
    }
    match_optional_xor_rdx(base, size, &off);
    if (off + 3 > size) return false;
    if (!((base[off] == 0x45 || base[off] == 0x4D) && base[off + 1] == 0x85 && base[off + 2] == 0xC0)) return false;
    off += 3;
    if (off + 2 > size) return false;
    if (base[off] == 0x7E) {
        off += 2;
    } else if (off + 6 <= size && base[off] == 0x0F && base[off + 1] == 0x8E) {
        off += 6;
    } else {
        return false;
    }
    match_optional_xor_rdx(base, size, &off);
    return off + 7 <= size && base[off] == 0x48 && base[off + 1] == 0x8D && base[off + 2] == 0x05;
}

static dl_allocator_for_object_fn_t find_for_object_fn(void) {
    size_t image_size = 0;
    uint8_t *image_base = get_module_image_base(NULL, &image_size);
    if (image_base == NULL) return NULL;

    const IMAGE_SECTION_HEADER *text = pe_section_by_name(image_base, ".text");
    size_t text_size = 0;
    uint8_t *text_base = pe_section_data(image_base, text, &text_size);
    if (text_base == NULL || text_size == 0) return NULL;

    for (size_t i = 0; i + 24 <= text_size; i++) {
        if (match_for_object_pattern(text_base + i, text_size - i)) {
            return (dl_allocator_for_object_fn_t)(text_base + i);
        }
    }
    return NULL;
}

dl_allocator_t *dl_allocator_for_object(const void *object) {
    static INIT_ONCE once = INIT_ONCE_STATIC_INIT;
    InitOnceExecuteOnce(&once, init_for_object_fn_once, NULL, NULL);
    return for_object_fn ? for_object_fn(object) : NULL;
}

void dl_allocator_dealloc(dl_allocator_t *allocator, void *ptr) {
    if (allocator == NULL || allocator->vtable == NULL || allocator->vtable->free == NULL || ptr == NULL) return;
    allocator->vtable->free(allocator, ptr);
}
