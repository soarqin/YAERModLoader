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

file(GLOB smoke_sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/smoke_*.c")

foreach(smoke_src ${smoke_sources})
    get_filename_component(smoke_target "${smoke_src}" NAME_WE)
    add_executable(${smoke_target} "${smoke_src}" ${CMAKE_SOURCE_DIR}/src/common/allocator.c)
    target_link_libraries(${smoke_target} PRIVATE game_registry process klib)
    if(smoke_target STREQUAL "smoke_mimalloc_allocator")
        target_sources(${smoke_target} PRIVATE ${CMAKE_SOURCE_DIR}/src/modloader/mimalloc_allocator.c)
        target_link_libraries(${smoke_target} PRIVATE mimalloc-static)
    endif()
    if(smoke_target STREQUAL "smoke_filecache_mt")
        target_sources(${smoke_target} PRIVATE "${CMAKE_SOURCE_DIR}/src/modloader/filecache.c")
        target_link_libraries(${smoke_target} PRIVATE klib shlwapi)
    endif()
    if(smoke_target STREQUAL "smoke_wwise_path")
        target_sources(${smoke_target} PRIVATE ${CMAKE_SOURCE_DIR}/src/modloader/patches/wwise_path.c)
    endif()
    if(smoke_target STREQUAL "smoke_hook")
        target_sources(${smoke_target} PRIVATE ${CMAKE_SOURCE_DIR}/src/modloader/hook.c)
        target_link_libraries(${smoke_target} PRIVATE minhook)
    endif()
    if(smoke_target STREQUAL "smoke_lifecycle")
        target_sources(${smoke_target} PRIVATE ${CMAKE_SOURCE_DIR}/src/modloader/lifecycle.c)
    endif()
    if(smoke_target STREQUAL "smoke_dlrf")
        target_sources(${smoke_target} PRIVATE ${CMAKE_SOURCE_DIR}/src/process/dlrf.c)
    endif()
    if(smoke_target STREQUAL "smoke_vfs")
        target_sources(${smoke_target} PRIVATE ${CMAKE_SOURCE_DIR}/src/modloader/vfs.c)
        target_link_libraries(${smoke_target} PRIVATE shlwapi klib)
    endif()
    if(smoke_target STREQUAL "smoke_dl_device")
        target_sources(${smoke_target} PRIVATE ${CMAKE_SOURCE_DIR}/src/modloader/patches/dl_device.c)
        target_link_libraries(${smoke_target} PRIVATE shlwapi miniz)
    endif()
    target_compile_definitions(${smoke_target} PRIVATE TEST_SOURCE_ROOT="${CMAKE_SOURCE_DIR}")
    target_include_directories(${smoke_target} PRIVATE ${TEST_INCLUDES})
    add_test(NAME ${smoke_target} COMMAND ${smoke_target})
endforeach()
