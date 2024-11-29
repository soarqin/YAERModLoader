add_project(lz4 STATIC lz4.c lz4.h LANGUAGES C FOLDER libs)
target_include_directories(${PROJECT_NAME} PUBLIC .)
