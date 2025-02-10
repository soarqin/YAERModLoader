/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include "wstring.h"

#include <stdbool.h>

#pragma pack(push, 8)

typedef struct {
    uint64_t param_id;
    intptr_t offset;
    uint64_t unk0;
} param_entry_offset_t;

typedef struct {
    uintptr_t vtable;
    uint16_t unk0;
    uint16_t count;
    uintptr_t unk1[6];
    param_entry_offset_t entries[0];
} param_table_t;

#pragma pack(pop)

bool param_load_table();
void param_unload();
const param_table_t *param_find_table(const wchar_t *name);

#define param_table_find_id(t, id, tp) { \
    uint16_t count = (t)->count; \
    for (uint16_t i = 0; i < count; i++) { \
        const param_entry_offset_t *entry = &((t)->entries[i]); \
        if (entry->param_id == id) { \
            return (tp*)((uintptr_t)t + entry->offset); \
        } \
    } \
}

#define param_table_iterate_begin(t, tp, var) { \
    uint16_t count = (t)->count; \
    for (uint16_t i = 0; i < count; i++) { \
        const param_entry_offset_t *entry = &((t)->entries[i]); \
        tp *var = (tp*)((uintptr_t)t + entry->offset); \
        if (!var) { \
            continue; \
        }

#define param_table_iterate_end() } }
