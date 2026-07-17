#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct xxh128_hash_s {
    uint64_t low64;
    uint64_t high64;
} XXH128_hash_t;

XXH128_hash_t XXH3_128bits_withSeed(const void *input, size_t length, uint64_t seed);
