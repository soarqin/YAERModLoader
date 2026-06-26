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
} er_param_api_t;

typedef const er_param_api_t *(*er_param_api_get_t)(void);

#ifdef __cplusplus
}
#endif
