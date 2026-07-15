/*
 * almighty_kale - 1:1 C port of the Glorious Merchant mod
 * (https://github.com/ThomasJClark/elden-ring-glorious-merchant, MIT).
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "shop_hooks.h"
#include "shops.h"
#include "config.h"

#include <er_param/er_param_api.h>
#include <er_param/from/messages.h>
#include <er_param/from/game_data.h>
#include <er_param/defs/equip_param_weapon.h>
#include <er_param/defs/shop_lineup_param.h>
#include <er_param/param.h>

#include "ext_shared.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <math.h>
#include <stdint.h>

extern const er_param_api_t *ak_param_api;

typedef ak_find_shop_menu_result_t *(*ak_lookup_shop_menu_t)(ak_find_shop_menu_result_t *, unsigned char, int, int);
typedef void (*ak_lookup_shop_lineup_t)(ak_find_shop_menu_result_t *, unsigned char, int);
typedef void (*ak_open_regular_shop_t)(void *, long long, long long);
typedef int (*ak_get_sell_value_t)(unsigned int *);
typedef unsigned long long (*ak_get_max_repository_num_t)(unsigned int *);
typedef unsigned int (*ak_get_event_flag_t)(void *, unsigned int);

static ak_lookup_shop_menu_t ak_orig_lookup_shop_menu = NULL;
static ak_lookup_shop_lineup_t ak_orig_lookup_shop_lineup = NULL;
static ak_open_regular_shop_t ak_orig_open_regular_shop = NULL;
static ak_get_sell_value_t ak_orig_get_sell_value = NULL;
static ak_get_max_repository_num_t ak_orig_get_max_repository_num = NULL;
static ak_get_event_flag_t ak_orig_get_event_flag = NULL;

static ak_find_shop_menu_result_t *ak_lookup_shop_menu_detour(ak_find_shop_menu_result_t *result, unsigned char shop_type, int begin_id, int end_id) {
    ak_shop_t *shops = ak_mod_shops_array();
    for (int i = 0; i < AK_SHOP_COUNT; i++) {
        if (begin_id == (int)shops[i].id) {
            result->shop_type = shop_type;
            result->id = begin_id;
            result->row = &shops[i].lineups[0];
            return result;
        }
    }
    return ak_orig_lookup_shop_menu(result, shop_type, begin_id, end_id);
}

static void ak_lookup_shop_lineup_detour(ak_find_shop_menu_result_t *result, unsigned char shop_type, int id) {
    ak_shop_t *shop = ak_get_mod_shop_public(id);
    if (shop && id < (int)shop->id + (int)shop->count) {
        result->shop_type = shop_type;
        result->id = id;
        result->row = &shop->lineups[id - (int)shop->id];
        return;
    }
    ak_orig_lookup_shop_lineup(result, shop_type, id);
}

static void ak_open_regular_shop_detour(void *unk, long long begin_id, long long end_id) {
    ak_shop_t *shop = ak_get_mod_shop_public((int)begin_id);

    if (ak_config.auto_upgrade_weapons && shop &&
        (shop->id == AK_SHOP_weapons || shop->id == AK_SHOP_dlc_weapons)) {
        er_game_data_man_t *gdm = ak_param_api->get_game_data_man();
        if (gdm && gdm->player_game_data) {
            unsigned char max_reinforce_level = gdm->player_game_data->max_reinforce_level;
            const er_param_table_t *tbl = ak_param_api->find_table(L"EquipParamWeapon");
            for (size_t i = 0; i < shop->count; i++) {
                er_shop_lineup_param_t *lineup = &shop->lineups[i];
                if (lineup->equipType == 0 /* equip_type_weapon */) {
                    int weapon_id = lineup->equipId - lineup->equipId % 100;
                    const er_equip_param_weapon_t *weapon = NULL;
                    if (tbl != NULL) {
                        uint16_t count = tbl->count;
                        for (uint16_t j = 0; j < count; j++) {
                            const er_param_entry_offset_t *entry = &tbl->entries[j];
                            if (entry->param_id == (uint64_t)weapon_id) {
                                weapon = (const er_equip_param_weapon_t *)((uintptr_t)tbl + entry->offset);
                                break;
                            }
                        }
                    }
                    if (weapon) {
                        int max_level = ak_max_level_for_reinforce_type((int)weapon->reinforceTypeId, 0);
                        int reinforce_level = (int)floor((max_reinforce_level + 0.5) * max_level / 25.0);
                        lineup->equipId = weapon_id + reinforce_level;
                    }
                }
            }
        }
    }

    ak_orig_open_regular_shop(unk, begin_id, end_id);

    if (shop) {
        ak_set_shop_open(true);
        er_game_data_man_t *gdm = ak_param_api->get_game_data_man();
        if (gdm && gdm->menu_system_save_load) {
            gdm->menu_system_save_load->sorts[ER_SORT_INDEX_ALL_ITEMS] = ER_MENU_SORT_ITEM_TYPE_ASCENDING;
        }
    }
}

static int ak_get_sell_value_detour(unsigned int *item_id) {
    if (ak_is_shop_open_check()) {
        return 0;
    }
    return ak_orig_get_sell_value(item_id);
}

static unsigned long long ak_get_max_repository_num_detour(unsigned int *item_id) {
    if (ak_is_shop_open_check() && ak_no_repository_contains(*item_id)) {
        return 0;
    }
    return ak_orig_get_max_repository_num(item_id);
}

static unsigned int ak_get_event_flag_detour(void *self, unsigned int flag_id) {
    switch (flag_id) {
        case AK_KALE_ALIVE_FLAG_ID: return 1;
        case AK_KALE_HOSTILE_FLAG_ID: return 0;
        case AK_KALE_DEAD_FLAG_ID: return 0;
        default: return ak_orig_get_event_flag(self, flag_id);
    }
}

void ak_setup_shop_hooks(void) {
    void *p;
    p = ak_param_api->get_lookup_shop_menu();
    if (p) ml_ext_hook(p, (void *)ak_lookup_shop_menu_detour, (void **)&ak_orig_lookup_shop_menu);
    p = ak_param_api->get_lookup_shop_lineup();
    if (p) ml_ext_hook(p, (void *)ak_lookup_shop_lineup_detour, (void **)&ak_orig_lookup_shop_lineup);
    p = ak_param_api->get_open_regular_shop();
    if (p) ml_ext_hook(p, (void *)ak_open_regular_shop_detour, (void **)&ak_orig_open_regular_shop);
    p = ak_param_api->get_get_sell_value();
    if (p) ml_ext_hook(p, (void *)ak_get_sell_value_detour, (void **)&ak_orig_get_sell_value);
    p = ak_param_api->get_get_max_repository_num();
    if (p) ml_ext_hook(p, (void *)ak_get_max_repository_num_detour, (void **)&ak_orig_get_max_repository_num);
    p = ak_param_api->get_get_event_flag();
    if (p) ml_ext_hook(p, (void *)ak_get_event_flag_detour, (void **)&ak_orig_get_event_flag);
}

void ak_unhook_shop_hooks(void) {
    void *p;
    p = ak_param_api->get_lookup_shop_menu();
    if (p) ml_ext_unhook(p);
    p = ak_param_api->get_lookup_shop_lineup();
    if (p) ml_ext_unhook(p);
    p = ak_param_api->get_open_regular_shop();
    if (p) ml_ext_unhook(p);
    p = ak_param_api->get_get_sell_value();
    if (p) ml_ext_unhook(p);
    p = ak_param_api->get_get_max_repository_num();
    if (p) ml_ext_unhook(p);
    p = ak_param_api->get_get_event_flag();
    if (p) ml_ext_unhook(p);
}
