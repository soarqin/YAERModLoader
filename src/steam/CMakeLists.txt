add_project(steam STATIC
    api.c api.h
    app.c app.h
    vdf.c vdf.h
    FOLDER libs
)

if (MSVC)
    target_compile_options(steam PRIVATE "/FI${CMAKE_SOURCE_DIR}/src/common/allocator.h")
else ()
    target_compile_options(steam PRIVATE -include ${CMAKE_SOURCE_DIR}/src/common/allocator.h)
endif ()
