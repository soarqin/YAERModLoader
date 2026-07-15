/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <wchar.h>

void *ml_ext_get_module_image_base(const wchar_t *module_name, size_t *size);
uint8_t *ml_ext_sig_scan(void *base, size_t size, const char *pattern);
bool ml_ext_hook_init(void);
bool ml_ext_hook(void *target, void *detour, void **original);
void ml_ext_unhook(void *target);
void ml_ext_hook_uninit(void);
