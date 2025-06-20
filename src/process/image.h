/*
 * Copyright (C) 2024,2005 Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void *get_module_image_base(const wchar_t *module_name, size_t *size);

#ifdef __cplusplus
}
#endif
