#include <stdio.h>

#include "test_common.h"
#include "log.h"

int main(void) {
    ml_log_level_t level;

    EXPECT_TRUE(ml_log_level_parse("trace", &level));
    EXPECT_EQ(level, ML_LOG_LEVEL_TRACE);
    EXPECT_TRUE(ml_log_level_parse("DEBUG", &level));
    EXPECT_EQ(level, ML_LOG_LEVEL_DEBUG);
    EXPECT_TRUE(ml_log_level_parse("warning", &level) == false);
    EXPECT_TRUE(ml_log_level_parse(NULL, &level) == false);

    ml_log_set_level(ML_LOG_LEVEL_WARN);
    EXPECT_EQ(ml_log_get_level(), ML_LOG_LEVEL_WARN);
    ml_log_set_level(ML_LOG_LEVEL_OFF);
    EXPECT_EQ(ml_log_get_level(), ML_LOG_LEVEL_OFF);
    printf("smoke_log: all tests passed\n");
    return 0;
}
