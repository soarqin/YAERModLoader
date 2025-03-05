#pragma once

typedef struct er_enemy_standard_info_bank_s {
    /* 挙動ｉｄ
     *   敵の挙動ＩＤ
     * Behavior id
     *   Enemy behavior ID */
    int EnemyBehaviorID;

    /* ヒットポイント
     *   ヒットポイント
     * Hit points
     *   Hit points
     * Default Value  = 1 */
    unsigned short HP;

    /* 攻撃力
     *   攻撃力（プロト専用）
     * Offensive power
     *   Attack power (for proto only)
     * Default Value  = 1 */
    unsigned short AttackPower;

    /* キャラタイプ
     *   キャラタイプ
     * Character type
     *   Character type
     * Default Value  = 5 */
    int ChrType;

    /* あたりの高さ[m]
     *   あたりの高さ（直径以上のサイズを指定してください）
     * Height per [m]
     *   Height per (Please specify a size larger than the diameter)
     * Default Value  = 2 */
    float HitHeight;

    /* あたりの半径[m]
     *   あたりの半径
     * Radius around [m]
     *   Radius around
     * Default Value  = 0.4 */
    float HitRadius;

    /* 重さ[kg]
     *   キャラの重さ
     * Weight [kg]
     *   The weight of the character
     * Default Value  = 60 */
    float Weight;

    /* 動摩擦力
     *   動摩擦力
     * Dynamic friction force
     *   Dynamic friction force */
    float DynamicFriction;

    /* 静摩擦力
     *   静止摩擦力
     * Static friction
     *   Static friction force */
    float StaticFriction;

    /* 上半身初期状態
     *   上半身初期状態（PG入力）
     * Upper body initial state
     *   Upper body initial state (PG input) */
    int UpperDefState;

    /* アクション初期状態
     *   アクション初期状態（PG入力）
     * Initial state of action
     *   Action initial state (PG input) */
    int ActionDefState;

    /* 単位時間当たり旋回できる角度[deg/s]
     *   単位時間当たりのＹ軸旋回角度[deg/s]
     * Angle that can be turned per unit time [deg / s]
     *   Y-axis turning angle per unit time [deg / s]
     * Default Value  = 10 */
    float RotY_per_Second;

    /* 予約 */
    char reserve0[20];

    /* 未使用
     *   未使用
     * unused
     *   unused */
    unsigned char RotY_per_Second_old;

    /* 左右移動できるか
     *   左右移動できるか
     * Can you move left and right?
     *   Can you move left and right? */
    unsigned char EnableSideStep;

    /* キャラあたりにラグドールを使用するか
     *   キャラあたりにラグドールを使用するか
     * Whether to use a ragdoll per character
     *   Whether to use a ragdoll per character */
    unsigned char UseRagdollHit;

    /* 予約 */
    char reserve_last[5];

    /* スタミナ量
     *   スタミナ総量
     * Amount of stamina
     *   Total amount of stamina */
    unsigned short stamina;

    /* スタミナ回復
     *   1秒間あたりのスタミナ回復量
     * Stamina recovery
     *   Stamina recovery amount per second */
    unsigned short staminaRecover;

    /* スタミナ基本消費
     *   攻撃、ガード時に使用するスタミナ消費の基本値
     * Stamina basic consumption
     *   Basic value of stamina consumption used when attacking and guarding */
    unsigned short staminaConsumption;

    /* 物理防御力
     *   物理攻撃に対するダメージ減少基本値
     * Physical defense
     *   Damage reduction base value for physical attacks */
    unsigned short deffenct_Phys;

    /* 予約1 */
    char reserve_last2[48];
} er_enemy_standard_info_bank_t;
