#pragma once

typedef struct er_cs_ssao_quality_detail_s {
    /* SSAO有効
     *   SSAO有効
     * SSAO Enabled
     *   SSAO enabled
     * Default Value  = 1 */
    unsigned char enabled;

    /* リプロジェクション有効
     *   リプロジェクション強制有効の時は、PreventGhostも有効になる
     * Reprojection Enabled
     *   When reprojection is forcibly enabled, Prevent Ghost is also enabled.
     * Default Value  = 1 */
    unsigned char cs_reprojEnabledType;

    /* バイラテラルアップスケール有効
     *   バイラテラルアップスケール有効
     * Bilateral Upscale Enable Type
     *   Bilateral upscale effective */
    unsigned char cs_upScaleEnabledType;

    /* 法線使用有効
     *   法線使用有効
     * Use Normal Enabled Type
     *   Valid to use normals
     * Default Value  = 1 */
    unsigned char cs_useNormalEnabledType;

    char dmy[1];
} er_cs_ssao_quality_detail_t;
