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

typedef enum {
    INIT_CS_REGULATION_MANAGER = 1,
    INIT_SOLO_PARAM_REPOSITORY = 2,
} er_pointers_init_flag_t;

typedef struct {
    void *cs_regulation_manager;
    void *solo_param_repository;
} er_pointers_t;

uint32_t er_pointers_init(uint32_t init);

extern er_pointers_t er_pointers;

#ifdef __cplusplus
}
#endif
