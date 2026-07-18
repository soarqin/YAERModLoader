/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "common.h"
#include "common/allocator.h"
#include "modloader/hook.h"
#include "wwise_path.h"

#include "modloader/config.h"
#include "log.h"
#include "modloader/mod.h"
#include "modloader/vfs.h"

#include "process/rtti.h"
#include "process/pe.h"

#include <MinHook.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>

#include <stdint.h>

BOOL WINAPI ImmDisableIME_hooked(DWORD unused) {
    (void)unused;
    return TRUE;
}

static void *ime_hook_target;

static bool patch_ime_disable() {
    void *func = NULL;
    MH_STATUS status = MH_CreateHookApiEx(L"imm32", "ImmDisableIME", ImmDisableIME_hooked, NULL, &func);
    if (status != MH_OK || func == NULL) return false;
    status = MH_EnableHook(func);
    if (status != MH_OK) {
        MH_RemoveHook(func);
        return false;
    }
    ime_hook_target = func;
    return true;
}

typedef enum ak_open_mode_e {
    READ            = 0,
    WRITE           = 1,
    WRITE_OVERWRITE = 2,
    READ_WRITE      = 3,

    // Custom mode specific to From Software's implementation
    READ_EBL = 10,
} ak_open_mode_t;

_Static_assert(READ == 0, "AkOpenMode READ value");
_Static_assert(WRITE == 1, "AkOpenMode WRITE value");
_Static_assert(WRITE_OVERWRITE == 2, "AkOpenMode WRITE_OVERWRITE value");
_Static_assert(READ_WRITE == 3, "AkOpenMode READ_WRITE value");
_Static_assert(READ_EBL == 10, "AkOpenMode READ_EBL value");

typedef void *(__cdecl *ak_file_location_resolver_open_t)(uint64_t p1, wchar_t *path, ak_open_mode_t openMode, uint64_t p4, uint64_t p5, uint64_t p6);
static ak_file_location_resolver_open_t old_ak_file_location_resolver_open = NULL;
static void *wwise_hook_target;

typedef struct dlmow_io_hook_blocking_vtable_s {
    void *dtor;
    void *open_by_id;
    ak_file_location_resolver_open_t open_by_name;
} dlmow_io_hook_blocking_vtable_t;

void *__cdecl ak_file_location_resolver_open(const uint64_t p1, wchar_t *path, const ak_open_mode_t openMode, const uint64_t p4, const uint64_t p5, const uint64_t p6) {
    static const wchar_t *prefixes[3] = {
        L"sd/",
        L"sd/enus/",
        L"sd/ja/",
    };
    const wchar_t *replace = wwise_strip_prefixes(path);
    if (replace == NULL)
        return old_ak_file_location_resolver_open(p1, path, openMode, p4, p5, p6);
    const wchar_t *ext = PathFindExtensionW(replace);
    if (ext != NULL && StrCmpIW(ext, L".wem") == 0) {
        wchar_t *direct_path;
        wchar_t *nested_path;
        if (wwise_wem_candidates(replace, &direct_path, &nested_path)) {
            const wchar_t *new_replace = NULL;
            for (int i = 0; i < 3 && new_replace == NULL; i++) {
                wchar_t *candidate = wwise_join_path(prefixes[i], direct_path);
                if (candidate != NULL) {
                    new_replace = vfs_lookup_domain(candidate, VFS_LOOKUP_WWISE);
                    yaer_mem_free(candidate);
                }
            }
            for (int i = 0; i < 3 && new_replace == NULL; i++) {
                wchar_t *candidate = wwise_join_path(prefixes[i], nested_path);
                if (candidate != NULL) {
                    new_replace = vfs_lookup_domain(candidate, VFS_LOOKUP_WWISE);
                    yaer_mem_free(candidate);
                }
            }
            yaer_mem_free(direct_path);
            yaer_mem_free(nested_path);
            if (new_replace != NULL) {
            /* FromSoftware's READ_EBL (9) mode yields an EBLFileOperator that
             * only reads from BDT archives. An override file lives on disk, so
             * we must switch back to READ (0) to get a FileOperator that reads
             * the absolute disk path we pass in. See ModEngine2's
             * wwise_file_overrides.cpp for the same rationale. */
                return old_ak_file_location_resolver_open(p1, (wchar_t*)new_replace, READ, p4, p5, p6);
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        wchar_t *new_path = wwise_join_path(prefixes[i], replace);
        if (new_path == NULL) continue;
        const wchar_t *new_replace = vfs_lookup_domain(new_path, VFS_LOOKUP_WWISE);
        yaer_mem_free(new_path);
        if (new_replace != NULL) {
            return old_ak_file_location_resolver_open(p1, (wchar_t*)new_replace, READ, p4, p5, p6);
        }
    }
    return old_ak_file_location_resolver_open(p1, path, openMode, p4, p5, p6);
}

static bool hook_wwise_archive_position_resolver() {
    void **vtable = rtti_find_vtable("DLMOW::IOHookBlocking");
    ak_file_location_resolver_open_t open_by_name = vtable == NULL ? NULL :
        ((dlmow_io_hook_blocking_vtable_t *)vtable)->open_by_name;
    if (open_by_name == NULL) {
        void *image = GetModuleHandleW(NULL);
        const IMAGE_SECTION_HEADER *text = pe_section_by_name(image, ".text");
        size_t text_size = 0;
        uint8_t *text_base = pe_section_data(image, text, &text_size);
        size_t call_offset = wwise_find_open_call(text_base, text_size);
        if (call_offset != SIZE_MAX) {
            int32_t displacement;
            memcpy(&displacement, text_base + call_offset + 1, sizeof(displacement));
            open_by_name = (ak_file_location_resolver_open_t)(text_base + call_offset + 5 + displacement);
            ML_LOG_INFO(L"common", L"Wwise resolver found by signature fallback at %p", open_by_name);
        }
    }
    if (open_by_name == NULL) {
        ML_LOG_WARN(L"common", L"Wwise resolver SIGNATURE_NOT_FOUND: RTTI and fallback scan found no target");
        return false;
    }
    ml_hook_result_t result = ml_hook_install((void *)open_by_name, (void *)&ak_file_location_resolver_open, (void **)&old_ak_file_location_resolver_open);
    if (result != ML_HOOK_APPLIED) {
        ML_LOG_WARN(L"common", L"Wwise archive resolver hook %hs", ml_hook_result_name(result));
        return false;
    }
    wwise_hook_target = (void *)open_by_name;
    return true;
}

bool common_install() {
    bool ime_applied = common_install_ime();
    bool wwise_applied = common_install_wwise();
    if (!ime_applied) ML_LOG_WARN(L"common", L"IME capability HOOK_FAILED; continuing with other capabilities");
    return wwise_applied;
}

bool common_install_ime() {
    if (config.enable_ime) {
        return ime_hook_target != NULL || patch_ime_disable();
    }
    return true;
}

bool common_wwise_requested() {
    return vfs_has_wwise_entries();
}

bool common_install_wwise() {
    if (!common_wwise_requested()) return true;
    if (wwise_hook_target != NULL) return true;
    if (!hook_wwise_archive_position_resolver()) return false;
    return true;
}

void common_uninstall() {
    void **targets[2] = { &wwise_hook_target, &ime_hook_target };
    for (size_t i = 0; i < 2; i++) {
        void *target = *targets[i];
        if (target == NULL) continue;
        MH_STATUS status = MH_RemoveHook(target);
        if (status == MH_OK || status == MH_ERROR_NOT_CREATED) {
            *targets[i] = NULL;
        } else {
            ML_LOG_WARN(L"common", L"failed to remove hook at %p: %d", target, status);
        }
    }
    if (wwise_hook_target == NULL) old_ak_file_location_resolver_open = NULL;
}
