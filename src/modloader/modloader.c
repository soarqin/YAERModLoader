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
#include "detours_subset.h"

#include "proxy/winhttp.h"
#include "proxy/dxgi.h"
#include "proxy/dinput8.h"

#include <MinHook.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

HMODULE module_instance = NULL;
typedef int (WINAPI*entrypoint_t)(void);
static entrypoint_t orig_entrypoint = NULL;

int WINAPI new_entrypoint(void) {
    load_winhttp_proxy();
    load_dxgi_proxy();
    load_dinput8_proxy();
    config_init(module_instance);
    mods_init();
    config_load();
    gamehook_install();
    extdlls_load_all();
    return orig_entrypoint();
}

BOOL APIENTRY DllMain(const HMODULE module, const DWORD ul_reason_for_call, LPVOID reserved) {
    UNREFERENCED_PARAMETER(reserved);

    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(module);
            DetourRestoreAfterWith();
            module_instance = module;
            {
                MH_Initialize();
                void *old_entrypoint = DetourGetEntryPoint(NULL);
                MH_CreateHook(old_entrypoint, new_entrypoint, (LPVOID*)&orig_entrypoint);
                MH_EnableHook(old_entrypoint);
            }
            break;
        case DLL_PROCESS_DETACH:
            extdlls_unload_all();
            gamehook_uninstall();
            mods_uninit();
            break;
        default:
            break;
    }

    return TRUE;
}
