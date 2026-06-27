/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* Returns the singleton instance pointer for name, or NULL. */
extern void *singleton_find(const char *name);

#ifdef __cplusplus
}
#endif
