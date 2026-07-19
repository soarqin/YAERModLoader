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
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct extdll_t {
    char *name;
    wchar_t *base_path;
    bool early;
    bool effective_early;
    bool delayed;
    uint32_t delay_ms;
    char **after;
    int after_count;
    int after_capacity;
    HMODULE dll_module;
    void *extension_object;
    uint32_t load_order;
} extdll_t;

static extdll_t *extdlls = NULL;
static int extdll_count = 0;
static int extdll_capacity = 0;
static uint32_t load_counter = 0;

static bool extdlls_reserve(int capacity) {
    extdll_t *new_dlls;
    if (capacity <= extdll_capacity) return true;
    new_dlls = extdlls == NULL
        ? yaer_mem_alloc(LMEM_ZEROINIT, (size_t)capacity * sizeof(*extdlls))
        : yaer_mem_realloc(extdlls, (size_t)capacity * sizeof(*extdlls), LMEM_MOVEABLE | LMEM_ZEROINIT);
    if (new_dlls == NULL) return false;
    extdlls = new_dlls;
    extdll_capacity = capacity;
    return true;
}

static bool extdll_after_add(extdll_t *extdll, const char *name) {
    char **new_after;
    if (extdll->after_count >= extdll->after_capacity) {
        int capacity = extdll->after_capacity == 0 ? 4 : extdll->after_capacity * 2;
        new_after = extdll->after == NULL
            ? yaer_mem_alloc(LMEM_ZEROINIT, (size_t)capacity * sizeof(*extdll->after))
            : yaer_mem_realloc(extdll->after, (size_t)capacity * sizeof(*extdll->after),
                               LMEM_MOVEABLE | LMEM_ZEROINIT);
        if (new_after == NULL) return false;
        extdll->after = new_after;
        extdll->after_capacity = capacity;
    }
    extdll->after[extdll->after_count] = yaer_mem_strdup_a(name);
    if (extdll->after[extdll->after_count] == NULL) return false;
    extdll->after_count++;
    return true;
}

static bool parse_delay(const char *value, uint32_t *delay_ms) {
    char *end;
    unsigned long parsed;
    if (value == NULL || value[0] < '0' || value[0] > '9') return false;
    errno = 0;
    parsed = strtoul(value, &end, 10);
    if (errno == ERANGE || end == value || *end != '\0' || parsed > UINT32_MAX) return false;
    *delay_ms = (uint32_t)parsed;
    return true;
}

void extdlls_add(const char *name, const wchar_t *path) {
    extdll_t *extdll;
    if (name == NULL || path == NULL) return;
    if (extdll_count >= extdll_capacity &&
        !extdlls_reserve(extdll_capacity == 0 ? 8 : extdll_capacity * 2)) return;
    extdll = &extdlls[extdll_count++];
    memset(extdll, 0, sizeof(*extdll));
    extdll->name = yaer_mem_strdup_a(name);
    extdll->base_path = yaer_mem_strdup_w(path);
    extdll->effective_early = false;
    if (extdll->name == NULL || extdll->base_path == NULL) {
        if (extdll->name != NULL) yaer_mem_free(extdll->name);
        if (extdll->base_path != NULL) yaer_mem_free(extdll->base_path);
        memset(extdll, 0, sizeof(*extdll));
        extdll_count--;
    }
}

void extdlls_add_spec(const char *name, const char *value) {
    char *spec;
    char *condition;
    char *next;
    wchar_t path[MAX_PATH];
    extdll_t *extdll;

    if (name == NULL || value == NULL) return;
    if (extdll_count >= extdll_capacity &&
        !extdlls_reserve(extdll_capacity == 0 ? 8 : extdll_capacity * 2)) return;
    spec = yaer_mem_strdup_a(value);
    if (spec == NULL) return;
    condition = strchr(spec, '|');
    if (condition != NULL) *condition++ = '\0';
    if (spec[0] == '\0' || MultiByteToWideChar(CP_UTF8, 0, spec, -1, path, MAX_PATH) == 0) {
        ML_LOG_ERROR(L"extdll", L"invalid external DLL path for %hs", name);
        yaer_mem_free(spec);
        return;
    }
    path[MAX_PATH - 1] = L'\0';

    extdll = &extdlls[extdll_count++];
    memset(extdll, 0, sizeof(*extdll));
    extdll->name = yaer_mem_strdup_a(name);
    extdll->base_path = yaer_mem_strdup_w(path);
    if (extdll->name == NULL || extdll->base_path == NULL) {
        ML_LOG_ERROR(L"extdll", L"cannot allocate external DLL configuration for %hs", name);
        if (extdll->name != NULL) yaer_mem_free(extdll->name);
        if (extdll->base_path != NULL) yaer_mem_free(extdll->base_path);
        memset(extdll, 0, sizeof(*extdll));
        extdll_count--;
        yaer_mem_free(spec);
        return;
    }
    while (condition != NULL && condition[0] != '\0') {
        next = strchr(condition, '|');
        if (next != NULL) *next++ = '\0';
        if (strcmp(condition, "early") == 0) {
            extdll->early = true;
            extdll->effective_early = true;
        } else if (strncmp(condition, "delay,", 6) == 0) {
            uint32_t delay_ms;
            if (!parse_delay(condition + 6, &delay_ms)) {
                ML_LOG_ERROR(L"extdll", L"invalid delay condition for %hs: %hs", name, condition);
            } else {
                extdll->delayed = true;
                extdll->delay_ms = delay_ms;
            }
        } else if (strncmp(condition, "after,", 6) == 0 && condition[6] != '\0') {
            if (!extdll_after_add(extdll, condition + 6)) {
                ML_LOG_ERROR(L"extdll", L"cannot allocate dependency for %hs", name);
            }
        } else {
            ML_LOG_WARN(L"extdll", L"unknown condition for %hs: %hs", name, condition);
        }
        condition = next;
    }
    yaer_mem_free(spec);
}

int extdlls_count() {
    return extdll_count;
}

static int extdll_index_by_name(const char *name) {
    for (int i = 0; i < extdll_count; i++) {
        if (strcmp(extdlls[i].name, name) == 0) return i;
    }
    return -1;
}

static bool extdll_has_unique_dependency(const extdll_t *extdll, int dependency_index, int before) {
    const char *dependency_name = extdlls[dependency_index].name;
    for (int i = 0; i < before; i++) {
        if (strcmp(extdll->after[i], dependency_name) == 0) return false;
    }
    return true;
}

void extdlls_prepare() {
    unsigned char *selected;
    int *indegree;
    int *order;
    extdll_t *sorted;
    int output_count = 0;

    if (extdll_count < 2) {
        if (extdll_count == 1) extdlls[0].effective_early = extdlls[0].early;
        return;
    }
    selected = yaer_mem_alloc(LMEM_ZEROINIT, (size_t)extdll_count * sizeof(*selected));
    indegree = yaer_mem_alloc(LMEM_ZEROINIT, (size_t)extdll_count * sizeof(*indegree));
    order = yaer_mem_alloc(0, (size_t)extdll_count * sizeof(*order));
    if (selected == NULL || indegree == NULL || order == NULL) {
        ML_LOG_ERROR(L"extdll", L"cannot allocate external DLL dependency sorter");
        yaer_mem_free(selected);
        yaer_mem_free(indegree);
        yaer_mem_free(order);
        return;
    }

    for (int i = 0; i < extdll_count; i++) {
        for (int j = 0; j < extdlls[i].after_count; j++) {
            int dependency = extdll_index_by_name(extdlls[i].after[j]);
            if (dependency < 0) {
                ML_LOG_WARN(L"extdll", L"external DLL %hs depends on missing DLL %hs",
                            extdlls[i].name, extdlls[i].after[j]);
                continue;
            }
            if (extdll_has_unique_dependency(&extdlls[i], dependency, j)) indegree[i]++;
        }
    }

    while (output_count < extdll_count) {
        int next = -1;
        /* Choosing the first currently available entry makes the topological
           sort stable: unrelated entries retain their configured order. */
        for (int i = 0; i < extdll_count; i++) {
            if (!selected[i] && indegree[i] == 0) {
                next = i;
                break;
            }
        }
        if (next < 0) {
            ML_LOG_ERROR(L"extdll", L"external DLL dependency cycle detected; preserving configured order");
            yaer_mem_free(selected);
            yaer_mem_free(indegree);
            yaer_mem_free(order);
            return;
        }
        selected[next] = true;
        order[output_count++] = next;
        for (int i = 0; i < extdll_count; i++) {
            if (selected[i]) continue;
            for (int j = 0; j < extdlls[i].after_count; j++) {
                if (strcmp(extdlls[i].after[j], extdlls[next].name) == 0) {
                    if (extdll_has_unique_dependency(&extdlls[i], extdll_index_by_name(extdlls[next].name), j)) {
                        indegree[i]--;
                    }
                    break;
                }
            }
        }
    }

    /* Rebuild the order from the original positions. When a dependency is
       later than its dependent, move the nearest such dependency directly
       before the dependent. This keeps unrelated entries in their original
       order and changes only the entries needed to satisfy the constraints. */
    for (int i = 0; i < extdll_count; i++) order[i] = i;
    for (int move_count = 0; move_count <= extdll_count * extdll_count; move_count++) {
        bool moved = false;
        for (int i = 0; i < extdll_count && !moved; i++) {
            int nearest_position = -1;
            for (int j = 0; j < extdlls[order[i]].after_count; j++) {
                int dependency = extdll_index_by_name(extdlls[order[i]].after[j]);
                int dependency_position = -1;
                if (dependency < 0) continue;
                for (int k = 0; k < extdll_count; k++) {
                    if (order[k] == dependency) {
                        dependency_position = k;
                        break;
                    }
                }
                if (dependency_position > i &&
                    (nearest_position < 0 || dependency_position < nearest_position)) {
                    nearest_position = dependency_position;
                }
            }
            if (nearest_position >= 0) {
                int dependency = order[nearest_position];
                memmove(&order[i + 1], &order[i], (size_t)(nearest_position - i) * sizeof(*order));
                order[i] = dependency;
                moved = true;
            }
        }
        if (!moved) break;
        if (move_count == extdll_count * extdll_count) {
            ML_LOG_ERROR(L"extdll", L"external DLL dependency cycle detected; preserving configured order");
            yaer_mem_free(selected);
            yaer_mem_free(indegree);
            yaer_mem_free(order);
            return;
        }
    }

    sorted = yaer_mem_alloc(0, (size_t)extdll_count * sizeof(*sorted));
    if (sorted == NULL) {
        ML_LOG_ERROR(L"extdll", L"cannot allocate external DLL dependency order");
    } else {
        for (int i = 0; i < extdll_count; i++) sorted[i] = extdlls[order[i]];
        memcpy(extdlls, sorted, (size_t)extdll_count * sizeof(*extdlls));
        yaer_mem_free(sorted);
    }
    /* Dependencies of an early DLL must also be available before the
       runtime-ready phase. Promote only the prerequisite closure. */
    for (int i = 0; i < extdll_count; i++) extdlls[i].effective_early = extdlls[i].early;
    for (;;) {
        bool changed = false;
        for (int i = 0; i < extdll_count; i++) {
            if (!extdlls[i].effective_early) continue;
            for (int j = 0; j < extdlls[i].after_count; j++) {
                int dependency = extdll_index_by_name(extdlls[i].after[j]);
                if (dependency >= 0 && !extdlls[dependency].effective_early) {
                    extdlls[dependency].effective_early = true;
                    changed = true;
                }
            }
        }
        if (!changed) break;
    }
    yaer_mem_free(selected);
    yaer_mem_free(indegree);
    yaer_mem_free(order);
}

static HMODULE load_extdll_module(const extdll_t *extdll) {
    const wchar_t *path = extdll->base_path;
    if (StrChrW(path, L':') == NULL && path[0] != L'\\' && path[0] != L'/') {
        wchar_t full_path[MAX_PATH];
        config_full_path(full_path, path);
        return LoadLibraryW(full_path);
    }
    return LoadLibraryW(path);
}

static void load_extdll_one(int index) {
    extdll_t *extdll = &extdlls[index];
    HMODULE dll;
    if (extdll->dll_module != NULL) return;
    dll = load_extdll_module(extdll);
    extdll->dll_module = dll;
    if (dll == NULL) {
        ML_LOG_ERROR(L"extdll", L"cannot load external DLL %hs from `%ls`", extdll->name, extdll->base_path);
        return;
    }
    extdll->load_order = ++load_counter;
    ML_LOG_INFO(L"extdll", L"loaded external DLL %hs from `%ls`", extdll->name, extdll->base_path);
    extdll->extension_object = NULL;
    {
        FARPROC me_ext_init = GetProcAddress(dll, "modengine_ext_init");
        if (me_ext_init == NULL) return;
        if (!((bool(*)(void *, void **))me_ext_init)(NULL, &extdll->extension_object)) return;
        ML_LOG_INFO(L"extdll", L"initialized external DLL %hs using ModEngine API", extdll->name);
        if (extdll->extension_object == NULL) return;
        {
            void **vtable = *(void***)extdll->extension_object;
            if (vtable == NULL) return;
            /* Call ModEngineExtension::on_attach(). */
            ((void(*)(void *))vtable[1])(extdll->extension_object);
            /* Call ModEngineExtension::id() to get the extension ID. */
            ML_LOG_INFO(L"extdll", L"attached extension ID: %hs",
                        ((const char *(*)(void *))vtable[3])(extdll->extension_object));
        }
    }
}

void extdlls_load_early() {
    if (ml_game_context_get() == NULL) {
        ML_LOG_WARN(L"extdll", L"external DLLs are disabled because the game context is unavailable");
        return;
    }
    for (int i = 0; i < extdll_count; i++) {
        if (!extdlls[i].effective_early) continue;
        if (extdlls[i].delayed && extdlls[i].delay_ms != 0) Sleep(extdlls[i].delay_ms);
        load_extdll_one(i);
    }
}

void extdlls_load_all() {
    if (ml_game_context_get() == NULL) {
        ML_LOG_WARN(L"extdll", L"external DLLs are disabled because the game context is unavailable");
        return;
    }
    for (int i = 0; i < extdll_count; i++) {
        if (extdlls[i].effective_early) continue;
        if (extdlls[i].delayed && extdlls[i].delay_ms != 0) Sleep(extdlls[i].delay_ms);
        load_extdll_one(i);
    }
}

void extdlls_unload_all() {
    for (;;) {
        extdll_t *extdll = NULL;
        for (int i = 0; i < extdll_count; i++) {
            if (extdlls[i].dll_module != NULL &&
                (extdll == NULL || extdlls[i].load_order > extdll->load_order)) {
                extdll = &extdlls[i];
            }
        }
        if (extdll == NULL) break;
        if (extdll->dll_module) {
            ML_LOG_INFO(L"extdll", L"uninitializing external DLL %hs", extdll->name);
            if (extdll->extension_object) {
                void **vtable = *(void***)extdll->extension_object;
                if (vtable) {
                    /* Call ModEngineExtension::on_detach(). */
                    ((void(*)(void*))vtable[2])(extdll->extension_object);
                }
                extdll->extension_object = NULL;
            }
            FreeLibrary(extdll->dll_module);
            extdll->dll_module = NULL;
            extdll->load_order = 0;
            ML_LOG_INFO(L"extdll", L"uninitialized external DLL %hs", extdll->name);
        }
    }
    for (int i = extdll_count - 1; i >= 0; i--) {
        extdll_t *extdll = &extdlls[i];
        for (int j = 0; j < extdll->after_count; j++) yaer_mem_free(extdll->after[j]);
        yaer_mem_free(extdll->after);
        yaer_mem_free(extdll->name);
        yaer_mem_free(extdll->base_path);
        memset(extdll, 0, sizeof(*extdll));
    }
    yaer_mem_free(extdlls);
    extdlls = NULL;
    extdll_count = 0;
    extdll_capacity = 0;
    load_counter = 0;
}

#ifdef ML_EXTDLL_TEST
const char *extdlls_test_name_at(int index) {
    return index >= 0 && index < extdll_count ? extdlls[index].name : NULL;
}

bool extdlls_test_is_early_at(int index) {
    return index >= 0 && index < extdll_count ? extdlls[index].early : false;
}

bool extdlls_test_is_effective_early_at(int index) {
    return index >= 0 && index < extdll_count ? extdlls[index].effective_early : false;
}

uint32_t extdlls_test_delay_at(int index) {
    return index >= 0 && index < extdll_count ? extdlls[index].delay_ms : 0;
}

int extdlls_test_after_count(int index) {
    return index >= 0 && index < extdll_count ? extdlls[index].after_count : 0;
}

const char *extdlls_test_after_at(int index, int dependency) {
    if (index < 0 || index >= extdll_count || dependency < 0 || dependency >= extdlls[index].after_count) return NULL;
    return extdlls[index].after[dependency];
}
#endif
