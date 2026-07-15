/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Returns the lowest-offset vtable slot for class_name, or NULL. */
extern void *rtti_find_vtable(const char *class_name);
extern size_t rtti_vtable_count(const char *class_name);
extern void *rtti_find_vtable_at(const char *class_name, size_t index);

typedef struct rtti_vtable_list_s {
    void **items;
    size_t count;
    size_t capacity;
} rtti_vtable_list_t;

void rtti_vtable_list_insert(rtti_vtable_list_t *list, void *vtable, uint32_t offset, uint32_t *offsets);

#ifdef __cplusplus
}
#endif
