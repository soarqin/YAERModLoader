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
