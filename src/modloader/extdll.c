/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "extdll.h"

#include "config.h"

#include "game/game.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct extdll_t {
    char *name;
    wchar_t *base_path;
    HMODULE dll_module;
    void *extension_object;

} extdll_t;

extdll_t *extdlls = NULL;
int extdll_count = 0;
int extdll_capacity = 0;

static bool is_elden_ring_extension(const char *name) {
    return lstrcmpA(name, "er_param") == 0 ||
           lstrcmpA(name, "almighty_kale") == 0 ||
           lstrcmpA(name, "itemlot_rate") == 0 ||
           lstrcmpA(name, "no_dup_loot") == 0 ||
           lstrcmpA(name, "autoloot") == 0;
}

void extdlls_add(const char *name, const wchar_t *path) {
    if (extdll_count >= extdll_capacity) {
        extdll_capacity = extdll_capacity == 0 ? 8 : extdll_capacity * 2;
        extdll_t *new_dlls = extdlls == NULL ? LocalAlloc(LMEM_ZEROINIT, extdll_capacity * sizeof(extdll_t)) : LocalReAlloc(extdlls, extdll_capacity * sizeof(extdll_t), LMEM_MOVEABLE | LMEM_ZEROINIT);
        if (new_dlls == NULL) {
            return;
        }
        extdlls = new_dlls;
    }
    extdll_t *extdll = &extdlls[extdll_count++];
    extdll->name = StrDupA(name);
    extdll->base_path = StrDupW(path);
}

int extdlls_count() {
    return extdll_count;
}

void extdlls_load_all() {
    const ml_game_descriptor_t *game = ml_game_context_get();
    if (game == NULL) {
        fwprintf(stderr, L"WARNING: external DLLs are disabled because the game context is unavailable\n");
        return;
    }
    for (int i = 0; i < extdll_count; i++) {
        HMODULE dll;
        const wchar_t *path = extdlls[i].base_path;
        if (game->id != ML_GAME_ELDEN_RING && is_elden_ring_extension(extdlls[i].name)) {
            fwprintf(stdout, L"Skipped external dll %hs outside Elden Ring\n", extdlls[i].name);
            continue;
        }
        if (StrChrW(path, L':') == NULL && path[0] != L'\\' && path[0] != L'/') {
            wchar_t full_path[MAX_PATH];
            config_full_path(full_path, path);
            dll = LoadLibraryW(full_path);
        } else {
            dll = LoadLibraryW(path);
        }
        extdlls[i].dll_module = dll;
        if (dll == NULL) {
            fwprintf(stderr, L"Cannot load external dll %hs from `%ls`\n", extdlls[i].name, path);
            continue;
        }
        fwprintf(stdout, L"Loaded external dll %hs from `%ls`\n", extdlls[i].name, path);
        extdlls[i].extension_object = NULL;
    }
    for (int i = 0; i < extdll_count; i++) {
        extdll_t *extdll = &extdlls[i];
        HMODULE dll = extdll->dll_module;
        if (!dll) continue;
        FARPROC me_ext_init = GetProcAddress(dll, "modengine_ext_init");
        if (!me_ext_init) continue;
        extdll->extension_object = NULL;
        if (!((bool(*)(void *, void **))me_ext_init)(NULL, &extdll->extension_object)) continue;
        fwprintf(stdout, L"Initialized external dll %hs (using modengine API)\n", extdll->name);
        fflush(stdout);
        if (!extdll->extension_object) continue;
        void **vtable = *(void***)extdll->extension_object;
        if (!vtable) continue;
        // Call ModEngineExtension::on_attach()
        ((void(*)(void *))vtable[1])(extdll->extension_object);
        // Call ModEngineExtension::id() to get the extension id
        fwprintf(stdout, L"Attached extension id: %hs\n", ((const char *(*)(void *))vtable[3])(extdll->extension_object));
    }
}

void extdlls_unload_all() {
    for (int i = extdll_count - 1; i >= 0; i--) {
        extdll_t *extdll = &extdlls[i];
        if (extdll->dll_module) {
            fwprintf(stdout, L"Uninitializing external dll %hs\n", extdll->name);
            fflush(stdout);
            if (extdll->extension_object) {
                void **vtable = *(void***)extdll->extension_object;
                if (vtable) {
                    // Call ModEngineExtension::on_detach()
                    ((void(*)(void*))vtable[2])(extdll->extension_object);
                }
                extdll->extension_object = NULL;
            }

            FreeLibrary(extdll->dll_module);
            extdll->dll_module = NULL;

            fwprintf(stdout, L"Uninitialized external dll %hs\n", extdll->name);
        }
        if (extdll->name) {
            LocalFree(extdll->name);
            extdll->name = NULL;
        }
        if (extdll->base_path) {
            LocalFree(extdll->base_path);
            extdll->base_path = NULL;
        }
    }
    LocalFree(extdlls);
    extdlls = NULL;
    extdll_count = 0;
    extdll_capacity = 0;
}
