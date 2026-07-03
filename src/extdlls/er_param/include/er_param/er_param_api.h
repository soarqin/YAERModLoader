/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include <er_param/param.h>

/* Forward declarations: er_msg_repository_imp_t and er_game_data_man_t are
 * used only as opaque pointer types in the API struct, so consumers of
 * er_param_api.h don't need to pull in from/messages.h or from/game_data.h
 * (which would force recompilation of unrelated extdlls when those headers
 * change). Consumers that need the full struct layouts include the
 * corresponding from/ headers explicitly. */
typedef struct er_msg_repository_imp_s er_msg_repository_imp_t;
typedef struct er_game_data_man_s er_game_data_man_t;
typedef struct er_wstring_impl_s er_wstring_impl_t;

#ifdef __cplusplus
extern "C" {
#endif

typedef struct er_param_api_s {
    uint32_t api_version;
    const er_param_table_t *(*find_table)(const wchar_t *name);
    const wchar_t *(*wstring_str)(const er_wstring_impl_t *str);

    bool (*is_loaded)(void);
    bool (*on_param_loaded)(void (*cb)(void *userp), void *userp);
    void (*off_param_loaded)(void (*cb)(void *userp), void *userp);

    /* API v2 additions (appended; existing field offsets preserved). Each
     * accessor returns the scanned runtime address/pointer, or NULL if the
     * signature did not resolve. The msg_repository / game_data_man accessors
     * dereference the indirect pointer slot (may be NULL until the game
     * initializes it). */
    er_msg_repository_imp_t *(*get_msg_repository)(void);
    er_game_data_man_t *(*get_game_data_man)(void);
    void *(*get_lookup_shop_menu)(void);
    void *(*get_lookup_shop_lineup)(void);
    void *(*get_msg_repository_lookup_entry)(void);
    void *(*get_ezstate_enter_state)(void);
    void *(*get_get_event_flag)(void);
    void *(*get_get_sell_value)(void);
    void *(*get_get_max_repository_num)(void);
    void *(*get_open_regular_shop)(void);
} er_param_api_t;

typedef const er_param_api_t *(*er_param_api_get_t)(void);

#ifdef __cplusplus
}
#endif
