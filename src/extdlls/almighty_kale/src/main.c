/*
 * almighty_kale - 1:1 C port of the Glorious Merchant mod
 * (https://github.com/ThomasJClark/elden-ring-glorious-merchant, MIT).
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "config.h"
#include "messages.h"
#include "shops.h"
#include "shop_hooks.h"
#include "talkscript.h"

#include <er_param/er_param_api.h>
#include <steam/api.h>
#include "ext_shared.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdbool.h>
#include <stdio.h>

#define AK_LOG(fmt, ...) do { \
    char _ak_buf[512]; \
    snprintf(_ak_buf, sizeof(_ak_buf), "[almighty_kale] " fmt "\n", ##__VA_ARGS__); \
    OutputDebugStringA(_ak_buf); \
} while (0)

/* Forward decls for shop count log */
extern ak_shop_t *ak_mod_shops_array(void);

const er_param_api_t *ak_param_api = NULL;

static HMODULE g_module = NULL;

static void ak_on_param_loaded(void *userp) {
    (void)userp;
    AK_LOG("ak_on_param_loaded fired");
    ak_setup_messages();
    ak_setup_shops();
    {
        ak_shop_t *shops = ak_mod_shops_array();
        AK_LOG("ak_on_param_loaded: shop counts w=%zu a=%zu s=%zu t=%zu am=%zu ow=%zu ss=%zu c=%zu m=%zu mi=%zu cg=%zu ca=%zu dw=%zu da=%zu ds=%zu dt=%zu dam=%zu daow=%zu dss=%zu dc=%zu dm=%zu dmi=%zu",
            shops[0].count, shops[1].count, shops[2].count, shops[3].count,
            shops[4].count, shops[5].count, shops[6].count, shops[7].count,
            shops[8].count, shops[9].count, shops[10].count, shops[11].count,
            shops[12].count, shops[13].count, shops[14].count, shops[15].count,
            shops[16].count, shops[17].count, shops[18].count, shops[19].count,
            shops[20].count, shops[21].count);
    }
    ak_setup_shop_hooks();
    ak_setup_talkscript();
    AK_LOG("ak_on_param_loaded: all done");
}

static void ak_on_uninit(void) {
    if (ak_param_api == NULL) return;
    if (GetModuleHandleW(L"er_param.dll") != NULL) {
        ak_param_api->off_param_loaded(ak_on_param_loaded, NULL);
    }
    ak_unhook_talkscript();
    ak_unhook_shop_hooks();
    ak_free_shop_data();
}

static void ak_init(void) {
    if (!ml_ext_hook_init()) return;
    ak_load_config(g_module);
    HMODULE er_param_mod = GetModuleHandleW(L"er_param.dll");
    if (er_param_mod != NULL) {
        er_param_api_get_t get_api = (er_param_api_get_t)GetProcAddress(er_param_mod, "er_param_api_get");
        if (get_api != NULL) {
            ak_param_api = get_api();
        }
    }
    if (ak_param_api != NULL) {
        ak_param_api->on_param_loaded(ak_on_param_loaded, NULL);
    }
}

BOOL APIENTRY DllMain(HMODULE module, DWORD ul_reason_for_call, LPVOID reserved) {
    (void)reserved;
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(module);
            g_module = module;
            ak_init();
            break;
        case DLL_PROCESS_DETACH:
            ak_on_uninit();
            ml_ext_hook_uninit();
            break;
    }
    return TRUE;
}
