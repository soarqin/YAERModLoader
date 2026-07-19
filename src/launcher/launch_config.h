/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include "game/game.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include <stdbool.h>
#include <stddef.h>
#include <wchar.h>

typedef enum ml_launcher_game_config_result_e {
    ML_LAUNCHER_GAME_CONFIG_NOT_SPECIFIED,
    ML_LAUNCHER_GAME_CONFIG_FOUND,
    ML_LAUNCHER_GAME_CONFIG_INVALID,
    ML_LAUNCHER_GAME_CONFIG_ERROR,
} ml_launcher_game_config_result_t;

ml_launcher_game_config_result_t ml_launcher_game_from_ini_string(
    const char *contents, const ml_game_descriptor_t **game,
    wchar_t *invalid_key, size_t invalid_key_count);
ml_launcher_game_config_result_t ml_launcher_game_from_ini_file(
    const wchar_t *path, const ml_game_descriptor_t **game,
    wchar_t *invalid_key, size_t invalid_key_count);
const ml_game_descriptor_t *ml_launcher_select_game(
    const ml_game_descriptor_t *explicit_game,
    const ml_game_descriptor_t *config_game);
bool ml_launcher_resolve_config_path(wchar_t path[MAX_PATH],
                                     const wchar_t *module_dir,
                                     const wchar_t *requested_path);
