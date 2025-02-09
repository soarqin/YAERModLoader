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
    uintptr_t unk2[6];
    param_entry_offset_t entries[0];
} param_data_t;

typedef struct {
    uintptr_t vtable;
    uintptr_t unk0;
    wstring_impl_t name;
    uintptr_t unk1[9];
    struct {
        uintptr_t unk0[16];
        param_data_t *data;
    } *path;
} param_t;

typedef struct {
    param_t **start;
    param_t **end;
} param_collection_t;

#pragma pack(pop)

bool param_load_table();
