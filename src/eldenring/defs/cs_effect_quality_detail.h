#pragma once

typedef struct cs_effect_quality_detail_s {
    /* ソフトパーティクル有効
     *   ソフトパーティクル有効
     * Soft Particles Enabled
     *   Soft particles Enabled
     * Default Value  = 1 */
    unsigned char softParticleEnabled;

    /* グロー有効
     *   グロー有効
     * Glow Enabled
     *   Glow effective
     * Default Value  = 1 */
    unsigned char glowEnabled;

    /* 歪み有効
     *   歪み有効
     * Distortion Enabled
     *   Distortion effective
     * Default Value  = 1 */
    unsigned char distortionEnable;

    /* バイラテラルアップスケールを有効
     *   バイラテラルアップスケール有効
     * Enable Bilateral Upscale
     *   Bilateral upscale effective */
    unsigned char cs_upScaleEnabledType;

    /* 一回のエミット数
     *   一回のエミット数
     * Number of Emits in Instance
     *   Number of Emits at one time
     * Default Value  = 0.9 */
    float fNumOnceEmitsScale;

    /* エミット間隔
     *   エミット間隔
     * Emit Interval
     *   Emit interval
     * Default Value  = 1.1 */
    float fEmitSpanScale;

    /* 1段階目のLOD距離スケール
     *   1段階目のLOD距離スケール
     * 1st LOD Distance Scale
     *   1st stage LOD distance scale
     * Default Value  = 0.9 */
    float fLodDistance1Scale;

    /* 2段階目のLOD距離スケール
     *   2段階目のLOD距離スケール
     * 2nd LOD Distance Scale
     *   Second stage LOD distance scale
     * Default Value  = 0.9 */
    float fLodDistance2Scale;

    /* 3段階目のLOD距離スケール
     *   3段階目のLOD距離スケール
     * 3rd LOD Distance Scale
     *   3rd stage LOD distance scale
     * Default Value  = 0.9 */
    float fLodDistance3Scale;

    /* 4段階目のLOD距離スケール
     *   4段階目のLOD距離スケール
     * 4th LOD Distance Scale
     *   4th stage LOD distance scale
     * Default Value  = 0.9 */
    float fLodDistance4Scale;

    /* 縮小バッファへ登録される距離への倍率
     *   縮小バッファへ登録される距離への倍率
     * Scale Render Distance Scale
     *   Magnification to the distance registered in the reduction buffer
     * Default Value  = 1.2 */
    float fScaleRenderDistanceScale;

    /* ダミー */
    char dmy[4];
} cs_effect_quality_detail_t;
