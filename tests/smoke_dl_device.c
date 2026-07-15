#include <stdint.h>
#include <string.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "test_common.h"
#include "modloader/patches/dl_device.h"

int main(void) {
    uint8_t header[64] = { 0 };
    uint64_t first;
    uint64_t second;
    wchar_t temporary[MAX_PATH];
    uint32_t file_size = 64;
    uint32_t bucket_count = 2;
    uint32_t bucket_offset = 32;
    ml_dl_virtual_root_t roots[2] = { 0 };
    ml_dl_device_manager_t manager = { 0 };
    wchar_t *expanded = NULL;

    memcpy(header, "BHD5", 4);
    memcpy(header + 12, &file_size, sizeof(file_size));
    memcpy(header + 16, &bucket_count, sizeof(bucket_count));
    memcpy(header + 20, &bucket_offset, sizeof(bucket_offset));
    EXPECT_TRUE(ml_bhd5_header_valid(header, sizeof(header)));
    EXPECT_TRUE(ml_boot_boost_cache_key(header, sizeof(header), &first));
    EXPECT_TRUE(ml_boot_boost_cache_key(header, sizeof(header), &second));
    EXPECT_EQ(first, second);
    EXPECT_TRUE(GetTempPathW(MAX_PATH, temporary) != 0);
    EXPECT_TRUE(GetTempFileNameW(temporary, L"bbd", 0, temporary) != 0);
    DeleteFileW(temporary);
    EXPECT_TRUE(ml_boot_boost_cache_store(temporary, header, sizeof(header)));
    memset(header, 0, sizeof(header));
    EXPECT_TRUE(ml_boot_boost_cache_load(temporary, header, sizeof(header)));
    DeleteFileW(temporary);
    memcpy(roots[0].root.storage.inline_storage, L"dataX", 12);
    roots[0].root.length = roots[0].root.capacity = 4;
    roots[0].root.encoding = 1;
    memcpy(roots[0].expanded.storage.inline_storage, L"game:/X", 16);
    roots[0].expanded.length = roots[0].expanded.capacity = 6;
    roots[0].expanded.encoding = 1;
    memcpy(roots[1].root.storage.inline_storage, L"gameX", 12);
    roots[1].root.length = roots[1].root.capacity = 4;
    roots[1].root.encoding = 1;
    memcpy(roots[1].expanded.storage.inline_storage, L"rootX", 12);
    roots[1].expanded.length = roots[1].expanded.capacity = 4;
    roots[1].expanded.encoding = 1;
    manager.virtual_roots.first = roots;
    manager.virtual_roots.last = roots + 2;
    EXPECT_TRUE(ml_dl_device_expand_path(&manager, L"data:/parts/test.bin", &expanded));
    EXPECT_STREQ_W(expanded, L"rootparts/test.bin");
    LocalFree(expanded);
    EXPECT_TRUE(ml_dl_device_expand_path(&manager, L"data:/parts:/test.bin", &expanded));
    EXPECT_STREQ_W(expanded, L"rootparts:/test.bin");
    LocalFree(expanded);
    EXPECT_TRUE(ml_dl_device_expand_path(&manager, L"data:\\parts\\test.bin", &expanded));
    EXPECT_STREQ_W(expanded, L"data:\\parts\\test.bin");
    LocalFree(expanded);
    header[0] = 'X';
    EXPECT_TRUE(!ml_bhd5_header_valid(header, sizeof(header)));
    printf("smoke_dl_device: all tests passed\n");
    return 0;
}
