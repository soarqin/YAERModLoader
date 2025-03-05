#pragma once

typedef struct er_cs_dof_quality_detail_s {
    /* DOF許可
     *   DOF許可
     * Depth of Field Enabled
     *   DOF permission
     * Default Value  = 1 */
    unsigned char enabled;

    char dmy[3];

    /* HiResolutionBlur の設定を変更する
     *   HiResolutionBlur の設定を変更する(-1:強制オフ、0:そのまま、1:強制オン)
     * Force High Resolution Blur
     *   Change the HiResolutionBlur setting (-1- forced off, 0- as-is, 1- forced on)
     * Default Value  = -1 */
    int forceHiResoBlur;

    /* 最大ブラーレベル
     *   最大ブラーレベル。2:最大、1:レベルを一段落とす、0:さらに精度を落とす
     * Maximum Blur Level
     *   Maximum blur level. 2- Maximum, 1- Level to one paragraph, 0- Further reduce accuracy
     * Default Value  = 1 */
    int maxBlurLevel;
} er_cs_dof_quality_detail_t;
