/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "vfs.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>

#include <wctype.h>
#include <stdlib.h>

#define kcalloc(N,Z) LocalAlloc(LPTR, (N) * (Z))
#define kmalloc(Z) LocalAlloc(0, (Z))
#define krealloc(P,Z) ((P) ? LocalReAlloc((P), (Z), LMEM_MOVEABLE) : LocalAlloc(0, (Z)))
#define kfree(P) LocalFree(P)
#include "khash.h"
#include "khash_wstr.h"

typedef struct vfs_entry_s {
    wchar_t *key;
    wchar_t *path;
} vfs_entry_t;

typedef struct vfs_writable_entry_s {
    wchar_t *key;
    wchar_t *path;
} vfs_writable_entry_t;

KHASH_INIT(vfs_index, const wchar_t *, size_t, 1, kh_wstr_hash_func, kh_wstr_hash_equal)
KHASH_INIT(vfs_lookup_cache, const wchar_t *, const wchar_t *, 1, kh_wstr_hash_func, kh_wstr_hash_equal)

static khash_t(vfs_index) *index;
static khash_t(vfs_lookup_cache) *lookup_caches[VFS_LOOKUP_DOMAIN_COUNT];
static khash_t(vfs_lookup_cache) *uid_cache;
static vfs_entry_t *entries;
static size_t entry_count;
static size_t entry_capacity;
static volatile LONG frozen;
static volatile LONG64 generation;
static volatile LONG64 generation_sequence;
static SRWLOCK lookup_cache_lock = SRWLOCK_INIT;
static SRWLOCK writable_lock = SRWLOCK_INIT;
static __declspec(thread) unsigned int vfs_recursion_depth;
static vfs_writable_entry_t *writable_entries;
static size_t writable_count;
static size_t writable_capacity;

static wchar_t *vfs_join(const wchar_t *left, const wchar_t *right) {
    size_t left_len = wcslen(left);
    size_t right_len = wcslen(right);
    wchar_t *result = LocalAlloc(0, (left_len + right_len + 2) * sizeof(*result));
    if (result == NULL) return NULL;
    memcpy(result, left, left_len * sizeof(*result));
    if (left_len != 0 && left[left_len - 1] != L'\\') result[left_len++] = L'\\';
    memcpy(result + left_len, right, (right_len + 1) * sizeof(*result));
    return result;
}

bool vfs_normalize_path(const wchar_t *path, wchar_t **normalized) {
    size_t length;
    wchar_t *result;
    size_t *segment_starts;
    size_t out = 0;
    size_t segment_count = 0;
    if (normalized == NULL || path == NULL) return false;
    *normalized = NULL;
    length = wcslen(path);
    if (length == SIZE_MAX || length + 1 > SIZE_MAX / sizeof(*result) ||
        length + 1 > SIZE_MAX / sizeof(*segment_starts)) return false;
    result = LocalAlloc(0, (length + 1) * sizeof(*result));
    if (result == NULL) return false;
    segment_starts = LocalAlloc(0, (length + 1) * sizeof(*segment_starts));
    if (segment_starts == NULL) {
        LocalFree(result);
        return false;
    }

    while (*path == L'\\' || *path == L'/') path++;
    if (path[0] != L'\0' && path[1] == L':') {
        path += 2;
        while (*path == L'\\' || *path == L'/') path++;
    }
    while (*path != L'\0') {
        const wchar_t *start = path;
        size_t part_len;
        while (*path != L'\0' && *path != L'\\' && *path != L'/') path++;
        part_len = (size_t)(path - start);
        while (*path == L'\\' || *path == L'/') path++;
        if (part_len == 0 || (part_len == 1 && start[0] == L'.')) continue;
        if (part_len == 2 && start[0] == L'.' && start[1] == L'.') {
            if (segment_count == 0) {
                LocalFree(segment_starts);
                LocalFree(result);
                return false;
            }
            out = segment_starts[--segment_count];
            continue;
        }
        segment_starts[segment_count++] = out;
        if (out != 0) result[out++] = L'\\';
        for (size_t i = 0; i < part_len; i++) result[out++] = towlower(start[i]);
    }
    result[out] = L'\0';
    LocalFree(segment_starts);
    *normalized = result;
    return true;
}

static bool vfs_insert(const wchar_t *relative, const wchar_t *physical) {
    wchar_t *key;
    wchar_t *path;
    khiter_t slot;
    int ret;
    if (!vfs_normalize_path(relative, &key)) return false;
    path = StrDupW(physical);
    if (path == NULL) {
        LocalFree(key);
        return false;
    }
    slot = kh_put(vfs_index, index, key, &ret);
    if (ret < 0) {
        LocalFree(key);
        LocalFree(path);
        return false;
    }
    if (ret == 0) {
        vfs_entry_t *entry = &entries[kh_value(index, slot)];
        LocalFree(entry->path);
        entry->path = path;
        LocalFree(key);
        return true;
    }
    if (entry_count == entry_capacity) {
        size_t capacity = entry_capacity == 0 ? 128 : entry_capacity * 2;
        vfs_entry_t *new_entries = entries == NULL
            ? LocalAlloc(LMEM_ZEROINIT, capacity * sizeof(*entries))
            : LocalReAlloc(entries, capacity * sizeof(*entries), LMEM_MOVEABLE | LMEM_ZEROINIT);
        if (new_entries == NULL) {
            kh_del(vfs_index, index, slot);
            LocalFree(key);
            LocalFree(path);
            return false;
        }
        entries = new_entries;
        entry_capacity = capacity;
    }
    kh_key(index, slot) = key;
    kh_value(index, slot) = entry_count;
    entries[entry_count++] = (vfs_entry_t){ key, path };
    return true;
}

static bool vfs_scan(const wchar_t *root, const wchar_t *relative) {
    wchar_t *directory = relative[0] == L'\0' ? StrDupW(root) : vfs_join(root, relative);
    wchar_t *pattern;
    WIN32_FIND_DATAW find;
    HANDLE handle;
    if (directory == NULL) return false;
    pattern = vfs_join(directory, L"*");
    LocalFree(directory);
    if (pattern == NULL) return false;
    handle = FindFirstFileW(pattern, &find);
    LocalFree(pattern);
    if (handle == INVALID_HANDLE_VALUE) return false;
    do {
        if (lstrcmpW(find.cFileName, L".") == 0 || lstrcmpW(find.cFileName, L"..") == 0) continue;
        wchar_t *child_relative = relative[0] == L'\0' ? StrDupW(find.cFileName) : vfs_join(relative, find.cFileName);
        wchar_t *child_path = child_relative == NULL ? NULL : vfs_join(root, child_relative);
        if (child_relative == NULL || child_path == NULL) {
            LocalFree(child_relative);
            LocalFree(child_path);
            FindClose(handle);
            return false;
        }
        if ((find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) {
            if ((find.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) == 0 && !vfs_scan(root, child_relative)) {
                LocalFree(child_relative);
                LocalFree(child_path);
                FindClose(handle);
                return false;
            }
        } else {
            if (!vfs_insert(child_relative, child_path)) {
                LocalFree(child_relative);
                LocalFree(child_path);
                FindClose(handle);
                return false;
            }
        }
        LocalFree(child_relative);
        LocalFree(child_path);
    } while (FindNextFileW(handle, &find));
    FindClose(handle);
    return true;
}

void vfs_init(void) {
    index = kh_init(vfs_index);
    for (size_t i = 0; i < VFS_LOOKUP_DOMAIN_COUNT; i++) {
        lookup_caches[i] = kh_init(vfs_lookup_cache);
    }
    uid_cache = kh_init(vfs_lookup_cache);
    entries = NULL;
    entry_count = 0;
    entry_capacity = 0;
    InterlockedExchange(&frozen, FALSE);
    InterlockedExchange64(&generation, 0);
    InterlockedExchange64(&generation_sequence, 0);
    writable_entries = NULL;
    writable_count = 0;
    writable_capacity = 0;
}

void vfs_uninit(void) {
    if (entries != NULL) {
        for (size_t i = 0; i < entry_count; i++) {
            LocalFree(entries[i].key);
            LocalFree(entries[i].path);
        }
        LocalFree(entries);
    }
    for (size_t i = 0; i < VFS_LOOKUP_DOMAIN_COUNT; i++) {
        khash_t(vfs_lookup_cache) *cache = lookup_caches[i];
        if (cache != NULL) {
            for (khiter_t slot = kh_begin(cache); slot != kh_end(cache); slot++) {
                if (kh_exist(cache, slot)) LocalFree((void *)kh_key(cache, slot));
            }
            kh_destroy(vfs_lookup_cache, cache);
        }
        lookup_caches[i] = NULL;
    }
    if (uid_cache != NULL) {
        for (khiter_t slot = kh_begin(uid_cache); slot != kh_end(uid_cache); slot++) {
            if (kh_exist(uid_cache, slot)) {
                LocalFree((void *)kh_key(uid_cache, slot));
                LocalFree((void *)kh_value(uid_cache, slot));
            }
        }
        kh_destroy(vfs_lookup_cache, uid_cache);
        uid_cache = NULL;
    }
    if (index != NULL) kh_destroy(vfs_index, index);
    for (size_t i = 0; i < writable_count; i++) {
        LocalFree(writable_entries[i].key);
        LocalFree(writable_entries[i].path);
    }
    LocalFree(writable_entries);
    index = NULL;
    entries = NULL;
    entry_count = 0;
    entry_capacity = 0;
    InterlockedExchange(&frozen, FALSE);
    InterlockedExchange64(&generation, 0);
    InterlockedExchange64(&generation_sequence, 0);
    writable_entries = NULL;
    writable_count = 0;
    writable_capacity = 0;
}

bool vfs_add_package(const wchar_t *path) {
    if (index == NULL || InterlockedCompareExchange(&frozen, FALSE, FALSE) || path == NULL || !PathIsDirectoryW(path)) return false;
    return vfs_scan(path, L"");
}

bool vfs_register_writable_path(const wchar_t *virtual_path, const wchar_t *physical_path) {
    wchar_t *key;
    wchar_t *path;
    if (virtual_path == NULL || physical_path == NULL || physical_path[0] == L'\0' || !vfs_normalize_path(virtual_path, &key)) return false;
    if (key[0] == L'\0') {
        LocalFree(key);
        return false;
    }
    path = StrDupW(physical_path);
    if (path == NULL) {
        LocalFree(key);
        return false;
    }
    AcquireSRWLockExclusive(&writable_lock);
    for (size_t i = 0; i < writable_count; i++) {
        if (wcscmp(key, writable_entries[i].key) == 0) {
            bool same = CompareStringOrdinal(path, -1, writable_entries[i].path, -1, TRUE) == CSTR_EQUAL;
            LocalFree(path);
            LocalFree(key);
            ReleaseSRWLockExclusive(&writable_lock);
            return same;
        }
    }
    if (writable_count == writable_capacity) {
        size_t capacity = writable_capacity == 0 ? 8 : writable_capacity * 2;
        vfs_writable_entry_t *new_entries = writable_entries == NULL
            ? LocalAlloc(LMEM_ZEROINIT, capacity * sizeof(*writable_entries))
            : LocalReAlloc(writable_entries, capacity * sizeof(*writable_entries), LMEM_MOVEABLE | LMEM_ZEROINIT);
        if (new_entries == NULL) {
            LocalFree(key);
            LocalFree(path);
            ReleaseSRWLockExclusive(&writable_lock);
            return false;
        }
        writable_entries = new_entries;
        writable_capacity = capacity;
    }
    writable_entries[writable_count++] = (vfs_writable_entry_t){ key, path };
    ReleaseSRWLockExclusive(&writable_lock);
    return true;
}

bool vfs_has_writable_paths(void) {
    bool result;
    AcquireSRWLockShared(&writable_lock);
    result = writable_count != 0;
    ReleaseSRWLockShared(&writable_lock);
    return result;
}

const wchar_t *vfs_lookup(const wchar_t *path) {
    return vfs_lookup_domain(path, VFS_LOOKUP_VIRTUAL);
}

const wchar_t *vfs_lookup_domain(const wchar_t *path, vfs_lookup_domain_t domain) {
    wchar_t *key;
    khiter_t slot;
    const wchar_t *result;
    uint64_t lookup_generation;
    khash_t(vfs_lookup_cache) *cache;
    if (index == NULL || path == NULL || domain < 0 || domain >= VFS_LOOKUP_DOMAIN_COUNT) return NULL;
    cache = lookup_caches[domain];
    if (cache == NULL) return NULL;

    result = vfs_uid_to_path(path);
    if (result != NULL) return result;

    lookup_generation = vfs_generation();
    if (lookup_generation != 0) {
        AcquireSRWLockShared(&lookup_cache_lock);
        slot = kh_get(vfs_lookup_cache, cache, path);
        if (slot != kh_end(cache)) {
            result = kh_value(cache, slot);
            ReleaseSRWLockShared(&lookup_cache_lock);
            return result;
        }
        ReleaseSRWLockShared(&lookup_cache_lock);
    }

    if (!vfs_normalize_path(path, &key)) return NULL;
    slot = kh_get(vfs_index, index, key);
    LocalFree(key);
    result = slot == kh_end(index) ? NULL : entries[kh_value(index, slot)].path;

    if (lookup_generation == 0) return result;
    wchar_t *cache_key = StrDupW(path);
    if (cache_key == NULL) return result;
    AcquireSRWLockExclusive(&lookup_cache_lock);
    if (vfs_generation() != lookup_generation) {
        ReleaseSRWLockExclusive(&lookup_cache_lock);
        LocalFree(cache_key);
        return result;
    }
    slot = kh_get(vfs_lookup_cache, cache, cache_key);
    if (slot != kh_end(cache)) {
        result = kh_value(cache, slot);
        LocalFree(cache_key);
    } else {
        int ret;
        slot = kh_put(vfs_lookup_cache, cache, cache_key, &ret);
        if (ret < 0) {
            LocalFree(cache_key);
        } else {
            kh_value(cache, slot) = result;
        }
    }
    ReleaseSRWLockExclusive(&lookup_cache_lock);
    return result;
}

uint64_t vfs_generation(void) {
    return (uint64_t)InterlockedCompareExchange64(&generation, 0, 0);
}

static void clear_lookup_cache_locked(void) {
    for (size_t i = 0; i < VFS_LOOKUP_DOMAIN_COUNT; i++) {
        khash_t(vfs_lookup_cache) *cache = lookup_caches[i];
        if (cache == NULL) continue;
        for (khiter_t slot = kh_begin(cache); slot != kh_end(cache); slot++) {
            if (kh_exist(cache, slot)) LocalFree((void *)kh_key(cache, slot));
        }
        kh_clear(vfs_lookup_cache, cache);
    }
    if (uid_cache != NULL) {
        for (khiter_t slot = kh_begin(uid_cache); slot != kh_end(uid_cache); slot++) {
            if (kh_exist(uid_cache, slot)) {
                LocalFree((void *)kh_key(uid_cache, slot));
                LocalFree((void *)kh_value(uid_cache, slot));
            }
        }
        kh_clear(vfs_lookup_cache, uid_cache);
    }
}

void vfs_begin_lookup_reset(void) {
    InterlockedExchange(&frozen, TRUE);
    AcquireSRWLockExclusive(&lookup_cache_lock);
    InterlockedExchange64(&generation, 0);
    clear_lookup_cache_locked();
    ReleaseSRWLockExclusive(&lookup_cache_lock);
}

uint64_t vfs_reset_lookup_caches(void) {
    uint64_t next;
    AcquireSRWLockExclusive(&lookup_cache_lock);
    InterlockedExchange(&frozen, TRUE);
    clear_lookup_cache_locked();
    next = (uint64_t)InterlockedIncrement64(&generation_sequence);
    InterlockedExchange64(&generation, (LONG64)next);
    ReleaseSRWLockExclusive(&lookup_cache_lock);
    return next;
}

bool vfs_virtual_to_uid(const wchar_t *path, wchar_t **uid) {
    wchar_t *key;
    khiter_t slot;
    uint64_t current;
    int length;
    wchar_t *result;
    wchar_t *cache_key;
    int ret;
    if (uid == NULL) return false;
    *uid = NULL;
    AcquireSRWLockShared(&lookup_cache_lock);
    current = vfs_generation();
    if (current == 0 || path == NULL || index == NULL || uid_cache == NULL) {
        ReleaseSRWLockShared(&lookup_cache_lock);
        return false;
    }
    slot = kh_get(vfs_lookup_cache, uid_cache, path);
    if (slot != kh_end(uid_cache)) {
        const wchar_t *cached = kh_value(uid_cache, slot);
        if (cached != NULL) *uid = StrDupW(cached);
        ReleaseSRWLockShared(&lookup_cache_lock);
        return *uid != NULL;
    }
    ReleaseSRWLockShared(&lookup_cache_lock);

    if (!vfs_normalize_path(path, &key)) return false;
    slot = kh_get(vfs_index, index, key);
    LocalFree(key);
    result = NULL;
    if (slot != kh_end(index)) {
        length = _scwprintf(L"\\\\YAERModLoader?%llu?%zx", (unsigned long long)current,
                            (size_t)kh_value(index, slot));
        if (length < 0) return false;
        result = LocalAlloc(0, ((size_t)length + 1) * sizeof(*result));
        if (result == NULL) return false;
        _snwprintf(result, (size_t)length + 1, L"\\\\YAERModLoader?%llu?%zx",
                   (unsigned long long)current, (size_t)kh_value(index, slot));
    }
    cache_key = StrDupW(path);
    if (cache_key == NULL) {
        *uid = result;
        return result != NULL;
    }
    AcquireSRWLockExclusive(&lookup_cache_lock);
    if (vfs_generation() != current) {
        ReleaseSRWLockExclusive(&lookup_cache_lock);
        LocalFree(cache_key);
        LocalFree(result);
        return false;
    }
    slot = kh_get(vfs_lookup_cache, uid_cache, cache_key);
    if (slot != kh_end(uid_cache)) {
        const wchar_t *cached = kh_value(uid_cache, slot);
        if (cached != NULL) *uid = StrDupW(cached);
        LocalFree(cache_key);
        LocalFree(result);
    } else {
        slot = kh_put(vfs_lookup_cache, uid_cache, cache_key, &ret);
        if (ret < 0) {
            LocalFree(cache_key);
            *uid = result;
        } else {
            kh_value(uid_cache, slot) = result;
            if (result != NULL) *uid = StrDupW(result);
        }
    }
    ReleaseSRWLockExclusive(&lookup_cache_lock);
    return *uid != NULL;
}

bool vfs_virtual_to_uid_prefixed(const wchar_t *path, const wchar_t *game_root, wchar_t **uid) {
    size_t root_length;
    if (uid != NULL) *uid = NULL;
    if (path == NULL || game_root == NULL || uid == NULL) return false;
    root_length = wcslen(game_root);
    if (CompareStringOrdinal(path, (int)root_length, game_root, (int)root_length, TRUE) != CSTR_EQUAL ||
        (path[root_length] != L'\0' && path[root_length] != L'\\' && path[root_length] != L'/')) return false;
    return vfs_virtual_to_uid(path + root_length, uid);
}

const wchar_t *vfs_uid_to_path(const wchar_t *uid) {
    static const wchar_t prefix[] = L"\\\\YAERModLoader?";
    wchar_t *end;
    unsigned long long uid_generation;
    unsigned long long index_value;
    if (uid == NULL || wcsncmp(uid, prefix, (sizeof(prefix) / sizeof(prefix[0])) - 1) != 0) return NULL;
    AcquireSRWLockShared(&lookup_cache_lock);
    uid += (sizeof(prefix) / sizeof(prefix[0])) - 1;
    if (!iswdigit(*uid)) {
        ReleaseSRWLockShared(&lookup_cache_lock);
        return NULL;
    }
    uid_generation = wcstoull(uid, &end, 10);
    if (end == uid || *end++ != L'?' || uid_generation != vfs_generation()) {
        ReleaseSRWLockShared(&lookup_cache_lock);
        return NULL;
    }
    uid = end;
    if (!iswxdigit(*uid)) {
        ReleaseSRWLockShared(&lookup_cache_lock);
        return NULL;
    }
    index_value = wcstoull(uid, &end, 16);
    if (end == uid || *end != L'\0' || index_value >= entry_count) {
        ReleaseSRWLockShared(&lookup_cache_lock);
        return NULL;
    }
    const wchar_t *result = entries[index_value].path;
    ReleaseSRWLockShared(&lookup_cache_lock);
    return result;
}

const wchar_t *vfs_lookup_prefixed(const wchar_t *path, const wchar_t *game_root) {
    return vfs_lookup_prefixed_domain(path, game_root, VFS_LOOKUP_VIRTUAL);
}

const wchar_t *vfs_lookup_prefixed_domain(const wchar_t *path, const wchar_t *game_root,
                                          vfs_lookup_domain_t domain) {
    size_t root_length;
    if (path == NULL || game_root == NULL) return NULL;
    root_length = wcslen(game_root);
    if (CompareStringOrdinal(path, (int)root_length, game_root, (int)root_length, TRUE) != CSTR_EQUAL ||
        (path[root_length] != L'\0' && path[root_length] != L'\\' && path[root_length] != L'/')) return NULL;
    return vfs_lookup_domain(path + root_length, domain);
}

size_t vfs_entry_count(void) {
    return index != NULL ? kh_size(index) : 0;
}

void vfs_recursion_guard_enter(void) {
    vfs_recursion_depth++;
}

void vfs_recursion_guard_leave(void) {
    if (vfs_recursion_depth != 0) vfs_recursion_depth--;
}

bool vfs_recursion_guard_active(void) {
    return vfs_recursion_depth != 0;
}

static bool vfs_is_package_path(const wchar_t *path) {
    for (size_t i = 0; i < entry_count; i++) {
        if (CompareStringOrdinal(path, -1, entries[i].path, -1, TRUE) == CSTR_EQUAL) return true;
    }
    return false;
}

const wchar_t *vfs_route_writable_path(const wchar_t *path) {
    wchar_t *key;
    const wchar_t *result = NULL;
    if (path == NULL || vfs_recursion_depth != 0 || !vfs_normalize_path(path, &key)) return NULL;
    AcquireSRWLockShared(&writable_lock);
    for (size_t i = 0; i < writable_count; i++) {
        if (wcscmp(key, writable_entries[i].key) == 0) {
            result = writable_entries[i].path;
            break;
        }
    }
    ReleaseSRWLockShared(&writable_lock);
    LocalFree(key);
    return result;
}

const wchar_t *vfs_route_read_path(const wchar_t *path, DWORD desired_access, DWORD creation_disposition) {
    if (path == NULL || vfs_recursion_depth != 0 || vfs_is_package_path(path)) return NULL;
    const wchar_t *writable = vfs_route_writable_path(path);
    if (writable != NULL) return writable;
    if ((desired_access & (GENERIC_WRITE | DELETE)) != 0 ||
        creation_disposition == CREATE_NEW || creation_disposition == CREATE_ALWAYS ||
        creation_disposition == TRUNCATE_EXISTING) return NULL;
    return vfs_lookup_domain(path, VFS_LOOKUP_DISK_WIDE);
}

const wchar_t *vfs_route_read_path_a(const char *path, DWORD desired_access, DWORD creation_disposition) {
    int length;
    wchar_t *wide;
    const wchar_t *result;
    if (path == NULL) return NULL;
    length = MultiByteToWideChar(CP_ACP, 0, path, -1, NULL, 0);
    if (length <= 0) return NULL;
    wide = LocalAlloc(0, (size_t)length * sizeof(*wide));
    if (wide == NULL) return NULL;
    if (MultiByteToWideChar(CP_ACP, 0, path, -1, wide, length) == 0) {
        LocalFree(wide);
        return NULL;
    }
    if (vfs_recursion_depth != 0 || vfs_is_package_path(wide)) {
        LocalFree(wide);
        return NULL;
    }
    result = vfs_route_writable_path(wide);
    if (result == NULL && (desired_access & (GENERIC_WRITE | DELETE)) == 0 &&
        creation_disposition != CREATE_NEW && creation_disposition != CREATE_ALWAYS &&
        creation_disposition != TRUNCATE_EXISTING) {
        result = vfs_lookup_domain(wide, VFS_LOOKUP_DISK_ANSI);
    }
    LocalFree(wide);
    return result;
}
