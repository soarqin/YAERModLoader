/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "extdll.h"

#include "allocator.h"

#include "config.h"
#include "log.h"
#include "game/game.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>
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

void extdlls_add(const char *name, const wchar_t *path) {
    if (extdll_count >= extdll_capacity) {
        extdll_capacity = extdll_capacity == 0 ? 8 : extdll_capacity * 2;
        extdll_t *new_dlls = extdlls == NULL ? yaer_mem_alloc(LMEM_ZEROINIT, extdll_capacity * sizeof(extdll_t)) : yaer_mem_realloc(extdlls, extdll_capacity * sizeof(extdll_t), LMEM_MOVEABLE | LMEM_ZEROINIT);
        if (new_dlls == NULL) {
            return;
        }
        extdlls = new_dlls;
    }
    extdll_t *extdll = &extdlls[extdll_count++];
    extdll->name = yaer_mem_strdup_a(name);
    extdll->base_path = yaer_mem_strdup_w(path);
}

int extdlls_count() {
    return extdll_count;
}

void extdlls_load_all() {
    if (ml_game_context_get() == NULL) {
        ML_LOG_WARN(L"extdll", L"external DLLs are disabled because the game context is unavailable");
        return;
    }
    for (int i = 0; i < extdll_count; i++) {
        HMODULE dll;
        const wchar_t *path = extdlls[i].base_path;
        if (StrChrW(path, L':') == NULL && path[0] != L'\\' && path[0] != L'/') {
            wchar_t full_path[MAX_PATH];
            config_full_path(full_path, path);
            dll = LoadLibraryW(full_path);
        } else {
            dll = LoadLibraryW(path);
        }
        extdlls[i].dll_module = dll;
        if (dll == NULL) {
            ML_LOG_ERROR(L"extdll", L"cannot load external DLL %hs from `%ls`", extdlls[i].name, path);
            continue;
        }
        ML_LOG_INFO(L"extdll", L"loaded external DLL %hs from `%ls`", extdlls[i].name, path);
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
        ML_LOG_INFO(L"extdll", L"initialized external DLL %hs using ModEngine API", extdll->name);
        if (!extdll->extension_object) continue;
        void **vtable = *(void***)extdll->extension_object;
        if (!vtable) continue;
        // Call ModEngineExtension::on_attach()
        ((void(*)(void *))vtable[1])(extdll->extension_object);
        // Call ModEngineExtension::id() to get the extension id
        ML_LOG_INFO(L"extdll", L"attached extension ID: %hs",
                    ((const char *(*)(void *))vtable[3])(extdll->extension_object));
    }
}

void extdlls_unload_all() {
    for (int i = extdll_count - 1; i >= 0; i--) {
        extdll_t *extdll = &extdlls[i];
        if (extdll->dll_module) {
            ML_LOG_INFO(L"extdll", L"uninitializing external DLL %hs", extdll->name);
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

            ML_LOG_INFO(L"extdll", L"uninitialized external DLL %hs", extdll->name);
        }
        if (extdll->name) {
            yaer_mem_free(extdll->name);
            extdll->name = NULL;
        }
        if (extdll->base_path) {
            yaer_mem_free(extdll->base_path);
            extdll->base_path = NULL;
        }
    }
    yaer_mem_free(extdlls);
    extdlls = NULL;
    extdll_count = 0;
    extdll_capacity = 0;
}
