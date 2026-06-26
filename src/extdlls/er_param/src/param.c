/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "param_internal.h"

#include "pointers.h"
#include <er_param/wstring.h>

#include <windows.h>

#define kcalloc(N,Z)  LocalAlloc(LPTR, (N)*(Z))
#define kmalloc(Z)    LocalAlloc(0, (Z))
#define krealloc(P,Z) ((P) ? LocalReAlloc((P), (Z), LMEM_MOVEABLE) : LocalAlloc(0, (Z)))
#define kfree(P)      LocalFree(P)
#include "khash.h"
#include "khash_wstr.h"

#pragma pack(push, 8)

typedef struct {
    uintptr_t vtable[2];
    er_wstring_impl_t name;
    uintptr_t unk1[9];
    struct {
        uintptr_t unk0[16];
        er_param_table_t *data;
    } *path;
} er_param_t;

typedef struct {
    uintptr_t vtable[3];
    er_param_t **start;
    er_param_t **end;
    uintptr_t unk0;
    uintptr_t unk1;
    uintptr_t unk2;
    int loaded;
} cs_regulation_manager_t;

#pragma pack(pop)

typedef struct {
    const wchar_t *name;
    const er_param_table_t *param;
} er_param_type_t;

static khash_t(wstr) *param_types = NULL;

bool er_param_load_table() {
    /* preserve uthash HASH_CLEAR semantics: clears table without freeing user entries;
       entries' lifetime is managed elsewhere (or pre-existing leak — out of scope) */
    if (param_types) kh_clear(wstr, param_types); else param_types = kh_init(wstr);
    if (!er_pointers.cs_regulation_manager) {
        return false;
    }
    const cs_regulation_manager_t *reg_man;
    const int max_retries = 300; /* ~30 seconds timeout */
    for (int retry = 0; retry < max_retries; retry++) {
        reg_man = (const cs_regulation_manager_t*)*(uintptr_t*)er_pointers.cs_regulation_manager;
        if (reg_man != NULL && reg_man->start != NULL && reg_man->end != NULL && reg_man->loaded) break;
        Sleep(100);
    }
    if (reg_man == NULL || reg_man->start == NULL || reg_man->end == NULL || !reg_man->loaded) {
        return false;
    }
    /*fwprintf(stderr, L"%p %p %zd\n", reg_man->start, reg_man->end, reg_man->end - reg_man->start);*/
    for (er_param_t **current = reg_man->start; current < reg_man->end; current++) {
        const er_param_t *param = *current;
        er_param_type_t *pt = (er_param_type_t*)LocalAlloc(0, sizeof(er_param_type_t));
        pt->name = er_wstring_impl_str(&param->name);
        pt->param = param->path->data;
        /*fwprintf(stderr, L"%p %ls\n", param, pt->name);*/
        int ret;
        khiter_t k = kh_put(wstr, param_types, pt->name, &ret);
        kh_value(param_types, k) = pt;
    }
    return true;
}

void er_param_unload() {
    /* preserve uthash HASH_CLEAR semantics: clears table without freeing user entries;
       entries' lifetime is managed elsewhere (or pre-existing leak — out of scope) */
    if (param_types) kh_clear(wstr, param_types); else param_types = kh_init(wstr);
}

const er_param_table_t *er_param_find_table(const wchar_t *name) {
    /* NULL guard: kh_get on NULL is UB; uthash HASH_FIND on NULL head was safe — preserve that safety */
    if (!param_types) return NULL;
    khiter_t k = kh_get(wstr, param_types, name);
    if (k == kh_end(param_types)) return NULL;
    er_param_type_t *res = (er_param_type_t*)kh_value(param_types, k);
    return res->param;
}
