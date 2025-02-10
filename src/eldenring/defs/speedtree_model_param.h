#pragma once

typedef struct speedtree_model_param_s {
    /* Leafの最小フェード値
     * Leaf - Min Fade */
    float MinFadeLeaf;

    /* Frondの最小フェード値
     * Frond - Min Fade */
    float MinFadeFrond;

    /* Branchの最小フェード値
     * Branch - Min Fade */
    float MinFadeBranch;

    /* Leafの透過光最小値
     * Leaf - Min Translucency */
    float MinTranslucencyLeaf;

    /* Leafの透過光最大値
     * Leaf - Max Translucency
     * Default Value  = 5 */
    float MaxTranslucencyLeaf;

    /* Frondの透過光最小値
     * Frond - Min Translucency */
    float MinTranslucencyFrond;

    /* Frondの透過光最大値
     * Frond - Max Translucency
     * Default Value  = 5 */
    float MaxTranslucencyFrond;

    /* Branchの透過光最小値
     * Branch - Min Translucency */
    float MinTranslucencyBranch;

    /* Branchの透過光最大値
     * Branch - Max Translucency
     * Default Value  = 5 */
    float MaxTranslucencyBranch;

    /* ビルボードのSpecular抑制値
     * Billboard Specular Suppression Value
     * Default Value  = 1 */
    float BillboardBackSpecularWeakenParam;
} speedtree_model_param_t;
