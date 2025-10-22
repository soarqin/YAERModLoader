/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "eldenring.h"

#include "modloader/config.h"
#include "modloader/mod.h"
#include "modloader/extdll.h"

#include "process/image.h"
#include "process/scanner.h"
#include "process/util.h"

#include "steam/api.h"

#include "eldenring/wstring.h"
#include "eldenring/param_internal.h"
#include "eldenring/pointers.h"
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

static wchar_t replaced_save_filename[64] = L"";
static wchar_t replaced_save_filename_bak[64] = L"";
static wchar_t replaced_seamless_coop_save_filename[64] = L"";
static wchar_t replaced_seamless_coop_save_filename_bak[64] = L"";

#define ORIGINAL_SAVE_FILENAME L"ER0000.sl2"
#define ORIGINAL_SAVE_FILENAME_LEN 10
#define ORIGIANL_SAVE_FILENAME_BAK L"ER0000.sl2.bak"
#define ORIGIANL_SAVE_FILENAME_BAK_LEN 14
#define SEAMLESS_COOP_SAVE_FILENAME L"ER0000.co2"
#define SEAMLESS_COOP_SAVE_FILENAME_LEN 10
#define SEAMLESS_COOP_SAVE_FILENAME_BAK L"ER0000.co2.bak"
#define SEAMLESS_COOP_SAVE_FILENAME_BAK_LEN 14

static bool str_ends_with(const wchar_t *str, size_t str_len, const wchar_t *suffix, size_t suffix_len) {
    if (suffix_len > str_len) return false;
    return StrCmpNIW(str + str_len - suffix_len, suffix, suffix_len) == 0;
}

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
    er_pointers_init(INIT_CS_REGULATION_MANAGER);
    er_param_load_table();
    extdlls_on_param_initialized();

    if (config.cpu_affinity_strategy != 0) set_process_cpu_affinity_strategy(config.cpu_affinity_strategy);
    if (config.world_map_cursor_speed != 1.0f) {
        const er_param_table_t *t = er_param_find_table(L"MenuCommonParam");
        er_param_table_iterate_begin(t, er_menu_common_param_t, param)
            param->worldMapCursorSpeed *= config.world_map_cursor_speed;
        er_param_table_iterate_end();
    }
    return 0;
}

typedef void *(__cdecl *map_archive_path_t)(er_wstring_impl_t *path, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5, uint64_t p6);
typedef HANDLE (WINAPI *CreateFileW_t)(LPCWSTR lpFileName,
                                       DWORD dwDesiredAccess,
                                       DWORD dwShareMode,
                                       LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                                       DWORD dwCreationDisposition,
                                       DWORD dwFlagsAndAttributes,
                                       HANDLE hTemplateFile);
typedef BOOL (WINAPI *CopyFileW_t)(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, BOOL bFailIfExists);

static map_archive_path_t old_map_archive_path = NULL;
static CreateFileW_t old_CreateFileW = NULL;
static CopyFileW_t old_CopyFileW = NULL;

void *__cdecl map_archive_path(er_wstring_impl_t *path, const uint64_t p2, const uint64_t p3, const uint64_t p4, const uint64_t p5, const uint64_t p6) {
    void *res = old_map_archive_path(path, p2, p3, p4, p5, p6);
    if (path == NULL) return res;
    wchar_t *str = er_wstring_impl_str_mutable(path);
    if (StrCmpNW(str, L"data", 4) == 0 && StrCmpNW(str + 5, L":/", 2) == 0) {
        const wchar_t *replace = mods_file_search(str + 6);
        if (replace == NULL) return res;
        memcpy(str, L"./////", 6 * sizeof(wchar_t));
    }
    return res;
}

wchar_t *check_replace_file(const wchar_t *lpFileName) {
    bool has_replaced = replaced_save_filename[0] != L'\0';
    bool has_seamless_coop_replaced = replaced_seamless_coop_save_filename[0] != L'\0';
    if (!has_replaced && !has_seamless_coop_replaced) {
        return NULL;
    }
    size_t len = lstrlenW(lpFileName);
    const wchar_t *replace = NULL;
    if (has_replaced) {
        if (str_ends_with(lpFileName, len, ORIGINAL_SAVE_FILENAME, ORIGINAL_SAVE_FILENAME_LEN)) {
            replace = replaced_save_filename;
        } else if (str_ends_with(lpFileName, len, ORIGIANL_SAVE_FILENAME_BAK, ORIGIANL_SAVE_FILENAME_BAK_LEN)) {
            replace = replaced_save_filename_bak;
        }
    }
    if (has_seamless_coop_replaced) {
        if (str_ends_with(lpFileName, len, SEAMLESS_COOP_SAVE_FILENAME, SEAMLESS_COOP_SAVE_FILENAME_LEN)) {
            replace = replaced_seamless_coop_save_filename;
        } else if (str_ends_with(lpFileName, len, SEAMLESS_COOP_SAVE_FILENAME_BAK, SEAMLESS_COOP_SAVE_FILENAME_BAK_LEN)) {
            replace = replaced_seamless_coop_save_filename_bak;
        }
    }
    if (replace == NULL) {
        return NULL;
    }
    wchar_t *full_path = malloc((64 + len) * sizeof(wchar_t));
    if (full_path == NULL) {
        return NULL;
    }
    lstrcpyW(full_path, lpFileName);
    PathRemoveFileSpecW(full_path);
    PathAppendW(full_path, replace);
    return full_path;
}

HANDLE WINAPI CreateFile_hooked(const LPCWSTR lpFileName,
                                const DWORD dwDesiredAccess,
                                const DWORD dwShareMode,
                                LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                                const DWORD dwCreationDisposition,
                                const DWORD dwFlagsAndAttributes,
                                HANDLE hTemplateFile) {
    if (lpFileName[0] == L'\\') {
        return old_CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    }
    const wchar_t *replace = mods_file_search_prefixed(lpFileName);
    if (replace != NULL) {
        return old_CreateFileW(replace, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    }
    wchar_t *full_path = check_replace_file(lpFileName);
    if (full_path == NULL) {
        return old_CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    }
    HANDLE h = old_CreateFileW(full_path, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    free(full_path);
    return h;
}

BOOL WINAPI CopyFile_hooked(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, BOOL bFailIfExists) {
    wchar_t *new_existing_filename = check_replace_file(lpExistingFileName);
    if (new_existing_filename == NULL) {
        return old_CopyFileW(lpExistingFileName, lpNewFileName, bFailIfExists);
    }
    wchar_t *new_new_filename = check_replace_file(lpNewFileName);
    if (new_new_filename == NULL) {
        free(new_existing_filename);
        return old_CopyFileW(new_existing_filename, lpNewFileName, bFailIfExists);
    }
    BOOL res = old_CopyFileW(new_existing_filename, new_new_filename, bFailIfExists);
    free(new_existing_filename);
    free(new_new_filename);
    return res;
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

float (*old_get_mouse_delta_h)(void*);
float patch_get_mouse_delta_h(void *p)
{
    return 0.0f;
}

float (*old_get_mouse_delta_v)(void*);
float patch_get_mouse_delta_v(void *p)
{
    return 0.0f;
}

static bool patch_eldenring_disable_mouse_camera_control() {
    uint8_t *addr = sig_scan(image_base, image_size, "48 8D 4D ?? E8 ?? ?? ?? ?? 0F 28 F0 48 8D 4D ?? E8 ?? ?? ?? ?? F3 0F 11 45 07 F3 0F 11 75 0B");
    if (!addr) return false;

    uint8_t *jmp = addr + 4;
    uint8_t *real_addr = jmp + *(int32_t*)(jmp + 1) + 5;
    MH_CreateHook(real_addr, (void*)&patch_get_mouse_delta_h, (void**)&old_get_mouse_delta_h);

    jmp = addr + 0x10;
    real_addr = jmp + *(int32_t*)(jmp + 1) + 5;
    MH_CreateHook(real_addr, (void*)&patch_get_mouse_delta_v, (void**)&old_get_mouse_delta_v);
    return true;
}

static bool hook_eldenring_archive_position_resolver() {
    uint8_t *addr = sig_scan(image_base, image_size, "48 83 7B 20 08 48 8D 4B 08 72 03 48 8B 09 4C 8B 4B 18 41 B8 05 00 00 00 4D 3B C8");
    if (!addr) return false;
    addr += *(int32_t*)(addr - 4);
    while (*addr == 0xE9) {
        addr += *(int32_t*)(addr + 1) + 5;
    }
    MH_CreateHook(addr, (void*)&map_archive_path, (void**)&old_map_archive_path);
    return true;
}

static void hook_eldenring_create_file() {
    MH_CreateHook(CreateFileW, (void*)&CreateFile_hooked, (void**)&old_CreateFileW);
}

static void hook_eldenring_copy_file() {
    MH_CreateHook(CopyFileW, (void*)&CopyFile_hooked, (void**)&old_CopyFileW);
}

static bool patch_regulation_safety_check() {
    uint8_t *addr = sig_scan(image_base, image_size, "48 8B 43 08 48 89 88 C8 00 00 00 38 0D ?? ?? ?? ?? 75 ?? E8 ?? ?? ?? ?? 88 05 ?? ?? ?? ?? 88 05 ?? ?? ?? ?? 88 05");
    if (!addr) return false;
    DWORD old_protect;
    VirtualProtect(addr, 1, PAGE_EXECUTE_READWRITE, &old_protect);
    *(addr + 36) = 0x30;
    VirtualProtect(addr, 1, old_protect, &old_protect);
    return true;
}

bool eldenring_install() {
    if (config.replaced_save_filename[0] == L'.') {
        lstrcpyW(replaced_save_filename, ORIGINAL_SAVE_FILENAME);
        PathRemoveExtensionW(replaced_save_filename);
        lstrcatW(replaced_save_filename, config.replaced_save_filename);
    } else {
        lstrcpyW(replaced_save_filename, config.replaced_save_filename);
    }
    if (config.replaced_save_filename[0] != L'\0') {
        lstrcpyW(replaced_save_filename_bak, replaced_save_filename);
        lstrcatW(replaced_save_filename_bak, L".bak");
    }

    if (config.replaced_seamless_coop_save_filename[0] == L'.') {
        lstrcpyW(replaced_seamless_coop_save_filename, SEAMLESS_COOP_SAVE_FILENAME);
        PathRemoveExtensionW(replaced_seamless_coop_save_filename);
        lstrcatW(replaced_seamless_coop_save_filename, config.replaced_seamless_coop_save_filename);
    } else {
        lstrcpyW(replaced_seamless_coop_save_filename, config.replaced_seamless_coop_save_filename);
    }
    if (config.replaced_seamless_coop_save_filename[0] != L'\0') {
        lstrcpyW(replaced_seamless_coop_save_filename_bak, replaced_seamless_coop_save_filename);
        lstrcatW(replaced_seamless_coop_save_filename_bak, L".bak");
    }

    game_running = true;

    async_operations_thread_handle = CreateThread(NULL, 0, async_operation_thread, NULL, 0, NULL);
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

    if (config.disable_mouse_camera_control) {
        patch_eldenring_disable_mouse_camera_control();
    }

    if (replaced_save_filename[0] != L'\0' || replaced_seamless_coop_save_filename[0] != L'\0') {
        patch_regulation_safety_check();
        hook_eldenring_copy_file();
    }

    int modcount = mods_count();
    if (modcount > 0 || replaced_save_filename[0] != L'\0' || replaced_seamless_coop_save_filename[0] != L'\0') {
        hook_eldenring_create_file();
    }
    /* Do not hook if no mod is added, to improve game performance during loading. */
    if (modcount > 0) {
        if (!hook_eldenring_archive_position_resolver()) return false;
    }
    return true;
}

void eldenring_uninstall() {
    game_running = false;

    if (async_operations_thread_handle && WaitForSingleObject(async_operations_thread_handle, 1000) == WAIT_TIMEOUT)
        TerminateThread(async_operations_thread_handle, 0);
    if (reset_achievements_on_new_game_thread_handle && WaitForSingleObject(reset_achievements_on_new_game_thread_handle, 1000) == WAIT_TIMEOUT)
        TerminateThread(reset_achievements_on_new_game_thread_handle, 0);
    er_param_unload();
}
