#include <stdint.h>
#include <stdio.h>

#include "test_common.h"
#include "process/fd4_step.h"

static void *seen_this;
static fd4_time_t *seen_time;

static void __cdecl original_step(void *this_ptr, fd4_time_t *time) {
    seen_this = this_ptr;
    seen_time = time;
}

static void __cdecl trampoline(void *this_ptr, fd4_time_t *time) {
    original_step(this_ptr, time);
}

int main(void) {
    fd4_time_t time = { 0, 1.0f };
    int object = 0;

    trampoline(&object, &time);
    EXPECT_EQ(seen_this, &object);
    EXPECT_EQ(seen_time, &time);
    printf("smoke_fd4_step: all tests passed\n");
    return 0;
}
