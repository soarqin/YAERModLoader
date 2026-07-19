/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "game.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

static const ml_game_descriptor_t *current_game;

bool ml_game_context_init(void) {
    wchar_t expected[32];
    DWORD length;

    current_game = ml_game_detect_current_process();
    if (current_game == NULL) return false;

    length = GetEnvironmentVariableW(L"YAFSML_GAME", expected, 32);
    if (length != 0 && (length >= 32 || ml_game_by_key(expected) != current_game)) {
        current_game = NULL;
        return false;
    }
    return true;
}

const ml_game_descriptor_t *ml_game_context_get(void) {
    return current_game;
}
