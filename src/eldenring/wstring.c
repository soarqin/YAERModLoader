/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "wstring.h"

const wchar_t *wstring_impl_str(const wstring_impl_t *str) {
    if (sizeof(wchar_t) * str->capacity >= 15) {
        return str->string;
    }
    return (const wchar_t*)&str->string;
}

wchar_t *wstring_impl_str_mutable(wstring_impl_t *str) {
    if (sizeof(wchar_t) * str->capacity >= 15) {
        return str->string;
    }
    return (wchar_t*)&str->string;
}
