/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    INIT_CS_REGULATION_MANAGER       = 1u << 0,
    INIT_SOLO_PARAM_REPOSITORY       = 1u << 1,
    INIT_MSG_REPOSITORY              = 1u << 2,
    INIT_GAME_DATA_MAN               = 1u << 3,
    INIT_LOOKUP_SHOP_MENU            = 1u << 4,
    INIT_LOOKUP_SHOP_LINEUP          = 1u << 5,
    INIT_MSG_REPOSITORY_LOOKUP_ENTRY = 1u << 6,
    INIT_EZSTATE_ENTER_STATE         = 1u << 7,
    INIT_EVENT_FLAG_GET              = 1u << 8,
    INIT_SELL_VALUE                  = 1u << 9,
    INIT_MAX_REPOSITORY_NUM          = 1u << 10,
    INIT_OPEN_REGULAR_SHOP           = 1u << 11,
} er_pointers_init_flag_t;

#define INIT_ALL_GAME \
    (INIT_MSG_REPOSITORY | INIT_GAME_DATA_MAN | INIT_LOOKUP_SHOP_MENU | \
     INIT_LOOKUP_SHOP_LINEUP | INIT_MSG_REPOSITORY_LOOKUP_ENTRY | \
     INIT_EZSTATE_ENTER_STATE | INIT_EVENT_FLAG_GET | INIT_SELL_VALUE | \
     INIT_MAX_REPOSITORY_NUM | INIT_OPEN_REGULAR_SHOP)

typedef struct {
    void *cs_regulation_manager;
    void *solo_param_repository;
    void *msg_repository;
    void *game_data_man;
    void *lookup_shop_menu;
    void *lookup_shop_lineup;
    void *msg_repository_lookup_entry;
    void *ezstate_enter_state;
    void *get_event_flag;
    void *get_sell_value;
    void *get_max_repository_num;
    void *open_regular_shop;
} er_pointers_t;

uint32_t er_pointers_init(uint32_t init);

extern er_pointers_t er_pointers;

#ifdef __cplusplus
}
#endif