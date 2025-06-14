macro(add_project)
    cmake_policy(SET CMP0174 NEW)
    cmake_parse_arguments(PROJ "INLINE_TARGET;EXECUTABLE;WIN32;SHARED;STATIC;INTERFACE;NO_PREFIX" "FOLDER;VERSION;LANGUAGES;OUTPUT_SUBDIR;OUTPUT_NAME;PREFIX" "" ${ARGN})

    list(GET PROJ_UNPARSED_ARGUMENTS 0 PROJ_NAME)
    list(REMOVE_AT PROJ_UNPARSED_ARGUMENTS 0)

    if (NOT PROJ_INLINE_TARGET)
        set(PROJECT_OPTIONS)
        if (PROJ_VERSION)
            list(APPEND PROJECT_OPTIONS VERSION ${PROJ_VERSION})
        endif ()
        if (PROJ_LANGUAGES)
            list(APPEND PROJECT_OPTIONS LANGUAGES ${PROJ_LANGUAGES})
        endif ()
        project(${PROJ_NAME} ${PROJECT_OPTIONS})
    endif ()

    if (PROJ_EXECUTABLE)
        add_executable(${PROJ_NAME} ${PROJ_UNPARSED_ARGUMENTS})
    elseif (PROJ_WIN32)
        add_executable(${PROJ_NAME} WIN32 ${PROJ_UNPARSED_ARGUMENTS})
    elseif (PROJ_SHARED)
        add_library(${PROJ_NAME} SHARED ${PROJ_UNPARSED_ARGUMENTS})
    elseif (PROJ_STATIC)
        add_library(${PROJ_NAME} STATIC ${PROJ_UNPARSED_ARGUMENTS})
    elseif (PROJ_INTERFACE)
        add_library(${PROJ_NAME} INTERFACE ${PROJ_UNPARSED_ARGUMENTS})
    else ()
        add_library(${PROJ_NAME} ${PROJ_UNPARSED_ARGUMENTS})
    endif ()
    if (PROJ_FOLDER)
        set_target_properties(${PROJ_NAME} PROPERTIES FOLDER ${PROJ_FOLDER})
    endif ()
    if (PROJ_NO_PREFIX)
        set_target_properties(${PROJ_NAME} PROPERTIES PREFIX "")
    elseif (PROJ_PREFIX)
        set_target_properties(${PROJ_NAME} PROPERTIES PREFIX ${PROJ_PREFIX})
    endif ()
    set_target_properties(${PROJ_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<0:>/${PROJ_OUTPUT_SUBDIR}
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<0:>/${PROJ_OUTPUT_SUBDIR}
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<0:>/${PROJ_OUTPUT_SUBDIR}
    )
    if (PROJ_OUTPUT_NAME)
        set_target_properties(${PROJ_NAME} PROPERTIES OUTPUT_NAME ${PROJ_OUTPUT_NAME})
    endif ()
endmacro()
