#include "allocator.h"
#include "log.h"

#include "modloader/hook.h"
#include "modloader/hook_batch.h"
#include "modloader/mimalloc_allocator.h"

#include "process/image.h"
#include "process/rtti.h"
#include "process/scanner.h"

#include <MinHook.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include <stdint.h>
#include <stdio.h>

typedef struct cs_memory_vtable_s {
    void (__cdecl *drop)(void *this_ptr);
    void (__cdecl *init)(void *this_ptr);
    void (__cdecl *deinit)(void *this_ptr);
} cs_memory_vtable_t;

static bool system_allocator_hook_installed;

static bool remove_allocator_hook(void *target) {
    MH_STATUS status = target == NULL ? MH_OK : MH_RemoveHook(target);
    return status == MH_OK || status == MH_ERROR_NOT_CREATED;
}

static bool heap_allocator_failed(const ml_game_descriptor_t *game, const wchar_t *stage) {
    ML_LOG_WARN(L"allocator", L"heap allocators HOOK_FAILED for %ls stage=%ls",
                game == NULL ? L"<unknown>" : game->title, stage);
    return false;
}

static dl_allocator_t *__cdecl get_system_allocator(void) {
    return mimalloc_dl_allocator();
}

static dl_allocator_t *__cdecl get_debug_allocator(void *unused) {
    (void)unused;
    return mimalloc_dl_allocator();
}

static void __cdecl allocator_noop(void *this_ptr) {
    (void)this_ptr;
}

static void **rip_target(uint8_t *instruction) {
    return (void **)(instruction + 7 + *(int32_t *)(instruction + 3));
}

static void **find_last_table_entry(void *image, size_t image_size, ml_allocator_strategy_t strategy) {
    const char *pattern = strategy == ML_ALLOCATOR_STRATEGY_ELDEN_RING
        ? "48 89 3D ?? ?? ?? ?? C7 44 24 20 FF FF FF FF 45 33 C9 4C 8B C7 48 8D 15 ?? ?? ?? ??"
        : strategy == ML_ALLOCATOR_STRATEGY_SEKIRO
            ? "48 89 05 ?? ?? ?? ?? 4C 8B C0 BA 08 00 00 00 8D 4A 70"
            : "48 89 05 ?? ?? ?? ?? 4C 8B C0 BA 08 00 00 00 8D 4A 78";
    uint8_t *cursor = image;
    size_t remaining = image_size;
    void **last = NULL;
    while (remaining >= 19) {
        uint8_t *match = sig_scan(cursor, remaining, pattern);
        void **candidate;
        if (match == NULL) break;
        candidate = rip_target(match);
        if (last == NULL || candidate > last) last = candidate;
        remaining -= (size_t)(match + 1 - cursor);
        cursor = match + 1;
    }
    return last;
}

static bool allocator_table_range(const ml_game_descriptor_t *game, void *image, size_t image_size,
                                  void ***first_out, void ***last_out) {
    uint8_t *first_match = sig_scan(image, image_size,
        "48 89 05 ?? ?? ?? ?? 4C 8B C0 BA 08 00 00 00 8D 4A 08");
    void **first = first_match != NULL ? rip_target(first_match) : NULL;
    void **last = find_last_table_entry(image, image_size, game->allocator_strategy);
    if (first_out != NULL) *first_out = first;
    if (last_out != NULL) *last_out = last;
    return first != NULL && last != NULL && first <= last;
}

static cs_memory_vtable_t *find_cs_memory_vtable(void *image, size_t image_size) {
    uint8_t *match = sig_scan(image, image_size,
        "E8 ?? ?? ?? ?? 90 48 8D 05 ?? ?? ?? ?? 48 89 03 C6 83 ?? 02 00 00 00 "
        "48 8B C3 48 83 C4 ?? 5B C3");
    if (match == NULL) return NULL;
    return (cs_memory_vtable_t *)(match + 13 + *(int32_t *)(match + 9));
}

static bool fill_allocator_table(void **first, void **last) {
    DWORD old_protect;
    size_t count;
    if (first == NULL || last == NULL || first > last) return false;
    count = (size_t)(last - first) + 1;
    if (!VirtualProtect(first, count * sizeof(*first), PAGE_READWRITE, &old_protect)) return false;
    for (size_t i = 0; i < count; i++) first[i] = mimalloc_dl_allocator();
    VirtualProtect(first, count * sizeof(*first), old_protect, &old_protect);
    return true;
}

static void *find_debug_allocator_target(const ml_game_descriptor_t *game, void *image, size_t image_size) {
    uint8_t *match = NULL;
    if (game->allocator_strategy == ML_ALLOCATOR_STRATEGY_DARK_SOULS_3) {
        match = sig_scan(image, image_size,
            "48 8B 1D ?? ?? ?? ?? 48 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8B D0 45 33 C0 48 8B CB E8 ?? ?? ?? ?? E8 ?? ?? ?? ??");
        return match == NULL ? NULL : match + 19 + *(int32_t *)(match + 15);
    }
    if (game->allocator_strategy == ML_ALLOCATOR_STRATEGY_SEKIRO) {
        match = sig_scan(image, image_size,
            "E8 ?? ?? ?? ?? 48 89 44 24 ?? 4C 8B C0 BA 08 00 00 00 B9 90 00 00 00 E8 ?? ?? ?? ??");
        return match == NULL ? NULL : match + 5 + *(int32_t *)(match + 1);
    }
    return NULL;
}

bool ml_allocator_install_before_main(const ml_game_descriptor_t *game) {
    size_t image_size = 0;
    void *image;
    uint8_t *match;
    void *target;
    if (game == NULL || game->allocator_strategy == ML_ALLOCATOR_STRATEGY_UNSUPPORTED) return false;
    image = get_module_image_base(NULL, &image_size);
    match = sig_scan(image, image_size,
        "E8 ?? ?? ?? ?? 48 8B 74 24 30 48 8B 5C 24 38 48 83 C4 20 5F E9 ?? ?? ?? ??");
    if (match == NULL) {
        ML_LOG_WARN(L"allocator", L"system allocator getter SIGNATURE_NOT_FOUND for %ls", game->title);
        return false;
    }
    target = match + 25 + *(int32_t *)(match + 21);
    system_allocator_hook_installed = ml_hook_install(target, get_system_allocator, NULL) == ML_HOOK_APPLIED;
    ml_log_write(system_allocator_hook_installed ? ML_LOG_LEVEL_INFO : ML_LOG_LEVEL_WARN,
                 L"allocator", system_allocator_hook_installed
                     ? L"system allocator getter APPLIED for %ls"
                     : L"system allocator getter HOOK_FAILED for %ls", game->title);
    return system_allocator_hook_installed;
}

bool ml_allocator_install_after_runtime(const ml_game_descriptor_t *game) {
    size_t image_size = 0;
    void *image;
    void **vtable;
    void **first;
    void **last;
    void *debug_target;
    void *graphics_target = NULL;
    ml_hook_spec_t specs[4];
    const wchar_t *roles[4];
    size_t spec_count = 0;
    size_t installed = 0;
    cs_memory_vtable_t *memory;
    bool result;
    ml_hook_result_t hook_result;
    if (game == NULL) return heap_allocator_failed(game, L"game_descriptor");
    if (!system_allocator_hook_installed) {
        return heap_allocator_failed(game, L"system_allocator");
    }
    image = get_module_image_base(NULL, &image_size);
    vtable = rtti_find_vtable("CS::CSMemoryImp");
    if (vtable == NULL) vtable = rtti_find_vtable("NS_SPRJ::CSMemoryImp");
    if (vtable == NULL) {
        vtable = (void **)find_cs_memory_vtable(image, image_size);
        if (vtable != NULL) ML_LOG_INFO(L"allocator", L"CSMemoryImp vtable found by signature fallback at %p", vtable);
    }
    if (vtable == NULL) {
        return heap_allocator_failed(game, L"memory_vtable");
    }
    if (!allocator_table_range(game, image, image_size, &first, &last)) {
        return heap_allocator_failed(game, L"allocator_table");
    }
    memory = (cs_memory_vtable_t *)vtable;
    debug_target = find_debug_allocator_target(game, image, image_size);
    if (game->allocator_strategy == ML_ALLOCATOR_STRATEGY_DARK_SOULS_3 ||
        game->allocator_strategy == ML_ALLOCATOR_STRATEGY_SEKIRO) {
        if (debug_target == NULL) {
            return heap_allocator_failed(game, L"debug_allocator");
        }
        roles[spec_count] = L"debug_allocator";
        specs[spec_count++] = (ml_hook_spec_t){ debug_target, get_debug_allocator, NULL };
    }
    if (game->allocator_strategy == ML_ALLOCATOR_STRATEGY_ELDEN_RING) {
        void **graphics = rtti_find_vtable("CS::CSGraphicsImp");
        graphics_target = graphics == NULL ? NULL : graphics[0];
        if (graphics_target == NULL) return heap_allocator_failed(game, L"graphics_init");
        roles[spec_count] = L"graphics_init";
        specs[spec_count++] = (ml_hook_spec_t){ graphics_target, allocator_noop, NULL };
    }
    roles[spec_count] = L"memory_init";
    specs[spec_count++] = (ml_hook_spec_t){ memory->init, allocator_noop, NULL };
    for (; installed < spec_count; installed++) {
        hook_result = ml_hook_install(specs[installed].target, specs[installed].detour,
                                      specs[installed].original);
        if (hook_result != ML_HOOK_APPLIED) {
            ML_LOG_WARN(L"allocator", L"required heap allocator hook %hs role=%ls target=%p",
                        ml_hook_result_name(hook_result), roles[installed], specs[installed].target);
            if (!ml_hook_batch_remove(specs, installed, remove_allocator_hook)) {
                ML_LOG_WARN(L"allocator", L"hook rollback incomplete for %ls", game->title);
            }
            return heap_allocator_failed(game, roles[installed]);
        }
    }
    result = fill_allocator_table(first, last);
    if (!result) {
        ML_LOG_WARN(L"allocator", L"allocator table write failed: first=%p last=%p", first, last);
        bool removed = ml_hook_batch_remove(specs, spec_count, remove_allocator_hook);
        if (!removed) ML_LOG_WARN(L"allocator", L"failed to roll back allocator hooks for %ls", game->title);
        return heap_allocator_failed(game, L"allocator_table_write");
    }
    hook_result = ml_hook_install(memory->deinit, allocator_noop, NULL);
    if (hook_result == ML_HOOK_APPLIED) {
        ML_LOG_INFO(L"allocator", L"optional CSMemoryImp::deinit hook APPLIED target=%p", memory->deinit);
    } else {
        ML_LOG_INFO(L"allocator", L"optional CSMemoryImp::deinit hook SKIPPED target=%p result=%hs",
                    memory->deinit, ml_hook_result_name(hook_result));
    }
    ML_LOG_INFO(L"allocator", L"heap allocators APPLIED for %ls", game->title);
    return true;
}
