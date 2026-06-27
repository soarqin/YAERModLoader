#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "test_common.h"

#ifndef TEST_SOURCE_ROOT
#define TEST_SOURCE_ROOT "."
#endif

static bool has_source_extension(const char *path) {
    const char *dot = strrchr(path, '.');
    if (dot == NULL) return false;
    return _stricmp(dot, ".c") == 0 || _stricmp(dot, ".h") == 0;
}

static int file_contains_text(const char *path, const char *needle, bool *contains) {
    FILE *f = NULL;
    *contains = false;
    if (fopen_s(&f, path, "rb") != 0 || f == NULL) {
        fprintf(stderr, "failed to open %s\n", path);
        return 1;
    }
    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        return 1;
    }
    long len = ftell(f);
    if (len < 0) {
        fclose(f);
        return 1;
    }
    rewind(f);

    char *data = malloc((size_t)len + 1);
    if (data == NULL) {
        fclose(f);
        return 1;
    }
    size_t read_len = fread(data, 1, (size_t)len, f);
    fclose(f);
    if (read_len != (size_t)len) {
        free(data);
        return 1;
    }
    data[len] = '\0';
    *contains = strstr(data, needle) != NULL;
    free(data);
    return 0;
}

static int scan_source_dir(const char *dir, int *violations) {
    char pattern[4096];
    int written = snprintf(pattern, sizeof(pattern), "%s\\*", dir);
    if (written < 0 || (size_t)written >= sizeof(pattern)) return 1;

    WIN32_FIND_DATAA data;
    HANDLE find = FindFirstFileA(pattern, &data);
    if (find == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "failed to scan %s\n", dir);
        return 1;
    }

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
            if (scan_source_dir(path, violations) != 0) result = 1;
            continue;
        }

        if (!has_source_extension(path)) continue;

        bool contains = false;
        if (file_contains_text(path, "MH_ALL_HOOKS", &contains) != 0) {
            result = 1;
            continue;
        }
        if (contains) {
            fprintf(stderr, "%s contains MH_ALL_HOOKS\n", path);
            (*violations)++;
        }
    } while (FindNextFileA(find, &data));

    DWORD last_error = GetLastError();
    FindClose(find);
    if (last_error != ERROR_NO_MORE_FILES) return 1;
    return result;
}

int main(void) {
    char src_dir[4096];
    int written = snprintf(src_dir, sizeof(src_dir), "%s\\src", TEST_SOURCE_ROOT);
    EXPECT_TRUE(written >= 0 && (size_t)written < sizeof(src_dir));

    int violations = 0;
    EXPECT_EQ(scan_source_dir(src_dir, &violations), 0);
    EXPECT_EQ(violations, 0);

    printf("smoke_no_global_minhook: all tests passed\n");
    return 0;
}
