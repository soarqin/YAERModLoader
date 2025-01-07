/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "mod.h"

#include "filecache.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>
#include <stdlib.h>
#include <stdint.h>

#include "config.h"

static wchar_t game_folder[MAX_PATH];
static int game_folder_length;

typedef struct mod_t {
    char *name;
    wchar_t *base_path;
} mod_t;

mod_t *mods = NULL;
int mod_count = 0;
int mod_capacity = 0;

void mods_init() {
    GetModuleFileNameW(NULL, game_folder, MAX_PATH);
    PathRemoveFileSpecW(game_folder);
    PathRemoveBackslashW(game_folder);
    game_folder_length = lstrlenW(game_folder);

    filecache_init();
    mods = NULL;
}

void mods_uninit() {
    for (int i = 0; i < mod_count; i++) {
        LocalFree(mods[i].name);
        LocalFree(mods[i].base_path);
    }
    LocalFree(mods);
    mods = NULL;
    mod_count = 0;
    mod_capacity = 0;
    filecache_uninit();
}

void mods_add(const char *name, const wchar_t *path) {
    if (mod_count >= mod_capacity) {
        mod_capacity = mod_capacity == 0 ? 8 : mod_capacity * 2;
        mod_t *new_mods = mods == NULL ? LocalAlloc(LMEM_ZEROINIT, mod_capacity * sizeof(mod_t)) : LocalReAlloc(mods, mod_capacity * sizeof(mod_t), LMEM_ZEROINIT);
        if (new_mods == NULL) {
            return;
        }
        mods = new_mods;
    }
    wchar_t base_path[MAX_PATH];
    if (path[0] == L'\\' || path[1] == L':') {
        PathCanonicalizeW(base_path, path);
    } else {
        config_full_path(base_path, path);
    }
    if (!PathFileExistsW(base_path) || !PathIsDirectoryW(base_path)) {
        fwprintf(stderr, L"Cannot find mod %hs from directory `%ls`\n", name, path);
        return;
    }
    mod_t *mod = &mods[mod_count++];
    mod->name = StrDupA(name);
    mod->base_path = StrDupW(base_path);
    fwprintf(stdout, L"Added mod %hs from `%ls`\n", name, base_path);
}

int mods_count() {
    return mod_count;
}

const wchar_t *mods_file_search(const wchar_t *path) {
    const wchar_t *res = filecache_find(path);
    if (res != NULL) {
        return res[0] == 0 ? NULL : res;
    }
    wchar_t cpath[MAX_PATH];
    if (path[0] == '\\' || path[0] == '/')
        lstrcpyW(cpath, path);
    else
        _snwprintf(cpath, MAX_PATH, L"\\%ls", path);
    for (int n = (int)lstrlenW(cpath) - 1; n >= 0; n--) {
        if (cpath[n] == L'/') cpath[n] = L'\\';
    }
    for (int i = 0; i < mod_count; i++) {
        wchar_t full_path[MAX_PATH];
        _snwprintf(full_path, MAX_PATH, L"%ls%ls", mods[i].base_path, cpath);
        if (PathFileExistsW(full_path) && !PathIsDirectoryW(full_path)) {
            return filecache_add(path, full_path);
        }
    }
    filecache_add(path, L"");
    return NULL;
}

const wchar_t *mods_file_search_prefixed(const wchar_t *path) {
    if (StrCmpNIW(path, game_folder, game_folder_length) != 0) return NULL;
    const wchar_t *res = filecache_find(path);
    if (res != NULL) {
        return res[0] == 0 ? NULL : res;
    }
    const wchar_t *cpath = path + game_folder_length;
    for (int i = 0; i < mod_count; i++) {
        wchar_t full_path[MAX_PATH];
        _snwprintf(full_path, MAX_PATH, L"%ls%ls", mods[i].base_path, cpath);
        if (PathFileExistsW(full_path) && !PathIsDirectoryW(full_path)) {
            return filecache_add(path, full_path);
        }
    }
    filecache_add(path, L"");
    return NULL;
}
