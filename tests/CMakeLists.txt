# Smoke tests for hash table migrations.
# Each add_executable is gated by file existence so that Wave 2 tasks can land
# independently — when a .c file is added by T5/T6/T7, CMake's automatic
# reconfigure picks it up. Until then, the corresponding target simply does not exist.
set(TEST_INCLUDES
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/common
    ${CMAKE_SOURCE_DIR}/src/process
    ${CMAKE_SOURCE_DIR}/deps/klib
    ${CMAKE_SOURCE_DIR}/tests
)

file(GLOB SMOKE_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/smoke_*.c")

set(SMOKE_COMMON_SOURCES ${CMAKE_SOURCE_DIR}/src/common/log.c)
set(SMOKE_COMMON_LIBRARIES game_registry process klib)

set(SMOKE_smoke_mimalloc_allocator_SOURCES ${CMAKE_SOURCE_DIR}/src/modloader/mimalloc_allocator.c)
set(SMOKE_smoke_mimalloc_allocator_LIBRARIES mimalloc-static)
set(SMOKE_smoke_path_convert_SOURCES ${CMAKE_SOURCE_DIR}/src/modloader/path_convert.c)
set(SMOKE_smoke_filecache_mt_SOURCES ${CMAKE_SOURCE_DIR}/src/modloader/filecache.c)
set(SMOKE_smoke_filecache_mt_LIBRARIES shlwapi)
set(SMOKE_smoke_wwise_path_SOURCES ${CMAKE_SOURCE_DIR}/src/modloader/patches/wwise_path.c)
set(SMOKE_smoke_hook_SOURCES ${CMAKE_SOURCE_DIR}/src/modloader/hook.c)
set(SMOKE_smoke_hook_LIBRARIES minhook)
set(SMOKE_smoke_hook_batch_SOURCES ${CMAKE_SOURCE_DIR}/src/modloader/hook_batch.c)
set(SMOKE_smoke_window_flash_SOURCES
    ${CMAKE_SOURCE_DIR}/src/modloader/hook.c
    ${CMAKE_SOURCE_DIR}/src/modloader/patches/window_flash.c)
set(SMOKE_smoke_window_flash_LIBRARIES minhook user32 gdi32)
set(SMOKE_smoke_win32_hooks_SOURCES
    ${CMAKE_SOURCE_DIR}/src/modloader/hook.c
    ${CMAKE_SOURCE_DIR}/src/modloader/hook_batch.c
    ${CMAKE_SOURCE_DIR}/src/modloader/patches/win32_hooks.c)
set(SMOKE_smoke_win32_hooks_LIBRARIES minhook)
set(SMOKE_smoke_win32_hooks_DEFINITIONS ML_WIN32_HOOKS_TEST)
set(SMOKE_smoke_lifecycle_SOURCES ${CMAKE_SOURCE_DIR}/src/modloader/lifecycle.c)
set(SMOKE_smoke_logo_SOURCES ${CMAKE_SOURCE_DIR}/src/modloader/patches/logo.c)
set(SMOKE_smoke_dlrf_SOURCES ${CMAKE_SOURCE_DIR}/src/process/dlrf.c)
set(SMOKE_smoke_rip_scan_SOURCES ${CMAKE_SOURCE_DIR}/src/process/rip_scan.c)
set(SMOKE_smoke_mod_routing_SOURCES ${CMAKE_SOURCE_DIR}/src/modloader/mod.c)
set(SMOKE_smoke_mod_routing_LIBRARIES shlwapi)
set(SMOKE_smoke_launcher_game_SOURCES ${CMAKE_SOURCE_DIR}/src/launcher/launch_config.c)
set(SMOKE_smoke_launcher_game_LIBRARIES inih shlwapi)

foreach(SMOKE_TARGET smoke_vfs smoke_vfs_writable_mt smoke_vfs_generation_mt)
    set(SMOKE_${SMOKE_TARGET}_SOURCES ${CMAKE_SOURCE_DIR}/src/modloader/vfs.c)
    set(SMOKE_${SMOKE_TARGET}_LIBRARIES shlwapi)
endforeach()
set(SMOKE_smoke_vfs_DEFINITIONS ML_USE_TEST_ALLOCATOR)

foreach(SMOKE_TARGET smoke_save_mapping smoke_save_mapping_mt)
    set(SMOKE_${SMOKE_TARGET}_SOURCES
        ${CMAKE_SOURCE_DIR}/src/modloader/vfs.c
        ${CMAKE_SOURCE_DIR}/src/modloader/patches/save_mapping.c)
    set(SMOKE_${SMOKE_TARGET}_LIBRARIES shlwapi)
endforeach()

set(SMOKE_smoke_dl_device_SOURCES
    ${CMAKE_SOURCE_DIR}/src/modloader/dl_allocator.c
    ${CMAKE_SOURCE_DIR}/src/modloader/patches/dl_device.c)
set(SMOKE_smoke_dl_device_LIBRARIES shlwapi miniz xxhash::headers)
set(SMOKE_smoke_asset_hooks_SOURCES ${CMAKE_SOURCE_DIR}/src/modloader/patches/asset_hooks.c)
set(SMOKE_smoke_asset_hooks_LIBRARIES shlwapi)
set(SMOKE_smoke_asset_hooks_DEFINITIONS ML_ASSET_HOOKS_TEST)
set(SMOKE_smoke_xxh3_LIBRARIES xxhash)

foreach(SMOKE_SOURCE ${SMOKE_SOURCES})
    get_filename_component(SMOKE_TARGET "${SMOKE_SOURCE}" NAME_WE)
    add_executable(${SMOKE_TARGET} "${SMOKE_SOURCE}" ${SMOKE_COMMON_SOURCES}
        ${SMOKE_${SMOKE_TARGET}_SOURCES})
    target_link_libraries(${SMOKE_TARGET} PRIVATE ${SMOKE_COMMON_LIBRARIES}
        ${SMOKE_${SMOKE_TARGET}_LIBRARIES})
    target_compile_definitions(${SMOKE_TARGET} PRIVATE ML_USE_WIN32_ALLOCATOR
        ML_TEST_SOURCE_ROOT="${CMAKE_SOURCE_DIR}"
        ${SMOKE_${SMOKE_TARGET}_DEFINITIONS})
    target_include_directories(${SMOKE_TARGET} PRIVATE ${TEST_INCLUDES})
    if (MSVC)
        target_compile_options(${SMOKE_TARGET} PRIVATE "/FI${CMAKE_SOURCE_DIR}/src/common/allocator.h")
    else ()
        target_compile_options(${SMOKE_TARGET} PRIVATE -include ${CMAKE_SOURCE_DIR}/src/common/allocator.h)
    endif ()
    add_test(NAME ${SMOKE_TARGET} COMMAND ${SMOKE_TARGET})
endforeach()
