/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 8)

typedef struct er_param_entry_offset_s {
    uint64_t param_id;
    intptr_t offset;
    uint64_t unk0;
} er_param_entry_offset_t;

typedef struct er_param_table_s {
    uintptr_t vtable;
    uint16_t unk0;
    uint16_t count;
    uint16_t padding0[2];
    uintptr_t unk1[6];
    er_param_entry_offset_t entries[0];
} er_param_table_t;

#pragma pack(pop)

#define param_table_find_id(t, id, tp) { \
    uint16_t count = (t)->count; \
    for (uint16_t i = 0; i < count; i++) { \
        const er_param_entry_offset_t *entry = &((t)->entries[i]); \
        if (entry->param_id == id) { \
            return (tp*)((uintptr_t)t + entry->offset); \
        } \
    } \
}

#define er_param_table_iterate_begin(t, tp, var) do { \
    uint16_t count = (t)->count; \
    for (uint16_t i = 0; i < count; i++) { \
        const er_param_entry_offset_t *entry = &((t)->entries[i]); \
        tp *var = (tp*)((uintptr_t)t + entry->offset); \
        if (!var) { \
            continue; \
        }

#define er_param_table_iterate_end() } } while(0)

#ifdef __cplusplus
}
#endif
