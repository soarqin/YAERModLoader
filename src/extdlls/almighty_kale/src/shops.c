/*
 * almighty_kale - 1:1 C port of the Glorious Merchant mod
 * (https://github.com/ThomasJClark/elden-ring-glorious-merchant, MIT).
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "shops.h"
#include "messages.h"
#include "config.h"

#include <er_param/er_param_api.h>
#include <er_param/param.h>
#include <er_param/defs/equip_param_weapon.h>
#include <er_param/defs/equip_param_protector.h>
#include <er_param/defs/equip_param_goods.h>
#include <er_param/defs/equip_param_gem.h>
#include <er_param/defs/itemlot_param.h>
#include <er_param/defs/reinforce_param_weapon.h>
#include <er_param/defs/shop_lineup_param.h>


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "log.h"

#define AK_LOG(fmt, ...) ML_LOG_DEBUG(L"almighty-kale", L##fmt, ##__VA_ARGS__)

#define kcalloc(N,Z)   LocalAlloc(LPTR, (N)*(Z))
#define kmalloc(Z)     LocalAlloc(0, (Z))
#define krealloc(P,Z)  ((P) ? LocalReAlloc((P), (Z), LMEM_MOVEABLE) : LocalAlloc(0, (Z)))
#define kfree(P)       LocalFree(P)
#include "khash.h"
KHASH_MAP_INIT_INT(ak_int_int, int)
KHASH_SET_INIT_INT(ak_int_set)

extern const er_param_api_t *ak_param_api;

static const wchar_t ak_cut_content_prefix[] = L"[ERROR]";
static const wchar_t ak_reforged_cut_spirit_summon_prefix[] = L"Depleted ";

static const unsigned char AK_LOT_ITEM_CATEGORY_GOODS = 1;
static const unsigned char AK_COST_TYPE_LOST_ASHES_OF_WAR = 4;

enum {
    AK_EQUIP_TYPE_WEAPON = 0,
    AK_EQUIP_TYPE_PROTECTOR = 1,
    AK_EQUIP_TYPE_ACCESSORY = 2,
    AK_EQUIP_TYPE_GOODS = 3,
    AK_EQUIP_TYPE_GEM = 4,
};

static const unsigned short AK_WEAPON_TYPE_ARROW = 81;
static const unsigned short AK_WEAPON_TYPE_GREATARROW = 83;
static const unsigned short AK_WEAPON_TYPE_BOLT = 85;
static const unsigned short AK_WEAPON_TYPE_BALLISTA_BOLT = 86;

static const long long AK_WEAPON_UNARMED_ID = 110000;

static const unsigned char AK_PROTECTOR_CATEGORY_HEAD = 0;
static const unsigned char AK_PROTECTOR_CATEGORY_CHEST = 1;
static const unsigned char AK_PROTECTOR_CATEGORY_ARMS = 2;
static const unsigned char AK_PROTECTOR_CATEGORY_LEGS = 3;

static const long long AK_PROTECTOR_BARE_HEAD_ID = 10000;
static const long long AK_PROTECTOR_BARE_CHEST_ID = 10100;
static const long long AK_PROTECTOR_BARE_ARMS_ID = 10200;
static const long long AK_PROTECTOR_BARE_LEGS_ID = 10300;

static const long long AK_GOODS_GOLDEN_SEED_ID = 10010;
static const long long AK_GOODS_SACRED_TEAR_ID = 10020;

enum {
    AK_GOODS_TYPE_NORMAL_ITEM = 0,
    AK_GOODS_TYPE_KEY_ITEM = 1,
    AK_GOODS_TYPE_CRAFTING_MATERIAL = 2,
    AK_GOODS_TYPE_REMEMBRANCE = 3,
    AK_GOODS_TYPE_SORCERY = 5,
    AK_GOODS_TYPE_SPIRIT_SUMMON_LESSER = 7,
    AK_GOODS_TYPE_SPIRIT_SUMMON_GREATER = 8,
    AK_GOODS_TYPE_WONDROUS_PHYSICK = 9,
    AK_GOODS_TYPE_WONDROUS_PHYSICK_TEAR = 10,
    AK_GOODS_TYPE_REGENERATIVE_MATERIAL = 11,
    AK_GOODS_TYPE_INFO_ITEM = 12,
    AK_GOODS_TYPE_REINFORCEMENT_MATERIAL = 14,
    AK_GOODS_TYPE_GREAT_RUNE = 15,
    AK_GOODS_TYPE_INCANTATION = 16,
    AK_GOODS_TYPE_SELF_BUFF_SORCERY = 17,
    AK_GOODS_TYPE_SELF_BUFF_INCANTATION = 18,
    AK_GOODS_TYPE_CONVERGENCE_RUNE = 100,
    AK_GOODS_TYPE_CONVERGENCE_REMEMBRANCE = 101,
};

static const unsigned char AK_GOODS_SORT_GROUP_TUTORIAL = 20;
static const unsigned char AK_GOODS_SORT_GROUP_GESTURE = 250;

static const long long ak_excluded_goods[] = {
    107, 113, 114, 115, 135, 251,
    1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009, 1010, 1011, 1012, 1013, 1014, 1015,
    1016, 1017, 1018, 1019, 1020, 1021, 1022, 1023, 1024, 1025,
    1050, 1051, 1052, 1053, 1054, 1055, 1056, 1057, 1058, 1059, 1060, 1061, 1062, 1063, 1064, 1065,
    1066, 1067, 1068, 1069, 1070, 1071, 1072, 1073, 1074, 1075,
};
static const size_t ak_excluded_goods_count = sizeof(ak_excluded_goods) / sizeof(ak_excluded_goods[0]);

static const long long ak_cut_content_goods[] = { 8860, 8861, 2008023 };
static const size_t ak_cut_content_goods_count = sizeof(ak_cut_content_goods) / sizeof(ak_cut_content_goods[0]);

static const long long ak_cut_content_protectors[] = {
    610000, 610100, 610200, 610300, 611000, 611100, 955000, 955100, 955200, 955300, 956100,
};
static const size_t ak_cut_content_protectors_count = sizeof(ak_cut_content_protectors) / sizeof(ak_cut_content_protectors[0]);

static const long long ak_cut_content_weapons[] = { 33290000 };
static const size_t ak_cut_content_weapons_count = sizeof(ak_cut_content_weapons) / sizeof(ak_cut_content_weapons[0]);

static const long long ak_cut_content_accessories[] = { 3100, 6120, 6121 };
static const size_t ak_cut_content_accessories_count = sizeof(ak_cut_content_accessories) / sizeof(ak_cut_content_accessories[0]);

static ak_shop_t ak_mod_shops[AK_SHOP_COUNT] = {
    {AK_SHOP_weapons, NULL, 0, 0},
    {AK_SHOP_armor, NULL, 0, 0},
    {AK_SHOP_spells, NULL, 0, 0},
    {AK_SHOP_talismans, NULL, 0, 0},
    {AK_SHOP_ammunition, NULL, 0, 0},
    {AK_SHOP_ashes_of_war, NULL, 0, 0},
    {AK_SHOP_spirit_summons, NULL, 0, 0},
    {AK_SHOP_consumables, NULL, 0, 0},
    {AK_SHOP_materials, NULL, 0, 0},
    {AK_SHOP_miscellaneous_items, NULL, 0, 0},
    {AK_SHOP_cut_goods, NULL, 0, 0},
    {AK_SHOP_cut_armor, NULL, 0, 0},
    {AK_SHOP_dlc_weapons, NULL, 0, 0},
    {AK_SHOP_dlc_armor, NULL, 0, 0},
    {AK_SHOP_dlc_spells, NULL, 0, 0},
    {AK_SHOP_dlc_talismans, NULL, 0, 0},
    {AK_SHOP_dlc_ammunition, NULL, 0, 0},
    {AK_SHOP_dlc_ashes_of_war, NULL, 0, 0},
    {AK_SHOP_dlc_spirit_summons, NULL, 0, 0},
    {AK_SHOP_dlc_consumables, NULL, 0, 0},
    {AK_SHOP_dlc_materials, NULL, 0, 0},
    {AK_SHOP_dlc_miscellaneous_items, NULL, 0, 0},
};

static khash_t(ak_int_int) *ak_max_level_by_reinforce_type_id = NULL;
static khash_t(ak_int_set) *ak_no_repository_item_ids = NULL;
static khash_t(ak_int_int) *ak_goods_flags = NULL;
static khash_t(ak_int_int) *ak_gems_flags = NULL;
static khash_t(ak_int_set) *ak_dummy_goods_ids = NULL;
static khash_t(ak_int_int) *ak_goods_flag_counts = NULL;

static bool ak_is_shop_open = false;

void ak_set_shop_open(bool shop_open) {
    ak_is_shop_open = shop_open;
}

bool ak_is_shop_open_check(void) {
    return ak_is_shop_open;
}

static bool ak_int_set_contains(const khash_t(ak_int_set) *set, int key) {
    if (set == NULL) return false;
    khiter_t k = kh_get(ak_int_set, set, key);
    return k != kh_end(set);
}

static void ak_int_set_insert(khash_t(ak_int_set) *set, int key) {
    if (set == NULL) return;
    int ret;
    khiter_t k = kh_get(ak_int_set, set, key);
    if (k == kh_end(set)) {
        k = kh_put(ak_int_set, set, key, &ret);
        kh_key(set, k) = key;
    }
}

static int ak_int_int_get(const khash_t(ak_int_int) *map, int key, int def) {
    if (map == NULL) return def;
    khiter_t k = kh_get(ak_int_int, map, key);
    if (k == kh_end(map)) return def;
    return kh_value(map, k);
}

static void ak_int_int_put(khash_t(ak_int_int) *map, int key, int val) {
    if (map == NULL) return;
    int ret;
    khiter_t k = kh_put(ak_int_int, map, key, &ret);
    kh_value(map, k) = val;
}

static bool ak_ll_contains(const long long *arr, size_t n, long long id) {
    for (size_t i = 0; i < n; i++) {
        if (arr[i] == id) return true;
    }
    return false;
}

static ak_shop_t *ak_get_mod_shop(int shop_lineup_id) {
    for (int i = 0; i < AK_SHOP_COUNT; i++) {
        if (shop_lineup_id >= ak_mod_shops[i].id && shop_lineup_id < ak_mod_shops[i].id + AK_SHOP_CAPACITY) {
            return &ak_mod_shops[i];
        }
    }
    return NULL;
}

static void ak_shop_push(ak_shop_t *shop, const er_shop_lineup_param_t *row) {
    if (shop->count >= shop->cap) {
        size_t new_cap = shop->cap == 0 ? 16 : shop->cap * 2;
        shop->lineups = (er_shop_lineup_param_t *)krealloc(shop->lineups, new_cap * sizeof(er_shop_lineup_param_t));
        shop->cap = new_cap;
    }
    shop->lineups[shop->count] = *row;
    shop->count++;
}

static bool ak_wstr_starts_with(const wchar_t *s, const wchar_t *prefix) {
    if (s == NULL) return false;
    while (*prefix) {
        if (*s == 0 || *s != *prefix) return false;
        s++;
        prefix++;
    }
    return true;
}

static bool ak_wstr_eq(const wchar_t *s, const wchar_t *other) {
    if (s == NULL || other == NULL) return s == other;
    return wcscmp(s, other) == 0;
}

/* Variant of er_param_table_iterate_begin that also exposes the row id as
 * `ak_id` inside the loop body (the stock macro hides the entry). */
#define ak_iterate_begin(t, tp, var) do { \
    uint16_t ak_count = (t)->count; \
    for (uint16_t ak_i = 0; ak_i < ak_count; ak_i++) { \
        const er_param_entry_offset_t *ak_entry = &((t)->entries[ak_i]); \
        uint64_t ak_id = ak_entry->param_id; \
        tp *var = (tp*)((uintptr_t)(t) + ak_entry->offset); \
        if (!var) { continue; }

#define ak_iterate_end() } } while(0)

/* Spin-wait until the MsgRepository's bnd message tables are actually loaded.
 * The repo indirect pointer becomes non-NULL early, but the localized bnd data
 * (weapon/item/menu names) is bound later. If setup_shops runs before that, every
 * ak_get_message() call returns NULL and every lineup is skipped -> empty shops
 * and "?MenuText?" titles. Probe by looking up names of the first few real weapon
 * rows in EquipParamWeapon; once any resolves to a non-NULL string the bnd is usable.
 * Bounded by a timeout so a permanently-missing entry can't hang init forever. */
static void ak_wait_for_bnd_ready(void) {
    const er_param_table_t *tbl = ak_param_api->find_table(L"EquipParamWeapon");
    if (tbl == NULL) return;
    int probe_ids[8];
    int probe_count = 0;
    uint16_t count = tbl->count;
    for (uint16_t i = 0; i < count && probe_count < 8; i++) {
        const er_param_entry_offset_t *entry = &tbl->entries[i];
        uint64_t id = entry->param_id;
        if (id == (uint64_t)AK_WEAPON_UNARMED_ID) continue;
        if ((int)((id % 10000) / 100) != 0) continue; /* skip affinity rows */
        probe_ids[probe_count++] = (int)id;
    }
    if (probe_count == 0) return;
    const int max_retries = 600; /* ~60 seconds */
    for (int retry = 0; retry < max_retries; retry++) {
        for (int p = 0; p < probe_count; p++) {
            const wchar_t *name = ak_get_message(ER_MSGBND_weapon_name, probe_ids[p]);
            if (name != NULL && name[0] != 0) {
                AK_LOG("ak_wait_for_bnd_ready: bnd ready (retry=%d id=%d)", retry, probe_ids[p]);
                return;
            }
        }
        Sleep(100);
    }
    AK_LOG("ak_wait_for_bnd_ready: timed out after %d retries", max_retries);
}

void ak_setup_shops(void) {
    ak_wait_for_bnd_ready();
    ak_max_level_by_reinforce_type_id = kh_init(ak_int_int);
    ak_no_repository_item_ids = kh_init(ak_int_set);
    ak_goods_flags = kh_init(ak_int_int);
    ak_gems_flags = kh_init(ak_int_int);
    ak_dummy_goods_ids = kh_init(ak_int_set);
    ak_goods_flag_counts = kh_init(ak_int_int);

    ak_shop_t *weapon_lineups = &ak_mod_shops[0];
    ak_shop_t *armor_lineups = &ak_mod_shops[1];
    ak_shop_t *spell_lineups = &ak_mod_shops[2];
    ak_shop_t *talisman_lineups = &ak_mod_shops[3];
    ak_shop_t *ammunition_lineups = &ak_mod_shops[4];
    ak_shop_t *ash_of_war_lineups = &ak_mod_shops[5];
    ak_shop_t *spirit_summon_lineups = &ak_mod_shops[6];
    ak_shop_t *consumable_lineups = &ak_mod_shops[7];
    ak_shop_t *material_lineups = &ak_mod_shops[8];
    ak_shop_t *miscellaneous_item_lineups = &ak_mod_shops[9];
    ak_shop_t *cut_good_lineups = &ak_mod_shops[10];
    ak_shop_t *cut_armor_lineups = &ak_mod_shops[11];
    ak_shop_t *dlc_weapon_lineups = &ak_mod_shops[12];
    ak_shop_t *dlc_armor_lineups = &ak_mod_shops[13];
    ak_shop_t *dlc_spell_lineups = &ak_mod_shops[14];
    ak_shop_t *dlc_talisman_lineups = &ak_mod_shops[15];
    ak_shop_t *dlc_ammunition_lineups = &ak_mod_shops[16];
    ak_shop_t *dlc_ashes_of_war_lineups = &ak_mod_shops[17];
    ak_shop_t *dlc_spirit_summon_lineups = &ak_mod_shops[18];
    ak_shop_t *dlc_consumable_lineups = &ak_mod_shops[19];
    ak_shop_t *dlc_material_lineups = &ak_mod_shops[20];
    ak_shop_t *dlc_miscellaneous_item_lineups = &ak_mod_shops[21];

    const wchar_t *itemlot_names[] = { L"ItemLotParam_map", L"ItemLotParam_enemy" };
    for (int t = 0; t < 2; t++) {
        const er_param_table_t *tbl = ak_param_api->find_table(itemlot_names[t]);
        if (tbl == NULL) continue;
        er_param_table_iterate_begin(tbl, er_itemlot_param_t, row) {
            if (row->lotItemCategory01 == AK_LOT_ITEM_CATEGORY_GOODS && row->getItemFlagId > 0) {
                ak_int_int_put(ak_goods_flags, row->lotItemId01, (int)row->getItemFlagId);
            }
        } er_param_table_iterate_end();
    }

    {
        const er_param_table_t *tbl = ak_param_api->find_table(L"ShopLineupParam");
        if (tbl != NULL) {
            er_param_table_iterate_begin(tbl, er_shop_lineup_param_t, row) {
                if (row->equipType == AK_EQUIP_TYPE_GOODS) {
                    ak_int_int_put(ak_goods_flags, row->equipId, (int)row->eventFlag_forStock);
                } else if (row->equipType == AK_EQUIP_TYPE_GEM && row->costType == AK_COST_TYPE_LOST_ASHES_OF_WAR) {
                    ak_int_int_put(ak_gems_flags, row->equipId, (int)row->eventFlag_forRelease);
                }
                if (row->nameMsgId != -1) {
                    ak_int_set_insert(ak_dummy_goods_ids, row->nameMsgId);
                }
            } er_param_table_iterate_end();
        }
    }

    {
        const er_param_table_t *tbl = ak_param_api->find_table(L"EquipParamGoods");
        if (tbl != NULL) {
            er_param_table_iterate_begin(tbl, er_equip_param_goods_t, row) {
                if (row->appearanceReplaceItemId != -1) {
                    ak_int_set_insert(ak_dummy_goods_ids, row->appearanceReplaceItemId);
                }
            } er_param_table_iterate_end();
        }
    }

    /* goods_flag_counts: count usages of each flag prefix (flag - flag%10) */
    if (ak_goods_flags != NULL) {
        for (khiter_t k = kh_begin(ak_goods_flags); k != kh_end(ak_goods_flags); ++k) {
            if (!kh_exist(ak_goods_flags, k)) continue;
            unsigned int flag = (unsigned int)kh_value(ak_goods_flags, k);
            unsigned int prefix = flag - flag % 10;
            int ret;
            khiter_t kc = kh_put(ak_int_int, ak_goods_flag_counts, (int)prefix, &ret);
            if (ret) {
                kh_value(ak_goods_flag_counts, kc) = 0;
            }
            kh_value(ak_goods_flag_counts, kc)++;
        }
    }

    /* Weapons */
    {
        const er_param_table_t *tbl = ak_param_api->find_table(L"EquipParamWeapon");
        if (tbl != NULL) {
            ak_iterate_begin(tbl, er_equip_param_weapon_t, row) {
                uint64_t id = ak_id;
                if (id == (uint64_t)AK_WEAPON_UNARMED_ID) continue;
                int affinity_id = (int)((id % 10000) / 100);
                if (affinity_id != 0) continue;

                bool is_dlc = false;
                const wchar_t *weapon_name = ak_get_message(ER_MSGBND_weapon_name, (int)id);
                if (weapon_name == NULL || weapon_name[0] == 0) {
                    is_dlc = true;
                    weapon_name = ak_get_message(ER_MSGBND_dlc_weapon_name, (int)id);
                }
                if (weapon_name == NULL || weapon_name[0] == 0 || ak_wstr_starts_with(weapon_name, ak_cut_content_prefix)) {
                    continue;
                }

                ak_shop_t *lineups = NULL;
                if (ak_ll_contains(ak_cut_content_weapons, ak_cut_content_weapons_count, (long long)id)) {
                    lineups = cut_good_lineups;
                } else if (row->wepType == AK_WEAPON_TYPE_ARROW || row->wepType == AK_WEAPON_TYPE_GREATARROW ||
                           row->wepType == AK_WEAPON_TYPE_BOLT || row->wepType == AK_WEAPON_TYPE_BALLISTA_BOLT) {
                    lineups = is_dlc ? dlc_ammunition_lineups : ammunition_lineups;
                } else if (is_dlc) {
                    lineups = dlc_weapon_lineups;
                } else {
                    lineups = weapon_lineups;
                }
                er_shop_lineup_param_t l = {0};
                l.equipId = (int)id;
                l.equipType = AK_EQUIP_TYPE_WEAPON;
                l.value = -1;
                l.mtrlId = -1;
                l.sellQuantity = -1;
                l.costType = 0;
                l.setNum = 1;
                l.value_Magnification = 1.0f;
                l.iconId = -1;
                l.nameMsgId = -1;
                l.menuTitleMsgId = -1;
                l.menuIconId = -1;
                ak_shop_push(lineups, &l);
            } ak_iterate_end();
        }
    }

    /* Protectors */
    {
        const er_param_table_t *tbl = ak_param_api->find_table(L"EquipParamProtector");
        if (tbl != NULL) {
            ak_iterate_begin(tbl, er_equip_param_protector_t, row) {
                uint64_t id = ak_id;
                if (id == (uint64_t)AK_PROTECTOR_BARE_HEAD_ID || id == (uint64_t)AK_PROTECTOR_BARE_CHEST_ID ||
                    id == (uint64_t)AK_PROTECTOR_BARE_ARMS_ID || id == (uint64_t)AK_PROTECTOR_BARE_LEGS_ID) {
                    continue;
                }
                if (row->protectorCategory != AK_PROTECTOR_CATEGORY_HEAD &&
                    row->protectorCategory != AK_PROTECTOR_CATEGORY_CHEST &&
                    row->protectorCategory != AK_PROTECTOR_CATEGORY_ARMS &&
                    row->protectorCategory != AK_PROTECTOR_CATEGORY_LEGS) {
                    continue;
                }

                bool is_dlc = false;
                const wchar_t *protector_name = ak_get_message(ER_MSGBND_protector_name, (int)id);
                if (protector_name == NULL || protector_name[0] == 0) {
                    is_dlc = true;
                    protector_name = ak_get_message(ER_MSGBND_dlc_protector_name, (int)id);
                }
                if (protector_name == NULL || protector_name[0] == 0 || ak_wstr_eq(protector_name, ak_cut_content_prefix)) {
                    continue;
                }

                ak_shop_t *lineups = NULL;
                if (ak_wstr_starts_with(protector_name, ak_cut_content_prefix) ||
                    ak_ll_contains(ak_cut_content_protectors, ak_cut_content_protectors_count, (long long)id)) {
                    lineups = cut_armor_lineups;
                } else if (is_dlc) {
                    lineups = dlc_armor_lineups;
                } else {
                    lineups = armor_lineups;
                }
                er_shop_lineup_param_t l = {0};
                l.equipId = (int)id;
                l.equipType = AK_EQUIP_TYPE_PROTECTOR;
                l.value = -1;
                l.mtrlId = -1;
                l.sellQuantity = -1;
                l.setNum = 1;
                l.value_Magnification = 1.0f;
                l.iconId = -1;
                l.nameMsgId = -1;
                l.menuTitleMsgId = -1;
                l.menuIconId = -1;
                ak_shop_push(lineups, &l);
            } ak_iterate_end();
        }
    }

    /* Accessories - NOTE: faithfully replicates the merchant bug at ~line 564
     * of ermerchant_shops.cpp: the `if (is_dlc)` / else block is NOT chained
     * with `else if` after `if (cut_content_accessories.contains(id))`, so the
     * dlc/talisman branch always overwrites the cut_good assignment. */
    {
        const er_param_table_t *tbl = ak_param_api->find_table(L"EquipParamAccessory");
        if (tbl != NULL) {
            ak_iterate_begin(tbl, er_equip_param_goods_t, row) {
                uint64_t id = ak_id;
                bool is_dlc = false;
                const wchar_t *accessory_name = ak_get_message(ER_MSGBND_accessory_name, (int)id);
                if (accessory_name == NULL || accessory_name[0] == 0) {
                    is_dlc = true;
                    accessory_name = ak_get_message(ER_MSGBND_dlc_accessory_name, (int)id);
                }
                if (accessory_name == NULL || accessory_name[0] == 0 || ak_wstr_starts_with(accessory_name, ak_cut_content_prefix)) {
                    continue;
                }

                ak_shop_t *lineups = NULL;
                if (ak_ll_contains(ak_cut_content_accessories, ak_cut_content_accessories_count, (long long)id)) {
                    lineups = cut_good_lineups;
                }
                if (is_dlc) {
                    lineups = dlc_talisman_lineups;
                } else {
                    lineups = talisman_lineups;
                }
                er_shop_lineup_param_t l = {0};
                l.equipId = (int)id;
                l.equipType = AK_EQUIP_TYPE_ACCESSORY;
                l.value = -1;
                l.mtrlId = -1;
                l.sellQuantity = -1;
                l.setNum = 1;
                l.value_Magnification = 1.0f;
                l.iconId = -1;
                l.nameMsgId = -1;
                l.menuTitleMsgId = -1;
                l.menuIconId = -1;
                ak_shop_push(lineups, &l);
            } ak_iterate_end();
        }
    }

    /* Goods */
    {
        const er_param_table_t *tbl = ak_param_api->find_table(L"EquipParamGoods");
        if (tbl != NULL) {
            ak_iterate_begin(tbl, er_equip_param_goods_t, row) {
                uint64_t id = ak_id;
                if (ak_ll_contains(ak_excluded_goods, ak_excluded_goods_count, (long long)id)) continue;
                if (row->goodsType == AK_GOODS_TYPE_NORMAL_ITEM && row->sortGroupId == AK_GOODS_SORT_GROUP_GESTURE) continue;
                if (row->goodsType == AK_GOODS_TYPE_INFO_ITEM && row->sortGroupId == AK_GOODS_SORT_GROUP_TUTORIAL) continue;
                if (ak_int_set_contains(ak_dummy_goods_ids, (int)id)) continue;

                bool is_dlc = false;
                const wchar_t *goods_name = ak_get_message(ER_MSGBND_goods_name, (int)id);
                if (goods_name == NULL || goods_name[0] == 0) {
                    is_dlc = true;
                    goods_name = ak_get_message(ER_MSGBND_dlc_goods_name, (int)id);
                }
                if (goods_name == NULL || goods_name[0] == 0 || ak_wstr_eq(goods_name, ak_cut_content_prefix)) {
                    continue;
                }

                ak_shop_t *lineups = NULL;
                if (ak_wstr_starts_with(goods_name, ak_cut_content_prefix) || !row->iconId ||
                    ak_ll_contains(ak_cut_content_goods, ak_cut_content_goods_count, (long long)id)) {
                    lineups = cut_good_lineups;
                } else if (id == (uint64_t)AK_GOODS_GOLDEN_SEED_ID || id == (uint64_t)AK_GOODS_SACRED_TEAR_ID) {
                    lineups = is_dlc ? dlc_consumable_lineups : consumable_lineups;
                } else {
                    switch (row->goodsType) {
                        case AK_GOODS_TYPE_NORMAL_ITEM:
                            if (row->isConsume && !row->disable_offline) {
                                lineups = is_dlc ? dlc_consumable_lineups : consumable_lineups;
                            } else {
                                lineups = is_dlc ? dlc_miscellaneous_item_lineups : miscellaneous_item_lineups;
                            }
                            break;
                        case AK_GOODS_TYPE_SORCERY:
                        case AK_GOODS_TYPE_INCANTATION:
                        case AK_GOODS_TYPE_SELF_BUFF_SORCERY:
                        case AK_GOODS_TYPE_SELF_BUFF_INCANTATION:
                            lineups = is_dlc ? dlc_spell_lineups : spell_lineups;
                            break;
                        case AK_GOODS_TYPE_SPIRIT_SUMMON_LESSER:
                        case AK_GOODS_TYPE_SPIRIT_SUMMON_GREATER: {
                            int upgrade_level = (int)(id % 100);
                            if (upgrade_level == 0) {
                                if (ak_wstr_starts_with(goods_name, ak_reforged_cut_spirit_summon_prefix)) {
                                    lineups = cut_good_lineups;
                                } else {
                                    lineups = is_dlc ? dlc_spirit_summon_lineups : spirit_summon_lineups;
                                }
                            }
                            break;
                        }
                        case AK_GOODS_TYPE_REMEMBRANCE:
                        case AK_GOODS_TYPE_REGENERATIVE_MATERIAL:
                        case AK_GOODS_TYPE_CONVERGENCE_RUNE:
                        case AK_GOODS_TYPE_CONVERGENCE_REMEMBRANCE:
                            lineups = is_dlc ? dlc_consumable_lineups : consumable_lineups;
                            break;
                        case AK_GOODS_TYPE_CRAFTING_MATERIAL:
                        case AK_GOODS_TYPE_REINFORCEMENT_MATERIAL:
                            lineups = is_dlc ? dlc_material_lineups : material_lineups;
                            break;
                        case AK_GOODS_TYPE_KEY_ITEM:
                        case AK_GOODS_TYPE_INFO_ITEM:
                        case AK_GOODS_TYPE_WONDROUS_PHYSICK:
                        case AK_GOODS_TYPE_WONDROUS_PHYSICK_TEAR:
                        case AK_GOODS_TYPE_GREAT_RUNE:
                            lineups = is_dlc ? dlc_miscellaneous_item_lineups : miscellaneous_item_lineups;
                            break;
                        default:
                            break;
                    }
                }

                if (lineups != NULL) {
                    unsigned int event_flag = (unsigned int)ak_int_int_get(ak_goods_flags, (int)id, 0);
                    short sell_quantity = -1;
                    if (event_flag && row->maxNum == 1 && row->maxRepositoryNum == 1) {
                        ak_int_set_insert(ak_no_repository_item_ids, (int)(0x40000000u | (unsigned int)id));
                        if (event_flag % 10 == 0) {
                            int count = ak_int_int_get(ak_goods_flag_counts, (int)(event_flag - event_flag % 10), 0);
                            if (count == 1) {
                                sell_quantity = 1;
                            }
                        }
                    }
                    er_shop_lineup_param_t l = {0};
                    l.equipId = (int)id;
                    l.eventFlag_forStock = event_flag;
                    l.sellQuantity = sell_quantity;
                    l.equipType = AK_EQUIP_TYPE_GOODS;
                    l.value = -1;
                    l.mtrlId = -1;
                    l.costType = 0;
                    l.setNum = 1;
                    l.value_Magnification = 1.0f;
                    l.iconId = -1;
                    l.nameMsgId = -1;
                    l.menuTitleMsgId = -1;
                    l.menuIconId = -1;
                    ak_shop_push(lineups, &l);
                }
            } ak_iterate_end();
        }
    }

    /* Gems */
    {
        const er_param_table_t *tbl = ak_param_api->find_table(L"EquipParamGem");
        if (tbl != NULL) {
            ak_iterate_begin(tbl, er_equip_param_gem_t, row) {
                uint64_t id = ak_id;
                bool is_dlc = false;
                const wchar_t *gem_name = ak_get_message(ER_MSGBND_gem_name, (int)id);
                if (gem_name == NULL || gem_name[0] == 0) {
                    is_dlc = true;
                    gem_name = ak_get_message(ER_MSGBND_dlc_gem_name, (int)id);
                }
                if (gem_name == NULL || gem_name[0] == 0 || ak_wstr_starts_with(gem_name, ak_cut_content_prefix)) {
                    continue;
                }
                ak_shop_t *lineups = is_dlc ? dlc_ashes_of_war_lineups : ash_of_war_lineups;
                unsigned int event_flag = (unsigned int)ak_int_int_get(ak_gems_flags, (int)id, 0);
                er_shop_lineup_param_t l = {0};
                l.equipId = (int)id;
                l.eventFlag_forStock = event_flag;
                l.equipType = AK_EQUIP_TYPE_GEM;
                l.value = -1;
                l.mtrlId = -1;
                l.sellQuantity = -1;
                l.costType = 0;
                l.setNum = 1;
                l.value_Magnification = 1.0f;
                l.iconId = -1;
                l.nameMsgId = -1;
                l.menuTitleMsgId = -1;
                l.menuIconId = -1;
                ak_shop_push(lineups, &l);
            } ak_iterate_end();
        }
    }

    /* ReinforceParamWeapon: record max upgrade level per reinforce type id */
    {
        const er_param_table_t *tbl = ak_param_api->find_table(L"ReinforceParamWeapon");
        if (tbl != NULL) {
            ak_iterate_begin(tbl, er_reinforce_param_weapon_t, row) {
                uint64_t id = ak_id;
                int level = (int)(id % 50);
                ak_int_int_put(ak_max_level_by_reinforce_type_id, (int)(id - level), level);
            } ak_iterate_end();
        }
    }
}

/* Accessors used by shop_hooks.c */
ak_shop_t *ak_get_mod_shop_public(int shop_lineup_id) {
    return ak_get_mod_shop(shop_lineup_id);
}

ak_shop_t *ak_mod_shops_array(void) {
    return ak_mod_shops;
}

int ak_max_level_for_reinforce_type(int reinforce_type_id, int def) {
    return ak_int_int_get(ak_max_level_by_reinforce_type_id, reinforce_type_id, def);
}

bool ak_no_repository_contains(unsigned int item_id) {
    return ak_int_set_contains(ak_no_repository_item_ids, (int)item_id);
}

void ak_free_shop_data(void) {
    for (int i = 0; i < AK_SHOP_COUNT; i++) {
        if (ak_mod_shops[i].lineups) {
            LocalFree(ak_mod_shops[i].lineups);
            ak_mod_shops[i].lineups = NULL;
            ak_mod_shops[i].count = 0;
            ak_mod_shops[i].cap = 0;
        }
    }
    if (ak_max_level_by_reinforce_type_id) { kh_destroy(ak_int_int, ak_max_level_by_reinforce_type_id); ak_max_level_by_reinforce_type_id = NULL; }
    if (ak_no_repository_item_ids) { kh_destroy(ak_int_set, ak_no_repository_item_ids); ak_no_repository_item_ids = NULL; }
    if (ak_goods_flags) { kh_destroy(ak_int_int, ak_goods_flags); ak_goods_flags = NULL; }
    if (ak_gems_flags) { kh_destroy(ak_int_int, ak_gems_flags); ak_gems_flags = NULL; }
    if (ak_dummy_goods_ids) { kh_destroy(ak_int_set, ak_dummy_goods_ids); ak_dummy_goods_ids = NULL; }
    if (ak_goods_flag_counts) { kh_destroy(ak_int_int, ak_goods_flag_counts); ak_goods_flag_counts = NULL; }
}
