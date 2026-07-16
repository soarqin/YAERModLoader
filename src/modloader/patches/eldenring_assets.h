/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include "game/game.h"

#include <stdbool.h>

bool from_assets_install(const ml_game_descriptor_t *game, void *image_base, size_t image_size);
bool from_assets_uninstall(void);
