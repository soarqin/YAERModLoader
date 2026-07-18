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

extern void steamapi_init();
extern void steamapi_uninit();

extern isteam_userstats *steam_userstats();
extern bool isteam_userstats_store_stats(isteam_userstats *steam_userstats);
extern bool isteam_userstats_reset_all_stats(isteam_userstats *steam_userstats, bool achievements_too);

#ifdef __cplusplus
}
#endif
