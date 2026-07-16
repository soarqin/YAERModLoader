#include "hook_batch.h"

bool ml_hook_batch_install(const ml_hook_spec_t *specs, size_t count,
                           ml_hook_batch_install_fn_t install_fn,
                           ml_hook_batch_remove_fn_t remove_fn,
                           bool *rollback_complete) {
    size_t installed = 0;
    if (rollback_complete != NULL) *rollback_complete = true;
    if (specs == NULL || count == 0 || install_fn == NULL || remove_fn == NULL) return false;
    for (; installed < count; installed++) {
        if (install_fn(specs[installed].target, specs[installed].detour,
                       specs[installed].original) != ML_HOOK_APPLIED) {
            while (installed != 0) {
                void *target = specs[--installed].target;
                if (target != NULL && !remove_fn(target) && rollback_complete != NULL) {
                    *rollback_complete = false;
                }
            }
            return false;
        }
    }
    return true;
}

bool ml_hook_batch_remove(const ml_hook_spec_t *specs, size_t count,
                          ml_hook_batch_remove_fn_t remove_fn) {
    bool result = true;
    if (specs == NULL || remove_fn == NULL) return false;
    while (count != 0) {
        void *target = specs[--count].target;
        if (target != NULL && !remove_fn(target)) result = false;
    }
    return result;
}

bool ml_hook_targets_remove_unique(void *const *targets, size_t count,
                                   ml_hook_batch_remove_fn_t remove_fn) {
    bool result = true;
    if (targets == NULL || remove_fn == NULL) return false;
    while (count != 0) {
        void *target = targets[--count];
        bool duplicate = false;
        if (target == NULL) continue;
        for (size_t i = 0; i < count; i++) {
            if (targets[i] == target) {
                duplicate = true;
                break;
            }
        }
        if (!duplicate && !remove_fn(target)) result = false;
    }
    return result;
}
