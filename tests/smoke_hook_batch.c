#include <stdio.h>

#include "test_common.h"
#include "modloader/hook_batch.h"

static size_t install_count;
static size_t remove_count;
static size_t fail_at;
static size_t remove_fail_at;
static void *removed[15];

static ml_hook_result_t fake_install(void *target, void *detour, void **original) {
    (void)target;
    (void)detour;
    (void)original;
    return install_count++ == fail_at ? ML_HOOK_FAILED : ML_HOOK_APPLIED;
}

static bool fake_remove(void *target) {
    removed[remove_count++] = target;
    return remove_count - 1 != remove_fail_at;
}

int main(void) {
    ml_hook_spec_t specs[15];
    bool rollback_complete;
    for (size_t i = 0; i < 15; i++) {
        specs[i] = (ml_hook_spec_t){ (void *)(i + 1), (void *)1, NULL };
    }

    for (fail_at = 0; fail_at < 15; fail_at++) {
        install_count = 0;
        remove_count = 0;
        remove_fail_at = 15;
        EXPECT_TRUE(!ml_hook_batch_install(specs, 15, fake_install, fake_remove, &rollback_complete));
        EXPECT_TRUE(rollback_complete);
        EXPECT_EQ(install_count, fail_at + 1);
        EXPECT_EQ(remove_count, fail_at);
        for (size_t i = 0; i < remove_count; i++) {
            EXPECT_EQ(removed[i], specs[fail_at - i - 1].target);
        }
    }

    fail_at = 15;
    install_count = 0;
    remove_count = 0;
    remove_fail_at = 15;
    EXPECT_TRUE(ml_hook_batch_install(specs, 15, fake_install, fake_remove, &rollback_complete));
    EXPECT_TRUE(rollback_complete);
    EXPECT_EQ(remove_count, 0);
    EXPECT_TRUE(ml_hook_batch_remove(specs, 15, fake_remove));
    EXPECT_EQ(remove_count, 15);
    for (size_t i = 0; i < 15; i++) EXPECT_EQ(removed[i], specs[14 - i].target);

    remove_count = 0;
    remove_fail_at = 7;
    EXPECT_TRUE(!ml_hook_batch_remove(specs, 15, fake_remove));
    EXPECT_EQ(remove_count, 15);

    fail_at = 8;
    install_count = 0;
    remove_count = 0;
    remove_fail_at = 3;
    EXPECT_TRUE(!ml_hook_batch_install(specs, 15, fake_install, fake_remove, &rollback_complete));
    EXPECT_TRUE(!rollback_complete);
    EXPECT_EQ(remove_count, 8);

    specs[4].target = NULL;
    remove_count = 0;
    remove_fail_at = 15;
    EXPECT_TRUE(ml_hook_batch_remove(specs, 15, fake_remove));
    EXPECT_EQ(remove_count, 14);

    {
        void *targets[] = { (void *)1, NULL, (void *)2, (void *)1, (void *)3, (void *)2 };
        remove_count = 0;
        remove_fail_at = 15;
        EXPECT_TRUE(ml_hook_targets_remove_unique(targets, 6, fake_remove));
        EXPECT_EQ(remove_count, 3);
        EXPECT_EQ(removed[0], (void *)3);
        EXPECT_EQ(removed[1], (void *)2);
        EXPECT_EQ(removed[2], (void *)1);

        remove_count = 0;
        remove_fail_at = 1;
        EXPECT_TRUE(!ml_hook_targets_remove_unique(targets, 6, fake_remove));
        EXPECT_EQ(remove_count, 3);
    }

    printf("smoke_hook_batch: all tests passed\n");
    return 0;
}
