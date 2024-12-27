/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <wchar.h>

extern void extdlls_add(const char *name, const wchar_t *path);
extern int extdlls_count();
extern void extdlls_load_all();
extern void extdlls_unload_all();
