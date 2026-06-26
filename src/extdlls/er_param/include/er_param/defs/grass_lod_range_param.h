#pragma once

typedef struct er_grass_lod_range_param_s {
    /* LOD0 - 距離
     * LOD 0 - Distance */
    float LOD0_range;

    /* LOD0 - 遊び
     * LOD 0 - Play */
    float LOD0_play;

    /* LOD１ - 距離
     * LOD 1 - Distance */
    float LOD1_range;

    /* LOD１ - 遊び
     * LOD 1 - Play */
    float LOD1_play;

    /* LOD２ - 距離
     * LOD 2 - Distance */
    float LOD2_range;

    /* LOD２ - 遊び
     * LOD 2 - Play */
    float LOD2_play;
} er_grass_lod_range_param_t;
