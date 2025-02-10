#pragma once

typedef struct load_balancer_param_s {
    /* Lower FPS Threshold - Raise Balance Level
     *   If it falls below this FPS, increase the load balance level by 1.
     * Default Value  = 23 */
    float lowerFpsThreshold;

    /* Upper FPS Threshold - Lower Balance Level
     *   If you exceed this FPS, lower the load balance level by 1.
     * Default Value  = 27 */
    float upperFpsThreshold;

    /* Lower FPS Continous - Raise Balance Level
     *   If this frame continues below the threshold, level up
     * Default Value  = 5 */
    unsigned int lowerFpsContinousCount;

    /* Upper FPS Continous - Lower Balance Level
     *   If the threshold is exceeded continuously for this frame, level down
     * Default Value  = 20 */
    unsigned int upperFpsContinousCount;

    /* Sleep Frame Count after Level Lower
     *   Sleep frame count after level down
     * Default Value  = 30 */
    unsigned int downAfterChangeSleep;

    /* Sleep Frame Count after Level Raise
     *   Sleep frame count after leveling up
     * Default Value  = 10 */
    unsigned int upAfterChangeSleep;

    /* ライトシャフト
     *   フィルタのライトシャフト
     * Post Process Light Shaft
     *   Light shaft of filter
     * Default Value  = 20 */
    unsigned char postProcessLightShaft;

    /* Bloom
     *   ブルーム
     * Post Process Bloom
     *   Bloom
     * Default Value  = 20 */
    unsigned char postProcessBloom;

    /* Glow
     *   グロー
     * Post Process Glow
     *   Glow
     * Default Value  = 20 */
    unsigned char postProcessGlow;

    /* AA
     *   アンチエイリアス
     * Post Process Anti-Aliasing
     *   Antialiasing
     * Default Value  = 20 */
    unsigned char postProcessAA;

    /* SSAO
     *   SSAO
     * Post Process SSAO
     *   SSAO
     * Default Value  = 20 */
    unsigned char postProcessSSAO;

    /* DOF
     *   DOF
     * Post Process Depth of Field
     *   DOF
     * Default Value  = 20 */
    unsigned char postProcessDOF;

    /* MotionBlur
     *   MotionBlur
     * Post Process Motion Blur
     *   Motion Blur
     * Default Value  = 20 */
    unsigned char postProcessMotionBlur;

    /* MotionBlurIteration
     *   MotionBlurのイテレーション回数を下げる
     * Post Process Motion Blur Iteration
     *   Reduce the number of Motion Blur iterations
     * Default Value  = 20 */
    unsigned char postProcessMotionBlurIteration;

    /* 予備
     *   予備 */
    char reserve0[1];

    /* Shadow Blur
     *   影のブラーを切る
     * Cut Shadow Blur
     *   Cut the shadow blur
     * Default Value  = 20 */
    unsigned char shadowBlur;

    /* SFXのエミット回り
     *   エミット間隔、エミット数、LOD距離をグラフィックスコンフィグの半分に
     * Halve SFX Particle
     *   Emit interval, number of emits, LOD distance halved in graphics config
     * Default Value  = 20 */
    unsigned char sfxParticleHalf;

    /* SFXの反射
     *   反射シーンSFXをオミット
     * Omit SFX Reflection
     *   Omit the reflection scene SFX
     * Default Value  = 20 */
    unsigned char sfxReflection;

    /* 水面インタラクション
     *   水面インタラクトSFXをオミット
     * Omit Water Surface SFX Interaction
     *   Omit water surface interact SFX
     * Default Value  = 20 */
    unsigned char sfxWaterInteraction;

    /* SFXのグロー
     *   SFXでかけてるGlowをオミット
     * Omit SFX Glow
     *   Omit Glow playing with SFX
     * Default Value  = 20 */
    unsigned char sfxGlow;

    /* SFXの歪み
     *   SFXでかけてる歪みのオミット
     * Omit SFX Distortion
     *   Omit of distortion applied by SFX
     * Default Value  = 20 */
    unsigned char sfxDistortion;

    /* ソフトスプライト
     *   SFXでかけてるソフトスプライトのオミット
     * Omit SFX Soft Sprite
     *   Soft sprite omit with SFX
     * Default Value  = 20 */
    unsigned char sftSoftSprite;

    /* ライトシャフト
     *   SFXのライトシャフトのオミット
     * Omit SFX Light Shaft
     *   SFX Light Shaft Omit
     * Default Value  = 20 */
    unsigned char sfxLightShaft;

    /* 動的に縮小バッファに登録されるエフェクトの距離判定にスケール
     *   SFXの距離で動的に縮小バッファに登録されるエフェクトの距離判定にスケール
     * SFX Scale - Render Distance Scale
     *   Scale to the distance judgment of the effect dynamically registered in the reduction buffer by the distance of SFX
     * Default Value  = 20 */
    unsigned char sfxScaleRenderDistanceScale;

    /* 動的解像度
     *   動的解像度
     * Dynamic Resolution
     *   Dynamic resolution
     * Default Value  = 1 */
    unsigned char dynamicResolution;

    /* Shadow Cascade0 ResolutionHalf
     *   影（カスケード0）の解像度を半分に下げる
     * Halve Shadow Cascade [0] Resolution
     *   Cut the shadow (cascade 0) resolution in half */
    unsigned char shadowCascade0ResolutionHalf;

    /* Shadow Cascade1 ResolutionHalf
     *   影（カスケード1）の解像度を半分に下げる
     * Halve Shadow Cascade [1] Resolution
     *   Cut the shadow (cascade 1) resolution in half
     * Default Value  = 13 */
    unsigned char shadowCascade1ResolutionHalf;

    /* ローカルプレイヤー
     *   ローカルプレイヤーの水濡れ処理を切る
     * Disable Wetness for Player
     *   Turn off the water wetting process for local players
     * Default Value  = 21 */
    unsigned char chrWetDisablePlayer;

    /* リモートプレイヤー
     *   リモートプレイヤーの水濡れ処理を切る
     * Disable Wetness for Remote Player
     *   Turn off the water wetting process of the remote player
     * Default Value  = 21 */
    unsigned char chrWetDisableRemotePlayer;

    /* 敵キャラ
     *   敵キャラの水濡れ処理を切る
     * Disable Wetness for NPC
     *   Turn off the water wetting process of enemy characters
     * Default Value  = 21 */
    unsigned char chrWetDisableEnemy;

    /* 解像度引き下げ 下限(%)
     *   解像度引き下げ 下限(%)
     * Lower Limit of Resolution Reduction
     *   Resolution reduction lower limit (%)
     * Default Value  = 100 */
    unsigned char dynamicResolutionPercentageMin;

    /* 解像度引き下げ 上限(%)
     *   解像度引き下げ 上限(%)
     * Upper Limit of Resolution Reduction
     *   Resolution reduction upper limit (%)
     * Default Value  = 100 */
    unsigned char dynamicResolutionPercentageMax;

    /* 予備
     *   予備 */
    char reserve1[30];
} load_balancer_param_t;
