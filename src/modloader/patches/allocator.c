#include "allocator.h"
#include "log.h"

#include "modloader/hook.h"
#include "modloader/mimalloc_allocator.h"

#include "process/image.h"
#include "process/rtti.h"
#include "process/scanner.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdint.h>
#include <stdio.h>

typedef struct cs_memory_vtable_s {
    void (__cdecl *drop)(void *this_ptr);
    void (__cdecl *init)(void *this_ptr);
    void (__cdecl *deinit)(void *this_ptr);
} cs_memory_vtable_t;

static bool system_allocator_hook_installed;

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

static bool fill_allocator_table(const ml_game_descriptor_t *game, void *image, size_t image_size) {
    uint8_t *first_match = sig_scan(image, image_size,
        "48 89 05 ?? ?? ?? ?? 4C 8B C0 BA 08 00 00 00 8D 4A 08");
    void **first = first_match != NULL ? rip_target(first_match) : NULL;
    void **last = find_last_table_entry(image, image_size, game->allocator_strategy);
    DWORD old_protect;
    size_t count;
    if (first == NULL || last == NULL || first > last) return false;
    count = (size_t)(last - first) + 1;
    if (!VirtualProtect(first, count * sizeof(*first), PAGE_READWRITE, &old_protect)) return false;
    for (size_t i = 0; i < count; i++) first[i] = mimalloc_dl_allocator();
    VirtualProtect(first, count * sizeof(*first), old_protect, &old_protect);
    return true;
}

static bool install_debug_allocator(const ml_game_descriptor_t *game, void *image, size_t image_size) {
    uint8_t *match = NULL;
    void *target = NULL;
    if (game->allocator_strategy == ML_ALLOCATOR_STRATEGY_DARK_SOULS_3) {
        match = sig_scan(image, image_size,
            "48 8B 1D ?? ?? ?? ?? 48 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8B D0 45 33 C0 48 8B CB E8 ?? ?? ?? ?? E8 ?? ?? ?? ??");
        if (match != NULL) target = match + 19 + *(int32_t *)(match + 15);
    } else if (game->allocator_strategy == ML_ALLOCATOR_STRATEGY_SEKIRO) {
        match = sig_scan(image, image_size,
            "E8 ?? ?? ?? ?? 48 89 44 24 ?? 4C 8B C0 BA 08 00 00 00 B9 90 00 00 00 E8 ?? ?? ?? ??");
        if (match != NULL) target = match + 5 + *(int32_t *)(match + 1);
    }
    return target == NULL || ml_hook_install(target, get_debug_allocator, NULL) == ML_HOOK_APPLIED;
}

bool ml_allocator_install_before_main(const ml_game_descriptor_t *game, size_t heap_size_mb) {
    size_t image_size = 0;
    void *image;
    uint8_t *match;
    void *target;
    if (game == NULL || game->allocator_strategy == ML_ALLOCATOR_STRATEGY_UNSUPPORTED) return false;
    mimalloc_dl_allocator_prepare(heap_size_mb);
    image = get_module_image_base(NULL, &image_size);
    match = sig_scan(image, image_size,
        "E8 ?? ?? ?? ?? 48 8B 74 24 30 48 8B 5C 24 38 48 83 C4 20 5F E9 ?? ?? ?? ??");
    if (match == NULL) return false;
    target = match + 25 + *(int32_t *)(match + 21);
    system_allocator_hook_installed = ml_hook_install(target, get_system_allocator, NULL) == ML_HOOK_APPLIED;
    return system_allocator_hook_installed;
}

bool ml_allocator_install_after_runtime(const ml_game_descriptor_t *game, bool hook_cs_graphics) {
    size_t image_size = 0;
    void *image;
    void **vtable;
    cs_memory_vtable_t *memory;
    bool result;
    if (game == NULL || !system_allocator_hook_installed) return false;
    image = get_module_image_base(NULL, &image_size);
    vtable = rtti_find_vtable("CS::CSMemoryImp");
    if (vtable == NULL) vtable = rtti_find_vtable("NS_SPRJ::CSMemoryImp");
    if (vtable == NULL || !install_debug_allocator(game, image, image_size) ||
        !fill_allocator_table(game, image, image_size)) return false;
    memory = (cs_memory_vtable_t *)vtable;
    result = ml_hook_install(memory->init, allocator_noop, NULL) == ML_HOOK_APPLIED;
    (void)ml_hook_install(memory->deinit, allocator_noop, NULL);
    if (game->allocator_strategy == ML_ALLOCATOR_STRATEGY_ELDEN_RING && hook_cs_graphics) {
        void **graphics = rtti_find_vtable("CS::CSGraphicsImp");
        result = result && graphics != NULL && ml_hook_install(graphics[0], allocator_noop, NULL) == ML_HOOK_APPLIED;
    }
    ml_log_write(result ? ML_LOG_LEVEL_INFO : ML_LOG_LEVEL_WARN,
                 L"allocator", result
                     ? L"heap allocators APPLIED for %ls"
                     : L"heap allocators HOOK_FAILED for %ls", game->title);
    return result;
}
