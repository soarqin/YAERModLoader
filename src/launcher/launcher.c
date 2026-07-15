/*
 * Copyright (C) 2024, Soar Qin<soarchin@gmail.com>

 * Use of this source code is governed by an MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT.
 */

#include "steam/app.h"
#include "game/game.h"

#include "detours_subset.h"

#include <getopt.h>
/*
#include <LzmaDec.h>
#include <Alloc.h>
*/
#include <shlwapi.h>
#include <stdbool.h>

static wchar_t full_game_path[MAX_PATH] = L"";
static wchar_t full_config_path[MAX_PATH] = L"";
static wchar_t full_modengine_dll[MAX_PATH] = L"";
static bool suspend = false;
static const ml_game_descriptor_t *launch_game = NULL;

bool parse_args(const int argc, wchar_t *argv[]) {
    const struct option options[] = {
        { L"launch-target", required_argument, NULL, 't' },
        { L"game-path", required_argument, NULL, 'p' },
        { L"config", required_argument, NULL, 'c' },
        { L"modloader-dll", required_argument, NULL, 'd' },
        { L"suspend", no_argument, NULL, 's' },
        { L"modengine-dll", required_argument, NULL, 'd' },
        { NULL, 0, NULL, 0 },
    };
    int opt;
    while ((opt = getopt_long(argc, argv, L":t:p:c:d:s", options, NULL)) != -1) {
        switch (opt) {
            case 't':
                launch_game = ml_game_by_key(optarg);
                if (launch_game == NULL) {
                    fwprintf(stderr, L"unsupported launch target: %ls\n", optarg);
                    return false;
                }
                break;
            case 'p':
                lstrcpynW(full_game_path, optarg, MAX_PATH);
                break;
            case 'c':
                lstrcpynW(full_config_path, optarg, MAX_PATH);
                break;
            case 'd':
                lstrcpynW(full_modengine_dll, optarg, MAX_PATH);
                break;
            case 's':
                suspend = true;
                break;
            case '?':
                fwprintf(stderr, L"bad argument: %c\n", optopt);
                return false;
            case ':':
                fwprintf(stderr, L"missing argument for : %c\n", optopt);
                return false;
            default:
                break;
        }
    }
    return true;
}

static bool locate_game_executable(wchar_t *game_path) {
    wchar_t temp[MAX_PATH];
    if (launch_game == NULL) return false;
    if (PathFileExistsW(game_path) && !PathIsDirectoryW(game_path)) return true;
    if (StrChrW(game_path, L':') == NULL && game_path[0] != L'\\' && game_path[0] != L'/') {
        GetModuleFileNameW(NULL, temp, MAX_PATH);
        PathRemoveFileSpecW(temp);
        PathAppendW(temp, game_path);
        lstrcpyW(game_path, temp);
        if (PathFileExistsW(game_path) && !PathIsDirectoryW(game_path)) {
            return true;
        }
    }
    for (size_t i = 0; i < launch_game->exe_relpath_count; i++) {
        lstrcpyW(temp, game_path);
        PathAppendW(temp, launch_game->exe_relpaths[i]);
        if (PathFileExistsW(temp) && !PathIsDirectoryW(temp)) {
            lstrcpyW(game_path, temp);
            return true;
        }
    }
    return false;
}

static bool check_current_folder_for_game_path(wchar_t *game_path) {
    GetModuleFileNameW(NULL, game_path, MAX_PATH);
    PathRemoveFileSpecW(game_path);
    return locate_game_executable(game_path);
}

/*
bool decompress_embedded_dll_to(char *filepath) {
    wchar_t exe_filename[MAX_PATH], target_filename[MAX_PATH];
    DWORD size;
    size_t len = 0, decompressed_len = 0, props_data_size = 0;
    HANDLE f;
    char buf[4];
    Byte props[5];
    Byte *data, *decompressed_data;
    ELzmaStatus status;

    GetModuleFileNameW(NULL, exe_filename, MAX_PATH);
    f = CreateFileW(exe_filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (f == INVALID_HANDLE_VALUE) return false;
    if (SetFilePointer(f, -4, NULL, FILE_END) == INVALID_SET_FILE_POINTER) {
        goto fail1;
    }
    if (!ReadFile(f, buf, 4, &size, NULL) || size != 4) {
        goto fail1;
    }
    if (memcmp(buf, "EMBD", 4) != 0) {
        goto fail1;
    }
    if (SetFilePointer(f, -17, NULL, FILE_END) == INVALID_SET_FILE_POINTER) {
        goto fail1;
    }
    if (!ReadFile(f, props, 5, &size, NULL) || size != 5) {
        goto fail1;
    }
    if (!ReadFile(f, &len, 4, &size, NULL) || size != 4) {
        goto fail1;
    }
    if (!ReadFile(f, &decompressed_len, 4, &size, NULL) || size != 4) {
        goto fail1;
    }
    if (SetFilePointer(f, -17L - (long)len, NULL, FILE_END) == INVALID_SET_FILE_POINTER) {
        goto fail1;
    }
    data = (Byte*)malloc(len);
    if (data == NULL) {
        goto fail1;
    }
    if (!ReadFile(f, data, len, &size, NULL) || size != len) {
        goto fail2;
    }
    decompressed_data = (Byte*)malloc(decompressed_len);
    if (decompressed_data == NULL) {
        goto fail2;
    }
    if (LzmaDecode(decompressed_data, &decompressed_len, data, &len, props, 5, LZMA_FINISH_ANY, &status, &g_Alloc) != SZ_OK) {
        goto fail3;
    }

    GetTempPathW(MAX_PATH, target_filename);
    PathAppendW(target_filename, L"YAERModLoader.dll");
    CloseHandle(f);
    f = CreateFileW(target_filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (f == INVALID_HANDLE_VALUE) {
        goto fail3;
    }
    if (!WriteFile(f, decompressed_data, decompressed_len, &size, NULL) || size != decompressed_len) {
        goto fail3;
    }
    WideCharToMultiByte(CP_ACP, 0, target_filename, -1, filepath, MAX_PATH, NULL, NULL);

    free(data);
    CloseHandle(f);
    return true;

fail3:
    free(decompressed_data);
fail2:
    free(data);
fail1:
    CloseHandle(f);
    return false;
}
*/

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nShowCmd) {
    STARTUPINFOW si = {0};
    PROCESS_INFORMATION pi = {0};
    char filepath[MAX_PATH];
    wchar_t game_folder[MAX_PATH];

    launch_game = ml_game_by_id(ML_GAME_ELDEN_RING);
    if (!parse_args(__argc, __wargv)) return -1;
    if (full_modengine_dll[0] == L'\0' || !PathFileExistsW(full_modengine_dll) || PathIsDirectoryW(full_modengine_dll)) {
        /*if (decompress_embedded_dll_to(filepath)) {
            if (full_config_path[0] == L'\0') {
                GetModuleFileNameW(hInstance, full_config_path, MAX_PATH);
                PathRemoveFileSpecW(full_config_path);
            }
        } else*/ {
            GetModuleFileNameA(hInstance, filepath, MAX_PATH);
            PathRemoveFileSpecA(filepath);
            PathAppendA(filepath, "YAERModLoader.dll");
        }
    } else {
        if (StrChrW(full_modengine_dll, L':') == NULL && full_modengine_dll[0] != L'\\' && full_modengine_dll[0] != L'/') {
            char temp[MAX_PATH];
            GetModuleFileNameA(hInstance, filepath, MAX_PATH);
            PathRemoveFileSpecA(filepath);
            WideCharToMultiByte(CP_ACP, 0, full_modengine_dll, -1, temp, MAX_PATH, NULL, NULL);
            PathAppendA(filepath, temp);
        } else {
            WideCharToMultiByte(CP_ACP, 0, full_modengine_dll, -1, filepath, MAX_PATH, NULL, NULL);
        }
    }
    const HMODULE kernel32 = LoadLibraryW(L"kernel32.dll");
    FARPROC create_process_addr = GetProcAddress(kernel32, "CreateProcessW");

    if ((full_game_path[0] == L'\0' && !check_current_folder_for_game_path(full_game_path)) || (full_game_path[0] != L'\0' && !locate_game_executable(full_game_path))) {
        if (!app_find_game_path(launch_game->steam_app_id, game_folder)) {
            fwprintf(stderr, L"could not find %ls through Steam\n", launch_game->title);
            return -1;
        }
        lstrcpyW(full_game_path, game_folder);
        if (!locate_game_executable(full_game_path)) {
            fwprintf(stderr, L"could not find %ls executable in `%ls`\n", launch_game->title, game_folder);
            return -1;
        }
    }
    lstrcpyW(game_folder, full_game_path);
    PathRemoveFileSpecW(game_folder);
    if (full_config_path[0] != L'\0') SetEnvironmentVariableW(L"MODLOADER_CONFIG", full_config_path);
    {
        /* set SteamAppId here, to make sure the game can be launched w/o EAC */
        wchar_t app_id_str[16];
        _snwprintf(app_id_str, 16, L"%u", launch_game->steam_app_id);
        app_id_str[15] = L'\0';
        SetEnvironmentVariableW(L"SteamAppId", app_id_str);
        SetEnvironmentVariableW(L"SteamGameId", app_id_str);
        SetEnvironmentVariableW(L"SteamOverlayGameId", app_id_str);
    }
    {
        wchar_t game_key[32];
        MultiByteToWideChar(CP_ACP, 0, launch_game->key, -1, game_key, 32);
        game_key[31] = L'\0';
        SetEnvironmentVariableW(L"MODLOADER_GAME", game_key);
    }

    const BOOL success = DetourCreateProcessWithDllW(
        full_game_path,
        NULL,
        NULL,
        NULL,
        FALSE,
        suspend ? CREATE_SUSPENDED : 0,
        NULL,
        game_folder,
        &si,
        &pi,
        filepath,
        (const PDETOUR_CREATE_PROCESS_ROUTINEW)create_process_addr);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return success ? 0 : -1;
}
