add_project(toml-c STATIC toml.c toml.h LANGUAGES C FOLDER libs)
target_include_directories(toml-c PUBLIC .)
