#pragma once

typedef struct er_cs_lighting_quality_detail_s {
    /* ローカルライト有効距離係数
     *   ローカルライト有効距離係数(小さくすると、近い距離で消える)
     * Local Light Distance Factor
     *   Local light effective distance coefficient (smaller, it disappears at a short distance)
     * Default Value  = 0.75 */
    float localLightDistFactor;

    /* ローカルライトシャドウ有効
     *   ローカルライトシャドウ有効
     * Local Light Shadow Enabled
     *   Local light shadow enabled
     * Default Value  = 1 */
    unsigned char localLightShadowEnabled;

    /* フォワードパスライティング有効
     *   フォワードパスライティング有効
     * Forward Pass Write Enabled
     *   Forward pass writing enabled
     * Default Value  = 1 */
    unsigned char forwardPassLightingEnabled;

    /* ローカルライトシャドウスペックレベル
     *   ローカルライトシャドウスペックレベル。大きいほど、より多くの光源にシャドウが設定される
     * Local Light Shadow Specular Level
     *   Local light shadow spec level. The larger the value, the more light sources will be shadowed.
     * Default Value  = 1 */
    unsigned char localLightShadowSpecLevelMax;

    char dmy[1];
} er_cs_lighting_quality_detail_t;
