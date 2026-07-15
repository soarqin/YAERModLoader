/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <wchar.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

void vfs_init(void);
void vfs_uninit(void);
bool vfs_add_package(const wchar_t *path);
bool vfs_register_writable_path(const wchar_t *virtual_path, const wchar_t *physical_path);
bool vfs_has_writable_paths(void);
const wchar_t *vfs_lookup(const wchar_t *path);
const wchar_t *vfs_lookup_prefixed(const wchar_t *path, const wchar_t *game_root);
bool vfs_normalize_path(const wchar_t *path, wchar_t **normalized);
size_t vfs_entry_count(void);
const wchar_t *vfs_route_read_path(const wchar_t *path, DWORD desired_access, DWORD creation_disposition);
const wchar_t *vfs_route_read_path_a(const char *path, DWORD desired_access, DWORD creation_disposition);
const wchar_t *vfs_route_writable_path(const wchar_t *path);
void vfs_recursion_guard_enter(void);
void vfs_recursion_guard_leave(void);
