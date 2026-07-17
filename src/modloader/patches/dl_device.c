/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "dl_device.h"

#include "common/allocator.h"

#include "modloader/dl_allocator.h"
#include "process/pe.h"
#include "xxhash.h"

#include <shlwapi.h>

#include <string.h>
#include <wchar.h>

#include <miniz.h>
#include <miniz_tdef.h>
#include <miniz_tinfl.h>

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
    current = yaer_mem_strdup_w(path);
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
            next = yaer_mem_alloc(0, (to_len + remainder_len + 1) * sizeof(*next));
            if (next == NULL) { yaer_mem_free(current); return false; }
            memcpy(next, to, to_len * sizeof(*next));
            memcpy(next + to_len, current + from_len + 2, (remainder_len + 1) * sizeof(*next));
            yaer_mem_free(current);
            current = next;
            replaced = true;
            break;
        }
        if (!replaced) { *expanded = current; return true; }
    }
    yaer_mem_free(current);
    return false;
}

bool ml_dl_string_clone_replace(const ml_msvc2015_string_t *source, const wchar_t *path,
                                ml_msvc2015_string_t *replacement) {
    size_t length;
    wchar_t *buffer;
    dl_allocator_t *allocator;
    if (source == NULL || path == NULL || replacement == NULL || source->encoding != 1) return false;
    allocator = source->allocator;
    if (allocator == NULL || allocator->vtable == NULL || allocator->vtable->allocate_aligned == NULL) return false;
    length = wcslen(path);
    memset(replacement, 0, sizeof(*replacement));
    replacement->allocator = allocator;
    replacement->capacity = 7;
    replacement->encoding = 1;
    if (length <= replacement->capacity) {
        buffer = (wchar_t *)replacement->storage.inline_storage;
    } else {
        if (length == SIZE_MAX) return false;
        buffer = allocator->vtable->allocate_aligned(allocator, (length + 1) * sizeof(*buffer), _Alignof(wchar_t));
        if (buffer == NULL) return false;
        replacement->storage.large = buffer;
        replacement->capacity = length;
    }
    memcpy(buffer, path, (length + 1) * sizeof(*buffer));
    replacement->length = length;
    return true;
}

bool ml_dl_mount_snapshot(ml_dl_device_manager_t *manager, ml_dl_mount_snapshot_t *snapshot) {
    size_t count;
    if (manager == NULL || snapshot == NULL) return false;
    memset(snapshot, 0, sizeof(*snapshot));
    count = ml_dl_vector_count(&manager->bnd4_mounts, sizeof(ml_dl_virtual_mount_t));
    if (count == 0) return true;
    snapshot->roots = yaer_mem_alloc(0, count * sizeof(*snapshot->roots));
    if (snapshot->roots == NULL) return false;
    for (size_t i = 0; i < count; i++) {
        ml_dl_virtual_mount_t *mount = &((ml_dl_virtual_mount_t *)manager->bnd4_mounts.first)[i];
        const wchar_t *root = ml_dl_string_data(&mount->root);
        snapshot->roots[i] = root == NULL ? NULL : yaer_mem_strdup_w(root);
        if (root != NULL && snapshot->roots[i] == NULL) {
            ml_dl_mount_snapshot_destroy(snapshot);
            return false;
        }
        snapshot->count = i + 1;
    }
    return true;
}

void ml_dl_mount_snapshot_destroy(ml_dl_mount_snapshot_t *snapshot) {
    if (snapshot == NULL) return;
    for (size_t i = 0; i < snapshot->count; i++) yaer_mem_free(snapshot->roots[i]);
    yaer_mem_free(snapshot->roots);
    memset(snapshot, 0, sizeof(*snapshot));
}

bool ml_dl_mounts_init(ml_dl_vfs_mounts_t *mounts) {
    if (mounts == NULL) return false;
    memset(mounts, 0, sizeof(*mounts));
    return true;
}

static bool snapshot_contains(const ml_dl_mount_snapshot_t *snapshot, const wchar_t *root) {
    if (snapshot == NULL || root == NULL) return false;
    for (size_t i = 0; i < snapshot->count; i++) {
        if (snapshot->roots[i] != NULL && wcscmp(snapshot->roots[i], root) == 0) return true;
    }
    return false;
}

static bool mounts_reserve(ml_dl_vfs_mounts_t *mounts, size_t capacity) {
    ml_dl_virtual_mount_t *items;
    if (mounts == NULL || capacity > SIZE_MAX / sizeof(*items)) return false;
    if (capacity <= mounts->capacity) return true;
    items = yaer_mem_alloc(0, capacity * sizeof(*items));
    if (items == NULL) return false;
    memcpy(items, mounts->items, mounts->count * sizeof(*items));
    yaer_mem_free(mounts->items);
    mounts->items = items;
    mounts->capacity = capacity;
    return true;
}

static bool vector_reserve(ml_msvc2015_vector_t *vector, size_t count, size_t item_size) {
    size_t capacity;
    size_t used;
    dl_allocator_t *allocator;
    void *items;
    if (vector == NULL || item_size == 0 || count > SIZE_MAX / item_size) return false;
    capacity = vector->first == NULL || vector->end == NULL ? 0 :
               (size_t)((uint8_t *)vector->end - (uint8_t *)vector->first) / item_size;
    used = ml_dl_vector_count(vector, item_size);
    if (count <= capacity) return true;
    allocator = (dl_allocator_t *)vector->allocator;
    if (allocator == NULL || allocator->vtable == NULL || allocator->vtable->allocate_aligned == NULL) return false;
    items = allocator->vtable->allocate_aligned(allocator, count * item_size, sizeof(void *));
    if (items == NULL) return false;
    if (used != 0 && vector->first != NULL) memcpy(items, vector->first, used * item_size);
    if (vector->first != NULL && allocator->vtable->free != NULL) allocator->vtable->free(allocator, vector->first);
    vector->first = items;
    vector->last = (uint8_t *)items + used * item_size;
    vector->end = (uint8_t *)items + count * item_size;
    return true;
}

bool ml_dl_device_extract_new(ml_dl_device_manager_t *manager, const ml_dl_mount_snapshot_t *snapshot,
                              ml_dl_vfs_mounts_t *mounts) {
    size_t mount_count;
    size_t new_count = 0;
    if (manager == NULL || snapshot == NULL || mounts == NULL) return false;
    mount_count = ml_dl_vector_count(&manager->bnd4_mounts, sizeof(ml_dl_virtual_mount_t));
    for (size_t i = 0; i < mount_count; i++) {
        ml_dl_virtual_mount_t *items = (ml_dl_virtual_mount_t *)manager->bnd4_mounts.first;
        const wchar_t *root = ml_dl_string_data(&items[i].root);
        if (root != NULL && !snapshot_contains(snapshot, root)) new_count++;
    }
    /* MountEbl has already grown the game-owned vectors.  Detaching mounts only
       shortens last; avoid reallocating those ABI-owned vectors here. */
    if (new_count > SIZE_MAX - mounts->count ||
        !mounts_reserve(mounts, mounts->count + new_count)) return false;
    for (size_t i = mount_count; i != 0; i--) {
        ml_dl_virtual_mount_t *items = (ml_dl_virtual_mount_t *)manager->bnd4_mounts.first;
        ml_dl_virtual_mount_t mount = items[i - 1];
        const wchar_t *root = ml_dl_string_data(&mount.root);
        if (root == NULL || snapshot_contains(snapshot, root)) continue;
        memmove(mounts->items + 1, mounts->items, mounts->count * sizeof(*mounts->items));
        mounts->items[0] = mount;
        mounts->count++;
        memmove(items + i - 1, items + i, (mount_count - i) * sizeof(*items));
        mount_count--;
    }
    {
        size_t device_count = ml_dl_vector_count(&manager->devices, sizeof(ml_dl_device_t *));
        ml_dl_device_t **devices = (ml_dl_device_t **)manager->devices.first;
        for (size_t i = device_count; i != 0; i--) {
            bool used = false;
            for (size_t j = 0; j < mounts->count; j++) if (mounts->items[j].device == devices[i - 1]) used = true;
            if (used) memmove(devices + i - 1, devices + i, (device_count - i) * sizeof(*devices)), device_count--;
        }
        manager->devices.last = devices + device_count;
    }
    manager->bnd4_mounts.last = (uint8_t *)manager->bnd4_mounts.first + mount_count * sizeof(ml_dl_virtual_mount_t);
    return true;
}

bool ml_dl_device_restore_mounts(ml_dl_device_manager_t *manager, ml_dl_vfs_mounts_t *mounts) {
    size_t device_count;
    size_t mount_count;
    size_t required_devices;
    size_t required_mounts;
    if (manager == NULL || mounts == NULL) return false;
    device_count = ml_dl_vector_count(&manager->devices, sizeof(ml_dl_device_t *));
    mount_count = ml_dl_vector_count(&manager->bnd4_mounts, sizeof(ml_dl_virtual_mount_t));
    if (mounts->count == 0) return true;
    if (mounts->count > SIZE_MAX - device_count || mounts->count > SIZE_MAX - mount_count) return false;
    required_devices = device_count + mounts->count;
    required_mounts = mount_count + mounts->count;
    if (!vector_reserve(&manager->devices, required_devices, sizeof(ml_dl_device_t *)) ||
        !vector_reserve(&manager->bnd4_mounts, required_mounts, sizeof(ml_dl_virtual_mount_t))) return false;
    for (size_t i = 0; i < mounts->count; i++) {
        ((ml_dl_device_t **)manager->devices.first)[device_count + i] = mounts->items[i].device;
        ((ml_dl_virtual_mount_t *)manager->bnd4_mounts.first)[mount_count + i] = mounts->items[i];
    }
    manager->devices.last = (uint8_t *)manager->devices.first + required_devices * sizeof(ml_dl_device_t *);
    manager->bnd4_mounts.last = (uint8_t *)manager->bnd4_mounts.first +
                               required_mounts * sizeof(ml_dl_virtual_mount_t);
    yaer_mem_free(mounts->items);
    memset(mounts, 0, sizeof(*mounts));
    return true;
}

void ml_dl_mounts_destroy(ml_dl_vfs_mounts_t *mounts) {
    if (mounts == NULL) return;
    for (size_t i = 0; i < mounts->count; i++) ml_dl_string_destroy(&mounts->items[i].root);
    yaer_mem_free(mounts->items);
    memset(mounts, 0, sizeof(*mounts));
}

void ml_dl_mounts_release(ml_dl_vfs_mounts_t *mounts) {
    if (mounts == NULL) return;
    yaer_mem_free(mounts->items);
    memset(mounts, 0, sizeof(*mounts));
}

bool ml_dl_device_push_mounts_permanent(ml_dl_device_manager_t *manager, ml_dl_vfs_mounts_t *mounts) {
    size_t device_count;
    size_t mount_count;
    size_t required_devices;
    size_t required_mounts;
    if (manager == NULL || mounts == NULL) return false;
    device_count = ml_dl_vector_count(&manager->devices, sizeof(ml_dl_device_t *));
    mount_count = ml_dl_vector_count(&manager->bnd4_mounts, sizeof(ml_dl_virtual_mount_t));
    if (mounts->count == 0) return true;
    if (mounts->count > SIZE_MAX - device_count || mounts->count > SIZE_MAX - mount_count) return false;
    required_devices = device_count + mounts->count;
    required_mounts = mount_count + mounts->count;
    if (!vector_reserve(&manager->devices, required_devices, sizeof(ml_dl_device_t *)) ||
        !vector_reserve(&manager->bnd4_mounts, required_mounts, sizeof(ml_dl_virtual_mount_t))) return false;
    for (size_t i = 0; i < mounts->count; i++) {
        ((ml_dl_device_t **)manager->devices.first)[device_count + i] = mounts->items[i].device;
        ((ml_dl_virtual_mount_t *)manager->bnd4_mounts.first)[mount_count + i] = mounts->items[i];
    }
    manager->devices.last = (uint8_t *)manager->devices.first + required_devices * sizeof(ml_dl_device_t *);
    manager->bnd4_mounts.last = (uint8_t *)manager->bnd4_mounts.first +
                               required_mounts * sizeof(ml_dl_virtual_mount_t);
    yaer_mem_free(mounts->items);
    memset(mounts, 0, sizeof(*mounts));
    return true;
}

void ml_dl_string_destroy(ml_msvc2015_string_t *string) {
    if (string == NULL) return;
    if (string->capacity > 7 && string->storage.large != NULL) {
        dl_allocator_dealloc(string->allocator, string->storage.large);
    }
    memset(string, 0, sizeof(*string));
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
        void **next = seen_targets == NULL ? yaer_mem_alloc(0, capacity * sizeof(*next)) : yaer_mem_realloc(seen_targets, capacity * sizeof(*next), LMEM_MOVEABLE);
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

bool ml_boot_boost_cache_key(const void *data, size_t size, uint64_t key[2]) {
    const uint8_t *bytes = data;
    XXH128_hash_t hash;
    if (bytes == NULL || key == NULL) return false;
    hash = XXH3_128bits_withSeed(bytes, size, 1);
    key[0] = hash.low64;
    key[1] = hash.high64;
    return true;
}

wchar_t *ml_boot_boost_cache_path(const wchar_t *directory, const uint64_t key[2]) {
    int suffix_length;
    size_t directory_length;
    bool separator;
    wchar_t *result;
    if (directory == NULL || key == NULL) return NULL;
    directory_length = wcslen(directory);
    separator = directory_length != 0 && directory[directory_length - 1] != L'\\' &&
                directory[directory_length - 1] != L'/';
    suffix_length = _scwprintf(L"%016llx%016llx.bhd.zz", (unsigned long long)key[1], (unsigned long long)key[0]);
    if (suffix_length < 0 || directory_length > SIZE_MAX - (size_t)suffix_length - (separator ? 2 : 1)) return NULL;
    result = yaer_mem_alloc(0, (directory_length + (size_t)suffix_length + (separator ? 2 : 1)) * sizeof(*result));
    if (result == NULL) return NULL;
    memcpy(result, directory, directory_length * sizeof(*result));
    if (separator) result[directory_length++] = L'\\';
    _snwprintf(result + directory_length, (size_t)suffix_length + 1, L"%016llx%016llx.bhd.zz",
               (unsigned long long)key[1], (unsigned long long)key[0]);
    return result;
}

bool ml_boot_boost_cache_load(const wchar_t *path, void *output, size_t output_size) {
    HANDLE file = INVALID_HANDLE_VALUE;
    DWORD read;
    uint32_t expected_size;
    LARGE_INTEGER file_size;
    uint8_t *compressed = NULL;
    size_t compressed_size;
    bool valid = false;
    if (path == NULL || output == NULL || output_size > UINT32_MAX) return false;
    file = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) return false;
    if (!GetFileSizeEx(file, &file_size) || file_size.QuadPart < 4 || file_size.QuadPart > SIZE_MAX) goto done;
    if (!ReadFile(file, &expected_size, sizeof(expected_size), &read, NULL) || read != sizeof(expected_size) || expected_size != output_size) goto done;
    compressed_size = (size_t)file_size.QuadPart - sizeof(expected_size);
    compressed = yaer_mem_alloc(0, compressed_size);
    if (compressed == NULL) goto done;
    if (ReadFile(file, compressed, (DWORD)compressed_size, &read, NULL) && read == compressed_size) {
        tinfl_decompressor decompressor;
        size_t input_size = compressed_size;
        size_t uncompressed_size = output_size;
        tinfl_init(&decompressor);
        valid = tinfl_decompress(&decompressor, compressed, &input_size, output, output, &uncompressed_size,
                                 TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF) == TINFL_STATUS_DONE &&
                input_size == compressed_size && uncompressed_size == output_size &&
                ml_bhd5_header_valid(output, output_size);
    }
    yaer_mem_free(compressed);
done:
    CloseHandle(file);
    if (!valid) DeleteFileW(path);
    return valid;
}

bool ml_boot_boost_cache_store(const wchar_t *path, const void *data, size_t size) {
    wchar_t *temporary;
    HANDLE file = INVALID_HANDLE_VALUE;
    size_t bound;
    size_t compressed_size;
    uint8_t *compressed;
    uint32_t stored_size;
    DWORD written;
    bool result = false;
    if (path == NULL || data == NULL || size > UINT32_MAX || !ml_bhd5_header_valid(data, size)) return false;
    temporary = yaer_mem_alloc(0, (wcslen(path) + 5) * sizeof(*temporary));
    if (temporary == NULL) return false;
    lstrcpyW(temporary, path);
    lstrcatW(temporary, L".tmp");
    bound = mz_compressBound(size);
    compressed = yaer_mem_alloc(0, bound);
    if (compressed == NULL) { yaer_mem_free(temporary); return false; }
    {
        compressed_size = tdefl_compress_mem_to_mem(compressed, bound, data, size,
            tdefl_create_comp_flags_from_zip_params(7, -MZ_DEFAULT_WINDOW_BITS, MZ_DEFAULT_STRATEGY));
        if (compressed_size == 0) goto done;
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
        result = MoveFileExW(temporary, path, MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) != 0;
    }
done:
    if (file != INVALID_HANDLE_VALUE) CloseHandle(file);
    if (!result) DeleteFileW(temporary);
    yaer_mem_free(compressed);
    yaer_mem_free(temporary);
    return result;
}
