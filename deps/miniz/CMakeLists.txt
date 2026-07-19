add_library(miniz STATIC
    miniz.c
    miniz_tdef.c
    miniz_tinfl.c
    miniz_zip.c
)
target_include_directories(miniz PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
