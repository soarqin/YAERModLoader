/*
 * almighty_kale - 1:1 C port of the Glorious Merchant mod
 * (https://github.com/ThomasJClark/elden-ring-glorious-merchant, MIT).
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 *
 * C11 port of ermerchant_talkscript_utils.hpp. Builds the modded ESD state
 * trees at runtime via LocalAlloc'd backing arrays (the C++ original uses
 * static std::array initializers with cross-references; in C we construct the
 * graph in ak_talkscript_utils_init() and tear it down on uninit).
 */

#include "talkscript_utils.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string.h>
#include <stddef.h>

/* ---- Evaluator byte arrays (read-only, game reads them) ---- */

static const unsigned char ak_browse_inventory_evaluator[]     = {0x57,0x84,0x82,0x30,0x00,0x00,0x00,0x95,0xa1};
static const unsigned char ak_browse_cut_content_evaluator[]   = {0x57,0x84,0x82,0x31,0x00,0x00,0x00,0x95,0xa1};
static const unsigned char ak_weapons_evaluator[]              = {0x57,0x84,0x82,0x32,0x00,0x00,0x00,0x95,0xa1};
static const unsigned char ak_ammunition_evaluator[]           = {0x57,0x84,0x82,0x33,0x00,0x00,0x00,0x95,0xa1};
static const unsigned char ak_spells_evaluator[]               = {0x57,0x84,0x82,0x34,0x00,0x00,0x00,0x95,0xa1};
static const unsigned char ak_ashes_of_war_evaluator[]         = {0x57,0x84,0x82,0x35,0x00,0x00,0x00,0x95,0xa1};
static const unsigned char ak_armor_evaluator[]                = {0x57,0x84,0x82,0x36,0x00,0x00,0x00,0x95,0xa1};
static const unsigned char ak_talismans_evaluator[]            = {0x57,0x84,0x82,0x37,0x00,0x00,0x00,0x95,0xa1};
static const unsigned char ak_items_evaluator[]                = {0x57,0x84,0x82,0x38,0x00,0x00,0x00,0x95,0xa1};
static const unsigned char ak_dlc_evaluator[]                  = {0x57,0x84,0x82,0x39,0x00,0x00,0x00,0x95,0xa1};
static const unsigned char ak_gestures_evaluator[]             = {0x57,0x84,0x82,0x3a,0x00,0x00,0x00,0x95,0xa1};
static const unsigned char ak_goods_evaluator[]                = {0x57,0x84,0x82,0x3b,0x00,0x00,0x00,0x95,0xa1};
static const unsigned char ak_consumables_evaluator[]          = {0x57,0x84,0x82,0x3c,0x00,0x00,0x00,0x95,0xa1};
static const unsigned char ak_materials_evaluator[]            = {0x57,0x84,0x82,0x3d,0x00,0x00,0x00,0x95,0xa1};
static const unsigned char ak_spirit_summons_evaluator[]       = {0x57,0x84,0x82,0x3e,0x00,0x00,0x00,0x95,0xa1};
static const unsigned char ak_miscellaneous_items_evaluator[]  = {0x57,0x84,0x82,0x3f,0x00,0x00,0x00,0x95,0xa1};
static const unsigned char ak_unlock_evaluator[]               = {0x57,0x84,0x82,0x40,0x00,0x00,0x00,0x95,0xa1};
static const unsigned char ak_else_evaluator[]                 = {0x41,0xa1};

static const unsigned char ak_talk_menu_closed_evaluator[] = {
    0x7b,0x82,0x01,0x00,0x00,0x00,0x82,0x00,0x00,0x00,0x00,0x86,0x82,0x01,0x00,0x00,0x00,0x95,
    0x7a,0x82,0x00,0x00,0x00,0x00,0x85,0x82,0x00,0x00,0x00,0x00,0x95,0x98,0x82,0x00,0x00,0x00,0x00,0x95,0xa1,
};

static const unsigned char ak_shop_closed_evaluator[] = {
    0x7b,0x82,0x05,0x00,0x00,0x00,0x82,0x00,0x00,0x00,0x00,0x86,0x82,0x01,0x00,0x00,0x00,0x95,
    0x7a,0x82,0x00,0x00,0x00,0x00,0x85,0x82,0x00,0x00,0x00,0x00,0x95,0x98,0x82,0x00,0x00,0x00,0x00,0x95,0xa1,
};

/* ---- Public state objects ---- */

er_ezstate_transition_t ak_main_menu_return_transition;
er_ezstate_state_t ak_browse_inventory_state;
er_ezstate_state_t ak_browse_inventory_successor_state;
er_ezstate_state_t ak_browse_inventory_items_state;
er_ezstate_state_t ak_browse_inventory_items_successor_state;
er_ezstate_state_t ak_browse_dlc_inventory_state;
er_ezstate_state_t ak_browse_dlc_inventory_successor_state;
er_ezstate_state_t ak_browse_dlc_inventory_items_state;
er_ezstate_state_t ak_browse_dlc_inventory_items_successor_state;
er_ezstate_state_t ak_browse_cut_content_state;
er_ezstate_state_t ak_browse_cut_content_successor_state;
er_ezstate_state_t ak_gestures_state;
er_ezstate_state_t ak_gestures_successor_state;
er_ezstate_state_t ak_gestures_unlock_state;
er_ezstate_state_t ak_dlc_gestures_state;
er_ezstate_state_t ak_dlc_gestures_successor_state;
er_ezstate_state_t ak_dlc_gestures_unlock_state;
er_ezstate_state_t ak_cut_gestures_state;
er_ezstate_state_t ak_cut_gestures_successor_state;
er_ezstate_state_t ak_cut_gestures_unlock_state;

er_ezstate_transition_t ak_browse_inventory_transition;
er_ezstate_transition_t ak_browse_cut_content_transition;

er_ezstate_arg_t ak_browse_inventory_index_value;
er_ezstate_arg_t ak_browse_inventory_message_id_value;
er_ezstate_arg_t ak_browse_cut_content_index_value;
er_ezstate_arg_t ak_browse_cut_content_message_id_value;

/* ---- Helpers ---- */

int ak_get_int_value(er_ezstate_arg_t arg) {
    if (arg.count == 2) {
        return arg.data[0] - 64;
    }
    if (arg.count == 6 && arg.data[0] == 0x82) {
        return *(int *)&arg.data[1];
    }
    return -1;
}

er_ezstate_arg_t ak_make_int_value_into(unsigned char *buf6, int value) {
    buf6[0] = 0x82;
    buf6[1] = (unsigned char)(value & 0xff);
    buf6[2] = (unsigned char)((value >> 8) & 0xff);
    buf6[3] = (unsigned char)((value >> 16) & 0xff);
    buf6[4] = (unsigned char)((value >> 24) & 0xff);
    buf6[5] = 0xa1;
    er_ezstate_arg_t arg = { buf6, 6 };
    return arg;
}

/* ---- Backing storage (freed on uninit) ---- */

static void **ak_alloc_pool = NULL;
static size_t ak_alloc_pool_count = 0;
static size_t ak_alloc_pool_cap = 0;

static void *ak_pool_alloc(size_t bytes) {
    void *p = LocalAlloc(0, bytes);
    if (ak_alloc_pool_count >= ak_alloc_pool_cap) {
        size_t nc = ak_alloc_pool_cap == 0 ? 32 : ak_alloc_pool_cap * 2;
        void **np = ak_alloc_pool ? LocalReAlloc(ak_alloc_pool, nc * sizeof(void *), LMEM_MOVEABLE) : LocalAlloc(0, nc * sizeof(void *));
        ak_alloc_pool = np;
        ak_alloc_pool_cap = nc;
    }
    ak_alloc_pool[ak_alloc_pool_count++] = p;
    return p;
}

static void ak_pool_free_all(void) {
    if (ak_alloc_pool) {
        for (size_t i = 0; i < ak_alloc_pool_count; i++) {
            if (ak_alloc_pool[i]) LocalFree(ak_alloc_pool[i]);
        }
        LocalFree(ak_alloc_pool);
        ak_alloc_pool = NULL;
        ak_alloc_pool_count = 0;
        ak_alloc_pool_cap = 0;
    }
}

static unsigned char *ak_new_int_value(int v) {
    unsigned char *buf = (unsigned char *)ak_pool_alloc(6);
    ak_make_int_value_into(buf, v);
    return buf;
}

static er_ezstate_arg_t *ak_new_args(size_t n) {
    return (er_ezstate_arg_t *)ak_pool_alloc(n * sizeof(er_ezstate_arg_t));
}

static er_ezstate_event_t *ak_new_events(size_t n) {
    return (er_ezstate_event_t *)ak_pool_alloc(n * sizeof(er_ezstate_event_t));
}

static er_ezstate_transition_t *ak_new_transition(er_ezstate_state_t *target, const unsigned char *evaluator, size_t eval_count) {
    er_ezstate_transition_t *t = (er_ezstate_transition_t *)ak_pool_alloc(sizeof(er_ezstate_transition_t));
    t->target_state = target;
    t->pass_events = NULL;
    t->pass_events_count = 0;
    t->sub_transitions = NULL;
    t->sub_count = 0;
    t->evaluator = (unsigned char *)evaluator;
    t->evaluator_count = eval_count;
    return t;
}

static er_ezstate_transition_t **ak_new_transition_ptrs(size_t n) {
    return (er_ezstate_transition_t **)ak_pool_alloc(n * sizeof(er_ezstate_transition_t *));
}

/* Build the 3-arg list for an add_talk_list_data menu entry: {index, message_id, -1}. */
static er_ezstate_arg_t *ak_add_talk_list_args(int index, int message_id) {
    er_ezstate_arg_t *args = ak_new_args(3);
    args[0].data = ak_new_int_value(index); args[0].count = 6;
    args[1].data = ak_new_int_value(message_id); args[1].count = 6;
    args[2].data = ak_new_int_value(-1); args[2].count = 6;
    return args;
}

/* Build an event for a talk command with the given args. */
static er_ezstate_event_t ak_make_event(er_ezstate_command_t cmd, er_ezstate_arg_t *args, size_t args_count) {
    er_ezstate_event_t e;
    e.command = cmd;
    e.args = args;
    e.args_count = args_count;
    return e;
}

/* Build an OPEN_REGULAR_SHOP state: entry event calls open_regular_shop with
 * {begin_id, end_id}; single transition back to prev_state on shop_closed. */
static void ak_build_shop_state(er_ezstate_state_t *state, int state_id, er_ezstate_state_t *prev_state, long long shop_id) {
    er_ezstate_arg_t *args = ak_new_args(2);
    args[0].data = ak_new_int_value((int)shop_id); args[0].count = 6;
    args[1].data = ak_new_int_value((int)(shop_id + AK_SHOP_CAPACITY)); args[1].count = 6;
    er_ezstate_event_t *events = ak_new_events(1);
    events[0] = ak_make_event(ER_TALK_CMD_open_regular_shop, args, 2);
    er_ezstate_transition_t *tr = ak_new_transition(prev_state, ak_shop_closed_evaluator, sizeof(ak_shop_closed_evaluator));
    er_ezstate_transition_t **trs = ak_new_transition_ptrs(1);
    trs[0] = tr;
    state->id = state_id;
    state->_pad0 = 0;
    state->transitions = trs;
    state->transitions_count = 1;
    state->entry_events = events;
    state->entry_events_count = 1;
    state->exit_events = NULL;
    state->exit_events_count = 0;
    state->while_events = NULL;
    state->while_events_count = 0;
}

/* gesture unlock: acquire_gesture(gesture_id) + set_event_flag(flag_id, 0). */
static void ak_build_gesture_unlock_events(er_ezstate_event_t *out, int gesture_id, int event_flag_id, bool with_event) {
    er_ezstate_arg_t *unlock_args = ak_new_args(1);
    unlock_args[0].data = ak_new_int_value(gesture_id); unlock_args[0].count = 6;
    out[0] = ak_make_event(ER_TALK_CMD_acquire_gesture, unlock_args, 1);
    if (with_event) {
        er_ezstate_arg_t *flag_args = ak_new_args(2);
        flag_args[0].data = ak_new_int_value(event_flag_id); flag_args[0].count = 6;
        flag_args[1].data = ak_new_int_value(0); flag_args[1].count = 6;
        out[1] = ak_make_event(ER_TALK_CMD_set_event_flag, flag_args, 2);
    }
}

#define AK_GESTURE(id, gid, flag) { id, gid, flag, true }
#define AK_GESTURE_NO_EVENT(id, gid) { id, gid, 0, false }

typedef struct ak_gesture_def_s {
    int gesture_id;
    int gid;
    int event_flag_id;
    bool with_event;
} ak_gesture_def_t;

static const ak_gesture_def_t ak_gestures_list[] = {
    AK_GESTURE(0,0,60800), AK_GESTURE(1,1,60801), AK_GESTURE(2,2,60802), AK_GESTURE(3,3,60803),
    AK_GESTURE(4,4,60804), AK_GESTURE(5,5,60805), AK_GESTURE(6,6,60806), AK_GESTURE(7,7,60807),
    AK_GESTURE(8,8,60808), AK_GESTURE(9,9,60809), AK_GESTURE(10,10,60810), AK_GESTURE(20,20,60811),
    AK_GESTURE(21,21,60812), AK_GESTURE(22,22,60813), AK_GESTURE(23,23,60814), AK_GESTURE(24,24,60815),
    AK_GESTURE(25,25,60816), AK_GESTURE(30,30,60817), AK_GESTURE(40,40,60818), AK_GESTURE(41,41,60819),
    AK_GESTURE(50,50,60820), AK_GESTURE(51,51,60821), AK_GESTURE(52,52,60822), AK_GESTURE(53,53,60823),
    AK_GESTURE(54,54,60824), AK_GESTURE(60,60,60826), AK_GESTURE(70,70,60827), AK_GESTURE(71,71,60828),
    AK_GESTURE(72,72,60829), AK_GESTURE(73,73,60830), AK_GESTURE(80,80,60831), AK_GESTURE(90,90,60832),
    AK_GESTURE(91,91,60833), AK_GESTURE(92,92,60834), AK_GESTURE(93,93,60835), AK_GESTURE(94,94,60836),
    AK_GESTURE(95,95,60837), AK_GESTURE(97,97,60839), AK_GESTURE(98,98,60840), AK_GESTURE(100,100,60841),
    AK_GESTURE(101,101,60842), AK_GESTURE(102,102,60843), AK_GESTURE(103,103,60845), AK_GESTURE(104,104,60846),
    AK_GESTURE(105,105,60847), AK_GESTURE(106,106,60848),
    /* gesture108 (The Ring) intentionally omitted: see merchant TODO comment. */
};
static const size_t ak_gestures_list_count = sizeof(ak_gestures_list) / sizeof(ak_gestures_list[0]);

static const ak_gesture_def_t ak_dlc_gestures_list[] = {
    AK_GESTURE_NO_EVENT(111,111), AK_GESTURE_NO_EVENT(112,112),
    AK_GESTURE_NO_EVENT(114,114), AK_GESTURE_NO_EVENT(115,115),
};
static const size_t ak_dlc_gestures_list_count = sizeof(ak_dlc_gestures_list) / sizeof(ak_dlc_gestures_list[0]);

static const ak_gesture_def_t ak_cut_gestures_list[] = {
    AK_GESTURE(55,55,60825), AK_GESTURE(96,96,60838),
};
static const size_t ak_cut_gestures_list_count = sizeof(ak_cut_gestures_list) / sizeof(ak_cut_gestures_list[0]);

static void ak_build_gesture_submenu(er_ezstate_state_t *state, er_ezstate_state_t *successor_state, int state_id, const ak_gesture_def_t *gestures, size_t gesture_count) {
    er_ezstate_arg_t *show_arg = ak_new_args(1);
    show_arg[0].data = ak_new_int_value(0); show_arg[0].count = 6;
    er_ezstate_arg_t *unlock_args = ak_add_talk_list_args(64, AK_MSG_unlock);
    er_ezstate_arg_t *leave_args = ak_add_talk_list_args(99, AK_MSG_leave);
    er_ezstate_event_t *events = ak_new_events(5);
    events[0] = ak_make_event(ER_TALK_CMD_close_shop_message, NULL, 0);
    events[1] = ak_make_event(ER_TALK_CMD_clear_talk_list_data, NULL, 0);
    events[2] = ak_make_event(ER_TALK_CMD_add_talk_list_data, unlock_args, 3);
    events[3] = ak_make_event(ER_TALK_CMD_add_talk_list_data, leave_args, 3);
    events[4] = ak_make_event(ER_TALK_CMD_show_shop_message, show_arg, 1);
    er_ezstate_transition_t *next_tr = ak_new_transition(successor_state, ak_talk_menu_closed_evaluator, sizeof(ak_talk_menu_closed_evaluator));
    er_ezstate_transition_t **trs = ak_new_transition_ptrs(1);
    trs[0] = next_tr;
    state->id = state_id;
    state->_pad0 = 0;
    state->transitions = trs;
    state->transitions_count = 1;
    state->entry_events = events;
    state->entry_events_count = 5;
    state->exit_events = NULL;
    state->exit_events_count = 0;
    state->while_events = NULL;
    state->while_events_count = 0;
}

static void ak_build_gesture_unlock_state(er_ezstate_state_t *unlock_state, er_ezstate_state_t *parent_state, int state_id, const ak_gesture_def_t *gestures, size_t gesture_count) {
    size_t ev_count = 0;
    for (size_t i = 0; i < gesture_count; i++) ev_count += gestures[i].with_event ? 2 : 1;
    er_ezstate_event_t *events = ak_new_events(ev_count);
    size_t ei = 0;
    for (size_t i = 0; i < gesture_count; i++) {
        if (gestures[i].with_event) {
            ak_build_gesture_unlock_events(&events[ei], gestures[i].gid, gestures[i].event_flag_id, true);
            ei += 2;
        } else {
            ak_build_gesture_unlock_events(&events[ei], gestures[i].gid, 0, false);
            ei += 1;
        }
    }
    er_ezstate_transition_t *ret_tr = ak_new_transition(parent_state, ak_else_evaluator, sizeof(ak_else_evaluator));
    er_ezstate_transition_t **trs = ak_new_transition_ptrs(1);
    trs[0] = ret_tr;
    unlock_state->id = state_id;
    unlock_state->_pad0 = 0;
    unlock_state->transitions = trs;
    unlock_state->transitions_count = 1;
    unlock_state->entry_events = events;
    unlock_state->entry_events_count = ev_count;
    unlock_state->exit_events = NULL;
    unlock_state->exit_events_count = 0;
    unlock_state->while_events = NULL;
    unlock_state->while_events_count = 0;
}

static void ak_build_gesture_successor(er_ezstate_state_t *successor, er_ezstate_state_t *unlock_state, er_ezstate_state_t *return_state, int state_id) {
    er_ezstate_transition_t *unlock_tr = ak_new_transition(unlock_state, ak_unlock_evaluator, sizeof(ak_unlock_evaluator));
    er_ezstate_transition_t *return_tr = ak_new_transition(return_state, ak_else_evaluator, sizeof(ak_else_evaluator));
    er_ezstate_transition_t **trs = ak_new_transition_ptrs(2);
    trs[0] = unlock_tr;
    trs[1] = return_tr;
    successor->id = state_id;
    successor->_pad0 = 0;
    successor->transitions = trs;
    successor->transitions_count = 2;
    successor->entry_events = NULL;
    successor->entry_events_count = 0;
    successor->exit_events = NULL;
    successor->exit_events_count = 0;
    successor->while_events = NULL;
    successor->while_events_count = 0;
}

static void ak_build_items_submenu(er_ezstate_state_t *state, er_ezstate_state_t *successor, int state_id, er_ezstate_state_t *return_state) {
    er_ezstate_arg_t *show_arg = ak_new_args(1);
    show_arg[0].data = ak_new_int_value(0); show_arg[0].count = 6;
    er_ezstate_arg_t *consumables_args = ak_add_talk_list_args(60, AK_MSG_consumables);
    er_ezstate_arg_t *materials_args = ak_add_talk_list_args(61, AK_MSG_materials);
    er_ezstate_arg_t *spirit_args = ak_add_talk_list_args(62, AK_MSG_spirit_summons);
    er_ezstate_arg_t *misc_args = ak_add_talk_list_args(63, AK_MSG_miscellaneous_items);
    er_ezstate_arg_t *leave_args = ak_add_talk_list_args(99, AK_MSG_leave);
    er_ezstate_event_t *events = ak_new_events(8);
    events[0] = ak_make_event(ER_TALK_CMD_close_shop_message, NULL, 0);
    events[1] = ak_make_event(ER_TALK_CMD_clear_talk_list_data, NULL, 0);
    events[2] = ak_make_event(ER_TALK_CMD_add_talk_list_data, consumables_args, 3);
    events[3] = ak_make_event(ER_TALK_CMD_add_talk_list_data, materials_args, 3);
    events[4] = ak_make_event(ER_TALK_CMD_add_talk_list_data, spirit_args, 3);
    events[5] = ak_make_event(ER_TALK_CMD_add_talk_list_data, misc_args, 3);
    events[6] = ak_make_event(ER_TALK_CMD_add_talk_list_data, leave_args, 3);
    events[7] = ak_make_event(ER_TALK_CMD_show_shop_message, show_arg, 1);
    er_ezstate_transition_t *next_tr = ak_new_transition(successor, ak_talk_menu_closed_evaluator, sizeof(ak_talk_menu_closed_evaluator));
    er_ezstate_transition_t **trs = ak_new_transition_ptrs(1);
    trs[0] = next_tr;
    state->id = state_id;
    state->_pad0 = 0;
    state->transitions = trs;
    state->transitions_count = 1;
    state->entry_events = events;
    state->entry_events_count = 8;
    state->exit_events = NULL;
    state->exit_events_count = 0;
    state->while_events = NULL;
    state->while_events_count = 0;
}

/* builds the successor state that dispatches to the 4 shop states + else return. */
static void ak_build_items_successor(er_ezstate_state_t *successor,
                                     er_ezstate_state_t *consumables_shop, er_ezstate_state_t *materials_shop,
                                     er_ezstate_state_t *spirit_shop, er_ezstate_state_t *misc_shop,
                                     er_ezstate_state_t *return_state, int state_id) {
    er_ezstate_transition_t *t_cons = ak_new_transition(consumables_shop, ak_consumables_evaluator, sizeof(ak_consumables_evaluator));
    er_ezstate_transition_t *t_mat = ak_new_transition(materials_shop, ak_materials_evaluator, sizeof(ak_materials_evaluator));
    er_ezstate_transition_t *t_spi = ak_new_transition(spirit_shop, ak_spirit_summons_evaluator, sizeof(ak_spirit_summons_evaluator));
    er_ezstate_transition_t *t_misc = ak_new_transition(misc_shop, ak_miscellaneous_items_evaluator, sizeof(ak_miscellaneous_items_evaluator));
    er_ezstate_transition_t *t_ret = ak_new_transition(return_state, ak_else_evaluator, sizeof(ak_else_evaluator));
    er_ezstate_transition_t **trs = ak_new_transition_ptrs(5);
    trs[0] = t_cons; trs[1] = t_mat; trs[2] = t_spi; trs[3] = t_misc; trs[4] = t_ret;
    successor->id = state_id;
    successor->_pad0 = 0;
    successor->transitions = trs;
    successor->transitions_count = 5;
    successor->entry_events = NULL;
    successor->entry_events_count = 0;
    successor->exit_events = NULL;
    successor->exit_events_count = 0;
    successor->while_events = NULL;
    successor->while_events_count = 0;
}

void ak_talkscript_utils_init(void);
void ak_talkscript_utils_uninit(void);

er_ezstate_arg_t *ak_new_add_talk_list_args_pub(int index, int message_id) {
    return ak_add_talk_list_args(index, message_id);
}

er_ezstate_event_t ak_make_event_pub(er_ezstate_command_t cmd, er_ezstate_arg_t *args, size_t args_count) {
    return ak_make_event(cmd, args, args_count);
}

/* The 22 shop states (LocalAlloc'd via the pool so they have stable addresses). */
static er_ezstate_state_t *ak_shop_states[AK_SHOP_COUNT];

static er_ezstate_state_t *ak_new_shop_state(int state_id, er_ezstate_state_t *prev_state, long long shop_id) {
    er_ezstate_state_t *s = (er_ezstate_state_t *)ak_pool_alloc(sizeof(er_ezstate_state_t));
    ak_build_shop_state(s, state_id, prev_state, shop_id);
    return s;
}

void ak_talkscript_utils_init(void) {
    /* main_menu_return_transition: target filled in by talkscript hook. */
    ak_main_menu_return_transition.target_state = NULL;
    ak_main_menu_return_transition.pass_events = NULL;
    ak_main_menu_return_transition.pass_events_count = 0;
    ak_main_menu_return_transition.sub_transitions = NULL;
    ak_main_menu_return_transition.sub_count = 0;
    ak_main_menu_return_transition.evaluator = (unsigned char *)ak_else_evaluator;
    ak_main_menu_return_transition.evaluator_count = sizeof(ak_else_evaluator);

    /* browse_inventory / cut_content top-level menu args (also referenced by
     * talkscript.c to rewrite the Purchase/Sell entries). */
    ak_browse_inventory_index_value.data = ak_new_int_value(48); ak_browse_inventory_index_value.count = 6;
    ak_browse_inventory_message_id_value.data = ak_new_int_value(AK_MSG_browse_inventory); ak_browse_inventory_message_id_value.count = 6;
    ak_browse_cut_content_index_value.data = ak_new_int_value(49); ak_browse_cut_content_index_value.count = 6;
    ak_browse_cut_content_message_id_value.data = ak_new_int_value(AK_MSG_browse_cut_content); ak_browse_cut_content_message_id_value.count = 6;

    /* ---- Shop states ---- */
    ak_shop_states[0]  = ak_new_shop_state(5200, &ak_browse_inventory_state, AK_SHOP_weapons);
    ak_shop_states[1]  = ak_new_shop_state(5201, &ak_browse_inventory_state, AK_SHOP_armor);
    ak_shop_states[2]  = ak_new_shop_state(5202, &ak_browse_inventory_state, AK_SHOP_spells);
    ak_shop_states[3]  = ak_new_shop_state(5203, &ak_browse_inventory_state, AK_SHOP_talismans);
    ak_shop_states[4]  = ak_new_shop_state(5204, &ak_browse_inventory_state, AK_SHOP_ammunition);
    ak_shop_states[5]  = ak_new_shop_state(5205, &ak_browse_inventory_state, AK_SHOP_ashes_of_war);
    ak_shop_states[6]  = ak_new_shop_state(5206, &ak_browse_inventory_items_state, AK_SHOP_spirit_summons);
    ak_shop_states[7]  = ak_new_shop_state(5207, &ak_browse_inventory_items_state, AK_SHOP_consumables);
    ak_shop_states[8]  = ak_new_shop_state(5208, &ak_browse_inventory_items_state, AK_SHOP_materials);
    ak_shop_states[9]  = ak_new_shop_state(5209, &ak_browse_inventory_items_state, AK_SHOP_miscellaneous_items);
    ak_shop_states[10] = ak_new_shop_state(5210, &ak_browse_cut_content_state, AK_SHOP_cut_goods);
    ak_shop_states[11] = ak_new_shop_state(5211, &ak_browse_cut_content_state, AK_SHOP_cut_armor);
    ak_shop_states[12] = ak_new_shop_state(5800, &ak_browse_dlc_inventory_state, AK_SHOP_dlc_weapons);
    ak_shop_states[13] = ak_new_shop_state(5801, &ak_browse_dlc_inventory_state, AK_SHOP_dlc_armor);
    ak_shop_states[14] = ak_new_shop_state(5802, &ak_browse_dlc_inventory_state, AK_SHOP_dlc_spells);
    ak_shop_states[15] = ak_new_shop_state(5803, &ak_browse_dlc_inventory_state, AK_SHOP_dlc_talismans);
    ak_shop_states[16] = ak_new_shop_state(5804, &ak_browse_dlc_inventory_state, AK_SHOP_dlc_ammunition);
    ak_shop_states[17] = ak_new_shop_state(5805, &ak_browse_dlc_inventory_state, AK_SHOP_dlc_ashes_of_war);
    ak_shop_states[18] = ak_new_shop_state(5806, &ak_browse_dlc_inventory_items_state, AK_SHOP_dlc_spirit_summons);
    ak_shop_states[19] = ak_new_shop_state(5807, &ak_browse_dlc_inventory_items_state, AK_SHOP_dlc_consumables);
    ak_shop_states[20] = ak_new_shop_state(5808, &ak_browse_dlc_inventory_items_state, AK_SHOP_dlc_materials);
    ak_shop_states[21] = ak_new_shop_state(5809, &ak_browse_dlc_inventory_items_state, AK_SHOP_dlc_miscellaneous_items);

    /* ---- Gesture subtrees ---- */
    ak_build_gesture_submenu(&ak_gestures_state, &ak_gestures_successor_state, 5300, NULL, 0);
    ak_build_gesture_unlock_state(&ak_gestures_unlock_state, &ak_gestures_state, 5302, ak_gestures_list, ak_gestures_list_count);
    ak_build_gesture_successor(&ak_gestures_successor_state, &ak_gestures_unlock_state, &ak_browse_inventory_state, 5301);

    ak_build_gesture_submenu(&ak_dlc_gestures_state, &ak_dlc_gestures_successor_state, 5500, NULL, 0);
    ak_build_gesture_unlock_state(&ak_dlc_gestures_unlock_state, &ak_dlc_gestures_state, 5502, ak_dlc_gestures_list, ak_dlc_gestures_list_count);
    ak_build_gesture_successor(&ak_dlc_gestures_successor_state, &ak_dlc_gestures_unlock_state, &ak_browse_dlc_inventory_state, 5501);

    ak_build_gesture_submenu(&ak_cut_gestures_state, &ak_cut_gestures_successor_state, 5400, NULL, 0);
    ak_build_gesture_unlock_state(&ak_cut_gestures_unlock_state, &ak_cut_gestures_state, 5402, ak_cut_gestures_list, ak_cut_gestures_list_count);
    ak_build_gesture_successor(&ak_cut_gestures_successor_state, &ak_cut_gestures_unlock_state, &ak_browse_cut_content_state, 5401);

    /* ---- Items submenus ---- */
    ak_build_items_submenu(&ak_browse_inventory_items_state, &ak_browse_inventory_items_successor_state, 5002, &ak_browse_inventory_state);
    ak_build_items_successor(&ak_browse_inventory_items_successor_state,
        ak_shop_states[7], ak_shop_states[8], ak_shop_states[6], ak_shop_states[9],
        &ak_browse_inventory_state, 5003);

    ak_build_items_submenu(&ak_browse_dlc_inventory_items_state, &ak_browse_dlc_inventory_items_successor_state, 5702, &ak_browse_dlc_inventory_state);
    ak_build_items_successor(&ak_browse_dlc_inventory_items_successor_state,
        ak_shop_states[19], ak_shop_states[20], ak_shop_states[18], ak_shop_states[21],
        &ak_browse_dlc_inventory_state, 5703);

    /* ---- Browse Inventory submenu (10 entries + leave + show_shop_message) ---- */
    {
        er_ezstate_arg_t *show_arg = ak_new_args(1);
        show_arg[0].data = ak_new_int_value(0); show_arg[0].count = 6;
        er_ezstate_arg_t *a_weapons = ak_add_talk_list_args(50, AK_MSG_weapons);
        er_ezstate_arg_t *a_ammunition = ak_add_talk_list_args(51, AK_MSG_ammunition);
        er_ezstate_arg_t *a_spells = ak_add_talk_list_args(52, AK_MSG_spells);
        er_ezstate_arg_t *a_ashes = ak_add_talk_list_args(53, AK_MSG_ashes_of_war);
        er_ezstate_arg_t *a_armor = ak_add_talk_list_args(54, AK_MSG_armor);
        er_ezstate_arg_t *a_talismans = ak_add_talk_list_args(55, AK_MSG_talismans);
        er_ezstate_arg_t *a_items = ak_add_talk_list_args(56, AK_MSG_items);
        er_ezstate_arg_t *a_dlc = ak_add_talk_list_args(57, AK_MSG_dlc);
        er_ezstate_arg_t *a_gestures = ak_add_talk_list_args(58, AK_MSG_gestures);
        er_ezstate_arg_t *a_leave = ak_add_talk_list_args(99, AK_MSG_leave);
        er_ezstate_event_t *events = ak_new_events(13);
        events[0]  = ak_make_event(ER_TALK_CMD_close_shop_message, NULL, 0);
        events[1]  = ak_make_event(ER_TALK_CMD_clear_talk_list_data, NULL, 0);
        events[2]  = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_weapons, 3);
        events[3]  = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_ammunition, 3);
        events[4]  = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_spells, 3);
        events[5]  = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_ashes, 3);
        events[6]  = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_armor, 3);
        events[7]  = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_talismans, 3);
        events[8]  = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_items, 3);
        events[9]  = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_dlc, 3);
        events[10] = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_gestures, 3);
        events[11] = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_leave, 3);
        events[12] = ak_make_event(ER_TALK_CMD_show_shop_message, show_arg, 1);
        er_ezstate_transition_t *next_tr = ak_new_transition(&ak_browse_inventory_successor_state, ak_talk_menu_closed_evaluator, sizeof(ak_talk_menu_closed_evaluator));
        er_ezstate_transition_t **trs = ak_new_transition_ptrs(1);
        trs[0] = next_tr;
        ak_browse_inventory_state.id = 5000;
        ak_browse_inventory_state._pad0 = 0;
        ak_browse_inventory_state.transitions = trs;
        ak_browse_inventory_state.transitions_count = 1;
        ak_browse_inventory_state.entry_events = events;
        ak_browse_inventory_state.entry_events_count = 13;
        ak_browse_inventory_state.exit_events = NULL;
        ak_browse_inventory_state.exit_events_count = 0;
        ak_browse_inventory_state.while_events = NULL;
        ak_browse_inventory_state.while_events_count = 0;
    }

    /* browse_inventory_successor: 9 transitions + main_menu_return */
    {
        er_ezstate_transition_t *trs_arr[10];
        trs_arr[0] = ak_new_transition(ak_shop_states[0],  ak_weapons_evaluator, sizeof(ak_weapons_evaluator));
        trs_arr[1] = ak_new_transition(ak_shop_states[4],  ak_ammunition_evaluator, sizeof(ak_ammunition_evaluator));
        trs_arr[2] = ak_new_transition(ak_shop_states[2],  ak_spells_evaluator, sizeof(ak_spells_evaluator));
        trs_arr[3] = ak_new_transition(ak_shop_states[5],  ak_ashes_of_war_evaluator, sizeof(ak_ashes_of_war_evaluator));
        trs_arr[4] = ak_new_transition(ak_shop_states[1],  ak_armor_evaluator, sizeof(ak_armor_evaluator));
        trs_arr[5] = ak_new_transition(ak_shop_states[3],  ak_talismans_evaluator, sizeof(ak_talismans_evaluator));
        trs_arr[6] = ak_new_transition(&ak_browse_inventory_items_state, ak_items_evaluator, sizeof(ak_items_evaluator));
        trs_arr[7] = ak_new_transition(&ak_browse_dlc_inventory_state, ak_dlc_evaluator, sizeof(ak_dlc_evaluator));
        trs_arr[8] = ak_new_transition(&ak_gestures_state, ak_gestures_evaluator, sizeof(ak_gestures_evaluator));
        trs_arr[9] = &ak_main_menu_return_transition;
        er_ezstate_transition_t **trs = ak_new_transition_ptrs(10);
        for (int i = 0; i < 10; i++) trs[i] = trs_arr[i];
        ak_browse_inventory_successor_state.id = 5001;
        ak_browse_inventory_successor_state._pad0 = 0;
        ak_browse_inventory_successor_state.transitions = trs;
        ak_browse_inventory_successor_state.transitions_count = 10;
        ak_browse_inventory_successor_state.entry_events = NULL;
        ak_browse_inventory_successor_state.entry_events_count = 0;
        ak_browse_inventory_successor_state.exit_events = NULL;
        ak_browse_inventory_successor_state.exit_events_count = 0;
        ak_browse_inventory_successor_state.while_events = NULL;
        ak_browse_inventory_successor_state.while_events_count = 0;
    }

    /* ---- Browse DLC Inventory submenu (12 entries: no dlc entry) ---- */
    {
        er_ezstate_arg_t *show_arg = ak_new_args(1);
        show_arg[0].data = ak_new_int_value(0); show_arg[0].count = 6;
        er_ezstate_arg_t *a_weapons = ak_add_talk_list_args(50, AK_MSG_weapons);
        er_ezstate_arg_t *a_ammunition = ak_add_talk_list_args(51, AK_MSG_ammunition);
        er_ezstate_arg_t *a_spells = ak_add_talk_list_args(52, AK_MSG_spells);
        er_ezstate_arg_t *a_ashes = ak_add_talk_list_args(53, AK_MSG_ashes_of_war);
        er_ezstate_arg_t *a_armor = ak_add_talk_list_args(54, AK_MSG_armor);
        er_ezstate_arg_t *a_talismans = ak_add_talk_list_args(55, AK_MSG_talismans);
        er_ezstate_arg_t *a_items = ak_add_talk_list_args(56, AK_MSG_items);
        er_ezstate_arg_t *a_gestures = ak_add_talk_list_args(58, AK_MSG_gestures);
        er_ezstate_arg_t *a_leave = ak_add_talk_list_args(99, AK_MSG_leave);
        er_ezstate_event_t *events = ak_new_events(12);
        events[0]  = ak_make_event(ER_TALK_CMD_close_shop_message, NULL, 0);
        events[1]  = ak_make_event(ER_TALK_CMD_clear_talk_list_data, NULL, 0);
        events[2]  = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_weapons, 3);
        events[3]  = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_ammunition, 3);
        events[4]  = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_spells, 3);
        events[5]  = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_ashes, 3);
        events[6]  = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_armor, 3);
        events[7]  = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_talismans, 3);
        events[8]  = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_items, 3);
        events[9]  = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_gestures, 3);
        events[10] = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_leave, 3);
        events[11] = ak_make_event(ER_TALK_CMD_show_shop_message, show_arg, 1);
        er_ezstate_transition_t *next_tr = ak_new_transition(&ak_browse_dlc_inventory_successor_state, ak_talk_menu_closed_evaluator, sizeof(ak_talk_menu_closed_evaluator));
        er_ezstate_transition_t **trs = ak_new_transition_ptrs(1);
        trs[0] = next_tr;
        ak_browse_dlc_inventory_state.id = 5700;
        ak_browse_dlc_inventory_state._pad0 = 0;
        ak_browse_dlc_inventory_state.transitions = trs;
        ak_browse_dlc_inventory_state.transitions_count = 1;
        ak_browse_dlc_inventory_state.entry_events = events;
        ak_browse_dlc_inventory_state.entry_events_count = 12;
        ak_browse_dlc_inventory_state.exit_events = NULL;
        ak_browse_dlc_inventory_state.exit_events_count = 0;
        ak_browse_dlc_inventory_state.while_events = NULL;
        ak_browse_dlc_inventory_state.while_events_count = 0;
    }

    /* browse_dlc_inventory_successor: 8 transitions + return to browse_inventory */
    {
        er_ezstate_transition_t *trs_arr[9];
        trs_arr[0] = ak_new_transition(ak_shop_states[12], ak_weapons_evaluator, sizeof(ak_weapons_evaluator));
        trs_arr[1] = ak_new_transition(ak_shop_states[16], ak_ammunition_evaluator, sizeof(ak_ammunition_evaluator));
        trs_arr[2] = ak_new_transition(ak_shop_states[14], ak_spells_evaluator, sizeof(ak_spells_evaluator));
        trs_arr[3] = ak_new_transition(ak_shop_states[17], ak_ashes_of_war_evaluator, sizeof(ak_ashes_of_war_evaluator));
        trs_arr[4] = ak_new_transition(ak_shop_states[13], ak_armor_evaluator, sizeof(ak_armor_evaluator));
        trs_arr[5] = ak_new_transition(ak_shop_states[15], ak_talismans_evaluator, sizeof(ak_talismans_evaluator));
        trs_arr[6] = ak_new_transition(&ak_browse_dlc_inventory_items_state, ak_items_evaluator, sizeof(ak_items_evaluator));
        trs_arr[7] = ak_new_transition(&ak_dlc_gestures_state, ak_gestures_evaluator, sizeof(ak_gestures_evaluator));
        trs_arr[8] = ak_new_transition(&ak_browse_inventory_state, ak_else_evaluator, sizeof(ak_else_evaluator));
        er_ezstate_transition_t **trs = ak_new_transition_ptrs(9);
        for (int i = 0; i < 9; i++) trs[i] = trs_arr[i];
        ak_browse_dlc_inventory_successor_state.id = 5701;
        ak_browse_dlc_inventory_successor_state._pad0 = 0;
        ak_browse_dlc_inventory_successor_state.transitions = trs;
        ak_browse_dlc_inventory_successor_state.transitions_count = 9;
        ak_browse_dlc_inventory_successor_state.entry_events = NULL;
        ak_browse_dlc_inventory_successor_state.entry_events_count = 0;
        ak_browse_dlc_inventory_successor_state.exit_events = NULL;
        ak_browse_dlc_inventory_successor_state.exit_events_count = 0;
        ak_browse_dlc_inventory_successor_state.while_events = NULL;
        ak_browse_dlc_inventory_successor_state.while_events_count = 0;
    }

    /* ---- Browse Cut Content submenu (7 entries) ---- */
    {
        er_ezstate_arg_t *show_arg = ak_new_args(1);
        show_arg[0].data = ak_new_int_value(0); show_arg[0].count = 6;
        er_ezstate_arg_t *a_armor = ak_add_talk_list_args(54, AK_MSG_armor);
        er_ezstate_arg_t *a_goods = ak_add_talk_list_args(59, AK_MSG_goods);
        er_ezstate_arg_t *a_gestures = ak_add_talk_list_args(58, AK_MSG_gestures);
        er_ezstate_arg_t *a_leave = ak_add_talk_list_args(99, AK_MSG_leave);
        er_ezstate_event_t *events = ak_new_events(7);
        events[0] = ak_make_event(ER_TALK_CMD_close_shop_message, NULL, 0);
        events[1] = ak_make_event(ER_TALK_CMD_clear_talk_list_data, NULL, 0);
        events[2] = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_armor, 3);
        events[3] = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_goods, 3);
        events[4] = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_gestures, 3);
        events[5] = ak_make_event(ER_TALK_CMD_add_talk_list_data, a_leave, 3);
        events[6] = ak_make_event(ER_TALK_CMD_show_shop_message, show_arg, 1);
        er_ezstate_transition_t *next_tr = ak_new_transition(&ak_browse_cut_content_successor_state, ak_talk_menu_closed_evaluator, sizeof(ak_talk_menu_closed_evaluator));
        er_ezstate_transition_t **trs = ak_new_transition_ptrs(1);
        trs[0] = next_tr;
        ak_browse_cut_content_state.id = 5100;
        ak_browse_cut_content_state._pad0 = 0;
        ak_browse_cut_content_state.transitions = trs;
        ak_browse_cut_content_state.transitions_count = 1;
        ak_browse_cut_content_state.entry_events = events;
        ak_browse_cut_content_state.entry_events_count = 7;
        ak_browse_cut_content_state.exit_events = NULL;
        ak_browse_cut_content_state.exit_events_count = 0;
        ak_browse_cut_content_state.while_events = NULL;
        ak_browse_cut_content_state.while_events_count = 0;
    }

    /* browse_cut_content_successor: cut_armor, cut_goods, cut_gestures + main_menu_return */
    {
        er_ezstate_transition_t *trs_arr[4];
        trs_arr[0] = ak_new_transition(ak_shop_states[11], ak_armor_evaluator, sizeof(ak_armor_evaluator));
        trs_arr[1] = ak_new_transition(ak_shop_states[10], ak_goods_evaluator, sizeof(ak_goods_evaluator));
        trs_arr[2] = ak_new_transition(&ak_cut_gestures_state, ak_gestures_evaluator, sizeof(ak_gestures_evaluator));
        trs_arr[3] = &ak_main_menu_return_transition;
        er_ezstate_transition_t **trs = ak_new_transition_ptrs(4);
        for (int i = 0; i < 4; i++) trs[i] = trs_arr[i];
        ak_browse_cut_content_successor_state.id = 5101;
        ak_browse_cut_content_successor_state._pad0 = 0;
        ak_browse_cut_content_successor_state.transitions = trs;
        ak_browse_cut_content_successor_state.transitions_count = 4;
        ak_browse_cut_content_successor_state.entry_events = NULL;
        ak_browse_cut_content_successor_state.entry_events_count = 0;
        ak_browse_cut_content_successor_state.exit_events = NULL;
        ak_browse_cut_content_successor_state.exit_events_count = 0;
        ak_browse_cut_content_successor_state.while_events = NULL;
        ak_browse_cut_content_successor_state.while_events_count = 0;
    }

    /* ---- Main menu transitions ---- */
    ak_browse_inventory_transition.target_state = &ak_browse_inventory_state;
    ak_browse_inventory_transition.pass_events = NULL;
    ak_browse_inventory_transition.pass_events_count = 0;
    ak_browse_inventory_transition.sub_transitions = NULL;
    ak_browse_inventory_transition.sub_count = 0;
    ak_browse_inventory_transition.evaluator = (unsigned char *)ak_browse_inventory_evaluator;
    ak_browse_inventory_transition.evaluator_count = sizeof(ak_browse_inventory_evaluator);

    ak_browse_cut_content_transition.target_state = &ak_browse_cut_content_state;
    ak_browse_cut_content_transition.pass_events = NULL;
    ak_browse_cut_content_transition.pass_events_count = 0;
    ak_browse_cut_content_transition.sub_transitions = NULL;
    ak_browse_cut_content_transition.sub_count = 0;
    ak_browse_cut_content_transition.evaluator = (unsigned char *)ak_browse_cut_content_evaluator;
    ak_browse_cut_content_transition.evaluator_count = sizeof(ak_browse_cut_content_evaluator);
}

void ak_talkscript_utils_uninit(void) {
    ak_pool_free_all();
    memset(&ak_main_menu_return_transition, 0, sizeof(ak_main_menu_return_transition));
    memset(&ak_browse_inventory_state, 0, sizeof(ak_browse_inventory_state));
    memset(&ak_browse_inventory_successor_state, 0, sizeof(ak_browse_inventory_successor_state));
    memset(&ak_browse_inventory_items_state, 0, sizeof(ak_browse_inventory_items_state));
    memset(&ak_browse_inventory_items_successor_state, 0, sizeof(ak_browse_inventory_items_successor_state));
    memset(&ak_browse_dlc_inventory_state, 0, sizeof(ak_browse_dlc_inventory_state));
    memset(&ak_browse_dlc_inventory_successor_state, 0, sizeof(ak_browse_dlc_inventory_successor_state));
    memset(&ak_browse_dlc_inventory_items_state, 0, sizeof(ak_browse_dlc_inventory_items_state));
    memset(&ak_browse_dlc_inventory_items_successor_state, 0, sizeof(ak_browse_dlc_inventory_items_successor_state));
    memset(&ak_browse_cut_content_state, 0, sizeof(ak_browse_cut_content_state));
    memset(&ak_browse_cut_content_successor_state, 0, sizeof(ak_browse_cut_content_successor_state));
    memset(&ak_gestures_state, 0, sizeof(ak_gestures_state));
    memset(&ak_gestures_successor_state, 0, sizeof(ak_gestures_successor_state));
    memset(&ak_gestures_unlock_state, 0, sizeof(ak_gestures_unlock_state));
    memset(&ak_dlc_gestures_state, 0, sizeof(ak_dlc_gestures_state));
    memset(&ak_dlc_gestures_successor_state, 0, sizeof(ak_dlc_gestures_successor_state));
    memset(&ak_dlc_gestures_unlock_state, 0, sizeof(ak_dlc_gestures_unlock_state));
    memset(&ak_cut_gestures_state, 0, sizeof(ak_cut_gestures_state));
    memset(&ak_cut_gestures_successor_state, 0, sizeof(ak_cut_gestures_successor_state));
    memset(&ak_cut_gestures_unlock_state, 0, sizeof(ak_cut_gestures_unlock_state));
    memset(&ak_browse_inventory_transition, 0, sizeof(ak_browse_inventory_transition));
    memset(&ak_browse_cut_content_transition, 0, sizeof(ak_browse_cut_content_transition));
    for (int i = 0; i < AK_SHOP_COUNT; i++) ak_shop_states[i] = NULL;
}