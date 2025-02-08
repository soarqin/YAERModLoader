/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "common.h"

#include "modloader/config.h"
#include "modloader/mod.h"

#include "process/image.h"
#include "process/scanner.h"

#include <MinHook.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>

#include <stdint.h>

static void *image_base;
static size_t image_size;

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

void *__cdecl ak_file_location_resolver_open(const uint64_t p1, wchar_t *path, const AKOpenMode openMode, const uint64_t p4, const uint64_t p5, const uint64_t p6) {
    static const wchar_t *prefixes[3] = {
        L"sd/",
        L"sd/enus/",
        L"sd/ja/",
    };
    if (StrCmpNW(path, L"sd:/", 4) != 0)
        return old_ak_file_location_resolver_open(p1, path, openMode, p4, p5, p6);
    const wchar_t *replace = path + 4;
    const wchar_t *ext = PathFindExtensionW(replace);
    if (ext != NULL && StrCmpIW(ext, L".wem") == 0) {
        wchar_t new_path[MAX_PATH];
        _snwprintf(new_path, MAX_PATH, L"wem/%lc%lc/%ls", replace[0], replace[1], replace);
        const wchar_t *new_replace = mods_file_search(new_path);
        if (new_replace != NULL) {
            return old_ak_file_location_resolver_open(p1, (wchar_t*)new_replace, openMode, p4, p5, p6);
        }
    }
    for (int i = 0; i < 3; i++) {
        wchar_t new_path[MAX_PATH];
        _snwprintf(new_path, MAX_PATH, L"%ls%ls", prefixes[i], replace);
        const wchar_t *new_replace = mods_file_search(new_path);
        if (new_replace != NULL) {
            return old_ak_file_location_resolver_open(p1, (wchar_t*)new_replace, openMode, p4, p5, p6);
        }
    }
    return old_ak_file_location_resolver_open(p1, path, openMode, p4, p5, p6);
}

static bool hook_wwise_archive_position_resolver() {
    uint8_t *addr = sig_scan(image_base, image_size, "4C 89 74 24 28 48 8B 84 24 90 00 00 00 48 89 44 24 20 4C 8B CE 45 8B C4 49 8B D7 48 8B CD E8");
    if (!addr) {
        return false;
    }
    addr += *(int32_t*)(addr + 31) + 35;
    while (*addr == 0xE9) {
        addr += *(int32_t*)(addr + 1) + 5;
    }
    MH_CreateHook(addr, (void*)&ak_file_location_resolver_open, (void**)&old_ak_file_location_resolver_open);
    return true;
}

bool common_install() {
    if (config.enable_ime) {
        patch_ime_disable();
    }
    image_base = get_module_image_base(NULL, &image_size);
    /* Do not hook if no mod is added, to improve game performance during loading. */
    if (mods_count() <= 0) return true;
    if (!hook_wwise_archive_position_resolver()) return false;
    return true;
}

void common_uninstall() {
}
