/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

extern bool common_install();
extern bool common_install_ime();
extern bool common_wwise_requested();
extern bool common_install_wwise();
extern void common_uninstall();

#ifdef __cplusplus
}
#endif
