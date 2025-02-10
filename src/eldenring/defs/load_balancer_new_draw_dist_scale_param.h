#pragma once

typedef struct load_balancer_new_draw_dist_scale_param_s {
    /* 発動レベル(開始)
     *   描画距離スケール発動レベル(開始)
     * Draw Distance - Level Start
     *   Drawing distance scale activation level (start)
     * Default Value  = 21 */
    unsigned char DrawDist_LvBegin;

    /* 発動レベル(終了)
     *   描画距離スケール発動レベル(修了)
     * Draw Distance - Level End
     *   Drawing distance scale activation level (completed)
     * Default Value  = 21 */
    unsigned char DrawDist_LvEnd;

    /* 予備
     *   予備 */
    char reserve0[2];

    /* スケール（開始）
     *   描画距離スケール（開始）
     * Draw Distance - Scale Start
     *   Drawing distance scale (start)
     * Default Value  = 1 */
    float DrawDist_ScaleBegin;

    /* スケール（終了）
     *   描画距離スケール（修了）
     * Draw Distance - Scale End
     *   Drawing distance scale (completed)
     * Default Value  = 1 */
    float DrawDist_ScaleEnd;

    /* 発動レベル(開始)
     *   影描画距離スケール発動レベル(開始)
     * Shadow Draw Distance - Level Start
     *   Shadow drawing distance scale activation level (start)
     * Default Value  = 21 */
    unsigned char ShadwDrawDist_LvBegin;

    /* 発動レベル(終了)
     *   影描画距離スケール発動レベル(修了)
     * Shadow Draw Distance - Level End
     *   Shadow drawing distance scale activation level (completed)
     * Default Value  = 21 */
    unsigned char ShadwDrawDist_LvEnd;

    /* 予備
     *   予備 */
    char reserve1[2];

    /* スケール（開始）
     *   影描画距離スケール（開始）
     * Shadow Draw Distance - Scale Start
     *   Shadow drawing distance scale (start)
     * Default Value  = 1 */
    float ShadwDrawDist_ScaleBegin;

    /* スケール（終了）
     *   影描画距離スケール（修了）
     * Shadow Draw Distance - Scale End
     *   Shadow drawing distance scale (completed)
     * Default Value  = 1 */
    float ShadwDrawDist_ScaleEnd;

    /* 予備
     *   予備 */
    char reserve2[24];
} load_balancer_new_draw_dist_scale_param_t;
