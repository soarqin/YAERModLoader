#include <stdint.h>
#include <stdio.h>

#include "test_common.h"
#include "process/rtti.h"

int main(void) {
    void *items[3] = { 0 };
    uint32_t offsets[3] = { 0 };
    rtti_vtable_list_t list = { items, 0, 3 };
    int first;
    int second;
    int third;

    rtti_vtable_list_insert(&list, &second, 8, offsets);
    rtti_vtable_list_insert(&list, &first, 0, offsets);
    rtti_vtable_list_insert(&list, &third, 16, offsets);
    rtti_vtable_list_insert(&list, &first, 0, offsets);

    EXPECT_EQ(list.count, 3);
    EXPECT_EQ(list.items[0], &first);
    EXPECT_EQ(list.items[1], &second);
    EXPECT_EQ(list.items[2], &third);
    EXPECT_EQ(offsets[0], 0);
    EXPECT_EQ(offsets[1], 8);
    EXPECT_EQ(offsets[2], 16);
    printf("smoke_rtti: all tests passed\n");
    return 0;
}
