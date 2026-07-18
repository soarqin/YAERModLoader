#include "darksouls3.h"
#include "log.h"

#include "asset_hooks.h"
#include "common.h"
#include "save_mapping.h"
#include "win32_hooks.h"
#include "properties.h"

#include "modloader/config.h"
#include "modloader/hook.h"
#include "modloader/lifecycle.h"
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
static volatile LONG runtime_ready_reached;
static bool assets_requested_at_start;

static BOOL CALLBACK install_after_runtime(PINIT_ONCE once, PVOID parameter, PVOID *context) {
    const ml_game_descriptor_t *game = ml_game_context_get();
    bool wwise_requested = common_wwise_requested();
    bool assets_requested = assets_requested_at_start;
    bool assets_applied = !assets_requested;
    bool wwise_applied;
    (void)once;
    (void)parameter;
    (void)context;

    if (!ml_lifecycle_advance(ML_LIFECYCLE_PHASE_AFTER_RUNTIME_INIT)) {
        ML_LOG_WARN(L"darksouls3", L"AFTER_RUNTIME_INIT lifecycle advance failed");
    }
    if (assets_requested) assets_applied = ml_asset_hooks_install(game, image_base, image_size);
    ml_log_write(assets_applied ? ML_LOG_LEVEL_INFO : ML_LOG_LEVEL_WARN,
                 L"darksouls3", assets_requested
                     ? (assets_applied
                         ? L"AFTER_RUNTIME_INIT reached; asset initialization hook APPLIED"
                         : L"AFTER_RUNTIME_INIT reached; asset initialization hook HOOK_FAILED")
                     : L"AFTER_RUNTIME_INIT reached; asset capability NOT_REQUESTED");
    wwise_applied = common_install_wwise();
    ml_log_write(wwise_applied ? ML_LOG_LEVEL_INFO : ML_LOG_LEVEL_WARN,
                 L"darksouls3", wwise_applied
                     ? (wwise_requested ? L"Wwise capability APPLIED" : L"Wwise capability NOT_REQUESTED")
                     : L"Wwise capability HOOK_FAILED");
    InterlockedExchange(&runtime_ready_reached, 1);
    return TRUE;
}

static bool __cdecl steam_api_init_hooked(void) {
    bool result = old_steam_api_init();
    if (result && !InitOnceExecuteOnce(&after_runtime_once, install_after_runtime, NULL, NULL)) {
        ML_LOG_WARN(L"darksouls3", L"AFTER_RUNTIME_INIT setup failed; deferred initialization will retry");
    }
    return result;
}

static bool install_runtime_ready_hook(void) {
    HMODULE steam_api = GetModuleHandleW(L"steam_api64.dll");
    void *steam_api_init = steam_api == NULL ? NULL : (void *)GetProcAddress(steam_api, "SteamAPI_Init");
    ml_hook_result_t result = ml_hook_install(steam_api_init, steam_api_init_hooked,
                                              (void **)&old_steam_api_init);
    if (result == ML_HOOK_APPLIED) runtime_ready_hook_target = steam_api_init;
    ml_log_write(result == ML_HOOK_APPLIED ? ML_LOG_LEVEL_INFO : ML_LOG_LEVEL_WARN,
                 L"darksouls3", L"SteamAPI_Init runtime-ready hook %hs", ml_hook_result_name(result));
    return result == ML_HOOK_APPLIED;
}

bool darksouls3_install(void) {
    const ml_game_descriptor_t *game = ml_game_context_get();
    bool result = true;
    bool needs_file_hooks;
    bool common_applied;
    if (game == NULL || game->id != ML_GAME_DARK_SOULS_3 ||
        game->support_level != ML_SUPPORT_EXPERIMENTAL ||
        game->runtime_ready_trigger != ML_RUNTIME_READY_STEAM_API_INIT) return false;

    ML_LOG_WARN(L"darksouls3", L"experimental adapter enabled; dearxan is not required or scheduled");
    if (ml_asset_hooks_loose_params_present(game)) {
        if (ml_properties_set_loose_params(true)) {
            ML_LOG_INFO(L"darksouls3", L"loose param property override scheduled");
        } else {
            ML_LOG_WARN(L"darksouls3", L"loose param property override HOOK_FAILED");
            result = false;
        }
    } else {
        (void)ml_properties_set_loose_params(false);
        ML_LOG_INFO(L"darksouls3", L"loose param property override NOT_REQUESTED");
    }
    needs_file_hooks = mods_count() > 0 || config.replaced_save_filename[0] != L'\0';
    assets_requested_at_start = game != NULL && ml_asset_hooks_requested();
    if (config.replaced_save_filename[0] == L'\0') {
        ML_LOG_INFO(L"darksouls3", L"save mapping NOT_REQUESTED");
    } else if (ml_save_mapping_init(game, config.replaced_save_filename)) {
        ML_LOG_INFO(L"darksouls3", L"save mapping APPLIED");
    } else {
        ML_LOG_WARN(L"darksouls3", L"save mapping HOOK_FAILED");
        result = false;
    }
    if (!needs_file_hooks) {
        ML_LOG_INFO(L"darksouls3", L"Win32 VFS hooks NOT_REQUESTED");
    } else if (ml_win32_file_hooks_install()) {
        ML_LOG_INFO(L"darksouls3", L"Win32 VFS hooks APPLIED");
    } else {
        ML_LOG_WARN(L"darksouls3", L"Win32 VFS hooks HOOK_FAILED");
        result = false;
    }

    image_base = get_module_image_base(NULL, &image_size);
    if (image_base == NULL || image_size == 0 || !install_runtime_ready_hook()) {
        ML_LOG_WARN(L"darksouls3", L"runtime-ready trigger HOOK_FAILED; deferred capabilities disabled");
        result = false;
    }
    common_applied = common_install_ime();
    ml_log_write(common_applied ? ML_LOG_LEVEL_INFO : ML_LOG_LEVEL_WARN,
                 L"darksouls3", common_applied
                     ? (config.enable_ime ? L"IME capability APPLIED" : L"IME capability SKIPPED_DISABLED")
                     : L"IME capability HOOK_FAILED");
    ML_LOG_INFO(L"darksouls3", common_wwise_requested()
        ? L"Wwise capability REQUESTED" : L"Wwise capability NOT_REQUESTED");
    ML_LOG_INFO(L"darksouls3", config.skip_intro
        ? L"SPRJ Logo capability REQUESTED" : L"SPRJ Logo capability SKIPPED_DISABLED");
    ML_LOG_INFO(L"darksouls3", L"offline property capability REQUESTED");
    ML_LOG_INFO(L"darksouls3", config.prevent_regulation_save_write
        ? L"regulation protection capability REQUESTED"
        : L"regulation protection capability SKIPPED_DISABLED");
    ML_LOG_INFO(L"darksouls3", config.patch_mem
        ? L"heap allocator capability REQUESTED"
        : L"heap allocator capability SKIPPED_DISABLED");
    ML_LOG_INFO(L"darksouls3", config.boot_boost && assets_requested_at_start
        ? L"BootBoost capability REQUESTED"
        : L"BootBoost capability NOT_REQUESTED");
    return common_applied && result;
}

void darksouls3_uninstall(void) {
    bool runtime_hook_removed = true;
    if (runtime_ready_hook_target != NULL) {
        MH_STATUS status = MH_RemoveHook(runtime_ready_hook_target);
        runtime_hook_removed = status == MH_OK || status == MH_ERROR_NOT_CREATED;
        if (!runtime_hook_removed) {
            ML_LOG_WARN(L"darksouls3", L"failed to remove runtime-ready hook at %p: %d",
                        runtime_ready_hook_target, status);
        }
    }
    if (!runtime_hook_removed) return;
    if (InterlockedCompareExchange(&runtime_ready_reached, 0, 0) == 0) {
        ML_LOG_WARN(L"darksouls3", L"runtime-ready capabilities DEFERRED_NOT_REACHED");
    }
    if (!ml_asset_hooks_uninstall()) {
        ML_LOG_WARN(L"darksouls3", L"one or more asset hooks could not be removed");
    }
    ml_win32_file_hooks_uninstall();
    ml_save_mapping_uninit();
    common_uninstall();
    runtime_ready_hook_target = NULL;
    old_steam_api_init = NULL;
    image_base = NULL;
    image_size = 0;
    runtime_ready_reached = 0;
    assets_requested_at_start = false;
    InitOnceInitialize(&after_runtime_once);
}
