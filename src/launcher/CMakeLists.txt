project(modloader_launcher LANGUAGES C VERSION "${YAFSML_VERSION}")

# exe target
generate_version_info(exe_res_files
    RC_FOLDER "../modloader"
    NAME "YAFSML"
    VERSION_MAJOR ${PROJECT_VERSION_MAJOR}
    VERSION_MINOR ${PROJECT_VERSION_MINOR}
    VERSION_PATCH ${PROJECT_VERSION_PATCH}
    VERSION_REVISION ${PROJECT_VERSION_TWEAK}
    ORIGINAL_FILENAME "YAFSML.exe"
    COMPANY_NAME "Soar Qin"
    FILE_DESCRIPTION "Yet Another FromSoftware Mod Loader")

add_project(modloader_launcher WIN32
    launcher.c
    launch_config.c
    config_ui.c
    ${CMAKE_SOURCE_DIR}/src/common/log.c

    launcher.rc

    ${exe_res_files}

    INLINE_TARGET OUTPUT_NAME "YAFSML" FOLDER app
)

target_include_directories(modloader_launcher PRIVATE ..)
target_include_directories(modloader_launcher PRIVATE ${CMAKE_SOURCE_DIR}/src/common)
if (NOT MSVC)
    target_link_options(modloader_launcher PRIVATE -municode)
else ()
    target_link_options(modloader_launcher PRIVATE
        "/MANIFESTDEPENDENCY:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'")
endif ()
target_link_libraries(modloader_launcher game_registry steam wingetopt inih #[[lzma]] shlwapi psapi comctl32 comdlg32)
