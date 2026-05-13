add_project(klib INTERFACE
    khash.h
    LANGUAGES C FOLDER extlibs
)
target_include_directories(klib INTERFACE .)
add_library(klib::headers ALIAS klib)
