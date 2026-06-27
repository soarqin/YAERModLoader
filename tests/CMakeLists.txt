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
    add_executable(${smoke_target} "${smoke_src}")
    target_link_libraries(${smoke_target} PRIVATE process klib)
    if(smoke_target STREQUAL "smoke_mimalloc_allocator")
        target_sources(${smoke_target} PRIVATE ${CMAKE_SOURCE_DIR}/src/modloader/mimalloc_allocator.c)
        target_link_libraries(${smoke_target} PRIVATE mimalloc-static)
    endif()
    target_include_directories(${smoke_target} PRIVATE ${TEST_INCLUDES})
    add_test(NAME ${smoke_target} COMMAND ${smoke_target})
endforeach()

# Multithreaded stress test compiling the real filecache.c — guards against
# khash data races in the game hook paths (find/add from multiple threads).
set(mt_src "${CMAKE_CURRENT_SOURCE_DIR}/smoke_filecache_mt.c")
if(EXISTS "${mt_src}")
    add_executable(smoke_filecache_mt "${mt_src}" "${CMAKE_SOURCE_DIR}/src/modloader/filecache.c")
    target_link_libraries(smoke_filecache_mt PRIVATE klib shlwapi)
    target_include_directories(smoke_filecache_mt PRIVATE ${TEST_INCLUDES} ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/modloader)
    add_test(NAME smoke_filecache_mt COMMAND smoke_filecache_mt)
endif()
