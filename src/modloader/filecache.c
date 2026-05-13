/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "filecache.h"

#include <windows.h>

#define kcalloc(N,Z)  LocalAlloc(LPTR, (N)*(Z))
#define kmalloc(Z)    LocalAlloc(0, (Z))
#define krealloc(P,Z) ((P) ? LocalReAlloc((P), (Z), LMEM_MOVEABLE) : LocalAlloc(0, (Z)))
#define kfree(P)      LocalFree(P)
#include "khash.h"
#include "khash_wstr.h"

#include <shlwapi.h>

typedef struct {
    wchar_t *base_path;
    wchar_t *native_path;
} file_t;

static khash_t(wstr) *files = NULL;

file_t *file_new(const wchar_t *base_path, const wchar_t *native_path) {
    file_t *file = LocalAlloc(0, sizeof(file_t));
    if (file == NULL) {
        return NULL;
    }
    file->base_path = StrDupW(base_path);
    file->native_path = StrDupW(native_path && native_path[0] ? native_path : L"");
    return file;
}

void file_free(file_t *file) {
    if (file == NULL) {
        return;
    }
    if (file->base_path) LocalFree(file->base_path);
    if (file->native_path) LocalFree(file->native_path);
    LocalFree(file);
}

void filecache_init() {
    files = kh_init(wstr);
}

void filecache_uninit() {
    khiter_t k;
    for (k = kh_begin(files); k != kh_end(files); ++k) {
        if (kh_exist(files, k)) {
            file_free((file_t*)kh_value(files, k));
        }
    }
    kh_destroy(wstr, files);
    files = NULL;
}

const wchar_t *filecache_add(const wchar_t *path, const wchar_t *replace) {
    file_t *file = file_new(path, replace);
    if (file == NULL) {
        return NULL;
    }
    int ret;
    khiter_t k = kh_put(wstr, files, file->base_path, &ret);
    if (ret == 0) {
        /* duplicate key — kh_put returns existing slot; free the new file and keep existing */
        file_free(file);
        return (const wchar_t*)kh_value(files, k) ? ((file_t*)kh_value(files, k))->native_path : NULL;
    }
    kh_value(files, k) = file;
    return file->native_path;
}

const wchar_t *filecache_find(const wchar_t *path) {
    khiter_t k = kh_get(wstr, files, path);
    if (k == kh_end(files)) return NULL;
    file_t *file = (file_t*)kh_value(files, k);
    return file->native_path[0] ? file->native_path : NULL;
}
