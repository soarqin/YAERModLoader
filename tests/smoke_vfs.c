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
    EXPECT_TRUE(vfs_normalize_path(L"data0:/PARAM/gameparam/gameparam.parambnd.dcx", &normalized));
    EXPECT_STREQ_W(normalized, L"param\\gameparam\\gameparam.parambnd.dcx");
    LocalFree(normalized);
    EXPECT_TRUE(!vfs_normalize_path(L"..\\test.bin", &normalized));
    {
        wchar_t deep[1600];
        size_t offset = 0;
        for (size_t i = 0; i < 600; i++) {
            deep[offset++] = L'a';
            deep[offset++] = L'/';
        }
        deep[offset] = L'\0';
        EXPECT_TRUE(vfs_normalize_path(deep, &normalized));
        EXPECT_EQ(wcslen(normalized), 1199);
        LocalFree(normalized);
        deep[offset++] = L'.';
        deep[offset++] = L'.';
        deep[offset++] = L'/';
        deep[offset++] = L'.';
        deep[offset++] = L'.';
        deep[offset] = L'\0';
        EXPECT_TRUE(vfs_normalize_path(deep, &normalized));
        EXPECT_EQ(wcslen(normalized), 1195);
        LocalFree(normalized);
    }

    vfs_init();
    EXPECT_TRUE(vfs_add_package(first));
    EXPECT_TRUE(vfs_add_package(second));
    EXPECT_EQ(vfs_generation(), 0);
    EXPECT_NOT_NULL(vfs_lookup(L"parts/test.bin"));
    EXPECT_NOT_NULL(vfs_lookup(L"data0:/parts/test.bin"));
    {
        wchar_t *uncached_uid = NULL;
        EXPECT_TRUE(vfs_virtual_to_uid(L"parts/test.bin", &uncached_uid));
        EXPECT_TRUE(wcscmp(uncached_uid, L"\\\\me3??0") == 0);
        EXPECT_STREQ_W(vfs_uid_to_path(uncached_uid), vfs_lookup(L"parts/test.bin"));
        LocalFree(uncached_uid);
    }
    EXPECT_EQ(vfs_generation(), 0);
    EXPECT_EQ(vfs_reset_lookup_caches(), 1);
    EXPECT_EQ(vfs_generation(), 1);
    EXPECT_TRUE(wcsncmp(vfs_lookup(L"parts/test.bin"), second, wcslen(second)) == 0);
    {
        wchar_t absolute[MAX_PATH];
        wchar_t *prefixed_uid = NULL;
        lstrcpyW(absolute, root); PathAppendW(absolute, L"parts/test.bin");
        EXPECT_STREQ_W(vfs_lookup_prefixed_domain(absolute, root, VFS_LOOKUP_DISK_WIDE),
                       vfs_lookup(L"parts/test.bin"));
        EXPECT_TRUE(vfs_virtual_to_uid_prefixed(absolute, root, &prefixed_uid));
        EXPECT_STREQ_W(vfs_uid_to_path(prefixed_uid), vfs_lookup(L"parts/test.bin"));
        LocalFree(prefixed_uid);
        lstrcpyW(absolute, root); lstrcatW(absolute, L"-outside\\parts\\test.bin");
        EXPECT_NULL(vfs_lookup_prefixed_domain(absolute, root, VFS_LOOKUP_DISK_WIDE));
        EXPECT_TRUE(!vfs_virtual_to_uid_prefixed(absolute, root, &prefixed_uid));
    }
    EXPECT_STREQ_W(vfs_lookup_domain(L"parts/test.bin", VFS_LOOKUP_VIRTUAL), vfs_lookup(L"parts/test.bin"));
    EXPECT_STREQ_W(vfs_lookup_domain(L"parts/test.bin", VFS_LOOKUP_DISK_WIDE), vfs_lookup(L"parts/test.bin"));
    EXPECT_STREQ_W(vfs_lookup_domain(L"parts/test.bin", VFS_LOOKUP_DISK_ANSI), vfs_lookup(L"parts/test.bin"));
    EXPECT_STREQ_W(vfs_lookup_domain(L"parts/test.bin", VFS_LOOKUP_WWISE), vfs_lookup(L"parts/test.bin"));
    EXPECT_NULL(vfs_lookup_domain(L"parts/test.bin", VFS_LOOKUP_DOMAIN_COUNT));
    EXPECT_NULL(vfs_lookup_domain(L"parts/domain-missing.bin", VFS_LOOKUP_VIRTUAL));
    EXPECT_NULL(vfs_lookup_domain(L"parts/domain-missing.bin", VFS_LOOKUP_WWISE));
    EXPECT_NOT_NULL(vfs_route_read_path(L"parts/test.bin", GENERIC_READ, OPEN_EXISTING));
    EXPECT_NOT_NULL(vfs_route_read_path_a("parts/test.bin", GENERIC_READ, OPEN_EXISTING));
    EXPECT_NULL(vfs_route_read_path(L"parts/test.bin", GENERIC_WRITE, OPEN_EXISTING));
    EXPECT_NULL(vfs_route_read_path(L"parts/test.bin", GENERIC_READ, CREATE_ALWAYS));
    EXPECT_TRUE(vfs_register_writable_path(L"settings/test.ini", L"C:\\profile\\test.ini"));
    EXPECT_TRUE(!vfs_register_writable_path(L"", L"C:\\profile\\test.ini"));
    EXPECT_TRUE(!vfs_register_writable_path(L"settings/empty.ini", L""));
    EXPECT_TRUE(vfs_has_writable_paths());
    EXPECT_STREQ_W(vfs_route_writable_path(L"settings/test.ini"), L"C:\\profile\\test.ini");
    EXPECT_TRUE(vfs_register_writable_path(L"SETTINGS\\test.ini", L"C:\\profile\\test.ini"));
    EXPECT_TRUE(!vfs_register_writable_path(L"settings/test.ini", L"C:\\other\\test.ini"));
    EXPECT_STREQ_W(vfs_route_read_path(L"settings/test.ini", GENERIC_WRITE, CREATE_ALWAYS), L"C:\\profile\\test.ini");
    vfs_recursion_guard_enter();
    EXPECT_NULL(vfs_route_read_path(L"parts/test.bin", GENERIC_READ, OPEN_EXISTING));
    vfs_recursion_guard_leave();
    EXPECT_NULL(vfs_lookup(L"parts/missing.bin"));
    {
        wchar_t *uid = NULL;
        wchar_t *cached_uid = NULL;
        EXPECT_TRUE(vfs_virtual_to_uid(L"parts/test.bin", &uid));
        EXPECT_TRUE(wcscmp(uid, L"\\\\me3??0") == 0);
        EXPECT_NOT_NULL(uid);
        EXPECT_TRUE(vfs_virtual_to_uid(L"parts/test.bin", &cached_uid));
        EXPECT_STREQ_W(cached_uid, uid);
        EXPECT_TRUE(cached_uid != uid);
        LocalFree(cached_uid);
        EXPECT_TRUE(!vfs_virtual_to_uid(L"parts/uid-missing.bin", &cached_uid));
        EXPECT_NULL(cached_uid);
        EXPECT_TRUE(!vfs_virtual_to_uid(L"parts/uid-missing.bin", &cached_uid));
        EXPECT_NULL(cached_uid);
        EXPECT_STREQ_W(vfs_uid_to_path(uid), vfs_lookup(L"parts/test.bin"));
        EXPECT_STREQ_W(vfs_lookup(uid), vfs_lookup(L"parts/test.bin"));
        vfs_begin_lookup_reset();
        EXPECT_EQ(vfs_generation(), 0);
        EXPECT_STREQ_W(vfs_uid_to_path(uid), vfs_lookup(L"parts/test.bin"));
        EXPECT_EQ(vfs_reset_lookup_caches(), 2);
        EXPECT_EQ(vfs_generation(), 2);
        EXPECT_TRUE(vfs_virtual_to_uid(L"parts/test.bin", &cached_uid));
        EXPECT_TRUE(wcscmp(cached_uid, uid) == 0);
        LocalFree(cached_uid);
        EXPECT_NULL(vfs_uid_to_path(L"\\\\me3??ffffffff"));
        EXPECT_NULL(vfs_uid_to_path(L"\\\\me3??-2"));
        EXPECT_NULL(vfs_uid_to_path(L"\\\\me3?? 2"));
        LocalFree(uid);
    }
    vfs_uninit();

    DeleteFileW(path);
    lstrcpyW(path, first); PathAppendW(path, L"parts\\test.bin"); DeleteFileW(path);
    lstrcpyW(path, second); PathAppendW(path, L"parts"); RemoveDirectoryW(path);
    lstrcpyW(path, first); PathAppendW(path, L"parts"); RemoveDirectoryW(path);
    RemoveDirectoryW(second); RemoveDirectoryW(first); RemoveDirectoryW(root);
    printf("smoke_vfs: all tests passed\n");
    return 0;
}
