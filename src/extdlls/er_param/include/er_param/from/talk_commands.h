/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 *
 * C11 port of from/talk_commands.hpp. Each command is a {bank, id} pair.
 * The actual definitions live in talk_commands.c (single definition site).
 */

#pragma once

#include "ezstate.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Talk command {bank, id} constants. Defined as `static const` so each
 * translation unit gets its own copy (header-only, no link dependency on
 * er_param.dll for these). */
static const er_ezstate_command_t ER_TALK_CMD_close_shop_message    = {1, 12};
static const er_ezstate_command_t ER_TALK_CMD_set_event_flag        = {1, 11};
static const er_ezstate_command_t ER_TALK_CMD_show_shop_message     = {1, 10};
static const er_ezstate_command_t ER_TALK_CMD_clear_talk_list_data  = {1, 20};
static const er_ezstate_command_t ER_TALK_CMD_open_regular_shop     = {1, 22};
static const er_ezstate_command_t ER_TALK_CMD_add_talk_list_data    = {1, 19};
static const er_ezstate_command_t ER_TALK_CMD_add_talk_list_data_alt= {1, 149};
static const er_ezstate_command_t ER_TALK_CMD_add_talk_list_data_if = {5, 19};
static const er_ezstate_command_t ER_TALK_CMD_acquire_gesture       = {1, 131};

#ifdef __cplusplus
}
#endif