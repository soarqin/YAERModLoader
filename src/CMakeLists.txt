project(modloader LANGUAGES C VERSION 0.2.0)

include(GenerateVersionInfo)

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

add_project(modloader SHARED
    dll/modloader.c
    modloader/config.c modloader/config.h
    modloader/gamehook.c modloader/gamehook.h
    modloader/mod.c modloader/mod.h
    modloader/filecache.c modloader/filecache.h
    modloader/processutil.c modloader/processutil.h

    steam/api.c steam/api.h

    proxy/winhttp.c proxy/winhttp.h proxy/winhttp.def
    proxy/dinput8.c proxy/dinput8.h proxy/dinput8.def
    proxy/dxgi.c proxy/dxgi.h proxy/dxgi.def

    ${dll_res_files}

    INLINE_TARGET OUTPUT_NAME "YAERModLoader" NO_PREFIX FOLDER app
)

target_include_directories(modloader PRIVATE .)
target_link_libraries(modloader minhook toml-c inih uthash shlwapi version)
if (MSVC)
    target_compile_options(modloader PRIVATE /utf-8)
else ()
    target_link_options(modloader PRIVATE -municode)
endif ()

# exe target
generate_version_info(exe_res_files
    NAME "YAERModLoader"
    VERSION_MAJOR ${PROJECT_VERSION_MAJOR}
    VERSION_MINOR ${PROJECT_VERSION_MINOR}
    VERSION_PATCH ${PROJECT_VERSION_PATCH}
    VERSION_REVISION ${PROJECT_VERSION_TWEAK}
    ORIGINAL_FILENAME "YAERModLoader.exe"
    COMPANY_NAME "Soar Qin"
    FILE_DESCRIPTION "Yet Another Elden Ring Mod Loader")

add_project(modlauncher WIN32
    exe/launcher.c
    exe/detours_subset.h

    steam/app.c steam/app.h
    steam/vdf.c steam/vdf.h

    exe/launcher.rc

    ${exe_res_files}

    INLINE_TARGET OUTPUT_NAME "YAERModLoader" FOLDER app
)

target_include_directories(modlauncher PRIVATE .)

if (MSVC)
    target_compile_options(modlauncher PRIVATE /utf-8)
else ()
    target_link_options(modlauncher PRIVATE -municode)
endif ()
target_link_libraries(modlauncher wingetopt lzma shlwapi)
add_dependencies(modlauncher modloader)
