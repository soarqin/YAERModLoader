/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "undname.h"

#include <string.h>

#define UNDNAME_MAX_COMPONENTS 32

typedef struct name_component_s {
    const char *start;
    size_t len;
} name_component_t;

static bool append_text(char *out, size_t out_size, size_t *pos, const char *text, size_t len) {
    if (*pos + len >= out_size) {
        return false;
    }
    memcpy(out + *pos, text, len);
    *pos += len;
    out[*pos] = '\0';
    return true;
}

bool undname_class(const char *mangled, char *out, size_t out_size) {
    name_component_t components[UNDNAME_MAX_COMPONENTS];
    size_t count = 0;
    const char *p;
    size_t out_pos = 0;

    if (out != NULL && out_size > 0) {
        out[0] = '\0';
    }

    if (mangled == NULL || out == NULL || out_size == 0) {
        return false;
    }

    if (strncmp(mangled, ".?AV", 4) != 0) {
        return false;
    }

    p = mangled + 4;
    for (;;) {
        const char *start = p;
        while (*p != '\0' && *p != '@') {
            p++;
        }

        if (p == start) {
            break;
        }

        if (count == UNDNAME_MAX_COMPONENTS) {
            return false;
        }

        components[count].start = start;
        components[count].len = (size_t)(p - start);
        count++;

        if (*p != '@') {
            return false;
        }
        p++;
    }

    if (count == 0 || *p != '@') {
        return false;
    }

    while (*p == '@') {
        p++;
    }
    if (*p != '\0') {
        return false;
    }

    for (size_t i = count; i > 0; i--) {
        const name_component_t *component = &components[i - 1];
        if (!append_text(out, out_size, &out_pos, component->start, component->len)) {
            return false;
        }
        if (i > 1 && !append_text(out, out_size, &out_pos, "::", 2)) {
            return false;
        }
    }

    return true;
}
