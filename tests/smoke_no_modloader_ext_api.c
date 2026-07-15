#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "test_common.h"

#ifndef TEST_SOURCE_ROOT
#define TEST_SOURCE_ROOT "."
#endif

static const char *forbidden[] = {
    "modloader_ext_init",
    "modloader_ext_api_t",
    "modloader_ext_def_t",
    "extdll_api.h",
};

static bool has_checked_extension(const char *path) {
    const char *dot = strrchr(path, '.');
    if (dot == NULL) return false;
    return _stricmp(dot, ".c") == 0 || _stricmp(dot, ".h") == 0 || _stricmp(dot, ".cmake") == 0;
}

static int scan_file(const char *path, int *violations) {
    FILE *file = NULL;
    if (fopen_s(&file, path, "rb") != 0 || file == NULL) return 1;
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return 1;
    }
    long length = ftell(file);
    if (length < 0) {
        fclose(file);
        return 1;
    }
    rewind(file);
    char *data = malloc((size_t)length + 1);
    if (data == NULL) {
        fclose(file);
        return 1;
    }
    size_t read_length = fread(data, 1, (size_t)length, file);
    fclose(file);
    if (read_length != (size_t)length) {
        free(data);
        return 1;
    }
    data[length] = '\0';
    for (size_t i = 0; i < sizeof(forbidden) / sizeof(forbidden[0]); i++) {
        if (strstr(data, forbidden[i]) != NULL) {
            fprintf(stderr, "%s contains %s\n", path, forbidden[i]);
            (*violations)++;
        }
    }
    free(data);
    return 0;
}

static int scan_dir(const char *dir, int *violations) {
    char pattern[4096];
    int written = snprintf(pattern, sizeof(pattern), "%s\\*", dir);
    if (written < 0 || (size_t)written >= sizeof(pattern)) return 1;
    WIN32_FIND_DATAA data;
    HANDLE find = FindFirstFileA(pattern, &data);
    if (find == INVALID_HANDLE_VALUE) return 1;
    int result = 0;
    do {
        if (strcmp(data.cFileName, ".") == 0 || strcmp(data.cFileName, "..") == 0) continue;
        char path[4096];
        written = snprintf(path, sizeof(path), "%s\\%s", dir, data.cFileName);
        if (written < 0 || (size_t)written >= sizeof(path)) {
            result = 1;
            break;
        }
        if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) {
            if (scan_dir(path, violations) != 0) result = 1;
        } else if (has_checked_extension(path) && scan_file(path, violations) != 0) {
            result = 1;
        }
    } while (FindNextFileA(find, &data));
    DWORD error = GetLastError();
    FindClose(find);
    return error == ERROR_NO_MORE_FILES ? result : 1;
}

int main(void) {
    char src_dir[4096];
    int written = snprintf(src_dir, sizeof(src_dir), "%s\\src", TEST_SOURCE_ROOT);
    EXPECT_TRUE(written >= 0 && (size_t)written < sizeof(src_dir));
    int violations = 0;
    EXPECT_EQ(scan_dir(src_dir, &violations), 0);
    EXPECT_EQ(violations, 0);
    printf("smoke_no_modloader_ext_api: all tests passed\n");
    return 0;
}
