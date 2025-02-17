/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <stdint.h>

typedef enum {
    INIT_CS_REGULATION_MANAGER = 1,
    INIT_SOLO_PARAM_REPOSITORY = 2,
} pointers_init_flag_t;

typedef struct {
    void *cs_regulation_manager;
    void *solo_param_repository;
} pointers_t;

uint32_t pointers_init(uint32_t init);

extern pointers_t pointers;
