add_project(inih STATIC ini.c ini.h LANGUAGES C FOLDER libs)
target_include_directories(${PROJECT_NAME} PUBLIC .)
