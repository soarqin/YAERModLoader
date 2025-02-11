/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "eldenring.h"

#include "modloader/config.h"
#include "modloader/mod.h"

#include "process/image.h"
#include "process/scanner.h"
#include "process/util.h"

#include "steam/api.h"

#include "eldenring/wstring.h"
#include "eldenring/param.h"
#include "eldenring/defs/menu_common_param.h"

#include <MinHook.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>

#include <stdint.h>

static HANDLE async_operations_thread_handle = NULL;
static bool game_running = false;
static HANDLE reset_achievements_on_new_game_thread_handle = NULL;
static void *image_base;
static size_t image_size;

/*
static uint64_t get_game_version() {
    wchar_t exepath[MAX_PATH];
    GetModuleFileNameW(NULL, exepath, MAX_PATH);
    DWORD len = GetFileVersionInfoSizeW(exepath, NULL);
    if (len == 0) return 0LL;
    BYTE *pVersionResource = malloc(len);
    if (!GetFileVersionInfoW(exepath, 0, len, pVersionResource)) {
        free(pVersionResource);
        return 0LL;
    }
    UINT uLen;
    VS_FIXEDFILEINFO *ptFixedFileInfo;
    if (VerQueryValueW(pVersionResource, L"\\", (LPVOID*)&ptFixedFileInfo, &uLen) && uLen > 0) {
        free(pVersionResource);
        return (uint64_t)ptFixedFileInfo->dwFileVersionMS << 32 | (uint64_t)ptFixedFileInfo->dwFileVersionLS;
    }
    free(pVersionResource);
    return 0LL;
}
*/

DWORD WINAPI async_operation_thread(LPVOID arg) {
    param_load_table();

    if (config.cpu_affinity_strategy != 0) set_process_cpu_affinity_strategy(config.cpu_affinity_strategy);
    if (config.world_map_cursor_speed != 1.0f) {
        const param_table_t *t = param_find_table(L"MenuCommonParam");
        param_table_iterate_begin(t, menu_common_param_t, param)
            param->worldMapCursorSpeed *= config.world_map_cursor_speed;
        param_table_iterate_end();
    }
    return 0;
}

typedef void *(__cdecl *map_archive_path_t)(wstring_impl_t *path, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5, uint64_t p6);
typedef HANDLE (WINAPI *CreateFileW_t)(LPCWSTR lpFileName,
                                       DWORD dwDesiredAccess,
                                       DWORD dwShareMode,
                                       LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                                       DWORD dwCreationDisposition,
                                       DWORD dwFlagsAndAttributes,
                                       HANDLE hTemplateFile);


static map_archive_path_t old_map_archive_path = NULL;
static CreateFileW_t old_CreateFileW = NULL;

void *__cdecl map_archive_path(wstring_impl_t *path, const uint64_t p2, const uint64_t p3, const uint64_t p4, const uint64_t p5, const uint64_t p6) {
    void *res = old_map_archive_path(path, p2, p3, p4, p5, p6);
    if (path == NULL) return res;
    wchar_t *str = wstring_impl_str_mutable(path);
    if (StrCmpNW(str, L"data", 4) == 0 && StrCmpNW(str + 5, L":/", 2) == 0) {
        const wchar_t *replace = mods_file_search(str + 6);
        if (replace == NULL) return res;
        memcpy(str, L"./////", 6 * sizeof(wchar_t));
    }
    return res;
}

HANDLE WINAPI CreateFile_hooked(const LPCWSTR lpFileName,
                                const DWORD dwDesiredAccess,
                                const DWORD dwShareMode,
                                LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                                const DWORD dwCreationDisposition,
                                const DWORD dwFlagsAndAttributes,
                                HANDLE hTemplateFile) {
    const wchar_t *replace = mods_file_search_prefixed(lpFileName);
    return old_CreateFileW(replace == NULL ? lpFileName : replace, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

DWORD WINAPI reset_achievements_on_new_game_thread(LPVOID arg) {
    uint8_t *addr = sig_scan(image_base, image_size, "48 8B 05 ?? ?? ?? ?? 48 85 C0 74 05 48 8B 40 58 C3 C3");
    if (!addr) return 1;
    addr += *(int32_t*)(addr + 3) + 7;
    HANDLE process = GetCurrentProcess();
    uint32_t last_igt = UINT32_MAX;
    while (game_running) {
        uint8_t *addr2;
        if (ReadProcessMemory(process, addr, &addr2, sizeof(uint8_t*), NULL) && addr2) {
            uint32_t igt;
            if (ReadProcessMemory(process, addr2 + 0xA0, &igt, sizeof(uint32_t), NULL) && igt > 0) {
                if (igt < last_igt && igt < 5000) {
                    isteam_userstats *ustats = steam_userstats();
                    if (ustats) {
                        isteam_userstats_reset_all_stats(ustats, true);
                        isteam_userstats_store_stats(ustats);
                    }
                }
                last_igt = igt;
            }
        }
        Sleep(1000);
    }
    return 0;
}

static bool patch_eldenring_skip_intro() {
    static const uint8_t new_bytes[] = { 0x90, 0x90 };
    uint8_t *addr = sig_scan(image_base, image_size, "74 53 48 8B 05 ?? ?? ?? ?? 48 85 C0 75 2E 48 8D 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 4C 8B C8");
    if (!addr) return false;
    DWORD old_protect;
    VirtualProtect(addr, 2, PAGE_EXECUTE_READWRITE, &old_protect);
    memcpy(addr, new_bytes, 2);
    VirtualProtect(addr, 2, old_protect, &old_protect);
    return true;
}

static bool patch_eldenring_remove_chromatic_aberratio() {
    static const uint8_t new_bytes[] = { 0x66, 0x0f, 0xef, 0xc9 };
    uint8_t *addr = sig_scan(image_base, image_size, "0F 11 ?? 60 ?? 8D ?? 80 00 00 00 0F 10 ?? A0 00 00 00 0F 11 ?? F0 ?? 8D ?? B0 00 00 00 0F 10 ?? 0F 11 ?? 0F 10 ?? 10");
    if (!addr) return false;
    DWORD old_protect;
    VirtualProtect(addr + 0x2F, 4, PAGE_EXECUTE_READWRITE, &old_protect);
    memcpy(addr + 0x2F, new_bytes, 4);
    VirtualProtect(addr + 0x2F, 4, old_protect, &old_protect);
    return true;
}

static bool patch_eldenring_remove_vignette() {
    static const uint8_t new_bytes[] = { 0xf3, 0x0f, 0x5c, 0xc0, 0x90 };
    uint8_t *addr = sig_scan(image_base, image_size, "F3 0F 10 ?? 50 F3 0F 59 ?? ?? ?? ?? ?? E8 ?? ?? ?? ?? F3 ?? 0F 5C ?? F3 ?? 0F 59 ?? ?? 8D ?? ?? A0 00 00 00");
    if (!addr) return false;
    DWORD old_protect;
    VirtualProtect(addr + 0x17, 5, PAGE_EXECUTE_READWRITE, &old_protect);
    memcpy(addr + 0x17, new_bytes, 5);
    VirtualProtect(addr + 0x17, 5, old_protect, &old_protect);
    return true;
}

static bool hook_eldenring_archive_position_resolver() {
    uint8_t *addr = sig_scan(image_base, image_size, "48 83 7B 20 08 48 8D 4B 08 72 03 48 8B 09 4C 8B 4B 18 41 B8 05 00 00 00 4D 3B C8");
    if (!addr) {
        return false;
    }
    addr += *(int32_t*)(addr - 4);
    while (*addr == 0xE9) {
        addr += *(int32_t*)(addr + 1) + 5;
    }
    MH_CreateHook(addr, (void*)&map_archive_path, (void**)&old_map_archive_path);

    MH_CreateHook(CreateFileW, (void*)&CreateFile_hooked, (void**)&old_CreateFileW);
    return true;
}

bool eldenring_install() {
    game_running = true;

    if (config.cpu_affinity_strategy > 0 || config.world_map_cursor_speed != 1.0f) {
        async_operations_thread_handle = CreateThread(NULL, 0, async_operation_thread, NULL, 0, NULL);
    }
    if (config.reset_achievements_on_new_game) {
        reset_achievements_on_new_game_thread_handle = CreateThread(NULL, 0, reset_achievements_on_new_game_thread, NULL, 0, NULL);
    }
    image_base = get_module_image_base(NULL, &image_size);

    if (config.skip_intro) {
        patch_eldenring_skip_intro();
    }

    if (config.remove_chromatic_aberration) {
        patch_eldenring_remove_chromatic_aberratio();
    }

    if (config.remove_vignette) {
        patch_eldenring_remove_vignette();
    }

    /* Do not hook if no mod is added, to improve game performance during loading. */
    if (mods_count() <= 0) return true;
    if (!hook_eldenring_archive_position_resolver()) return false;
    return true;
}

void eldenring_uninstall() {
    game_running = false;

    if (async_operations_thread_handle && WaitForSingleObject(async_operations_thread_handle, 1000) == WAIT_TIMEOUT)
        TerminateThread(async_operations_thread_handle, 0);
    if (reset_achievements_on_new_game_thread_handle && WaitForSingleObject(reset_achievements_on_new_game_thread_handle, 1000) == WAIT_TIMEOUT)
        TerminateThread(reset_achievements_on_new_game_thread_handle, 0);
    param_unload();
}
