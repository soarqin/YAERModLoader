#include "sekiro.h"
#include "log.h"

#include "asset_hooks.h"
#include "common.h"
#include "save_mapping.h"
#include "win32_hooks.h"

#include "modloader/config.h"
#include "modloader/lifecycle.h"
#include "modloader/hook.h"
#include "modloader/mod.h"

#include "game/game.h"
#include "process/image.h"

#include <MinHook.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef bool (__cdecl *steam_api_init_t)(void);

static steam_api_init_t old_steam_api_init;
static INIT_ONCE after_runtime_once = INIT_ONCE_STATIC_INIT;
static void *image_base;
static size_t image_size;
static void *runtime_ready_hook_target;

static BOOL CALLBACK install_after_runtime(PINIT_ONCE once, PVOID parameter, PVOID *context) {
    const ml_game_descriptor_t *game = ml_game_context_get();
    bool assets_requested = game != NULL && mods_count() > 0;
    bool assets_applied = !assets_requested;
    (void)once;
    (void)parameter;
    (void)context;

    if (assets_requested) {
        assets_applied = ml_asset_hooks_install(game, image_base, image_size);
    }
    if (assets_requested) {
        ml_log_write(assets_applied ? ML_LOG_LEVEL_INFO : ML_LOG_LEVEL_WARN,
                     L"sekiro", assets_applied
                         ? L"AFTER_RUNTIME_INIT reached; asset capability APPLIED"
                         : L"AFTER_RUNTIME_INIT reached; asset capability HOOK_FAILED");
    } else {
        ML_LOG_INFO(L"sekiro", L"AFTER_RUNTIME_INIT reached; asset capability NOT_REQUESTED");
    }
    if (!assets_applied) return FALSE;
    if (!ml_lifecycle_advance(ML_LIFECYCLE_PHASE_AFTER_RUNTIME_INIT)) {
        ML_LOG_WARN(L"sekiro", L"AFTER_RUNTIME_INIT lifecycle advance failed");
    }
    return TRUE;
}

static bool __cdecl steam_api_init_hooked(void) {
    bool result = old_steam_api_init();
    if (result && !InitOnceExecuteOnce(&after_runtime_once, install_after_runtime, NULL, NULL)) {
        ML_LOG_WARN(L"sekiro", L"AFTER_RUNTIME_INIT setup failed; deferred initialization will retry");
    }
    return result;
}

static bool install_runtime_ready_hook(void) {
    HMODULE steam_api = LoadLibraryW(L"steam_api64.dll");
    void *steam_api_init;
    ml_hook_result_t result;

    if (steam_api == NULL) return false;
    steam_api_init = (void *)GetProcAddress(steam_api, "SteamAPI_Init");
    result = ml_hook_install(steam_api_init, steam_api_init_hooked, (void **)&old_steam_api_init);
    if (result == ML_HOOK_APPLIED) runtime_ready_hook_target = steam_api_init;
    ml_log_write(result == ML_HOOK_APPLIED ? ML_LOG_LEVEL_INFO : ML_LOG_LEVEL_WARN,
                 L"sekiro", L"SteamAPI_Init runtime-ready hook %hs", ml_hook_result_name(result));
    return result == ML_HOOK_APPLIED;
}

bool sekiro_install(void) {
    const ml_game_descriptor_t *game = ml_game_context_get();
    bool result = true;
    bool needs_file_hooks;
    if (game == NULL || game->id != ML_GAME_SEKIRO ||
        game->runtime_ready_trigger != ML_RUNTIME_READY_STEAM_API_INIT) return false;

    needs_file_hooks = mods_count() > 0 || config.replaced_save_filename[0] != L'\0';
    if (config.replaced_save_filename[0] != L'\0' &&
        !ml_save_mapping_init(game, config.replaced_save_filename)) {
        ML_LOG_WARN(L"sekiro", L"save mapping initialization failed");
        result = false;
    }
    if (needs_file_hooks && !ml_win32_file_hooks_install()) {
        ML_LOG_WARN(L"sekiro", L"Win32 VFS hook installation failed");
        result = false;
    }
    image_base = get_module_image_base(NULL, &image_size);
    if (image_base == NULL || image_size == 0 || !install_runtime_ready_hook()) {
        ML_LOG_WARN(L"sekiro", L"runtime-ready trigger installation failed; deferred capabilities disabled");
        result = false;
    }
    return common_install() && result;
}

void sekiro_uninstall(void) {
    bool runtime_hook_removed = true;
    if (!ml_asset_hooks_uninstall()) {
        ML_LOG_WARN(L"sekiro", L"one or more asset hooks could not be removed");
    }
    ml_win32_file_hooks_uninstall();
    ml_save_mapping_uninit();
    common_uninstall();
    if (runtime_ready_hook_target != NULL) {
        MH_STATUS status = MH_RemoveHook(runtime_ready_hook_target);
        runtime_hook_removed = status == MH_OK || status == MH_ERROR_NOT_CREATED;
        if (!runtime_hook_removed) {
            ML_LOG_WARN(L"sekiro", L"failed to remove runtime-ready hook at %p: %d",
                        runtime_ready_hook_target, status);
        }
    }
    if (runtime_hook_removed) {
        runtime_ready_hook_target = NULL;
        old_steam_api_init = NULL;
        image_base = NULL;
        image_size = 0;
        InitOnceInitialize(&after_runtime_once);
    }
}
