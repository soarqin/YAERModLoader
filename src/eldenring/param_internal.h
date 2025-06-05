/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include "param.h"

#ifdef __cplusplus
extern "C" {
#endif

extern bool er_param_load_table();
extern void er_param_unload();
extern const er_param_table_t *er_param_find_table(const wchar_t *name);

#ifdef __cplusplus
}
#endif
