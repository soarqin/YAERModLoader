#include "xxhash.h"

#include <string.h>

#if defined(_MSC_VER)
#include <intrin.h>
#else
static uint64_t portable_mul128_low(uint64_t left, uint64_t right, uint64_t *high) {
    uint64_t left_low = (uint32_t)left;
    uint64_t left_high = left >> 32;
    uint64_t right_low = (uint32_t)right;
    uint64_t right_high = right >> 32;
    uint64_t low_low = left_low * right_low;
    uint64_t high_low = left_high * right_low;
    uint64_t low_high = left_low * right_high;
    uint64_t cross = (low_low >> 32) + (uint32_t)high_low + low_high;
    *high = left_high * right_high + (high_low >> 32) + (cross >> 32);
    return (cross << 32) | (uint32_t)low_low;
}

static uint64_t byte_swap64(uint64_t value) {
    return ((value & UINT64_C(0x00000000000000ff)) << 56) |
           ((value & UINT64_C(0x000000000000ff00)) << 40) |
           ((value & UINT64_C(0x0000000000ff0000)) << 24) |
           ((value & UINT64_C(0x00000000ff000000)) << 8) |
           ((value & UINT64_C(0x000000ff00000000)) >> 8) |
           ((value & UINT64_C(0x0000ff0000000000)) >> 24) |
           ((value & UINT64_C(0x00ff000000000000)) >> 40) |
           ((value & UINT64_C(0xff00000000000000)) >> 56);
}

static uint32_t byte_swap32(uint32_t value) {
    return ((value & UINT32_C(0x000000ff)) << 24) |
           ((value & UINT32_C(0x0000ff00)) << 8) |
           ((value & UINT32_C(0x00ff0000)) >> 8) |
           ((value & UINT32_C(0xff000000)) >> 24);
}

#endif

static uint32_t rotate_left32(uint32_t value, unsigned count) {
    return (value << count) | (value >> (32 - count));
}

#define PRIME32_1 UINT64_C(0x9E3779B1)
#define PRIME32_2 UINT64_C(0x85EBCA77)
#define PRIME32_3 UINT64_C(0xC2B2AE3D)
#define PRIME64_1 UINT64_C(0x9E3779B185EBCA87)
#define PRIME64_2 UINT64_C(0xC2B2AE3D27D4EB4F)
#define PRIME64_3 UINT64_C(0x165667B19E3779F9)
#define PRIME64_4 UINT64_C(0x85EBCA77C2B2AE63)
#define PRIME64_5 UINT64_C(0x27D4EB2F165667C5)
#define SECRET_SIZE 192
#define SECRET_SIZE_MIN 136
#define STRIPE_LEN 64
#define SECRET_CONSUME_RATE 8
#define SECRET_LASTACC_START 7
#define SECRET_MERGEACCS_START 11

static const uint8_t default_secret[SECRET_SIZE] = {
    0xb8,0xfe,0x6c,0x39,0x23,0xa4,0x4b,0xbe,0x7c,0x01,0x81,0x2c,0xf7,0x21,0xad,0x1c,
    0xde,0xd4,0x6d,0xe9,0x83,0x90,0x97,0xdb,0x72,0x40,0xa4,0xa4,0xb7,0xb3,0x67,0x1f,
    0xcb,0x79,0xe6,0x4e,0xcc,0xc0,0xe5,0x78,0x82,0x5a,0xd0,0x7d,0xcc,0xff,0x72,0x21,
    0xb8,0x08,0x46,0x74,0xf7,0x43,0x24,0x8e,0xe0,0x35,0x90,0xe6,0x81,0x3a,0x26,0x4c,
    0x3c,0x28,0x52,0xbb,0x91,0xc3,0x00,0xcb,0x88,0xd0,0x65,0x8b,0x1b,0x53,0x2e,0xa3,
    0x71,0x64,0x48,0x97,0xa2,0x0d,0xf9,0x4e,0x38,0x19,0xef,0x46,0xa9,0xde,0xac,0xd8,
    0xa8,0xfa,0x76,0x3f,0xe3,0x9c,0x34,0x3f,0xf9,0xdc,0xbb,0xc7,0xc7,0x0b,0x4f,0x1d,
    0x8a,0x51,0xe0,0x4b,0xcd,0xb4,0x59,0x31,0xc8,0x9f,0x7e,0xc9,0xd9,0x78,0x73,0x64,
    0xea,0xc5,0xac,0x83,0x34,0xd3,0xeb,0xc3,0xc5,0x81,0xa0,0xff,0xfa,0x13,0x63,0xeb,
    0x17,0x0d,0xdd,0x51,0xb7,0xf0,0xda,0x49,0xd3,0x16,0x55,0x26,0x29,0xd4,0x68,0x9e,
    0x2b,0x16,0xbe,0x58,0x7d,0x47,0xa1,0xfc,0x8f,0xf8,0xb8,0xd1,0x7a,0xd0,0x31,0xce,
    0x45,0xcb,0x3a,0x8f,0x95,0x16,0x04,0x28,0xaf,0xd7,0xfb,0xca,0xbb,0x4b,0x40,0x7e,
};

static uint32_t r32(const uint8_t *p) {
    uint32_t value;
    memcpy(&value, p, sizeof(value));
    return value;
}

static uint64_t r64(const uint8_t *p) {
    uint64_t value;
    memcpy(&value, p, sizeof(value));
    return value;
}

static void w64(uint8_t *p, uint64_t value) {
    memcpy(p, &value, sizeof(value));
}

static uint64_t avalanche(uint64_t value) {
    value ^= value >> 37;
    value *= UINT64_C(0x165667919E3779F9);
    return value ^ (value >> 32);
}

static uint64_t xxh64_avalanche(uint64_t value) {
    value ^= value >> 33;
    value *= PRIME64_2;
    value ^= value >> 29;
    value *= PRIME64_3;
    return value ^ (value >> 32);
}

static XXH128_hash_t mul128(uint64_t left, uint64_t right) {
    XXH128_hash_t result;
#if defined(_MSC_VER)
    result.low64 = _umul128(left, right, &result.high64);
#else
    result.low64 = portable_mul128_low(left, right, &result.high64);
#endif
    return result;
}

static uint64_t fold(uint64_t left, uint64_t right) {
    XXH128_hash_t product = mul128(left, right);
    return product.low64 ^ product.high64;
}

static uint64_t mix16(const uint8_t *input, const uint8_t *secret, uint64_t seed) {
    return fold(r64(input) ^ (r64(secret) + seed),
                r64(input + 8) ^ (r64(secret + 8) - seed));
}

static XXH128_hash_t hash_0_16(const uint8_t *p, size_t len, uint64_t seed) {
    XXH128_hash_t out;
    if (len > 8) {
        uint64_t input_lo = r64(p);
        uint64_t input_hi = r64(p + len - 8);
        uint64_t bitflip_lo = (r64(default_secret + 32) ^ r64(default_secret + 40)) - seed;
        uint64_t bitflip_hi = (r64(default_secret + 48) ^ r64(default_secret + 56)) + seed;
        XXH128_hash_t mixed = mul128(input_lo ^ input_hi ^ bitflip_lo, PRIME64_1);
        mixed.low64 += (len - 1) << 54;
        input_hi ^= bitflip_hi;
        mixed.high64 += input_hi + (uint64_t)(uint32_t)input_hi * (PRIME32_2 - 1);
#if defined(_MSC_VER)
        mixed.low64 ^= _byteswap_uint64(mixed.high64);
#else
        mixed.low64 ^= byte_swap64(mixed.high64);
#endif
        out = mul128(mixed.low64, PRIME64_2);
        out.high64 += mixed.high64 * PRIME64_2;
        out.low64 = avalanche(out.low64);
        out.high64 = avalanche(out.high64);
    } else if (len >= 4) {
        uint64_t adjusted_seed = seed ^ ((uint64_t)
#if defined(_MSC_VER)
            _byteswap_ulong((uint32_t)seed)
#else
            byte_swap32((uint32_t)seed)
#endif
            << 32);
        uint64_t input = r32(p) + ((uint64_t)r32(p + len - 4) << 32);
        uint64_t bitflip = (r64(default_secret + 16) ^ r64(default_secret + 24)) + adjusted_seed;
        out = mul128(input ^ bitflip, PRIME64_1 + (len << 2));
        out.high64 += out.low64 << 1;
        out.low64 ^= out.high64 >> 3;
        out.low64 = (out.low64 ^ (out.low64 >> 35)) * UINT64_C(0x9FB21C651E98DF25);
        out.low64 ^= out.low64 >> 28;
        out.high64 = avalanche(out.high64);
    } else if (len != 0) {
        uint32_t combined_lo = ((uint32_t)p[0] << 16) | ((uint32_t)p[len >> 1] << 24) |
                               p[len - 1] | ((uint32_t)len << 8);
        uint32_t combined_hi = rotate_left32(
#if defined(_MSC_VER)
            _byteswap_ulong(combined_lo),
#else
            byte_swap32(combined_lo),
#endif
            13);
        uint64_t bitflip_lo = (r32(default_secret) ^ r32(default_secret + 4)) + seed;
        uint64_t bitflip_hi = (r32(default_secret + 8) ^ r32(default_secret + 12)) - seed;
        out.low64 = xxh64_avalanche((uint64_t)combined_lo ^ bitflip_lo);
        out.high64 = xxh64_avalanche((uint64_t)combined_hi ^ bitflip_hi);
    } else {
        out.low64 = xxh64_avalanche(seed ^ r64(default_secret + 64) ^ r64(default_secret + 72));
        out.high64 = xxh64_avalanche(seed ^ r64(default_secret + 80) ^ r64(default_secret + 88));
    }
    return out;
}

static XXH128_hash_t mix32(XXH128_hash_t acc, const uint8_t *input1, const uint8_t *input2,
                           const uint8_t *secret, uint64_t seed) {
    acc.low64 += mix16(input1, secret, seed);
    acc.low64 ^= r64(input2) + r64(input2 + 8);
    acc.high64 += mix16(input2, secret + 16, seed);
    acc.high64 ^= r64(input1) + r64(input1 + 8);
    return acc;
}

static XXH128_hash_t finalize_mid(XXH128_hash_t acc, size_t len, uint64_t seed) {
    XXH128_hash_t out;
    out.low64 = avalanche(acc.low64 + acc.high64);
    out.high64 = (uint64_t)0 - avalanche(acc.low64 * PRIME64_1 + acc.high64 * PRIME64_4 +
                                        (len - seed) * PRIME64_2);
    return out;
}

static XXH128_hash_t hash_17_128(const uint8_t *p, size_t len, uint64_t seed) {
    XXH128_hash_t acc = { len * PRIME64_1, 0 };
    if (len > 32) {
        if (len > 64) {
            if (len > 96) acc = mix32(acc, p + 48, p + len - 64, default_secret + 96, seed);
            acc = mix32(acc, p + 32, p + len - 48, default_secret + 64, seed);
        }
        acc = mix32(acc, p + 16, p + len - 32, default_secret + 32, seed);
    }
    acc = mix32(acc, p, p + len - 16, default_secret, seed);
    return finalize_mid(acc, len, seed);
}

static XXH128_hash_t hash_129_240(const uint8_t *p, size_t len, uint64_t seed) {
    XXH128_hash_t acc = { len * PRIME64_1, 0 };
    unsigned int i;
    for (i = 32; i < 160; i += 32) {
        acc = mix32(acc, p + i - 32, p + i - 16, default_secret + i - 32, seed);
    }
    acc.low64 = avalanche(acc.low64);
    acc.high64 = avalanche(acc.high64);
    for (i = 160; i <= len; i += 32) {
        acc = mix32(acc, p + i - 32, p + i - 16, default_secret + 3 + i - 160, seed);
    }
    acc = mix32(acc, p + len - 16, p + len - 32,
                default_secret + SECRET_SIZE_MIN - 17 - 16, (uint64_t)0 - seed);
    return finalize_mid(acc, len, seed);
}

static void custom_secret(uint8_t *secret, uint64_t seed) {
    for (size_t i = 0; i < SECRET_SIZE; i += 16) {
        w64(secret + i, r64(default_secret + i) + seed);
        w64(secret + i + 8, r64(default_secret + i + 8) - seed);
    }
}

static void accumulate_stripe(uint64_t acc[8], const uint8_t *p, const uint8_t *secret) {
    for (size_t i = 0; i < 8; i++) {
        uint64_t data = r64(p + i * 8);
        uint64_t key = data ^ r64(secret + i * 8);
        acc[i ^ 1] += data;
        acc[i] += (uint64_t)(uint32_t)key * (uint32_t)(key >> 32);
    }
}

static void accumulate(uint64_t acc[8], const uint8_t *p, const uint8_t *secret, size_t stripes) {
    for (size_t i = 0; i < stripes; i++) {
        accumulate_stripe(acc, p + i * STRIPE_LEN, secret + i * SECRET_CONSUME_RATE);
    }
}

static void scramble(uint64_t acc[8], const uint8_t *secret) {
    for (size_t i = 0; i < 8; i++) {
        uint64_t value = acc[i] ^ (acc[i] >> 47) ^ r64(secret + i * 8);
        acc[i] = value * PRIME32_1;
    }
}

static uint64_t merge_accs(const uint64_t acc[8], const uint8_t *secret, uint64_t start) {
    uint64_t result = start;
    for (size_t i = 0; i < 4; i++) {
        result += fold(acc[i * 2] ^ r64(secret + i * 16),
                       acc[i * 2 + 1] ^ r64(secret + i * 16 + 8));
    }
    return avalanche(result);
}

static XXH128_hash_t hash_long(const uint8_t *p, size_t len, uint64_t seed) {
    uint8_t secret[SECRET_SIZE];
    uint64_t acc[8] = {
        PRIME32_3, PRIME64_1, PRIME64_2, PRIME64_3,
        PRIME64_4, PRIME32_2, PRIME64_5, PRIME32_1
    };
    size_t stripes_per_block = (SECRET_SIZE - STRIPE_LEN) / SECRET_CONSUME_RATE;
    size_t block_len = STRIPE_LEN * stripes_per_block;
    size_t blocks = (len - 1) / block_len;
    size_t stripes;
    custom_secret(secret, seed);
    for (size_t i = 0; i < blocks; i++) {
        accumulate(acc, p + i * block_len, secret, stripes_per_block);
        scramble(acc, secret + SECRET_SIZE - STRIPE_LEN);
    }
    stripes = ((len - 1) - block_len * blocks) / STRIPE_LEN;
    accumulate(acc, p + blocks * block_len, secret, stripes);
    accumulate_stripe(acc, p + len - STRIPE_LEN,
                      secret + SECRET_SIZE - STRIPE_LEN - SECRET_LASTACC_START);
    {
        XXH128_hash_t out;
        out.low64 = merge_accs(acc, secret + SECRET_MERGEACCS_START, len * PRIME64_1);
        out.high64 = merge_accs(acc, secret + SECRET_SIZE - STRIPE_LEN - SECRET_MERGEACCS_START,
                                ~(len * PRIME64_2));
        return out;
    }
}

XXH128_hash_t XXH3_128bits_withSeed(const void *input, size_t len, uint64_t seed) {
    const uint8_t *p = input;
    if (len <= 16) return hash_0_16(p, len, seed);
    if (len <= 128) return hash_17_128(p, len, seed);
    if (len <= 240) return hash_129_240(p, len, seed);
    return hash_long(p, len, seed);
}
