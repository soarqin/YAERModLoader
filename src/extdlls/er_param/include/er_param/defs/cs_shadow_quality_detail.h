#pragma once

typedef struct er_cs_shadow_quality_detail_s {
    /* シャドウが有効
     *   シャドウが有効
     * Shadow Enabled
     *   Shadow is enabled
     * Default Value  = 1 */
    unsigned char enabled;

    /* 許可される最大のフィルタ品質
     *   許可される最大のフィルタ品質
     * Maximum Filter Level
     *   Maximum filter quality allowed
     * Default Value  = 1 */
    unsigned char maxFilterLevel;

    char dmy[2];

    /* 設定されたシャドウマップ解像度のスケーラ
     *   設定されたシャドウマップ解像度のスケーラ
     * Texture Size Scalar
     *   Scaler with set shadow map resolution
     * Default Value  = 1 */
    unsigned int textureSizeScaler;

    /* 設定されたシャドウマップ解像度を除算
     *   設定されたシャドウマップ解像度を除算
     * Texture Size Division
     *   Divide the set shadow map resolution
     * Default Value  = 2 */
    unsigned int textureSizeDivider;

    /* 解像度最小
     *   解像度をクランプ
     * Minimum Resolution
     *   Clamp resolution
     * Default Value  = 128 */
    unsigned int textureMinSize;

    /* 解像度最大
     *   解像度をクランプ。カスケード毎の解像度判定になります
     * Maximum Resolution
     *   Clamp the resolution. It will be the resolution judgment for each cascade
     * Default Value  = 1024 */
    unsigned int textureMaxSize;

    /* ブラーカウントバイアス
     *   ブラーカウントバイアス(設定されたカウントのバイアス。0で変更なし)
     * Blur Count Bias
     *   Blur count bias (set count bias, unchanged at 0)
     * Default Value  = -1 */
    int blurCountBias;
} er_cs_shadow_quality_detail_t;
