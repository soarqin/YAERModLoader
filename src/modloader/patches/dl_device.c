/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "dl_device.h"

#include "process/pe.h"

#include <shlwapi.h>

#include <string.h>
#include <wchar.h>

#include <miniz.h>

static void **seen_targets;
static size_t seen_count;
static size_t seen_capacity;
static SRWLOCK seen_lock = SRWLOCK_INIT;

static bool pointer_in_section(void *image_base, const IMAGE_SECTION_HEADER *section, const void *pointer) {
    return pointer != NULL && pe_section_contains_va(image_base, section, pointer);
}

static bool vector_valid(const ml_msvc2015_vector_t *vector, void *allocator) {
    uintptr_t first;
    uintptr_t last;
    uintptr_t end;
    if (vector == NULL || vector->allocator != allocator) return false;
    first = (uintptr_t)vector->first;
    last = (uintptr_t)vector->last;
    end = (uintptr_t)vector->end;
    return (first | last | end) % sizeof(void *) == 0 && first <= last && last <= end;
}

static bool manager_valid(void *image_base, const IMAGE_SECTION_HEADER *data,
                          const IMAGE_SECTION_HEADER *rdata, const ml_dl_device_manager_t *manager) {
    void *allocator;
    if (manager == NULL || !pointer_in_section(image_base, data, manager)) return false;
    allocator = manager->devices.allocator;
    /* patch_mem may replace Dantelion's original .data allocator with mimalloc. */
    if (allocator == NULL || ((uintptr_t)allocator & (sizeof(void *) - 1)) != 0) return false;
    if (!vector_valid(&manager->spis, allocator) || !vector_valid(&manager->virtual_roots, allocator) ||
        !vector_valid(&manager->bnd3_mounts, allocator) || !vector_valid(&manager->bnd4_mounts, allocator)) return false;
    if (manager->disk_device == NULL || manager->disk_device->vtable == NULL ||
        !pointer_in_section(image_base, rdata, manager->disk_device->vtable)) return false;
    return manager->bnd3_spi != NULL && manager->bnd4_spi != NULL &&
           pointer_in_section(image_base, rdata, manager->mutex_vtable);
}

ml_dl_device_manager_t *ml_dl_device_manager_find(void *image_base) {
    const IMAGE_SECTION_HEADER *data;
    const IMAGE_SECTION_HEADER *rdata;
    uintptr_t *pointers;
    size_t size;
    if (image_base == NULL) return NULL;
    data = pe_section_by_name(image_base, ".data");
    rdata = pe_section_by_name(image_base, ".rdata");
    pointers = data == NULL ? NULL : pe_section_data(image_base, data, &size);
    if (pointers == NULL || rdata == NULL) return NULL;
    for (size_t i = 0; i < size / sizeof(*pointers); i++) {
        ml_dl_device_manager_t *manager = (ml_dl_device_manager_t *)pointers[i];
        if (manager_valid(image_base, data, rdata, manager)) return manager;
    }
    return NULL;
}

bool ml_dl_device_manager_lock(ml_dl_device_manager_t *manager, ml_dl_device_manager_guard_t *guard) {
    if (manager == NULL || guard == NULL) return false;
    EnterCriticalSection(&manager->critical_section);
    guard->manager = manager;
    return true;
}

void ml_dl_device_manager_unlock(ml_dl_device_manager_guard_t *guard) {
    if (guard != NULL && guard->manager != NULL) {
        LeaveCriticalSection(&guard->manager->critical_section);
        guard->manager = NULL;
    }
}

const wchar_t *ml_dl_string_data(const ml_msvc2015_string_t *value) {
    if (value == NULL || value->encoding != 1 || value->length > value->capacity) return NULL;
    return value->capacity * sizeof(wchar_t) >= sizeof(value->storage.inline_storage)
        ? (const wchar_t *)value->storage.large : (const wchar_t *)value->storage.inline_storage;
}

size_t ml_dl_vector_count(const ml_msvc2015_vector_t *vector, size_t item_size) {
    uintptr_t first;
    uintptr_t last;
    if (vector == NULL || item_size == 0) return 0;
    first = (uintptr_t)vector->first;
    last = (uintptr_t)vector->last;
    return last >= first && (last - first) % item_size == 0 ? (last - first) / item_size : 0;
}

bool ml_dl_device_expand_path(ml_dl_device_manager_t *manager, const wchar_t *path, wchar_t **expanded) {
    wchar_t *current;
    if (manager == NULL || path == NULL || expanded == NULL) return false;
    *expanded = NULL;
    current = StrDupW(path);
    if (current == NULL) return false;
    for (size_t depth = 0; depth != 16; depth++) {
        size_t count = ml_dl_vector_count(&manager->virtual_roots, sizeof(ml_dl_virtual_root_t));
        bool replaced = false;
        const wchar_t *separator = wcsstr(current, L":/");
        size_t root_len;
        if (separator == NULL) { *expanded = current; return true; }
        root_len = (size_t)(separator - current);
        for (size_t i = 0; i < count; i++) {
            ml_dl_virtual_root_t *root = &((ml_dl_virtual_root_t *)manager->virtual_roots.first)[i];
            const wchar_t *from = ml_dl_string_data(&root->root);
            const wchar_t *to = ml_dl_string_data(&root->expanded);
            size_t from_len = root->root.length;
            size_t to_len = root->expanded.length;
            size_t remainder_len;
            wchar_t *next;
            if (from == NULL || to == NULL || from_len == 0 || from_len != root_len ||
                memcmp(current, from, from_len * sizeof(*current)) != 0) continue;
            remainder_len = wcslen(current + from_len + 2);
            next = LocalAlloc(0, (to_len + remainder_len + 1) * sizeof(*next));
            if (next == NULL) { LocalFree(current); return false; }
            memcpy(next, to, to_len * sizeof(*next));
            memcpy(next + to_len, current + from_len + 2, (remainder_len + 1) * sizeof(*next));
            LocalFree(current);
            current = next;
            replaced = true;
            break;
        }
        if (!replaced) { *expanded = current; return true; }
    }
    LocalFree(current);
    return false;
}

bool ml_dl_string_replace_path(ml_msvc2015_string_t *dl_string, const wchar_t *path) {
    size_t length;
    wchar_t *buffer;
    if (dl_string == NULL || path == NULL || dl_string->encoding != 1) return false;
    length = wcslen(path);
    if (length > dl_string->capacity) return false;
    buffer = dl_string->capacity * sizeof(wchar_t) >= sizeof(dl_string->storage.inline_storage)
        ? (wchar_t *)dl_string->storage.large : (wchar_t *)dl_string->storage.inline_storage;
    if (buffer == NULL) return false;
    memcpy(buffer, path, (length + 1) * sizeof(*buffer));
    dl_string->length = length;
    return true;
}

bool ml_dl_device_seen(void *target) {
    bool found = false;
    AcquireSRWLockShared(&seen_lock);
    for (size_t i = 0; i < seen_count; i++) if (seen_targets[i] == target) { found = true; break; }
    ReleaseSRWLockShared(&seen_lock);
    return found;
}

bool ml_dl_device_mark_seen(void *target) {
    if (target == NULL) return false;
    AcquireSRWLockExclusive(&seen_lock);
    for (size_t i = 0; i < seen_count; i++) if (seen_targets[i] == target) { ReleaseSRWLockExclusive(&seen_lock); return false; }
    if (seen_count == seen_capacity) {
        size_t capacity = seen_capacity == 0 ? 16 : seen_capacity * 2;
        void **next = seen_targets == NULL ? LocalAlloc(0, capacity * sizeof(*next)) : LocalReAlloc(seen_targets, capacity * sizeof(*next), LMEM_MOVEABLE);
        if (next == NULL) { ReleaseSRWLockExclusive(&seen_lock); return false; }
        seen_targets = next;
        seen_capacity = capacity;
    }
    seen_targets[seen_count++] = target;
    ReleaseSRWLockExclusive(&seen_lock);
    return true;
}

bool ml_bhd5_header_valid(const void *data, size_t size) {
    const uint8_t *bytes = data;
    uint32_t file_size;
    uint32_t bucket_count;
    uint32_t bucket_offset;
    if (bytes == NULL || size < 24 || memcmp(bytes, "BHD5", 4) != 0) return false;
    memcpy(&file_size, bytes + 12, sizeof(file_size));
    memcpy(&bucket_count, bytes + 16, sizeof(bucket_count));
    memcpy(&bucket_offset, bytes + 20, sizeof(bucket_offset));
    return file_size >= 24 && file_size <= size && bucket_offset <= file_size &&
           bucket_count <= (file_size - bucket_offset) / sizeof(uint32_t);
}

bool ml_boot_boost_cache_key(const void *data, size_t size, uint64_t *key) {
    const uint8_t *bytes = data;
    uint64_t hash = UINT64_C(1469598103934665603);
    if (bytes == NULL || key == NULL) return false;
    for (size_t i = 0; i < size; i++) {
        hash ^= bytes[i];
        hash *= UINT64_C(1099511628211);
    }
    *key = hash;
    return true;
}

wchar_t *ml_boot_boost_cache_path(const wchar_t *directory, uint64_t key) {
    int suffix_length;
    size_t directory_length;
    bool separator;
    wchar_t *result;
    if (directory == NULL) return NULL;
    directory_length = wcslen(directory);
    separator = directory_length != 0 && directory[directory_length - 1] != L'\\' &&
                directory[directory_length - 1] != L'/';
    suffix_length = _scwprintf(L"%016llx.bhd.zz", (unsigned long long)key);
    if (suffix_length < 0 || directory_length > SIZE_MAX - (size_t)suffix_length - (separator ? 2 : 1)) return NULL;
    result = LocalAlloc(0, (directory_length + (size_t)suffix_length + (separator ? 2 : 1)) * sizeof(*result));
    if (result == NULL) return NULL;
    memcpy(result, directory, directory_length * sizeof(*result));
    if (separator) result[directory_length++] = L'\\';
    _snwprintf(result + directory_length, (size_t)suffix_length + 1, L"%016llx.bhd.zz",
               (unsigned long long)key);
    return result;
}

bool ml_boot_boost_cache_load(const wchar_t *path, void *output, size_t output_size) {
    HANDLE file = INVALID_HANDLE_VALUE;
    DWORD read;
    uint32_t expected_size;
    LARGE_INTEGER file_size;
    uint8_t *compressed;
    size_t compressed_size;
    bool valid = false;
    if (path == NULL || output == NULL || output_size > UINT32_MAX) return false;
    file = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) return false;
    if (!GetFileSizeEx(file, &file_size) || file_size.QuadPart < 4 || file_size.QuadPart > SIZE_MAX) goto done;
    if (!ReadFile(file, &expected_size, sizeof(expected_size), &read, NULL) || read != sizeof(expected_size) || expected_size != output_size) goto done;
    compressed_size = (size_t)file_size.QuadPart - sizeof(expected_size);
    compressed = LocalAlloc(0, compressed_size);
    if (compressed == NULL) goto done;
    if (ReadFile(file, compressed, (DWORD)compressed_size, &read, NULL) && read == compressed_size) {
        mz_ulong uncompressed_size = output_size;
        valid = mz_uncompress(output, &uncompressed_size, compressed, compressed_size) == MZ_OK &&
                uncompressed_size == output_size && ml_bhd5_header_valid(output, output_size);
    }
    LocalFree(compressed);
done:
    CloseHandle(file);
    if (!valid) DeleteFileW(path);
    return valid;
}

bool ml_boot_boost_cache_store(const wchar_t *path, const void *data, size_t size) {
    wchar_t *temporary;
    HANDLE file;
    size_t bound;
    size_t compressed_size;
    uint8_t *compressed;
    uint32_t stored_size;
    DWORD written;
    bool result = false;
    if (path == NULL || data == NULL || size > UINT32_MAX || !ml_bhd5_header_valid(data, size)) return false;
    temporary = LocalAlloc(0, (wcslen(path) + 5) * sizeof(*temporary));
    if (temporary == NULL) return false;
    lstrcpyW(temporary, path);
    lstrcatW(temporary, L".tmp");
    bound = mz_compressBound(size);
    compressed = LocalAlloc(0, bound);
    if (compressed == NULL) { LocalFree(temporary); return false; }
    {
        mz_ulong compressed_length = bound;
        if (mz_compress2(compressed, &compressed_length, data, size, MZ_BEST_COMPRESSION) != MZ_OK) goto done;
        compressed_size = compressed_length;
    }
    if (compressed_size == 0 || compressed_size > MAXDWORD) goto done;
    file = CreateFileW(temporary, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) goto done;
    stored_size = (uint32_t)size;
    if (WriteFile(file, &stored_size, sizeof(stored_size), &written, NULL) && written == sizeof(stored_size) &&
        WriteFile(file, compressed, (DWORD)compressed_size, &written, NULL) && written == (DWORD)compressed_size) {
        FlushFileBuffers(file);
        CloseHandle(file);
        file = INVALID_HANDLE_VALUE;
        if (!MoveFileExW(temporary, path, MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
            DeleteFileW(path);
            result = MoveFileExW(temporary, path, MOVEFILE_WRITE_THROUGH) != 0;
        } else {
            result = true;
        }
    }
done:
    if (file != INVALID_HANDLE_VALUE) CloseHandle(file);
    if (!result) DeleteFileW(temporary);
    LocalFree(compressed);
    LocalFree(temporary);
    return result;
}
