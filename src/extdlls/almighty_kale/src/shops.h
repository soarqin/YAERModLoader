/*
 * almighty_kale - 1:1 C port of the Glorious Merchant mod
 * (https://github.com/ThomasJClark/elden-ring-glorious-merchant, MIT).
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <er_param/defs/shop_lineup_param.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AK_SHOP_CAPACITY 9999

#define AK_SHOP_weapons                9100000LL
#define AK_SHOP_armor                  9110000LL
#define AK_SHOP_spells                 9120000LL
#define AK_SHOP_talismans              9130000LL
#define AK_SHOP_ammunition             9140000LL
#define AK_SHOP_ashes_of_war           9150000LL
#define AK_SHOP_spirit_summons         9160000LL
#define AK_SHOP_consumables            9170000LL
#define AK_SHOP_materials              9180000LL
#define AK_SHOP_miscellaneous_items    9190000LL
#define AK_SHOP_cut_goods              9200000LL
#define AK_SHOP_cut_armor              9210000LL
#define AK_SHOP_dlc_weapons            9300000LL
#define AK_SHOP_dlc_armor              9310000LL
#define AK_SHOP_dlc_spells             9320000LL
#define AK_SHOP_dlc_talismans          9330000LL
#define AK_SHOP_dlc_ammunition         9340000LL
#define AK_SHOP_dlc_ashes_of_war       9350000LL
#define AK_SHOP_dlc_spirit_summons     9360000LL
#define AK_SHOP_dlc_consumables        9370000LL
#define AK_SHOP_dlc_materials          9380000LL
#define AK_SHOP_dlc_miscellaneous_items 9390000LL

#define AK_SHOP_COUNT 22

/* Kalé life/death event flag IDs (shared between shops.c and shop_hooks.c so
 * the get_event_flag hook and any future consumer agree on the values). */
#define AK_KALE_ALIVE_FLAG_ID   4700u
#define AK_KALE_HOSTILE_FLAG_ID 4701u
#define AK_KALE_DEAD_FLAG_ID    4703u

typedef struct ak_shop_s {
    long long id;
    er_shop_lineup_param_t *lineups;
    size_t count;
    size_t cap;
} ak_shop_t;

void ak_setup_shops(void);
void ak_set_shop_open(bool shop_open);
bool ak_is_shop_open_check(void);
void ak_free_shop_data(void);

/* Accessors used by shop_hooks.c */
ak_shop_t *ak_get_mod_shop_public(int shop_lineup_id);
ak_shop_t *ak_mod_shops_array(void);
int ak_max_level_for_reinforce_type(int reinforce_type_id, int def);
bool ak_no_repository_contains(unsigned int item_id);

#ifdef __cplusplus
}
#endif