add_project(process STATIC
    fd4_step.c fd4_step.h
    dlrf.c dlrf.h
    image.c image.h
    pe.c pe.h
    rtti.c rtti.h
    scanner.c scanner.h
    singleton.c singleton.h
    undname.c undname.h
    util.c util.h
    FOLDER libs
)

target_include_directories(process PRIVATE ${CMAKE_SOURCE_DIR}/src/common)
target_link_libraries(process PRIVATE klib)
if (MSVC)
    target_compile_options(process PRIVATE "/FI${CMAKE_SOURCE_DIR}/src/common/allocator.h")
else ()
    target_compile_options(process PRIVATE -include ${CMAKE_SOURCE_DIR}/src/common/allocator.h)
endif ()
