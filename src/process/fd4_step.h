/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <stddef.h>
#include <stdint.h>
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct fd4_time_s {
    uintptr_t vtable;
    float time;
} fd4_time_t;

typedef void (__cdecl *fd4_step_fn_t)(void *this_ptr, fd4_time_t *time);

_Static_assert(offsetof(fd4_time_t, vtable) == 0, "fd4_time_t vtable offset");
_Static_assert(offsetof(fd4_time_t, time) == sizeof(uintptr_t), "fd4_time_t time offset");
_Static_assert(sizeof(fd4_time_t) == 16, "fd4_time_t size");

/* Returns the initialized FD4 step function pointer for step_name, or NULL. */
extern void *fd4_step_find(const wchar_t *step_name);

#ifdef __cplusplus
}
#endif
