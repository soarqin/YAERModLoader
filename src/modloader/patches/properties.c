/*
 * Copyright (C) 2026, Soar Qin<soarchin@gmail.com>
 *
 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "properties.h"
#include "log.h"

#include "modloader/hook.h"
#include "modloader/lifecycle.h"

#include "process/dlrf.h"
#include "process/image.h"
#include "process/pe.h"
#include "process/rip_scan.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <MinHook.h>

typedef void (__cdecl *set_game_property_t)(const char *property, const char *value);

void *ml_property_init_trampoline;

static set_game_property_t set_game_property;
static void *property_init_target;
static volatile LONG property_init_seen;

typedef struct internal_property_s {
    const char *property;
    const char *value;
} internal_property_t;

static internal_property_t loose_param_property;
static bool loose_param_property_enabled;

extern void ml_property_init_hook_raw(void);

static void apply_offline_property(ml_lifecycle_phase_t phase, void *userp) {
    (void)phase;
    (void)userp;
    if (set_game_property == NULL) {
        ML_LOG_WARN(L"properties", L"SetGameProperty is unavailable");
        return;
    }
    set_game_property("Menu.IsEnableOnlineMode", "false");
    ML_LOG_INFO(L"properties", L"Menu.IsEnableOnlineMode=false applied");
    if (loose_param_property_enabled) {
        set_game_property(loose_param_property.property, loose_param_property.value);
        ML_LOG_INFO(L"properties", L"%hs=%hs applied",
                    loose_param_property.property, loose_param_property.value);
    }
}

bool ml_properties_set_loose_params(bool enabled) {
    loose_param_property = (internal_property_t){
        "Game.Debug.EnableRegulationFile", "false"
    };
    loose_param_property_enabled = enabled;
    return true;
}

void ml_properties_on_init(void) {
    if (InterlockedCompareExchange(&property_init_seen, 1, 0) != 0) return;
    ML_LOG_INFO(L"properties", L"AFTER_PROPERTIES_READY reached");
    if (!ml_lifecycle_advance(ML_LIFECYCLE_PHASE_AFTER_PROPERTIES_READY)) {
        ML_LOG_WARN(L"properties", L"could not advance lifecycle");
    }
    MH_DisableHook(property_init_target);
}

bool ml_properties_install(const ml_game_descriptor_t *game) {
    const dlrf_runtime_class_entry_t *classes;
    size_t class_count;
    dlrf_method_info_t method;
    size_t image_size;
    void *image;
    const IMAGE_SECTION_HEADER *text_section;
    const IMAGE_SECTION_HEADER *rdata_section;
    uint8_t *text;
    uint8_t *rdata;
    size_t text_size = 0;
    size_t rdata_size = 0;
    const uint8_t *property_string;
    const uint8_t *property_init;
    ml_hook_result_t hook_result;

    if (game == NULL || game->control_api_class == NULL) return false;
    classes = dlrf_runtime_classes(&class_count);
    if (classes == NULL) {
        ML_LOG_WARN(L"properties", L"DLRF runtime class registry not found");
        return false;
    }
    {
        const void *control_class = dlrf_find_runtime_class(classes, class_count, game->control_api_class);
        if (control_class == NULL ||
            !dlrf_find_method(control_class,
                              game->stl_abi == ML_STL_ABI_MSVC2012
                                  ? DLRF_VECTOR_ABI_MSVC2012
                                  : DLRF_VECTOR_ABI_MSVC2015,
                              "SetGameProperty", &method)) {
            ML_LOG_WARN(L"properties", L"%hs::SetGameProperty not found", game->control_api_class);
            return false;
        }
    }
    set_game_property = (set_game_property_t)method.address;

    image = get_module_image_base(NULL, &image_size);
    text_section = pe_section_by_name(image, ".text");
    rdata_section = pe_section_by_name(image, ".rdata");
    text = text_section == NULL ? NULL : pe_section_data(image, text_section, &text_size);
    rdata = rdata_section == NULL ? NULL : pe_section_data(image, rdata_section, &rdata_size);
    property_string = ml_find_utf16_string(rdata, rdata_size, L"Game.Debug.NearOnlyDraw");
    if (property_string == NULL) {
        property_string = ml_find_utf16_string(image, image_size, L"Game.Debug.NearOnlyDraw");
        if (property_string != NULL) {
            ML_LOG_INFO(L"properties", L"property string found outside .rdata at %p", property_string);
        }
    }
    if (property_string == NULL) {
        ML_LOG_WARN(L"properties", L"property string not found image=%p size=%zu rdata=%p size=%zu",
                    image, image_size, rdata, rdata_size);
        return false;
    }
    property_init = ml_find_rip_relative_lea(text, text_size, property_string);
    if (property_init == NULL && text != (uint8_t *)image) {
        property_init = ml_find_rip_relative_lea((const uint8_t *)image, image_size, property_string);
        if (property_init != NULL) {
            ML_LOG_INFO(L"properties", L"property reference found outside .text at %p", property_init);
        }
    }
    if (property_init == NULL) {
        ML_LOG_WARN(L"properties", L"property initializer reference not found string=%p text=%p size=%zu",
                    property_string, text, text_size);
        return false;
    }
    property_init_target = (void *)property_init;
    hook_result = ml_hook_install(property_init_target, ml_property_init_hook_raw,
                                  &ml_property_init_trampoline);
    if (hook_result != ML_HOOK_APPLIED) {
        ML_LOG_WARN(L"properties", L"initializer hook %hs", ml_hook_result_name(hook_result));
        return false;
    }
    if (!ml_lifecycle_on_phase(ML_LIFECYCLE_PHASE_AFTER_PROPERTIES_READY, apply_offline_property, NULL)) {
        ML_LOG_WARN(L"properties", L"could not schedule offline property");
        return false;
    }
    ML_LOG_INFO(L"properties", L"%hs::SetGameProperty resolved at %p; initializer hook applied at %p",
                game->control_api_class, method.address, property_init_target);
    return true;
}
