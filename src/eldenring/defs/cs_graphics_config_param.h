#pragma once

typedef struct cs_graphics_config_param_s {
    /* テクスチャフィルタ品質
     *   テクスチャフィルタ品質(デフォルトMidele)
     * Texture Filter Quality
     *   Texture filter quality (default Midele)
     * Default Value  = 2 */
    unsigned char m_textureFilterQuality;

    /* AA品質
     *   AA品質(デフォルトHigh)
     * AA Quality
     *   AA quality (default High)
     * Default Value  = 3 */
    unsigned char m_aaQuality;

    /* SSAO品質
     *   SSAO品質(デフォルトHigh)
     * SSAO Quality
     *   SSAO quality (default High)
     * Default Value  = 3 */
    unsigned char m_ssaoQuality;

    /* 被写界深度品質
     *   被写界深度品質(デフォルトHigh)
     * Depth of Field Quality
     *   Depth of field quality (default High)
     * Default Value  = 3 */
    unsigned char m_dofQuality;

    /* モーションブラー品質
     *   モーションブラー品質(デフォルトHigh)
     * Motion Blur Quality
     *   Motion blur quality (default High)
     * Default Value  = 3 */
    unsigned char m_motionBlurQuality;

    /* シャドウ品質
     *   シャドウ品質(デフォルトHigh)
     * Shadow Quality
     *   Shadow quality (default High)
     * Default Value  = 3 */
    unsigned char m_shadowQuality;

    /* ライティング品質
     *   ライティング品質(デフォルトHigh)
     * Lighting Quality
     *   Lighting quality (default High)
     * Default Value  = 3 */
    unsigned char m_lightingQuality;

    /* エフェクト品質
     *   エフェクト品質(デフォルトHigh)
     * Effect Quality
     *   Effect quality (default High)
     * Default Value  = 3 */
    unsigned char m_effectQuality;

    /* デカール品質
     *   デカール品質(デフォルトHigh)
     * Decal Quality
     *   Decal quality (default High)
     * Default Value  = 3 */
    unsigned char m_decalQuality;

    /* 反射品質
     *   反射品質(デフォルトHigh)
     * Reflection Quality
     *   Reflection quality (default High)
     * Default Value  = 3 */
    unsigned char m_reflectionQuality;

    /* ウォーター品質
     *   ウォーター品質(デフォルトHigh)
     * Water Quality
     *   Water quality (default High)
     * Default Value  = 3 */
    unsigned char m_waterQuality;

    /* シェーダー品質
     *   シェーダー品質(デフォルトHigh)
     * Shader Quality
     *   Shader quality (default High)
     * Default Value  = 3 */
    unsigned char m_shaderQuality;

    /* ボリューメトリック効果品質
     *   ボリューメトリック効果品質(デフォルトHigh)
     * Volumetric Effect Quality
     *   Volumetric effect quality (default High)
     * Default Value  = 3 */
    unsigned char m_volumetricEffectQuality;

    /* Raytracing Quality
     *   Raytracing quality (default High) */
    unsigned char m_RayTracingQuality;

    /* dmy */
    char m_dummy[2];
} cs_graphics_config_param_t;
