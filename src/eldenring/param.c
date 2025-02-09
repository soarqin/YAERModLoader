/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "param.h"

#include "pointers.h"

#include <stdio.h>

bool param_load_table() {
    pointers_init(INIT_CS_REGULATION_MANAGER);
    if (!pointers.cs_regulation_manager) {
        return false;
    }
    const param_collection_t *param_collection = (const param_collection_t *)(*(uintptr_t*)pointers.cs_regulation_manager + 0x18);
    if (!param_collection->start || !param_collection->end) {
        return false;
    }
    fprintf(stderr, "%p %p %zd\n", param_collection->start, param_collection->end, param_collection->end - param_collection->start);
    for (param_t **current = param_collection->start; current < param_collection->end; current++) {
        const param_t *param = *current;
        const uintptr_t ptr = *(uintptr_t*)(*(uintptr_t*)((const uintptr_t)param + 0x80) + 0x80);
        uint16_t count = param->path->data->count;
        fwprintf(stderr, L"%ls %u\n", wstring_impl_str(&param->name), count);
        const param_entry_offset_t *entries = param->path->data->entries;
        if (count > 5) count = 5;
        for (uint16_t i = 0; i < count; i++) {
            const param_entry_offset_t *entry = entries + i;
            fwprintf(stderr, L"%llu %zd\n", entry->param_id, entry->offset);
        }
    }
    return true;
}
