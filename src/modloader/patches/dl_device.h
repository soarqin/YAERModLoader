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
#include <stdint.h>

#include "from/abi_msvc2015.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

typedef struct ml_dl_device_s ml_dl_device_t;
typedef struct ml_dl_file_operator_s ml_dl_file_operator_t;

typedef struct ml_dl_device_vtable_s {
    void *dtor;
    void *open_file;
} ml_dl_device_vtable_t;

typedef struct ml_dl_file_operator_vtable_s {
    void *dtor;
    void *copy;
    void *set_path;
    void *set_path2;
    void *set_path3;
} ml_dl_file_operator_vtable_t;

struct ml_dl_device_s {
    ml_dl_device_vtable_t *vtable;
};

struct ml_dl_file_operator_s {
    ml_dl_file_operator_vtable_t *vtable;
};

typedef struct ml_dl_virtual_root_s {
    ml_msvc2015_string_t root;
    ml_msvc2015_string_t expanded;
} ml_dl_virtual_root_t;

typedef struct ml_dl_virtual_mount_s {
    ml_msvc2015_string_t root;
    ml_dl_device_t *device;
    size_t size;
} ml_dl_virtual_mount_t;

typedef struct ml_dl_device_manager_s {
    ml_msvc2015_vector_t devices;
    ml_msvc2015_vector_t spis;
    ml_dl_device_t *disk_device;
    ml_msvc2015_vector_t virtual_roots;
    ml_msvc2015_vector_t bnd3_mounts;
    ml_msvc2015_vector_t bnd4_mounts;
    void *bnd3_spi;
    void *bnd4_spi;
    void *mutex_vtable;
    CRITICAL_SECTION critical_section;
    bool unknown;
} ml_dl_device_manager_t;

typedef struct ml_dl_device_manager_guard_s {
    ml_dl_device_manager_t *manager;
} ml_dl_device_manager_guard_t;

typedef struct ml_dl_mount_snapshot_s {
    wchar_t **roots;
    size_t count;
} ml_dl_mount_snapshot_t;

typedef struct ml_dl_vfs_mounts_s {
    ml_dl_virtual_mount_t *items;
    size_t count;
    size_t capacity;
} ml_dl_vfs_mounts_t;

_Static_assert(offsetof(ml_dl_device_manager_t, disk_device) == 64, "DlDeviceManager disk device offset");
_Static_assert(offsetof(ml_dl_device_manager_t, virtual_roots) == 72, "DlDeviceManager virtual roots offset");

ml_dl_device_manager_t *ml_dl_device_manager_find(void *image_base);
bool ml_dl_device_manager_lock(ml_dl_device_manager_t *manager, ml_dl_device_manager_guard_t *guard);
void ml_dl_device_manager_unlock(ml_dl_device_manager_guard_t *guard);
bool ml_dl_device_expand_path(ml_dl_device_manager_t *manager, const wchar_t *path, wchar_t **expanded);
bool ml_dl_mount_snapshot(ml_dl_device_manager_t *manager, ml_dl_mount_snapshot_t *snapshot);
void ml_dl_mount_snapshot_destroy(ml_dl_mount_snapshot_t *snapshot);
bool ml_dl_mounts_init(ml_dl_vfs_mounts_t *mounts);
void ml_dl_mounts_destroy(ml_dl_vfs_mounts_t *mounts);
bool ml_dl_device_extract_new(ml_dl_device_manager_t *manager, const ml_dl_mount_snapshot_t *snapshot,
                              ml_dl_vfs_mounts_t *mounts);
bool ml_dl_device_restore_mounts(ml_dl_device_manager_t *manager, ml_dl_vfs_mounts_t *mounts);
bool ml_dl_device_push_mounts_permanent(ml_dl_device_manager_t *manager, ml_dl_vfs_mounts_t *mounts);
bool ml_dl_string_clone_replace(const ml_msvc2015_string_t *source, const wchar_t *path,
                                 ml_msvc2015_string_t *replacement);
void ml_dl_string_destroy(ml_msvc2015_string_t *string);
const wchar_t *ml_dl_string_data(const ml_msvc2015_string_t *string);
size_t ml_dl_vector_count(const ml_msvc2015_vector_t *vector, size_t item_size);
bool ml_dl_device_seen(void *target);
bool ml_dl_device_mark_seen(void *target);
bool ml_bhd5_header_valid(const void *data, size_t size);
bool ml_boot_boost_cache_key(const void *data, size_t size, uint64_t key[2]);
wchar_t *ml_boot_boost_cache_path(const wchar_t *directory, const uint64_t key[2]);
bool ml_boot_boost_cache_load(const wchar_t *path, void *output, size_t output_size);
bool ml_boot_boost_cache_store(const wchar_t *path, const void *data, size_t size);
