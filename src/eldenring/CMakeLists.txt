file(GLOB PARAM_DEF_SRC defs/*.h)
add_project(eldenring STATIC
    pointers.c pointers.h
    param.c param.h param_defs.h param_internal.h
    param_defs.h ${PARAM_DEF_SRC}
    wstring.c wstring.h
    LANGUAGES C FOLDER libs
)

target_include_directories(${PROJECT_NAME} PRIVATE ..)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/common)
target_link_libraries(${PROJECT_NAME} klib::headers process)
