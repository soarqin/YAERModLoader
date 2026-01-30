/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include <modloader/extdll_api.h>

#define uthash_malloc(sz) LocalAlloc(0, sz)
#define uthash_free(ptr,sz) LocalFree(ptr)
#define uthash_bzero(a,n) ZeroMemory(a, n)
#include <uthash.h>

#include <windows.h>
#include <shlwapi.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

static modloader_ext_api_t* the_api;

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

static void *item_spawn = NULL;
static void *game_data_man = NULL;
static int (*item_spawn_return)(void *map_item_man, spawn_request_t *request, uint32_t *output, uint32_t unk) = NULL;

static int inventory_item_count = 0;
static int chest_item_count = 0;

typedef struct item_count_s {
    uint32_t item_id;   /* 0x00 */
    int32_t count;
    UT_hash_handle hh;
} item_count_t;

static item_count_t *item_count_map = NULL;

static void clear_item_count() {
    item_count_t *item_count, *tmp;
    HASH_ITER(hh, item_count_map, item_count, tmp) {
        item_count->count = 0;
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
                    /* fall through */
                case 1:
                case 2:
                    break;
                default:
                    continue;
            }
            item_count_t *item_count = NULL;
            HASH_FIND_INT(item_count_map, &item_id, item_count);
            if (item_count) {
                item_count->count++;
            } else {
                item_count = LocalAlloc(0, sizeof(item_count_t));
                item_count->item_id = item_id;
                item_count->count = 1;
                HASH_ADD_INT(item_count_map, item_id, item_count);
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
    item_count_t *item_count = NULL;
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
                HASH_FIND_INT(item_count_map, &item_id, item_count);
                if (item_count && item_count->count >= 2) {
                    item->item_id = 0;
                    item->quantity = 0;
                    continue;
                }
                if (item_count) {
                    item_count->count++;
                } else {
                    item_count = LocalAlloc(0, sizeof(item_count_t));
                    item_count->item_id = item_id;
                    item_count->count = 1;
                    HASH_ADD_INT(item_count_map, item_id, item_count);
                    inventory_item_count++;
                }
                break;
            case 1:
            case 2:
                if (!updated) {
                    update_if_needed();
                    updated = true;
                }
                HASH_FIND_INT(item_count_map, &item_id, item_count);
                if (item_count && item_count->count >= 1) {
                    item->item_id = 0;
                    item->quantity = 0;
                    continue;
                }
                if (item_count) {
                    item_count->count++;
                } else {
                    item_count = LocalAlloc(0, sizeof(item_count_t));
                    item_count->item_id = item_id;
                    item_count->count = 1;
                    HASH_ADD_INT(item_count_map, item_id, item_count);
                    inventory_item_count++;
                }
                break;
            default:
                break;
        }
    }
    return item_spawn_return(map_item_man, request, output, unk);
}

static void init() {
    size_t size;
    void* base = the_api->get_module_image_base(NULL, &size);
    if (base == NULL) {
        return;
    }
    item_spawn = the_api->sig_scan(base, size, "40 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 48 C7 45 ?? ?? ?? ?? ?? 48 89 9C 24 ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 44 89 4C 24");
    if (item_spawn == NULL) {
        return;
    }
    game_data_man = the_api->sig_scan(base, size, "48 8B 05 ?? ?? ?? ?? 48 85 C0 74 05 48 8B 40 58 C3 C3");
    if (game_data_man == NULL) {
        item_spawn = NULL;
        return;
    }
    game_data_man += *(int32_t*)(game_data_man + 3) + 7;
    the_api->hook(item_spawn, item_spawn_hook, (void**)&item_spawn_return);
}

void on_uninit(void* userp) {
    (void)userp;
    if (item_spawn != NULL) {
        the_api->unhook(item_spawn);
    }
}

modloader_ext_def_t def = {
    "no_dup_loot",
    NULL,
    on_uninit,
    NULL
};

__declspec(dllexport)
modloader_ext_def_t* modloader_ext_init(modloader_ext_api_t* api) {
    the_api = api;
    init();
    return &def;
}

BOOL APIENTRY DllMain(HMODULE module, DWORD ul_reason_for_call, LPVOID reserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(module);
            break;
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}
