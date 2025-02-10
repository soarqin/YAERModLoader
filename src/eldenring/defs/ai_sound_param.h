#pragma once

typedef struct ai_sound_param_s {
    /* 音半径[m]
     *   AI音の半径
     * Radius
     *   AI sound radius */
    float radius;

    /* 消滅時間[秒]
     *   AI音が残る時間
     * Duration
     *   Time for AI sound to remain */
    float lifeFrame;

    /* 特殊効果からの影響を受けるか
     *   特殊効果の”音半径倍率”の影響を受けるかどうか
     * Is Affected by Sound Radius Magnification
     *   Whether it is affected by the special effect Sound Radius Magnification */
    unsigned char bSpEffectEnable;

    /* 種別
     *   AI音の種別
     * Rate Type
     *   AI sound type */
    unsigned char type;

    /* 対象：●敵対
     *   対象：●敵対
     * Target: Hostile
     *   Target:  Hostile
     * Default Value  = 1 */
    unsigned char opposeTarget:1;

    /* 対象：○味方
     *   対象：○味方
     * Target: Friendly
     *   Target:  Allies */
    unsigned char friendlyTarget:1;

    /* 対象：自分
     *   対象：自分
     * Target: Self
     *   Target: myself */
    unsigned char selfTarget:1;

    /* PC自軍をターゲット中は聞けない
     *   PC自軍をターゲット中は聞けない
     * Disable on Targeting Player
     *   You can't listen while targeting your PC */
    unsigned char disableOnTargetPCompany:1;

    /* キャラの振る舞い
     *   キャラの振る舞い(旧：音タイプ
     * Rank
     *   Character behavior (former: sound type) */
    unsigned char rank;

    /* 音ターゲット忘れる時間（上書き）[sec]
     *   音ターゲット忘れる時間（上書き）[sec]
     * Forget Time
     *   Time to forget the sound target (overwrite) [sec]
     * Default Value  = -1 */
    float forgetTime;

    /* AI音優先度
     *   AI音優先度
     * Priority
     *   AI sound priority
     * Default Value  = 100 */
    int priority;

    /* 振る舞いID
     *   振る舞いID
     * Sound Behavior ID
     *   Behavior ID
     * Default Value  = -1 */
    int soundBehaviorId;

    /* AI音レベル
     *   どれくらい聞き取りづらい音なのか
     * AI Sound Level
     *   How hard it is to hear */
    unsigned char aiSoundLevel;

    /* リプランニングするAI状態
     *   AI音を聞いた際にリプランニングを走らせるAI状態の設定
     * Replanning State
     *   AI state setting to run replanning when listening to AI sound */
    unsigned char replaningState;

    /* パッド
     *   pad */
    char pad1[6];
} ai_sound_param_t;
