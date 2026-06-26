#pragma once

typedef struct er_toughness_param_s {
    /* 武器強靭度補正倍率
     *   強靭度を求める際に武器の「強靭度補正倍率」に掛かる補正倍率です
     * Toughness Correction
     *   It is a correction magnification applied to the toughness correction magnification of the weapon when calculating the toughness.
     * Default Value  = 1 */
    float correctionRate;

    /* 最低 強靭度
     *   強靭度期間開始時に適用される現在強靭度の下限値です。強靭度開始時に強靭度がこの値を下回る場合は、この値まで回復します。
     * Minimum Toughness
     *   The lower limit of current toughness applied at the beginning of the toughness period. If the toughness falls below this value at the start of toughness, it will recover to this value. */
    unsigned short minToughness;

    /* 最低強靭値が強靭度倍率の影響を受けない
     *   強靭度 補正倍率を、最低 強靭度に、適用しなくなります
     * Minimum Toughness not affected by Toughness Multiplier
     *   The toughness correction factor will no longer be applied to the minimum toughness. */
    unsigned char isNonEffectiveCorrectionForMin;

    /* パッド
     *   pad */
    char pad2[1];

    /* 特殊効果ID
     *   強靭度期間中にかかる差換え特殊効果Idです。-1の場合は通常の差換えルールが適用されます。プレイヤーキャラでしか使われません
     * Damage Level Replacement - SpEffect ID
     *   Replacement special effect Id that takes place during the toughness period. If -1, the normal replacement rule applies. Only used by player characters
     * Default Value  = -1 */
    int spEffectId;

    /* 防具強靭度補正倍率
     *   強靭度を求める際に防具の「強靭度補正倍率」に掛かる補正倍率です
     * Armor - Toughness Correction
     *   This is the correction factor applied to the toughness correction factor of the armor when determining the toughness.
     * Default Value  = 1 */
    float proCorrectionRate;

    /* Default Value  = 1 */
    float unk1;

    /* Default Value  = 1 */
    float unk2;

    /* パッド
     *   pad */
    char pad1[8];
} er_toughness_param_t;
