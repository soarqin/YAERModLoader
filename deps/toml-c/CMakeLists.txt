project(toml-c C)

add_library(toml-c STATIC toml.c toml.h)
target_include_directories(toml-c PUBLIC .)
