/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <stdint.h>

typedef struct {
    void *unk;
    wchar_t *string;
    void *unk2;
    uint64_t length;
    uint64_t capacity;
} wstring_impl_t;

extern const wchar_t *wstring_impl_str(const wstring_impl_t *str);
extern wchar_t *wstring_impl_str_mutable(wstring_impl_t *str);
