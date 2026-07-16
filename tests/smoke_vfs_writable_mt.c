#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "test_common.h"
#include "modloader/vfs.h"

#define THREAD_COUNT 8
#define KEY_COUNT 2048

static wchar_t keys[KEY_COUNT][48];
static wchar_t values[KEY_COUNT][64];
static volatile LONG failures;

static DWORD WINAPI worker(LPVOID parameter) {
    size_t thread = (size_t)parameter;
    for (size_t i = thread; i < KEY_COUNT; i += THREAD_COUNT) {
        if (!vfs_register_writable_path(keys[i], values[i])) {
            InterlockedIncrement(&failures);
            continue;
        }
        {
            const wchar_t *own = vfs_route_writable_path(keys[i]);
            if (own == NULL || wcscmp(own, values[i]) != 0) InterlockedIncrement(&failures);
        }
        for (size_t probe = 0; probe <= i; probe += 17) {
            const wchar_t *found = vfs_route_writable_path(keys[probe]);
            if (found != NULL && wcscmp(found, values[probe]) != 0) InterlockedIncrement(&failures);
        }
    }
    return 0;
}

int main(void) {
    HANDLE threads[THREAD_COUNT];
    vfs_init();
    for (size_t i = 0; i < KEY_COUNT; i++) {
        _snwprintf(keys[i], 48, L"settings/file_%zu.ini", i);
        _snwprintf(values[i], 64, L"C:\\profiles\\file_%zu.ini", i);
    }
    for (size_t i = 0; i < THREAD_COUNT; i++) {
        threads[i] = CreateThread(NULL, 0, worker, (LPVOID)i, 0, NULL);
        EXPECT_NOT_NULL(threads[i]);
    }
    EXPECT_EQ(WaitForMultipleObjects(THREAD_COUNT, threads, TRUE, 60000), WAIT_OBJECT_0);
    for (size_t i = 0; i < THREAD_COUNT; i++) CloseHandle(threads[i]);
    EXPECT_EQ(failures, 0);
    for (size_t i = 0; i < KEY_COUNT; i++) {
        EXPECT_STREQ_W(vfs_route_writable_path(keys[i]), values[i]);
    }
    vfs_uninit();
    printf("smoke_vfs_writable_mt: all tests passed\n");
    return 0;
}
