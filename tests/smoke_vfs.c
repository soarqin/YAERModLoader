#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>

#include "test_common.h"
#include "modloader/vfs.h"

int main(void) {
    wchar_t root[MAX_PATH];
    wchar_t first[MAX_PATH];
    wchar_t second[MAX_PATH];
    wchar_t path[MAX_PATH];
    wchar_t *normalized = NULL;
    HANDLE file;

    EXPECT_TRUE(GetTempPathW(MAX_PATH, root) != 0);
    EXPECT_TRUE(GetTempFileNameW(root, L"vfs", 0, root) != 0);
    DeleteFileW(root);
    EXPECT_TRUE(CreateDirectoryW(root, NULL));
    lstrcpyW(first, root); PathAppendW(first, L"first");
    lstrcpyW(second, root); PathAppendW(second, L"second");
    EXPECT_TRUE(CreateDirectoryW(first, NULL));
    EXPECT_TRUE(CreateDirectoryW(second, NULL));
    lstrcpyW(path, first); PathAppendW(path, L"parts"); EXPECT_TRUE(CreateDirectoryW(path, NULL));
    PathAppendW(path, L"test.bin");
    file = CreateFileW(path, GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, NULL); EXPECT_TRUE(file != INVALID_HANDLE_VALUE); CloseHandle(file);
    lstrcpyW(path, second); PathAppendW(path, L"parts"); EXPECT_TRUE(CreateDirectoryW(path, NULL));
    PathAppendW(path, L"test.bin");
    file = CreateFileW(path, GENERIC_WRITE, 0, NULL, CREATE_NEW, 0, NULL); EXPECT_TRUE(file != INVALID_HANDLE_VALUE); CloseHandle(file);

    EXPECT_TRUE(vfs_normalize_path(L"\\PARTS/./test.bin\0", &normalized));
    EXPECT_STREQ_W(normalized, L"parts\\test.bin");
    LocalFree(normalized);
    EXPECT_TRUE(!vfs_normalize_path(L"..\\test.bin", &normalized));

    vfs_init();
    EXPECT_TRUE(vfs_add_package(first));
    EXPECT_TRUE(vfs_add_package(second));
    EXPECT_NOT_NULL(vfs_lookup(L"parts/test.bin"));
    EXPECT_TRUE(wcsncmp(vfs_lookup(L"parts/test.bin"), second, wcslen(second)) == 0);
    EXPECT_NOT_NULL(vfs_route_read_path(L"parts/test.bin", GENERIC_READ, OPEN_EXISTING));
    EXPECT_NOT_NULL(vfs_route_read_path_a("parts/test.bin", GENERIC_READ, OPEN_EXISTING));
    EXPECT_NULL(vfs_route_read_path(L"parts/test.bin", GENERIC_WRITE, OPEN_EXISTING));
    EXPECT_NULL(vfs_route_read_path(L"parts/test.bin", GENERIC_READ, CREATE_ALWAYS));
    EXPECT_TRUE(vfs_register_writable_path(L"settings/test.ini", L"C:\\profile\\test.ini"));
    EXPECT_TRUE(!vfs_register_writable_path(L"", L"C:\\profile\\test.ini"));
    EXPECT_TRUE(!vfs_register_writable_path(L"settings/empty.ini", L""));
    EXPECT_TRUE(vfs_has_writable_paths());
    EXPECT_STREQ_W(vfs_route_writable_path(L"settings/test.ini"), L"C:\\profile\\test.ini");
    EXPECT_STREQ_W(vfs_route_read_path(L"settings/test.ini", GENERIC_WRITE, CREATE_ALWAYS), L"C:\\profile\\test.ini");
    vfs_recursion_guard_enter();
    EXPECT_NULL(vfs_route_read_path(L"parts/test.bin", GENERIC_READ, OPEN_EXISTING));
    vfs_recursion_guard_leave();
    EXPECT_NULL(vfs_lookup(L"parts/missing.bin"));
    vfs_uninit();

    DeleteFileW(path);
    lstrcpyW(path, first); PathAppendW(path, L"parts\\test.bin"); DeleteFileW(path);
    lstrcpyW(path, second); PathAppendW(path, L"parts"); RemoveDirectoryW(path);
    lstrcpyW(path, first); PathAppendW(path, L"parts"); RemoveDirectoryW(path);
    RemoveDirectoryW(second); RemoveDirectoryW(first); RemoveDirectoryW(root);
    printf("smoke_vfs: all tests passed\n");
    return 0;
}
