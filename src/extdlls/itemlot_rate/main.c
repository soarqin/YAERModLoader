/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include <modloader/extdll_api.h>
#include <eldenring/param.h>
#include <eldenring/defs/itemlot_param.h>

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

static modloader_ext_api_t* the_api;

void process_param(er_itemlot_param_t* param) {
#define PARAM_IS_MISSABLE_EQUIPMENT(n) bool is_missable_##n = param->lotItemBasePoint##n > 0 && param->lotItemBasePoint##n < 1000 && (param->lotItemCategory##n == 3 || param->lotItemCategory##n == 2 && (param->lotItemId##n < 43100000 || param->lotItemId##n >= 60000000))
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
        PROCESS_PARAM(01);
        PROCESS_PARAM(02);
        PROCESS_PARAM(03);
        PROCESS_PARAM(04);
        PROCESS_PARAM(05);
        PROCESS_PARAM(06);
        PROCESS_PARAM(07);
        PROCESS_PARAM(08);
        param->cumulateNumMax = 0;
    }
#undef PARAM_IS_MISSABLE_EQUIPMENT
#undef PROCESS_PARAM
}

void on_param_initialized(void* userp) {
    (void)userp;
    const er_param_table_t* table = the_api->er_param_find_table(L"ItemLotParam_enemy");
    if (table == NULL) {
        return;
    }

    er_param_table_iterate_begin(table, er_itemlot_param_t, param) {
        process_param(param);
    } er_param_table_iterate_end();
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
