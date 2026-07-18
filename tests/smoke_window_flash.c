#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "test_common.h"
#include "modloader/patches/window_flash.h"

int main(void) {
    WNDCLASSEXW source = { 0 };
    WNDCLASSEXW expected;
    WNDCLASSEXW result;
    HBRUSH black_background = (HBRUSH)(uintptr_t)0x1234;

    source.cbSize = sizeof(source);
    source.style = CS_HREDRAW | CS_VREDRAW;
    source.hInstance = (HINSTANCE)(uintptr_t)0x5678;
    source.hbrBackground = (HBRUSH)(uintptr_t)0x9abc;
    source.lpszClassName = L"YAFSMLWindowFlashTest";
    expected = source;
    expected.hbrBackground = black_background;

    memset(&result, 0xcc, sizeof(result));
    ml_window_class_blacken(&source, black_background, &result);

    EXPECT_TRUE(memcmp(&result, &expected, sizeof(result)) == 0);
    EXPECT_TRUE(source.hbrBackground == (HBRUSH)(uintptr_t)0x9abc);
    printf("smoke_window_flash: all tests passed\n");
    return 0;
}
