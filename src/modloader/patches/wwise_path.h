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
#include <wchar.h>

const wchar_t *wwise_strip_prefixes(const wchar_t *path);
bool wwise_wem_candidates(const wchar_t *path, wchar_t *first, size_t first_count,
                          wchar_t *second, size_t second_count);
