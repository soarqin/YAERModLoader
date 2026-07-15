#include <stdio.h>

#include "test_common.h"
#include "modloader/patches/wwise_path.h"

int main(void) {
    wchar_t first[64];
    wchar_t second[64];

    EXPECT_STREQ_W(wwise_strip_prefixes(L"sd:/sd_dlc02:/init.bnk"), L"init.bnk");
    EXPECT_STREQ_W(wwise_strip_prefixes(L"sd_dlc02:/1000519763.wem"), L"1000519763.wem");
    EXPECT_TRUE(wwise_wem_candidates(L"1000519763.wem", first, 64, second, 64));
    EXPECT_STREQ_W(first, L"wem/1000519763.wem");
    EXPECT_STREQ_W(second, L"wem/10/1000519763.wem");
    EXPECT_TRUE(!wwise_wem_candidates(L"1", first, 64, second, 64));

    printf("smoke_wwise_path: all tests passed\n");
    return 0;
}
