/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct isteam_userstats isteam_userstats;
typedef struct isteam_apps isteam_apps;

extern void steamapi_init();
extern void steamapi_uninit();

extern isteam_userstats *steam_userstats();
extern bool isteam_userstats_store_stats(isteam_userstats *steam_userstats);
extern bool isteam_userstats_reset_all_stats(isteam_userstats *steam_userstats, bool achievements_too);

/* ISteamApps accessor. May return NULL if steam_api64.dll or the export is
 * unavailable. vtable index 4 = GetCurrentGameLanguage. */
extern isteam_apps *steam_apps();
extern const char *isteam_apps_get_current_game_language(isteam_apps *apps);

#ifdef __cplusplus
}
#endif
