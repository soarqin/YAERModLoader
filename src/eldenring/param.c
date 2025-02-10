/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "param.h"

#include "pointers.h"

#define uthash_malloc(sz) LocalAlloc(0, sz)
#define uthash_free(ptr,sz) LocalFree(ptr)
#define uthash_bzero(a,n) ZeroMemory(a, n)
#define uthash_strlen(s) lstrlenA(s)

#include <uthash.h>

#include <windows.h>
#include <stdio.h>

typedef struct {
    uintptr_t vtable;
    uintptr_t unk0;
    wstring_impl_t name;
    uintptr_t unk1[9];
    struct {
        uintptr_t unk0[16];
        param_table_t *data;
    } *path;
} param_t;

typedef struct {
    param_t **start;
    param_t **end;
} param_collection_t;

typedef struct {
    const wchar_t *name;
    const param_table_t *param;

    UT_hash_handle hh;
} param_type_t;

static param_type_t *param_types = NULL;

bool param_load_table() {
    HASH_CLEAR(hh, param_types);
    pointers_init(INIT_CS_REGULATION_MANAGER);
    if (!pointers.cs_regulation_manager) {
        return false;
    }
    const param_collection_t *param_collection = (const param_collection_t*)(*(uintptr_t*)pointers.cs_regulation_manager + 0x18);
    if (!param_collection->start || !param_collection->end) {
        return false;
    }
    fprintf(stderr, "%p %p %zd\n", param_collection->start, param_collection->end, param_collection->end - param_collection->start);
    for (param_t **current = param_collection->start; current < param_collection->end; current++) {
        const param_t *param = *current;
        param_type_t *pt = LocalAlloc(0, sizeof(param_type_t));
        pt->name = wstring_impl_str(&param->name);
        pt->param = param->path->data;
        HASH_ADD_KEYPTR(hh, param_types, pt->name, lstrlenW(pt->name) * sizeof(wchar_t), pt);
    }
    return true;
}

void param_unload() {
    HASH_CLEAR(hh, param_types);
}

const param_table_t *param_find_table(const wchar_t *name) {
    param_type_t *res = NULL;
    HASH_FIND(hh, param_types, name, lstrlenW(name) * sizeof(wchar_t), res);
    if (!res) return NULL;
    return res->param;
}
