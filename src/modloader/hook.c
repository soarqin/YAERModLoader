/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "hook.h"

#include <MinHook.h>

ml_hook_result_t ml_hook_install(void *target, void *detour, void **original) {
    if (target == NULL) return ML_HOOK_SIGNATURE_NOT_FOUND;
    if (MH_CreateHook(target, detour, original) != MH_OK) return ML_HOOK_FAILED;
    if (MH_EnableHook(target) != MH_OK) {
        MH_RemoveHook(target);
        return ML_HOOK_FAILED;
    }
    return ML_HOOK_APPLIED;
}

const char *ml_hook_result_name(ml_hook_result_t result) {
    switch (result) {
        case ML_HOOK_APPLIED: return "APPLIED";
        case ML_HOOK_SIGNATURE_NOT_FOUND: return "SIGNATURE_NOT_FOUND";
        case ML_HOOK_FAILED: return "HOOK_FAILED";
        default: return "UNKNOWN";
    }
}
