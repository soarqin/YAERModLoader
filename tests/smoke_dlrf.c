#include <stdio.h>

#include "test_common.h"
#include "process/dlrf.h"

typedef struct fake_runtime_class_s {
    void *vtable;
} fake_runtime_class_t;

int main(void) {
    struct {
        unsigned char type_ids[3];
        fake_runtime_class_t classes[3];
        dlrf_runtime_class_entry_t entries[4];
    } data = { 0 };
    void *vtable = &data;
    dlrf_range_t data_range = { (const unsigned char *)&data, sizeof(data) };
    dlrf_range_t rdata = { (const unsigned char *)&vtable, sizeof(vtable) };
    const dlrf_runtime_class_entry_t *registry = NULL;

    data.classes[0].vtable = &vtable;
    data.classes[1].vtable = &vtable;
    data.classes[2].vtable = &vtable;
    data.entries[0] = (dlrf_runtime_class_entry_t){ &data.type_ids[0], &data.classes[0] };
    data.entries[1] = (dlrf_runtime_class_entry_t){ &data.type_ids[1], &data.classes[1] };
    data.entries[2] = (dlrf_runtime_class_entry_t){ &data.type_ids[2], &data.classes[2] };

    EXPECT_EQ(dlrf_find_registry(data.entries, 4, data_range, rdata, &registry), 3);
    EXPECT_EQ(registry, data.entries);
    printf("smoke_dlrf: all tests passed\n");
    return 0;
}
