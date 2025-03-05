#pragma once

typedef struct er_env_obj_lot_param_s {
    /* Asset ID [0]
     *   AssetId_0 (-1 Ignore)
     * Default Value  = -1 */
    int AssetId_0;

    /* Asset ID [1]
     *   AssetId_1 (-1 Ignore)
     * Default Value  = -1 */
    int AssetId_1;

    /* Asset ID [2]
     *   AssetId_2 (-1 Ignore)
     * Default Value  = -1 */
    int AssetId_2;

    /* Asset ID [3]
     *   AssetId_3 (-1 Ignore)
     * Default Value  = -1 */
    int AssetId_3;

    /* Asset ID [4]
     *   AssetId_4 (-1 Ignore)
     * Default Value  = -1 */
    int AssetId_4;

    /* Asset ID [5]
     *   AssetId_5 (-1 Ignore)
     * Default Value  = -1 */
    int AssetId_5;

    /* Asset ID [6]
     *   AssetId_6 (-1 Ignore)
     * Default Value  = -1 */
    int AssetId_6;

    /* Asset ID [7]
     *   AssetId_7 (-1 Ignore)
     * Default Value  = -1 */
    int AssetId_7;

    /* 出現ウェイト_0
     *   出現の比率ポイント(ウェイト)_0: 0だと無視
     * Create Weight [0]
     *   Appearance ratio point (weight) _0 0 is ignored */
    unsigned char CreateWeight_0;

    /* 出現ウェイト_1
     *   出現の比率ポイント(ウェイト)_1
     * Create Weight [1]
     *   Appearance ratio point (weight) _1 */
    unsigned char CreateWeight_1;

    /* 出現ウェイト_2
     *   出現の比率ポイント(ウェイト)_2
     * Create Weight [2]
     *   Appearance ratio point (weight) _2 */
    unsigned char CreateWeight_2;

    /* 出現ウェイト_3
     *   出現の比率ポイント(ウェイト)_3
     * Create Weight [3]
     *   Appearance ratio point (weight) _3 */
    unsigned char CreateWeight_3;

    /* 出現ウェイト_4
     *   出現の比率ポイント(ウェイト)_4
     * Create Weight [4]
     *   Appearance ratio point (weight) _4 */
    unsigned char CreateWeight_4;

    /* 出現ウェイト_5
     *   出現の比率ポイント(ウェイト)_5
     * Create Weight [5]
     *   Appearance ratio point (weight) _5 */
    unsigned char CreateWeight_5;

    /* 出現ウェイト_6
     *   出現の比率ポイント(ウェイト)_6
     * Create Weight [6]
     *   Appearance ratio point (weight) _6 */
    unsigned char CreateWeight_6;

    /* 出現ウェイト_7
     *   出現の比率ポイント(ウェイト)_7
     * Create Weight [7]
     *   Appearance ratio point (weight) _7 */
    unsigned char CreateWeight_7;

    /* リザーブ
     *   リザーブ */
    char Reserve_0[24];
} er_env_obj_lot_param_t;
