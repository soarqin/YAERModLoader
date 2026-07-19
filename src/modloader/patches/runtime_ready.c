#include "runtime_ready.h"

#include "log.h"

#include "modloader/hook.h"

#include <MinHook.h>

typedef bool (__cdecl *steam_api_init_t)(void);

static steam_api_init_t old_steam_api_init;
static HMODULE steam_api_module;
static void *steam_api_init_hook_target;
static INIT_ONCE after_runtime_once = INIT_ONCE_STATIC_INIT;
static ml_runtime_ready_callback_t after_runtime_callback;
static const wchar_t *hook_log_scope;

static bool __cdecl steam_api_init_hooked(void) {
    bool result = old_steam_api_init();
    if (result && !InitOnceExecuteOnce(&after_runtime_once, after_runtime_callback, NULL, NULL)) {
        ML_LOG_WARN(hook_log_scope, L"AFTER_RUNTIME_INIT setup failed; deferred initialization will retry");
    }
    return result;
}

bool ml_runtime_ready_hook_install(const wchar_t *log_scope,
                                   ml_runtime_ready_callback_t callback) {
    void *steam_api_init;
    ml_hook_result_t result;

    if (log_scope == NULL || callback == NULL || steam_api_init_hook_target != NULL) return false;
    steam_api_module = LoadLibraryW(L"steam_api64.dll");
    steam_api_init = steam_api_module == NULL ? NULL :
        (void *)GetProcAddress(steam_api_module, "SteamAPI_Init");
    after_runtime_callback = callback;
    hook_log_scope = log_scope;
    result = ml_hook_install(steam_api_init, steam_api_init_hooked, (void **)&old_steam_api_init);
    if (result != ML_HOOK_APPLIED) {
        if (steam_api_module != NULL) FreeLibrary(steam_api_module);
        steam_api_module = NULL;
        after_runtime_callback = NULL;
        hook_log_scope = NULL;
        ml_log_write(ML_LOG_LEVEL_WARN, log_scope,
                     L"SteamAPI_Init runtime-ready hook %hs", ml_hook_result_name(result));
        return false;
    }
    steam_api_init_hook_target = steam_api_init;
    ML_LOG_INFO(log_scope, L"SteamAPI_Init runtime-ready hook APPLIED");
    return true;
}

bool ml_runtime_ready_hook_uninstall(const wchar_t *log_scope) {
    MH_STATUS status = MH_OK;
    if (steam_api_init_hook_target != NULL) {
        status = MH_RemoveHook(steam_api_init_hook_target);
        if (status != MH_OK && status != MH_ERROR_NOT_CREATED) {
            ML_LOG_WARN(log_scope, L"failed to remove runtime-ready hook at %p: %d",
                        steam_api_init_hook_target, status);
            return false;
        }
    }
    steam_api_init_hook_target = NULL;
    old_steam_api_init = NULL;
    after_runtime_callback = NULL;
    hook_log_scope = NULL;
    InitOnceInitialize(&after_runtime_once);
    if (steam_api_module != NULL) FreeLibrary(steam_api_module);
    steam_api_module = NULL;
    return true;
}
