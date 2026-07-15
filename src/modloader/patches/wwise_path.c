/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "wwise_path.h"

#include <stdio.h>
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

bool wwise_wem_candidates(const wchar_t *path, wchar_t *first, size_t first_count,
                          wchar_t *second, size_t second_count) {
    size_t length;
    if (path == NULL || first == NULL || second == NULL || first_count == 0 || second_count == 0) return false;

    length = wcslen(path);
    if (length < 2 || _snwprintf(first, first_count, L"wem/%ls", path) < 0 ||
        _snwprintf(second, second_count, L"wem/%.*ls/%ls", 2, path, path) < 0) {
        first[first_count - 1] = L'\0';
        second[second_count - 1] = L'\0';
        return false;
    }
    first[first_count - 1] = L'\0';
    second[second_count - 1] = L'\0';
    return true;
}
