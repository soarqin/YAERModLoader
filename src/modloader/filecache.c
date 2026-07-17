/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "filecache.h"

#include "allocator.h"

#include <windows.h>

#define kcalloc(N,Z)  yaer_mem_alloc(LPTR, (N)*(Z))
#define kmalloc(Z)    yaer_mem_alloc(0, (Z))
#define krealloc(P,Z) ((P) ? yaer_mem_realloc((P), (Z), LMEM_MOVEABLE) : yaer_mem_alloc(0, (Z)))
#define kfree(P)      yaer_mem_free(P)
#include "khash.h"
#include "khash_wstr.h"

#include <shlwapi.h>

typedef struct {
    wchar_t *base_path;
    wchar_t *native_path;
} file_t;

static khash_t(wstr) *files = NULL;
/* Guards `files`. Game hooks call filecache_find/filecache_add concurrently
 * from multiple threads (CreateFileW hook, archive path hook, Wwise hook).
 * khash is not thread-safe: kh_put may rehash and free internal arrays while
 * another thread is probing them. Returned strings stay valid without the
 * lock because file_t allocations are never freed until filecache_uninit. */
static SRWLOCK files_lock = SRWLOCK_INIT;

void file_free(file_t *file);

file_t *file_new(const wchar_t *base_path, const wchar_t *native_path) {
    file_t *file = yaer_mem_alloc(0, sizeof(file_t));
    if (file == NULL) {
        return NULL;
    }
    file->base_path = yaer_mem_strdup_w(base_path);
    file->native_path = yaer_mem_strdup_w(native_path && native_path[0] ? native_path : L"");
    if (file->base_path == NULL || file->native_path == NULL) {
        file_free(file);
        return NULL;
    }
    return file;
}

void file_free(file_t *file) {
    if (file == NULL) {
        return;
    }
    if (file->base_path) yaer_mem_free(file->base_path);
    if (file->native_path) yaer_mem_free(file->native_path);
    yaer_mem_free(file);
}

void filecache_init() {
    files = kh_init(wstr);
}

void filecache_uninit() {
    khiter_t k;
    if (files == NULL) return;
    AcquireSRWLockExclusive(&files_lock);
    for (k = kh_begin(files); k != kh_end(files); ++k) {
        if (kh_exist(files, k)) {
            file_free((file_t*)kh_value(files, k));
        }
    }
    kh_destroy(wstr, files);
    files = NULL;
    ReleaseSRWLockExclusive(&files_lock);
}

const wchar_t *filecache_add(const wchar_t *path, const wchar_t *replace) {
    file_t *file = file_new(path, replace);
    if (file == NULL) {
        return NULL;
    }
    int ret;
    AcquireSRWLockExclusive(&files_lock);
    khiter_t k = kh_put(wstr, files, file->base_path, &ret);
    if (ret == 0) {
        /* duplicate key — kh_put returns existing slot; free the new file and keep existing */
        const wchar_t *existing = ((file_t*)kh_value(files, k))->native_path;
        ReleaseSRWLockExclusive(&files_lock);
        file_free(file);
        return existing;
    }
    kh_value(files, k) = file;
    ReleaseSRWLockExclusive(&files_lock);
    return file->native_path;
}

/* Returns NULL when `path` has never been cached. For cached entries the
 * stored native path is returned as-is: an empty string marks a negative
 * entry (file not provided by any mod) — callers check res[0]. */
const wchar_t *filecache_find(const wchar_t *path) {
    AcquireSRWLockShared(&files_lock);
    khiter_t k = kh_get(wstr, files, path);
    const wchar_t *res = k == kh_end(files) ? NULL : ((file_t*)kh_value(files, k))->native_path;
    ReleaseSRWLockShared(&files_lock);
    return res;
}
