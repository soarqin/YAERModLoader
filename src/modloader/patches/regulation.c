#include "regulation.h"
#include "log.h"

#include "modloader/dl_allocator.h"
#include "modloader/hook.h"

#include "process/fd4_step.h"
#include "process/image.h"
#include "process/pe.h"
#include "process/scanner.h"
#include "process/singleton.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>

typedef struct dl_vector_ptr_msvc2015_s {
    dl_allocator_t *allocator;
    void **first;
    void **last;
    void **end;
} dl_vector_ptr_msvc2015_t;

typedef struct cs_regulation_manager_s {
    void *vtable;
    void *regulation_step;
    dl_vector_ptr_msvc2015_t param_res_caps;
    uint8_t *raw_regulation;
    size_t raw_regulation_len;
} cs_regulation_manager_t;

static fd4_step_fn_t old_regulation_step_idle;

_Static_assert(offsetof(cs_regulation_manager_t, raw_regulation) == 0x30, "CSRegulationManager raw_regulation offset mismatch");
_Static_assert(offsetof(cs_regulation_manager_t, raw_regulation_len) == 0x38, "CSRegulationManager raw_regulation_len offset mismatch");

static void __cdecl regulation_step_idle_hooked(void *this_ptr, fd4_time_t *time) {
    cs_regulation_manager_t *manager;
    uint8_t *raw;
    size_t len;
    dl_allocator_t *allocator;

    old_regulation_step_idle(this_ptr, time);
    manager = singleton_find("CSRegulationManager");
    if (manager == NULL || manager->raw_regulation == NULL) return;

    raw = manager->raw_regulation;
    len = manager->raw_regulation_len;
    manager->raw_regulation = NULL;
    manager->raw_regulation_len = 0;
    if (len == 0) return;

    allocator = dl_allocator_for_object(raw);
    if (allocator == NULL) {
        ML_LOG_WARN(L"regulation", L"raw buffer detached but allocator was not found");
        return;
    }
    dl_allocator_dealloc(allocator, raw);
}

static bool __cdecl skip_regulation_write(void *state) {
    (void)state;
    return true;
}

static bool install_fd4(void) {
    void *step = fd4_step_find(L"CSRegulationStep::STEP_Idle");
    return step != NULL &&
           ml_hook_install(step, regulation_step_idle_hooked, (void **)&old_regulation_step_idle) == ML_HOOK_APPLIED;
}

static bool sprj_writer_signature_matches(const uint8_t *target, const uint8_t *text_end) {
    if (target == NULL || target + 17 > text_end) return false;
    if (memcmp(target, "\x48\x8b\xd1\x48\x8b\x0d", 6) != 0) return false;
    if (memcmp(target + 10, "\x48\x85\xc9", 3) != 0) return false;
    if (target[13] == 0x75) return target + 17 <= text_end && target[15] == 0x32 && target[16] == 0xc0;
    return target + 21 <= text_end && target[13] == 0x0f && target[14] == 0x85 && target[19] == 0x32 && target[20] == 0xc0;
}

static bool install_sprj(void) {
    size_t image_size = 0;
    void *image = get_module_image_base(NULL, &image_size);
    const IMAGE_SECTION_HEADER *text = pe_section_by_name(image, ".text");
    size_t text_size = 0;
    uint8_t *base = pe_section_data(image, text, &text_size);
    uint8_t *cursor = base;
    size_t remaining = text_size;
    size_t installed = 0;

    while (cursor != NULL && remaining >= 13) {
        uint8_t *call = sig_scan(cursor, remaining, "48 8D 4C 24 ?? E8 ?? ?? ?? ?? 84 C0 74 ??");
        uint8_t *target;
        if (call == NULL) break;
        target = call + 10 + *(int32_t *)(call + 6);
        if (target >= base && target < base + text_size &&
            sprj_writer_signature_matches(target, base + text_size) &&
            ml_hook_install(target, skip_regulation_write, NULL) == ML_HOOK_APPLIED) {
            installed++;
        }
        remaining -= (size_t)(call + 1 - cursor);
        cursor = call + 1;
    }
    return installed > 0;
}

bool ml_regulation_install(const ml_game_descriptor_t *game) {
    bool result = false;
    if (game == NULL) return false;
    if (game->regulation_strategy == ML_REGULATION_STRATEGY_FD4) result = install_fd4();
    if (game->regulation_strategy == ML_REGULATION_STRATEGY_SPRJ) result = install_sprj();
    ml_log_write(result ? ML_LOG_LEVEL_INFO : ML_LOG_LEVEL_WARN,
                 L"regulation", result
                     ? L"protection APPLIED for %ls"
                     : L"protection SIGNATURE_NOT_FOUND for %ls", game->title);
    return result;
}
