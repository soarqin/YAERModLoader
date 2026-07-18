#include <stdint.h>
#include <stdio.h>

#include "test_common.h"
#include "scanner.h"

int main(void) {
    /* data1:  48 8B 05 11 22 33 44 C3 */
    uint8_t data[] = { 0x48, 0x8B, 0x05, 0x11, 0x22, 0x33, 0x44, 0xC3 };
    const size_t data_size = sizeof(data);

    /* exact match (no wildcards) -> without_mask path, hit at offset 0 */
    EXPECT_EQ(sig_scan(data, data_size, "48 8B 05"), data);

    /* wildcard match -> with_mask path, spans the whole buffer */
    EXPECT_EQ(sig_scan(data, data_size, "48 8B 05 ?? ?? ?? ?? C3"), data);

    /* single byte at the very end (boundary: s == data_size - pat_size) */
    EXPECT_EQ(sig_scan(data, data_size, "C3"), data + 7);

    /* interior match */
    EXPECT_EQ(sig_scan(data, data_size, "33 44"), data + 5);

    /* no match returns NULL (both paths) */
    EXPECT_NULL(sig_scan(data, data_size, "99 99 99"));
    EXPECT_NULL(sig_scan(data, data_size, "48 ?? 99"));

    /* regression: pattern longer than data must not underflow / read OOB.
       Before the guard, `data_size - pat_size` wrapped to a huge value. */
    {
        uint8_t tiny[] = { 0x48, 0x8B };
        EXPECT_NULL(sig_scan(tiny, sizeof(tiny), "48 8B 05 11"));    /* without_mask */
        EXPECT_NULL(sig_scan(tiny, sizeof(tiny), "48 ?? 05 11"));    /* with_mask */
        EXPECT_NULL(sig_scan(tiny, 0, "48"));                        /* empty data */
        EXPECT_NULL(sig_scan(tiny, 1, "48 8B"));                     /* off-by-one */
    }

    printf("smoke_scanner: all tests passed\n");
    return 0;
}
