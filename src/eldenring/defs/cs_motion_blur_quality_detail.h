#pragma once

typedef struct er_cs_motion_blur_quality_detail_s {
    /* モーションブラー有効
     *   モーションブラー有効
     * Default Value  = 1 */
    unsigned char enabled;

    /* OMB(オブジェクトモーションブラー)有効
     *   OMB(オブジェクトモーションブラー)有効
     * Object Motion Blur Enabled
     *   OMB (object motion blur) Enabled
     * Default Value  = 1 */
    unsigned char ombEnabled;

    /* 内部で使用するベロシティバッファの解像度を下げる
     *   内部で使用するベロシティバッファの解像度を下げる。高精度ベロシティバッファを使っていない場合は効果ない
     * Force Scale Velocity Buffer
     *   Decrease the resolution of the velocity buffer used internally. Not effective if you are not using precision velocity buffers
     * Default Value  = 1 */
    unsigned char forceScaleVelocityBuffer;

    /* 通常、Reconstructionフィルタで処理されるが、軽い処理にダウングレードする
     *   通常、Reconstructionフィルタで処理されるが、軽い処理にダウングレードする
     * Cheap Filter Mode
     *   Normally processed by the Reconstruction filter, but downgraded to a lighter process */
    unsigned char cheapFilterMode;

    /* サンプルカウントにオフセットを与える
     *   サンプルカウントにオフセットを与える※2の倍数に設定して下さい
     * Sample Count Bias
     *   Give an offset to the sample count * Set to a multiple of 2
     * Default Value  = -2 */
    int sampleCountBias;

    /* 再帰ブラー回数にオフセットを与える
     *   再帰ブラー回数にオフセットを与える
     * Recurrence Count Bias
     *   Give an offset to the number of recursive blurs */
    int recurrenceCountBias;

    /* ブラー最大長さパラメータに対するスケール値
     *   ブラー最大長さパラメータに対するスケール値
     * Blur Max Length Scale
     *   Scale value for blur maximum length parameter
     * Default Value  = 0.75 */
    float blurMaxLengthScale;
} er_cs_motion_blur_quality_detail_t;
