project(modloader LANGUAGES C VERSION 0.3.3)

option(STRIP_MODENGINE_CONFIG_SUPPORT "Strip ModEngine config support" OFF)

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

add_project(modloader_dll SHARED
    modloader/modloader.c
    modloader/config.c modloader/config.h
    modloader/extdll.c modloader/extdll.h
    modloader/gamehook.c modloader/gamehook.h
    modloader/mod.c modloader/mod.h
    modloader/filecache.c modloader/filecache.h
    modloader/processutil.c modloader/processutil.h
    modloader/detours_subset.h

    steam/api.c steam/api.h

    proxy/winhttp.c proxy/winhttp.h proxy/winhttp.def
    proxy/dinput8.c proxy/dinput8.h proxy/dinput8.def
    proxy/dxgi.c proxy/dxgi.h proxy/dxgi.def

    ${dll_res_files}

    INLINE_TARGET OUTPUT_NAME "YAERModLoader" NO_PREFIX FOLDER app
)

target_include_directories(modloader_dll PRIVATE .)
if (STRIP_MODENGINE_CONFIG_SUPPORT)
    target_compile_definitions(modloader_dll PRIVATE STRIP_MODENGINE_CONFIG_SUPPORT)
else ()
    target_link_libraries(modloader_dll toml-c)
endif ()
target_link_libraries(modloader_dll minhook inih uthash shlwapi version)
if (MSVC)
    target_compile_options(modloader_dll PRIVATE /utf-8)
else ()
    target_link_options(modloader_dll PRIVATE -municode)
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

add_project(modloader_exe WIN32
    exe/launcher.c
    exe/detours_subset.h

    steam/app.c steam/app.h
    steam/vdf.c steam/vdf.h

    exe/launcher.rc

    ${exe_res_files}

    INLINE_TARGET OUTPUT_NAME "YAERModLoader" FOLDER app
)

target_include_directories(modloader_exe PRIVATE .)
if (MSVC)
    target_compile_options(modloader_exe PRIVATE /utf-8)
else ()
    target_link_options(modloader_exe PRIVATE -municode)
endif ()
target_link_libraries(modloader_exe wingetopt #[[lzma]] shlwapi)
add_dependencies(modloader_exe modloader_dll)

# Distribution target
add_custom_target(dist)
add_custom_command(TARGET dist POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/dist"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:modloader_exe>" "$<TARGET_FILE:modloader_dll>" "${CMAKE_CURRENT_SOURCE_DIR}/YAERModLoader.ini" "${CMAKE_SOURCE_DIR}/README.md" "${CMAKE_SOURCE_DIR}/LICENSE" "${CMAKE_BINARY_DIR}/dist/"
    COMMENT "Copying files...")

#add_custom_command(TARGET dist POST_BUILD
#    COMMAND "$<TARGET_FILE:embeddll>" "${CMAKE_BINARY_DIR}/dist/$<TARGET_FILE_NAME:modloader_exe>" "${CMAKE_BINARY_DIR}/dist/$<TARGET_FILE_NAME:modloader_dll>"
#    COMMENT "Embedding modloader DLL into exe..."
#)

# Compress to a zip and a 7z file
add_custom_command(TARGET dist POST_BUILD
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/dist"
    COMMAND ${CMAKE_COMMAND} -E tar "cf" "${CMAKE_BINARY_DIR}/dist/YAERModLoader-${PROJECT_VERSION}.zip" --format=zip -- "$<TARGET_FILE_NAME:modloader_exe>" "$<TARGET_FILE_NAME:modloader_dll>" "YAERModLoader.ini" "README.md" "LICENSE"
    COMMAND ${CMAKE_COMMAND} -E tar "cf" "${CMAKE_BINARY_DIR}/dist/YAERModLoader-${PROJECT_VERSION}.7z" --format=7zip -- "$<TARGET_FILE_NAME:modloader_exe>" "$<TARGET_FILE_NAME:modloader_dll>" "YAERModLoader.ini" "README.md" "LICENSE"
    COMMENT "Compressing to archives..."
)

# add_dependencies(dist embeddll modloader_exe)
