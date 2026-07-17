/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "asset_hooks.h"

#include <string.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static bool rsa_public_key_block_size(const char *pem, size_t pem_length, size_t *block_size);

#ifndef ML_ASSET_HOOKS_TEST
#include "dl_device.h"

#include "modloader/config.h"
#include "modloader/dl_allocator.h"
#include "modloader/hook.h"
#include "modloader/hook_batch.h"
#include "modloader/mod.h"
#include "modloader/vfs.h"
#include "game/game.h"
#include "process/fd4_step.h"
#include "process/pe.h"
#include "process/rtti.h"
#include "process/scanner.h"
#include "process/singleton.h"

#include <MinHook.h>

#include <stdio.h>
#include <shlwapi.h>
#endif

#ifndef ML_ASSET_HOOKS_TEST
typedef void *(__cdecl *dl_open_file_t)(ml_dl_device_t *, ml_msvc2015_string_t *, const wchar_t *, void *, void *, bool);
typedef bool (__cdecl *dl_set_path_t)(ml_dl_file_operator_t *, ml_msvc2015_string_t *, bool, bool);
typedef void *(__cdecl *make_ebl_object_t)(void *, const wchar_t *, void *);
typedef bool (__cdecl *mount_ebl_t)(const wchar_t *, const wchar_t *, const wchar_t *, void *, const char *, size_t);

static void *game_image_base;
static size_t game_image_size;
static ml_dl_device_manager_t *device_manager;
static fd4_step_fn_t old_file_step_init;
static make_ebl_object_t old_make_ebl_object;
static mount_ebl_t old_mount_ebl;
static bool pre_hooks_installed;
static bool post_hooks_installed;
static bool file_step_hook_installed;
static void *file_step_hook_target;
static void *mount_ebl_hook_target;
static void *make_ebl_object_hook_target;

typedef struct asset_hook_s {
    void *target;
    void *original;
    void **slot;
} asset_hook_t;

typedef struct ebl_open_hook_s {
    void *target;
    void *original;
} ebl_open_hook_t;

typedef struct bhd5_holder_s {
    uint8_t *header;
    uint32_t bucket_count;
    uint32_t *buckets;
} bhd5_holder_t;

static bool remove_asset_hook(void *target);
static bool remove_asset_hooks(asset_hook_t *hooks, size_t count);
static bool make_override_path(const ml_msvc2015_string_t *path, ml_msvc2015_string_t *replacement);
static void *__cdecl disk_open_file_hooked(ml_dl_device_t *device, ml_msvc2015_string_t *path,
                                           const wchar_t *path_cstr, void *container,
                                           void *allocator, bool temporary);
static void remove_ebl_device_opens_from(size_t count);
static asset_hook_t open_hooks[64];
static size_t open_hook_count;
static ebl_open_hook_t ebl_open_hooks[64];
static size_t ebl_open_hook_count;
static asset_hook_t set_path_hooks[64];
static size_t set_path_hook_count;
static ml_dl_device_t *disk_device;
static SRWLOCK set_path_hook_lock = SRWLOCK_INIT;
static bool set_path_hook_attempted;
static bool set_path_hook_result;
static LONG logged_disk_override;
static LONG logged_disk_open;
static LONG logged_disk_open_return;
static LONG logged_set_path_override;
static LONG logged_ebl_fallback;
static LONG logged_mount_ebl;

static bool pointer_in_text(const void *pointer) {
    const IMAGE_SECTION_HEADER *text = pe_section_by_name(game_image_base, ".text");
    return text != NULL && pe_section_contains_va(game_image_base, text, pointer);
}
#endif

typedef struct mount_pattern_match_s {
    size_t displacement_offset;
    size_t instruction_end_offset;
} mount_pattern_match_t;

static bool match_mount_ebl_pattern(const uint8_t *p, size_t remaining, mount_pattern_match_t *match) {
    bool stack_compare;
    if (p == NULL || match == NULL) return false;
    if (remaining >= 42 && p[0] == 0x48 && p[1] == 0x8B && p[2] == 0x45 &&
        memcmp(p + 4, "\x48\x89\x44\x24\x28", 5) == 0 &&
        (p[9] == 0x48 || p[9] == 0x4C || p[9] == 0x7C) && p[10] == 0x89 &&
        p[11] >= 0x44 && p[11] <= 0x7C && ((p[11] - 0x44) % 8) == 0 &&
        p[12] == 0x24 && p[13] == 0x20 && memcmp(p + 14, "\x4C\x8B\x0D", 3) == 0 &&
        (p[21] == 0x48 || p[21] == 0x49 || p[21] == 0x7C) && p[22] == 0x8B &&
        p[23] >= 0xD0 && p[23] <= 0xD7 &&
        (p[24] == 0x48 || p[24] == 0x49 || p[24] == 0x7C) && p[25] == 0x8B &&
        p[26] >= 0xC8 && p[26] <= 0xCF && p[27] == 0xE8 &&
        memcmp(p + 32, "\x0F\xB6\xD8", 3) == 0) {
        stack_compare = memcmp(p + 35, "\x48\x83\x7D", 3) == 0 && p[39] == 0x08 && p[40] == 0x72;
        if (!stack_compare && remaining >= 43) {
            stack_compare = memcmp(p + 35, "\x48\x83\x7C\x24", 4) == 0 && p[40] == 0x08 && p[41] == 0x72;
        }
        if (stack_compare) {
            match->displacement_offset = 28;
            match->instruction_end_offset = 32;
            return true;
        }
    }
    if (remaining >= 56 &&
        memcmp(p, "\x53\x48\x83\xEC\x30\x48\x8B\x44\x24\x70\x4D\x8B\xD1\x4C\x8B\x4C\x24\x60"
                  "\x4D\x8B\xD8\x48\x89\x44\x24\x28\x48\x8B\xCA\x48\x8B\x44\x24\x68\x4D\x8B\xC2"
                  "\x49\x8B\xD3\x48\x89\x44\x24\x20\xE8", 46) == 0 &&
        memcmp(p + 50, "\x48\x83\xC4\x30\x5B\xC3", 6) == 0) {
        match->displacement_offset = 46;
        match->instruction_end_offset = 50;
        return true;
    }
    return false;
}

bool ml_asset_hooks_test_match_mount_ebl(const uint8_t *bytes, size_t size,
                                         size_t *displacement_offset, size_t *instruction_end_offset) {
    mount_pattern_match_t match;
    if (!match_mount_ebl_pattern(bytes, size, &match)) return false;
    if (displacement_offset != NULL) *displacement_offset = match.displacement_offset;
    if (instruction_end_offset != NULL) *instruction_end_offset = match.instruction_end_offset;
    return true;
}

bool ml_asset_hooks_test_rsa_public_key_block_size(const char *pem, size_t pem_length, size_t *block_size) {
#ifdef ML_ASSET_HOOKS_TEST
    return rsa_public_key_block_size(pem, pem_length, block_size);
#else
    (void)pem;
    (void)pem_length;
    (void)block_size;
    return false;
#endif
}

#ifndef ML_ASSET_HOOKS_TEST
static void *find_mount_ebl(void) {
    const IMAGE_SECTION_HEADER *text = pe_section_by_name(game_image_base, ".text");
    size_t text_size = 0;
    uint8_t *bytes = text == NULL ? NULL : pe_section_data(game_image_base, text, &text_size);
    if (bytes == NULL) return NULL;
    for (size_t i = 0; i < text_size; i++) {
        uint8_t *p = bytes + i;
        mount_pattern_match_t match;
        if (match_mount_ebl_pattern(p, text_size - i, &match)) {
            int32_t displacement;
            memcpy(&displacement, p + match.displacement_offset, sizeof(displacement));
            void *target = p + match.instruction_end_offset + displacement;
            if (!pointer_in_text(target)) continue;
            fwprintf(stderr, L"NOTE: [asset-hooks] MountEbl signature matched at %p target=%p\n", p, target);
            return target;
        }
    }
    return NULL;
}
#endif

static int base64_value(char value) {
    if (value >= 'A' && value <= 'Z') return value - 'A';
    if (value >= 'a' && value <= 'z') return value - 'a' + 26;
    if (value >= '0' && value <= '9') return value - '0' + 52;
    if (value == '+') return 62;
    if (value == '/') return 63;
    return -1;
}

static bool der_read_length(const uint8_t **cursor, const uint8_t *end, size_t *length) {
    uint8_t first;
    if (cursor == NULL || *cursor == NULL || end == NULL || length == NULL || *cursor >= end) return false;
    first = *(*cursor)++;
    if ((first & 0x80) == 0) {
        *length = first;
        return true;
    }
    {
        size_t bytes = first & 0x7f;
        size_t value = 0;
        if (bytes == 0 || bytes > sizeof(size_t) || (size_t)(end - *cursor) < bytes) return false;
        for (size_t i = 0; i < bytes; i++) value = (value << 8) | *(*cursor)++;
        *length = value;
        return true;
    }
}

static bool rsa_public_key_block_size(const char *pem, size_t pem_length, size_t *block_size) {
    static const char begin[] = "-----BEGIN RSA PUBLIC KEY-----";
    static const char pem_end[] = "-----END RSA PUBLIC KEY-----";
    uint8_t *der;
    size_t begin_offset = SIZE_MAX;
    size_t end_offset = SIZE_MAX;
    size_t der_length = 0;
    uint32_t accumulator = 0;
    unsigned bits = 0;
    const uint8_t *cursor;
    const uint8_t *end;
    const uint8_t *sequence_end;
    size_t sequence_length;
    size_t modulus_length;
    if (pem == NULL || block_size == NULL || pem_length < sizeof(begin) + sizeof(pem_end)) return false;
    for (size_t i = 0; i + sizeof(begin) - 1 <= pem_length; i++) {
        if (memcmp(pem + i, begin, sizeof(begin) - 1) == 0) { begin_offset = i + sizeof(begin) - 1; break; }
    }
    if (begin_offset == SIZE_MAX) return false;
    for (size_t i = begin_offset; i + sizeof(pem_end) - 1 <= pem_length; i++) {
        if (memcmp(pem + i, pem_end, sizeof(pem_end) - 1) == 0) { end_offset = i; break; }
    }
    if (end_offset == SIZE_MAX) return false;
    der = LocalAlloc(0, end_offset - begin_offset);
    if (der == NULL) return false;
    for (size_t i = begin_offset; i < end_offset; i++) {
        int value = base64_value(pem[i]);
        if (value < 0) continue;
        accumulator = (accumulator << 6) | value;
        bits += 6;
        if (bits >= 8) {
            bits -= 8;
            der[der_length++] = (uint8_t)(accumulator >> bits);
            accumulator &= (UINT32_C(1) << bits) - 1;
        }
    }
    cursor = der;
    end = der + der_length;
    if (cursor >= end || *cursor++ != 0x30 || !der_read_length(&cursor, end, &sequence_length) ||
        sequence_length > (size_t)(end - cursor)) {
        LocalFree(der);
        return false;
    }
    sequence_end = cursor + sequence_length;
    if (cursor >= sequence_end || *cursor++ != 0x02 || !der_read_length(&cursor, sequence_end, &modulus_length) ||
        modulus_length == 0 || modulus_length > (size_t)(sequence_end - cursor)) {
        LocalFree(der);
        return false;
    }
    *block_size = modulus_length - (modulus_length > 1 && cursor[0] == 0 ? 1 : 0);
    LocalFree(der);
    return *block_size != 0;
}

#ifndef ML_ASSET_HOOKS_TEST
static bool write_boot_boost_stub(const uint8_t *source, size_t size, size_t block_size,
                                  wchar_t *path, size_t path_capacity) {
    wchar_t directory[MAX_PATH];
    HANDLE file;
    DWORD written;
    size_t count;
    if (source == NULL || size == 0 || path == NULL || path_capacity == 0 ||
        GetTempPathW(MAX_PATH, directory) == 0 || GetTempFileNameW(directory, L"me3", 0, path) == 0) return false;
    count = block_size < size ? block_size : size;
    file = CreateFileW(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
    if (file == INVALID_HANDLE_VALUE || !WriteFile(file, source, (DWORD)count, &written, NULL) || written != count) {
        if (file != INVALID_HANDLE_VALUE) CloseHandle(file);
        DeleteFileW(path);
        return false;
    }
    CloseHandle(file);
    return true;
}

static bool boot_boost_mount(const wchar_t *bhd_path, dl_allocator_t *allocator, mount_ebl_t original,
                             const wchar_t *mount_name, const wchar_t *bdt_path,
                             const char *rsa_key, size_t key_len, bool *mounted, bool *handled) {
    wchar_t *cache_directory = NULL;
    wchar_t *cache_path = NULL;
    wchar_t *expanded = NULL;
    wchar_t stub_path[MAX_PATH] = { 0 };
    HANDLE source = INVALID_HANDLE_VALUE;
    LARGE_INTEGER source_size = { 0 };
    uint8_t *encrypted = NULL;
    DWORD read = 0;
    uint64_t key[2];
    size_t block_size;
    bool result = false;
    ml_dl_mount_snapshot_t snapshot = { 0 };
    ml_dl_vfs_mounts_t stub_mounts = { 0 };
    ml_dl_vfs_mounts_t full_mounts = { 0 };
    ml_dl_device_manager_guard_t guard = { 0 };
    if (mounted == NULL || handled == NULL || !config.boot_boost || bhd_path == NULL || allocator == NULL || device_manager == NULL ||
        !rsa_public_key_block_size(rsa_key, key_len, &block_size)) return false;
    *mounted = false;
    *handled = false;
    if (!ml_dl_device_manager_lock(device_manager, &guard) ||
        !ml_dl_device_expand_path(device_manager, bhd_path, &expanded)) goto fallback;
    source = CreateFileW(expanded, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (source == INVALID_HANDLE_VALUE || !GetFileSizeEx(source, &source_size) || source_size.QuadPart <= 0 ||
        source_size.QuadPart > 64 * 1024 * 1024) goto fallback;
    encrypted = LocalAlloc(0, (size_t)source_size.QuadPart);
    if (encrypted == NULL || !ReadFile(source, encrypted, (DWORD)source_size.QuadPart, &read, NULL) ||
        read != (DWORD)source_size.QuadPart || !ml_boot_boost_cache_key(encrypted, (size_t)source_size.QuadPart, key)) goto fallback;
    CloseHandle(source); source = INVALID_HANDLE_VALUE;
    cache_directory = config_full_path_alloc(L"cache");
    cache_path = ml_boot_boost_cache_path(cache_directory, key);
    if (cache_directory == NULL || cache_path == NULL) goto fallback;
    CreateDirectoryW(cache_directory, NULL);
    if (!write_boot_boost_stub(encrypted, (size_t)source_size.QuadPart, block_size, stub_path, MAX_PATH) ||
        !ml_dl_mount_snapshot(device_manager, &snapshot) || !ml_dl_mounts_init(&stub_mounts)) goto fallback;
    result = original(mount_name, stub_path, bdt_path, allocator, rsa_key, key_len);
    *handled = result;
    DeleteFileW(stub_path);
    if (!result) goto fallback;
    if (!ml_dl_device_extract_new(device_manager, &snapshot, &stub_mounts)) {
        *mounted = true;
        result = true;
        goto done;
    }
    if (stub_mounts.count == 0) goto fallback;
    {
        ml_dl_virtual_mount_t *mount = &stub_mounts.items[0];
        bhd5_holder_t *holder = (bhd5_holder_t *)((uint8_t *)mount->device + ml_game_context_get()->ebl_bhd_holder_offset);
        uint32_t size;
        if (holder->header == NULL || memcmp(holder->header, "BHD5", 4) != 0 ||
            (memcpy(&size, holder->header + 12, sizeof(size)), size < 24 || size > 64 * 1024 * 1024)) goto full_mount;
        {
            uint8_t *cached = allocator->vtable->allocate_aligned(allocator, size, 4096);
            if (cached != NULL) {
                uint32_t bucket_count;
                uint32_t bucket_offset;
                if (ml_boot_boost_cache_load(cache_path, cached, size)) {
                    memcpy(&bucket_count, cached + 16, sizeof(bucket_count));
                    memcpy(&bucket_offset, cached + 20, sizeof(bucket_offset));
                } else {
                    bucket_count = UINT32_MAX;
                    bucket_offset = UINT32_MAX;
                }
                if (bucket_offset <= size && bucket_count <= (size - bucket_offset) / sizeof(uint32_t)) {
                    uint8_t *previous = holder->header;
                    holder->header = cached;
                    holder->bucket_count = bucket_count;
                    holder->buckets = (uint32_t *)(cached + bucket_offset);
                    dl_allocator_dealloc(allocator, previous);
                    if (!ml_dl_device_push_mounts_permanent(device_manager, &stub_mounts)) {
                        if (ml_dl_device_restore_mounts(device_manager, &stub_mounts)) {
                            *mounted = true;
                            result = true;
                            goto done;
                        }
                        *handled = false;
                        goto fallback;
                    }
                    *mounted = true;
                    result = true;
                    goto done;
                }
                dl_allocator_dealloc(allocator, cached);
            }
        }
    }
full_mount:
    if (stub_mounts.count != 0) {
        if (!ml_dl_device_restore_mounts(device_manager, &stub_mounts)) {
            *handled = false;
            result = false;
            goto done;
        }
        ml_dl_mount_snapshot_destroy(&snapshot);
        if (!ml_dl_mount_snapshot(device_manager, &snapshot)) {
            *mounted = true;
            result = true;
            goto done;
        }
    }
    ml_dl_mounts_destroy(&stub_mounts);
    if (!ml_dl_mounts_init(&full_mounts)) goto fallback;
    result = original(mount_name, bhd_path, bdt_path, allocator, rsa_key, key_len);
    if (result) *handled = true;
    if (!result) goto fallback;
    if (!ml_dl_device_extract_new(device_manager, &snapshot, &full_mounts)) {
        *mounted = true;
        result = true;
        goto done;
    }
    if (full_mounts.count == 0) goto fallback;
    *handled = true;
    {
        ml_dl_virtual_mount_t *mount = &full_mounts.items[0];
        bhd5_holder_t *holder = (bhd5_holder_t *)((uint8_t *)mount->device + ml_game_context_get()->ebl_bhd_holder_offset);
        uint32_t size;
        if (holder->header != NULL && memcmp(holder->header, "BHD5", 4) == 0 &&
            (memcpy(&size, holder->header + 12, sizeof(size)), size >= 24 && size <= 64 * 1024 * 1024) &&
            ml_bhd5_header_valid(holder->header, size)) {
            (void)ml_boot_boost_cache_store(cache_path, holder->header, size);
        }
    }
    if (!ml_dl_device_push_mounts_permanent(device_manager, &full_mounts)) {
        if (ml_dl_device_restore_mounts(device_manager, &full_mounts)) {
            *mounted = true;
            result = true;
            goto done;
        }
        *handled = false;
        goto fallback;
    }
    *mounted = true;
    result = true;
    goto done;
fallback:
    result = false;
done:
    if (source != INVALID_HANDLE_VALUE) CloseHandle(source);
    DeleteFileW(stub_path);
    LocalFree(encrypted);
    LocalFree(cache_directory);
    LocalFree(cache_path);
    LocalFree(expanded);
    ml_dl_mounts_destroy(&stub_mounts);
    ml_dl_mounts_destroy(&full_mounts);
    ml_dl_mount_snapshot_destroy(&snapshot);
    ml_dl_device_manager_unlock(&guard);
    *mounted = result;
    return result;
}

static bool make_override_path(const ml_msvc2015_string_t *path, ml_msvc2015_string_t *replacement) {
    ml_dl_device_manager_guard_t guard = { 0 };
    wchar_t *expanded = NULL;
    wchar_t *uid = NULL;
    bool result = false;
    const wchar_t *raw = ml_dl_string_data(path);
    if (raw == NULL || device_manager == NULL || !ml_dl_device_manager_lock(device_manager, &guard)) return false;
    if (vfs_uid_to_path(raw) == NULL && ml_dl_device_expand_path(device_manager, raw, &expanded)) {
        if (mods_file_virtual_to_uid_prefixed(expanded, &uid) || vfs_virtual_to_uid(expanded, &uid)) {
            result = ml_dl_string_clone_replace(path, uid, replacement);
        }
    }
    LocalFree(uid);
    LocalFree(expanded);
    ml_dl_device_manager_unlock(&guard);
    return result;
}

static void *asset_hook_original(asset_hook_t *hooks, size_t count, void **slot) {
    for (size_t i = 0; i < count; i++) if (hooks[i].slot == slot) return hooks[i].original;
    return NULL;
}

static bool install_asset_hook(asset_hook_t *hooks, size_t *count, size_t capacity,
                               void **slot, void *detour) {
    ml_hook_result_t result;
    void *target;
    void *original;
    if (slot == NULL) return false;
    target = *slot;
    if (target == NULL || !pointer_in_text(target)) return false;
    if (asset_hook_original(hooks, *count, slot) != NULL) return true;
    if (*count == capacity) return false;
    original = NULL;
    for (size_t i = 0; i < *count; i++) if (hooks[i].target == target) original = hooks[i].original;
    if (original == NULL) {
        result = ml_hook_install(target, detour, &original);
        if (result != ML_HOOK_APPLIED) return false;
    }
    hooks[*count].target = target;
    hooks[*count].original = original;
    hooks[*count].slot = slot;
    (*count)++;
    return true;
}

static bool hook_file_operator(ml_dl_file_operator_t *file_operator);

static void *__cdecl disk_open_file_hooked(ml_dl_device_t *device, ml_msvc2015_string_t *path,
                                            const wchar_t *path_cstr, void *container, void *allocator, bool temporary) {
    void *result;
    ml_msvc2015_string_t replacement = { 0 };
    bool overridden = make_override_path(path, &replacement);
    dl_open_file_t original = (dl_open_file_t)asset_hook_original(open_hooks, open_hook_count, &device->vtable->open_file);
    if (InterlockedCompareExchange(&logged_disk_open, 1, 0) == 0) {
        fwprintf(stderr, L"NOTE: [asset-hooks] disk open_file enter: device=%p path=%p path_cstr=%p container=%p allocator=%p temporary=%d\n",
                 device, path, path_cstr, container, allocator, temporary ? 1 : 0);
    }
    if (overridden) {
        path = &replacement;
        path_cstr = ml_dl_string_data(&replacement);
    }
    if (overridden && InterlockedCompareExchange(&logged_disk_override, 1, 0) == 0) {
        fwprintf(stderr, L"NOTE: [asset-hooks] disk open_file VFS override: %s\n", path_cstr);
    }
    if (original == NULL) { ml_dl_string_destroy(&replacement); return NULL; }
    result = original(device, path, path_cstr, container, allocator, temporary);
    ml_dl_string_destroy(&replacement);
    if (InterlockedCompareExchange(&logged_disk_open_return, 1, 0) == 0) {
        fwprintf(stderr, L"NOTE: [asset-hooks] disk open_file returned: operator=%p\n", result);
    }
    if (result != NULL) (void)hook_file_operator(result);
    return result;
}

static dl_open_file_t ebl_open_original(void *target) {
    for (size_t i = 0; i < ebl_open_hook_count; i++) {
        if (ebl_open_hooks[i].target == target) return (dl_open_file_t)ebl_open_hooks[i].original;
    }
    return NULL;
}

static void *__cdecl ebl_open_file_hooked(ml_dl_device_t *device, ml_msvc2015_string_t *path,
                                          const wchar_t *path_cstr, void *container, void *allocator, bool temporary) {
    ml_msvc2015_string_t replacement = { 0 };
    dl_open_file_t original = device == NULL || device->vtable == NULL ? NULL :
                              ebl_open_original(device->vtable->open_file);
    if (make_override_path(path, &replacement)) {
        void *result;
        const wchar_t *replacement_cstr = ml_dl_string_data(&replacement);
        result = disk_open_file_hooked(disk_device, &replacement, replacement_cstr,
                                       container, allocator, temporary);
        ml_dl_string_destroy(&replacement);
        return result;
    }
    return original == NULL ? NULL : original(device, path, path_cstr, container, allocator, temporary);
}

static bool hook_ebl_device_opens(void) {
    size_t mount_count;
    size_t start_count = ebl_open_hook_count;
    ml_dl_virtual_mount_t *mounts;
    if (device_manager == NULL || disk_device == NULL) return false;
    mount_count = ml_dl_vector_count(&device_manager->bnd4_mounts, sizeof(ml_dl_virtual_mount_t));
    mounts = (ml_dl_virtual_mount_t *)device_manager->bnd4_mounts.first;
    for (size_t i = 0; i < mount_count; i++) {
        void *target;
        void *original;
        bool already_hooked = false;
        if (mounts[i].device == NULL || mounts[i].device->vtable == NULL) continue;
        target = mounts[i].device->vtable->open_file;
        for (size_t j = 0; j < ebl_open_hook_count; j++) {
            if (ebl_open_hooks[j].target == target) already_hooked = true;
        }
        if (already_hooked) continue;
        if (ebl_open_hook_count == sizeof(ebl_open_hooks) / sizeof(ebl_open_hooks[0]) ||
            ml_hook_install(target, ebl_open_file_hooked, &original) != ML_HOOK_APPLIED) {
            remove_ebl_device_opens_from(start_count);
            return false;
        }
        ebl_open_hooks[ebl_open_hook_count++] = (ebl_open_hook_t){ target, original };
    }
    return true;
}

static void remove_ebl_device_opens_from(size_t count) {
    while (ebl_open_hook_count > count) {
        ebl_open_hook_count--;
        (void)remove_asset_hook(ebl_open_hooks[ebl_open_hook_count].target);
        memset(&ebl_open_hooks[ebl_open_hook_count], 0, sizeof(ebl_open_hooks[ebl_open_hook_count]));
    }
}

static bool set_path_with_override(ml_dl_file_operator_t *file_operator, ml_msvc2015_string_t *path,
                                   bool p3, bool p4, size_t index) {
    void **slot = &file_operator->vtable->set_path + index;
    dl_set_path_t original = (dl_set_path_t)asset_hook_original(set_path_hooks, set_path_hook_count, slot);
    ml_msvc2015_string_t replacement = { 0 };
    bool overridden = make_override_path(path, &replacement);
    bool result;
    if (overridden) path = &replacement;
    if (overridden && InterlockedCompareExchange(&logged_set_path_override, 1, 0) == 0) {
        fwprintf(stderr, L"NOTE: [asset-hooks] DlFileOperator::SetPath%zu VFS override: %s\n",
                 index + 1, ml_dl_string_data(path));
    }
    result = original != NULL && original(file_operator, path, p3, p4);
    ml_dl_string_destroy(&replacement);
    return result;
}

static bool __cdecl set_path_hooked(ml_dl_file_operator_t *file_operator, ml_msvc2015_string_t *path, bool p3, bool p4) {
    return set_path_with_override(file_operator, path, p3, p4, 0);
}

static bool __cdecl set_path2_hooked(ml_dl_file_operator_t *file_operator, ml_msvc2015_string_t *path, bool p3, bool p4) {
    return set_path_with_override(file_operator, path, p3, p4, 1);
}

static bool __cdecl set_path3_hooked(ml_dl_file_operator_t *file_operator, ml_msvc2015_string_t *path, bool p3, bool p4) {
    return set_path_with_override(file_operator, path, p3, p4, 2);
}

static bool hook_file_operator(ml_dl_file_operator_t *file_operator) {
    void *targets[3];
    void *detours[3] = { set_path_hooked, set_path2_hooked, set_path3_hooked };
    bool result = true;
    AcquireSRWLockExclusive(&set_path_hook_lock);
    if (set_path_hook_attempted) {
        result = set_path_hook_result;
        ReleaseSRWLockExclusive(&set_path_hook_lock);
        return result;
    }
    set_path_hook_attempted = true;
    if (file_operator == NULL || file_operator->vtable == NULL ||
        !pointer_in_text(file_operator->vtable->set_path) ||
        !pointer_in_text(file_operator->vtable->set_path2) ||
        !pointer_in_text(file_operator->vtable->set_path3)) {
        fwprintf(stderr, L"WARNING: [asset-hooks] DlFileOperator layout validation failed: operator=%p vtable=%p\n",
                 file_operator, file_operator == NULL ? NULL : file_operator->vtable);
        set_path_hook_result = false;
        ReleaseSRWLockExclusive(&set_path_hook_lock);
        return false;
    }
    targets[0] = file_operator->vtable->set_path;
    targets[1] = file_operator->vtable->set_path2;
    targets[2] = file_operator->vtable->set_path3;
    fwprintf(stderr, L"NOTE: [asset-hooks] DlFileOperator layout: operator=%p vtable=%p set_path=%p set_path2=%p set_path3=%p\n",
             file_operator, file_operator->vtable, targets[0], targets[1], targets[2]);
    for (size_t i = 0; i < 3; i++) {
        fwprintf(stderr, L"NOTE: [asset-hooks] installing DlFileOperator::SetPath%zu hook\n", i + 1);
        if (!install_asset_hook(set_path_hooks, &set_path_hook_count, 64, &file_operator->vtable->set_path + i, detours[i])) {
            fwprintf(stderr, L"WARNING: [asset-hooks] DlFileOperator::SetPath%zu hook failed\n", i + 1);
            result = false;
        } else {
            fwprintf(stderr, L"NOTE: [asset-hooks] DlFileOperator::SetPath%zu hook applied\n", i + 1);
        }
    }
    set_path_hook_result = result;
    ReleaseSRWLockExclusive(&set_path_hook_lock);
    return result;
}

static void *__cdecl make_ebl_object_hooked(void *utility, const wchar_t *path, void *allocator) {
    ml_dl_device_manager_guard_t guard = { 0 };
    wchar_t *expanded = NULL;
    bool loose_override = false;
    if (device_manager != NULL && path != NULL && ml_dl_device_manager_lock(device_manager, &guard)) {
        if (ml_dl_device_expand_path(device_manager, path, &expanded)) {
            loose_override = mods_file_search_prefixed_domain(expanded, VFS_LOOKUP_VIRTUAL) != NULL ||
                             vfs_lookup(expanded) != NULL;
        }
        LocalFree(expanded);
    }
    if (loose_override && InterlockedCompareExchange(&logged_ebl_fallback, 1, 0) == 0) {
        fwprintf(stderr, L"NOTE: [asset-hooks] MakeEblObject loose fallback: %s\n", path);
    }
    if (loose_override) {
        ml_dl_device_manager_unlock(&guard);
        return NULL;
    }
    ml_dl_device_manager_unlock(&guard);
    return old_make_ebl_object(utility, path, allocator);
}

static bool __cdecl mount_ebl_hooked(const wchar_t *mount_name, const wchar_t *bhd_path, const wchar_t *bdt_path,
                                     void *allocator, const char *rsa_key, size_t key_len) {
    ml_dl_device_manager_guard_t guard = { 0 };
    ml_dl_mount_snapshot_t snapshot = { 0 };
    ml_dl_vfs_mounts_t new_mounts = { 0 };
    bool snapshot_ok = false;
    bool handled = false;
    bool result;
    fwprintf(stderr, L"NOTE: [asset-hooks] MountEbl enter: mount=%p bhd=%p bdt=%p allocator=%p key=%p key_len=%zu boot_boost=%d\n",
             mount_name, bhd_path, bdt_path, allocator, rsa_key, key_len, config.boot_boost ? 1 : 0);
    if (config.boot_boost && boot_boost_mount(bhd_path, (dl_allocator_t *)allocator, old_mount_ebl,
                                               mount_name, bdt_path, rsa_key, key_len, &result, &handled)) {
        fwprintf(stderr, L"NOTE: [asset-hooks] MountEbl BootBoost result: %d\n", result ? 1 : 0);
        if (result) {
            ml_dl_device_manager_guard_t hook_guard = { 0 };
            bool hooked = ml_dl_device_manager_lock(device_manager, &hook_guard) && hook_ebl_device_opens();
            ml_dl_device_manager_unlock(&hook_guard);
            if (!hooked) fwprintf(stderr, L"WARNING: [asset-hooks] failed to hook BootBoost BND4 device opens\n");
        }
        return result;
    }
    if (handled) return result;
    fwprintf(stderr, L"NOTE: [asset-hooks] MountEbl calling original\n");
    if (device_manager != NULL && ml_dl_device_manager_lock(device_manager, &guard)) {
        snapshot_ok = ml_dl_mount_snapshot(device_manager, &snapshot);
        (void)ml_dl_mounts_init(&new_mounts);
    }
    result = old_mount_ebl(mount_name, bhd_path, bdt_path, allocator, rsa_key, key_len);
    if (guard.manager != NULL && snapshot_ok && ml_dl_device_extract_new(device_manager, &snapshot, &new_mounts)) {
        if (!ml_dl_device_push_mounts_permanent(device_manager, &new_mounts)) {
            fwprintf(stderr, L"WARNING: [asset-hooks] failed to restore mounted BND4 devices\n");
            (void)ml_dl_device_restore_mounts(device_manager, &new_mounts);
        }
    }
    ml_dl_mounts_destroy(&new_mounts);
    ml_dl_mount_snapshot_destroy(&snapshot);
    ml_dl_device_manager_unlock(&guard);
    if (result) {
        ml_dl_device_manager_guard_t hook_guard = { 0 };
        bool hooked = ml_dl_device_manager_lock(device_manager, &hook_guard) && hook_ebl_device_opens();
        ml_dl_device_manager_unlock(&hook_guard);
        if (!hooked) fwprintf(stderr, L"WARNING: [asset-hooks] failed to hook mounted BND4 device opens\n");
    }
    fwprintf(stderr, L"NOTE: [asset-hooks] MountEbl original returned: %d\n", result ? 1 : 0);
    if (result && InterlockedCompareExchange(&logged_mount_ebl, 1, 0) == 0) {
        fwprintf(stderr, L"NOTE: [asset-hooks] MountEbl completed: %s\n", mount_name);
    }
    return result;
}

static bool install_pre_hooks(void) {
    void *mount;
    if (pre_hooks_installed) return true;
    device_manager = ml_dl_device_manager_find(game_image_base);
    if (device_manager == NULL) {
        fwprintf(stderr, L"WARNING: [asset-hooks] DlDeviceManager validation failed; archive device hooks disabled\n");
        return false;
    }
    disk_device = device_manager->disk_device;
    if (!install_asset_hook(open_hooks, &open_hook_count, 64, &disk_device->vtable->open_file, disk_open_file_hooked)) {
        fwprintf(stderr, L"WARNING: [asset-hooks] disk open_file hook failed\n");
        return false;
    }
    fwprintf(stderr, L"NOTE: [asset-hooks] disk open_file hook applied\n");
    mount = find_mount_ebl();
    if (mount != NULL && ml_hook_install(mount, mount_ebl_hooked, (void **)&old_mount_ebl) == ML_HOOK_APPLIED) {
        mount_ebl_hook_target = mount;
        fwprintf(stderr, L"NOTE: [asset-hooks] MountEbl hook applied\n");
        pre_hooks_installed = true;
        return true;
    } else {
        fwprintf(stderr, L"WARNING: [asset-hooks] MountEbl signature/hook failed\n");
        (void)remove_asset_hooks(open_hooks, open_hook_count);
        memset(open_hooks, 0, sizeof(open_hooks));
        open_hook_count = 0;
        disk_device = NULL;
        return false;
    }
}

static bool install_post_hooks(void) {
    void **vtable;
    void *target = NULL;
    if (post_hooks_installed) return true;
    vtable = rtti_find_vtable("DLEBL::DLEncryptedBinderLightUtility");
    if (vtable != NULL) target = vtable[1];
    if (target == NULL) {
        void **manager = singleton_find("CSEblFileManager");
        const IMAGE_SECTION_HEADER *rdata = pe_section_by_name(game_image_base, ".rdata");
        if (manager != NULL && rdata != NULL) {
            void *interface_pointer = pe_section_contains_va(game_image_base, rdata, manager[0])
                ? manager[1] : manager[0];
            void **utility = interface_pointer == NULL ? NULL : *(void ***)interface_pointer;
            if (utility != NULL) target = utility[1];
        }
    }
    if (target != NULL && pointer_in_text(target) &&
        ml_hook_install(target, make_ebl_object_hooked, (void **)&old_make_ebl_object) == ML_HOOK_APPLIED) {
        make_ebl_object_hook_target = target;
        fwprintf(stderr, L"NOTE: [asset-hooks] MakeEblObject hook applied\n");
    } else {
        fwprintf(stderr, L"WARNING: [asset-hooks] MakeEblObject RTTI/hook failed\n");
        return false;
    }
    {
        ml_dl_device_manager_guard_t guard = { 0 };
        size_t previous_open_count = ebl_open_hook_count;
        bool hooked = ml_dl_device_manager_lock(device_manager, &guard) && hook_ebl_device_opens();
        ml_dl_device_manager_unlock(&guard);
        if (!hooked) {
            fwprintf(stderr, L"WARNING: [asset-hooks] initial BND4 device open hooks failed\n");
            remove_ebl_device_opens_from(previous_open_count);
            (void)remove_asset_hook(make_ebl_object_hook_target);
            make_ebl_object_hook_target = NULL;
            old_make_ebl_object = NULL;
            return false;
        }
    }
    post_hooks_installed = true;
    return true;
}

static void __cdecl file_step_init_hooked(void *this_ptr, fd4_time_t *time) {
    bool pre_hooks_applied = install_pre_hooks();
    old_file_step_init(this_ptr, time);
    fwprintf(stdout, L"NOTE: [asset-hooks] VFS cache generation %llu enabled\n",
             (unsigned long long)vfs_reset_lookup_caches());
    if (pre_hooks_applied) install_post_hooks();
}

bool ml_asset_hooks_install(const ml_game_descriptor_t *game, void *image_base, size_t image_size) {
    void *step;
    if (game == NULL || game->file_step_name == NULL || image_base == NULL || image_size == 0 ||
        vfs_entry_count() == 0) return true;
    if (file_step_hook_installed) return true;
    game_image_base = image_base;
    game_image_size = image_size;
    step = fd4_step_find(game->file_step_name);
    if (step == NULL) {
        fwprintf(stderr, L"WARNING: [asset-hooks] %ls not found for %ls; Dantelion VFS disabled\n",
                 game->file_step_name, game->title);
        return false;
    }
    if (ml_hook_install(step, file_step_init_hooked, (void **)&old_file_step_init) != ML_HOOK_APPLIED) {
        fwprintf(stderr, L"WARNING: [asset-hooks] %ls hook failed for %ls\n",
                 game->file_step_name, game->title);
        return false;
    }
    file_step_hook_installed = true;
    file_step_hook_target = step;
    fwprintf(stderr, L"NOTE: [asset-hooks] %ls hook applied for %ls\n",
             game->file_step_name, game->title);
    return true;
}

static bool remove_asset_hook(void *target) {
    MH_STATUS status;
    if (target == NULL) return true;
    status = MH_RemoveHook(target);
    if (status == MH_OK || status == MH_ERROR_NOT_CREATED) return true;
    fwprintf(stderr, L"WARNING: [asset-hooks] failed to remove hook at %p: %d\n", target, status);
    return false;
}

static bool remove_asset_hooks(asset_hook_t *hooks, size_t count) {
    void *targets[64];
    if (count > sizeof(targets) / sizeof(targets[0])) return false;
    for (size_t i = 0; i < count; i++) targets[i] = hooks[i].target;
    return ml_hook_targets_remove_unique(targets, count, remove_asset_hook);
}

bool ml_asset_hooks_uninstall(void) {
    bool result = true;
    if (!remove_asset_hook(file_step_hook_target)) result = false;
    if (!remove_asset_hook(make_ebl_object_hook_target)) result = false;
    if (!remove_asset_hook(mount_ebl_hook_target)) result = false;
    if (!remove_asset_hooks(set_path_hooks, set_path_hook_count)) result = false;
    if (!remove_asset_hooks(open_hooks, open_hook_count)) result = false;
    for (size_t i = 0; i < ebl_open_hook_count; i++) {
        if (!remove_asset_hook(ebl_open_hooks[i].target)) result = false;
    }
    if (!result) return false;

    memset(open_hooks, 0, sizeof(open_hooks));
    memset(set_path_hooks, 0, sizeof(set_path_hooks));
    memset(ebl_open_hooks, 0, sizeof(ebl_open_hooks));
    open_hook_count = 0;
    set_path_hook_count = 0;
    ebl_open_hook_count = 0;
    game_image_base = NULL;
    game_image_size = 0;
    device_manager = NULL;
    disk_device = NULL;
    old_file_step_init = NULL;
    old_make_ebl_object = NULL;
    old_mount_ebl = NULL;
    file_step_hook_target = NULL;
    mount_ebl_hook_target = NULL;
    make_ebl_object_hook_target = NULL;
    pre_hooks_installed = false;
    post_hooks_installed = false;
    file_step_hook_installed = false;
    logged_disk_override = 0;
    logged_disk_open = 0;
    logged_disk_open_return = 0;
    logged_set_path_override = 0;
    logged_ebl_fallback = 0;
    logged_mount_ebl = 0;
    set_path_hook_attempted = false;
    set_path_hook_result = false;
    return true;
}
#endif
