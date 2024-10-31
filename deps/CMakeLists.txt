add_subdirectory(inih)
add_subdirectory(toml-c)
add_subdirectory(uthash)
add_subdirectory(detours)
add_subdirectory(getopt)

foreach (target inih toml-c uthash detours wingetopt)
    if (TARGET ${target})
        set_target_properties(${target} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
            ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
            FOLDER "libs")
    endif ()
endforeach ()
