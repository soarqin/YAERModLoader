/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#pragma once

#include <stdbool.h>
#include <wchar.h>

typedef struct {
    int cpu_affinity_strategy;
    bool reset_achievements_on_new_game;
    bool enable_ime;
    bool skip_intro;
    bool remove_chromatic_aberration;
    bool remove_vignette;
} config_t;

extern void config_init(void *module);
extern void config_load();

extern const wchar_t *module_path();
extern void config_full_path(wchar_t *path, const wchar_t *filename);

extern config_t config;
