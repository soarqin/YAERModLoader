/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "pointers.h"

#include "process/image.h"
#include "process/scanner.h"

er_pointers_t er_pointers;

static void *scan_indirect_pointer(void *image_base, size_t image_size, const char *pattern, size_t offset) {
    uint8_t *addr = sig_scan(image_base, image_size, pattern);
    if (addr == NULL) {
        return NULL;
    }
    uintptr_t offset2 = *(int32_t*)(addr + offset);
    return addr + offset + 4 + offset2;
}

#define er_init_indirect_pointer(flag, name, pattern, offset) do { \
    if (init & flag) { \
        if (er_pointers.name == NULL) { \
            er_pointers.name = scan_indirect_pointer(image_base, image_size, pattern, offset); \
            if (er_pointers.name == NULL) break; \
        } \
        res |= flag; \
    } \
} while (0)

uint32_t er_pointers_init(uint32_t init) {
    uint32_t res = 0;
    size_t image_size;
    void *image_base = get_module_image_base(NULL, &image_size);
    er_init_indirect_pointer(INIT_CS_REGULATION_MANAGER, cs_regulation_manager, "48 8B 0D ?? ?? ?? ?? 48 85 C9 74 0B 4C 8B C0 48 8B D7", 3);
    er_init_indirect_pointer(INIT_SOLO_PARAM_REPOSITORY, solo_param_repository, "48 8B 0D ?? ?? ?? ?? 48 85 C9 0F 84 ?? ?? ?? ?? 45 33 C0 BA 8D 00 00 00 E8", 3);
    return res;
}
