enable_language(ASM_NASM)

file(GLOB dirs LIST_DIRECTORIES true ./*)

# First pass: process self-contained subdirectories (with their own CMakeLists.txt)
# via add_subdirectory so their INTERFACE/ALIAS targets exist before the second pass.
# Convention: a self-contained subdir's CMakeLists.txt must create target extdll_<subdir>.
foreach (dir ${dirs})
    if (NOT IS_DIRECTORY ${dir})
        continue()
    endif ()
    get_filename_component(subdir ${dir} NAME)
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/CMakeLists.txt")
        add_subdirectory(${subdir})
    endif ()
endforeach ()

# Second pass: build regular extdlls (no CMakeLists.txt) via add_project. These
# DLLs initialize from DllMain and share the direct process/MinHook helpers;
# they do not implement a modloader-specific extension ABI.
foreach (dir ${dirs})
    if (NOT IS_DIRECTORY ${dir})
        continue()
    endif ()
    get_filename_component(subdir ${dir} NAME)
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/CMakeLists.txt")
        continue()
    endif ()
    file(GLOB files ${dir}/*)
    if (NOT files)
        continue()
    endif ()
    add_project(extdll_${subdir} SHARED ${files}
        ${CMAKE_SOURCE_DIR}/src/common/allocator.c
        ${CMAKE_SOURCE_DIR}/src/common/ext_shared.c
        LANGUAGES C FOLDER extdlls OUTPUT_SUBDIR dll NO_PREFIX OUTPUT_NAME ${subdir})
    target_include_directories(extdll_${subdir} PRIVATE .. ${CMAKE_SOURCE_DIR}/src/common)
    target_link_libraries(extdll_${subdir} PRIVATE inih klib shlwapi process minhook er_param::headers)
    if (MSVC)
        target_compile_options(extdll_${subdir} PRIVATE "$<$<COMPILE_LANGUAGE:C>:/FI${CMAKE_SOURCE_DIR}/src/common/allocator.h>")
    else ()
        target_compile_options(extdll_${subdir} PRIVATE "$<$<COMPILE_LANGUAGE:C>:-include;${CMAKE_SOURCE_DIR}/src/common/allocator.h>")
    endif ()
endforeach ()
