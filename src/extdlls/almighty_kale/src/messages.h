/*
 * almighty_kale - 1:1 C port of the Glorious Merchant mod
 * (https://github.com/ThomasJClark/elden-ring-glorious-merchant, MIT).
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <er_param/from/messages.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AK_MSG_weapons              99999000
#define AK_MSG_armor                99999001
#define AK_MSG_spells               99999002
#define AK_MSG_talismans            99999003
#define AK_MSG_ammunition           99999004
#define AK_MSG_ashes_of_war         99999005
#define AK_MSG_consumables          99999006
#define AK_MSG_spirit_summons       99999007
#define AK_MSG_materials            99999008
#define AK_MSG_miscellaneous_items  99999009
#define AK_MSG_gestures             99999010
#define AK_MSG_browse_inventory     99999030
#define AK_MSG_items                99999031
#define AK_MSG_browse_cut_content   99999032
#define AK_MSG_goods                99999033
#define AK_MSG_unlock               99999100
#define AK_MSG_dlc                  99999200

#define AK_MSG_about_kale           28000002
#define AK_MSG_leave                20000009
#define AK_MSG_purchase             20000010
#define AK_MSG_sell                 20000011

typedef struct ak_msg_entry_s {
    int id;
    const wchar_t *text;
} ak_msg_entry_t;

typedef struct ak_lang_messages_s {
    const char *lang;
    const ak_msg_entry_t *entries;
    size_t entries_count;
} ak_lang_messages_t;

extern const ak_lang_messages_t ak_event_text_for_talk_by_lang[];
extern const size_t ak_event_text_for_talk_by_lang_count;

void ak_setup_messages(void);
const wchar_t *ak_get_message(er_msgbnd_t bnd_id, int msg_id);
void ak_set_shop_open(bool shop_open);

#ifdef __cplusplus
}
#endif