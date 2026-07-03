/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 *
 * C11 port of from/game_data.hpp. Offsets are verified to match the
 * merchant's reverse engineering byte-for-byte.
 */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum er_menu_sort_e {
    ER_MENU_SORT_ITEM_TYPE_ASCENDING = 0x80005141u,
} er_menu_sort_t;

#define ER_SORT_INDEX_ALL_ITEMS 12

typedef struct er_player_game_data_s {
    unsigned char unk[0xda];
    unsigned char max_reinforce_level;
} er_player_game_data_t;

typedef struct er_cs_menu_system_save_load_s {
    unsigned char unk[0x1438];
    uint32_t sorts[20];
} er_cs_menu_system_save_load_t;

typedef struct er_game_data_man_s {
    unsigned char unk1[0x8];
    er_player_game_data_t *player_game_data;
    unsigned char unk2[0x50];
    er_cs_menu_system_save_load_t *menu_system_save_load;
} er_game_data_man_t;

#ifdef __cplusplus
}
#endif