#pragma once

typedef struct cs_reflection_quality_detail_s {
    /* 反射有効
     *   反射有効
     * Reflection Enabled
     *   Reflective effective
     * Default Value  = 1 */
    unsigned char enabled;

    /* ローカルライト有効
     *   ローカルライト有効
     * Local Light Enabled
     *   Local light enabled
     * Default Value  = 1 */
    unsigned char localLightEnabled;

    /* ローカルライト強制有効
     *   ローカルライト強制有効
     * Local Light Forced Enabled
     *   Local light forced enable */
    unsigned char localLightForceEnabled;

    char dmy[1];

    /* 解像度スケール
     *   解像度スケール
     * Resolution Scale
     *   Resolution scale
     * Default Value  = 2 */
    unsigned int resolutionDivider;

    /* SSR有効
     *   SSR有効
     * SSR Enabled
     *   SSR enabled
     * Default Value  = 1 */
    unsigned char ssrEnabled;

    /* ガウスぼかしの許可
     *   ガウスぼかしの許可
     * Gaussian Blur Enabled
     *   Gaussian blur permission
     * Default Value  = 1 */
    unsigned char ssrGaussianBlurEnabled;

    /* dmy */
    char dmy2[2];

    /* 計算距離スケール
     *   計算距離スケール
     * Calculated Distance Scale
     *   Calculated distance scale
     * Default Value  = 1 */
    float ssrDepthRejectThresholdScale;

    /* レイトレースステップ係数（SSRパラメータに乗算）
     *   レイトレースステップ係数（SSRパラメータに乗算）
     * Raytrace Step Scale
     *   Raytrace step factor (multiply by SSR parameter)
     * Default Value  = 1 */
    float ssrRayTraceStepScale;

    /* フェード角度バイアス。小さくすると高品質
     *   フェード角度バイアス。小さくすると高品質
     * Fade Angle Bias
     *   Fade angle bias. High quality when made smaller */
    float ssrFadeToViewerBias;

    /* フレネルリジェクトバイアス。小さくすると高品質
     *   フレネルリジェクトバイアス。小さくすると高品質
     * Fresnel Reject Bias
     *   Fresnel reject bias. High quality when made smaller */
    float ssrFresnelRejectBias;
} cs_reflection_quality_detail_t;
