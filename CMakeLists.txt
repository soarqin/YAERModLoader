cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0091 NEW)
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.24)
    cmake_policy(SET CMP0135 NEW)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(CustomCompilerOptions)
fix_compile_flags()
fix_release_flags(STRIP_BINARY ON USE_LTO ON USE_STATIC_CRT ON)

include(GlobalOptions)
add_global_options()

include(ProjectMacros)

project(YAERModLoader)

add_subdirectory(deps)
add_subdirectory(src)
add_subdirectory(tools)

# Distribution target
add_custom_target(dist)
add_custom_command(TARGET dist POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/dist"
    COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:modlauncher>" "$<TARGET_FILE:modloader>" "${CMAKE_BINARY_DIR}/dist/$<TARGET_FILE_NAME:modloader>" "${CMAKE_CURRENT_SOURCE_DIR}/YAERModLoader.ini" "${CMAKE_BINARY_DIR}/dist/YAERModLoader.ini" "${CMAKE_SOURCE_DIR}/README.md" "${CMAKE_BINARY_DIR}/dist/README.md" "${CMAKE_SOURCE_DIR}/LICENSE" "${CMAKE_BINARY_DIR}/dist/"
    COMMENT "Copying files...")
add_custom_command(TARGET dist POST_BUILD
    COMMAND "$<TARGET_FILE:embeddll>" "${CMAKE_BINARY_DIR}/dist/$<TARGET_FILE_NAME:modlauncher>" "${CMAKE_BINARY_DIR}/dist/$<TARGET_FILE_NAME:modloader>"
    COMMENT "Embedding modloader into modlauncher..."
)
# Compress to a zip and a 7z file
add_custom_command(TARGET dist POST_BUILD
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/dist"
    COMMAND ${CMAKE_COMMAND} -E tar "cf" "${CMAKE_BINARY_DIR}/dist/YAERModLoader-${PROJECT_VERSION}.zip" --format=zip -- "$<TARGET_FILE_NAME:modlauncher>" "$<TARGET_FILE_NAME:modloader>" "YAERModLoader.ini" "README.md" "LICENSE"
    COMMAND ${CMAKE_COMMAND} -E tar "cf" "${CMAKE_BINARY_DIR}/dist/YAERModLoader-${PROJECT_VERSION}.7z" --format=7zip -- "$<TARGET_FILE_NAME:modlauncher>" "$<TARGET_FILE_NAME:modloader>" "YAERModLoader.ini" "README.md" "LICENSE"
    COMMENT "Compressing to archives..."
)

add_dependencies(dist embeddll modlauncher)
