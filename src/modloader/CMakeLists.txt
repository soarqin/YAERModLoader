project(modloader LANGUAGES C VERSION 0.3.3)

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
    config.c config.h
    extdll.c extdll.h
    gamehook.c gamehook.h
    mod.c mod.h
    filecache.c filecache.h
    detours_subset.h
    patches/common.c patches/common.h
    patches/eldenring.c patches/eldenring.h

    proxy/winhttp.c proxy/winhttp.h proxy/winhttp.def
    proxy/dinput8.c proxy/dinput8.h proxy/dinput8.def
    proxy/dxgi.c proxy/dxgi.h proxy/dxgi.def

    ${dll_res_files}

    INLINE_TARGET OUTPUT_NAME "YAERModLoader" NO_PREFIX FOLDER app
)

target_include_directories(modloader_dll PRIVATE ..)
if (STRIP_MODENGINE_CONFIG_SUPPORT)
    target_compile_definitions(modloader_dll PRIVATE STRIP_MODENGINE_CONFIG_SUPPORT)
else ()
    target_link_libraries(modloader_dll toml-c)
endif ()
target_link_libraries(modloader_dll process steam minhook inih uthash shlwapi version)
if (MSVC)
    target_compile_options(modloader_dll PRIVATE /utf-8)
else ()
    target_link_options(modloader_dll PRIVATE -municode)
endif ()
