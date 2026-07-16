/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "wwise_path.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdint.h>
#include <wchar.h>

const wchar_t *wwise_strip_prefixes(const wchar_t *path) {
    if (path == NULL) return NULL;

    for (;;) {
        if (wcsncmp(path, L"sd:/", 4) == 0) {
            path += 4;
        } else if (wcsncmp(path, L"sd_dlc02:/", 10) == 0) {
            path += 10;
        } else {
            return path;
        }
    }
}

wchar_t *wwise_join_path(const wchar_t *prefix, const wchar_t *path) {
    size_t prefix_length;
    size_t path_length;
    wchar_t *result;
    if (prefix == NULL || path == NULL) return NULL;
    prefix_length = wcslen(prefix);
    path_length = wcslen(path);
    if (prefix_length > SIZE_MAX - path_length - 1) return NULL;
    result = LocalAlloc(0, (prefix_length + path_length + 1) * sizeof(*result));
    if (result == NULL) return NULL;
    memcpy(result, prefix, prefix_length * sizeof(*result));
    memcpy(result + prefix_length, path, (path_length + 1) * sizeof(*result));
    return result;
}

bool wwise_wem_candidates(const wchar_t *path, wchar_t **first, wchar_t **second) {
    size_t path_length;
    wchar_t prefix[] = L"wem/00/";
    if (first == NULL || second == NULL) return false;
    *first = NULL;
    *second = NULL;
    if (path == NULL || (path_length = wcslen(path)) < 2) return false;
    prefix[4] = path[0];
    prefix[5] = path[1];
    *first = wwise_join_path(L"wem/", path);
    *second = wwise_join_path(prefix, path);
    if (*first == NULL || *second == NULL) {
        LocalFree(*first);
        LocalFree(*second);
        *first = NULL;
        *second = NULL;
        return false;
    }
    return true;
}
