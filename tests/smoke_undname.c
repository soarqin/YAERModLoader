#include <stdio.h>
#include <string.h>

#include "test_common.h"
#include "undname.h"

static int expect_demangle(const char *mangled, const char *expected) {
    char out[128];
    EXPECT_TRUE(undname_class(mangled, out, sizeof(out)));
    EXPECT_TRUE(strcmp(out, expected) == 0);
    return 0;
}

int main(void) {
    char out[32];

    if (expect_demangle(".?AVCSRegulationManager@CS@@@", "CS::CSRegulationManager") != 0) return 1;
    if (expect_demangle(".?AVCSMemoryImp@CS@@@", "CS::CSMemoryImp") != 0) return 1;
    if (expect_demangle(".?AVCSGraphicsImp@CS@@@", "CS::CSGraphicsImp") != 0) return 1;
    if (expect_demangle(".?AVDLEncryptedBinderLightUtility@DLEBL@@@", "DLEBL::DLEncryptedBinderLightUtility") != 0) return 1;
    if (expect_demangle(".?AVIOHookBlocking@DLMOW@@@", "DLMOW::IOHookBlocking") != 0) return 1;
    if (expect_demangle(".?AVNoNamespaceClass@@", "NoNamespaceClass") != 0) return 1;

    EXPECT_TRUE(!undname_class(NULL, out, sizeof(out)));
    EXPECT_TRUE(!undname_class("CSRegulationManager", out, sizeof(out)));
    EXPECT_TRUE(!undname_class(".?AUCSRegulationManager@CS@@@", out, sizeof(out)));
    EXPECT_TRUE(!undname_class(".?AVCSRegulationManager@CS@@@", out, 4));

    printf("smoke_undname: all tests passed\n");
    return 0;
}
