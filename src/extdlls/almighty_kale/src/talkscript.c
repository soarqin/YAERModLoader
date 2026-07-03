/*
 * almighty_kale - 1:1 C port of the Glorious Merchant mod
 * (https://github.com/ThomasJClark/elden-ring-glorious-merchant, MIT).
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "talkscript.h"
#include "talkscript_utils.h"
#include "shops.h"
#include "messages.h"

#include <er_param/er_param_api.h>
#include <er_param/from/ezstate.h>
#include <er_param/from/talk_commands.h>

#include <modloader/extdll_api.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string.h>
#include <stddef.h>

extern modloader_ext_api_t *ak_the_api;
extern const er_param_api_t *ak_param_api;

static const unsigned char AK_GET_TALK_LIST_ENTRY_RESULT_FUNCTION = 23;

static er_ezstate_event_t ak_patched_event_array[100];
static er_ezstate_transition_t *ak_patched_transition_array[100];

typedef void (*ak_ezstate_enter_state_t)(er_ezstate_state_t *, er_ezstate_machine_impl_t *, void *);
static ak_ezstate_enter_state_t ak_orig_ezstate_enter_state = NULL;

static bool ak_patch_states(er_ezstate_state_group_t *state_group) {
    er_ezstate_event_t *add_menu1_event = NULL;
    er_ezstate_event_t *add_menu2_event = NULL;
    er_ezstate_event_t *about_kale_event = NULL;
    er_ezstate_state_t *add_menu_state = NULL;
    er_ezstate_state_t *menu_transition_state = NULL;

    for (size_t si = 0; si < state_group->states_count; si++) {
        er_ezstate_state_t *state = &state_group->states[si];
        for (size_t ei = 0; ei < state->entry_events_count; ei++) {
            er_ezstate_event_t *event = &state->entry_events[ei];
            int message_id = -1;
            if (event->command.bank == ER_TALK_CMD_add_talk_list_data.bank && event->command.id == ER_TALK_CMD_add_talk_list_data.id) {
                if (event->args_count > 1) message_id = ak_get_int_value(event->args[1]);
            } else if (event->command.bank == ER_TALK_CMD_add_talk_list_data_alt.bank && event->command.id == ER_TALK_CMD_add_talk_list_data_alt.id) {
                if (event->args_count > 1) message_id = ak_get_int_value(event->args[1]);
            } else if (event->command.bank == ER_TALK_CMD_add_talk_list_data_if.bank && event->command.id == ER_TALK_CMD_add_talk_list_data_if.id) {
                if (event->args_count > 2) message_id = ak_get_int_value(event->args[2]);
            } else {
                continue;
            }

            if (message_id == AK_MSG_purchase) {
                add_menu1_event = event;
            } else if (message_id == AK_MSG_sell) {
                add_menu2_event = event;
            } else if (message_id == AK_MSG_browse_inventory || message_id == AK_MSG_browse_cut_content) {
                return true;
            } else if (message_id == AK_MSG_about_kale) {
                about_kale_event = event;
                add_menu_state = state;
            }
        }

        for (size_t ti = 0; ti < state->transitions_count; ti++) {
            er_ezstate_transition_t *tr = state->transitions[ti];
            if (tr->evaluator_count > 1 && tr->evaluator[0] - 64 == AK_GET_TALK_LIST_ENTRY_RESULT_FUNCTION) {
                menu_transition_state = state;
                break;
            }
        }
    }

    if (!about_kale_event || !menu_transition_state ||
        ((!add_menu1_event || !add_menu2_event) && !add_menu_state)) {
        return false;
    }

    if (add_menu1_event && add_menu2_event) {
        add_menu1_event->args[0] = ak_browse_inventory_index_value;
        add_menu1_event->args[1] = ak_browse_inventory_message_id_value;
        add_menu2_event->args[0] = ak_browse_cut_content_index_value;
        add_menu2_event->args[1] = ak_browse_cut_content_message_id_value;
    } else if (add_menu_state) {
        er_ezstate_event_t *events = add_menu_state->entry_events;
        size_t ev_count = add_menu_state->entry_events_count;
        for (size_t i = 0; i < ev_count && i < 100; i++) {
            ak_patched_event_array[i] = events[i];
        }
        if (ev_count + 2 <= 100) {
            er_ezstate_arg_t *bi_args = ak_new_add_talk_list_args_pub(48, AK_MSG_browse_inventory);
            er_ezstate_arg_t *bc_args = ak_new_add_talk_list_args_pub(49, AK_MSG_browse_cut_content);
            ak_patched_event_array[ev_count] = ak_make_event_pub(ER_TALK_CMD_add_talk_list_data, bi_args, 3);
            ak_patched_event_array[ev_count + 1] = ak_make_event_pub(ER_TALK_CMD_add_talk_list_data, bc_args, 3);
            add_menu_state->entry_events = ak_patched_event_array;
            add_menu_state->entry_events_count = ev_count + 2;
        }
    }

    er_ezstate_transition_t **transitions = menu_transition_state->transitions;
    size_t tr_count = menu_transition_state->transitions_count;
    if (tr_count >= 1 && tr_count + 2 <= 100) {
        for (size_t i = 0; i < tr_count - 1; i++) {
            ak_patched_transition_array[i] = transitions[i];
        }
        size_t start_index = tr_count - 1;
        ak_patched_transition_array[start_index] = &ak_browse_inventory_transition;
        ak_patched_transition_array[start_index + 1] = &ak_browse_cut_content_transition;
        ak_patched_transition_array[start_index + 2] = transitions[tr_count - 1];
        menu_transition_state->transitions = ak_patched_transition_array;
        menu_transition_state->transitions_count = tr_count + 2;
    }

    return true;
}

static void ak_ezstate_enter_state_detour(er_ezstate_state_t *state, er_ezstate_machine_impl_t *machine, void *unk) {
    if (state == machine->state_group->initial_state) {
        if (ak_patch_states(machine->state_group)) {
            ak_main_menu_return_transition.target_state = state;
        }
    }
    ak_set_shop_open(false);
    ak_orig_ezstate_enter_state(state, machine, unk);
}

void ak_setup_talkscript(void) {
    ak_talkscript_utils_init();
    void *p = ak_param_api->get_ezstate_enter_state();
    if (p) ak_the_api->hook(p, (void *)ak_ezstate_enter_state_detour, (void **)&ak_orig_ezstate_enter_state);
}

void ak_unhook_talkscript(void) {
    void *p = ak_param_api->get_ezstate_enter_state();
    if (p) ak_the_api->unhook(p);
    ak_orig_ezstate_enter_state = NULL;
    ak_talkscript_utils_uninit();
}