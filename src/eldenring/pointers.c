/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "pointers.h"

#include "process/image.h"
#include "process/scanner.h"

pointers_t pointers;

uint32_t pointers_init(uint32_t init) {
    uint32_t res = 0;
    size_t image_size;
    void *image_base = get_module_image_base(NULL, &image_size);
    if (init & INIT_CS_REGULATION_MANAGER) {
        if (pointers.cs_regulation_manager == NULL) {
            uint8_t *addr = sig_scan(image_base, image_size, "48 8B 0D ?? ?? ?? ?? 48 85 C9 74 0B 4C 8B C0 48 8B D7");
            if (addr != NULL) {
                uintptr_t offset = *(int32_t*)(addr + 3);
                pointers.cs_regulation_manager = addr + 7 + offset;
                res |= INIT_CS_REGULATION_MANAGER;
            }
        } else {
            res |= INIT_CS_REGULATION_MANAGER;
        }
    }
    return res;
}
