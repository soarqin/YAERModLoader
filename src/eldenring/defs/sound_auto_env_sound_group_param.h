#pragma once

typedef struct sound_auto_env_sound_group_param_s {
    /* サウンドNo
     *   再生するサウンドNo (サウンドタイプはa固定)
     * Sound Number
     *   Sound No to play (sound type is fixed to a)
     * Default Value  = -1 */
    int SoundNo;

    /* 判定拡張距離
     *   再生判定領域の拡張距離
     * Expand Range
     *   Extended distance of playback judgment area
     * Default Value  = 100 */
    float ExpandRange;

    /* 音源追従スピード
     *   実音源の目標位置への追従速度(固定速度)
     * Follow Speed
     *   Follow-up speed (fixed speed) to the target position of the actual sound source
     * Default Value  = 0.1 */
    float FollowSpeed;

    /* 音源追従率
     *   実音源の目標位置への追従速度(差分割合)
     * Follow Rate
     *   Follow-up speed (difference ratio) to the target position of the actual sound source
     * Default Value  = 0.015 */
    float FollowRate;
} sound_auto_env_sound_group_param_t;
