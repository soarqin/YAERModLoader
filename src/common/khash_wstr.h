#ifndef KHASH_WSTR_H
#define KHASH_WSTR_H

#include <windows.h>
#include "khash.h"

static inline khint_t kh_wstr_hash_func(const wchar_t *s) {
    khint_t h = 2166136261u;
    const unsigned char *p = (const unsigned char *)s;
    size_t len = (size_t)lstrlenW(s) * sizeof(wchar_t);
    for (size_t i = 0; i < len; i++) {
        h ^= (khint_t)p[i];
        h *= 16777619u;
    }
    return h;
}

static inline int kh_wstr_hash_equal(const wchar_t *a, const wchar_t *b) {
    return wcscmp(a, b) == 0;
}

KHASH_INIT(wstr, const wchar_t*, void*, 1, kh_wstr_hash_func, kh_wstr_hash_equal)

#endif
