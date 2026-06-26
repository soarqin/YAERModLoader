/*
 * Copyright (C) 2024,2025, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include <modloader/extdll_api.h>
#include <er_param/er_param_api.h>
#include <er_param/param.h>
#include <er_param/wstring.h>
#include <er_param/defs/menu_common_param.h>
#include "param_internal.h"
#include "pointers.h"

#include <ini.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct observer_s {
    void (*cb)(void *userp);
    void *userp;
} observer_t;

static modloader_ext_api_t *the_api = NULL;

static CRITICAL_SECTION observers_lock;
static bool observers_inited = false;
static observer_t *observers = NULL;
static int observers_count = 0;
static int observers_capacity = 0;
static bool param_loaded = false;
static float config_world_map_cursor_speed = 1.0f;
static HANDLE param_thread_handle = NULL;

static const er_param_table_t *provider_find_table(const wchar_t *name) {
    return er_param_find_table(name);
}

static const wchar_t *provider_wstring_str(const er_wstring_impl_t *str) {
    return er_wstring_impl_str(str);
}

static bool provider_is_loaded(void) {
    return param_loaded;
}

static bool provider_on_param_loaded(void (*cb)(void *userp), void *userp) {
    if (cb == NULL) return false;
    EnterCriticalSection(&observers_lock);
    if (param_loaded) {
        LeaveCriticalSection(&observers_lock);
        cb(userp);
        return true;
    }
    if (observers_count >= observers_capacity) {
        observers_capacity = observers_capacity == 0 ? 8 : observers_capacity * 2;
        observer_t *new_obs = observers == NULL
            ? LocalAlloc(LMEM_ZEROINIT, observers_capacity * sizeof(observer_t))
            : LocalReAlloc(observers, observers_capacity * sizeof(observer_t), LMEM_ZEROINIT);
        if (new_obs == NULL) {
            LeaveCriticalSection(&observers_lock);
            return false;
        }
        observers = new_obs;
    }
    observers[observers_count].cb = cb;
    observers[observers_count].userp = userp;
    observers_count++;
    LeaveCriticalSection(&observers_lock);
    return true;
}

static void provider_off_param_loaded(void (*cb)(void *userp), void *userp) {
    if (cb == NULL) return;
    EnterCriticalSection(&observers_lock);
    for (int i = 0; i < observers_count; i++) {
        if (observers[i].cb == cb && observers[i].userp == userp) {
            observers[i] = observers[observers_count - 1];
            observers_count--;
            break;
        }
    }
    LeaveCriticalSection(&observers_lock);
}

static const er_param_api_t g_api = {
    .api_version = 1,
    .find_table = provider_find_table,
    .wstring_str = provider_wstring_str,
    .is_loaded = provider_is_loaded,
    .on_param_loaded = provider_on_param_loaded,
    .off_param_loaded = provider_off_param_loaded,
};

__declspec(dllexport)
const er_param_api_t *er_param_api_get(void) {
    return &g_api;
}

static void apply_cursor_speed(void) {
    if (config_world_map_cursor_speed == 1.0f) return;
    const er_param_table_t *t = er_param_find_table(L"MenuCommonParam");
    if (t == NULL) return;
    er_param_table_iterate_begin(t, er_menu_common_param_t, param)
        param->worldMapCursorSpeed *= config_world_map_cursor_speed;
    er_param_table_iterate_end();
}

static int config_ini_handler(void *user, const char *section, const char *name, const char *value) {
    (void)user;
    if (section == NULL || section[0] == 0) {
        if (lstrcmpA(name, "world_map_cursor_speed") == 0) {
            config_world_map_cursor_speed = strtof(value, NULL);
            if (config_world_map_cursor_speed <= 0.0f) {
                config_world_map_cursor_speed = 1.0f;
            } else if (config_world_map_cursor_speed < 0.5f) {
                config_world_map_cursor_speed = 0.5f;
            } else if (config_world_map_cursor_speed > 10.0f) {
                config_world_map_cursor_speed = 10.0f;
            }
        }
    }
    return 1;
}

static void load_config(HMODULE module) {
    wchar_t ini_path[512];
    GetModuleFileNameW(module, ini_path, sizeof(ini_path) / sizeof(ini_path[0]));
    PathRemoveFileSpecW(ini_path);
    PathAppendW(ini_path, L"er_param.ini");
    FILE *file = _wfopen(ini_path, L"r");
    if (file == NULL) return;
    ini_parse_file(file, config_ini_handler, NULL);
    fclose(file);
}

DWORD WINAPI param_thread(LPVOID arg) {
    (void)arg;
    er_pointers_init(INIT_CS_REGULATION_MANAGER);
    if (!er_param_load_table()) {
        return 1;
    }
    observer_t *snapshot = NULL;
    int snap_count = 0;
    EnterCriticalSection(&observers_lock);
    param_loaded = true;
    snap_count = observers_count;
    if (snap_count > 0) {
        snapshot = LocalAlloc(0, snap_count * sizeof(observer_t));
        if (snapshot) {
            memcpy(snapshot, observers, snap_count * sizeof(observer_t));
        }
    }
    observers_count = 0;
    LeaveCriticalSection(&observers_lock);

    apply_cursor_speed();

    if (snapshot) {
        for (int i = 0; i < snap_count; i++) {
            snapshot[i].cb(snapshot[i].userp);
        }
        LocalFree(snapshot);
    }
    return 0;
}

static HMODULE g_module = NULL;

modloader_ext_def_t def = {
    "er_param",
    NULL,
    NULL,
};

void on_uninit(void *userp) {
    (void)userp;
    if (param_thread_handle && WaitForSingleObject(param_thread_handle, 5000) == WAIT_TIMEOUT)
        TerminateThread(param_thread_handle, 0);
    if (param_thread_handle) {
        CloseHandle(param_thread_handle);
        param_thread_handle = NULL;
    }
    er_param_unload();
    if (observers) {
        LocalFree(observers);
        observers = NULL;
        observers_count = 0;
        observers_capacity = 0;
    }
    DeleteCriticalSection(&observers_lock);
    observers_inited = false;
}

__declspec(dllexport)
modloader_ext_def_t *modloader_ext_init(modloader_ext_api_t *api) {
    the_api = api;
    if (!observers_inited) {
        InitializeCriticalSection(&observers_lock);
        observers_inited = true;
    }
    load_config(g_module);
    def.on_uninit = on_uninit;
    param_thread_handle = CreateThread(NULL, 0, param_thread, NULL, 0, NULL);
    return &def;
}

BOOL APIENTRY DllMain(HMODULE module, DWORD ul_reason_for_call, LPVOID reserved) {
    (void)reserved;
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(module);
            g_module = module;
            break;
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}