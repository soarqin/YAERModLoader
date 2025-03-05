#pragma once

typedef struct er_ai_standard_info_bank_s {
    /* 認識距離[m]
     *   敵性キャラクタを認識する距離
     * Recognition distance [m]
     *   Distance to recognize hostile characters
     * Default Value  = 20 */
    unsigned short RadarRange;

    /* 認識角度Ｘ[deg]
     *   敵性キャラクタを認識するX角度　現在の視線方向を０度として、上が＋。
     * Recognition angle X [deg]
     *   X angle for recognizing hostile characters: The current line-of-sight direction is 0 degrees, and the top is +.
     * Default Value  = 30 */
    unsigned char RadarAngleX;

    /* 認識角度Y[deg]
     *   敵性キャラクタを認識するY角度　現在の視線方向を０度として、右が＋。
     * Recognition angle Y [deg]
     *   Y angle for recognizing hostile characters: The current line-of-sight direction is 0 degrees, and the right is +.
     * Default Value  = 60 */
    unsigned char RadarAngleY;

    /* 縄張り距離[m]
     *   自分の縄張りの距離。認識しているプレイヤーがこの距離から外れると初期位置に戻ります。
     * Territory distance [m]
     *   The distance of your territory. If the recognizing player deviates from this distance, it will return to the initial position.
     * Default Value  = 20 */
    unsigned short TerritorySize;

    /* 攻撃前威嚇率[0～100]
     *   攻撃前に威嚇する確率
     * Intimidation rate before attack [0-100]
     *   Probability of threatening before attack
     * Default Value  = 50 */
    unsigned char ThreatBeforeAttackRate;

    /* 初回認識威嚇
     *   初回プレイヤー認識時に必ず威嚇するかどうか
     * First recognition menacing
     *   Whether to intimidate when recognizing the first player */
    unsigned char ForceThreatOnFirstLocked;

    /* 予約 */
    char reserve0[24];

    /* 攻撃１　間合い[m]
     *   攻撃するときの間合い[m]
     * Attack 1 Maai [m]
     *   Time to attack [m] */
    unsigned short Attack1_Distance;

    /* 攻撃１　間合い遊び[m]
     *   攻撃間合いの遊び。間合い距離近辺で、振動しないように
     * Attack 1 Maai play [m]
     *   Play between attacks. Do not vibrate near the distance */
    unsigned short Attack1_Margin;

    /* 攻撃１　割合[0～100]
     *   攻撃の頻度
     * Attack 1 ratio [0-100]
     *   Frequency of attacks
     * Default Value  = 50 */
    unsigned char Attack1_Rate;

    /* 攻撃１　種類
     *   攻撃の種類
     * Attack 1 type
     *   Types of attacks */
    unsigned char Attack1_ActionID;

    /* 攻撃１　最小遅延時間[frame]
     *   攻撃可能になった時点から、攻撃するまでの遅延時間の最小。
     * Attack 1 Minimum delay time [frame]
     *   The minimum delay time from the time when an attack becomes possible to the time when an attack is possible. */
    unsigned char Attack1_DelayMin;

    /* 攻撃１　最長遅延時間[frame]
     *   攻撃可能になった時点から、攻撃するまでの遅延時間の最長。
     * Attack 1 Maximum delay time [frame]
     *   The longest delay time from the time when an attack becomes possible to the time when an attack is possible. */
    unsigned char Attack1_DelayMax;

    /* 攻撃１　攻撃許可円錐の角度[deg]
     *   視線方向とターゲットへの方向ベクトルのなす角が、この角度以内の場合、攻撃ＯＫ。
     * Attack 1 Attack permission Conical angle [deg]
     *   If the angle between the line-of-sight direction and the direction vector to the target is within this angle, the attack is OK.
     * Default Value  = 30 */
    unsigned char Attack1_ConeAngle;

    /* 予約 */
    char reserve10[7];

    /* 攻撃２　間合い[m]
     *   攻撃するときの間合い[m]
     * Attack 2 Maai [m]
     *   Time to attack [m] */
    unsigned short Attack2_Distance;

    /* 攻撃２　間合い遊び[m]
     *   攻撃間合いの遊び。間合い距離近辺で、振動しないように
     * Attack 2 Maai play [m]
     *   Play between attacks. Do not vibrate near the distance */
    unsigned short Attack2_Margin;

    /* 攻撃１　割合[0～100]
     *   攻撃の頻度
     * Attack 1 ratio [0-100]
     *   Frequency of attacks
     * Default Value  = 50 */
    unsigned char Attack2_Rate;

    /* 攻撃２　種類
     *   攻撃の種類
     * Attack 2 type
     *   Types of attacks */
    unsigned char Attack2_ActionID;

    /* 攻撃2　最小遅延時間[frame]
     *   攻撃可能になった時点から、攻撃するまでの遅延時間の最小。
     * Attack 2 Minimum delay time [frame]
     *   The minimum delay time from the time when an attack becomes possible to the time when an attack is possible. */
    unsigned char Attack2_DelayMin;

    /* 攻撃2　最長遅延時間[frame]
     *   攻撃可能になった時点から、攻撃するまでの遅延時間の最長。
     * Attack 2 Maximum delay time [frame]
     *   The longest delay time from the time when an attack becomes possible to the time when an attack is possible. */
    unsigned char Attack2_DelayMax;

    /* 攻撃2　攻撃許可円錐の角度[deg]
     *   視線方向とターゲットへの方向ベクトルのなす角が、この角度以内の場合、攻撃ＯＫ。
     * Attack 2 Attack permission Conical angle [deg]
     *   If the angle between the line-of-sight direction and the direction vector to the target is within this angle, the attack is OK.
     * Default Value  = 30 */
    unsigned char Attack2_ConeAngle;

    /* 予約 */
    char reserve11[7];

    /* 攻撃３　間合い[m]
     *   攻撃するときの間合い[m]
     * Attack 3 Maai [m]
     *   Time to attack [m] */
    unsigned short Attack3_Distance;

    /* 攻撃３　間合い遊び[m]
     *   攻撃間合いの遊び。間合い距離近辺で、振動しないように
     * Attack 3 Maai play [m]
     *   Play between attacks. Do not vibrate near the distance */
    unsigned short Attack3_Margin;

    /* 攻撃１　割合[0～100]
     *   攻撃の頻度
     * Attack 1 ratio [0-100]
     *   Frequency of attacks
     * Default Value  = 50 */
    unsigned char Attack3_Rate;

    /* 攻撃３　種類
     *   攻撃の種類
     * Attack 3 types
     *   Types of attacks */
    unsigned char Attack3_ActionID;

    /* 攻撃3　最小遅延時間[frame]
     *   攻撃可能になった時点から、攻撃するまでの遅延時間の最小。
     * Attack 3 Minimum delay time [frame]
     *   The minimum delay time from the time when an attack becomes possible to the time when an attack is possible. */
    unsigned char Attack3_DelayMin;

    /* 攻撃3　最長遅延時間[frame]
     *   攻撃可能になった時点から、攻撃するまでの遅延時間の最長。
     * Attack 3 Maximum delay time [frame]
     *   The longest delay time from the time when an attack becomes possible to the time when an attack is possible. */
    unsigned char Attack3_DelayMax;

    /* 攻撃3　攻撃許可円錐の角度[deg]
     *   視線方向とターゲットへの方向ベクトルのなす角が、この角度以内の場合、攻撃ＯＫ。
     * Attack 3 Attack permission Conical angle [deg]
     *   If the angle between the line-of-sight direction and the direction vector to the target is within this angle, the attack is OK.
     * Default Value  = 30 */
    unsigned char Attack3_ConeAngle;

    /* 予約 */
    char reserve12[7];

    /* 攻撃４　間合い[m]
     *   攻撃するときの間合い[m]
     * Attack 4 Maai [m]
     *   Time to attack [m] */
    unsigned short Attack4_Distance;

    /* 攻撃４　間合い遊び[m]
     *   攻撃間合いの遊び。間合い距離近辺で、振動しないように
     * Attack 4 Maai play [m]
     *   Play between attacks. Do not vibrate near the distance */
    unsigned short Attack4_Margin;

    /* 攻撃１　割合[0～100]
     *   攻撃の頻度
     * Attack 1 ratio [0-100]
     *   Frequency of attacks
     * Default Value  = 50 */
    unsigned char Attack4_Rate;

    /* 攻撃４　種類
     *   攻撃の種類
     * 4 types of attacks
     *   Types of attacks */
    unsigned char Attack4_ActionID;

    /* 攻撃4　最小遅延時間[frame]
     *   攻撃可能になった時点から、攻撃するまでの遅延時間の最小。
     * Attack 4 Minimum delay time [frame]
     *   The minimum delay time from the time when an attack becomes possible to the time when an attack is possible. */
    unsigned char Attack4_DelayMin;

    /* 攻撃4　最長遅延時間[frame]
     *   攻撃可能になった時点から、攻撃するまでの遅延時間の最長。
     * Attack 4 Maximum delay time [frame]
     *   The longest delay time from the time when an attack becomes possible to the time when an attack is possible. */
    unsigned char Attack4_DelayMax;

    /* 攻撃4　攻撃許可円錐の角度[deg]
     *   視線方向とターゲットへの方向ベクトルのなす角が、この角度以内の場合、攻撃ＯＫ。
     * Attack 4 Attack permission Conical angle [deg]
     *   If the angle between the line-of-sight direction and the direction vector to the target is within this angle, the attack is OK.
     * Default Value  = 30 */
    unsigned char Attack4_ConeAngle;

    /* 予約 */
    char reserve13[7];

    /* 予約 */
    char reserve_last[32];
} er_ai_standard_info_bank_t;
