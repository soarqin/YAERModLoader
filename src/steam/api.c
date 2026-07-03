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
static FARPROC steam_apps_func = NULL;

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
    /* ISteamApps accessor export. Try v008 first (current), fall back to v007.
     * If neither is present the language accessor returns NULL and callers
     * fall back to English. */
    steam_apps_func = GetProcAddress(steam_api_module, "SteamAPI_SteamApps_v008");
    if (steam_apps_func == NULL) {
        steam_apps_func = GetProcAddress(steam_api_module, "SteamAPI_SteamApps_v007");
    }
}

void steamapi_uninit() {
    steam_userstats_func = NULL;
    steam_apps_func = NULL;
    if (steam_api_module != NULL) {
        FreeLibrary(steam_api_module);
        steam_api_module = NULL;
    }
}

isteam_userstats *steam_userstats() {
    if (steam_userstats_func == NULL) {
        return NULL;
    }
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

isteam_apps *steam_apps() {
    if (steam_apps_func == NULL) {
        return NULL;
    }
    return ((void*(*__cdecl)())steam_apps_func)();
}

const char *isteam_apps_get_current_game_language(isteam_apps *apps) {
    if (apps == NULL) {
        return NULL;
    }
    void **vtable = *(void***)apps;
    /* vtable index 4 = GetCurrentGameLanguage (verified against the game's
     * steam_api64.dll ISteamApps vtable layout). */
    return ((const char *(*__cdecl)(isteam_apps *))vtable[4])(apps);
}
