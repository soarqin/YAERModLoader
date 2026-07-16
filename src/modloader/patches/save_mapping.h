#pragma once

#include "game/game.h"

#include <stdbool.h>
#include <wchar.h>

bool ml_save_mapping_init(const ml_game_descriptor_t *game, const wchar_t *override_name);
bool ml_save_mapping_route(const wchar_t *path, const wchar_t **mapped_path);
void ml_save_mapping_uninit(void);
