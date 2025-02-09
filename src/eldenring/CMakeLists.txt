add_project(eldenring STATIC
    pointers.c pointers.h
    param.c param.h
    wstring.c wstring.h
    LANGUAGES C FOLDER libs
)

target_include_directories(${PROJECT_NAME} PRIVATE ..)
target_link_libraries(${PROJECT_NAME} process)
