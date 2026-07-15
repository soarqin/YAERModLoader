#include <stdio.h>
#include <string.h>

#include "test_common.h"
#include "modloader/hook.h"

int main(void) {
    EXPECT_TRUE(strcmp(ml_hook_result_name(ML_HOOK_APPLIED), "APPLIED") == 0);
    EXPECT_TRUE(strcmp(ml_hook_result_name(ML_HOOK_SIGNATURE_NOT_FOUND), "SIGNATURE_NOT_FOUND") == 0);
    EXPECT_TRUE(strcmp(ml_hook_result_name(ML_HOOK_FAILED), "HOOK_FAILED") == 0);
    EXPECT_EQ(ml_hook_install(NULL, NULL, NULL), ML_HOOK_SIGNATURE_NOT_FOUND);
    printf("smoke_hook: all tests passed\n");
    return 0;
}
