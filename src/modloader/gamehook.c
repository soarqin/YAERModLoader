/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "gamehook.h"

#include "mod.h"
#include "steam/api.h"
#include "process/image.h"
#include "process/scanner.h"
#include "process/util.h"

#include <MinHook.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>

#include <wchar.h>

typedef struct {
    void *unk;
    wchar_t *string;
    void *unk2;
    uint64_t length;
    uint64_t capacity;
} wstring_impl_t;

wchar_t *wstring_impl_str(wstring_impl_t *str) {
    if (sizeof(wchar_t) * str->capacity >= 15) {
        return str->string;
    }
    return (wchar_t*)&str->string;
}

typedef enum {
    READ            = 0,
    WRITE           = 1,
    WRITE_OVERWRITE = 2,
    READ_WRITE      = 3,

    // Custom mode specific to From Software's implementation
    READ_EBL = 9,
} AKOpenMode;

BOOL WINAPI ImmDisableIME_hooked(DWORD unused) {
    (void)unused;
    return TRUE;
}

typedef void *(__cdecl *map_archive_path_t)(wstring_impl_t *path, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5, uint64_t p6);
typedef HANDLE (WINAPI *CreateFileW_t)(LPCWSTR lpFileName,
                                       DWORD dwDesiredAccess,
                                       DWORD dwShareMode,
                                       LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                                       DWORD dwCreationDisposition,
                                       DWORD dwFlagsAndAttributes,
                                       HANDLE hTemplateFile);
typedef void *(__cdecl *ak_file_location_resolver_open_t)(uint64_t p1, wchar_t *path, AKOpenMode openMode, uint64_t p4, uint64_t p5, uint64_t p6);


static map_archive_path_t old_map_archive_path = NULL;
static CreateFileW_t old_CreateFileW = NULL;
static ak_file_location_resolver_open_t old_ak_file_location_resolver_open = NULL;

void *__cdecl map_archive_path(wstring_impl_t *path, const uint64_t p2, const uint64_t p3, const uint64_t p4, const uint64_t p5, const uint64_t p6) {
    void *res = old_map_archive_path(path, p2, p3, p4, p5, p6);
    if (path == NULL) return res;
    wchar_t *str = wstring_impl_str(path);
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

const wchar_t *prefixes[3] = {
    L"sd/",
    L"sd/enus/",
    L"sd/ja/",
};

void *__cdecl ak_file_location_resolver_open(const uint64_t p1, wchar_t *path, const AKOpenMode openMode, const uint64_t p4, const uint64_t p5, const uint64_t p6) {
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

static bool game_running = false;
static HANDLE set_process_cpu_affinity_thread_handle = NULL;
static HANDLE reset_achievements_on_new_game_thread_handle = NULL;
static void *image_base;
static size_t image_size;

DWORD WINAPI set_process_cpu_affinity_thread(LPVOID arg) {
    const int strat = (int)(intptr_t)arg;
    const uint64_t game_version = get_game_version();
    uintptr_t offset;
    uint8_t *addr = sig_scan(image_base, image_size, "48 8B 0D ?? ?? ?? ?? 48 8B 49 08 E8 ?? ?? ?? ?? 48 8B D0 48 8B CE E8");
    if (!addr) { return 1; }
    addr += *(int32_t*)(addr + 3) + 7;
    if (game_version < 0x0001000300000000ULL) {
        offset = 0x718 + 0x14;
    } else if (game_version < 0x0002000200000000ULL) {
        offset = 0x728 + 0x14;
    } else {
        offset = 0x730 + 0x14;
    }
    HANDLE process = GetCurrentProcess();
    while (game_running) {
        uint8_t *addr2;
        if (ReadProcessMemory(process, addr, &addr2, sizeof(uint8_t*), NULL) && addr2) {
            float on_menu_time;
            if (ReadProcessMemory(process, addr2 + offset, &on_menu_time, sizeof(float), NULL) && on_menu_time > 0.0f) {
                set_process_cpu_affinity_strategy(strat);
                return 0;
            }
        }
        Sleep(500);
    }
    return 0;
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

extern int cpu_affinity_strategy;
extern bool reset_achievements_on_new_game;
extern bool enable_ime;
extern bool skip_intro;
extern bool remove_chromatic_aberration;
extern bool remove_vignette;

static bool patch_ime_disable() {
    void *func = NULL;
    MH_CreateHookApiEx(L"imm32", "ImmDisableIME", ImmDisableIME_hooked, NULL, &func);
    if (!func) return false;
    MH_EnableHook(func);
    return true;
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

bool gamehook_install() {
    game_running = true;

    steamapi_init();
    if (cpu_affinity_strategy > 0) {
        set_process_cpu_affinity_thread_handle = CreateThread(NULL, 0, set_process_cpu_affinity_thread, (LPVOID)(intptr_t)cpu_affinity_strategy, 0, NULL);
    }
    if (reset_achievements_on_new_game) {
        reset_achievements_on_new_game_thread_handle = CreateThread(NULL, 0, reset_achievements_on_new_game_thread, NULL, 0, NULL);
    }
    if (enable_ime) {
        patch_ime_disable();
    }

    image_base = get_module_image_base(&image_size);

    if (skip_intro) {
        patch_eldenring_skip_intro();
    }

    if (remove_chromatic_aberration) {
        patch_eldenring_remove_chromatic_aberratio();
    }

    if (remove_vignette) {
        patch_eldenring_remove_vignette();
    }

    /* Do not hook if no mod is added, to improve game performance during loading. */
    if (mods_count() <= 0) return true;

    if (!hook_eldenring_archive_position_resolver()) return false;

    hook_wwise_archive_position_resolver();
    MH_EnableHook(MH_ALL_HOOKS);
    return true;
}

void gamehook_uninstall() {
    game_running = false;
    if (set_process_cpu_affinity_thread_handle && WaitForSingleObject(set_process_cpu_affinity_thread_handle, 1000) == WAIT_TIMEOUT)
        TerminateThread(set_process_cpu_affinity_thread_handle, 0);
    if (reset_achievements_on_new_game_thread_handle && WaitForSingleObject(reset_achievements_on_new_game_thread_handle, 1000) == WAIT_TIMEOUT)
        TerminateThread(reset_achievements_on_new_game_thread_handle, 0);

    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
    steamapi_uninit();
}
