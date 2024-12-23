# tool to embed dll into exe
add_project(embeddll WIN32
    embeddll.c
    INLINE_TARGET OUTPUT_NAME "embeddll" FOLDER tools
)
target_link_libraries(embeddll lzma)
