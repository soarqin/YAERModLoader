add_subdirectory(getopt)
add_subdirectory(inih)
add_subdirectory(klib)
add_subdirectory(lzma)
add_library(miniz STATIC
    miniz/miniz.c
    miniz/miniz_tdef.c
    miniz/miniz_tinfl.c
    miniz/miniz_zip.c
)
target_include_directories(miniz PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/miniz)
add_subdirectory(minhook)
set(MI_OVERRIDE OFF CACHE BOOL "" FORCE)
set(MI_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(MI_BUILD_STATIC ON CACHE BOOL "" FORCE)
set(MI_BUILD_OBJECT OFF CACHE BOOL "" FORCE)
set(MI_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(MI_NO_USE_CXX ON CACHE BOOL "" FORCE)
set(MI_WIN_REDIRECT OFF CACHE BOOL "" FORCE)
add_subdirectory(mimalloc)
add_subdirectory(toml-c)
add_subdirectory(xxhash)
