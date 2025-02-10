#pragma once

/* Dynamic instanced assets, combined with a flat or billboard texture. Used to generate scattered grass or other such arrangements without the need for manual placement. */
typedef struct grass_type_param_s {
    /* LOD距離
     * LOD Distance */
    unsigned short lodRange;

    /* LOD0のクラスタータイプ
     * LOD 0 - Cluster Type */
    unsigned char lod0ClusterType;

    /* LOD1のクラスタータイプ
     * LOD 1 - Cluster Type */
    unsigned char lod1ClusterType;

    /* LOD2のクラスタータイプ
     * LOD 2 - Cluster Type */
    unsigned char lod2ClusterType;

    char pad0[2];

    /* 配置方法
     * Placement Method */
    unsigned char distributionType;

    /* 基本密度
     * Base Density
     * Default Value  = 1 */
    float baseDensity;

    /* モデル名（０）
     * Model Name [0] */
    wchar_t model0Name[16];

    /* フラットテクスチャー名
     * Flat Texture Name */
    wchar_t flatTextureName[32];

    /* ビルボードのテクスチャー名
     * Billboard Texture Name */
    wchar_t billboardTextureName[32];

    /* 傾きの影響（％）
     * Effect of Tilt % */
    unsigned char normalInfluence;

    /* 傾きの最大角度（度）
     * Maximum Tilt Angle
     * Default Value  = 90 */
    unsigned char inclinationMax;

    /* 傾斜角のランダム性（度）
     * Randomness of Tilt Angle */
    unsigned char inclinationJitter;

    /* 幅のスケール範囲(min，％)
     * Width Scale - Min
     * Default Value  = 100 */
    unsigned char scaleBaseMin;

    /* 幅のスケール範囲(max，％)
     * Width Scale - Max
     * Default Value  = 100 */
    unsigned char scaleBaseMax;

    /* 高さのスケール範囲(min，％)
     * Height Scale - Min
     * Default Value  = 100 */
    unsigned char scaleHeightMin;

    /* 高さのスケール範囲(max，％)
     * Height Scale - Max
     * Default Value  = 100 */
    unsigned char scaleHeightMax;

    /* 乗算カラー１ (赤）
     * Color Shade [1] R
     * Default Value  = 255 */
    unsigned char colorShade1_r;

    /* 乗算カラー１ （緑）
     * Color Shade [1] G
     * Default Value  = 255 */
    unsigned char colorShade1_g;

    /* 乗算カラー １（青）
     * Color Shade [1] B
     * Default Value  = 255 */
    unsigned char colorShade1_b;

    /* 乗算カラー２ （赤）
     * Color Shade [2] R
     * Default Value  = 255 */
    unsigned char colorShade2_r;

    /* 乗算カラー２ （緑）
     * Color Shade [2] G
     * Default Value  = 255 */
    unsigned char colorShade2_g;

    /* 乗算カラー ２（青）
     * Color Shade [2] B
     * Default Value  = 255 */
    unsigned char colorShade2_b;

    /* 平面の分離
     * Plane Split Type */
    unsigned char flatSplitType;

    /* 平面の枚数
     * Number of Planes
     * Default Value  = 2 */
    unsigned char flatBladeCount;

    /* 平面の角度（度）
     * Plane Angle */
    char flatSlant;

    /* 平面の距離
     * Plane Distance */
    float flatRadius;

    /* 影を落とすか
     * Cast Shadow
     * Default Value  = 1 */
    unsigned char castShadow;

    /* 振幅(揺れの大きさ)
     * Wind Amplitude
     * Default Value  = 80 */
    unsigned char windAmplitude;

    char pad1[1];

    /* 周期(速度)
     * Wind Speed
     * Default Value  = 40 */
    unsigned char windCycle;

    /* 方向（度）
     *   -1の場合はランダム
     * Direction
     *   Random for -1
     * Default Value  = -1 */
    float orientationAngle;

    /* 方向の範囲（度）
     * Direction Range
     * Default Value  = -1 */
    float orientationRange;

    /* モデル間隔
     * Model Spacing */
    float spacing;

    /* ディザリング
     * Dithering */
    unsigned char dithering;

    /* pad2 */
    char pad[3];

    /* Simpleモデル名
     * Simple Model Name */
    wchar_t simpleModelName[16];

    /* モデル名（１）
     * Model Name [1] */
    wchar_t model1Name[16];
} grass_type_param_t;
