/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "config.h"

#include "mod.h"

#include <ini.h>
#include <toml.h>

#include <shlwapi.h>
#include <string.h>

static wchar_t modulePath_[MAX_PATH];

static void enable_debug() {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    freopen("CONIN$", "r", stdin);
    fwprintf(stderr, L"NOTE: Debug mode enabled\n");
}

static void try_load_dll(const char *name, const wchar_t *path) {
    HMODULE dll;
    if (wcschr(path, L':') == NULL && path[0] != L'\\' && path[0] != L'/') {
        wchar_t full_path[MAX_PATH];
        config_full_path(full_path, path);
        dll = LoadLibraryW(full_path);
    } else {
        dll = LoadLibraryW(path);
    }
    if (dll == NULL) {
        fwprintf(stderr, L"Cannot load dll %hs from `%ls`\n", name, path);
    } else {
        fwprintf(stdout, L"Loaded dll %hs from `%ls`\n", name, path);
    }
}

static bool value_to_bool(const char *value) {
    return strcmp(value, "true") == 0 || strcmp(value, "yes") == 0 || strcmp(value, "on") == 0 || strcmp(value, "1") == 0;
}

static int ini_read_cb(void *user, const char *section,
                       const char *name, const char *value) {
    wchar_t path[MAX_PATH];
    if (section[0] == 0) {
        if (strcmp(name, "debug") == 0) {
            if (value_to_bool(value)) {
                enable_debug();
            }
        }
    } else if (strcmp(section, "dlls") == 0) {
        MultiByteToWideChar(CP_UTF8, 0, value, -1, path, MAX_PATH);
        try_load_dll(name, path);
    } else if (strcmp(section, "mods") == 0) {
        MultiByteToWideChar(CP_UTF8, 0, value, -1, path, MAX_PATH);
        mods_add(name, path);
    }
    return 1;
}

void config_load_ini(FILE *f) {
    ini_parse_file(f, ini_read_cb, NULL);
}

bool config_load_toml(FILE *f) {
    char errbuf[256];
    toml_table_t *root = toml_parse_file(f, errbuf, 256);
    toml_table_t *me;
    toml_value_t value;
    toml_array_t *arr;
    int i, len;
    if (root == NULL) return false;
    me = toml_table_table(root, "modengine");
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
        strncpy(name, value.u.s, MAX_PATH);
        free(value.u.s);
        MultiByteToWideChar(CP_UTF8, 0, name, -1, path, MAX_PATH);
        PathRemoveExtensionA(name);
        try_load_dll(name, path);
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
        toml_value_t enabled, name, path;
        wchar_t wpath[MAX_PATH];
        if (!sub) continue;
        enabled = toml_table_bool(sub, "enabled");
        if (!enabled.ok || !enabled.u.b) continue;
        name = toml_table_string(sub, "name");
        if (!name.ok) continue;
        path = toml_table_string(sub, "path");
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

void config_load(void *module) {
    wchar_t config_path[MAX_PATH] = L"";
    FILE *config_file = NULL;
    GetModuleFileNameW((HMODULE)module, modulePath_, MAX_PATH);
    PathRemoveFileSpecW(modulePath_);
    PathRemoveBackslashW(modulePath_);
    GetEnvironmentVariableW(L"MODLOADER_CONFIG", config_path, MAX_PATH);
    if (config_path[0] == L'\0') {
        config_full_path(config_path, L"YAERModLoader.ini");
        if (!PathFileExistsW(config_path) || PathIsDirectoryW(config_path)) {
            config_full_path(config_path, L"config_eldenring.toml");
        }
    } else {
        if (wcschr(config_path, L':') == NULL && config_path[0] != L'\\' && config_path[0] != L'/') {
            wchar_t temp[MAX_PATH];
            wcscpy(temp, config_path);
            config_full_path(config_path, temp);
        }
    }
    config_file = _wfopen(config_path, L"r");
    if (config_file == NULL) return;
#if !defined(STRIP_MODENGINE_CONFIG_SUPPORT)
    if (wcsicmp(PathFindExtensionW(config_path), L".toml") != 0 || !config_load_toml(config_file))
#endif
        config_load_ini(config_file);
    fclose(config_file);
}

const wchar_t *module_path() { return modulePath_; }

void config_full_path(wchar_t *path, const wchar_t *filename) {
    wcscpy(path, modulePath_);
    PathAppendW(path, filename);
}
