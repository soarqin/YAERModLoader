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

typedef struct spawn_request_s {
    int32_t one;
    int32_t item_id;
    int32_t quantity;
    int32_t duration;
    int32_t gem;
} spawn_request_t;

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

static int item_spawn_hook(void *map_item_man, spawn_request_t *request, uint32_t *output, uint32_t unk) {
    (void)map_item_man;
    (void)request;
    (void)output;
    (void)unk;
    fprintf(stderr, "item_spawn: %d, %d, %d, %d, %d\n", request->one, request->item_id, request->quantity, request->duration, request->gem);
    return item_spawn_return(map_item_man, request, output, unk);
}

static void clear_item_count() {
    item_count_t *item_count, *tmp;
    HASH_ITER(hh, item_count_map, item_count, tmp) {
        HASH_DEL(item_count_map, item_count);
        LocalFree(item_count);
    }
}

static void update_item_count(uint8_t *addr, int32_t count, int32_t max_count) {
    HANDLE process = GetCurrentProcess();
    addr += 4;
    for (; max_count > 0 && count > 0; max_count--, count--) {
        uint32_t item_id;
        if (ReadProcessMemory(process, addr, &item_id, sizeof(int32_t), NULL) && item_id > 0 && item_id != 0xFFFFFFFFu) {
            switch (item_id >> 28) {
                case 0:
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
        addr += 0x18; /* 0x14 for version < 1.12 */
    }
}

static void update_if_needed() {
    HANDLE process = GetCurrentProcess();
    uint8_t *addr;
    bool need_update = false;
    if (ReadProcessMemory(process, game_data_man, &addr, sizeof(uint8_t*), NULL) && addr) {
        uint8_t *player_addr;
        if (ReadProcessMemory(process, addr + 8, &player_addr, sizeof(uint8_t*), NULL) && player_addr) {
            uint8_t *inventory_addr;
            if (ReadProcessMemory(process, player_addr + 0x5D0, &inventory_addr, sizeof(uint8_t*), NULL) && inventory_addr) {
                /* 0x5B8 for version < 1.12 */
                uint32_t count;
                if (ReadProcessMemory(process, inventory_addr + 0x18, &count, sizeof(uint32_t), NULL) && count != inventory_item_count) {
                    inventory_item_count = count;
                    need_update = true;
                }
            }
            uint8_t *chest_addr;
            if (ReadProcessMemory(process, player_addr + 0x8D0, &chest_addr, sizeof(uint8_t*), NULL) && chest_addr) {
                /* 0x8B0 for version < 1.12 */
                uint32_t count;
                if (ReadProcessMemory(process, chest_addr + 0x18, &count, sizeof(uint32_t), NULL) && count != chest_item_count) {
                    chest_item_count = count;
                    need_update = true;
                }
            }
            if (need_update) {
                clear_item_count();
                if (ReadProcessMemory(process, inventory_addr + 0x10, &inventory_addr, sizeof(uint8_t*), NULL) && inventory_addr) {
                    update_item_count(inventory_addr, inventory_item_count, 2688);
                }
                if (ReadProcessMemory(process, chest_addr + 0x10, &chest_addr, sizeof(uint8_t*), NULL) && chest_addr) {
                    update_item_count(chest_addr, chest_item_count, 1920);
                }
            }
        }
    }
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
    the_api->hook(item_spawn, item_spawn_hook, (void**)&item_spawn_return);
}

void on_uninit(void* userp) {
    (void)userp;
    if (item_spawn != NULL) {
        the_api->unhook(item_spawn);
    }
}

modloader_ext_def_t def = {
    "no_dup_pick",
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
            break;
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}
