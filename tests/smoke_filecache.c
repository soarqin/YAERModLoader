#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include "test_common.h"
#define kcalloc(N,Z)  calloc(N,Z)
#define kmalloc(Z)    malloc(Z)
#define krealloc(P,Z) realloc(P,Z)
#define kfree(P)      free(P)
#include "khash.h"
#include "khash_wstr.h"

typedef struct {
    wchar_t *base_path;
    wchar_t *native_path;
} file_t_test;

int main(void) {
    khash_t(wstr) *h = kh_init(wstr);
    EXPECT_NOT_NULL(h);

    /* empty find returns kh_end */
    khiter_t k = kh_get(wstr, h, L"nonexistent");
    EXPECT_TRUE(k == kh_end(h));

    /* add 3 entries */
    int ret;
    file_t_test f1 = { L"/mod/weapon.bnd", L"C:/mods/weapon.bnd" };
    file_t_test f2 = { L"/mod/armor.bnd", L"C:/mods/armor.bnd" };
    /* non-ASCII key (Japanese) */
    file_t_test f3 = { L"\u6b66\u5668\u30d5\u30a1\u30a4\u30eb", L"C:/mods/weapon_jp.bnd" };

    k = kh_put(wstr, h, f1.base_path, &ret); EXPECT_TRUE(ret != 0); kh_value(h, k) = &f1;
    k = kh_put(wstr, h, f2.base_path, &ret); EXPECT_TRUE(ret != 0); kh_value(h, k) = &f2;
    k = kh_put(wstr, h, f3.base_path, &ret); EXPECT_TRUE(ret != 0); kh_value(h, k) = &f3;

    /* find hit x3 */
    k = kh_get(wstr, h, L"/mod/weapon.bnd");
    EXPECT_TRUE(k != kh_end(h));
    EXPECT_STREQ_W(((file_t_test*)kh_value(h, k))->native_path, L"C:/mods/weapon.bnd");

    k = kh_get(wstr, h, L"/mod/armor.bnd");
    EXPECT_TRUE(k != kh_end(h));
    EXPECT_STREQ_W(((file_t_test*)kh_value(h, k))->native_path, L"C:/mods/armor.bnd");

    k = kh_get(wstr, h, L"\u6b66\u5668\u30d5\u30a1\u30a4\u30eb");
    EXPECT_TRUE(k != kh_end(h));
    EXPECT_STREQ_W(((file_t_test*)kh_value(h, k))->native_path, L"C:/mods/weapon_jp.bnd");

    /* find miss */
    k = kh_get(wstr, h, L"nonexistent");
    EXPECT_TRUE(k == kh_end(h));

    /* iteration — count 3 entries */
    int count = 0;
    for (k = kh_begin(h); k != kh_end(h); ++k) {
        if (kh_exist(h, k)) count++;
    }
    EXPECT_EQ(count, 3);

    /* long key (200+ wchar_t) */
    wchar_t long_key[210];
    for (int i = 0; i < 200; i++) long_key[i] = L'a' + (i % 26);
    long_key[200] = L'\0';
    file_t_test f4 = { long_key, L"C:/mods/long.bnd" };
    k = kh_put(wstr, h, long_key, &ret); EXPECT_TRUE(ret != 0); kh_value(h, k) = &f4;
    k = kh_get(wstr, h, long_key);
    EXPECT_TRUE(k != kh_end(h));

    /* empty string key */
    file_t_test f5 = { L"", L"C:/mods/empty.bnd" };
    k = kh_put(wstr, h, L"", &ret); EXPECT_TRUE(ret != 0); kh_value(h, k) = &f5;
    k = kh_get(wstr, h, L"");
    EXPECT_TRUE(k != kh_end(h));

    /* duplicate add — ret==0 means key exists */
    k = kh_put(wstr, h, L"/mod/weapon.bnd", &ret);
    EXPECT_EQ(ret, 0); /* key already present — first-wins semantics */

    /* destroy */
    kh_destroy(wstr, h);

    printf("smoke_filecache: all tests passed\n");
    return 0;
}
