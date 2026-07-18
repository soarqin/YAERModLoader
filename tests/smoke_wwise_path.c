#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "test_common.h"
#include "modloader/patches/wwise_path.h"

int main(void) {
    static const uint8_t wwise_call[] = {
        0xe8, 1, 2, 3, 4, 0x83, 0xf8, 0x01, 0x74, 0x05,
        0x48, 0x83, 0xc3, 0x38, 0x48, 0x83, 0x7d, 0x10, 0x08,
    };
    wchar_t *first;
    wchar_t *second;
    wchar_t long_path[600];

    EXPECT_EQ(wwise_find_open_call(wwise_call, sizeof(wwise_call)), 0);
    EXPECT_EQ(wwise_find_open_call(wwise_call, sizeof(wwise_call) - 1), SIZE_MAX);

    EXPECT_STREQ_W(wwise_strip_prefixes(L"sd:/sd_dlc02:/init.bnk"), L"init.bnk");
    EXPECT_STREQ_W(wwise_strip_prefixes(L"sd_dlc02:/1000519763.wem"), L"1000519763.wem");
    EXPECT_TRUE(wwise_wem_candidates(L"1000519763.wem", &first, &second));
    EXPECT_STREQ_W(first, L"wem/1000519763.wem");
    EXPECT_STREQ_W(second, L"wem/10/1000519763.wem");
    LocalFree(first);
    LocalFree(second);
    EXPECT_TRUE(!wwise_wem_candidates(L"1", &first, &second));
    EXPECT_NULL(first);
    EXPECT_NULL(second);

    long_path[0] = L'1';
    long_path[1] = L'0';
    for (size_t i = 2; i < 594; i++) long_path[i] = L'a';
    memcpy(long_path + 594, L".wem", 5 * sizeof(*long_path));
    EXPECT_TRUE(wwise_wem_candidates(long_path, &first, &second));
    EXPECT_EQ(wcslen(first), wcslen(long_path) + 4);
    EXPECT_EQ(wcslen(second), wcslen(long_path) + 7);
    EXPECT_TRUE(wcsncmp(first, L"wem/10", 6) == 0);
    EXPECT_TRUE(wcsncmp(second, L"wem/10/10", 9) == 0);
    LocalFree(first);
    LocalFree(second);

    printf("smoke_wwise_path: all tests passed\n");
    return 0;
}
