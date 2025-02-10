#pragma once

typedef struct se_material_convert_param_s {
    /* SE材質ID
     *   SFX材質ID（３桁）からSE材質ID（２桁）への変換
     * SE Material ID
     *   Conversion from SFX material ID (3 digits) to SE material ID (2 digits) */
    unsigned char seMaterialId;

    /* パディング
     *   パディング */
    char pad[3];
} se_material_convert_param_t;
