/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "gamehook.h"

#include "steam/api.h"
#include "config.h"
#include "patches/common.h"
#include "patches/eldenring.h"
#include "patches/logo.h"
#include "lifecycle.h"

#include "game/game.h"

#include <MinHook.h>

#include <stdio.h>

static void install_logo_after_runtime(ml_lifecycle_phase_t phase, void *userp) {
    (void)phase;
    ml_logo_skip_install((const ml_game_descriptor_t *)userp);
}

bool gamehook_install() {
    if (!ml_game_context_init()) {
        fwprintf(stderr, L"WARNING: unsupported or mismatched game process; game hooks are disabled\n");
        return false;
    }
    const ml_game_descriptor_t *game = ml_game_context_get();
    ml_lifecycle_advance(ML_LIFECYCLE_PHASE_BEFORE_MAIN);
    if (game->id != ML_GAME_ELDEN_RING) {
        fwprintf(stderr, L"WARNING: %ls adapter is not implemented; game hooks are disabled\n", game->title);
        return false;
    }
    if (config.skip_intro &&
        !ml_lifecycle_on_phase(ML_LIFECYCLE_PHASE_AFTER_RUNTIME_INIT, install_logo_after_runtime, (void *)game)) {
        fwprintf(stderr, L"WARNING: [logo] could not schedule Logo redirect\n");
    }
    steamapi_init();
    bool result = common_install() && eldenring_install();
    return result;
}

void gamehook_uninstall() {
    const ml_game_descriptor_t *game = ml_game_context_get();
    if (game != NULL && game->id == ML_GAME_ELDEN_RING) {
        eldenring_uninstall();
        common_uninstall();
    }

    MH_Uninitialize();
    steamapi_uninit();
}
