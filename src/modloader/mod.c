/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "mod.h"

#include "allocator.h"

#include "vfs.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>
#include <stdint.h>

#include "config.h"

static wchar_t game_folder[MAX_PATH];
static int game_folder_length;

int mod_count = 0;

void mods_init() {
    GetModuleFileNameW(NULL, game_folder, MAX_PATH);
    PathRemoveFileSpecW(game_folder);
    PathRemoveBackslashW(game_folder);
    game_folder_length = lstrlenW(game_folder);

    vfs_init();
}

void mods_uninit() {
    mod_count = 0;
    vfs_uninit();
}

void mods_add(const char *name, const wchar_t *path) {
    wchar_t base_path[MAX_PATH];
    if (path[0] == L'\\') {
        config_full_path(base_path, NULL);
        PathStripToRootW(base_path);
        PathAppendW(base_path, path + 1);
    } else if (path[1] == L':') {
        PathCanonicalizeW(base_path, path);
    } else {
        config_full_path(base_path, path);
    }
    if (!PathFileExistsW(base_path) || !PathIsDirectoryW(base_path)) {
        fwprintf(stderr, L"Cannot find mod %hs from directory `%ls`\n", name, base_path);
        return;
    }
    if (!vfs_add_package(base_path)) {
        fwprintf(stderr, L"Cannot scan mod %hs from directory `%ls`\n", name, base_path);
        return;
    }
    mod_count++;
    fwprintf(stdout, L"Added mod %hs from `%ls`\n", name, base_path);
}

int mods_count() {
    return mod_count;
}

const wchar_t *mods_file_search(const wchar_t *path) {
    return mod_count <= 0 ? NULL : vfs_lookup(path);
}

const wchar_t *mods_file_search_prefixed(const wchar_t *path) {
    return mod_count <= 0 ? NULL : vfs_lookup_prefixed(path, game_folder);
}

const wchar_t *mods_file_search_prefixed_domain(const wchar_t *path, int domain) {
    return mod_count <= 0 ? NULL : vfs_lookup_prefixed_domain(path, game_folder, (vfs_lookup_domain_t)domain);
}

bool mods_file_virtual_to_uid_prefixed(const wchar_t *path, wchar_t **uid) {
    if (uid != NULL) *uid = NULL;
    return mod_count > 0 && vfs_virtual_to_uid_prefixed(path, game_folder, uid);
}

const wchar_t *mods_file_route_read(const wchar_t *path, DWORD desired_access, DWORD creation_disposition) {
    const wchar_t *uid_path;
    if (mod_count <= 0 || path == NULL) return NULL;
    uid_path = vfs_uid_to_path(path);
    if (uid_path != NULL) return uid_path;
    if (StrCmpNIW(path, game_folder, game_folder_length) != 0 ||
        (path[game_folder_length] != L'\0' && path[game_folder_length] != L'\\' && path[game_folder_length] != L'/')) return NULL;
    return vfs_route_read_path(path + game_folder_length, desired_access, creation_disposition);
}

const wchar_t *mods_file_route_read_a(const char *path, DWORD desired_access, DWORD creation_disposition) {
    int length;
    wchar_t *wide;
    const wchar_t *result;
    if (path == NULL) return NULL;
    length = MultiByteToWideChar(CP_ACP, 0, path, -1, NULL, 0);
    if (length <= 0) return NULL;
    wide = yaer_mem_alloc(0, (size_t)length * sizeof(*wide));
    if (wide == NULL) return NULL;
    if (MultiByteToWideChar(CP_ACP, 0, path, -1, wide, length) == 0) {
        yaer_mem_free(wide);
        return NULL;
    }
    result = mods_file_route_read(wide, desired_access, creation_disposition);
    yaer_mem_free(wide);
    return result;
}
