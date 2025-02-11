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

#pragma pack(push, 8)

typedef struct {
    uintptr_t vtable[2];
    wstring_impl_t name;
    uintptr_t unk1[9];
    struct {
        uintptr_t unk0[16];
        param_table_t *data;
    } *path;
} param_t;

typedef struct {
    uintptr_t vtable[3];
    param_t **start;
    param_t **end;
    uintptr_t unk0;
    uintptr_t unk1;
    uintptr_t unk2;
    int loaded;
} cs_regulation_manager_t;

#pragma pack(pop)

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
    const cs_regulation_manager_t *reg_man;
    while (1) {
        reg_man = (const cs_regulation_manager_t*)*(uintptr_t*)pointers.cs_regulation_manager;
        if (reg_man != NULL && reg_man->start != NULL && reg_man->end != NULL && reg_man->loaded) break;
        Sleep(100);
    }
    /*fwprintf(stderr, L"%p %p %zd\n", reg_man->start, reg_man->end, reg_man->end - reg_man->start);*/
    for (param_t **current = reg_man->start; current < reg_man->end; current++) {
        const param_t *param = *current;
        param_type_t *pt = uthash_malloc(sizeof(param_type_t));
        pt->name = wstring_impl_str(&param->name);
        pt->param = param->path->data;
        /*fwprintf(stderr, L"%p %ls\n", param, pt->name);*/
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
