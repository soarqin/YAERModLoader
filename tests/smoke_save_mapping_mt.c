#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>

#include "test_common.h"
#include "game/game.h"
#include "modloader/patches/save_mapping.h"
#include "modloader/vfs.h"

#define ITERATIONS 2000

static const ml_game_descriptor_t *game;
static wchar_t source[MAX_PATH];
static volatile LONG failures;

static DWORD WINAPI route_worker(LPVOID parameter) {
    (void)parameter;
    for (size_t i = 0; i < ITERATIONS; i++) {
        const wchar_t *mapped = NULL;
        if (ml_save_mapping_route(source, &mapped) && mapped == NULL) InterlockedIncrement(&failures);
    }
    return 0;
}

static DWORD WINAPI config_worker(LPVOID parameter) {
    (void)parameter;
    for (size_t i = 0; i < ITERATIONS; i++) {
        if (!ml_save_mapping_init(game, L"sekiro-mt.sl2")) InterlockedIncrement(&failures);
        if ((i % 7) == 0) ml_save_mapping_uninit();
    }
    return 0;
}

int main(void) {
    wchar_t old_appdata[MAX_PATH];
    wchar_t root[MAX_PATH];
    DWORD old_length = GetEnvironmentVariableW(L"APPDATA", old_appdata, MAX_PATH);
    HANDLE threads[5];

    game = ml_game_by_id(ML_GAME_SEKIRO);
    EXPECT_NOT_NULL(game);
    EXPECT_TRUE(GetTempPathW(MAX_PATH, root) != 0);
    EXPECT_TRUE(GetTempFileNameW(root, L"smt", 0, root) != 0);
    DeleteFileW(root);
    EXPECT_TRUE(CreateDirectoryW(root, NULL));
    EXPECT_TRUE(SetEnvironmentVariableW(L"APPDATA", root));
    lstrcpyW(source, root);
    PathAppendW(source, L"Sekiro\\76561198000000000\\S0000.sl2");

    vfs_init();
    EXPECT_TRUE(ml_save_mapping_init(game, L"sekiro-mt.sl2"));
    threads[0] = CreateThread(NULL, 0, config_worker, NULL, 0, NULL);
    for (size_t i = 1; i < 5; i++) threads[i] = CreateThread(NULL, 0, route_worker, NULL, 0, NULL);
    for (size_t i = 0; i < 5; i++) EXPECT_NOT_NULL(threads[i]);
    EXPECT_EQ(WaitForMultipleObjects(5, threads, TRUE, 60000), WAIT_OBJECT_0);
    for (size_t i = 0; i < 5; i++) CloseHandle(threads[i]);
    EXPECT_EQ(failures, 0);

    ml_save_mapping_uninit();
    vfs_uninit();
    RemoveDirectoryW(root);
    SetEnvironmentVariableW(L"APPDATA", old_length != 0 && old_length < MAX_PATH ? old_appdata : NULL);
    printf("smoke_save_mapping_mt: all tests passed\n");
    return 0;
}
