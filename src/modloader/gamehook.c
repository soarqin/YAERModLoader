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
#include "patches/allocator.h"
#include "patches/eldenring.h"
#include "patches/logo.h"
#include "patches/properties.h"
#include "patches/regulation.h"
#include "mimalloc_allocator.h"
#include "lifecycle.h"

#include "game/game.h"

#include <MinHook.h>

#include <stdio.h>

static void install_logo_after_runtime(ml_lifecycle_phase_t phase, void *userp) {
    (void)phase;
    ml_logo_skip_install((const ml_game_descriptor_t *)userp);
}

static void install_properties_after_runtime(ml_lifecycle_phase_t phase, void *userp) {
    (void)phase;
    ml_properties_install((const ml_game_descriptor_t *)userp);
}

static void install_regulation_after_runtime(ml_lifecycle_phase_t phase, void *userp) {
    (void)phase;
    ml_regulation_install((const ml_game_descriptor_t *)userp);
}

static void install_allocator_after_runtime(ml_lifecycle_phase_t phase, void *userp) {
    (void)phase;
    ml_allocator_install_after_runtime((const ml_game_descriptor_t *)userp, config.patch_mem_hook_cs_graphics);
}

bool gamehook_install() {
    if (!ml_game_context_init()) {
        fwprintf(stderr, L"WARNING: unsupported or mismatched game process; game hooks are disabled\n");
        return false;
    }
    const ml_game_descriptor_t *game = ml_game_context_get();
    if (config.patch_mem) {
        size_t heap_size_mb = config.patch_mem_heap_size != 0
            ? config.patch_mem_heap_size : MIMALLOC_DL_ALLOCATOR_DEFAULT_HEAP_SIZE_MB;
        ml_allocator_install_before_main(game, heap_size_mb);
        ml_lifecycle_on_phase(ML_LIFECYCLE_PHASE_AFTER_RUNTIME_INIT, install_allocator_after_runtime, (void *)game);
    }
    ml_lifecycle_advance(ML_LIFECYCLE_PHASE_BEFORE_MAIN);
    if (game->id != ML_GAME_ELDEN_RING) {
        fwprintf(stderr, L"WARNING: %ls adapter is not implemented; game hooks are disabled\n", game->title);
        return false;
    }
    if (config.skip_intro &&
        !ml_lifecycle_on_phase(ML_LIFECYCLE_PHASE_AFTER_RUNTIME_INIT, install_logo_after_runtime, (void *)game)) {
        fwprintf(stderr, L"WARNING: [logo] could not schedule Logo redirect\n");
    }
    if (!ml_lifecycle_on_phase(ML_LIFECYCLE_PHASE_AFTER_RUNTIME_INIT, install_properties_after_runtime, (void *)game)) {
        fwprintf(stderr, L"WARNING: [properties] could not schedule installation\n");
    }
    if (config.prevent_regulation_save_write &&
        !ml_lifecycle_on_phase(ML_LIFECYCLE_PHASE_AFTER_RUNTIME_INIT, install_regulation_after_runtime, (void *)game)) {
        fwprintf(stderr, L"WARNING: [regulation] could not schedule installation\n");
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
