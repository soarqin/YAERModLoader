/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "filecache.h"

#define uthash_malloc(sz) LocalAlloc(0, sz)
#define uthash_free(ptr,sz) LocalFree(ptr)
#define uthash_bzero(a,n) ZeroMemory(a, n)
#define uthash_strlen(s) lstrlenA(s)

#include <uthash.h>
#include <shlwapi.h>

typedef struct {
    wchar_t *base_path;
    wchar_t *native_path;

    UT_hash_handle hh;
} file_t;

static file_t *files = NULL;

file_t *file_new(const wchar_t *base_path, const wchar_t *native_path) {
    file_t *file = LocalAlloc(0, sizeof(file_t));
    if (file == NULL) {
        return NULL;
    }
    file->base_path = StrDupW(base_path);
    file->native_path = native_path && native_path[0] ? StrDupW(native_path) : NULL;
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
    files = NULL;
}

void filecache_uninit() {
    file_t *file, *tmp;
    HASH_ITER(hh, files, file, tmp) {
        HASH_DEL(files, file);
        file_free(file);
    }
}

const wchar_t *filecache_add(const wchar_t *path, const wchar_t *replace) {
    file_t *file = file_new(path, replace);
    if (file == NULL) {
        return NULL;
    }
    HASH_ADD_KEYPTR(hh, files, file->base_path, sizeof(wchar_t) * lstrlenW(file->base_path), file);
    return file->native_path;
}

const wchar_t *filecache_find(const wchar_t *path) {
    file_t *file = NULL;
    HASH_FIND(hh, files, path, sizeof(wchar_t) * lstrlenW(path), file);
    if (!file) return NULL;
    return file->native_path;
}
