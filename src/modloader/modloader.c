/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "config.h"
#include "gamehook.h"
#include "mod.h"
#include "extdll.h"
#include "lifecycle.h"
#include "log.h"

#include "game/game.h"

#include "process/image.h"

#include "patches/window_flash.h"

#include "proxy/winhttp.h"
#include "proxy/dxgi.h"
#include "proxy/dinput8.h"

#include <MinHook.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

HMODULE module_instance = NULL;
typedef int (WINAPI*entrypoint_t)(void);
static entrypoint_t orig_entrypoint = NULL;

static void load_extdlls_after_runtime(ml_lifecycle_phase_t phase, void *userp) {
    (void)phase;
    (void)userp;
    extdlls_load_all();
}

static void modloader_init(void) {
    load_winhttp_proxy();
    load_dxgi_proxy();
    load_dinput8_proxy();
    ml_lifecycle_init();
    ml_lifecycle_advance(ML_LIFECYCLE_PHASE_PRE_ENTRY_SAFE);
    ml_window_flash_install();
    config_init(module_instance);
    mods_init();
    config_load();
    extdlls_prepare();
    gamehook_install();
    extdlls_load_early();
    if (ml_game_context_get() != NULL &&
        ml_game_context_get()->runtime_ready_trigger == ML_RUNTIME_READY_STEAM_API_INIT) {
        if (!ml_lifecycle_on_phase(ML_LIFECYCLE_PHASE_AFTER_RUNTIME_INIT,
                                   load_extdlls_after_runtime, NULL)) {
            ML_LOG_WARN(L"extdll", L"could not schedule external DLL loading after SteamAPI_Init");
        }
    } else {
        /* Preserve loading for unsupported game contexts without a runtime trigger. */
        extdlls_load_all();
    }
}

__declspec(dllexport) DWORD WINAPI YAFSMLInit(LPVOID parameter) {
    UNREFERENCED_PARAMETER(parameter);
    if (MH_Initialize() != MH_OK) return 0;
    modloader_init();
    return 1;
}

int WINAPI new_entrypoint(void) {
    modloader_init();
    return orig_entrypoint();
}

BOOL APIENTRY DllMain(const HMODULE module, const DWORD ul_reason_for_call, LPVOID reserved) {
    UNREFERENCED_PARAMETER(reserved);

    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(module);
            module_instance = module;
            {
                wchar_t remote_init[2];
                if (GetEnvironmentVariableW(L"YAFSML_REMOTE_INIT", remote_init, 2) != 0) break;
            }
            {
                if (MH_Initialize() != MH_OK) break;
                void *old_entrypoint = get_module_entrypoint(NULL);
                if (old_entrypoint == NULL ||
                    MH_CreateHook(old_entrypoint, new_entrypoint, (LPVOID*)&orig_entrypoint) != MH_OK ||
                    MH_EnableHook(old_entrypoint) != MH_OK) {
                    return FALSE;
                }
            }
            break;
        case DLL_PROCESS_DETACH:
            /* WARNING: FreeLibrary / MH_Uninitialize under loader lock is risky.
               Acceptable here because this only runs on game process exit. */
            extdlls_unload_all();
            gamehook_uninstall();
            mods_uninit();
            ml_lifecycle_uninit();
            break;
        default:
            break;
    }

    return TRUE;
}
