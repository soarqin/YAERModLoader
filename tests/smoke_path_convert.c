#include <stdio.h>
#include <string.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "test_common.h"
#include "modloader/path_convert.h"

int main(void) {
    char path[700];
    wchar_t *wide;

    memset(path, 'a', sizeof(path));
    path[0] = 'C';
    path[1] = ':';
    path[2] = '\\';
    path[sizeof(path) - 1] = '\0';
    wide = ml_path_from_ansi(path);
    EXPECT_NOT_NULL(wide);
    EXPECT_EQ(wcslen(wide), strlen(path));
    EXPECT_TRUE(wide[0] == L'C' && wide[2] == L'\\');
    EXPECT_TRUE(wide[sizeof(path) - 2] == L'a');
    LocalFree(wide);
    EXPECT_NULL(ml_path_from_ansi(NULL));

    printf("smoke_path_convert: all tests passed\n");
    return 0;
}
