#pragma once

typedef struct cs_volumetric_effect_quality_detail_s {
    /* フォグ有効
     *   フォグ有効
     * Fog Enabled
     *   Fog enabled
     * Default Value  = 1 */
    unsigned char fogEnabled;

    /* フォグシャドウ許可
     *   フォグシャドウ許可
     * Fog Shadow Enabled
     *   Fog shadow permission
     * Default Value  = 1 */
    unsigned char fogShadowEnabled;

    char dmy[2];

    /* シャドウのサンプルカウントオフセット。
     *   シャドウのサンプルカウントオフセット。
     * Shadow Sample Count Offset
     *   Shadow sample count offset. */
    int fogShadowSampleCountBias;

    /* ローカルライト計算距離スケール (0にするとローカルライト計算をしない)
     *   ローカルライト計算距離スケール (0にするとローカルライト計算をしない)
     * Local Light Distance Scale
     *   Local light calculation distance scale (0 does not calculate local light) */
    float fogLocalLightDistScale;

    /* フォグボリュームサイズスケーラ
     *   フォグボリュームサイズスケーラ
     * Fog Volume Size Scaler
     *   Fog volume size scaler
     * Default Value  = 1 */
    unsigned int fogVolueSizeScaler;

    /* フォグボリュームサイズ除算
     *   フォグボリュームサイズ除算
     * Fog Volume Size Division
     *   Fog volume size division
     * Default Value  = 1 */
    unsigned int fogVolueSizeDivider;

    /* フォグボリューム奥行きスライススケーラ
     *   フォグボリューム奥行きスライススケーラ
     * Fog Volume Depth Slice Scaler
     *   Fog Volume Depth Slice Scaler
     * Default Value  = 1 */
    unsigned int fogVolumeDepthScaler;

    /* フォグボリューム奥行きスライス除算
     *   フォグボリューム奥行きスライス除算
     * Fog Volume Depth Slice Division
     *   Fog volume depth slice division
     * Default Value  = 1 */
    unsigned int fogVolumeDepthDivider;

    /* 配置式フォグボリューム有効
     *   配置式フォグボリューム有効
     * Arranged Fog Volume Enabled
     *   Arranged fog volume enabled
     * Default Value  = 1 */
    unsigned char fogVolumeEnabled;

    /* アップスケール種別
     *   アップスケール時の手法種別
     * Upscale Type
     *   Method type at the time of upscale
     * Default Value  = 1 */
    unsigned char fogVolumeUpScaleType;

    /* バイラテラル時のみ行われるエッジ補正レベル
     *   バイラテラル時のみ行われるエッジ補正レベル(0:無効,1:1/2x1/2解像度でのエッジ再描画許可,2:1/2x1/2+1x1解像度でパラメータ削減ありのエッジ再描画許可,3:1/2x1/2+1x1解像度でのエッジ再描画許可)
     * Edge Correction Level
     *   Edge correction level performed only at bilateral (0- invalid, edge redraw permission at 1- 1 / 2x1 / 2 resolution, edge redraw permission with parameter reduction at 2- 1 / 2x1 / 2 + 1x1 resolution, 3 - 1 / 2x1 / 2 + 1x1 resolution edge redraw permission)
     * Default Value  = 2 */
    unsigned char fogVolumeEdgeCorrectionLevel;

    /* レイマーチング時のサンプリング数のオフセット
     *   レイマーチング時のサンプリング数のオフセット
     * Ray Sample Count Offset
     *   Offset of sampling number during ray marching */
    char fogVolumeRayMarcingSampleCountOffset;

    /* シャドウ許可
     *   シャドウ許可(領域に影が落ちる、領域内の密度変化による陰影処理を指す)
     * Fog Volume Shadow Enabled
     *   Shadow permission (refers to shadow processing due to density changes in the area, where shadows are cast on the area)
     * Default Value  = 1 */
    unsigned char fogVolumeShadowEnabled;

    /* シャドウ許可時に設定にかかわらず領域に強制的に影を落とす
     *   シャドウ許可時に設定にかかわらず領域に強制的に影を落とす(陰影処理は影響をうけない)
     * Fog Volume - Force Shadowing
     *   Forcibly casts a shadow on the area regardless of the setting when shadow is permitted (shadow processing is not affected) */
    unsigned char fogVolumeForceShadowing;

    /* フォグボリュームのアップスケール処理解像度
     * Fog Volume Resolution */
    unsigned char fogVolumeResolution;

    /* pad */
    char pad2[1];
} cs_volumetric_effect_quality_detail_t;
