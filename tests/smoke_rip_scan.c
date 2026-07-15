#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "test_common.h"
#include "process/rip_scan.h"

int main(void) {
    uint8_t image[128] = { 0 };
    const wchar_t *property = L"Game.Debug.NearOnlyDraw";
    uint8_t *text = image;
    uint8_t *rdata = image + 64;
    uint8_t *instruction = text + 8;
    int64_t displacement;

    memcpy(rdata, property, (wcslen(property) + 1) * sizeof(wchar_t));
    instruction[0] = 0x48;
    instruction[1] = 0x8d;
    instruction[2] = 0x0d;
    displacement = (int64_t)(rdata - (instruction + 7));
    EXPECT_TRUE(displacement >= INT32_MIN && displacement <= INT32_MAX);
    {
        int32_t relative = (int32_t)displacement;
        memcpy(instruction + 3, &relative, sizeof(relative));
    }

    EXPECT_EQ(ml_find_utf16_string(rdata, 64, property), rdata);
    EXPECT_EQ(ml_find_rip_relative_lea(text, 64, rdata), instruction);
    instruction[1] = 0x8b;
    EXPECT_EQ(ml_find_rip_relative_lea(text, 64, rdata), instruction);
    EXPECT_NULL(ml_find_utf16_string(rdata, 16, property));
    EXPECT_NULL(ml_find_rip_relative_lea(text, 7, rdata));
    printf("smoke_rip_scan: all tests passed\n");
    return 0;
}
