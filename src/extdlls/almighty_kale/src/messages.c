/*
 * almighty_kale - 1:1 C port of the Glorious Merchant mod
 * (https://github.com/ThomasJClark/elden-ring-glorious-merchant, MIT).
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "messages.h"

#include <steam/api.h>
#include <er_param/er_param_api.h>
#include "ext_shared.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <string.h>

#define AK_MSG_LOG(fmt, ...) do { \
    char _ak_buf[512]; \
    snprintf(_ak_buf, sizeof(_ak_buf), "[almighty_kale] " fmt "\n", ##__VA_ARGS__); \
    OutputDebugStringA(_ak_buf); \
} while (0)

extern const er_param_api_t *ak_param_api;

static const ak_msg_entry_t *ak_mod_event_text = NULL;
static size_t ak_mod_event_text_count = 0;

static er_msg_repository_imp_t *ak_msg_repository = NULL;

typedef const wchar_t *(*ak_lookup_entry_t)(er_msg_repository_imp_t *, unsigned int, er_msgbnd_t, int);
static ak_lookup_entry_t ak_lookup_entry_original = NULL;

static const wchar_t *ak_lookup_entry_detour(er_msg_repository_imp_t *repo, unsigned int unknown, er_msgbnd_t bnd_id, int msg_id) {
    if (bnd_id == ER_MSGBND_event_text_for_talk && ak_mod_event_text != NULL) {
        for (size_t i = 0; i < ak_mod_event_text_count; i++) {
            if (ak_mod_event_text[i].id == msg_id) {
                return ak_mod_event_text[i].text;
            }
        }
    }
    return ak_lookup_entry_original(repo, unknown, bnd_id, msg_id);
}

void ak_setup_messages(void) {
    /* almighty_kale links its own static copy of the steam lib, so initialize
     * it locally for the ISteamApps accessor (idempotent-ish: just loads
     * steam_api64.dll + resolves exports). */
    steamapi_init();
    const char *language = NULL;
    isteam_apps *apps = steam_apps();
    if (apps != NULL) {
        language = isteam_apps_get_current_game_language(apps);
    }
    AK_MSG_LOG("ak_setup_messages: steam language='%s'", language ? language : "(null)");
    const ak_lang_messages_t *chosen = NULL;
    if (language != NULL) {
        for (size_t i = 0; i < ak_event_text_for_talk_by_lang_count; i++) {
            if (strcmp(ak_event_text_for_talk_by_lang[i].lang, language) == 0) {
                chosen = &ak_event_text_for_talk_by_lang[i];
                break;
            }
        }
    }
    if (chosen == NULL) {
        /* default to English */
        chosen = &ak_event_text_for_talk_by_lang[0];
    }
    ak_mod_event_text = chosen->entries;
    ak_mod_event_text_count = chosen->entries_count;

    void *lookup_entry = ak_param_api->get_msg_repository_lookup_entry();
    if (lookup_entry == NULL) {
        return;
    }
    /* Spin-wait for the game to initialize the MsgRepositoryImp instance. */
    for (;;) {
        ak_msg_repository = ak_param_api->get_msg_repository();
        if (ak_msg_repository != NULL) break;
        Sleep(100);
    }
    ml_ext_hook(lookup_entry, (void *)ak_lookup_entry_detour, (void **)&ak_lookup_entry_original);
    AK_MSG_LOG("ak_setup_messages: hook installed, original=%p", (void*)ak_lookup_entry_original);
}

const wchar_t *ak_get_message(er_msgbnd_t bnd_id, int msg_id) {
    if (ak_lookup_entry_original == NULL || ak_msg_repository == NULL) {
        return NULL;
    }
    return ak_lookup_entry_original(ak_msg_repository, 0, bnd_id, msg_id);
}
