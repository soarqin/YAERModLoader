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

add_project(${PROJECT_NAME} SHARED
    dll/modloader.c
    modloader/config.c modloader/config.h
    modloader/gamehook.c modloader/gamehook.h
    modloader/mod.c modloader/mod.h
    modloader/filecache.c modloader/filecache.h
    modloader/processutil.c modloader/processutil.h

    proxy/winhttp.c proxy/winhttp.h proxy/winhttp.def
    proxy/dinput8.c proxy/dinput8.h proxy/dinput8.def
    proxy/dxgi.c proxy/dxgi.h proxy/dxgi.def

    ${dll_res_files}

    INLINE_TARGET OUTPUT_NAME "YAERModLoader" NO_PREFIX FOLDER app
)

target_include_directories(${PROJECT_NAME} PRIVATE .)
target_link_libraries(${PROJECT_NAME} minhook toml-c inih uthash shlwapi version)
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
else ()
    target_link_options(${PROJECT_NAME} PRIVATE -municode)
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
add_dependencies(modlauncher ${PROJECT_NAME})

# tool to embed dll into exe
add_project(embeddll WIN32
    tools/embeddll.c
    INLINE_TARGET OUTPUT_NAME "embeddll" FOLDER tools
)
target_link_libraries(embeddll lzma)

add_custom_target(dist)
add_custom_command(TARGET dist POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/dist"
    COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:modlauncher>" "$<TARGET_FILE:${PROJECT_NAME}>" "${CMAKE_BINARY_DIR}/dist/$<TARGET_FILE_NAME:${PROJECT_NAME}>" "${CMAKE_CURRENT_SOURCE_DIR}/YAERModLoader.ini" "${CMAKE_BINARY_DIR}/dist/YAERModLoader.ini" "${CMAKE_SOURCE_DIR}/README.md" "${CMAKE_BINARY_DIR}/dist/README.md" "${CMAKE_SOURCE_DIR}/LICENSE" "${CMAKE_BINARY_DIR}/dist/"
    COMMENT "Copying files...")
add_custom_command(TARGET dist POST_BUILD
    COMMAND "$<TARGET_FILE:embeddll>" "${CMAKE_BINARY_DIR}/dist/$<TARGET_FILE_NAME:modlauncher>" "${CMAKE_BINARY_DIR}/dist/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
    COMMENT "Embedding ${PROJECT_NAME} into modlauncher..."
)
# Compress to a zip and a 7z file
add_custom_command(TARGET dist POST_BUILD
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/dist"
    COMMAND ${CMAKE_COMMAND} -E tar "cf" "${CMAKE_BINARY_DIR}/dist/YAERModLoader-${PROJECT_VERSION}.zip" --format=zip -- "$<TARGET_FILE_NAME:modlauncher>" "$<TARGET_FILE_NAME:${PROJECT_NAME}>" "YAERModLoader.ini" "README.md" "LICENSE"
    COMMAND ${CMAKE_COMMAND} -E tar "cf" "${CMAKE_BINARY_DIR}/dist/YAERModLoader-${PROJECT_VERSION}.7z" --format=7zip -- "$<TARGET_FILE_NAME:modlauncher>" "$<TARGET_FILE_NAME:${PROJECT_NAME}>" "YAERModLoader.ini" "README.md" "LICENSE"
    COMMENT "Compressing to archives..."
)

add_dependencies(dist embeddll ${PROJECT_NAME} modlauncher)
