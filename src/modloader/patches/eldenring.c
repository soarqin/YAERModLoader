/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "eldenring.h"
#include "../lifecycle.h"
#include "eldenring_assets.h"

#include "modloader/config.h"
#include "modloader/dl_allocator.h"
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
#include <stdio.h>

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
static bool system_allocator_hook_installed = false;
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
    fwprintf(stderr, L"NOTE: [eldenring] ");
    va_start(args, fmt);
    vfwprintf(stderr, fmt, args);
    va_end(args);
    fwprintf(stderr, L"\n");
    fflush(stderr);
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

typedef dl_allocator_t *(__cdecl *get_system_allocator_override_t)(void);
typedef bool (__cdecl *SteamAPI_Init_t)(void);
typedef void (__cdecl *game_noop_fn_t)(void *this_ptr);

static get_system_allocator_override_t old_get_system_allocator_override = NULL;
static SteamAPI_Init_t old_SteamAPI_Init = NULL;
static fd4_step_fn_t old_regulation_step_idle = NULL;
static game_noop_fn_t old_cs_memory_init = NULL;
static game_noop_fn_t old_cs_memory_deinit = NULL;
static game_noop_fn_t old_cs_graphics_init = NULL;

typedef struct dl_vector_ptr_msvc2015_s {
    dl_allocator_t *allocator;
    void **first;
    void **last;
    void **end;
} dl_vector_ptr_msvc2015_t;

typedef struct cs_regulation_manager_s {
    void *vtable;
    void *regulation_step;
    dl_vector_ptr_msvc2015_t param_res_caps;
    uint8_t *raw_regulation;
    size_t raw_regulation_len;
} cs_regulation_manager_t;

typedef struct cs_memory_vtable_s {
    void (__cdecl *drop)(void *this_ptr);
    void (__cdecl *init)(void *this_ptr);
    void (__cdecl *deinit)(void *this_ptr);
} cs_memory_vtable_t;

_Static_assert(offsetof(cs_regulation_manager_t, raw_regulation) == 0x30, "CSRegulationManager raw_regulation offset mismatch");
_Static_assert(offsetof(cs_regulation_manager_t, raw_regulation_len) == 0x38, "CSRegulationManager raw_regulation_len offset mismatch");

static dl_allocator_t *__cdecl get_system_allocator_override_hooked(void) {
    dl_allocator_t *allocator = mimalloc_dl_allocator();
    static LONG logged = 0;
    if (InterlockedCompareExchange(&logged, 1, 0) == 0) {
        er_log(L"patch_mem system allocator hook invoked; returning mimalloc allocator=%p", allocator);
    }
    return allocator;
}

static void __cdecl cs_memory_init_nothing(void *this_ptr) {
    (void)this_ptr;
    static LONG logged = 0;
    if (InterlockedCompareExchange(&logged, 1, 0) == 0) {
        er_log(L"patch_mem CSMemoryImp::init no-op invoked");
    }
}

static void __cdecl cs_memory_deinit_nothing(void *this_ptr) {
    (void)this_ptr;
    static LONG logged = 0;
    if (InterlockedCompareExchange(&logged, 1, 0) == 0) {
        er_log(L"patch_mem CSMemoryImp::deinit no-op invoked");
    }
}

static void __cdecl cs_graphics_init_nothing(void *this_ptr) {
    (void)this_ptr;
    static LONG logged = 0;
    if (InterlockedCompareExchange(&logged, 1, 0) == 0) {
        er_log(L"patch_mem CSGraphicsImp first-slot no-op invoked");
    }
}

static void warn_once_bool(bool *warned, const wchar_t *message) {
    if (!*warned) {
        fwprintf(stderr, L"WARNING: %ls\n", message);
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
    wchar_t *full_path = LocalAlloc(0, (MAX_PATH + len) * sizeof(wchar_t));
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
    if (lpFileName == NULL || lpFileName[0] == L'\\') {
        return old_CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    }
    const wchar_t *replace = vfs_route_writable_path(lpFileName);
    if (replace == NULL) replace = mods_file_route_read(lpFileName, dwDesiredAccess, dwCreationDisposition);
    if (replace != NULL) {
        return old_CreateFileW(replace, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    }
    wchar_t *full_path = check_replace_file(lpFileName);
    if (full_path == NULL) {
        return old_CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    }
    HANDLE h = old_CreateFileW(full_path, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    LocalFree(full_path);
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
        LocalFree(new_existing_filename);
        return res;
    }
    BOOL res = old_CopyFileW(new_existing_filename, new_new_filename, bFailIfExists);
    LocalFree(new_existing_filename);
    LocalFree(new_new_filename);
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
        fwprintf(stderr, L"WARNING: disable_mouse_camera_control failed to create horizontal hook: %d\n", status);
        return false;
    }
    status = MH_EnableHook(real_addr);
    if (status != MH_OK) {
        fwprintf(stderr, L"WARNING: disable_mouse_camera_control failed to enable horizontal hook: %d\n", status);
        return false;
    }

    jmp = addr + 0x10;
    real_addr = jmp + *(int32_t*)(jmp + 1) + 5;
    status = MH_CreateHook(real_addr, (void*)&patch_get_mouse_delta_v, (void**)&old_get_mouse_delta_v);
    if (status != MH_OK) {
        fwprintf(stderr, L"WARNING: disable_mouse_camera_control failed to create vertical hook: %d\n", status);
        return false;
    }
    status = MH_EnableHook(real_addr);
    if (status != MH_OK) {
        fwprintf(stderr, L"WARNING: disable_mouse_camera_control failed to enable vertical hook: %d\n", status);
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
        fwprintf(stderr, L"WARNING: failed to create archive position resolver hook: %d\n", status);
        return false;
    }
    status = MH_EnableHook(addr);
    if (status != MH_OK) {
        fwprintf(stderr, L"WARNING: failed to enable archive position resolver hook: %d\n", status);
        return false;
    }
    return true;
}

static void hook_eldenring_create_file() {
    MH_STATUS status = MH_CreateHook(CreateFileW, (void*)&CreateFile_hooked, (void**)&old_CreateFileW);
    if (status != MH_OK) {
        fwprintf(stderr, L"WARNING: failed to create CreateFileW hook: %d\n", status);
        return;
    }
    status = MH_EnableHook(CreateFileW);
    if (status != MH_OK) {
        fwprintf(stderr, L"WARNING: failed to enable CreateFileW hook: %d\n", status);
    }
    status = MH_CreateHook(CreateFileA, (void *)&CreateFileA_hooked, (void **)&old_CreateFileA);
    if (status == MH_OK) status = MH_EnableHook(CreateFileA);
    if (status != MH_OK) fwprintf(stderr, L"WARNING: failed to install CreateFileA hook: %d\n", status);
    status = MH_CreateHook(CreateFile2, (void *)&CreateFile2_hooked, (void **)&old_CreateFile2);
    if (status == MH_OK) status = MH_EnableHook(CreateFile2);
    if (status != MH_OK) fwprintf(stderr, L"WARNING: failed to install CreateFile2 hook: %d\n", status);
}

BOOL WINAPI DeleteFileW_hooked(LPCWSTR lpFileName) {
    const wchar_t *replace = vfs_route_writable_path(lpFileName);
    wchar_t *allocated = replace == NULL ? check_replace_file(lpFileName) : NULL;
    BOOL result = old_DeleteFileW(replace != NULL ? replace : (allocated != NULL ? allocated : lpFileName));
    LocalFree(allocated);
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
        fwprintf(stderr, L"WARNING: failed to create CopyFileW hook: %d\n", status);
        return;
    }
    status = MH_EnableHook(CopyFileW);
    if (status != MH_OK) {
        fwprintf(stderr, L"WARNING: failed to enable CopyFileW hook: %d\n", status);
    }
}

static void hook_eldenring_writable_file_apis() {
    MH_STATUS status = MH_CreateHook(DeleteFileW, (void *)&DeleteFileW_hooked, (void **)&old_DeleteFileW);
    if (status == MH_OK) status = MH_EnableHook(DeleteFileW);
    if (status != MH_OK) fwprintf(stderr, L"WARNING: failed to install DeleteFileW hook: %d\n", status);
    status = MH_CreateHook(DeleteFileA, (void *)&DeleteFileA_hooked, (void **)&old_DeleteFileA);
    if (status == MH_OK) status = MH_EnableHook(DeleteFileA);
    if (status != MH_OK) fwprintf(stderr, L"WARNING: failed to install DeleteFileA hook: %d\n", status);
    status = MH_CreateHook(CreateDirectoryW, (void *)&CreateDirectoryW_hooked, (void **)&old_CreateDirectoryW);
    if (status == MH_OK) status = MH_EnableHook(CreateDirectoryW);
    if (status != MH_OK) fwprintf(stderr, L"WARNING: failed to install CreateDirectoryW hook: %d\n", status);
    status = MH_CreateHook(CreateDirectoryA, (void *)&CreateDirectoryA_hooked, (void **)&old_CreateDirectoryA);
    if (status == MH_OK) status = MH_EnableHook(CreateDirectoryA);
    if (status != MH_OK) fwprintf(stderr, L"WARNING: failed to install CreateDirectoryA hook: %d\n", status);
    status = MH_CreateHook(CreateDirectoryExW, (void *)&CreateDirectoryExW_hooked, (void **)&old_CreateDirectoryExW);
    if (status == MH_OK) status = MH_EnableHook(CreateDirectoryExW);
    if (status != MH_OK) fwprintf(stderr, L"WARNING: failed to install CreateDirectoryExW hook: %d\n", status);
}

static void __cdecl regulation_step_idle_hooked(void *this_ptr, fd4_time_t *time) {
    static bool warned_manager = false;
    static bool warned_allocator = false;

    old_regulation_step_idle(this_ptr, time);


    cs_regulation_manager_t *mgr = singleton_find("CSRegulationManager");
    if (mgr == NULL) {
        warn_once_bool(&warned_manager, L"prevent_regulation_save_write could not find CSRegulationManager");
        return;
    }

    uint8_t *raw = mgr->raw_regulation;
    size_t len = mgr->raw_regulation_len;
    if (raw == NULL) return;

    mgr->raw_regulation = NULL;
    mgr->raw_regulation_len = 0;
    if (len == 0) return;

    dl_allocator_t *allocator = dl_allocator_for_object(raw);
    if (allocator == NULL) {
        warn_once_bool(&warned_allocator, L"prevent_regulation_save_write cleared raw regulation but could not find its allocator; leaking one buffer");
        return;
    }
    static bool logged_clear = false;
    if (!logged_clear) {
        er_log(L"prevent_regulation_save_write cleared raw regulation buffer len=%zu allocator=%p", len, allocator);
        logged_clear = true;
    }
    dl_allocator_dealloc(allocator, raw);
}

static bool install_regulation_save_guard(void) {
    void *step = fd4_step_find(L"CSRegulationStep::STEP_Idle");
    if (step == NULL) {
        fwprintf(stderr, L"WARNING: prevent_regulation_save_write could not find CSRegulationStep::STEP_Idle\n");
        return false;
    }
    er_log(L"prevent_regulation_save_write step found: CSRegulationStep::STEP_Idle=%p", step);
    MH_STATUS status = MH_CreateHook(step, (void *)&regulation_step_idle_hooked, (void **)&old_regulation_step_idle);
    if (status != MH_OK) {
        fwprintf(stderr, L"WARNING: prevent_regulation_save_write failed to create hook: %d\n", status);
        return false;
    }
    status = MH_EnableHook(step);
    if (status != MH_OK) {
        fwprintf(stderr, L"WARNING: prevent_regulation_save_write failed to enable hook: %d\n", status);
        return false;
    }
    er_log(L"prevent_regulation_save_write hook enabled");
    return true;
}

static bool install_system_allocator_hook_before_main(void) {
    uint8_t *addr = sig_scan(image_base, image_size, "E8 ?? ?? ?? ?? 48 8B 74 24 30 48 8B 5C 24 38 48 83 C4 20 5F E9 ?? ?? ?? ??");
    if (addr == NULL) {
        fwprintf(stderr, L"WARNING: patch_mem could not find system allocator override target\n");
        return false;
    }

    void *target = addr + 25 + *(int32_t *)(addr + 21);
    er_log(L"patch_mem system allocator override target=%p", target);
    MH_STATUS status = MH_CreateHook(target, (void *)&get_system_allocator_override_hooked, (void **)&old_get_system_allocator_override);
    if (status != MH_OK) {
        fwprintf(stderr, L"WARNING: patch_mem failed to create system allocator hook: %d\n", status);
        return false;
    }
    status = MH_EnableHook(target);
    if (status != MH_OK) {
        fwprintf(stderr, L"WARNING: patch_mem failed to enable system allocator hook: %d\n", status);
        return false;
    }
    system_allocator_hook_installed = true;
    er_log(L"patch_mem system allocator hook enabled");
    return true;
}

static bool install_heap_allocator_patch(void) {
    er_log(L"patch_mem heap substeps: cs_graphics=%d", config.patch_mem_hook_cs_graphics ? 1 : 0);

    void **cs_memory_vtable = rtti_find_vtable("CS::CSMemoryImp");
    if (cs_memory_vtable == NULL) {
        cs_memory_vtable = rtti_find_vtable("NS_SPRJ::CSMemoryImp");
    }
    if (cs_memory_vtable == NULL) {
        fwprintf(stderr, L"WARNING: patch_mem could not find CSMemoryImp vtable\n");
        return false;
    }
    cs_memory_vtable_t *mem_vtable = (cs_memory_vtable_t *)cs_memory_vtable;
    er_log(L"patch_mem CSMemoryImp vtable=%p init=%p deinit=%p", cs_memory_vtable, mem_vtable->init, mem_vtable->deinit);

    void *cs_graphics_first = NULL;
    if (config.patch_mem_hook_cs_graphics) {
        void **cs_graphics_vtable = rtti_find_vtable("CS::CSGraphicsImp");
        cs_graphics_first = cs_graphics_vtable ? *cs_graphics_vtable : NULL;
        if (cs_graphics_first == NULL) {
            fwprintf(stderr, L"WARNING: patch_mem could not find CSGraphicsImp first vtable slot\n");
            return false;
        }
        er_log(L"patch_mem CSGraphicsImp vtable=%p first=%p", cs_graphics_vtable, cs_graphics_first);
    } else {
        er_log(L"patch_mem CSGraphicsImp hook disabled by config");
    }

    void **allocator_table_first = dl_allocator_table_first();
    void **allocator_table_last = dl_allocator_table_last_er();
    er_log(L"patch_mem allocator table first=%p last=%p", allocator_table_first, allocator_table_last);
    if (!dl_allocator_fill_table(mimalloc_dl_allocator())) {
        fwprintf(stderr, L"WARNING: patch_mem could not fill Dantelion allocator table\n");
        return false;
    }
    er_log(L"patch_mem allocator table filled with mimalloc allocator=%p", mimalloc_dl_allocator());

    MH_STATUS status = MH_CreateHook((void *)mem_vtable->init, (void *)&cs_memory_init_nothing, (void **)&old_cs_memory_init);
    if (status != MH_OK) {
        fwprintf(stderr, L"WARNING: patch_mem failed to create CSMemoryImp::init hook: %d\n", status);
        return false;
    }
    status = MH_EnableHook((void *)mem_vtable->init);
    if (status != MH_OK) {
        fwprintf(stderr, L"WARNING: patch_mem failed to enable CSMemoryImp::init hook: %d\n", status);
        return false;
    }
    er_log(L"patch_mem CSMemoryImp::init hook enabled");

    status = MH_CreateHook((void *)mem_vtable->deinit, (void *)&cs_memory_deinit_nothing, (void **)&old_cs_memory_deinit);
    if (status != MH_OK) {
        fwprintf(stderr, L"WARNING: patch_mem failed to create CSMemoryImp::deinit hook: %d\n", status);
    } else {
        status = MH_EnableHook((void *)mem_vtable->deinit);
        if (status != MH_OK) {
            fwprintf(stderr, L"WARNING: patch_mem failed to enable CSMemoryImp::deinit hook: %d\n", status);
        } else {
            er_log(L"patch_mem CSMemoryImp::deinit hook enabled");
        }
    }

    if (config.patch_mem_hook_cs_graphics) {
        status = MH_CreateHook(cs_graphics_first, (void *)&cs_graphics_init_nothing, (void **)&old_cs_graphics_init);
        if (status != MH_OK) {
            fwprintf(stderr, L"WARNING: patch_mem failed to create CSGraphicsImp hook: %d\n", status);
            return false;
        }
        status = MH_EnableHook(cs_graphics_first);
        if (status != MH_OK) {
            fwprintf(stderr, L"WARNING: patch_mem failed to enable CSGraphicsImp hook: %d\n", status);
            return false;
        }
        er_log(L"patch_mem CSGraphicsImp hook enabled");
    } else {
        er_log(L"patch_mem CSGraphicsImp hook disabled by config");
    }
    er_log(L"patch_mem heap allocator patch complete");
    return true;
}

static BOOL CALLBACK eldenring_after_main_install_once(PINIT_ONCE init_once, PVOID parameter, PVOID *context) {
    (void)init_once;
    (void)parameter;
    (void)context;
    er_log(L"after-main install start");
    if (config.prevent_regulation_save_write) {
        install_regulation_save_guard();
    } else {
        er_log(L"prevent_regulation_save_write disabled by config");
    }
    if (config.patch_mem && system_allocator_hook_installed) {
        install_heap_allocator_patch();
    } else if (config.patch_mem) {
        fwprintf(stderr, L"WARNING: patch_mem skipping heap allocator patch because system allocator hook is not installed\n");
    } else {
        er_log(L"patch_mem disabled by config");
    }
    if (mods_count() > 0) {
        eldenring_assets_install(image_base, image_size);
    }
    er_log(L"after-main install end");
    return TRUE;
}

static bool __cdecl SteamAPI_Init_hooked(void) {
    bool result = old_SteamAPI_Init();
    er_log(L"SteamAPI_Init returned %d", result ? 1 : 0);
    if (result) {
        InitOnceExecuteOnce(&after_main_once, eldenring_after_main_install_once, NULL, NULL);
        ml_lifecycle_advance(ML_LIFECYCLE_PHASE_AFTER_RUNTIME_INIT);
    }
    return result;
}

static bool install_steamapi_deferred_hook(void) {
    HMODULE steam_api = LoadLibraryW(L"steam_api64.dll");
    if (steam_api == NULL) {
        fwprintf(stderr, L"WARNING: could not load steam_api64.dll for deferred Elden Ring hooks\n");
        return false;
    }
    void *steam_api_init = (void *)GetProcAddress(steam_api, "SteamAPI_Init");
    if (steam_api_init == NULL) {
        fwprintf(stderr, L"WARNING: could not find SteamAPI_Init for deferred Elden Ring hooks\n");
        return false;
    }
    MH_STATUS status = MH_CreateHook(steam_api_init, (void *)&SteamAPI_Init_hooked, (void **)&old_SteamAPI_Init);
    if (status != MH_OK) {
        fwprintf(stderr, L"WARNING: failed to create SteamAPI_Init deferred hook: %d\n", status);
        return false;
    }
    status = MH_EnableHook(steam_api_init);
    if (status != MH_OK) {
        fwprintf(stderr, L"WARNING: failed to enable SteamAPI_Init deferred hook: %d\n", status);
        return false;
    }
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

    if (config.patch_mem) {
        install_system_allocator_hook_before_main();
    } else {
        er_log(L"patch_mem disabled by config before main");
    }

    if ((config.skip_intro || config.prevent_regulation_save_write || config.patch_mem) &&
        ml_game_context_get()->runtime_ready_trigger == ML_RUNTIME_READY_STEAM_API_INIT) {
        install_steamapi_deferred_hook();
    } else {
        er_log(L"runtime-ready trigger is unavailable or not needed");
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
    er_log(L"uninstall start");
    game_running = false;

    /* NOTE: TerminateThread is unsafe (leaks stack, CRT state, held locks).
       We use a longer timeout and accept the thread may still be running on process exit. */
    if (async_operations_thread_handle && WaitForSingleObject(async_operations_thread_handle, 5000) == WAIT_TIMEOUT)
        TerminateThread(async_operations_thread_handle, 0);
    if (reset_achievements_on_new_game_thread_handle && WaitForSingleObject(reset_achievements_on_new_game_thread_handle, 5000) == WAIT_TIMEOUT)
        TerminateThread(reset_achievements_on_new_game_thread_handle, 0);
}
