/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Returns the initialized FD4 step function pointer for step_name, or NULL. */
extern void *fd4_step_find(const wchar_t *step_name);

#ifdef __cplusplus
}
#endif
