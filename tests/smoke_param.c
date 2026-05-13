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
    const wchar_t *name;
    int value; /* stand-in for er_param_table_t* */
} er_param_type_test_t;

int main(void) {
    /* init */
    khash_t(wstr) *h = kh_init(wstr);
    EXPECT_NOT_NULL(h);

    /* find on empty map returns kh_end (not crash) */
    khiter_t k = kh_get(wstr, h, L"AtkParam_Pc");
    EXPECT_TRUE(k == kh_end(h));

    /* add 3 entries — keys point into static const data (not owned by entries) */
    static er_param_type_test_t p1 = { L"AtkParam_Pc", 1 };
    static er_param_type_test_t p2 = { L"EquipParamWeapon", 2 };
    static er_param_type_test_t p3 = { L"SpEffectParam", 3 };

    int ret;
    k = kh_put(wstr, h, p1.name, &ret); EXPECT_TRUE(ret != 0); kh_value(h, k) = &p1;
    k = kh_put(wstr, h, p2.name, &ret); EXPECT_TRUE(ret != 0); kh_value(h, k) = &p2;
    k = kh_put(wstr, h, p3.name, &ret); EXPECT_TRUE(ret != 0); kh_value(h, k) = &p3;

    /* find hit x3 */
    k = kh_get(wstr, h, L"AtkParam_Pc");
    EXPECT_TRUE(k != kh_end(h));
    EXPECT_EQ(((er_param_type_test_t*)kh_value(h, k))->value, 1);

    k = kh_get(wstr, h, L"EquipParamWeapon");
    EXPECT_TRUE(k != kh_end(h));
    EXPECT_EQ(((er_param_type_test_t*)kh_value(h, k))->value, 2);

    k = kh_get(wstr, h, L"SpEffectParam");
    EXPECT_TRUE(k != kh_end(h));
    EXPECT_EQ(((er_param_type_test_t*)kh_value(h, k))->value, 3);

    /* find miss */
    k = kh_get(wstr, h, L"NonExistentParam");
    EXPECT_TRUE(k == kh_end(h));

    /* kh_clear must NOT free user entries — save pointers before clear */
    er_param_type_test_t *saved_p1 = &p1;
    er_param_type_test_t *saved_p2 = &p2;
    /* kh_clear must NOT free user entries */
    kh_clear(wstr, h);

    /* verify size is 0 after clear */
    EXPECT_EQ((int)kh_size(h), 0);

    /* verify saved pointers are still readable (kh_clear did NOT free them) */
    EXPECT_EQ(saved_p1->value, 1);
    EXPECT_EQ(saved_p2->value, 2);

    /* re-add after clear */
    k = kh_put(wstr, h, p1.name, &ret); EXPECT_TRUE(ret != 0); kh_value(h, k) = &p1;
    k = kh_get(wstr, h, L"AtkParam_Pc");
    EXPECT_TRUE(k != kh_end(h));

    /* destroy */
    kh_destroy(wstr, h);

    printf("smoke_param: all tests passed\n");
    return 0;
}
