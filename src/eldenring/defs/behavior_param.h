#pragma once

/* Handles animation events, including attack frames or firing bullets.
 * Responsible for stamina consumption.
 * Note that in Elden Ring, SpEffects are applied directly from the animation. */
typedef struct behavior_param_s {
    /* 行動バリエーションID
     *   攻撃パラメータ用のIDを算出する際に使用します。実機上では直接使用しません。
     * Behavior Variation ID
     *   Used when calculating the ID for attack parameters. It is not used directly on the actual machine. */
    int variationId;

    /* 行動判定ID
     *   攻撃パラメータ用のIDを算出する際に使用します。このIDはTimeActEditorで入力される行動判定IDと一致させます。実機上では直接使用しません。
     * Behavior Judge ID
     *   Used when calculating the ID for attack parameters. This ID matches the action judgment ID entered in TimeActEditor. It is not used directly on the actual machine. */
    int behaviorJudgeId;

    /* IDルール用
     *   ID算出ルール用
     * State Behavior Type
     *   For ID calculation rules */
    unsigned char ezStateBehaviorType_old;

    /* 参照IDタイプ
     *   参照IDを間違わないように指定.
     * Reference Type
     *   Specify the reference ID so that it is correct. */
    unsigned char refType;

    /* pad */
    char pad2[2];

    /* 参照ID
     *   攻撃力、飛び道具、特殊効果パラメータのID、refTypeによって使い分けられる。
     * Reference ID
     *   It can be used properly according to the attack power, missile, ID of special effect parameter, and refType.
     * Default Value  = -1 */
    int refId;

    /* 消費SA
     *   行動時の消費SA量を設定.
     * Poise Cost
     *   Set the amount of SA consumed during action. */
    float consumeSA;

    /* 消費スタミナ
     *   行動時の消費スタミナ量を設定.
     * Stamina Cost
     *   Set the amount of stamina consumed during action. */
    int stamina;

    /* 武器耐久度消費（飛び道具時のみ）
     *   行動時の消費武器耐久度を設定.
     * Durability Cost
     *   Set the durability of weapons consumed during action. */
    int consumeDurability;

    /* カテゴリ
     *   スキルや、魔法、アイテムなどで、パラメータが変動する効果（エンチャントウェポンなど）があるので、│定した効果が、「武器攻撃のみをパワーアップする」といった効果に対応できるように行動ごとに設定するバリスタなど、設定の必要のないものは「なし」を設定する
     * Category
     *   Since there are effects (enchantment weapons, etc.) whose parameters fluctuate depending on skills, magic, items, etc., set each action so that the determined effect can correspond to the effect such as power up only weapon attack. Set None for items that do not need to be set, such as varistor. */
    unsigned char category;

    /* 消費人間性
     *   行動時の消費人間性量を設定
     * Humanity Cost
     *   Set the amount of humanity consumed during action */
    unsigned char heroPoint;

    /* pad */
    char pad1[2];
} behavior_param_t;
