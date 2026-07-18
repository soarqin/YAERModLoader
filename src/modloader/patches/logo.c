/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "logo.h"
#include "log.h"

#include "process/fd4_step.h"
#include "process/image.h"
#include "process/pe.h"
#include "process/scanner.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

bool ml_logo_fd4_redirect(void **step_slot, void *next_step) {
    if (step_slot == NULL || next_step == NULL) return false;
    step_slot[0] = next_step;
    return true;
}

bool ml_logo_sprj_redirect(void **step_slot) {
    DWORD old_protect;
    if (step_slot == NULL || step_slot[2] == NULL) return false;
    if (!VirtualProtect(step_slot, sizeof(*step_slot), PAGE_READWRITE, &old_protect)) return false;
    step_slot[0] = step_slot[2];
    VirtualProtect(step_slot, sizeof(*step_slot), old_protect, &old_protect);
    return true;
}

static bool install_sprj_logo(void) {
    size_t image_size = 0;
    void *image = get_module_image_base(NULL, &image_size);
    const IMAGE_SECTION_HEADER *text = pe_section_by_name(image, ".text");
    const IMAGE_SECTION_HEADER *data = pe_section_by_name(image, ".data");
    size_t text_size = 0;
    size_t data_size = 0;
    uint8_t *text_base = pe_section_data(image, text, &text_size);
    void **slots = pe_section_data(image, data, &data_size);
    void *logo_step;

    if (text_base == NULL || slots == NULL) return false;
    logo_step = sig_scan(text_base, text_size,
        "40 55 56 57 48 8D 6C 24 ?? 48 81 EC ?? ?? ?? ?? 48 C7 45 ?? FE FF FF FF 48 89 9C 24 ?? ?? ?? ?? 48 8B F9 C6 05 ?? ?? ?? ?? 01");
    if (logo_step == NULL) return false;
    for (size_t i = 0; i + 2 < data_size / sizeof(*slots); i++) {
        if (slots[i] == logo_step) return ml_logo_sprj_redirect(&slots[i]);
    }
    return false;
}

bool ml_logo_skip_install(const ml_game_descriptor_t *game) {
    bool result;

    if (game == NULL) return false;
    switch (game->logo_strategy) {
        case ML_LOGO_STRATEGY_FD4:
            result = ml_logo_fd4_redirect(fd4_step_find_slot(L"TitleStep::STEP_BeginLogo"),
                                          fd4_step_find(L"TitleStep::STEP_BeginTitle"));
            ml_log_write(result ? ML_LOG_LEVEL_INFO : ML_LOG_LEVEL_WARN,
                         L"logo", result
                             ? L"FD4 TitleStep redirect APPLIED"
                             : L"FD4 TitleStep redirect SIGNATURE_NOT_FOUND");
            return result;
        case ML_LOGO_STRATEGY_SPRJ:
            result = install_sprj_logo();
            ml_log_write(result ? ML_LOG_LEVEL_INFO : ML_LOG_LEVEL_WARN,
                         L"logo", result
                             ? L"SPRJ TitleStep redirect APPLIED"
                             : L"SPRJ TitleStep redirect SIGNATURE_NOT_FOUND");
            return result;
        default:
            ML_LOG_WARN(L"logo", L"strategy UNSUPPORTED for %ls", game->title);
            return false;
    }
}
