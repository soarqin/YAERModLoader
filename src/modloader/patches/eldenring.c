/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "eldenring.h"
#include "common/allocator.h"
#include "../lifecycle.h"
#include "asset_hooks.h"

#include "modloader/config.h"
#include "modloader/dl_allocator.h"
#include "log.h"
#include "modloader/mimalloc_allocator.h"
#include "modloader/mod.h"
#include "modloader/vfs.h"

#include "game/game.h"

#include "process/fd4_step.h"
#include "process/image.h"
#include "process/rtti.h"
#include "process/scanner.h"
#include "process/singleton.h"
#include "process/util.h"

#include "steam/api.h"

#include <MinHook.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

typedef struct er_wstring_local_s {
    void *unk;
    wchar_t *string;
    void *unk2;
    uint64_t length;
    uint64_t capacity;
} er_wstring_local_t;

static wchar_t *wstring_str_mutable(er_wstring_local_t *str) {
    return (sizeof(wchar_t) * str->capacity >= 16) ? str->string : (wchar_t*)&str->string;
}

static HANDLE async_operations_thread_handle = NULL;
static volatile bool game_running = false;
static HANDLE reset_achievements_on_new_game_thread_handle = NULL;
static void *image_base;
static size_t image_size;
static INIT_ONCE after_main_once = INIT_ONCE_STATIC_INIT;

/* 80: config values are up to 63 chars; the `.suffix` form prepends `ER0000`
 * (69 max) and the bak variants append `.bak` (73 max), plus terminator. */
static wchar_t replaced_save_filename[80] = L"";
static wchar_t replaced_save_filename_bak[80] = L"";
static wchar_t replaced_seamless_coop_save_filename[80] = L"";
static wchar_t replaced_seamless_coop_save_filename_bak[80] = L"";

#define ORIGINAL_SAVE_FILENAME L"ER0000.sl2"
#define ORIGINAL_SAVE_FILENAME_LEN 10
#define ORIGINAL_SAVE_FILENAME_BAK L"ER0000.sl2.bak"
#define ORIGINAL_SAVE_FILENAME_BAK_LEN 14
#define SEAMLESS_COOP_SAVE_FILENAME L"ER0000.co2"
#define SEAMLESS_COOP_SAVE_FILENAME_LEN 10
#define SEAMLESS_COOP_SAVE_FILENAME_BAK L"ER0000.co2.bak"
#define SEAMLESS_COOP_SAVE_FILENAME_BAK_LEN 14

static bool str_ends_with(const wchar_t *str, size_t str_len, const wchar_t *suffix, size_t suffix_len) {
    if (suffix_len > str_len) return false;
    return StrCmpNIW(str + str_len - suffix_len, suffix, suffix_len) == 0;
}

static void er_log(const wchar_t *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ml_log_vwrite(ML_LOG_LEVEL_DEBUG, L"eldenring", fmt, args);
    va_end(args);
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
    if (config.cpu_affinity_strategy != 0) set_process_cpu_affinity_strategy(config.cpu_affinity_strategy);
    return 0;
}

typedef void *(__cdecl *map_archive_path_t)(er_wstring_local_t *path, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5, uint64_t p6);
typedef HANDLE (WINAPI *CreateFileW_t)(LPCWSTR lpFileName,
                                       DWORD dwDesiredAccess,
                                       DWORD dwShareMode,
                                       LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                                       DWORD dwCreationDisposition,
                                       DWORD dwFlagsAndAttributes,
                                        HANDLE hTemplateFile);
typedef HANDLE (WINAPI *CreateFileA_t)(LPCSTR lpFileName,
                                        DWORD dwDesiredAccess,
                                        DWORD dwShareMode,
                                        LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                                        DWORD dwCreationDisposition,
                                        DWORD dwFlagsAndAttributes,
                                        HANDLE hTemplateFile);
typedef HANDLE (WINAPI *CreateFile2_t)(LPCWSTR lpFileName, DWORD dwDesiredAccess,
                                        DWORD dwShareMode, DWORD dwCreationDisposition,
                                        LPCREATEFILE2_EXTENDED_PARAMETERS pCreateExParams);
typedef BOOL (WINAPI *CopyFileW_t)(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, BOOL bFailIfExists);
typedef BOOL (WINAPI *DeleteFileW_t)(LPCWSTR lpFileName);
typedef BOOL (WINAPI *DeleteFileA_t)(LPCSTR lpFileName);
typedef BOOL (WINAPI *CreateDirectoryW_t)(LPCWSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
typedef BOOL (WINAPI *CreateDirectoryA_t)(LPCSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);
typedef BOOL (WINAPI *CreateDirectoryExW_t)(LPCWSTR lpTemplateDirectory, LPCWSTR lpNewDirectory, LPSECURITY_ATTRIBUTES lpSecurityAttributes);

static map_archive_path_t old_map_archive_path = NULL;
static CreateFileW_t old_CreateFileW = NULL;
static CreateFileA_t old_CreateFileA = NULL;
static CreateFile2_t old_CreateFile2 = NULL;
static CopyFileW_t old_CopyFileW = NULL;
static DeleteFileW_t old_DeleteFileW = NULL;
static DeleteFileA_t old_DeleteFileA = NULL;
static CreateDirectoryW_t old_CreateDirectoryW = NULL;
static CreateDirectoryA_t old_CreateDirectoryA = NULL;
static CreateDirectoryExW_t old_CreateDirectoryExW = NULL;

typedef bool (__cdecl *SteamAPI_Init_t)(void);

static SteamAPI_Init_t old_SteamAPI_Init = NULL;
static void *steam_api_init_hook_target;

static void warn_once_bool(bool *warned, const wchar_t *message) {
    if (!*warned) {
        ML_LOG_WARN(L"eldenring", L"%ls", message);
        *warned = true;
    }
}

void *__cdecl map_archive_path(er_wstring_local_t *path, const uint64_t p2, const uint64_t p3, const uint64_t p4, const uint64_t p5, const uint64_t p6) {
    void *res = old_map_archive_path(path, p2, p3, p4, p5, p6);
    if (path == NULL) return res;
    wchar_t *str = wstring_str_mutable(path);
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
        } else if (str_ends_with(lpFileName, len, ORIGINAL_SAVE_FILENAME_BAK, ORIGINAL_SAVE_FILENAME_BAK_LEN)) {
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
    /* MAX_PATH of headroom: PathAppendW requires the destination buffer to
     * hold at least MAX_PATH characters. */
    wchar_t *full_path = yaer_mem_alloc(0, (MAX_PATH + len) * sizeof(wchar_t));
    if (full_path == NULL) {
        return NULL;
    }
    lstrcpyW(full_path, lpFileName);
    PathRemoveFileSpecW(full_path);
    PathAppendW(full_path, replace);
    vfs_register_writable_path(lpFileName, full_path);
    return full_path;
}

HANDLE WINAPI CreateFile_hooked(const LPCWSTR lpFileName,
                                const DWORD dwDesiredAccess,
                                const DWORD dwShareMode,
                                LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                                const DWORD dwCreationDisposition,
                                const DWORD dwFlagsAndAttributes,
                                HANDLE hTemplateFile) {
    /* CreateFileW(NULL, ...) fails gracefully; do not crash on it here. */
    if (lpFileName == NULL) {
        return old_CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    }
    const wchar_t *replace = vfs_route_writable_path(lpFileName);
    if (replace == NULL) replace = mods_file_route_read(lpFileName, dwDesiredAccess, dwCreationDisposition);
    if (replace != NULL) {
        return old_CreateFileW(replace, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    }
    if (lpFileName[0] == L'\\') {
        return old_CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    }
    wchar_t *full_path = check_replace_file(lpFileName);
    if (full_path == NULL) {
        return old_CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    }
    HANDLE h = old_CreateFileW(full_path, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    yaer_mem_free(full_path);
    return h;
}

HANDLE WINAPI CreateFileA_hooked(const LPCSTR lpFileName,
                                 const DWORD dwDesiredAccess,
                                 const DWORD dwShareMode,
                                 LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                                 const DWORD dwCreationDisposition,
                                 const DWORD dwFlagsAndAttributes,
                                 HANDLE hTemplateFile) {
    const wchar_t *replace = mods_file_route_read_a(lpFileName, dwDesiredAccess, dwCreationDisposition);
    if (replace == NULL) {
        return old_CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
                               dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    }
    return old_CreateFileW(replace, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
                           dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

HANDLE WINAPI CreateFile2_hooked(const LPCWSTR lpFileName, const DWORD dwDesiredAccess,
                                 const DWORD dwShareMode, const DWORD dwCreationDisposition,
                                 LPCREATEFILE2_EXTENDED_PARAMETERS pCreateExParams) {
    const wchar_t *replace = mods_file_route_read(lpFileName, dwDesiredAccess, dwCreationDisposition);
    return old_CreateFile2(replace != NULL ? replace : lpFileName, dwDesiredAccess, dwShareMode,
                           dwCreationDisposition, pCreateExParams);
}

BOOL WINAPI CopyFile_hooked(LPCWSTR lpExistingFileName, LPCWSTR lpNewFileName, BOOL bFailIfExists) {
    wchar_t *new_existing_filename = check_replace_file(lpExistingFileName);
    if (new_existing_filename == NULL) {
        return old_CopyFileW(lpExistingFileName, lpNewFileName, bFailIfExists);
    }
    wchar_t *new_new_filename = check_replace_file(lpNewFileName);
    if (new_new_filename == NULL) {
        BOOL res = old_CopyFileW(new_existing_filename, lpNewFileName, bFailIfExists);
        yaer_mem_free(new_existing_filename);
        return res;
    }
    BOOL res = old_CopyFileW(new_existing_filename, new_new_filename, bFailIfExists);
    yaer_mem_free(new_existing_filename);
    yaer_mem_free(new_new_filename);
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

static bool patch_eldenring_remove_chromatic_aberration() {
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
    MH_STATUS status = MH_CreateHook(real_addr, (void*)&patch_get_mouse_delta_h, (void**)&old_get_mouse_delta_h);
    if (status != MH_OK) {
        ML_LOG_WARN(L"eldenring", L"disable_mouse_camera_control failed to create horizontal hook: %d", status);
        return false;
    }
    status = MH_EnableHook(real_addr);
    if (status != MH_OK) {
        ML_LOG_WARN(L"eldenring", L"disable_mouse_camera_control failed to enable horizontal hook: %d", status);
        return false;
    }

    jmp = addr + 0x10;
    real_addr = jmp + *(int32_t*)(jmp + 1) + 5;
    status = MH_CreateHook(real_addr, (void*)&patch_get_mouse_delta_v, (void**)&old_get_mouse_delta_v);
    if (status != MH_OK) {
        ML_LOG_WARN(L"eldenring", L"disable_mouse_camera_control failed to create vertical hook: %d", status);
        return false;
    }
    status = MH_EnableHook(real_addr);
    if (status != MH_OK) {
        ML_LOG_WARN(L"eldenring", L"disable_mouse_camera_control failed to enable vertical hook: %d", status);
        return false;
    }
    return true;
}

static bool hook_eldenring_archive_position_resolver() {
    uint8_t *addr = sig_scan(image_base, image_size, "48 83 7B 20 08 48 8D 4B 08 72 03 48 8B 09 4C 8B 4B 18 41 B8 05 00 00 00 4D 3B C8");
    if (!addr) return false;
    addr += *(int32_t*)(addr - 4);
    while (*addr == 0xE9) {
        addr += *(int32_t*)(addr + 1) + 5;
    }
    MH_STATUS status = MH_CreateHook(addr, (void*)&map_archive_path, (void**)&old_map_archive_path);
    if (status != MH_OK) {
        ML_LOG_WARN(L"eldenring", L"failed to create archive position resolver hook: %d", status);
        return false;
    }
    status = MH_EnableHook(addr);
    if (status != MH_OK) {
        ML_LOG_WARN(L"eldenring", L"failed to enable archive position resolver hook: %d", status);
        return false;
    }
    return true;
}

static void hook_eldenring_create_file() {
    MH_STATUS status = MH_CreateHook(CreateFileW, (void*)&CreateFile_hooked, (void**)&old_CreateFileW);
    if (status != MH_OK) {
        ML_LOG_WARN(L"eldenring", L"failed to create CreateFileW hook: %d", status);
        return;
    }
    status = MH_EnableHook(CreateFileW);
    if (status != MH_OK) {
        ML_LOG_WARN(L"eldenring", L"failed to enable CreateFileW hook: %d", status);
    }
    status = MH_CreateHook(CreateFileA, (void *)&CreateFileA_hooked, (void **)&old_CreateFileA);
    if (status == MH_OK) status = MH_EnableHook(CreateFileA);
    if (status != MH_OK) ML_LOG_WARN(L"eldenring", L"failed to install CreateFileA hook: %d", status);
    status = MH_CreateHook(CreateFile2, (void *)&CreateFile2_hooked, (void **)&old_CreateFile2);
    if (status == MH_OK) status = MH_EnableHook(CreateFile2);
    if (status != MH_OK) ML_LOG_WARN(L"eldenring", L"failed to install CreateFile2 hook: %d", status);
}

BOOL WINAPI DeleteFileW_hooked(LPCWSTR lpFileName) {
    const wchar_t *replace = vfs_route_writable_path(lpFileName);
    wchar_t *allocated = replace == NULL ? check_replace_file(lpFileName) : NULL;
    BOOL result = old_DeleteFileW(replace != NULL ? replace : (allocated != NULL ? allocated : lpFileName));
    yaer_mem_free(allocated);
    return result;
}

BOOL WINAPI DeleteFileA_hooked(LPCSTR lpFileName) {
    return old_DeleteFileA(lpFileName);
}

BOOL WINAPI CreateDirectoryW_hooked(LPCWSTR lpPathName, LPSECURITY_ATTRIBUTES attributes) {
    const wchar_t *replace = vfs_route_writable_path(lpPathName);
    return old_CreateDirectoryW(replace != NULL ? replace : lpPathName, attributes);
}

BOOL WINAPI CreateDirectoryA_hooked(LPCSTR lpPathName, LPSECURITY_ATTRIBUTES attributes) {
    return old_CreateDirectoryA(lpPathName, attributes);
}

BOOL WINAPI CreateDirectoryExW_hooked(LPCWSTR template_path, LPCWSTR new_path, LPSECURITY_ATTRIBUTES attributes) {
    const wchar_t *replace = vfs_route_writable_path(new_path);
    return old_CreateDirectoryExW(template_path, replace != NULL ? replace : new_path, attributes);
}

static void hook_eldenring_copy_file() {
    MH_STATUS status = MH_CreateHook(CopyFileW, (void*)&CopyFile_hooked, (void**)&old_CopyFileW);
    if (status != MH_OK) {
        ML_LOG_WARN(L"eldenring", L"failed to create CopyFileW hook: %d", status);
        return;
    }
    status = MH_EnableHook(CopyFileW);
    if (status != MH_OK) {
        ML_LOG_WARN(L"eldenring", L"failed to enable CopyFileW hook: %d", status);
    }
}

static void hook_eldenring_writable_file_apis() {
    MH_STATUS status = MH_CreateHook(DeleteFileW, (void *)&DeleteFileW_hooked, (void **)&old_DeleteFileW);
    if (status == MH_OK) status = MH_EnableHook(DeleteFileW);
    if (status != MH_OK) ML_LOG_WARN(L"eldenring", L"failed to install DeleteFileW hook: %d", status);
    status = MH_CreateHook(DeleteFileA, (void *)&DeleteFileA_hooked, (void **)&old_DeleteFileA);
    if (status == MH_OK) status = MH_EnableHook(DeleteFileA);
    if (status != MH_OK) ML_LOG_WARN(L"eldenring", L"failed to install DeleteFileA hook: %d", status);
    status = MH_CreateHook(CreateDirectoryW, (void *)&CreateDirectoryW_hooked, (void **)&old_CreateDirectoryW);
    if (status == MH_OK) status = MH_EnableHook(CreateDirectoryW);
    if (status != MH_OK) ML_LOG_WARN(L"eldenring", L"failed to install CreateDirectoryW hook: %d", status);
    status = MH_CreateHook(CreateDirectoryA, (void *)&CreateDirectoryA_hooked, (void **)&old_CreateDirectoryA);
    if (status == MH_OK) status = MH_EnableHook(CreateDirectoryA);
    if (status != MH_OK) ML_LOG_WARN(L"eldenring", L"failed to install CreateDirectoryA hook: %d", status);
    status = MH_CreateHook(CreateDirectoryExW, (void *)&CreateDirectoryExW_hooked, (void **)&old_CreateDirectoryExW);
    if (status == MH_OK) status = MH_EnableHook(CreateDirectoryExW);
    if (status != MH_OK) ML_LOG_WARN(L"eldenring", L"failed to install CreateDirectoryExW hook: %d", status);
}

static BOOL CALLBACK eldenring_after_main_install_once(PINIT_ONCE init_once, PVOID parameter, PVOID *context) {
    bool assets_applied = true;
    (void)init_once;
    (void)parameter;
    (void)context;
    er_log(L"after-main install start");
    if (mods_count() > 0) {
        assets_applied = ml_asset_hooks_install(ml_game_context_get(), image_base, image_size);
    }
    er_log(L"after-main install end: assets=%d", assets_applied ? 1 : 0);
    return assets_applied ? TRUE : FALSE;
}

static bool __cdecl SteamAPI_Init_hooked(void) {
    bool result = old_SteamAPI_Init();
    er_log(L"SteamAPI_Init returned %d", result ? 1 : 0);
    if (result) {
        if (!InitOnceExecuteOnce(&after_main_once, eldenring_after_main_install_once, NULL, NULL)) {
            ML_LOG_WARN(L"eldenring", L"AFTER_RUNTIME_INIT setup failed; deferred initialization will retry");
            return result;
        }
        ml_lifecycle_advance(ML_LIFECYCLE_PHASE_AFTER_RUNTIME_INIT);
    }
    return result;
}

static bool install_steamapi_deferred_hook(void) {
    HMODULE steam_api = LoadLibraryW(L"steam_api64.dll");
    if (steam_api == NULL) {
        ML_LOG_WARN(L"eldenring", L"could not load steam_api64.dll for deferred hooks");
        return false;
    }
    void *steam_api_init = (void *)GetProcAddress(steam_api, "SteamAPI_Init");
    if (steam_api_init == NULL) {
        ML_LOG_WARN(L"eldenring", L"could not find SteamAPI_Init for deferred hooks");
        return false;
    }
    MH_STATUS status = MH_CreateHook(steam_api_init, (void *)&SteamAPI_Init_hooked, (void **)&old_SteamAPI_Init);
    if (status != MH_OK) {
        ML_LOG_WARN(L"eldenring", L"failed to create SteamAPI_Init deferred hook: %d", status);
        return false;
    }
    status = MH_EnableHook(steam_api_init);
    if (status != MH_OK) {
        ML_LOG_WARN(L"eldenring", L"failed to enable SteamAPI_Init deferred hook: %d", status);
        MH_RemoveHook(steam_api_init);
        return false;
    }
    steam_api_init_hook_target = steam_api_init;
    er_log(L"deferred SteamAPI_Init hook enabled at %p", steam_api_init);
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

    image_base = get_module_image_base(NULL, &image_size);
    er_log(L"install start: image_base=%p image_size=%zu prevent_regulation_save_write=%d patch_mem=%d", image_base, image_size, config.prevent_regulation_save_write ? 1 : 0, config.patch_mem ? 1 : 0);

    if (ml_game_context_get()->runtime_ready_trigger == ML_RUNTIME_READY_STEAM_API_INIT) {
        install_steamapi_deferred_hook();
    } else {
        er_log(L"runtime-ready trigger is unavailable");
    }

    async_operations_thread_handle = CreateThread(NULL, 0, async_operation_thread, NULL, 0, NULL);
    if (config.reset_achievements_on_new_game) {
        reset_achievements_on_new_game_thread_handle = CreateThread(NULL, 0, reset_achievements_on_new_game_thread, NULL, 0, NULL);
    }

    if (config.remove_chromatic_aberration) {
        patch_eldenring_remove_chromatic_aberration();
    }

    if (config.remove_vignette) {
        patch_eldenring_remove_vignette();
    }

    if (config.disable_mouse_camera_control) {
        patch_eldenring_disable_mouse_camera_control();
    }

    if (replaced_save_filename[0] != L'\0' || replaced_seamless_coop_save_filename[0] != L'\0') {
        hook_eldenring_copy_file();
        hook_eldenring_writable_file_apis();
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
    bool runtime_hook_removed = true;
    er_log(L"uninstall start");
    game_running = false;

    if (!ml_asset_hooks_uninstall()) {
        ML_LOG_WARN(L"eldenring", L"one or more asset hooks could not be removed");
    }

    if (steam_api_init_hook_target != NULL) {
        MH_STATUS status = MH_RemoveHook(steam_api_init_hook_target);
        runtime_hook_removed = status == MH_OK || status == MH_ERROR_NOT_CREATED;
        if (!runtime_hook_removed) {
            ML_LOG_WARN(L"eldenring", L"failed to remove runtime-ready hook at %p: %d",
                        steam_api_init_hook_target, status);
        }
    }
    if (runtime_hook_removed) {
        steam_api_init_hook_target = NULL;
        old_SteamAPI_Init = NULL;
        InitOnceInitialize(&after_main_once);
    }

    /* NOTE: TerminateThread is unsafe (leaks stack, CRT state, held locks).
       We use a longer timeout and accept the thread may still be running on process exit. */
    if (async_operations_thread_handle && WaitForSingleObject(async_operations_thread_handle, 5000) == WAIT_TIMEOUT)
        TerminateThread(async_operations_thread_handle, 0);
    if (reset_achievements_on_new_game_thread_handle && WaitForSingleObject(reset_achievements_on_new_game_thread_handle, 5000) == WAIT_TIMEOUT)
        TerminateThread(reset_achievements_on_new_game_thread_handle, 0);
    if (async_operations_thread_handle != NULL) CloseHandle(async_operations_thread_handle);
    if (reset_achievements_on_new_game_thread_handle != NULL) CloseHandle(reset_achievements_on_new_game_thread_handle);
    async_operations_thread_handle = NULL;
    reset_achievements_on_new_game_thread_handle = NULL;
}
