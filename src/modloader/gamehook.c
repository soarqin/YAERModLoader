/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "gamehook.h"

#include "mod.h"
#include "steam/api.h"

#include <MinHook.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>

#include <wchar.h>

#include "processutil.h"

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
    if (wcsncmp(str, L"data", 4) == 0 && wcsncmp(str + 5, L":/", 2) == 0) {
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
    if (wcsncmp(path, L"sd:/", 4) != 0)
        return old_ak_file_location_resolver_open(p1, path, openMode, p4, p5, p6);
    const wchar_t *replace = path + 4;
    const wchar_t *ext = PathFindExtensionW(replace);
    if (ext != NULL && wcsicmp(ext, L".wem") == 0) {
        wchar_t new_path[MAX_PATH];
        _snwprintf(new_path, MAX_PATH, L"wem/%c%c/%s", replace[0], replace[1], replace);
        const wchar_t *new_replace = mods_file_search(new_path);
        if (new_replace != NULL) {
            return old_ak_file_location_resolver_open(p1, (wchar_t*)new_replace, openMode, p4, p5, p6);
        }
    }
    for (int i = 0; i < 3; i++) {
        wchar_t new_path[MAX_PATH];
        _snwprintf(new_path, MAX_PATH, L"%s%s", prefixes[i], replace);
        const wchar_t *new_replace = mods_file_search(new_path);
        if (new_replace != NULL) {
            return old_ak_file_location_resolver_open(p1, (wchar_t*)new_replace, openMode, p4, p5, p6);
        }
    }
    return old_ak_file_location_resolver_open(p1, path, openMode, p4, p5, p6);
}

static void *get_module_image_base(size_t *size) {
    const HMODULE hModule = GetModuleHandleW(NULL);
    if (hModule == NULL) {
        return NULL;
    }
    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)hModule;
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
        return NULL;
    }
    const PIMAGE_NT_HEADERS ntHeader = (const PIMAGE_NT_HEADERS64)((DWORD_PTR)dosHeader + dosHeader->e_lfanew);
    if (ntHeader->Signature != IMAGE_NT_SIGNATURE) {
        return NULL;
    }
    *size = ntHeader->OptionalHeader.SizeOfImage;
    return hModule;
}

static uint8_t *sig_scan(void *base, const size_t size, const uint8_t *pattern, const size_t pattern_size) {
    const size_t end = size - pattern_size;
    uint8_t *u8_base = base;
    for (size_t i = 0; i < end; i++) {
        if (memcmp(pattern, u8_base + i, pattern_size) != 0) continue;
        return u8_base + i;
    }
    return NULL;
}

static uint8_t *sig_scan_with_mask(void *base, const size_t size, const uint8_t *pattern, const uint8_t *mask, const size_t pattern_size) {
    const size_t end = size - pattern_size;
    uint8_t *u8_curr = base;
    uint8_t *u8_end = u8_curr + end;
    while (u8_curr < u8_end) {
        for (size_t i = 0; i < pattern_size; i++) {
            switch (mask[i]) {
                case 0:
                    continue;
                case 0xFF:
                    if (pattern[i] != u8_curr[i])
                        goto next;
                    break;
                default:
                    if ((pattern[i] & mask[i]) != (u8_curr[i] & mask[i]))
                        goto next;
                    break;
            }
        }
        return u8_curr;
    next:
        u8_curr++;
    }
    return NULL;
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
    static const uint8_t cs_menu_man_aob[] = {
        0x48, 0x8b, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8b, 0x49, 0x08, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8b, 0xd0, 0x48, 0x8b, 0xce, 0xe8
    };
    static const uint8_t cs_menu_man_mask[] = {
        0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
    };
    const int strat = (int)(intptr_t)arg;
    const uint64_t game_version = get_game_version();
    uintptr_t offset;
    uint8_t *addr = sig_scan_with_mask(image_base, image_size, cs_menu_man_aob, cs_menu_man_mask, sizeof(cs_menu_man_aob));
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
    static const uint8_t game_data_man_aob[] = {0x48, 0x8b, 0x05, 0x00, 0x00, 0x00, 0x00, 0x48, 0x85, 0xc0, 0x74, 0x05, 0x48, 0x8b, 0x40, 0x58, 0xc3, 0xc3};
    static const uint8_t game_data_man_mask[] = {0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    uint8_t *addr = sig_scan_with_mask(image_base, image_size, game_data_man_aob, game_data_man_mask, sizeof(game_data_man_aob));
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
extern bool skip_intro;
extern bool remove_chromatic_aberration;
extern bool remove_vignette;

static bool patch_eldenring_skip_intro() {
    static const uint8_t skip_intro_aob[] = {
        0x74, 0x53, 0x48, 0x8b, 0x05, 0x00, 0x00, 0x00, 0x00, 0x48, 0x85, 0xc0, 0x75, 0x2e, 0x48, 0x8d, 0x0d, 0x00, 0x00, 0x00, 0x00, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x4c, 0x8b, 0xc8
    };
    static const uint8_t skip_intro_mask[] = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff
    };
    static const uint8_t new_bytes[] = { 0x90, 0x90 };
    uint8_t *addr = sig_scan_with_mask(image_base, image_size, skip_intro_aob, skip_intro_mask, sizeof(skip_intro_aob));
    if (!addr) return false;
    DWORD old_protect;
    VirtualProtect(addr, 2, PAGE_EXECUTE_READWRITE, &old_protect);
    memcpy(addr, new_bytes, 2);
    VirtualProtect(addr, 2, old_protect, &old_protect);
    return true;
}

static bool patch_eldenring_remove_chromatic_aberratio() {
    static const uint8_t remove_chromatic_aberration_aob[] = {
        0x0f, 0x11, 0x00, 0x60, 0x00, 0x8d, 0x00, 0x80, 0x00, 0x00, 0x00, 0x0f, 0x10, 0x00, 0xa0, 0x00, 0x00, 0x00, 0x0f, 0x11, 0x00, 0xf0, 0x00, 0x8d, 0x00, 0xb0, 0x00, 0x00,
        0x00, 0x0f, 0x10, 0x00, 0x0f, 0x11, 0x00, 0x0f, 0x10, 0x00, 0x10
    };
    static const uint8_t remove_chromatic_aberration_mask[] = {
        0xff, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff
    };
    static const uint8_t new_bytes[] = { 0x66, 0x0f, 0xef, 0xc9 };
    uint8_t *addr = sig_scan_with_mask(image_base, image_size, remove_chromatic_aberration_aob, remove_chromatic_aberration_mask, sizeof(remove_chromatic_aberration_aob));
    if (!addr) return false;
    DWORD old_protect;
    VirtualProtect(addr + 0x2F, 4, PAGE_EXECUTE_READWRITE, &old_protect);
    memcpy(addr + 0x2F, new_bytes, 4);
    VirtualProtect(addr + 0x2F, 4, old_protect, &old_protect);
    return true;
}

static bool patch_eldenring_remove_vignette() {
    static const uint8_t remove_vignette_aob[] = {
        0xf3, 0x0f, 0x10, 0x00, 0x50, 0xf3, 0x0f, 0x59, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe8, 0x00, 0x00, 0x00, 0x00, 0xf3, 0x00, 0x0f, 0x5c, 0x00, 0xf3, 0x00, 0x0f, 0x59, 0x00,
        0x00, 0x8d, 0x00, 0x00, 0xa0, 0x00, 0x00, 0x00
    };
    static const uint8_t remove_vignette_mask[] = {
        0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0x00,
        0x00, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff
    };
    static const uint8_t new_bytes[] = { 0xf3, 0x0f, 0x5c, 0xc0, 0x90 };
    uint8_t *addr = sig_scan_with_mask(image_base, image_size, remove_vignette_aob, remove_vignette_mask, sizeof(remove_vignette_aob));
    if (!addr) return false;
    DWORD old_protect;
    VirtualProtect(addr + 0x17, 5, PAGE_EXECUTE_READWRITE, &old_protect);
    memcpy(addr + 0x17, new_bytes, 5);
    VirtualProtect(addr + 0x17, 5, old_protect, &old_protect);
    return true;
}

static bool hook_eldenring_archive_position_resolver() {
    static const uint8_t map_archive_aob[] = {
        0x48, 0x83, 0x7b, 0x20, 0x08, 0x48, 0x8d, 0x4b, 0x08, 0x72, 0x03, 0x48, 0x8b, 0x09, 0x4c, 0x8b, 0x4b, 0x18, 0x41, 0xb8, 0x05, 0x00,
        0x00, 0x00, 0x4d, 0x3b, 0xc8
    };
    uint8_t *addr = sig_scan(image_base, image_size, map_archive_aob, sizeof(map_archive_aob));
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
    static const uint8_t ak_file_location_resolver_aob[] = {
        0x4c, 0x89, 0x74, 0x24, 0x28, 0x48, 0x8b, 0x84, 0x24, 0x90, 0x00, 0x00, 0x00, 0x48, 0x89, 0x44, 0x24, 0x20, 0x4c, 0x8b,
        0xce, 0x45, 0x8b, 0xc4, 0x49, 0x8b, 0xd7, 0x48, 0x8b, 0xcd, 0xe8
    };
    uint8_t *addr = sig_scan(image_base, image_size, ak_file_location_resolver_aob, sizeof(ak_file_location_resolver_aob));
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
    MH_Initialize();
    if (cpu_affinity_strategy > 0) {
        set_process_cpu_affinity_thread_handle = CreateThread(NULL, 0, set_process_cpu_affinity_thread, (LPVOID)(intptr_t)cpu_affinity_strategy, 0, NULL);
    }
    if (reset_achievements_on_new_game) {
        reset_achievements_on_new_game_thread_handle = CreateThread(NULL, 0, reset_achievements_on_new_game_thread, NULL, 0, NULL);
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
