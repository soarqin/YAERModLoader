/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "mimalloc_allocator.h"

#include <mimalloc.h>

#include <stdint.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static INIT_ONCE mimalloc_heap_once = INIT_ONCE_STATIC_INIT;
static mi_heap_t *mimalloc_heap;

static BOOL CALLBACK mimalloc_heap_initialize(PINIT_ONCE init_once, PVOID parameter, PVOID *context) {
    size_t heap_size_mb = (size_t)(uintptr_t)parameter;
    mi_arena_id_t arena_id = NULL;
    (void)init_once;
    (void)context;

    if (heap_size_mb == 0) heap_size_mb = MIMALLOC_DL_ALLOCATOR_DEFAULT_HEAP_SIZE_MB;
    if (heap_size_mb > SIZE_MAX / (1024u * 1024u)) return TRUE;

    mi_option_set(mi_option_purge_decommits, 0);
    if (mi_reserve_os_memory_ex(heap_size_mb * 1024u * 1024u, true, true, true, &arena_id) != 0) return TRUE;
    mimalloc_heap = mi_heap_new_in_arena(arena_id);
    return TRUE;
}

bool mimalloc_dl_allocator_prepare(size_t heap_size_mb) {
    InitOnceExecuteOnce(&mimalloc_heap_once, mimalloc_heap_initialize, (PVOID)(uintptr_t)heap_size_mb, NULL);
    return mimalloc_heap != NULL;
}

static mi_heap_t *mimalloc_dl_heap(void) {
    mimalloc_dl_allocator_prepare(0);
    return mimalloc_heap;
}

static size_t round_up_size(size_t size, size_t alignment, bool *ok) {
    size_t mask = alignment - 1;
    if ((alignment & mask) != 0) {
        *ok = false;
        return 0;
    }
    if (size > SIZE_MAX - mask) {
        *ok = false;
        return 0;
    }
    *ok = true;
    return (size + mask) & ~mask;
}

static size_t normalized_alignment(size_t alignment) {
    return alignment < 16 ? 16 : alignment;
}

static void __cdecl mimalloc_noop(dl_allocator_t *self) {
    (void)self;
}

static uint32_t __cdecl mimalloc_heap_id(dl_allocator_t *self) {
    (void)self;
    return 0x401;
}

static uint32_t __cdecl mimalloc_allocator_id(dl_allocator_t *self) {
    (void)self;
    return 0xffffffffu;
}

static void *__cdecl mimalloc_capability(dl_allocator_t *self, uint32_t *out, dl_heap_direction_t heap) {
    (void)self;
    (void)heap;
    if (out != NULL) *out = 0x7b;
    return out;
}

static size_t __cdecl mimalloc_size_max(dl_allocator_t *self) {
    (void)self;
    return SIZE_MAX;
}

static size_t __cdecl mimalloc_zero(dl_allocator_t *self) {
    (void)self;
    return 0;
}

static size_t __cdecl mimalloc_block_size(dl_allocator_t *self, void *ptr) {
    (void)self;
    return ptr ? mi_usable_size(ptr) : 0;
}

static void *__cdecl mimalloc_allocate_aligned(dl_allocator_t *self, size_t size, size_t alignment) {
    mi_heap_t *heap;
    (void)self;
    bool ok = false;
    alignment = normalized_alignment(alignment);
    size = round_up_size(size, alignment, &ok);
    if (!ok) return NULL;
    heap = mimalloc_dl_heap();
    return heap != NULL ? mi_heap_malloc_aligned(heap, size, alignment) : mi_malloc_aligned(size, alignment);
}

static void *__cdecl mimalloc_allocate(dl_allocator_t *self, size_t size) {
    return mimalloc_allocate_aligned(self, size, 16);
}

static void *__cdecl mimalloc_reallocate_aligned(dl_allocator_t *self, void *ptr, size_t size, size_t alignment) {
    mi_heap_t *heap;
    (void)self;
    bool ok = false;
    alignment = normalized_alignment(alignment);
    size = round_up_size(size, alignment, &ok);
    if (!ok) return NULL;
    heap = mimalloc_dl_heap();
    return heap != NULL ? mi_heap_realloc_aligned(heap, ptr, size, alignment) : mi_realloc_aligned(ptr, size, alignment);
}

static void *__cdecl mimalloc_reallocate(dl_allocator_t *self, void *ptr, size_t size) {
    return mimalloc_reallocate_aligned(self, ptr, size, 16);
}

static void __cdecl mimalloc_free(dl_allocator_t *self, void *ptr) {
    (void)self;
    mi_free(ptr);
}

static bool __cdecl mimalloc_self_diagnose(dl_allocator_t *self) {
    (void)self;
    return false;
}

static bool __cdecl mimalloc_is_valid_block(dl_allocator_t *self, void *ptr) {
    (void)self;
    (void)ptr;
    return true;
}

static void * __cdecl mimalloc_block_of(dl_allocator_t *self, void *ptr) {
    (void)self;
    (void)ptr;
    return NULL;
}

static dl_allocator_vtable_t mimalloc_vtable = {
    mimalloc_noop,
    mimalloc_heap_id,
    mimalloc_allocator_id,
    mimalloc_capability,
    mimalloc_size_max,
    mimalloc_size_max,
    mimalloc_size_max,
    mimalloc_zero,
    mimalloc_block_size,
    mimalloc_allocate,
    mimalloc_allocate_aligned,
    mimalloc_reallocate,
    mimalloc_reallocate_aligned,
    mimalloc_free,
    mimalloc_noop,
    mimalloc_allocate,
    mimalloc_allocate_aligned,
    mimalloc_reallocate,
    mimalloc_reallocate_aligned,
    mimalloc_free,
    mimalloc_self_diagnose,
    mimalloc_is_valid_block,
    mimalloc_noop,
    mimalloc_noop,
    mimalloc_block_of,
};

static dl_allocator_t mimalloc_allocator = { &mimalloc_vtable };

dl_allocator_t *mimalloc_dl_allocator(void) {
    return &mimalloc_allocator;
}
