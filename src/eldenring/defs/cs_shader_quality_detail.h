#pragma once

typedef struct er_cs_shader_quality_detail_s {
    /* SSS有効
     *   SSS有効
     * SSS Enabled
     *   SSS enabled
     * Default Value  = 1 */
    unsigned char sssEnabled;

    /* テッセレーション有効
     *   テッセレーション有効
     * Tessellation Enabled
     *   Tessellation enabled */
    unsigned char tessellationEnabled;

    /* 高精度ノーマル有効
     *   高精度ノーマル有効(G-Bufferに格納する法線の精度の設定)
     * High Precision Normal Enabled
     *   High precision normal valid (setting the accuracy of the normal stored in G-Buffer) */
    unsigned char highPrecisionNormalEnabled;

    /* dmy */
    char dmy[1];
} er_cs_shader_quality_detail_t;
