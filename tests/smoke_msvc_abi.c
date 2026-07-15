#include <stdio.h>

#include "test_common.h"
#include "from/abi_msvc2012.h"
#include "from/abi_msvc2015.h"

int main(void) {
    ml_msvc2012_vector_t vector2012 = { 0 };
    ml_msvc2015_vector_t vector2015 = { 0 };
    ml_msvc2012_string_t string2012 = { 0 };
    ml_msvc2015_string_t string2015 = { 0 };

    EXPECT_EQ((char *)&vector2012.allocator - (char *)&vector2012, 24);
    EXPECT_EQ((char *)&vector2015.first - (char *)&vector2015, 8);
    EXPECT_EQ((char *)&string2012.encoding - (char *)&string2012, 40);
    EXPECT_EQ((char *)&string2015.encoding - (char *)&string2015, 40);
    printf("smoke_msvc_abi: all tests passed\n");
    return 0;
}
