#pragma once

typedef struct er_cs_aa_quality_detail_s {
    /* AA有効
     *   AA有効
     * AA Enabled
     *   AA valid */
    unsigned char enabled;

    /* 強制的にFXAA2
     *   強制的にFXAA2
     * Force FXAA2
     *   Force FXAA2 */
    unsigned char forceFXAA2;

    char dmy[2];
} er_cs_aa_quality_detail_t;
