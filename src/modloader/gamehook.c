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

#include <stdio.h>

bool gamehook_install() {
    steamapi_init();
    bool result = common_install() && eldenring_install();
    MH_STATUS status = MH_EnableHook(MH_ALL_HOOKS);
    if (status != MH_OK) {
        fwprintf(stderr, L"WARNING: MH_EnableHook(MH_ALL_HOOKS) failed: %d\n", status);
    } else {
        fwprintf(stderr, L"NOTE: MH_EnableHook(MH_ALL_HOOKS) succeeded\n");
        fflush(stderr);
    }
    return result;
}

void gamehook_uninstall() {
    eldenring_uninstall();
    common_uninstall();

    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
    steamapi_uninit();
}
