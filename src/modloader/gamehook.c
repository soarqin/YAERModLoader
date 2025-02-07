/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "gamehook.h"

#include "steam/api.h"
#include "patches/common.h"
#include "patches/eldenring.h"

#include <MinHook.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <wchar.h>

bool gamehook_install() {
    steamapi_init();
    MH_EnableHook(MH_ALL_HOOKS);

    return common_install() && eldenring_install();
}

void gamehook_uninstall() {
    eldenring_uninstall();
    common_uninstall();

    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
    steamapi_uninit();
}
