/*
 * almighty_kale - 1:1 C port of the Glorious Merchant mod
 * (https://github.com/ThomasJClark/elden-ring-glorious-merchant, MIT).
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 *
 * C11 port of ermerchant_talkscript_utils.hpp. Builds the modded ESD state
 * trees (browse inventory / cut content submenus, gesture unlock states) that
 * are patched into Kales dialogue tree.
 */

#pragma once

#include <er_param/from/ezstate.h>
#include <er_param/from/talk_commands.h>
#include <er_param/from/messages.h>
#include "messages.h"
#include "shops.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Parse an ESD expression containing only a 1 or 4 byte integer.
 * arg.data is the byte buffer, arg.count its length. */
int ak_get_int_value(er_ezstate_arg_t arg);

/* Build a 6-byte int value expression into a caller-provided 6-byte buffer.
 * Returns the arg span referencing that buffer. */
er_ezstate_arg_t ak_make_int_value_into(unsigned char *buf6, int value);

extern er_ezstate_transition_t ak_main_menu_return_transition;
extern er_ezstate_state_t ak_browse_inventory_state;
extern er_ezstate_state_t ak_browse_inventory_successor_state;
extern er_ezstate_state_t ak_browse_inventory_items_state;
extern er_ezstate_state_t ak_browse_inventory_items_successor_state;
extern er_ezstate_state_t ak_browse_dlc_inventory_state;
extern er_ezstate_state_t ak_browse_dlc_inventory_successor_state;
extern er_ezstate_state_t ak_browse_dlc_inventory_items_state;
extern er_ezstate_state_t ak_browse_dlc_inventory_items_successor_state;
extern er_ezstate_state_t ak_browse_cut_content_state;
extern er_ezstate_state_t ak_browse_cut_content_successor_state;
extern er_ezstate_state_t ak_gestures_state;
extern er_ezstate_state_t ak_gestures_successor_state;
extern er_ezstate_state_t ak_gestures_unlock_state;
extern er_ezstate_state_t ak_dlc_gestures_state;
extern er_ezstate_state_t ak_dlc_gestures_successor_state;
extern er_ezstate_state_t ak_dlc_gestures_unlock_state;
extern er_ezstate_state_t ak_cut_gestures_state;
extern er_ezstate_state_t ak_cut_gestures_successor_state;
extern er_ezstate_state_t ak_cut_gestures_unlock_state;

extern er_ezstate_transition_t ak_browse_inventory_transition;
extern er_ezstate_transition_t ak_browse_cut_content_transition;

extern er_ezstate_arg_t ak_browse_inventory_index_value;
extern er_ezstate_arg_t ak_browse_inventory_message_id_value;
extern er_ezstate_arg_t ak_browse_cut_content_index_value;
extern er_ezstate_arg_t ak_browse_cut_content_message_id_value;

/* Public builders (pool-backed) for appending menu entries. */
er_ezstate_arg_t *ak_new_add_talk_list_args_pub(int index, int message_id);
er_ezstate_event_t ak_make_event_pub(er_ezstate_command_t cmd, er_ezstate_arg_t *args, size_t args_count);

void ak_talkscript_utils_init(void);
void ak_talkscript_utils_uninit(void);

#ifdef __cplusplus
}
#endif