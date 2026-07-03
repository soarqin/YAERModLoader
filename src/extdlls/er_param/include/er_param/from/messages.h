/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 *
 * C11 port of from/messages.hpp. er_msgbnd_t maps to from::msgbnd.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum er_msgbnd_e {
    ER_MSGBND_goods_name         = 10,
    ER_MSGBND_weapon_name        = 11,
    ER_MSGBND_protector_name     = 12,
    ER_MSGBND_accessory_name     = 13,
    ER_MSGBND_goods_info         = 20,
    ER_MSGBND_accessory_info     = 23,
    ER_MSGBND_goods_caption      = 24,
    ER_MSGBND_accessory_caption  = 27,
    ER_MSGBND_event_text_for_talk= 33,
    ER_MSGBND_gem_name           = 35,
    ER_MSGBND_menu_text          = 200,
    ER_MSGBND_line_help          = 201,
    ER_MSGBND_dialogues          = 204,
    ER_MSGBND_dlc_weapon_name    = 310,
    ER_MSGBND_dlc_protector_name = 313,
    ER_MSGBND_dlc_accessory_name = 316,
    ER_MSGBND_dlc_goods_name     = 319,
    ER_MSGBND_dlc_gem_name       = 322,
} er_msgbnd_t;

typedef struct er_msg_repository_imp_s er_msg_repository_imp_t;

#ifdef __cplusplus
}
#endif