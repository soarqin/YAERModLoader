#pragma once

typedef struct phantom_param_s {
    /* A
     *   エッジ色Aです。
     * Edge Color: Alpha
     *   Edge color A.
     * Default Value  = 1 */
    float edgeColorA;

    /* A
     *   正面色Aです。
     * Front Color: Alpha
     *   The front color is A. */
    float frontColorA;

    /* A
     *   ディフューズ乗算色Aです。
     * Diffuse Color: Alpha
     *   Diffuse multiplication color A.
     * Default Value  = 1 */
    float diffMulColorA;

    /* A
     *   スペキュラ乗算色Aです。
     * Specular Color: Alpha
     *   Specular multiplication color A.
     * Default Value  = 1 */
    float specMulColorA;

    /* A
     *   ライト色Aです。
     * Light Color: Alpha
     *   Light color A. */
    float lightColorA;

    /* R
     *   エッジ色Rです。
     * Edge Color: R
     *   Edge color R.
     * Default Value  = 255 */
    unsigned char edgeColorR;

    /* G
     *   エッジ色Gです。
     * Edge Color: G
     *   Edge color G.
     * Default Value  = 255 */
    unsigned char edgeColorG;

    /* B
     *   エッジ色Bです。
     * Edge Color: B
     *   Edge color B.
     * Default Value  = 255 */
    unsigned char edgeColorB;

    /* R
     *   正面色Rです。
     * Front Color: R
     *   The front color is R. */
    unsigned char frontColorR;

    /* G
     *   正面色Gです。
     * Front Color: G
     *   The front color is G. */
    unsigned char frontColorG;

    /* B
     *   正面色Bです。
     * Front Color: B
     *   Front color B. */
    unsigned char frontColorB;

    /* R
     *   ディフューズ乗算色Rです。
     * Diffuse Color: R
     *   Diffuse multiplication color R.
     * Default Value  = 255 */
    unsigned char diffMulColorR;

    /* G
     *   ディフューズ乗算色Gです。
     * Diffuse Color: G
     *   Diffuse multiplication color G.
     * Default Value  = 255 */
    unsigned char diffMulColorG;

    /* B
     *   ディフューズ乗算色Bです。
     * Diffuse Color: B
     *   Diffuse multiplication color B.
     * Default Value  = 255 */
    unsigned char diffMulColorB;

    /* R
     *   スペキュラ乗算色Rです。
     * Specular Color: R
     *   Specular multiplication color R.
     * Default Value  = 255 */
    unsigned char specMulColorR;

    /* G
     *   スペキュラ乗算色Gです。
     * Specular Color: G
     *   Specular multiplication color G.
     * Default Value  = 255 */
    unsigned char specMulColorG;

    /* B
     *   スペキュラ乗算色Bです。
     * Specular Color: B
     *   Specular multiplication color B.
     * Default Value  = 255 */
    unsigned char specMulColorB;

    /* R
     *   ライト色Rです。
     * Light Color: R
     *   Light color R. */
    unsigned char lightColorR;

    /* G
     *   ライト色Gです。
     * Light Color: G
     *   Light color G. */
    unsigned char lightColorG;

    /* B
     *   ライト色Bです。
     * Light Color: B
     *   Light color B. */
    unsigned char lightColorB;

    /* 予備 */
    char reserve[1];

    /* α
     *   全体の透過度です。
     * Overall Alpha
     *   The overall transparency.
     * Default Value  = 1 */
    float alpha;

    /* ブレンド率
     *   ブレンド率です。
     * Blend Rate
     *   The blend ratio.
     * Default Value  = 1 */
    float blendRate;

    /* α種類
     *   αブレンドの種類です。
     * Blend Type
     *   The type of alpha blend. */
    unsigned char blendType;

    /* エッジ色減算を行うか
     *   エッジ色減算を行うかです。
     * Perform Edge Color Subtraction
     *   Whether to perform edge color subtraction. */
    unsigned char isEdgeSubtract;

    /* 正面色減算を行うか
     *   正面色減算を行うかです。
     * Perform Front Color Subtraction
     *   Is it front color subtraction? */
    unsigned char isFrontSubtract;

    /* 2passを行わない
     *   2passを行わないかです。
     * Is 1 Pass Only
     *   Do you not do 2pass? */
    unsigned char isNo2Pass;

    /* エッジの幅
     *   エッジの幅
     * Edge Width
     *   Edge width
     * Default Value  = 1 */
    float edgePower;

    /* Glowの強さ
     *   Glowの強さ
     * Glow Strength
     *   Glow strength */
    float glowScale;
} phantom_param_t;
