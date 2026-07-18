/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "api.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static HMODULE steam_api_module = NULL;
static FARPROC steam_userstats_func = NULL;

typedef isteam_userstats *(__cdecl *steam_userstats_factory_t)(void);
typedef bool (__cdecl *isteam_userstats_store_stats_t)(isteam_userstats *);
typedef bool (__cdecl *isteam_userstats_reset_all_stats_t)(isteam_userstats *, bool);

void steamapi_init() {
    steam_api_module = LoadLibraryW(L"steam_api64.dll");
    if (steam_api_module == NULL) {
        return;
    }
    steam_userstats_func = GetProcAddress(steam_api_module, "SteamAPI_SteamUserStats_v012");
    if (steam_userstats_func == NULL) {
        FreeLibrary(steam_api_module);
        steam_api_module = NULL;
        return;
    }
}

void steamapi_uninit() {
    steam_userstats_func = NULL;
    if (steam_api_module != NULL) {
        FreeLibrary(steam_api_module);
        steam_api_module = NULL;
    }
}

isteam_userstats *steam_userstats() {
    if (steam_userstats_func == NULL) {
        return NULL;
    }
    return ((steam_userstats_factory_t)steam_userstats_func)();
}

bool isteam_userstats_store_stats(isteam_userstats *steam_userstats) {
    void **vtable = *(void***)steam_userstats;
    return ((isteam_userstats_store_stats_t)vtable[10])(steam_userstats);
}

bool isteam_userstats_reset_all_stats(isteam_userstats *steam_userstats, bool achievements_too) {
    void **vtable = *(void***)steam_userstats;
    return ((isteam_userstats_reset_all_stats_t)vtable[21])(steam_userstats, achievements_too);
}
