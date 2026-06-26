#pragma once

typedef struct er_sound_auto_reverb_select_param_s {
    /* リバーブタイプ
     *   リバーブタイプ
     * Reverb Type
     *   Reverb type */
    unsigned int reverbType;

    /* エリアNo
     *   条件：エリアNo(-1:無効)
     * Condition: Area Number
     *   Condition: Area No. (-1: Invalid)
     * Default Value  = -1 */
    int AreaNo;

    /* 屋内外
     *   条件：屋内外指定(0:屋外,1:屋内)(-1:無効)
     * Condition: Indoor/Outdoor
     *   Condition: Indoor / outdoor designation (0: outdoor, 1: indoor) (-1: invalid)
     * Default Value  = -1 */
    char IndoorOutdoor;

    /* 使用評価距離番号A
     *   条件：使用する評価距離の番号A(-1:無効)
     * Condition: Evaluation Distance A
     *   Condition: Evaluation distance number A to use (-1: invalid)
     * Default Value  = -1 */
    char useDistNoA;

    /* 使用評価距離番号B
     *   条件：使用する評価距離の番号B(-1:無効)
     * Condition: Evaluation Distance B
     *   Condition: Evaluation distance number B to be used (-1: invalid)
     * Default Value  = -1 */
    char useDistNoB;

    char pad0[1];

    /* 距離MinA[m]
     *   条件：評価距離最小指定A用(0より小さい:無効)
     * Condition: Evaluation Distance A - Min
     *   Condition: For evaluation distance minimum specification A (less than 0: invalid)
     * Default Value  = -1 */
    float DistMinA;

    /* 距離MaxA[m]
     *   条件：評価距離最大指定A用(0より小さい:無効)
     * Condition: Evaluation Distance A - Max
     *   Condition: For evaluation distance maximum specification A (less than 0: invalid)
     * Default Value  = -1 */
    float DistMaxA;

    /* 距離MinB[m]
     *   条件：評価距離最小指定A用(0より小さい:無効)
     * Condition: Evaluation Distance B - Min
     *   Condition: For evaluation distance minimum specification A (less than 0: invalid)
     * Default Value  = -1 */
    float DistMinB;

    /* 距離MaxB[m]
     *   条件：評価距離最大指定A用(0より小さい:無効)
     * Condition: Evaluation Distance B - Max
     *   Condition: For evaluation distance maximum specification A (less than 0: invalid)
     * Default Value  = -1 */
    float DistMaxB;

    /* 衝突点NoHit数最小数
     *   条件：NoHit数(-1:無効)
     * Condition: No Hit Minimum
     *   Condition: No Hit number (-1: invalid)
     * Default Value  = -1 */
    int NoHitNumMin;
} er_sound_auto_reverb_select_param_t;
