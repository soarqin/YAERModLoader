# almighty_kale extdll - self-contained build (1:1 C port of Glorious Merchant)
add_project(extdll_almighty_kale SHARED
    src/main.c
    src/config.c src/config.h
    src/shops.c src/shops.h
    src/shop_hooks.c src/shop_hooks.h
    src/talkscript.c src/talkscript.h src/talkscript_utils.h src/talkscript_utils.c
    src/messages.c src/messages.h src/messages_by_lang.c
    LANGUAGES C FOLDER extdlls OUTPUT_SUBDIR dll NO_PREFIX OUTPUT_NAME almighty_kale)

target_include_directories(${PROJECT_NAME} PRIVATE src .. ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/src/common)
target_link_libraries(${PROJECT_NAME} PRIVATE process klib inih shlwapi er_param::headers steam)