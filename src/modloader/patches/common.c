/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "common.h"

#include "modloader/config.h"
#include "modloader/mod.h"

#include "process/rtti.h"

#include <MinHook.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>

#include <stdint.h>

BOOL WINAPI ImmDisableIME_hooked(DWORD unused) {
    (void)unused;
    return TRUE;
}

static bool patch_ime_disable() {
    void *func = NULL;
    MH_CreateHookApiEx(L"imm32", "ImmDisableIME", ImmDisableIME_hooked, NULL, &func);
    if (!func) return false;
    MH_EnableHook(func);
    return true;
}

typedef enum {
    READ            = 0,
    WRITE           = 1,
    WRITE_OVERWRITE = 2,
    READ_WRITE      = 3,

    // Custom mode specific to From Software's implementation
    READ_EBL = 9,
} AKOpenMode;

typedef void *(__cdecl *ak_file_location_resolver_open_t)(uint64_t p1, wchar_t *path, AKOpenMode openMode, uint64_t p4, uint64_t p5, uint64_t p6);
static ak_file_location_resolver_open_t old_ak_file_location_resolver_open = NULL;

typedef struct dlmow_io_hook_blocking_vtable_s {
    void *dtor;
    void *open_by_id;
    ak_file_location_resolver_open_t open_by_name;
} dlmow_io_hook_blocking_vtable_t;

void *__cdecl ak_file_location_resolver_open(const uint64_t p1, wchar_t *path, const AKOpenMode openMode, const uint64_t p4, const uint64_t p5, const uint64_t p6) {
    static const wchar_t *prefixes[3] = {
        L"sd/",
        L"sd/enus/",
        L"sd/ja/",
    };
    if (path == NULL || StrCmpNW(path, L"sd:/", 4) != 0)
        return old_ak_file_location_resolver_open(p1, path, openMode, p4, p5, p6);
    const wchar_t *replace = path + 4;
    const wchar_t *ext = PathFindExtensionW(replace);
    if (ext != NULL && StrCmpIW(ext, L".wem") == 0) {
        wchar_t new_path[MAX_PATH];
        _snwprintf(new_path, MAX_PATH, L"wem/%lc%lc/%ls", replace[0], replace[1], replace);
        new_path[MAX_PATH - 1] = L'\0';
        const wchar_t *new_replace = mods_file_search(new_path);
        if (new_replace != NULL) {
            /* FromSoftware's READ_EBL (9) mode yields an EBLFileOperator that
             * only reads from BDT archives. An override file lives on disk, so
             * we must switch back to READ (0) to get a FileOperator that reads
             * the absolute disk path we pass in. See ModEngine2's
             * wwise_file_overrides.cpp for the same rationale. */
            return old_ak_file_location_resolver_open(p1, (wchar_t*)new_replace, READ, p4, p5, p6);
        }
    }
    for (int i = 0; i < 3; i++) {
        wchar_t new_path[MAX_PATH];
        _snwprintf(new_path, MAX_PATH, L"%ls%ls", prefixes[i], replace);
        new_path[MAX_PATH - 1] = L'\0';
        const wchar_t *new_replace = mods_file_search(new_path);
        if (new_replace != NULL) {
            return old_ak_file_location_resolver_open(p1, (wchar_t*)new_replace, READ, p4, p5, p6);
        }
    }
    return old_ak_file_location_resolver_open(p1, path, openMode, p4, p5, p6);
}

static bool hook_wwise_archive_position_resolver() {
    void **vtable = rtti_find_vtable("DLMOW::IOHookBlocking");
    if (vtable == NULL) {
        return false;
    }
    ak_file_location_resolver_open_t open_by_name = ((dlmow_io_hook_blocking_vtable_t *)vtable)->open_by_name;
    if (open_by_name == NULL) {
        return false;
    }
    MH_CreateHook((void *)open_by_name, (void*)&ak_file_location_resolver_open, (void**)&old_ak_file_location_resolver_open);
    return true;
}

bool common_install() {
    if (config.enable_ime) {
        patch_ime_disable();
    }
    /* Do not hook if no mod is added, to improve game performance during loading. */
    if (mods_count() <= 0) return true;
    if (!hook_wwise_archive_position_resolver()) return false;
    return true;
}

void common_uninstall() {
}
