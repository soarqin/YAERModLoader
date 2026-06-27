/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct dl_allocator_s dl_allocator_t;
typedef struct dl_allocator_vtable_s dl_allocator_vtable_t;

typedef enum dl_heap_direction_e {
    DL_HEAP_FRONT = 0,
    DL_HEAP_BACK = 1,
} dl_heap_direction_t;

struct dl_allocator_s {
    dl_allocator_vtable_t *vtable;
};

struct dl_allocator_vtable_s {
    void (__cdecl *dtor)(dl_allocator_t *self);
    uint32_t (__cdecl *heap_id)(dl_allocator_t *self);
    uint32_t (__cdecl *allocator_id)(dl_allocator_t *self);
    void *(__cdecl *capability)(dl_allocator_t *self, uint32_t *out, uint32_t heap);
    size_t (__cdecl *total_size)(dl_allocator_t *self);
    size_t (__cdecl *free_size)(dl_allocator_t *self);
    size_t (__cdecl *max_size)(dl_allocator_t *self);
    size_t (__cdecl *num_blocks)(dl_allocator_t *self);
    size_t (__cdecl *block_size)(dl_allocator_t *self, const void *ptr);
    void *(__cdecl *allocate)(dl_allocator_t *self, size_t size);
    void *(__cdecl *allocate_aligned)(dl_allocator_t *self, size_t size, size_t alignment, dl_heap_direction_t direction);
    void *(__cdecl *reallocate)(dl_allocator_t *self, void *ptr, size_t size);
    void *(__cdecl *reallocate_aligned)(dl_allocator_t *self, void *ptr, size_t size, size_t alignment, dl_heap_direction_t direction);
    void (__cdecl *free)(dl_allocator_t *self, void *ptr);
    void (__cdecl *free_all)(dl_allocator_t *self);
    void *(__cdecl *back_allocate)(dl_allocator_t *self, size_t size);
    void *(__cdecl *back_allocate_aligned)(dl_allocator_t *self, size_t size, size_t alignment, dl_heap_direction_t direction);
    void *(__cdecl *back_reallocate)(dl_allocator_t *self, void *ptr, size_t size);
    void *(__cdecl *back_reallocate_aligned)(dl_allocator_t *self, void *ptr, size_t size, size_t alignment, dl_heap_direction_t direction);
    void (__cdecl *back_free)(dl_allocator_t *self, void *ptr);
    bool (__cdecl *self_diagnose)(dl_allocator_t *self);
    bool (__cdecl *is_valid_block)(dl_allocator_t *self, const void *ptr);
    void (__cdecl *lock)(dl_allocator_t *self);
    void (__cdecl *unlock)(dl_allocator_t *self);
    void *(__cdecl *block_of)(dl_allocator_t *self, const void *ptr);
};

dl_allocator_t *dl_allocator_for_object(const void *object);
void dl_allocator_dealloc(dl_allocator_t *allocator, void *ptr);
void **dl_allocator_table_first(void);
void **dl_allocator_table_last_er(void);
bool dl_allocator_fill_table(dl_allocator_t *allocator);

#ifdef __cplusplus
}
#endif
