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
    EXPECT_TRUE(!ml_log_enabled(ML_LOG_LEVEL_INFO));
    EXPECT_TRUE(ml_log_enabled(ML_LOG_LEVEL_WARN));
    EXPECT_TRUE(ml_log_enabled(ML_LOG_LEVEL_ERROR));
    ml_log_set_level(ML_LOG_LEVEL_OFF);
    EXPECT_TRUE(!ml_log_enabled(ML_LOG_LEVEL_ERROR));
    printf("smoke_log: all tests passed\n");
    return 0;
}
