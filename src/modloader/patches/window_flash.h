/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include "modloader/hook.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

ml_hook_result_t ml_window_flash_install(void);
void ml_window_class_blacken(const WNDCLASSEXW *source, HBRUSH background, WNDCLASSEXW *result);
