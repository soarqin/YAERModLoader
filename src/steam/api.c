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

void steamapi_init() {
    steam_api_module = LoadLibraryW(L"steam_api64.dll");
    if (steam_api_module == NULL) {
        return;
    }
    steam_userstats_func = GetProcAddress(steam_api_module, "SteamAPI_SteamUserStats_v012");
    if (steam_userstats_func == NULL) {
        FreeLibrary(steam_api_module);
        steam_api_module = NULL;
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
    return ((void*(*__cdecl)())steam_userstats_func)();
}

bool isteam_userstats_store_stats(isteam_userstats *steam_userstats) {
    void **vtable = *(void***)steam_userstats;
    return ((bool(*__cdecl)(isteam_userstats*))vtable[10])(steam_userstats);
}

bool isteam_userstats_reset_all_stats(isteam_userstats *steam_userstats, bool achievements_too) {
    void **vtable = *(void***)steam_userstats;
    return ((bool(*__cdecl)(isteam_userstats*, bool))vtable[21])(steam_userstats, achievements_too);
}
