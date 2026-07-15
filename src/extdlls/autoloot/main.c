#include <er_param/er_param_api.h>
#include "ext_shared.h"

#include <windows.h>

static const er_param_api_t* param_api = NULL;

void* exec_action_button_param_proxy = NULL;
uintptr_t execute_action_button_param_proxy_return = 0;

extern int exec_action_button_param_proxy_hook();

static void on_param_loaded(void* userp);

static void on_uninit(void) {
    if (param_api != NULL && GetModuleHandleW(L"er_param.dll") != NULL) {
        param_api->off_param_loaded(on_param_loaded, NULL);
    }
    ml_ext_unhook(exec_action_button_param_proxy);
    exec_action_button_param_proxy = NULL;
}

static void on_param_loaded(void* userp) {
    size_t size;
    void* base = ml_ext_get_module_image_base(NULL, &size);
    if (base == NULL) {
        return;
    }
    exec_action_button_param_proxy = (void*)ml_ext_sig_scan(base, size, "48 89 5C 24 08 57 48 81 EC 90 00 00 00 48 8B 84 24 E0 00 00 00 41 0F B6 D9 48 8B 0D ?? ?? ?? ?? 8B FA 0F 29 B4 24 80 00 00 00");
    if (exec_action_button_param_proxy == NULL) {
        return;
    }
    ml_ext_hook(exec_action_button_param_proxy, exec_action_button_param_proxy_hook, (void**)&execute_action_button_param_proxy_return);
}

static void init(void) {
    if (!ml_ext_hook_init()) return;
    HMODULE er_param_mod = GetModuleHandleW(L"er_param.dll");
    if (er_param_mod != NULL) {
        er_param_api_get_t get_api = (er_param_api_get_t)GetProcAddress(er_param_mod, "er_param_api_get");
        if (get_api != NULL) {
            param_api = get_api();
        }
    }
    if (param_api != NULL) {
        param_api->on_param_loaded(on_param_loaded, NULL);
    }
}

extern int check_exec_action_button_param_filters(uintptr_t action_button_region_system_imp, int entry_id) {
    static const int filters[] = {
        /* Lost runes */
        1000,
        /* Base game Action Button Param Filters */
        7800, 7810, 7811, 7812, 7813, 7814, 7815, 7816, 7817, 7818, 7819, 7820, 7821, 7822,
        7823, 7824, 7825, 7826, 7827, 7828, 7850, 7860,
        7861, 7862, 7863, 7864, 7865, 7866, 7867, 7868, 7869, 7870, 7871, 7872, 7873, 7874,
        7875, 7876, 7877, 7878,
        /* DLC Action Button Param Filters */
        207800, 207810, 207811, 207812, 207813, 207814, 207815, 207816, 207817, 207818, 207819,
        207820, 207821, 207822, 207823, 207824, 207825, 207826, 207827, 207828, 207829, 207830,
        207831, 207832, 207833, 207834, 207835, 207836, 207837, 207838, 207839, 207840, 207841,
        207842, 207843, 207844,
    };

    // Binary search for entry_id in filters array
    int left = 0;
    int right = sizeof(filters) / sizeof(filters[0]) - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        int value = filters[mid];
        if (value == entry_id) {
            return 1;
        }
        if (value < entry_id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

BOOL APIENTRY DllMain(HMODULE module, DWORD ul_reason_for_call, LPVOID reserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(module);
            init();
            break;
        case DLL_PROCESS_DETACH:
            on_uninit();
            ml_ext_hook_uninit();
            break;
    }
    return TRUE;
}
