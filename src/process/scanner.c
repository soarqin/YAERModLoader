/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "scanner.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdbool.h>

uint8_t *sig_scan_without_mask(void *base, size_t size, const uint8_t *pattern, size_t pattern_size) {
    size_t end = size - pattern_size;
    uint8_t *u8_base = base;
    for (size_t i = 0; i < end; i++) {
        if (memcmp(pattern, u8_base + i, pattern_size) != 0) continue;
        return u8_base + i;
    }
    return NULL;
}

uint8_t *sig_scan_with_mask(void *base, size_t size, const uint8_t *pattern, const uint8_t *mask, size_t pattern_size) {
    size_t end = size - pattern_size;
    uint8_t *u8_curr = base;
    uint8_t *u8_end = u8_curr + end;
    while (u8_curr < u8_end) {
        for (size_t i = 0; i < pattern_size; i++) {
            switch (mask[i]) {
                case 0:
                    continue;
                case 0xFF:
                    if (pattern[i] != u8_curr[i])
                        goto next;
                    break;
                default:
                    if ((pattern[i] & mask[i]) != (u8_curr[i] & mask[i]))
                        goto next;
                    break;
            }
        }
        return u8_curr;
    next:
        u8_curr++;
    }
    return NULL;
}

size_t sig_build_pattern_with_mask(const char *pattern, uint8_t *out_pattern, uint8_t *out_mask, size_t out_size) {
    static const uint8_t char_table[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0,
        0, 10, 11, 12, 13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 10, 11, 12, 13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    size_t pattern_size = 0;
    bool second_char = false;
    while (*pattern) {
        switch (*pattern) {
            case '\t': case '\v': case ' ': case '\r': case '\n':
                if (second_char) {
                    if (out_mask[pattern_size] == 0xF)
                        out_mask[pattern_size] = 0xFF;
                    pattern_size++;
                    second_char = false;
                }
                pattern++;
                break;
            case '?':
                if (second_char) {
                    out_mask[pattern_size] <<= 4;
                    out_pattern[pattern_size] <<= 4;
                    pattern_size++;
                    second_char = false;
                } else {
                    if (pattern_size >= out_size) {
                        return (size_t)-1;
                    }
                    out_mask[pattern_size] = 0x00;
                    out_pattern[pattern_size] = 0x00;
                    second_char = true;
                }
                pattern++;
                break;
            case '0' ... '9':
            case 'a' ... 'f':
            case 'A' ... 'F':
                if (second_char) {
                    out_mask[pattern_size] <<= 4;
                    out_pattern[pattern_size] <<= 4;
                    out_mask[pattern_size] |= 0xF;
                    out_pattern[pattern_size] |= char_table[*pattern];
                    pattern_size++;
                    second_char = false;
                } else {
                    if (pattern_size >= out_size) {
                        return (size_t)-1;
                    }
                    out_mask[pattern_size] = 0xF;
                    out_pattern[pattern_size] = char_table[*pattern];
                    second_char = true;
                }
                pattern++;
                break;
            default:
                return (size_t)-2;
        }
    }
    if (second_char) {
        if (out_mask[pattern_size] == 0xF)
            out_mask[pattern_size] = 0xFF;
        pattern_size++;
    }
    return pattern_size;
}

uint8_t *sig_scan(void *base, size_t size, const char *pattern) {
    size_t out_size = 64;
    for (;;) {
        uint8_t *out_pattern = LocalAlloc(0, out_size);
        uint8_t *out_mask = LocalAlloc(0, out_size);
        size_t pattern_size = sig_build_pattern_with_mask(pattern, out_pattern, out_mask, out_size);
        if (pattern_size == (size_t)-2) return NULL;
        if (pattern_size == (size_t)-1) {
            out_size <<= 1;
            continue;
        }
        bool any_mask_not_0xff = false;
        for (size_t i = 0; i < pattern_size; i++) {
            if (out_mask[i] != 0xFF) {
                any_mask_not_0xff = true;
                break;
            }
        }
        uint8_t *res = any_mask_not_0xff ?
            sig_scan_with_mask(base, size, out_pattern, out_mask, pattern_size) :
            sig_scan_without_mask(base, size, out_pattern, pattern_size);
        LocalFree(out_pattern);
        LocalFree(out_mask);
        return res;
    }
}
