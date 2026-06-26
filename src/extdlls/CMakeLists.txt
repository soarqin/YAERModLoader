enable_language(ASM_NASM)

file(GLOB dirs LIST_DIRECTORIES true ./*)

# First pass: process self-contained subdirectories (with their own CMakeLists.txt)
# via add_subdirectory so their INTERFACE/ALIAS targets exist before the second pass.
foreach (dir ${dirs})
    if (NOT IS_DIRECTORY ${dir})
        continue()
    endif ()
    get_filename_component(subdir ${dir} NAME)
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/CMakeLists.txt")
        add_subdirectory(${subdir})
    endif ()
endforeach ()

# Second pass: build regular extdlls (no CMakeLists.txt) and link er_param::headers
# to every extdll target (including those created in the first pass).
foreach (dir ${dirs})
    if (NOT IS_DIRECTORY ${dir})
        continue()
    endif ()
    file(GLOB files ${dir}/*)
    if (NOT files)
        continue()
    endif ()
    get_filename_component(subdir ${dir} NAME)
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/CMakeLists.txt")
        # already handled in first pass; just link er_param headers if target exists
        if (TARGET extdll_${subdir})
            target_link_libraries(extdll_${subdir} PRIVATE er_param::headers)
        endif ()
    else ()
        add_project(extdll_${subdir} SHARED ${files} LANGUAGES C FOLDER extdlls OUTPUT_SUBDIR dll NO_PREFIX OUTPUT_NAME ${subdir})
        target_include_directories(extdll_${subdir} PRIVATE ..)
        target_link_libraries(extdll_${subdir} PRIVATE inih klib shlwapi)
        target_link_libraries(extdll_${subdir} PRIVATE er_param::headers)
    endif ()
endforeach ()