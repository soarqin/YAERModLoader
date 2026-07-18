include(GenerateVersionInfo)

set(YAERMODLOADER_VERSION "0.6.1")

add_subdirectory(process)
add_subdirectory(game)
add_subdirectory(steam)
add_subdirectory(modloader)
add_subdirectory(launcher)
add_subdirectory(extdlls)

add_dependencies(modloader_launcher modloader_dll)

# Distribution target
add_custom_target(dist)
add_custom_command(TARGET dist POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/dist/dll"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:modloader_launcher>" "$<TARGET_FILE:modloader_dll>" "${CMAKE_CURRENT_SOURCE_DIR}/YAERModLoader.ini" "${CMAKE_CURRENT_SOURCE_DIR}/YAERModLoader.zhCN.ini" "${CMAKE_SOURCE_DIR}/README.md" "${CMAKE_SOURCE_DIR}/README.zhCN.md" "${CMAKE_SOURCE_DIR}/CHANGELOG.md" "${CMAKE_SOURCE_DIR}/LICENSE" "${CMAKE_BINARY_DIR}/dist/"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:extdll_er_param>" "${CMAKE_CURRENT_SOURCE_DIR}/extdlls/er_param/er_param.ini" "$<TARGET_FILE:extdll_almighty_kale>" "${CMAKE_CURRENT_SOURCE_DIR}/extdlls/almighty_kale/almighty_kale.ini" "$<TARGET_FILE:extdll_itemlot_rate>" "${CMAKE_CURRENT_SOURCE_DIR}/extdlls/itemlot_rate/itemlot_rate.ini" "${CMAKE_CURRENT_SOURCE_DIR}/extdlls/itemlot_rate/itemlot_rate.zhCN.ini" "$<TARGET_FILE:extdll_autoloot>" "$<TARGET_FILE:extdll_no_dup_loot>" "${CMAKE_BINARY_DIR}/dist/dll/"
    COMMENT "Copying files...")

#add_custom_command(TARGET dist POST_BUILD
#    COMMAND "$<TARGET_FILE:embeddll>" "${CMAKE_BINARY_DIR}/dist/$<TARGET_FILE_NAME:modloader_launcher>" "${CMAKE_BINARY_DIR}/dist/$<TARGET_FILE_NAME:modloader_dll>"
#    COMMENT "Embedding modloader DLL into exe..."
#)

# Compress to a zip and a 7z file
add_custom_command(TARGET dist POST_BUILD
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/dist"
    COMMAND ${CMAKE_COMMAND} -E tar "cf" "${CMAKE_BINARY_DIR}/dist/YAERModLoader-${YAERMODLOADER_VERSION}.zip" --format=zip -- "$<TARGET_FILE_NAME:modloader_launcher>" "$<TARGET_FILE_NAME:modloader_dll>" "YAERModLoader.ini" "YAERModLoader.zhCN.ini" "README.md" "README.zhCN.md" "CHANGELOG.md" "LICENSE" "dll/er_param.dll" "dll/er_param.ini" "dll/almighty_kale.dll" "dll/almighty_kale.ini" "dll/itemlot_rate.dll" "dll/itemlot_rate.ini" "dll/itemlot_rate.zhCN.ini" "dll/autoloot.dll" "dll/no_dup_loot.dll"
    COMMAND ${CMAKE_COMMAND} -E tar "cf" "${CMAKE_BINARY_DIR}/dist/YAERModLoader-${YAERMODLOADER_VERSION}.7z" --format=7zip -- "$<TARGET_FILE_NAME:modloader_launcher>" "$<TARGET_FILE_NAME:modloader_dll>" "YAERModLoader.ini" "YAERModLoader.zhCN.ini" "README.md" "README.zhCN.md" "CHANGELOG.md" "LICENSE" "dll/er_param.dll" "dll/er_param.ini" "dll/almighty_kale.dll" "dll/almighty_kale.ini" "dll/itemlot_rate.dll" "dll/itemlot_rate.ini" "dll/itemlot_rate.zhCN.ini" "dll/autoloot.dll" "dll/no_dup_loot.dll"
    COMMENT "Compressing to archives..."
)

add_dependencies(dist #[[embeddll]] modloader_launcher extdll_er_param extdll_almighty_kale
    extdll_itemlot_rate extdll_autoloot extdll_no_dup_loot)
