/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "app.h"

#include "vdf.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <stdio.h>

/* Steam's VDF files are UTF-8. Convert explicitly instead of relying on
 * printf's "%hs" (which uses the ANSI code page and corrupts non-ASCII
 * library paths / install directories, e.g. non-Latin folder names). */
static bool utf8_to_wide(const char *utf8, wchar_t *out, int out_count) {
    if (utf8 == NULL || out == NULL || out_count <= 0) return false;
    if (MultiByteToWideChar(CP_UTF8, 0, utf8, -1, out, out_count) == 0) {
        out[0] = L'\0';
        return false;
    }
    out[out_count - 1] = L'\0';
    return true;
}

bool app_find_game_path(const uint32_t app_id, wchar_t *path) {
    HKEY key;
    wchar_t steam_path[MAX_PATH];
    wchar_t library_path[MAX_PATH];
    /* Ensure callers never see an uninitialized buffer when the game is not
     * found in any library. */
    path[0] = L'\0';
    DWORD valtype = REG_SZ;
    DWORD cbdata = MAX_PATH * sizeof(wchar_t);
    if (RegOpenKeyW(HKEY_CURRENT_USER, L"Software\\Valve\\Steam", &key) != ERROR_SUCCESS) {
        return false;
    }
    if (RegQueryValueExW(key, L"SteamPath", NULL, &valtype, (LPBYTE)steam_path, &cbdata) != ERROR_SUCCESS) {
        RegCloseKey(key);
        return false;
    }
    RegCloseKey(key);
    _snwprintf(library_path, MAX_PATH, L"%ls\\steamapps\\libraryfolders.vdf", steam_path);
    library_path[MAX_PATH - 1] = L'\0';
    struct vdf_object *library_folders = vdf_parse_file(library_path);
    if (library_folders == NULL) {
        return false;
    }
    if (library_folders->key == NULL ||
        strcmp(library_folders->key, "libraryfolders") != 0 || library_folders->type != VDF_TYPE_ARRAY) {
        vdf_free_object(library_folders);
        return false;
    }
    for (int i = (int)vdf_object_get_array_length(library_folders) - 1; i >= 0; i--) {
        char app_id_str[16];
        wchar_t library_root[MAX_PATH];
        wchar_t install_dir[MAX_PATH];
        const struct vdf_object *sub = vdf_object_index_array(library_folders, i);
        if (sub == NULL || sub->type != VDF_TYPE_ARRAY) continue;
        const struct vdf_object *sub2 = vdf_object_index_array_str(sub, "path");
        if (sub2 == NULL || sub2->type != VDF_TYPE_STRING) continue;
        const struct vdf_object *sub3 = vdf_object_index_array_str(sub, "apps");
        if (sub3 == NULL || sub3->type != VDF_TYPE_ARRAY) continue;
        _snprintf(app_id_str, 16, "%u", app_id);
        app_id_str[15] = '\0';
        sub3 = vdf_object_index_array_str(sub3, app_id_str);
        if (sub3 == NULL || (sub3->type != VDF_TYPE_STRING && sub3->type != VDF_TYPE_INT)) continue;
        if (!utf8_to_wide(vdf_object_get_string(sub2), library_root, MAX_PATH)) continue;
        _snwprintf(library_path, MAX_PATH, L"%ls\\steamapps\\appmanifest_%u.acf", library_root, app_id);
        library_path[MAX_PATH - 1] = L'\0';
        struct vdf_object *acf = vdf_parse_file(library_path);
        if (acf == NULL) continue;
        if (acf->key == NULL || strcmp(acf->key, "AppState") != 0 || acf->type != VDF_TYPE_ARRAY) {
            vdf_free_object(acf);
            continue;
        }
        sub3 = vdf_object_index_array_str(acf, "installdir");
        if (sub3 == NULL || sub3->type != VDF_TYPE_STRING ||
            !utf8_to_wide(vdf_object_get_string(sub3), install_dir, MAX_PATH)) {
            vdf_free_object(acf);
            continue;
        }
        _snwprintf(path, MAX_PATH, L"%ls\\steamapps\\common\\%ls", library_root, install_dir);
        path[MAX_PATH - 1] = L'\0';
        vdf_free_object(acf);
        break;
    }
    vdf_free_object(library_folders);
    return true;
}
