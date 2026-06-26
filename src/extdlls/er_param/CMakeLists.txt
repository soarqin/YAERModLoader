# er_param provider DLL - 自包含构建, 导出 INTERFACE headers 供其他 extdll 消费
file(GLOB PARAM_DEF_SRC include/er_param/defs/*.h)

add_project(extdll_er_param SHARED
    src/provider.c
    src/param.c src/param_internal.h
    src/pointers.c src/pointers.h
    src/wstring.c
    include/er_param/er_param_api.h include/er_param/param.h include/er_param/wstring.h
    include/er_param/param_defs.h ${PARAM_DEF_SRC}
    LANGUAGES C FOLDER extdlls OUTPUT_SUBDIR dll NO_PREFIX OUTPUT_NAME er_param)

target_include_directories(${PROJECT_NAME} PRIVATE src include ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} PRIVATE process klib inih shlwapi)

add_library(er_param_headers INTERFACE)
target_include_directories(er_param_headers INTERFACE include)
add_library(er_param::headers ALIAS er_param_headers)
