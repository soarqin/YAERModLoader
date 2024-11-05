add_subdirectory(inih)
add_subdirectory(toml-c)
add_subdirectory(uthash)
add_subdirectory(minhook)
add_subdirectory(getopt)

foreach (target inih toml-c uthash minhook wingetopt)
    if (TARGET ${target})
        set_target_properties(${target} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
            ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
            FOLDER "libs")
    endif ()
endforeach ()
