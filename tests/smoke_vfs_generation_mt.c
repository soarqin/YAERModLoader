#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>

#include "test_common.h"
#include "modloader/vfs.h"

#define LOOKUP_THREADS 6
#define RESET_COUNT 1000

static const wchar_t *lookup_path = L"parts/test.bin";
static volatile LONG running = 1;
static volatile LONG failures;

static DWORD WINAPI lookup_worker(LPVOID parameter) {
    const wchar_t *expected = parameter;
    while (InterlockedCompareExchange(&running, 0, 0) != 0) {
        const wchar_t *found = vfs_lookup(lookup_path);
        if (found == NULL || wcscmp(found, expected) != 0) InterlockedIncrement(&failures);
        if (vfs_generation() != 0) {
            wchar_t *uid = NULL;
            if (vfs_virtual_to_uid(lookup_path, &uid)) {
                const wchar_t *uid_path = vfs_uid_to_path(uid);
                if (uid_path != NULL && wcscmp(uid_path, expected) != 0) InterlockedIncrement(&failures);
                LocalFree(uid);
            }
        }
    }
    return 0;
}

int main(void) {
    wchar_t temp[MAX_PATH];
    wchar_t root[MAX_PATH];
    wchar_t directory[MAX_PATH];
    wchar_t file_path[MAX_PATH];
    HANDLE file;
    HANDLE threads[LOOKUP_THREADS];

    EXPECT_TRUE(GetTempPathW(MAX_PATH, temp) != 0);
    EXPECT_TRUE(GetTempFileNameW(temp, L"gen", 0, root) != 0);
    DeleteFileW(root);
    EXPECT_TRUE(CreateDirectoryW(root, NULL));
    lstrcpyW(directory, root); PathAppendW(directory, L"parts");
    EXPECT_TRUE(CreateDirectoryW(directory, NULL));
    lstrcpyW(file_path, directory); PathAppendW(file_path, L"test.bin");
    file = CreateFileW(file_path, GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, NULL);
    EXPECT_TRUE(file != INVALID_HANDLE_VALUE);
    CloseHandle(file);

    vfs_init();
    EXPECT_TRUE(vfs_add_package(root));
    EXPECT_EQ(vfs_reset_lookup_caches(), 1);
    for (size_t i = 0; i < LOOKUP_THREADS; i++) {
        threads[i] = CreateThread(NULL, 0, lookup_worker, file_path, 0, NULL);
        EXPECT_NOT_NULL(threads[i]);
    }
    for (size_t i = 0; i < RESET_COUNT; i++) {
        vfs_begin_lookup_reset();
        vfs_reset_lookup_caches();
    }
    InterlockedExchange(&running, 0);
    EXPECT_EQ(WaitForMultipleObjects(LOOKUP_THREADS, threads, TRUE, 60000), WAIT_OBJECT_0);
    for (size_t i = 0; i < LOOKUP_THREADS; i++) CloseHandle(threads[i]);
    EXPECT_EQ(failures, 0);
    EXPECT_EQ(vfs_generation(), RESET_COUNT + 1);
    vfs_uninit();

    DeleteFileW(file_path);
    RemoveDirectoryW(directory);
    RemoveDirectoryW(root);
    printf("smoke_vfs_generation_mt: all tests passed\n");
    return 0;
}
