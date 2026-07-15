/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <stddef.h>

typedef struct dlrf_runtime_class_entry_s {
    const void *type_id;
    void *runtime_class;
} dlrf_runtime_class_entry_t;

typedef struct dlrf_range_s {
    const unsigned char *start;
    size_t size;
} dlrf_range_t;

const dlrf_runtime_class_entry_t *dlrf_runtime_classes(size_t *count);
size_t dlrf_find_registry(const dlrf_runtime_class_entry_t *entries, size_t count,
                          dlrf_range_t data, dlrf_range_t rdata,
                          const dlrf_runtime_class_entry_t **registry);
