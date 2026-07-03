# Smoke tests for hash table migrations.
# Each add_executable is gated by file existence so that Wave 2 tasks can land
# independently — when a .c file is added by T5/T6/T7, CMake's automatic
# reconfigure picks it up. Until then, the corresponding target simply does not exist.
set(TEST_INCLUDES
    ${CMAKE_SOURCE_DIR}/src/common
    ${CMAKE_SOURCE_DIR}/deps/klib
    ${CMAKE_SOURCE_DIR}/tests
)

foreach(smoke_name no_dup_loot filecache param)
    set(smoke_src "${CMAKE_CURRENT_SOURCE_DIR}/smoke_${smoke_name}.c")
    if(EXISTS "${smoke_src}")
        add_executable(smoke_${smoke_name} "${smoke_src}")
        target_link_libraries(smoke_${smoke_name} PRIVATE klib)
        target_include_directories(smoke_${smoke_name} PRIVATE ${TEST_INCLUDES})
        add_test(NAME smoke_${smoke_name} COMMAND smoke_${smoke_name})
    endif()
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
