#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "test_common.h"
#include "modloader/mimalloc_allocator.h"

int main(void) {
    EXPECT_TRUE(mimalloc_dl_allocator_prepare(64));
    dl_allocator_t *allocator = mimalloc_dl_allocator();
    EXPECT_NOT_NULL(allocator);
    EXPECT_NOT_NULL(allocator->vtable);

    void *ptr = allocator->vtable->allocate(allocator, 7);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQ((uintptr_t)ptr % 16, 0);
    EXPECT_TRUE(allocator->vtable->block_size(allocator, ptr) >= 7);
    allocator->vtable->free(allocator, ptr);

    ptr = allocator->vtable->allocate_aligned(allocator, 33, 64);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQ((uintptr_t)ptr % 64, 0);
    memset(ptr, 0x5a, 33);

    void *grown = allocator->vtable->reallocate_aligned(allocator, ptr, 96, 64);
    EXPECT_NOT_NULL(grown);
    EXPECT_EQ((uintptr_t)grown % 64, 0);
    EXPECT_EQ(((unsigned char *)grown)[0], 0x5a);
    EXPECT_EQ(((unsigned char *)grown)[32], 0x5a);
    allocator->vtable->free(allocator, grown);

    ptr = allocator->vtable->back_allocate_aligned(allocator, 33, 32);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQ((uintptr_t)ptr % 32, 0);
    allocator->vtable->back_free(allocator, ptr);

    EXPECT_EQ(allocator->vtable->block_size(allocator, NULL), 0);

    printf("smoke_mimalloc_allocator: all tests passed\n");
    return 0;
}
