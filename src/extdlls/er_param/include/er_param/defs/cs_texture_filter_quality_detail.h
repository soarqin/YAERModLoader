#pragma once

typedef struct er_cs_texture_filter_quality_detail_s {
    /* フィルター
     *   フィルター
     * Texture Filter
     *   filter
     * Default Value  = 3 */
    unsigned char filter;

    char dmy[3];

    /* アニソレベル
     *   アニソレベル
     * Anisotropic Level
     *   Aniso level
     * Default Value  = 4 */
    unsigned int maxAnisoLevel;
} er_cs_texture_filter_quality_detail_t;
