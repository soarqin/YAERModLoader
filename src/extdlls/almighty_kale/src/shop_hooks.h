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

#include <stddef.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Mirrors the game's from::find_shop_menu_result layout. Field offsets must
 * match the game's in-memory layout (shop_type@0, id@4, row@8) so the
 * lookup_shop_menu/lookup_shop_lineup detours write result->row to the
 * exact offset the game reads from. Defined here (and not in
 * er_param/from/messages.h) because only almighty_kale uses it; changing
 * the layout only invalidates this extdll. */
typedef struct ak_find_shop_menu_result_s {
    unsigned char shop_type;
    int id;
    const er_shop_lineup_param_t *row;
} ak_find_shop_menu_result_t;

static_assert(offsetof(ak_find_shop_menu_result_t, shop_type) == 0, "shop_type must be at offset 0");
static_assert(offsetof(ak_find_shop_menu_result_t, id) == 4, "id must be at offset 4");
static_assert(offsetof(ak_find_shop_menu_result_t, row) == 8, "row must be at offset 8");
static_assert(sizeof(ak_find_shop_menu_result_t) == 16, "find_shop_menu_result must be 16 bytes");

void ak_setup_shop_hooks(void);
void ak_unhook_shop_hooks(void);

#ifdef __cplusplus
}
#endif