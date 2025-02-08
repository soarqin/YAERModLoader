add_project(toml-c STATIC toml.c toml.h LANGUAGES C FOLDER extlibs)
target_include_directories(toml-c PUBLIC .)
