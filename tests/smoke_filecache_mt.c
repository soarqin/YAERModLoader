/* Multithreaded stress test for the shared file cache.
 *
 * Compiles the real src/modloader/filecache.c and hammers filecache_find /
 * filecache_add from several threads at once, the way the game hooks do
 * (CreateFileW hook, archive path hook, Wwise hook all run on different game
 * threads). Guards against regressions of the khash data race: kh_put may
 * rehash and free internal arrays while another thread is probing them.
 */
#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include "test_common.h"
#include "modloader/filecache.h"

#define THREAD_COUNT 8
#define KEY_COUNT 4096
#define ROUNDS 4

static wchar_t keys[KEY_COUNT][32];
static wchar_t values[KEY_COUNT][48];
static volatile LONG mismatches = 0;

static DWORD WINAPI worker(LPVOID arg) {
    const int tid = (int)(intptr_t)arg;
    for (int round = 0; round < ROUNDS; round++) {
        for (int i = 0; i < KEY_COUNT; i++) {
            /* Spread threads across the key space so adds (table growth /
             * rehashes) and finds interleave heavily. */
            const int idx = (i + tid * (KEY_COUNT / THREAD_COUNT)) % KEY_COUNT;
            const wchar_t *found = filecache_find(keys[idx]);
            if (found == NULL) {
                /* Every third key is a negative entry (empty replacement). */
                found = filecache_add(keys[idx], idx % 3 == 0 ? L"" : values[idx]);
            }
            if (found == NULL) {
                InterlockedIncrement(&mismatches); /* allocation failure */
                continue;
            }
            const wchar_t *expect = idx % 3 == 0 ? L"" : values[idx];
            if (wcscmp(found, expect) != 0) {
                InterlockedIncrement(&mismatches);
            }
        }
    }
    return 0;
}

int main(void) {
    for (int i = 0; i < KEY_COUNT; i++) {
        _snwprintf(keys[i], 32, L"/mod/file_%d.bnd", i);
        keys[i][31] = L'\0';
        _snwprintf(values[i], 48, L"C:/mods/file_%d.bnd", i);
        values[i][47] = L'\0';
    }

    filecache_init();

    HANDLE threads[THREAD_COUNT];
    for (int t = 0; t < THREAD_COUNT; t++) {
        threads[t] = CreateThread(NULL, 0, worker, (LPVOID)(intptr_t)t, 0, NULL);
        EXPECT_NOT_NULL(threads[t]);
    }
    const DWORD wait = WaitForMultipleObjects(THREAD_COUNT, threads, TRUE, 60000);
    EXPECT_TRUE(wait >= WAIT_OBJECT_0 && wait < WAIT_OBJECT_0 + THREAD_COUNT);
    for (int t = 0; t < THREAD_COUNT; t++) {
        CloseHandle(threads[t]);
    }

    EXPECT_EQ(mismatches, 0);

    /* Single-threaded consistency check after the storm. */
    for (int i = 0; i < KEY_COUNT; i++) {
        const wchar_t *found = filecache_find(keys[i]);
        EXPECT_NOT_NULL(found);
        EXPECT_STREQ_W(found, i % 3 == 0 ? L"" : values[i]);
    }

    filecache_uninit();
    /* uninit on an already-destroyed cache must be a no-op, not a crash */
    filecache_uninit();

    printf("smoke_filecache_mt: all tests passed\n");
    return 0;
}
