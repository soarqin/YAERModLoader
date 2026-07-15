/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "dlrf.h"

#include "pe.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <string.h>
#include <stdbool.h>
#include <stdint.h>

static INIT_ONCE dlrf_once = INIT_ONCE_STATIC_INIT;
static const dlrf_runtime_class_entry_t *dlrf_registry;
static size_t dlrf_registry_count;

static bool range_contains(dlrf_range_t range, const void *ptr, size_t size) {
    const unsigned char *address = (const unsigned char *)ptr;
    return range.start != NULL && address >= range.start && size <= range.size &&
           (size_t)(address - range.start) <= range.size - size;
}

size_t dlrf_find_registry(const dlrf_runtime_class_entry_t *entries, size_t count,
                          dlrf_range_t data, dlrf_range_t rdata,
                          const dlrf_runtime_class_entry_t **registry) {
    size_t best_count = 0;
    const dlrf_runtime_class_entry_t *best = NULL;
    size_t run = 0;
    const dlrf_runtime_class_entry_t *start = NULL;
    uintptr_t previous_type_id = 0;

    if (registry != NULL) *registry = NULL;
    for (size_t i = 0; i < count; i++) {
        const dlrf_runtime_class_entry_t *entry = &entries[i];
        void *vtable = NULL;
        bool valid = entry->type_id != NULL && entry->runtime_class != NULL &&
                     (uintptr_t)entry->type_id > previous_type_id &&
                     range_contains(data, entry->type_id, 1) && *(const unsigned char *)entry->type_id == 0 &&
                     range_contains(data, entry->runtime_class, sizeof(void *));
        if (valid) {
            memcpy(&vtable, entry->runtime_class, sizeof(vtable));
            valid = range_contains(rdata, vtable, sizeof(void *));
        }
        if (valid) {
            if (run == 0) start = entry;
            run++;
            previous_type_id = (uintptr_t)entry->type_id;
            if (run > best_count) {
                best = start;
                best_count = run;
            }
        } else {
            run = 0;
            previous_type_id = 0;
        }
    }
    if (registry != NULL) *registry = best;
    return best_count;
}

static BOOL CALLBACK dlrf_init_once(PINIT_ONCE once, PVOID parameter, PVOID *context) {
    void *image = GetModuleHandleW(NULL);
    const IMAGE_SECTION_HEADER *data;
    const IMAGE_SECTION_HEADER *rdata;
    size_t data_size;
    size_t rdata_size;
    dlrf_range_t data_range;
    dlrf_range_t rdata_range;
    (void)once;
    (void)parameter;
    (void)context;

    data = pe_section_by_name(image, ".data");
    rdata = pe_section_by_name(image, ".rdata");
    data_range.start = pe_section_data(image, data, &data_size);
    rdata_range.start = pe_section_data(image, rdata, &rdata_size);
    data_range.size = data_size;
    rdata_range.size = rdata_size;
    if (data_range.start != NULL && rdata_range.start != NULL) {
        size_t count = data_size / sizeof(dlrf_runtime_class_entry_t);
        size_t found = dlrf_find_registry((const dlrf_runtime_class_entry_t *)data_range.start, count,
                                          data_range, rdata_range, &dlrf_registry);
        if (found >= 512) dlrf_registry_count = found;
        else dlrf_registry = NULL;
    }
    return TRUE;
}

const dlrf_runtime_class_entry_t *dlrf_runtime_classes(size_t *count) {
    InitOnceExecuteOnce(&dlrf_once, dlrf_init_once, NULL, NULL);
    if (count != NULL) *count = dlrf_registry_count;
    return dlrf_registry;
}
