/*
 * Copyright (C) 2024,2025,2026, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "eldenring.h"

#include "asset_hooks.h"
#include "save_mapping.h"
#include "win32_hooks.h"

#include "modloader/config.h"
#include "modloader/hook.h"
#include "modloader/lifecycle.h"
#include "modloader/mod.h"

#include "log.h"

#include "game/game.h"

#include "process/image.h"
#include "process/scanner.h"
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

typedef void *(__cdecl *map_archive_path_t)(er_wstring_local_t *path, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5, uint64_t p6);
typedef bool (__cdecl *SteamAPI_Init_t)(void);

static HANDLE async_operations_thread_handle = NULL;
static volatile bool game_running = false;
static void *image_base;
static size_t image_size;
static INIT_ONCE after_main_once = INIT_ONCE_STATIC_INIT;

static map_archive_path_t old_map_archive_path = NULL;
static void *archive_resolver_hook_target;
static SteamAPI_Init_t old_SteamAPI_Init = NULL;
static void *steam_api_init_hook_target;

static void er_log(const wchar_t *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ml_log_vwrite(ML_LOG_LEVEL_DEBUG, L"eldenring", fmt, args);
    va_end(args);
}

DWORD WINAPI async_operation_thread(LPVOID arg) {
    (void)arg;
    if (config.cpu_affinity_strategy != 0) set_process_cpu_affinity_strategy(config.cpu_affinity_strategy);
    return 0;
}

/* Elden Ring resolves archive-relative virtual paths ("dataN:/...") through this
 * function; rewrite the prefix to a loose on-disk path when a mod provides the
 * file. This is ER-specific and unrelated to the Win32 file API hooks. */
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

static bool hook_eldenring_archive_position_resolver(void) {
    uint8_t *addr = sig_scan(image_base, image_size, "48 83 7B 20 08 48 8D 4B 08 72 03 48 8B 09 4C 8B 4B 18 41 B8 05 00 00 00 4D 3B C8");
    ml_hook_result_t result;
    if (!addr) {
        ML_LOG_WARN(L"eldenring", L"archive position resolver signature not found");
        return false;
    }
    addr += *(int32_t*)(addr - 4);
    while (*addr == 0xE9) {
        addr += *(int32_t*)(addr + 1) + 5;
    }
    result = ml_hook_install(addr, (void *)&map_archive_path, (void **)&old_map_archive_path);
    if (result == ML_HOOK_APPLIED) archive_resolver_hook_target = addr;
    ml_log_write(result == ML_HOOK_APPLIED ? ML_LOG_LEVEL_INFO : ML_LOG_LEVEL_WARN,
                 L"eldenring", L"archive position resolver hook %hs", ml_hook_result_name(result));
    return result == ML_HOOK_APPLIED;
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
    void *steam_api_init;
    ml_hook_result_t result;
    if (steam_api == NULL) {
        ML_LOG_WARN(L"eldenring", L"could not load steam_api64.dll for deferred hooks");
        return false;
    }
    steam_api_init = (void *)GetProcAddress(steam_api, "SteamAPI_Init");
    result = ml_hook_install(steam_api_init, (void *)&SteamAPI_Init_hooked, (void **)&old_SteamAPI_Init);
    if (result == ML_HOOK_APPLIED) steam_api_init_hook_target = steam_api_init;
    ml_log_write(result == ML_HOOK_APPLIED ? ML_LOG_LEVEL_INFO : ML_LOG_LEVEL_WARN,
                 L"eldenring", L"deferred SteamAPI_Init hook %hs", ml_hook_result_name(result));
    return result == ML_HOOK_APPLIED;
}

static void configure_save_mapping(const ml_game_descriptor_t *game) {
    bool want_main = config.replaced_save_filename[0] != L'\0';
    bool want_coop = config.replaced_seamless_coop_save_filename[0] != L'\0';
    if (!want_main && !want_coop) {
        ML_LOG_INFO(L"eldenring", L"save mapping NOT_REQUESTED");
        return;
    }
    if (!ml_save_mapping_init_root(game)) {
        ML_LOG_WARN(L"eldenring", L"save mapping initialization failed");
        return;
    }
    /* ER0000.sl2 is the main save; ER0000.co2 is the Seamless Co-op save. */
    if (want_main && !ml_save_mapping_add_extension(L".sl2", config.replaced_save_filename)) {
        ML_LOG_WARN(L"eldenring", L"main save mapping registration failed");
    }
    if (want_coop && !ml_save_mapping_add_extension(L".co2", config.replaced_seamless_coop_save_filename)) {
        ML_LOG_WARN(L"eldenring", L"seamless coop save mapping registration failed");
    }
}

bool eldenring_install(void) {
    const ml_game_descriptor_t *game = ml_game_context_get();
    bool needs_file_hooks;
    int modcount;
    if (game == NULL || game->id != ML_GAME_ELDEN_RING) return false;

    game_running = true;
    image_base = get_module_image_base(NULL, &image_size);
    er_log(L"install start: image_base=%p image_size=%zu prevent_regulation_save_write=%d patch_mem=%d",
           image_base, image_size, config.prevent_regulation_save_write ? 1 : 0, config.patch_mem ? 1 : 0);

    configure_save_mapping(game);

    if (game->runtime_ready_trigger == ML_RUNTIME_READY_STEAM_API_INIT) {
        install_steamapi_deferred_hook();
    } else {
        er_log(L"runtime-ready trigger is unavailable");
    }

    async_operations_thread_handle = CreateThread(NULL, 0, async_operation_thread, NULL, 0, NULL);

    modcount = mods_count();
    /* Route the game's file APIs through the shared Win32 VFS hooks when mods are
     * loaded or a save file is being remapped. */
    needs_file_hooks = modcount > 0 || config.replaced_save_filename[0] != L'\0' ||
                       config.replaced_seamless_coop_save_filename[0] != L'\0';
    if (needs_file_hooks && !ml_win32_file_hooks_install()) {
        ML_LOG_WARN(L"eldenring", L"Win32 VFS hook installation failed");
    }
    /* Do not hook the archive resolver if no mod is added, to improve game
     * performance during loading. */
    if (modcount > 0) {
        if (!hook_eldenring_archive_position_resolver()) return false;
    }
    return true;
}

void eldenring_uninstall(void) {
    bool runtime_hook_removed = true;
    er_log(L"uninstall start");
    game_running = false;

    if (!ml_asset_hooks_uninstall()) {
        ML_LOG_WARN(L"eldenring", L"one or more asset hooks could not be removed");
    }
    ml_win32_file_hooks_uninstall();
    ml_save_mapping_uninit();

    if (archive_resolver_hook_target != NULL) {
        MH_STATUS status = MH_RemoveHook(archive_resolver_hook_target);
        if (status == MH_OK || status == MH_ERROR_NOT_CREATED) {
            archive_resolver_hook_target = NULL;
            old_map_archive_path = NULL;
        } else {
            ML_LOG_WARN(L"eldenring", L"failed to remove archive resolver hook at %p: %d",
                        archive_resolver_hook_target, status);
        }
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
    if (async_operations_thread_handle != NULL) CloseHandle(async_operations_thread_handle);
    async_operations_thread_handle = NULL;
}
