/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "ext_shared.h"

#include <windows.h>
#include <shlwapi.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#define kcalloc(N,Z)   LocalAlloc(LPTR, (N)*(Z))
#define kmalloc(Z)     LocalAlloc(0, (Z))
#define krealloc(P,Z)  ((P) ? LocalReAlloc((P), (Z), LMEM_MOVEABLE) : LocalAlloc(0, (Z)))
#define kfree(P)       LocalFree(P)
#include "khash.h"
KHASH_MAP_INIT_INT(item_count, int32_t)

#pragma pack(push, 1)

typedef struct spawn_item_s {
    int32_t item_id;
    int32_t quantity;
    int32_t duration;
    int32_t gem;
} spawn_item_t;

typedef struct spawn_request_s {
    int32_t count;
    spawn_item_t items[0];
} spawn_request_t;

#pragma pack(pop)

static uint8_t *item_spawn = NULL;
static uint8_t *game_data_man = NULL;
static int (*item_spawn_return)(void *map_item_man, spawn_request_t *request, uint32_t *output, uint32_t unk) = NULL;

static int inventory_item_count = 0;
static int chest_item_count = 0;

static khash_t(item_count) *item_count_map = NULL;

static void clear_item_count() {
    khiter_t k;
    for (k = kh_begin(item_count_map); k != kh_end(item_count_map); ++k) {
        if (kh_exist(item_count_map, k)) {
            kh_value(item_count_map, k) = 0;
        }
    }
}

static void update_item_count(uint8_t *addr, int32_t count, int32_t max_count) {
    HANDLE process = GetCurrentProcess();
    addr += 4;
    for (; max_count > 0 && count > 0; max_count--, addr += 0x18/* 0x14 for version < 1.12 */) {
        uint32_t item_id;
        if (ReadProcessMemory(process, addr, &item_id, sizeof(int32_t), NULL) && item_id > 0 && item_id != 0xFFFFFFFFu) {
            count--;
            switch (item_id >> 28) {
                case 0:
                    if (item_id >= 50000000 && item_id < 60000000) {
                        continue;
                    }
                    item_id = item_id / 10000 * 10000;
                    /* fall through */
                case 1:
                    break;
                case 2:
                    if (item_id == 6070) continue; /* Sacrificial Twig - skip to allow stacking */
                    break;
                default:
                    continue;
            }
            int ret;
            khiter_t k = kh_get(item_count, item_count_map, item_id);
            if (k != kh_end(item_count_map)) {
                kh_value(item_count_map, k)++;
            } else {
                k = kh_put(item_count, item_count_map, item_id, &ret);
                kh_value(item_count_map, k) = 1;
            }
        }
    }
}

static void update_if_needed() {
    HANDLE process = GetCurrentProcess();
    uint8_t *addr = (uint8_t*)*(uintptr_t*)game_data_man;
    if (addr) {
        uint8_t *player_addr = (uint8_t*)*(uintptr_t*)(addr + 8);
        if (player_addr) {
            bool need_update = false;
            /* 0x5B8 for version < 1.12 */
            uint8_t *inventory_addr = (uint8_t*)*(uintptr_t*)(player_addr + 0x5D0);
            if (inventory_addr) {
                uint32_t count = *(uint32_t*)(inventory_addr + 0x18);
                if (count != inventory_item_count) {
                    inventory_item_count = count;
                    need_update = true;
                }
            }
            /* 0x8B0 for version < 1.12 */
            uint8_t *chest_addr = (uint8_t*)*(uintptr_t*)(player_addr + 0x8D0);
            if (chest_addr) {
                uint32_t count = *(uint32_t*)(chest_addr + 0x18);
                if (count != chest_item_count) {
                    chest_item_count = count;
                    need_update = true;
                }
            }
            if (need_update) {
                clear_item_count();
                uint8_t *item_addr = (uint8_t*)*(uintptr_t*)(inventory_addr + 0x10);
                if (item_addr) {
                    update_item_count(item_addr, inventory_item_count, 2688);
                }
                item_addr = (uint8_t*)*(uintptr_t*)(chest_addr + 0x10);
                if (item_addr) {
                    update_item_count(item_addr, chest_item_count, 1920);
                }
            }
        }
    }
}

static int item_spawn_hook(void *map_item_man, spawn_request_t *request, uint32_t *output, uint32_t unk) {
    bool updated = false;
    for (int i = 0; i < request->count; i++) {
        spawn_item_t *item = &request->items[i];
        uint32_t item_id = item->item_id;
        switch (item_id >> 28) {
            case 0:
                if (item_id >= 50000000 && item_id < 60000000) {
                    break;
                }
                if (!updated) {
                    update_if_needed();
                    updated = true;
                }
                item_id = item_id / 10000 * 10000;
                {
                    int ret;
                    khiter_t k = kh_get(item_count, item_count_map, item_id);
                    int found = (k != kh_end(item_count_map));
                    if (found && kh_value(item_count_map, k) >= 2) {
                        item->item_id = 0;
                        item->quantity = 0;
                        continue;
                    }
                    if (found) {
                        kh_value(item_count_map, k)++;
                    } else {
                        k = kh_put(item_count, item_count_map, item_id, &ret);
                        kh_value(item_count_map, k) = 1;
                        inventory_item_count++;
                    }
                }
                break;
            case 1:
            case 2:
                if (!updated) {
                    update_if_needed();
                    updated = true;
                }
                {
                    int ret;
                    khiter_t k = kh_get(item_count, item_count_map, item_id);
                    int found = (k != kh_end(item_count_map));
                    if (found && kh_value(item_count_map, k) >= 1) {
                        item->item_id = 0;
                        item->quantity = 0;
                        continue;
                    }
                    if (found) {
                        kh_value(item_count_map, k)++;
                    } else {
                        k = kh_put(item_count, item_count_map, item_id, &ret);
                        kh_value(item_count_map, k) = 1;
                        inventory_item_count++;
                    }
                }
                break;
            default:
                break;
        }
    }
    return item_spawn_return(map_item_man, request, output, unk);
}

static void init() {
    if (!ml_ext_hook_init()) return;
    size_t size;
    void* base = ml_ext_get_module_image_base(NULL, &size);
    if (base == NULL) {
        return;
    }
    item_count_map = kh_init(item_count);
    item_spawn = ml_ext_sig_scan(base, size, "40 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 48 C7 45 ?? ?? ?? ?? ?? 48 89 9C 24 ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 44 89 4C 24");
    if (item_spawn == NULL) {
        return;
    }
    game_data_man = ml_ext_sig_scan(base, size, "48 8B 05 ?? ?? ?? ?? 48 85 C0 74 05 48 8B 40 58 C3 C3");
    if (game_data_man == NULL) {
        item_spawn = NULL;
        return;
    }
    game_data_man += *(int32_t*)(game_data_man + 3) + 7;
    ml_ext_hook(item_spawn, item_spawn_hook, (void**)&item_spawn_return);
}

static void on_uninit(void* userp) {
    (void)userp;
    if (item_spawn != NULL) {
        ml_ext_unhook(item_spawn);
    }
    if (item_count_map != NULL) {
        kh_destroy(item_count, item_count_map);
        item_count_map = NULL;
    }
}

BOOL APIENTRY DllMain(HMODULE module, DWORD ul_reason_for_call, LPVOID reserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(module);
            init();
            break;
        case DLL_PROCESS_DETACH:
            on_uninit(NULL);
            ml_ext_hook_uninit();
            break;
    }
    return TRUE;
}
