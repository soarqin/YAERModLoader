#pragma once

typedef struct er_ride_param_s {
    /* 乗る側キャラID
     *   騎乗時に「乗る側」のキャラクタを特定するパラメータです
     * Rider - Character ID
     *   It is a parameter that identifies the character of the riding side when riding. */
    unsigned int atkChrId;

    /* 乗られる側キャラID
     *   騎乗時に「乗られる側」のキャラクタを特定するパラメータです
     * Mount - Character ID
     *   It is a parameter that identifies the character of the riding side when riding. */
    unsigned int defChrId;

    /* 騎乗時カメラID
     *   騎乗時のカメラパラメータを専用のカメラに変更するパラメータです。PC専用のパラメータで、敵に設定しても機能しません。
     * Ride - Camera Param ID
     *   It is a parameter to change the camera parameter at the time of riding to a dedicated camera. It is a parameter for PC only, and it does not work even if it is set to the enemy.
     * Default Value  = -1 */
    int rideCamParamId;

    /* 乗る側_騎乗アニメの種類と方向変数値
     *   キャラクタアニメ再生を制御しているツール「HavokAnimationTool（HAT）」の「RideOn（騎乗時再生）ステート」内に設定しているvariable（変数）"RideOnAnimId"の値を書き換えるパラメータです
     * Rider - Character Animation ID
     *   It is a parameter to rewrite the value of variable RideOnAnimId set in RideOn (playback during riding) state of the tool HavokAnimationTool (HAT) that controls character animation playback. */
    unsigned int atkChrAnimId;

    /* 乗られる側_騎乗アニメの種類と方向変数値
     *   キャラクタアニメ再生を制御しているツール「HavokAnimationTool（HAT）」の「RiddenOn（被騎乗時再生）ステート」内に設定しているvariable（変数）"RiddenOnAnimId"の値を書き換えるパラメータです
     * Mount - Character Animation ID
     *   It is a parameter to rewrite the value of variable RiddenOnAnimId set in RiddenOn (playback when riding) state of the tool HavokAnimationTool (HAT) that controls character animation playback. */
    unsigned int defChrAnimId;

    /* 騎乗アニメ開始時の乗られる側の位置合わせダミポリID
     *   乗られる側にのみ必要なダミポリ設定です（乗る側キャラクタには、設定の必要ありません）
     * Mount - Adjust Dummy Poly ID
     *   This is a Damipoli setting that is required only for the rider (the rider's character does not need to be set).
     * Default Value  = -1 */
    int defAdjustDmyId;

    /* 騎乗判定_乗られる側の判定基準ダミポリID
     *   乗る側のキャラには、ダミポリの設定はとくに必要ありません
     * Mount - Check Dummy Poly ID
     *   There is no need to set Damipoli for the character on the riding side.
     * Default Value  = -1 */
    int defCheckDmyId;

    /* 騎乗判定_乗る側の正面判定角度範囲[deg]
     *   乗る側の【向き】と、乗られる側の「正面判定ダミポリID」の角度差で判定します。値が大きいほど、「そっぽを向いていても乗れる」ようになります
     * Rider/Mount - Ride Angle Tolerance
     *   Judgment is made by the angle difference between the [direction] on the riding side and the front judgment Damipoly ID on the riding side. The higher the value, the more you can ride even if you are facing away. */
    float diffAngMyToDef;

    /* 騎乗判定_有効距離[m]
     *   「対象との騎乗可能距離」を決定するパラメータです
     * Mount Distance
     *   It is a parameter that determines the mountable distance to the target */
    float dist;

    /* 騎乗判定_有効高さ上方向[m]
     *   乗られる対象が、乗る対象よりどの程度上方にいても騎乗可能か？を、メートル単位で設定します
     * Mount Distance - Max Height
     *   Is it possible to ride even if the target to be ridden is above the target to be ridden? Is set in meters */
    float upperYRange;

    /* 騎乗判定_有効高さ下方向[m]
     *   乗られる対象が、乗る対象よりどの程度下方にいても騎乗可能か？を、メートル単位で設定します
     * Mount Distance - Min Height
     *   Is it possible to ride even if the target to be ridden is below the target to be ridden? Is set in meters */
    float lowerYRange;

    /* 騎乗判定_対象間の角度差範囲min[deg]
     *   乗る側が、乗られる側のどの範囲(角度)にいれば騎乗できるか？の最小値を設定します
     * Ride Angle Tolerance - Min
     *   In what range (angle) of the rider can ride? Set the minimum value of */
    float diffAngMin;

    /* 騎乗判定_対象間の角度差範囲max[deg]
     *   乗る側が、乗られる側のどの範囲(角度)にいれば騎乗できるか？の最大値を設定します
     * Ride Angle Tolerance - Max
     *   In what range (angle) of the rider can ride? Set the maximum value of */
    float diffAngMax;

    /* 予約
     *   予約領域 */
    char pad[12];
} er_ride_param_t;
