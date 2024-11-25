add_project(wingetopt getopt.c getopt.h LANGUAGES C FOLDER libs)
target_include_directories(wingetopt PUBLIC .)
target_compile_definitions(wingetopt PRIVATE _CRT_SECURE_NO_WARNINGS)
