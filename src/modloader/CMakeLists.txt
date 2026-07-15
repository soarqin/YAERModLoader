project(modloader LANGUAGES C VERSION "${YAERMODLOADER_VERSION}")

option(STRIP_MODENGINE_CONFIG_SUPPORT "Strip ModEngine config support" OFF)

# dll target
generate_version_info(dll_res_files
    NAME "YAERModLoader"
    VERSION_MAJOR ${PROJECT_VERSION_MAJOR}
    VERSION_MINOR ${PROJECT_VERSION_MINOR}
    VERSION_PATCH ${PROJECT_VERSION_PATCH}
    VERSION_REVISION ${PROJECT_VERSION_TWEAK}
    ORIGINAL_FILENAME "YAERModLoader.dll"
    COMPANY_NAME "Soar Qin"
    FILE_DESCRIPTION "Yet Another Elden Ring Mod Loader")

add_project(modloader_dll SHARED
    modloader.c
    ${CMAKE_SOURCE_DIR}/src/common/allocator.c
    config.c config.h
    extdll.c extdll.h extdll_api.h
    gamehook.c gamehook.h
    hook.c hook.h
    dl_allocator.c dl_allocator.h
    mimalloc_allocator.c mimalloc_allocator.h
    mod.c mod.h
    vfs.c vfs.h
    filecache.c filecache.h
    detours_subset.h
    patches/common.c patches/common.h
    patches/wwise_path.c patches/wwise_path.h
    patches/dl_device.c patches/dl_device.h
    patches/eldenring_assets.c patches/eldenring_assets.h
    patches/eldenring.c patches/eldenring.h

    proxy/winhttp.c proxy/winhttp.h proxy/winhttp.def
    proxy/dinput8.c proxy/dinput8.h proxy/dinput8.def
    proxy/dxgi.c proxy/dxgi.h proxy/dxgi.def

    ${dll_res_files}

    INLINE_TARGET OUTPUT_NAME "YAERModLoader" NO_PREFIX FOLDER app
)

target_include_directories(modloader_dll PRIVATE ..)
target_include_directories(modloader_dll PRIVATE ${CMAKE_SOURCE_DIR}/src/common)
target_compile_definitions(modloader_dll PRIVATE YAERMODLOADER_USE_MIMALLOC)
if (MSVC)
    target_compile_options(modloader_dll PRIVATE "/FI${CMAKE_SOURCE_DIR}/src/common/allocator.h")
else ()
    target_compile_options(modloader_dll PRIVATE -include ${CMAKE_SOURCE_DIR}/src/common/allocator.h)
endif ()
if (STRIP_MODENGINE_CONFIG_SUPPORT)
    target_compile_definitions(modloader_dll PRIVATE STRIP_MODENGINE_CONFIG_SUPPORT)
else ()
    target_link_libraries(modloader_dll toml-c)
endif ()
target_link_libraries(modloader_dll game_registry process steam minhook inih klib mimalloc-static miniz shlwapi version)
if (NOT MSVC)
    target_link_options(modloader_dll PRIVATE -municode)
endif ()
