/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include <modloader/extdll_api.h>
#include <eldenring/param.h>
#include <eldenring/defs/itemlot_param.h>

#include <ini.h>

#include <windows.h>
#include <shlwapi.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

static modloader_ext_api_t* the_api;

typedef struct config_s {
    bool include_weapons;
    bool include_arrows;
    bool include_armors;
    int *include_goods;
    int include_goods_count;
    struct alter_item_s {
        int id;
        int type;
        int new_count;
    } *alter_items;
    int alter_items_count;
    int alter_items_capacity;
} config_t;

static config_t config;

static int compare_int(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

static int my_ini_handler(void* user, const char* section, const char* name, const char* value) {
    config_t* cfg = (config_t*)user;
    
    if (section == NULL || section[0] == 0) {
        if (strcmp(name, "include_weapons") == 0) {
            cfg->include_weapons = strcmp(value, "true") == 0;
        } else if (strcmp(name, "include_arrows") == 0) {
            cfg->include_arrows = strcmp(value, "true") == 0;
        } else if (strcmp(name, "include_armors") == 0) {
            cfg->include_armors = strcmp(value, "true") == 0;
        } else if (strcmp(name, "include_goods") == 0) {
            char* goods_str = strdup(value);
            char* goods_token = strtok(goods_str, ",");
            int count = 16;
            cfg->include_goods = (int*)LocalAlloc(LMEM_FIXED, sizeof(int) * count);
            int i = 0;
            while (goods_token != NULL) {
                if (i >= count) {
                    count *= 2;
                    cfg->include_goods = (int*)LocalReAlloc(cfg->include_goods, sizeof(int) * count, LMEM_MOVEABLE);
                }
                cfg->include_goods[i] = atoi(goods_token);
                i++;
                goods_token = strtok(NULL, ",");
            }
            if (i < count) {
                cfg->include_goods = (int*)LocalReAlloc(cfg->include_goods, sizeof(int) * i, LMEM_MOVEABLE);
            }
            cfg->include_goods_count = i;
            qsort(cfg->include_goods, i, sizeof(int), compare_int);
            free(goods_str);
        }
    } else if (lstrcmpA(section, "alter_count") == 0) {
        int id = atoi(name);
        char *str = strdup(value);
        char *token = strtok(str, ",");
        int type = 1;
        if (lstrcmpA(token, "drop") == 0) {
            type = 2;
        } else if (lstrcmpA(token, "all") == 0) {
            type = 3;
        }
        token = strtok(NULL, ",");
        int new_count = atoi(token);
        free(str);
        if (cfg->alter_items == NULL) {
            cfg->alter_items_count = 0;
            cfg->alter_items_capacity = 8;
            cfg->alter_items = (typeof(cfg->alter_items))LocalAlloc(LMEM_FIXED, 8 * sizeof(*cfg->alter_items));
        } else if (cfg->alter_items_count < cfg->alter_items_capacity) {
            cfg->alter_items_capacity *= 2;
            cfg->alter_items = (typeof(cfg->alter_items))LocalReAlloc(cfg->alter_items, sizeof(*cfg->alter_items) * (cfg->alter_items_capacity), LMEM_MOVEABLE);
        }
        cfg->alter_items[cfg->alter_items_count].id = id;
        cfg->alter_items[cfg->alter_items_count].type = type;
        cfg->alter_items[cfg->alter_items_count].new_count = new_count;
        cfg->alter_items_count++;
    }
    return 1;
}

static void load_config(HMODULE module) {
    wchar_t ini_path[512];
    GetModuleFileNameW(module, ini_path, sizeof(ini_path) / sizeof(ini_path[0]));
    PathRemoveFileSpecW(ini_path);
    PathAppendW(ini_path, L"itemlot_rate.ini");
    
    config.include_weapons = true;
    config.include_arrows = false; 
    config.include_armors = true;
    if (config.include_goods != NULL) {
        LocalFree(config.include_goods);
        config.include_goods = NULL;
    }

    FILE* file = _wfopen(ini_path, L"r");
    if (file == NULL) {
        return;
    }
    ini_parse_file(file, my_ini_handler, &config);
    fclose(file);
}

static bool is_item_on_table(int category, int item_id) {
    switch (category) {
        case 1:
            if (!config.include_goods) return false;
            return bsearch(&item_id, config.include_goods, config.include_goods_count, sizeof(int), compare_int) != NULL;
        case 2:
            if (config.include_weapons && (item_id < 43100000 || item_id >= 60000000)) return true;
            return config.include_arrows && item_id >= 43100000 && item_id < 60000000;
        case 3:
            return config.include_armors;
        default:
            return false;
    }
}

static bool is_missable_equipment(short base_point, int category, int item_id) {
    return base_point > 0 && base_point < 1000 && is_item_on_table(category, item_id);
}

void process_param_rate(er_itemlot_param_t* param) {
#define PARAM_IS_MISSABLE_EQUIPMENT(n) bool is_missable_##n = is_missable_equipment(param->lotItemBasePoint##n, param->lotItemCategory##n, param->lotItemId##n)
#define PROCESS_PARAM(n) if (is_missable_##n) { \
        param->lotItemBasePoint##n = 1000; \
        param->enableLuck##n = 0; \
        param->cumulateLotPoint##n = 0; \
        param->cumulateReset##n = 0; \
    } else if (param->lotItemBasePoint##n > 0 && param->lotItemId##n == 0) { \
        param->lotItemBasePoint##n = 0; \
        param->enableLuck##n = 0; \
        param->cumulateLotPoint##n = 0; \
        param->cumulateReset##n = 0; \
    }
    PARAM_IS_MISSABLE_EQUIPMENT(01);
    PARAM_IS_MISSABLE_EQUIPMENT(02);
    PARAM_IS_MISSABLE_EQUIPMENT(03);
    PARAM_IS_MISSABLE_EQUIPMENT(04);
    PARAM_IS_MISSABLE_EQUIPMENT(05);
    PARAM_IS_MISSABLE_EQUIPMENT(06);
    PARAM_IS_MISSABLE_EQUIPMENT(07);
    PARAM_IS_MISSABLE_EQUIPMENT(08);
    if (is_missable_01 || is_missable_02 || is_missable_03 || is_missable_04 || is_missable_05 || is_missable_06 || is_missable_07 || is_missable_08) {
        PROCESS_PARAM(01)
        PROCESS_PARAM(02)
        PROCESS_PARAM(03)
        PROCESS_PARAM(04)
        PROCESS_PARAM(05)
        PROCESS_PARAM(06)
        PROCESS_PARAM(07)
        PROCESS_PARAM(08)
        param->cumulateNumMax = 0;
    }
#undef PARAM_IS_MISSABLE_EQUIPMENT
#undef PROCESS_PARAM
}

void process_param_count(er_itemlot_param_t* param, int type) {
#define LOT_ITEM_NUM(n) if (item->type & type) { \
        if (param->lotItemId##n == item->id && param->lotItemNum##n > 0 && param->lotItemBasePoint##n > 0) { \
            param->lotItemNum##n = item->new_count; \
            return; \
        } \
    }
    for (int i = config.alter_items_count - 1; i >= 0; i--) {
        struct alter_item_s* item = &config.alter_items[i];
        LOT_ITEM_NUM(01)
        LOT_ITEM_NUM(02)
        LOT_ITEM_NUM(03)
        LOT_ITEM_NUM(04)
        LOT_ITEM_NUM(05)
        LOT_ITEM_NUM(06)
        LOT_ITEM_NUM(07)
        LOT_ITEM_NUM(08)
    }
}

void on_param_initialized(void* userp) {
    (void)userp;
    const er_param_table_t* table = the_api->er_param_find_table(L"ItemLotParam_map");
    if (table != NULL) {
        er_param_table_iterate_begin(table, er_itemlot_param_t, param) {
            process_param_count(param, 1);
        } er_param_table_iterate_end();
    }
    table = the_api->er_param_find_table(L"ItemLotParam_enemy");
    if (table != NULL) {
        er_param_table_iterate_begin(table, er_itemlot_param_t, param) {
            process_param_rate(param);
            process_param_count(param, 2);
        } er_param_table_iterate_end();
    }
}

modloader_ext_def_t def = {
    "item_lot_rate",
    NULL,
    NULL,
    on_param_initialized
};

__declspec(dllexport)
modloader_ext_def_t* modloader_ext_init(modloader_ext_api_t* api) {
    the_api = api;
    return &def;
}

BOOL APIENTRY DllMain(HMODULE module, DWORD ul_reason_for_call, LPVOID reserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            load_config(module);
            break;
        case DLL_PROCESS_DETACH:
            if (config.include_goods != NULL) {
                LocalFree(config.include_goods);
                config.include_goods = NULL;
            }
            break;
    }
    return TRUE;
}
