#include <modloader/extdll_api.h>
#include <stddef.h>

static modloader_ext_api_t* the_api;

void* exec_action_button_param_proxy = NULL;
uintptr_t execute_action_button_param_proxy_return = 0;

extern int exec_action_button_param_proxy_hook();

void on_uninit(void* userp) {
    (void)userp;
    the_api->unhook(exec_action_button_param_proxy);
}

#include <stdio.h>

void on_param_initialized(void* userp) {
    size_t size;
    void* base = the_api->get_module_image_base(NULL, &size);
    if (base == NULL) {
        return;
    }
    exec_action_button_param_proxy = (void*)the_api->sig_scan(base, size, "48 89 5C 24 08 57 48 81 EC 90 00 00 00 48 8B 84 24 E0 00 00 00 41 0F B6 D9 48 8B 0D ?? ?? ?? ?? 8B FA 0F 29 B4 24 80 00 00 00");
    if (exec_action_button_param_proxy == NULL) {
        return;
    }
    the_api->hook(exec_action_button_param_proxy, exec_action_button_param_proxy_hook, (void**)&execute_action_button_param_proxy_return);
}

modloader_ext_def_t def = {
    "autoloot",
    NULL,
    on_uninit,
    on_param_initialized,
};

__declspec(dllexport)
modloader_ext_def_t* modloader_ext_init(modloader_ext_api_t* api) {
    the_api = api;
    return &def;
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
