#pragma once

typedef struct missile_param_s {
    /* FFXID
     *   ID on the FFX editor */
    int FFXID;

    /* 生存時間[frame]
     *   生存時間。
     * Survival time [frame]
     *   Survival time. */
    unsigned short LifeTime;

    /* 当たり球半径[cm]
     *   当たり球半径。単位cm
     * Hit ball radius [cm]
     *   Hit ball radius. Unit cm */
    unsigned short HitSphereRadius;

    /* 着弾ダメージ
     *   着弾時のダメージ量
     * Landing damage
     *   Amount of damage at the time of landing */
    unsigned short HitDamage;

    /* 予約 */
    char reserve0[6];

    /* 初速度[m/s]
     *   初速度[m/s]
     * Initial speed [m / s]
     *   Initial speed [m / s] */
    float InitVelocity;

    /* 射程距離
     *   射程距離
     * Range distance
     *   Range distance */
    float distance;

    /* 射程距離内重力
     *   射程距離内重力
     * Gravity within range
     *   Gravity within range */
    float gravityInRange;

    /* 射程距離外重力
     *   射程距離外重力
     * Out-of-range gravity
     *   Out-of-range gravity */
    float gravityOutRange;

    /* 消費MP
     *   消費MP
     * MP consumption
     *   MP consumption */
    int mp;

    /* 射程距離内加速度
     *   射程距離内加速度
     * Acceleration within range
     *   Acceleration within range */
    float accelInRange;

    /* 射程距離外加速度
     *   射程距離外加速度
     * Out-of-range acceleration
     *   Out-of-range acceleration */
    float accelOutRange;

    /* 予約 */
    char reserve1[20];

    /* 着弾ＩＤ
     *   着弾ＩＤ
     * Landing ID
     *   Landing ID */
    unsigned short HitMissileID;

    /* 寿命で死ぬか？
     *   着弾しても、死なずに、寿命を使い切るか？
     * Will you die at the end of your life?
     *   Will it use up its life without dying even if it lands? */
    unsigned char DiedNaturaly;

    /* 寿命が切れたときに着弾するか
     *   寿命が切れたときに着弾するか
     * Will it land when the life has expired?
     *   Will it land when the life has expired? */
    unsigned char ExplosionDie;

    /* ヒット時行動ID
     *   ダメージを与えたとき相手に与える行動ID
     * Action ID on hit
     *   Action ID given to the opponent when doing damage */
    int behaviorId;

    /* 予約 */
    char reserve_last[56];
} missile_param_t;
