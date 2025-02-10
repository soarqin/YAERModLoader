#pragma once

typedef struct ai_attack_param_s {
    /* 参照ID
     *   NPC思考パラメータで指定するID
     * Reference ID
     *   ID specified by NPC thinking parameters */
    int attackTableId;

    /* 攻撃ID
     *   攻撃の番号
     * Attack ID
     *   Attack number */
    int attackId;

    /* 成功判定距離
     *   Common_Attack系のサブゴールの引数用
     * Success judgment distance
     *   For arguments of Common_Attack type subgoals */
    float successDistance;

    /* 攻撃前旋回時間
     *   Common_Attack系のサブゴールの引数用
     * Turn time before attack
     *   For arguments of Common_Attack type subgoals */
    float turnTimeBeforeAttack;

    /* 正面判定角度
     *   Common_Attack系のサブゴールの引数用
     * Front judgment angle
     *   For arguments of Common_Attack type subgoals */
    short frontAngleRange;

    /* 上方実行閾値
     *   Common_Attack系のサブゴールの引数用
     * Upward execution threshold
     *   For arguments of Common_Attack type subgoals */
    short upAngleThreshold;

    /* 下方実行閾値
     *   Common_Attack系のサブゴールの引数用
     * Downward execution threshold
     *   For arguments of Common_Attack type subgoals */
    short downAngleThershold;

    /* 始動技か
     *   コンボの2段目以降の攻撃は×
     * Is it a starting technique?
     *   Attacks from the second stage of the combo are  */
    unsigned char isFirstAttack;

    /* 適正距離外で選択するか
     *   適正距離外の時に選択対象にするかどうか
     * Whether to select outside the proper distance
     *   Whether to select when the distance is out of the proper distance */
    unsigned char doesSelectOnOutRange;

    /* 最小適正距離
     *   攻撃の適正距離の最小値
     * Minimum proper distance
     *   Minimum value of proper attack distance */
    float minOptimalDistance;

    /* 最大適正距離
     *   攻撃の適性距離の最大値
     * Maximum proper distance
     *   Maximum attack suitability distance */
    float maxOptimalDistance;

    /* 適正角度基準方向1
     *   攻撃の適正角度の基準となる方向（XZ平面）
     * Appropriate angle reference direction 1
     *   Direction that serves as a reference for the proper angle of attack (XZ plane) */
    short baseDirectionForOptimalAngle1;

    /* 適正角度基準範囲1
     *   攻撃の適性角度の範囲
     * Appropriate angle reference range 1
     *   Range of aptitude angles for attacks */
    short optimalAttackAngleRange1;

    /* 適正角度基準方向2
     *   攻撃の適性確度の基準となる方向（XZ平面）
     * Appropriate angle reference direction 2
     *   Direction that serves as a reference for attack aptitude accuracy (XZ plane) */
    short baseDirectionForOptimalAngle2;

    /* 適正角度基準範囲2
     *   攻撃の適性角度の範囲
     * Appropriate angle reference range 2
     *   Range of aptitude angles for attacks */
    short optimalAttackAngleRange2;

    /* 実行可能インターバル
     *   一度攻撃を行ってから再度使うために必要な時間
     * Executable interval
     *   Time required to attack once and then use it again
     * Default Value  = 1 */
    float intervalForExec;

    /* 選択レート
     *   選択されやすさを倍率で指定する
     * Selection rate
     *   Specify the ease of selection by magnification
     * Default Value  = -1 */
    float selectionTendency;

    /* 近距離選択レート
     *   近距離での選択レート
     * Short range selection rate
     *   Selection rate at close range
     * Default Value  = -1 */
    float shortRangeTendency;

    /* 中距離選択レート
     *   中距離での選択レート
     * Medium range selection rate
     *   Selection rate at medium range
     * Default Value  = -1 */
    float middleRangeTendency;

    /* 遠距離選択レート
     *   遠距離での選択レート
     * Distance selection rate
     *   Selection rate at long distances
     * Default Value  = -1 */
    float farRangeTendency;

    /* 範囲外レート
     *   範囲外での選択レート
     * Out of range rate
     *   Selection rate out of range
     * Default Value  = -1 */
    float outRangeTendency;

    /* 派生攻撃1
     *   派生可能な攻撃の番号
     * Derived attack 1
     *   Derivable attack number
     * Default Value  = -1 */
    int deriveAttackId1;

    /* 派生攻撃2
     *   派生可能な攻撃の番号
     * Derived attack 2
     *   Derivable attack number
     * Default Value  = -1 */
    int deriveAttackId2;

    /* 派生攻撃3
     *   派生可能な攻撃の番号
     * Derived attack 3
     *   Derivable attack number
     * Default Value  = -1 */
    int deriveAttackId3;

    /* 派生攻撃4
     *   派生可能な攻撃の番号
     * Derived attack 4
     *   Derivable attack number
     * Default Value  = -1 */
    int deriveAttackId4;

    /* 派生攻撃5
     *   派生可能な攻撃の番号
     * Derived attack 5
     *   Derivable attack number
     * Default Value  = -1 */
    int deriveAttackId5;

    /* 派生攻撃6
     *   派生可能な攻撃の番号
     * Derived attack 6
     *   Derivable attack number
     * Default Value  = -1 */
    int deriveAttackId6;

    /* 派生攻撃7
     *   派生可能な攻撃の番号
     * Derived attack 7
     *   Derivable attack number
     * Default Value  = -1 */
    int deriveAttackId7;

    /* 派生攻撃8
     *   派生可能な攻撃の番号
     * Derived attack 8
     *   Derivable attack number
     * Default Value  = -1 */
    int deriveAttackId8;

    /* 派生攻撃9
     *   派生可能な攻撃の番号
     * Derived attack 9
     *   Derivable attack number
     * Default Value  = -1 */
    int deriveAttackId9;

    /* 派生攻撃10
     *   派生可能な攻撃の番号
     * Derived attack 10
     *   Derivable attack number
     * Default Value  = -1 */
    int deriveAttackId10;

    /* 派生攻撃11
     *   派生可能な攻撃の番号
     * Derived attack 11
     *   Derivable attack number
     * Default Value  = -1 */
    int deriveAttackId11;

    /* 派生攻撃12
     *   派生可能な攻撃の番号
     * Derived attack 12
     *   Derivable attack number
     * Default Value  = -1 */
    int deriveAttackId12;

    /* 派生攻撃13
     *   派生可能な攻撃の番号
     * Derived attack 13
     *   Derivable attack number
     * Default Value  = -1 */
    int deriveAttackId13;

    /* 派生攻撃14
     *   派生可能な攻撃の番号
     * Derived attack 14
     *   Derivable attack number
     * Default Value  = -1 */
    int deriveAttackId14;

    /* 派生攻撃15
     *   派生可能な攻撃の番号
     * Derived attack 15
     *   Derivable attack number
     * Default Value  = -1 */
    int deriveAttackId15;

    /* 派生攻撃16
     *   派生可能な攻撃の番号
     * Derived attack 16
     *   Derivable attack number
     * Default Value  = -1 */
    int deriveAttackId16;

    /* ゴールの最小寿命
     *   ゴールの最小寿命
     * Minimum life of the goal
     *   Minimum life of the goal */
    float goalLifeMin;

    /* ゴールの最大寿命
     *   ゴールの最大寿命
     * Maximum life span of the goal
     *   Maximum life span of the goal */
    float goalLifeMax;

    /* 適正距離内で選択するか
     *   適正距離内の時に選択対象にするかどうか
     * Whether to select within the appropriate distance
     *   Whether to select when within the appropriate distance */
    unsigned char doesSelectOnInnerRange;

    /* 初撃として使用するか
     *   初撃として使用するか
     * Whether to use it as the first hit
     *   Whether to use it as the first hit
     * Default Value  = 1 */
    unsigned char enableAttackOnBattleStart;

    /* ターゲットダウン時選択するか
     *   ターゲットダウン時選択するか
     * Whether to select when the target is down
     *   Whether to select when the target is down
     * Default Value  = 1 */
    unsigned char doesSelectOnTargetDown;

    /* pad */
    char pad1[1];

    /* 最小到達判定距離
     *   最小到達判定距離
     * Minimum reach judgment distance
     *   Minimum reach judgment distance */
    float minArriveDistance;

    /* 最大到達判定距離
     *   最大到達判定距離
     * Maximum reach judgment distance
     *   Maximum reach judgment distance */
    float maxArriveDistance;

    /* 連続攻撃実行距離
     *   二段目以降の攻撃の実行判定に使用する距離
     * Continuous attack execution distance
     *   Distance used to determine the execution of attacks from the second stage onward
     * Default Value  = 4 */
    float comboExecDistance;

    /* 連続攻撃実行角度
     *   二段目以降の攻撃の実行判定に使用する距離
     * Continuous attack execution angle
     *   Distance used to determine the execution of attacks from the second stage onward
     * Default Value  = 180 */
    float comboExecRange;
} ai_attack_param_t;
