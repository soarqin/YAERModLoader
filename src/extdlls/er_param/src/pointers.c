/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>
 *
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

static void *scan_call_target(void *image_base, size_t image_size, const char *pattern, size_t offset) {
    uint8_t *addr = sig_scan(image_base, image_size, pattern);
    if (addr == NULL) {
        return NULL;
    }
    uint8_t *call_addr = addr + offset;
    int32_t rel = *(int32_t*)(call_addr + 1);
    return call_addr + 5 + rel;
}

static void *scan_function(void *image_base, size_t image_size, const char *pattern, ptrdiff_t offset) {
    uint8_t *addr = sig_scan(image_base, image_size, pattern);
    if (addr == NULL) {
        return NULL;
    }
    return addr + offset;
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

#define er_init_call_target(flag, name, pattern, offset) do { \
    if (init & flag) { \
        if (er_pointers.name == NULL) { \
            er_pointers.name = scan_call_target(image_base, image_size, pattern, offset); \
            if (er_pointers.name == NULL) break; \
        } \
        res |= flag; \
    } \
} while (0)

#define er_init_function(flag, name, pattern, offset) do { \
    if (init & flag) { \
        if (er_pointers.name == NULL) { \
            er_pointers.name = scan_function(image_base, image_size, pattern, offset); \
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
    er_init_indirect_pointer(INIT_MSG_REPOSITORY, msg_repository, "48 8B 3D ?? ?? ?? ?? 44 0F B6 30 48 85 FF 75", 3);
    er_init_indirect_pointer(INIT_GAME_DATA_MAN, game_data_man, "48 8B 05 ?? ?? ?? ?? 48 85 C0 74 05 48 8B 40 58 C3 C3", 3);
    er_init_call_target(INIT_LOOKUP_SHOP_MENU, lookup_shop_menu, "?? 8B 4E 14 ?? 8B 46 10 33 D2 48 8D 4D ?? E8 ?? ?? ?? ??", 14);
    er_init_function(INIT_LOOKUP_SHOP_LINEUP, lookup_shop_lineup, "48 8D 15 ?? ?? ?? ?? 45 33 C0 ?? ?? ?? E8 ?? ?? ?? ?? 48 85 C0 74 ??", -129);
    er_init_call_target(INIT_MSG_REPOSITORY_LOOKUP_ENTRY, msg_repository_lookup_entry, "8B DA 44 8B CA 33 D2 48 8B F9 44 8D 42 6F E8 ?? ?? ?? ??", 14);
    er_init_call_target(INIT_EZSTATE_ENTER_STATE, ezstate_enter_state, "80 7E 18 00 74 15 4C 8D 44 24 40 48 8B D6 48 8B 4E 20 E8 ?? ?? ?? ??", 18);
    er_init_function(INIT_EVENT_FLAG_GET, get_event_flag, "41 F7 F0 4C 8B D1 45 33 C9 44 0F AF C0 45 2B D8", -12);
    er_init_function(INIT_SELL_VALUE, get_sell_value, "83 CB FF 41 8B C0 C1 E8 1C 48 8B F1 83 F8 0F", -29);
    er_init_function(INIT_MAX_REPOSITORY_NUM, get_max_repository_num, "48 8B 5C 24 70 B8 58 02 00 00 48 8B 7C 24 78", -521);
    er_init_function(INIT_OPEN_REGULAR_SHOP, open_regular_shop, "4C 8B 49 18 48 8B D9 48 8D 4C 24 20 E8 ?? ?? ?? ?? 48 8D 4C 24 20 0F 10 00 C7 43 10 05 00 00 00", -6);
    return res;
}