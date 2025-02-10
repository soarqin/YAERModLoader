#pragma once

typedef struct cs_water_quality_detail_s {
    /* インタラクション有効
     *   インタラクション有効
     * Interaction Enabled
     *   Interaction enabled
     * Default Value  = 1 */
    unsigned char interactionEnabled;

    char dmy[3];
} cs_water_quality_detail_t;
