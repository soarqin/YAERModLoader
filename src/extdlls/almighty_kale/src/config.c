/*
 * almighty_kale - 1:1 C port of the Glorious Merchant mod
 * (https://github.com/ThomasJClark/elden-ring-glorious-merchant, MIT).
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "config.h"

#include <ini.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>
#include <stdio.h>
#include <string.h>

ak_config_t ak_config = { .auto_upgrade_weapons = true };

static int ak_ini_handler(void *user, const char *section, const char *name, const char *value) {
    (void)user;
    if (section == NULL || section[0] == 0) {
        return 1;
    }
    if (lstrcmpA(section, "almighty_kale") != 0) {
        return 1;
    }
    if (lstrcmpA(name, "auto_upgrade_weapons") == 0) {
        ak_config.auto_upgrade_weapons = lstrcmpA(value, "false") != 0;
    }
    return 1;
}

void ak_load_config(HMODULE module) {
    ak_config.auto_upgrade_weapons = true;
    wchar_t ini_path[512];
    GetModuleFileNameW(module, ini_path, sizeof(ini_path) / sizeof(ini_path[0]));
    PathRemoveFileSpecW(ini_path);
    PathAppendW(ini_path, L"almighty_kale.ini");
    FILE *file = _wfopen(ini_path, L"r");
    if (file == NULL) {
        return;
    }
    ini_parse_file(file, ak_ini_handler, NULL);
    fclose(file);
}