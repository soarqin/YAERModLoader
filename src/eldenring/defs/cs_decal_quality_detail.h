#pragma once

typedef struct cs_decal_quality_detail_s {
    /* デカール有効
     *   デカール有効
     * Decal Enabled
     *   Decal valid
     * Default Value  = 1 */
    unsigned char enabled;

    char dmy[3];
} cs_decal_quality_detail_t;
