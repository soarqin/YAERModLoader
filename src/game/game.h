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

typedef enum ml_game_id_e {
    ML_GAME_UNKNOWN = 0,
    ML_GAME_ELDEN_RING,
    ML_GAME_SEKIRO,
    ML_GAME_DARK_SOULS_3,
} ml_game_id_t;

typedef enum ml_stl_abi_e {
    ML_STL_ABI_MSVC2012,
    ML_STL_ABI_MSVC2015,
} ml_stl_abi_t;

typedef enum ml_support_level_e {
    ML_SUPPORT_STABLE,
    ML_SUPPORT_EXPERIMENTAL,
} ml_support_level_t;

typedef enum ml_runtime_ready_trigger_e {
    ML_RUNTIME_READY_STEAM_API_INIT,
    ML_RUNTIME_READY_UNSUPPORTED,
} ml_runtime_ready_trigger_t;

typedef struct ml_game_descriptor_s {
    ml_game_id_t id;
    const char *key;
    const wchar_t *title;
    uint32_t steam_app_id;
    const wchar_t *const *exe_relpaths;
    size_t exe_relpath_count;
    const wchar_t *save_root_name;
    const wchar_t *ini_section;
    const wchar_t *modengine_config_name;
    ml_stl_abi_t stl_abi;
    ml_support_level_t support_level;
    const wchar_t *file_step_name;
    const char *control_api_class;
    size_t ebl_bhd_holder_offset;
    ml_runtime_ready_trigger_t runtime_ready_trigger;
} ml_game_descriptor_t;

const ml_game_descriptor_t *ml_game_by_id(ml_game_id_t id);
const ml_game_descriptor_t *ml_game_by_key(const wchar_t *key);
const ml_game_descriptor_t *ml_game_by_exe_path(const wchar_t *path);
const ml_game_descriptor_t *ml_game_detect_current_process(void);

bool ml_game_context_init(void);
const ml_game_descriptor_t *ml_game_context_get(void);
