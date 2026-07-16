#include <stdint.h>
#include <stdio.h>

#include "test_common.h"
#include "modloader/patches/logo.h"

int main(void) {
    void *logo_step = (void *)(uintptr_t)0x1000;
    void *logo_name = (void *)(uintptr_t)0x2000;
    void *title_step = (void *)(uintptr_t)0x3000;
    void *step_table[] = { logo_step, logo_name, title_step };

    EXPECT_TRUE(ml_logo_fd4_redirect(step_table, title_step));
    EXPECT_EQ(step_table[0], title_step);
    EXPECT_EQ(step_table[1], logo_name);
    EXPECT_EQ(step_table[2], title_step);
    EXPECT_TRUE(!ml_logo_fd4_redirect(NULL, title_step));

    EXPECT_TRUE(!ml_logo_fd4_redirect(step_table, NULL));
    EXPECT_EQ(step_table[0], title_step);

    step_table[0] = logo_step;
    EXPECT_TRUE(ml_logo_sprj_redirect(step_table));
    EXPECT_EQ(step_table[0], title_step);
    EXPECT_TRUE(!ml_logo_sprj_redirect(NULL));
    printf("smoke_logo: all tests passed\n");
    return 0;
}
