/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <stdbool.h>

typedef enum ml_hook_result_e {
    ML_HOOK_APPLIED,
    ML_HOOK_SIGNATURE_NOT_FOUND,
    ML_HOOK_FAILED,
} ml_hook_result_t;

ml_hook_result_t ml_hook_install(void *target, void *detour, void **original);
const char *ml_hook_result_name(ml_hook_result_t result);
