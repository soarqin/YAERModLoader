/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "eldenring_assets.h"

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

#include <MinHook.h>

#include <stdio.h>
#include <string.h>

#include <shlwapi.h>

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

typedef struct bhd5_holder_s {
    uint8_t *header;
    uint32_t bucket_count;
    uint32_t *buckets;
} bhd5_holder_t;

static asset_hook_t open_hooks[64];
static size_t open_hook_count;
static asset_hook_t set_path_hooks[64];
static size_t set_path_hook_count;
static LONG logged_disk_override;
static LONG logged_disk_open;
static LONG logged_disk_open_return;
static LONG logged_set_path_override;
static LONG logged_set_path_enter[3];
static LONG logged_set_path_return[3];
static LONG logged_ebl_fallback;
static LONG logged_mount_ebl;
static LONG file_operator_hook_attempted;

static bool pointer_in_text(const void *pointer) {
    const IMAGE_SECTION_HEADER *text = pe_section_by_name(game_image_base, ".text");
    return text != NULL && pe_section_contains_va(game_image_base, text, pointer);
}

static void *find_mount_ebl(void) {
    static const char *const patterns[] = {
        "48 8B 45 ?? 48 89 44 24 28 ?? 89 ?? 24 20 4C 8B 0D ?? ?? ?? ?? ?? 8B ?? ?? ?? ?? ?? ?? ?? E8 ?? ?? ?? ?? 0F B6 D8",
        "53 48 83 EC 30 48 8B 44 24 70 4D 8B D1 4C 8B 4C 24 60 4D 8B D8 48 89 44 24 28 48 8B CA 48 8B 44 24 68 4D 8B C2 49 8B D3 48 89 44 24 20 E8 ?? ?? ?? ?? 48 83 C4 30 5B C3",
    };
    for (size_t i = 0; i < sizeof(patterns) / sizeof(patterns[0]); i++) {
        uint8_t *match = sig_scan(game_image_base, game_image_size, patterns[i]);
        if (match == NULL) continue;
        for (size_t offset = 0; offset < 56; offset++) {
            if (match[offset] != 0xE8) continue;
            void *target = match + offset + 5 + *(int32_t *)(match + offset + 1);
            if (pointer_in_text(target)) {
                fwprintf(stderr, L"NOTE: [eldenring-assets] MountEbl signature %zu matched at %p target=%p\n", i + 1, match, target);
                return target;
            }
        }
    }
    return NULL;
}

static bool boot_boost_mount(const wchar_t *bhd_path, dl_allocator_t *allocator, mount_ebl_t original,
                             const wchar_t *mount_name, const wchar_t *bdt_path,
                             const char *rsa_key, size_t key_len, bool *mounted) {
    wchar_t *cache_directory = NULL;
    wchar_t *cache_path = NULL;
    wchar_t *expanded = NULL;
    HANDLE source;
    LARGE_INTEGER source_size = { 0 };
    uint8_t *encrypted = NULL;
    DWORD read;
    uint64_t key;
    bool result;
    ml_dl_device_manager_guard_t guard = { 0 };
    if (mounted == NULL || !config.boot_boost || bhd_path == NULL || allocator == NULL || device_manager == NULL) {
        fwprintf(stderr, L"NOTE: [eldenring-assets] BootBoost skipped: mounted=%p enabled=%d bhd=%p allocator=%p manager=%p\n",
                 mounted, config.boot_boost ? 1 : 0, bhd_path, allocator, device_manager);
        return false;
    }
    if (!ml_dl_device_manager_lock(device_manager, &guard)) {
        fwprintf(stderr, L"NOTE: [eldenring-assets] BootBoost skipped: device-manager lock failed\n");
        return false;
    }
    if (!ml_dl_device_expand_path(device_manager, bhd_path, &expanded)) {
        fwprintf(stderr, L"NOTE: [eldenring-assets] BootBoost skipped: virtual-root expansion failed\n");
        ml_dl_device_manager_unlock(&guard);
        return false;
    }
    fwprintf(stderr, L"NOTE: [eldenring-assets] BootBoost path: virtual=%s expanded=%s\n", bhd_path, expanded);
    source = CreateFileW(expanded, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (source == INVALID_HANDLE_VALUE || !GetFileSizeEx(source, &source_size) || source_size.QuadPart <= 0 || source_size.QuadPart > 64 * 1024 * 1024) {
        fwprintf(stderr, L"NOTE: [eldenring-assets] BootBoost skipped: source open/size failed path=%s error=%lu size=%lld\n",
                 expanded, GetLastError(), source_size.QuadPart);
        if (source != INVALID_HANDLE_VALUE) CloseHandle(source);
        LocalFree(expanded);
        ml_dl_device_manager_unlock(&guard);
        return false;
    }
    encrypted = LocalAlloc(0, (size_t)source_size.QuadPart);
    if (encrypted == NULL || !ReadFile(source, encrypted, (DWORD)source_size.QuadPart, &read, NULL) || read != source_size.QuadPart ||
        !ml_boot_boost_cache_key(encrypted, (size_t)source_size.QuadPart, &key)) {
        fwprintf(stderr, L"NOTE: [eldenring-assets] BootBoost skipped: source read/key failed allocation=%p error=%lu read=%lu\n",
                 encrypted, GetLastError(), read);
        CloseHandle(source); LocalFree(encrypted); LocalFree(expanded); ml_dl_device_manager_unlock(&guard); return false;
    }
    CloseHandle(source);
    cache_directory = config_full_path_alloc(L"cache");
    cache_path = ml_boot_boost_cache_path(cache_directory, key);
    if (cache_directory == NULL || cache_path == NULL) {
        LocalFree(cache_directory);
        LocalFree(cache_path);
        LocalFree(encrypted);
        LocalFree(expanded);
        ml_dl_device_manager_unlock(&guard);
        return false;
    }
    CreateDirectoryW(cache_directory, NULL);
    LocalFree(encrypted);
    /* The game must create the holder before cached contents can be substituted. */
    result = original(mount_name, bhd_path, bdt_path, allocator, rsa_key, key_len);
    *mounted = result;
    if (!result) {
        LocalFree(cache_directory);
        LocalFree(cache_path);
        LocalFree(expanded);
        ml_dl_device_manager_unlock(&guard);
        return true;
    }
    {
        size_t count = ml_dl_vector_count(&device_manager->bnd4_mounts, sizeof(ml_dl_virtual_mount_t));
        if (count != 0) {
            ml_dl_virtual_mount_t *mount = &((ml_dl_virtual_mount_t *)device_manager->bnd4_mounts.first)[count - 1];
            size_t holder_offset = ml_game_context_get()->ebl_bhd_holder_offset;
            bhd5_holder_t *holder = (bhd5_holder_t *)((uint8_t *)mount->device + holder_offset);
            if (holder->header != NULL && memcmp(holder->header, "BHD5", 4) == 0) {
                uint32_t size;
                uint32_t bucket_count;
                uint32_t bucket_offset;
                uint8_t *cached;
                memcpy(&size, holder->header + 12, sizeof(size));
                if (size >= 24 && size <= 64 * 1024 * 1024) {
                    cached = allocator->vtable->allocate_aligned(allocator, size, 4096);
                    if (cached != NULL && ml_boot_boost_cache_load(cache_path, cached, size)) {
                        memcpy(&bucket_count, cached + 16, sizeof(bucket_count));
                        memcpy(&bucket_offset, cached + 20, sizeof(bucket_offset));
                        if (bucket_offset <= size && bucket_count <= (size - bucket_offset) / sizeof(uint32_t)) {
                            uint8_t *previous = holder->header;
                            holder->header = cached;
                            holder->bucket_count = bucket_count;
                            holder->buckets = (uint32_t *)(cached + bucket_offset);
                            dl_allocator_dealloc(allocator, previous);
                        } else {
                            dl_allocator_dealloc(allocator, cached);
                        }
                    } else {
                        dl_allocator_dealloc(allocator, cached);
                        ml_boot_boost_cache_store(cache_path, holder->header, size);
                    }
                }
            }
        }
    }
    LocalFree(cache_directory);
    LocalFree(cache_path);
    LocalFree(expanded);
    ml_dl_device_manager_unlock(&guard);
    return true;
}

static bool replace_dl_path_with_uid(ml_msvc2015_string_t *path) {
    ml_dl_device_manager_guard_t guard = { 0 };
    wchar_t *expanded = NULL;
    bool result = false;
    const wchar_t *raw = ml_dl_string_data(path);
    if (raw == NULL || device_manager == NULL || !ml_dl_device_manager_lock(device_manager, &guard)) return false;
    if (vfs_uid_to_path(raw) == NULL && ml_dl_device_expand_path(device_manager, raw, &expanded)) {
        wchar_t *uid = NULL;
        if (mods_file_virtual_to_uid_prefixed(expanded, &uid) || vfs_virtual_to_uid(expanded, &uid)) {
            result = ml_dl_string_replace_path(path, uid);
            LocalFree(uid);
        }
    }
    LocalFree(expanded);
    ml_dl_device_manager_unlock(&guard);
    return result;
}

static const wchar_t *resolve_disk_path(const ml_msvc2015_string_t *path, wchar_t **expanded) {
    const wchar_t *raw = ml_dl_string_data(path);
    const wchar_t *replacement;
    *expanded = NULL;
    if (raw == NULL) return NULL;
    replacement = vfs_uid_to_path(raw);
    if (replacement != NULL) return replacement;
    if (device_manager != NULL && ml_dl_device_expand_path(device_manager, raw, expanded)) {
        replacement = mods_file_search_prefixed_domain(*expanded, VFS_LOOKUP_DISK_WIDE);
        return replacement != NULL ? replacement : vfs_lookup_domain(*expanded, VFS_LOOKUP_DISK_WIDE);
    }
    return NULL;
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

static void hook_file_operator(ml_dl_file_operator_t *file_operator);

static void *__cdecl disk_open_file_hooked(ml_dl_device_t *device, ml_msvc2015_string_t *path,
                                            const wchar_t *path_cstr, void *container, void *allocator, bool temporary) {
    void *result;
    wchar_t *expanded = NULL;
    const wchar_t *replacement = resolve_disk_path(path, &expanded);
    bool overridden = replacement != NULL;
    if (InterlockedCompareExchange(&logged_disk_open, 1, 0) == 0) {
        fwprintf(stderr, L"NOTE: [eldenring-assets] disk open_file enter: device=%p path=%p path_cstr=%p container=%p allocator=%p temporary=%d\n",
                 device, path, path_cstr, container, allocator, temporary ? 1 : 0);
    }
    if (overridden) path_cstr = replacement;
    if (overridden && InterlockedCompareExchange(&logged_disk_override, 1, 0) == 0) {
        fwprintf(stderr, L"NOTE: [eldenring-assets] disk open_file VFS override: %s\n", path_cstr);
    }
    dl_open_file_t original = (dl_open_file_t)asset_hook_original(open_hooks, open_hook_count, &device->vtable->open_file);
    if (original == NULL) { LocalFree(expanded); return NULL; }
    result = original(device, path, path_cstr, container, allocator, temporary);
    LocalFree(expanded);
    if (InterlockedCompareExchange(&logged_disk_open_return, 1, 0) == 0) {
        fwprintf(stderr, L"NOTE: [eldenring-assets] disk open_file returned: operator=%p\n", result);
    }
    if (result != NULL) hook_file_operator(result);
    return result;
}

static bool __cdecl set_path_hooked(ml_dl_file_operator_t *file_operator, ml_msvc2015_string_t *path, bool p3, bool p4) {
    dl_set_path_t original = (dl_set_path_t)asset_hook_original(set_path_hooks, set_path_hook_count, &file_operator->vtable->set_path);
    bool result;
    if (InterlockedCompareExchange(&logged_set_path_enter[0], 1, 0) == 0) {
        fwprintf(stderr, L"NOTE: [eldenring-assets] SetPath enter: this=%p path=%p p3=%d p4=%d trampoline=%p\n",
                 file_operator, path, p3 ? 1 : 0, p4 ? 1 : 0, original);
    }
    if (replace_dl_path_with_uid(path) && InterlockedCompareExchange(&logged_set_path_override, 1, 0) == 0) {
        fwprintf(stderr, L"NOTE: [eldenring-assets] DlFileOperator::SetPath VFS override: %s\n", ml_dl_string_data(path));
    }
    result = original != NULL && original(file_operator, path, p3, p4);
    if (InterlockedCompareExchange(&logged_set_path_return[0], 1, 0) == 0) {
        fwprintf(stderr, L"NOTE: [eldenring-assets] SetPath returned: %d\n", result ? 1 : 0);
    }
    return result;
}

static bool __cdecl set_path2_hooked(ml_dl_file_operator_t *file_operator, ml_msvc2015_string_t *path, bool p3, bool p4) {
    dl_set_path_t original = (dl_set_path_t)asset_hook_original(set_path_hooks, set_path_hook_count, &file_operator->vtable->set_path2);
    bool result;
    if (InterlockedCompareExchange(&logged_set_path_enter[1], 1, 0) == 0) {
        fwprintf(stderr, L"NOTE: [eldenring-assets] SetPath2 enter: this=%p path=%p p3=%d p4=%d trampoline=%p\n",
                 file_operator, path, p3 ? 1 : 0, p4 ? 1 : 0, original);
    }
    if (replace_dl_path_with_uid(path) && InterlockedCompareExchange(&logged_set_path_override, 1, 0) == 0) {
        fwprintf(stderr, L"NOTE: [eldenring-assets] DlFileOperator::SetPath2 VFS override: %s\n", ml_dl_string_data(path));
    }
    result = original != NULL && original(file_operator, path, p3, p4);
    if (InterlockedCompareExchange(&logged_set_path_return[1], 1, 0) == 0) {
        fwprintf(stderr, L"NOTE: [eldenring-assets] SetPath2 returned: %d\n", result ? 1 : 0);
    }
    return result;
}

static bool __cdecl set_path3_hooked(ml_dl_file_operator_t *file_operator, ml_msvc2015_string_t *path, bool p3, bool p4) {
    dl_set_path_t original = (dl_set_path_t)asset_hook_original(set_path_hooks, set_path_hook_count, &file_operator->vtable->set_path3);
    bool result;
    if (InterlockedCompareExchange(&logged_set_path_enter[2], 1, 0) == 0) {
        fwprintf(stderr, L"NOTE: [eldenring-assets] SetPath3 enter: this=%p path=%p p3=%d p4=%d trampoline=%p\n",
                 file_operator, path, p3 ? 1 : 0, p4 ? 1 : 0, original);
    }
    if (replace_dl_path_with_uid(path) && InterlockedCompareExchange(&logged_set_path_override, 1, 0) == 0) {
        fwprintf(stderr, L"NOTE: [eldenring-assets] DlFileOperator::SetPath3 VFS override: %s\n", ml_dl_string_data(path));
    }
    result = original != NULL && original(file_operator, path, p3, p4);
    if (InterlockedCompareExchange(&logged_set_path_return[2], 1, 0) == 0) {
        fwprintf(stderr, L"NOTE: [eldenring-assets] SetPath3 returned: %d\n", result ? 1 : 0);
    }
    return result;
}

static void hook_file_operator(ml_dl_file_operator_t *file_operator) {
    void *targets[3];
    void *detours[3] = { set_path_hooked, set_path2_hooked, set_path3_hooked };
    if (InterlockedCompareExchange(&file_operator_hook_attempted, 1, 0) != 0) return;
    if (file_operator == NULL || file_operator->vtable == NULL ||
        !pointer_in_text(file_operator->vtable->set_path) ||
        !pointer_in_text(file_operator->vtable->set_path2) ||
        !pointer_in_text(file_operator->vtable->set_path3)) {
        fwprintf(stderr, L"WARNING: [eldenring-assets] DlFileOperator layout validation failed: operator=%p vtable=%p\n",
                 file_operator, file_operator == NULL ? NULL : file_operator->vtable);
        return;
    }
    targets[0] = file_operator->vtable->set_path;
    targets[1] = file_operator->vtable->set_path2;
    targets[2] = file_operator->vtable->set_path3;
    fwprintf(stderr, L"NOTE: [eldenring-assets] DlFileOperator layout: operator=%p vtable=%p set_path=%p set_path2=%p set_path3=%p\n",
             file_operator, file_operator->vtable, targets[0], targets[1], targets[2]);
    for (size_t i = 0; i < 3; i++) {
        fwprintf(stderr, L"NOTE: [eldenring-assets] installing DlFileOperator::SetPath%zu hook\n", i + 1);
        if (!install_asset_hook(set_path_hooks, &set_path_hook_count, 64, &file_operator->vtable->set_path + i, detours[i])) {
            fwprintf(stderr, L"WARNING: [eldenring-assets] DlFileOperator::SetPath%zu hook failed\n", i + 1);
        } else {
            fwprintf(stderr, L"NOTE: [eldenring-assets] DlFileOperator::SetPath%zu hook applied\n", i + 1);
        }
    }
}

static void hook_mounted_bnd4_devices(void) {
    size_t count;
    if (device_manager == NULL) return;
    count = ml_dl_vector_count(&device_manager->bnd4_mounts, sizeof(ml_dl_virtual_mount_t));
    fwprintf(stderr, L"NOTE: [eldenring-assets] inspecting %zu mounted BND4 devices\n", count);
    for (size_t i = 0; i < count; i++) {
        ml_dl_virtual_mount_t *mount = &((ml_dl_virtual_mount_t *)device_manager->bnd4_mounts.first)[i];
        if (mount->device != NULL && mount->device->vtable != NULL &&
            !install_asset_hook(open_hooks, &open_hook_count, 64,
                                &mount->device->vtable->open_file, disk_open_file_hooked)) {
            fwprintf(stderr, L"WARNING: [eldenring-assets] BND4 open_file hook failed\n");
        }
    }
}

static void *__cdecl make_ebl_object_hooked(void *utility, const wchar_t *path, void *allocator) {
    ml_dl_device_manager_guard_t guard = { 0 };
    wchar_t *expanded = NULL;
    bool loose_override = false;
    if (device_manager != NULL && path != NULL && ml_dl_device_manager_lock(device_manager, &guard)) {
        if (ml_dl_device_expand_path(device_manager, path, &expanded)) loose_override = vfs_lookup(expanded) != NULL;
        LocalFree(expanded);
        ml_dl_device_manager_unlock(&guard);
    }
    if (loose_override && InterlockedCompareExchange(&logged_ebl_fallback, 1, 0) == 0) {
        fwprintf(stderr, L"NOTE: [eldenring-assets] MakeEblObject loose fallback: %s\n", path);
    }
    return loose_override ? NULL : old_make_ebl_object(utility, path, allocator);
}

static bool __cdecl mount_ebl_hooked(const wchar_t *mount_name, const wchar_t *bhd_path, const wchar_t *bdt_path,
                                     void *allocator, const char *rsa_key, size_t key_len) {
    bool result;
    fwprintf(stderr, L"NOTE: [eldenring-assets] MountEbl enter: mount=%p bhd=%p bdt=%p allocator=%p key=%p key_len=%zu boot_boost=%d\n",
             mount_name, bhd_path, bdt_path, allocator, rsa_key, key_len, config.boot_boost ? 1 : 0);
    if (config.boot_boost && boot_boost_mount(bhd_path, (dl_allocator_t *)allocator, old_mount_ebl,
                                              mount_name, bdt_path, rsa_key, key_len, &result)) {
        fwprintf(stderr, L"NOTE: [eldenring-assets] MountEbl BootBoost result: %d\n", result ? 1 : 0);
        return result;
    }
    fwprintf(stderr, L"NOTE: [eldenring-assets] MountEbl calling original\n");
    result = old_mount_ebl(mount_name, bhd_path, bdt_path, allocator, rsa_key, key_len);
    fwprintf(stderr, L"NOTE: [eldenring-assets] MountEbl original returned: %d\n", result ? 1 : 0);
    if (result && InterlockedCompareExchange(&logged_mount_ebl, 1, 0) == 0) {
        fwprintf(stderr, L"NOTE: [eldenring-assets] MountEbl completed: %s\n", mount_name);
    }
    if (!result || device_manager == NULL) return result;
    ml_dl_device_manager_guard_t guard = { 0 };
    if (ml_dl_device_manager_lock(device_manager, &guard)) {
        hook_mounted_bnd4_devices();
        ml_dl_device_manager_unlock(&guard);
    }
    return result;
}

static void install_pre_hooks(void) {
    void *mount;
    if (pre_hooks_installed) return;
    device_manager = ml_dl_device_manager_find(game_image_base);
    if (device_manager == NULL) {
        fwprintf(stderr, L"WARNING: [eldenring-assets] DlDeviceManager validation failed; archive device hooks disabled\n");
        return;
    }
    if (!install_asset_hook(open_hooks, &open_hook_count, 64, &device_manager->disk_device->vtable->open_file, disk_open_file_hooked)) {
        fwprintf(stderr, L"WARNING: [eldenring-assets] disk open_file hook failed\n");
    } else {
        fwprintf(stderr, L"NOTE: [eldenring-assets] disk open_file hook applied\n");
    }
    {
        ml_dl_device_manager_guard_t guard = { 0 };
        if (ml_dl_device_manager_lock(device_manager, &guard)) {
            hook_mounted_bnd4_devices();
            ml_dl_device_manager_unlock(&guard);
        }
    }
    mount = find_mount_ebl();
    if (mount != NULL && ml_hook_install(mount, mount_ebl_hooked, (void **)&old_mount_ebl) == ML_HOOK_APPLIED) {
        mount_ebl_hook_target = mount;
        fwprintf(stderr, L"NOTE: [eldenring-assets] MountEbl hook applied\n");
        pre_hooks_installed = true;
    } else {
        fwprintf(stderr, L"WARNING: [eldenring-assets] MountEbl signature/hook failed\n");
        pre_hooks_installed = true;
    }
}

static void install_post_hooks(void) {
    void **vtable;
    if (post_hooks_installed) return;
    vtable = rtti_find_vtable("DLEBL::DLEncryptedBinderLightUtility");
    if (vtable != NULL && pointer_in_text(vtable[1]) &&
        ml_hook_install(vtable[1], make_ebl_object_hooked, (void **)&old_make_ebl_object) == ML_HOOK_APPLIED) {
        make_ebl_object_hook_target = vtable[1];
        fwprintf(stderr, L"NOTE: [eldenring-assets] MakeEblObject hook applied\n");
    } else {
        fwprintf(stderr, L"WARNING: [eldenring-assets] MakeEblObject RTTI/hook failed\n");
    }
    post_hooks_installed = true;
}

static void __cdecl file_step_init_hooked(void *this_ptr, fd4_time_t *time) {
    vfs_begin_lookup_reset();
    install_pre_hooks();
    old_file_step_init(this_ptr, time);
    fwprintf(stdout, L"NOTE: [from-assets] VFS cache generation %llu enabled\n",
             (unsigned long long)vfs_reset_lookup_caches());
    install_post_hooks();
}

bool from_assets_install(const ml_game_descriptor_t *game, void *image_base, size_t image_size) {
    void *step;
    if (game == NULL || game->file_step_name == NULL || image_base == NULL || image_size == 0 ||
        vfs_entry_count() == 0) return true;
    if (file_step_hook_installed) return true;
    game_image_base = image_base;
    game_image_size = image_size;
    step = fd4_step_find(game->file_step_name);
    if (step == NULL) {
        fwprintf(stderr, L"WARNING: [from-assets] %ls not found for %ls; Dantelion VFS disabled\n",
                 game->file_step_name, game->title);
        return false;
    }
    if (ml_hook_install(step, file_step_init_hooked, (void **)&old_file_step_init) != ML_HOOK_APPLIED) {
        fwprintf(stderr, L"WARNING: [from-assets] %ls hook failed for %ls\n",
                 game->file_step_name, game->title);
        return false;
    }
    file_step_hook_installed = true;
    file_step_hook_target = step;
    fwprintf(stderr, L"NOTE: [from-assets] %ls hook applied for %ls\n",
             game->file_step_name, game->title);
    return true;
}

static bool remove_asset_hook(void *target) {
    MH_STATUS status;
    if (target == NULL) return true;
    status = MH_RemoveHook(target);
    if (status == MH_OK || status == MH_ERROR_NOT_CREATED) return true;
    fwprintf(stderr, L"WARNING: [from-assets] failed to remove hook at %p: %d\n", target, status);
    return false;
}

static bool remove_asset_hooks(asset_hook_t *hooks, size_t count) {
    void *targets[64];
    if (count > sizeof(targets) / sizeof(targets[0])) return false;
    for (size_t i = 0; i < count; i++) targets[i] = hooks[i].target;
    return ml_hook_targets_remove_unique(targets, count, remove_asset_hook);
}

bool from_assets_uninstall(void) {
    bool result = true;
    if (!remove_asset_hook(file_step_hook_target)) result = false;
    if (!remove_asset_hook(make_ebl_object_hook_target)) result = false;
    if (!remove_asset_hook(mount_ebl_hook_target)) result = false;
    if (!remove_asset_hooks(set_path_hooks, set_path_hook_count)) result = false;
    if (!remove_asset_hooks(open_hooks, open_hook_count)) result = false;
    if (!result) return false;

    memset(open_hooks, 0, sizeof(open_hooks));
    memset(set_path_hooks, 0, sizeof(set_path_hooks));
    open_hook_count = 0;
    set_path_hook_count = 0;
    game_image_base = NULL;
    game_image_size = 0;
    device_manager = NULL;
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
    memset(logged_set_path_enter, 0, sizeof(logged_set_path_enter));
    memset(logged_set_path_return, 0, sizeof(logged_set_path_return));
    logged_ebl_fallback = 0;
    logged_mount_ebl = 0;
    file_operator_hook_attempted = 0;
    return true;
}
