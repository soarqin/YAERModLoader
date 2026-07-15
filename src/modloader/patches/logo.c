/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "logo.h"

#include "process/fd4_step.h"

#include <stdio.h>

bool ml_logo_fd4_redirect(void **step_slot, void *next_step) {
    if (step_slot == NULL || next_step == NULL) return false;
    step_slot[0] = next_step;
    return true;
}

bool ml_logo_skip_install(const ml_game_descriptor_t *game) {
    bool result;

    if (game == NULL) return false;
    switch (game->logo_strategy) {
        case ML_LOGO_STRATEGY_FD4:
            result = ml_logo_fd4_redirect(fd4_step_find_slot(L"TitleStep::STEP_BeginLogo"),
                                          fd4_step_find(L"TitleStep::STEP_BeginTitle"));
            fwprintf(result ? stdout : stderr,
                     result
                         ? L"NOTE: [logo] FD4 TitleStep redirect APPLIED\n"
                         : L"WARNING: [logo] FD4 TitleStep redirect SIGNATURE_NOT_FOUND\n");
            return result;
        case ML_LOGO_STRATEGY_SPRJ:
            fwprintf(stderr, L"WARNING: [logo] SPRJ title step strategy UNSUPPORTED for %ls\n", game->title);
            return false;
        default:
            fwprintf(stderr, L"WARNING: [logo] strategy UNSUPPORTED for %ls\n", game->title);
            return false;
    }
}
