/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <stddef.h>
#include <stdint.h>
#include <wchar.h>

const uint8_t *ml_find_utf16_string(const void *data, size_t size, const wchar_t *value);
const uint8_t *ml_find_rip_relative_lea(const uint8_t *text, size_t size, const void *target);
