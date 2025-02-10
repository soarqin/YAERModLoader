#pragma once

typedef struct enemy_common_param_s {
    /* 予約
     *   (dummy8) */
    char reserved0[8];

    /* 音ターゲットに対して接近を試みる時間
     * Sound - Target Try Approach Time */
    int soundTargetTryApproachTime;

    /* 索敵ターゲットに対して接近を試みる時間
     * Search - Target Try Approach Time */
    int searchTargetTryApproachTime;

    /* 記憶ターゲットに対して接近を試みる時間
     * Memory - Target Try Approach Time */
    int memoryTargetTryApproachTime;

    /* 予約
     *   (dummy8) */
    char reserved5[40];

    /* 特定時間帯配置のエネミーの出現・消滅に演出に使うファントムシェーダID
     *   出現・消滅の演出でファントムシェーダをフェイドする、
     * Activate Chr by Time - Phantom ID
     *   Phantom shader ID used for directing the appearance and disappearance of enemies placed in a specific time zone */
    int activateChrByTime_PhantomId;

    /* パス終端まで行くと敵が見切れそうなことがわかったインタラプト、を発生させる距離
     *   Unreachパス時、終端と対象がこの距離以内ならインタラプトを発生させる
     * Find Unfavourable Failed Point Distance
     *   Distance to generate an interrupt, which turns out that the enemy is likely to be cut off when going to the end of the path */
    float findUnfavorableFailedPointDist;

    /* パス終端まで行くと敵が見切れそうなことがわかったインタラプト、を発生させる高さ
     *   Unreachパス時、終端と対象がこの距離以上ならインタラプトを発生させる
     * Find Unfavourable Failed Point Height
     *   The height that causes an interrupt, which turns out that the enemy is likely to be cut off when going to the end of the path */
    float findUnfavorableFailedPointHeight;

    /* 予約
     *   (dummy8) */
    char reserved18[184];
} enemy_common_param_t;
