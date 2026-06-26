/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct modloader_ext_def_s {
    const char *name;

    void *userp;

    void (*on_uninit)(void*);
} modloader_ext_def_t;

typedef struct modloader_ext_api_s {
    /* Common API */
    void *(*get_module_image_base)(const wchar_t *module_name, size_t *size);
    uint8_t *(*sig_scan)(void *base, size_t size, const char *pattern);

    /* Hook API */
    void (*hook)(void *target, void *detour, void **original);
    void (*unhook)(void *hook);
} modloader_ext_api_t;

typedef modloader_ext_def_t *(*modloader_ext_init_t)(modloader_ext_api_t *api);

#ifdef __cplusplus
}
#endif
