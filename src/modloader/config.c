/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "config.h"

#include "extdll.h"
#include "mod.h"

#include <ini.h>
#if !defined(STRIP_MODENGINE_CONFIG_SUPPORT)
#include <toml.h>
#endif

#include <shlwapi.h>

static wchar_t modulePath_[MAX_PATH];
int cpu_affinity_strategy = 0;
bool reset_achievements_on_new_game = false;
bool enable_ime = false;
bool skip_intro = false;
bool remove_chromatic_aberration = false;
bool remove_vignette = false;

static void enable_debug() {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    freopen("CONIN$", "r", stdin);
    fwprintf(stderr, L"NOTE: Debug mode enabled\n");
}

static bool value_to_bool(const char *value) {
    return lstrcmpA(value, "true") == 0 || lstrcmpA(value, "yes") == 0 || lstrcmpA(value, "on") == 0 || lstrcmpA(value, "1") == 0;
}

static int ini_read_cb(void *user, const char *section,
                       const char *name, const char *value) {
    wchar_t path[MAX_PATH];
    if (section[0] == 0) {
        if (lstrcmpA(name, "debug") == 0) {
            if (value_to_bool(value)) {
                enable_debug();
            }
        } else if (lstrcmpA(name, "cpu_affinity") == 0) {
            cpu_affinity_strategy = strtol(value, NULL, 0);
        } else if (lstrcmpA(name, "reset_achievements_on_new_game") == 0) {
            reset_achievements_on_new_game = value_to_bool(value);
        } else if (lstrcmpA(name, "enable_ime") == 0) {
            enable_ime = value_to_bool(value);
        }
    } else if (lstrcmpA(section, "elden_ring") == 0) {
        if (lstrcmpA(name, "skip_intro") == 0) {
            skip_intro = value_to_bool(value);
        } else if (lstrcmpA(name, "remove_chromatic_aberration") == 0) {
            remove_chromatic_aberration = value_to_bool(value);
        } else if (lstrcmpA(name, "remove_vignette") == 0) {
            remove_vignette = value_to_bool(value);
        }
    } else if (lstrcmpA(section, "dlls") == 0) {
        MultiByteToWideChar(CP_UTF8, 0, value, -1, path, MAX_PATH);
        extdlls_add(name, path);
    } else if (lstrcmpA(section, "mods") == 0) {
        MultiByteToWideChar(CP_UTF8, 0, value, -1, path, MAX_PATH);
        mods_add(name, path);
    }
    return 1;
}

void config_load_ini(FILE *f) {
    ini_parse_file(f, ini_read_cb, NULL);
}

#if !defined(STRIP_MODENGINE_CONFIG_SUPPORT)
bool config_load_toml(FILE *f) {
    char errbuf[256];
    toml_table_t *root = toml_parse_file(f, errbuf, 256);
    toml_value_t value;
    toml_array_t *arr;
    int i, len;
    if (root == NULL) return false;
    const toml_table_t *me = toml_table_table(root, "modengine");
    if (me == NULL) goto TOML_LOAD_MODS;
    value = toml_table_bool(me, "debug");
    if (value.ok && value.u.b) {
        enable_debug();
    }
    arr = toml_table_array(me, "external_dlls");
    if (arr == NULL) goto TOML_LOAD_MODS;
    len = toml_array_len(arr);
    for (i = 0; i < len; i++) {
        wchar_t path[MAX_PATH];
        char name[MAX_PATH];
        value = toml_array_string(arr, i);
        if (!value.ok) continue;
        lstrcpynA(name, value.u.s, MAX_PATH);
        free(value.u.s);
        MultiByteToWideChar(CP_UTF8, 0, name, -1, path, MAX_PATH);
        PathRemoveExtensionA(name);
        extdlls_add(name, path);
    }

    TOML_LOAD_MODS:
    me = toml_table_table(root, "extension");
    if (me == NULL) goto TOML_LOAD_END;
    me = toml_table_table(me, "mod_loader");
    if (me == NULL) goto TOML_LOAD_END;
    value = toml_table_bool(me, "enabled");
    if (!value.ok || !value.u.b) goto TOML_LOAD_END;
    arr = toml_table_array(me, "mods");
    if (arr == NULL) goto TOML_LOAD_END;
    len = toml_array_len(arr);
    for (i = 0; i < len; i++) {
        toml_table_t *sub = toml_array_table(arr, i);
        wchar_t wpath[MAX_PATH];
        if (!sub) continue;
        const toml_value_t enabled = toml_table_bool(sub, "enabled");
        if (!enabled.ok || !enabled.u.b) continue;
        const toml_value_t name = toml_table_string(sub, "name");
        if (!name.ok) continue;
        const toml_value_t path = toml_table_string(sub, "path");
        if (!path.ok) {
            free(name.u.s);
            continue;
        }
        MultiByteToWideChar(CP_UTF8, 0, path.u.s, -1, wpath, MAX_PATH);
        mods_add(name.u.s, wpath);
        free(name.u.s);
        free(path.u.s);
    }

    TOML_LOAD_END:
    toml_free(root);
    return true;
}
#endif

void config_load(void *module) {
    wchar_t config_path[MAX_PATH] = L"";
    FILE *config_file = NULL;
    GetModuleFileNameW(module, modulePath_, MAX_PATH);
    PathRemoveFileSpecW(modulePath_);
    PathRemoveBackslashW(modulePath_);
    GetEnvironmentVariableW(L"MODLOADER_CONFIG", config_path, MAX_PATH);
    if (config_path[0] == L'\0') {
        lstrcpyW(config_path, modulePath_);
        PathAppendW(config_path, L"YAERModLoader.ini");
        if (!PathFileExistsW(config_path) || PathIsDirectoryW(config_path)) {
            lstrcpyW(config_path, modulePath_);
            PathAppendW(config_path, L"config_eldenring.toml");
        }
    } else {
        if (StrChrW(config_path, L':') == NULL && config_path[0] != L'\\' && config_path[0] != L'/') {
            wchar_t temp[MAX_PATH];
            lstrcpyW(temp, config_path);
            lstrcpyW(config_path, modulePath_);
            PathAppendW(config_path, temp);
        } else if (PathIsDirectoryW(config_path)) {
            wchar_t temp[MAX_PATH];
            lstrcpyW(temp, config_path);
            PathAppendW(temp, L"YAERModLoader.ini");
            if (PathFileExistsW(temp) && !PathIsDirectoryW(temp)) {
                lstrcpyW(config_path, temp);
            } else {
                PathAppendW(config_path, L"config_eldenring.toml");
            }
        }
    }
    config_file = _wfopen(config_path, L"r");
    if (config_file == NULL) return;
#if !defined(STRIP_MODENGINE_CONFIG_SUPPORT)
    if (lstrcmpiW(PathFindExtensionW(config_path), L".toml") != 0 || !config_load_toml(config_file))
#endif
        config_load_ini(config_file);
    fclose(config_file);
}

const wchar_t *module_path() { return modulePath_; }

void config_full_path(wchar_t *path, const wchar_t *filename) {
    wchar_t config_path[MAX_PATH] = L"";
    GetEnvironmentVariableW(L"MODLOADER_CONFIG", config_path, MAX_PATH);
    if (config_path[0] == L'\0') {
        lstrcpyW(path, modulePath_);
    } else {
        lstrcpyW(path, config_path);
        if (PathFileExistsW(path) && !PathIsDirectoryW(path)) {
            PathRemoveFileSpecW(path);
        }
    }
    PathAppendW(path, filename);
}
