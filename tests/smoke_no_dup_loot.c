#include <stdio.h>
#include <stdint.h>
#include "test_common.h"
#include "khash.h"
KHASH_MAP_INIT_INT(item_count, int32_t)

int main(void) {
    /* init */
    khash_t(item_count) *h = kh_init(item_count);
    EXPECT_NOT_NULL(h);

    /* add item_id=42 with count=1 */
    int ret;
    khiter_t k = kh_put(item_count, h, 42u, &ret);
    EXPECT_TRUE(ret != 0); /* new key */
    kh_value(h, k) = 1;

    /* find hit */
    k = kh_get(item_count, h, 42u);
    EXPECT_TRUE(k != kh_end(h));
    EXPECT_EQ(kh_value(h, k), 1);

    /* increment */
    kh_value(h, k)++;
    EXPECT_EQ(kh_value(h, k), 2);

    /* find miss */
    k = kh_get(item_count, h, 999u);
    EXPECT_TRUE(k == kh_end(h));

    /* add item_id=100 */
    k = kh_put(item_count, h, 100u, &ret);
    EXPECT_TRUE(ret != 0);
    kh_value(h, k) = 5;

    /* iteration via kh_foreach_value — count entries */
    int count = 0;
    int32_t v;
    kh_foreach_value(h, v, { (void)v; count++; });
    EXPECT_EQ(count, 2);

    /* clear loop — set all to 0 (mirrors clear_item_count) */
    for (k = kh_begin(h); k != kh_end(h); ++k) {
        if (kh_exist(h, k)) kh_value(h, k) = 0;
    }
    k = kh_get(item_count, h, 42u);
    EXPECT_TRUE(k != kh_end(h));
    EXPECT_EQ(kh_value(h, k), 0); /* entry still exists, count reset */

    /* duplicate add — ret==0 means key already exists */
    k = kh_put(item_count, h, 42u, &ret);
    EXPECT_EQ(ret, 0); /* key already present */

    /* destroy */
    kh_destroy(item_count, h);

    printf("smoke_no_dup_loot: all tests passed\n");
    return 0;
}
