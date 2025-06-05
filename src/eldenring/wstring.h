/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct er_wstring_impl_s {
    void *unk;
    wchar_t *string;
    void *unk2;
    uint64_t length;
    uint64_t capacity;
} er_wstring_impl_t;

extern const wchar_t *er_wstring_impl_str(const er_wstring_impl_t *str);
extern wchar_t *er_wstring_impl_str_mutable(er_wstring_impl_t *str);

#ifdef __cplusplus
}
#endif
