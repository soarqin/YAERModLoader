/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "ext_shared.h"

#include "process/image.h"
#include "process/scanner.h"

#include <MinHook.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static bool hook_initialized;

void *ml_ext_get_module_image_base(const wchar_t *module_name, size_t *size) {
    return get_module_image_base(module_name, size);
}

uint8_t *ml_ext_sig_scan(void *base, size_t size, const char *pattern) {
    return sig_scan(base, size, pattern);
}

bool ml_ext_hook_init(void) {
    if (hook_initialized) return true;
    if (MH_Initialize() != MH_OK) return false;
    hook_initialized = true;
    return true;
}

bool ml_ext_hook(void *target, void *detour, void **original) {
    if (!hook_initialized || target == NULL || detour == NULL || original == NULL) return false;
    if (MH_CreateHook(target, detour, original) != MH_OK) return false;
    if (MH_EnableHook(target) != MH_OK) {
        MH_RemoveHook(target);
        return false;
    }
    return true;
}

void ml_ext_unhook(void *target) {
    if (!hook_initialized || target == NULL) return;
    MH_DisableHook(target);
    MH_RemoveHook(target);
}

void ml_ext_hook_uninit(void) {
    if (!hook_initialized) return;
    MH_Uninitialize();
    hook_initialized = false;
}
