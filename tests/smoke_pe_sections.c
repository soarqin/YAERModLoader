#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "test_common.h"
#include "pe.h"

int main(void) {
    HMODULE self = GetModuleHandleW(NULL);
    const IMAGE_SECTION_HEADER *text;
    const IMAGE_SECTION_HEADER *data;
    const IMAGE_SECTION_HEADER *rdata;
    size_t size = 0;

    EXPECT_NOT_NULL(self);

    text = pe_section_by_name(self, ".text");
    EXPECT_NOT_NULL(text);
    EXPECT_NOT_NULL(pe_section_data(self, text, &size));
    EXPECT_TRUE(size > 0);

    data = pe_section_by_name(self, ".data");
    EXPECT_NOT_NULL(data);
    EXPECT_NOT_NULL(pe_section_data(self, data, &size));
    EXPECT_TRUE(size > 0);

    rdata = pe_section_by_name(self, ".rdata");
    EXPECT_NOT_NULL(rdata);
    EXPECT_NOT_NULL(pe_section_data(self, rdata, &size));
    EXPECT_TRUE(size > 0);

    EXPECT_NULL(pe_section_by_name(self, ".missing"));

    printf("smoke_pe_sections: all tests passed\n");
    return 0;
}
