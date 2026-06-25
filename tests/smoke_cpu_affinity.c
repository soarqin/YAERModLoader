#include <stdio.h>
#include "test_common.h"
#include "process/cpu_affinity.h"

static int expect_ids(
    int strategy,
    const process_cpu_set_info_t *sets,
    size_t set_count,
    const process_cpu_set_id_t *expected,
    size_t expected_count) {
    process_cpu_set_id_t ids[32] = {0};
    const size_t count = select_process_cpu_set_ids(strategy, sets, set_count, ids, 32);
    EXPECT_EQ((int)count, (int)expected_count);
    for (size_t i = 0; i < expected_count; i++) {
        EXPECT_EQ((int)ids[i], (int)expected[i]);
    }
    return 0;
}

static int test_core_ultra_265k_layout(void) {
    const process_cpu_set_info_t sets[] = {
        {256, 0, 0, 1, 0, 0},
        {257, 0, 1, 1, 0, 0},
        {258, 0, 2, 0, 0, 0},
        {259, 0, 3, 0, 0, 0},
        {260, 0, 4, 0, 0, 0},
        {261, 0, 5, 0, 0, 0},
        {262, 0, 6, 1, 0, 0},
        {263, 0, 7, 1, 0, 0},
        {264, 0, 8, 1, 0, 0},
        {265, 0, 9, 1, 0, 0},
        {266, 0, 10, 0, 0, 0},
        {267, 0, 11, 0, 0, 0},
        {268, 0, 12, 0, 0, 0},
        {269, 0, 13, 0, 0, 0},
        {270, 0, 14, 0, 0, 0},
        {271, 0, 15, 0, 0, 0},
        {272, 0, 16, 0, 0, 0},
        {273, 0, 17, 0, 0, 0},
        {274, 0, 18, 1, 0, 0},
        {275, 0, 19, 1, 0, 0},
    };
    const process_cpu_set_id_t strategy1[] = {
        257, 258, 259, 260, 261, 262, 263, 264, 265, 266,
        267, 268, 269, 270, 271, 272, 273, 274, 275
    };
    const process_cpu_set_id_t strategy2[] = {
        258, 259, 260, 261, 266, 267, 268, 269, 270, 271, 272, 273
    };
    const process_cpu_set_id_t strategy3[] = {
        256, 257, 262, 263, 264, 265, 274, 275
    };
    const process_cpu_set_id_t strategy4[] = {
        257, 262, 263, 264, 265, 274, 275
    };
    EXPECT_EQ(expect_ids(1, sets, 20, strategy1, 19), 0);
    EXPECT_EQ(expect_ids(2, sets, 20, strategy2, 12), 0);
    EXPECT_EQ(expect_ids(3, sets, 20, strategy3, 8), 0);
    EXPECT_EQ(expect_ids(4, sets, 20, strategy4, 7), 0);
    return 0;
}

static int test_multiple_processor_groups_are_not_truncated(void) {
    const process_cpu_set_info_t sets[] = {
        {100, 0, 0, 0, 0, 0},
        {101, 0, 1, 1, 0, 0},
        {200, 1, 0, 0, 0, 0},
        {201, 1, 1, 1, 0, 0},
        {300, 2, 0, 0, 0, 0},
        {301, 2, 1, 1, 0, 0},
    };
    const process_cpu_set_id_t strategy1[] = {101, 200, 201, 300, 301};
    const process_cpu_set_id_t strategy2[] = {100, 200, 300};
    const process_cpu_set_id_t strategy3[] = {101, 201, 301};
    const process_cpu_set_id_t strategy4[] = {201, 301};
    EXPECT_EQ(expect_ids(1, sets, 6, strategy1, 5), 0);
    EXPECT_EQ(expect_ids(2, sets, 6, strategy2, 3), 0);
    EXPECT_EQ(expect_ids(3, sets, 6, strategy3, 3), 0);
    EXPECT_EQ(expect_ids(4, sets, 6, strategy4, 2), 0);
    return 0;
}

static int test_reserved_cpu_sets_owned_by_other_processes_are_skipped(void) {
    const process_cpu_set_info_t sets[] = {
        {10, 0, 0, 0, 0, 0},
        {11, 0, 1, 1, 1, 0},
        {12, 0, 2, 1, 1, 1},
    };
    const process_cpu_set_id_t strategy3[] = {12};
    EXPECT_EQ(expect_ids(3, sets, 3, strategy3, 1), 0);
    return 0;
}

int main(void) {
    EXPECT_EQ(test_core_ultra_265k_layout(), 0);
    EXPECT_EQ(test_multiple_processor_groups_are_not_truncated(), 0);
    EXPECT_EQ(test_reserved_cpu_sets_owned_by_other_processes_are_skipped(), 0);
    printf("smoke_cpu_affinity: all tests passed\n");
    return 0;
}
