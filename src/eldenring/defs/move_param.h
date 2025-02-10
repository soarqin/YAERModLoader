#pragma once

typedef struct move_param_s {
    /* 待機
     *   待機
     * Stay ID
     *   stand-by
     * Default Value  = -1 */
    int stayId;

    /* 歩行 前
     *   歩行 前
     * Walk - Forward
     *   Before walking
     * Default Value  = -1 */
    int walkF;

    /* 歩行 後
     *   歩行 後
     * Walk - Backward
     *   After walking
     * Default Value  = -1 */
    int walkB;

    /* 歩行 左
     *   歩行 左
     * Walk - Left
     *   Walking left
     * Default Value  = -1 */
    int walkL;

    /* 歩行 右
     *   歩行 右
     * Walk - Right
     *   Walking right
     * Default Value  = -1 */
    int walkR;

    /* 走行 前
     *   走行 前
     * Dash - Forward
     *   Before driving
     * Default Value  = -1 */
    int dashF;

    /* 走行 後
     *   走行 後
     * Dash - Backward
     *   After running
     * Default Value  = -1 */
    int dashB;

    /* 走行 左
     *   走行 左
     * Dash - Left
     *   Driving left
     * Default Value  = -1 */
    int dashL;

    /* 走行 右
     *   走行 右
     * Dash - Right
     *   Driving right
     * Default Value  = -1 */
    int dashR;

    /* ダッシュ移動
     *   ダッシュ移動
     * Sprint Dash
     *   Dash move
     * Default Value  = -1 */
    int superDash;

    /* 緊急回避 前
     *   緊急回避 前
     * Evasion - Forward
     *   Before emergency avoidance
     * Default Value  = -1 */
    int escapeF;

    /* 緊急回避 後
     *   緊急回避 後
     * Evasion - Backward
     *   After emergency avoidance
     * Default Value  = -1 */
    int escapeB;

    /* 緊急回避 左
     *   緊急回避 左
     * Evasion - Left
     *   Emergency avoidance left
     * Default Value  = -1 */
    int escapeL;

    /* 緊急回避 右
     *   緊急回避 右
     * Evasion - Right
     *   Emergency avoidance right
     * Default Value  = -1 */
    int escapeR;

    /* 90度旋回 左
     *   90度旋回 左
     * Turn - Left 90
     *   90 degree turn left
     * Default Value  = -1 */
    int turnL;

    /* 90度旋回 右
     *   90度旋回 右
     * Turn - Right 90
     *   90 degree turn right
     * Default Value  = -1 */
    int trunR;

    /* 180度旋回 左
     *   180度旋回 左
     * Turn - Left 180
     *   180 degree turn left
     * Default Value  = -1 */
    int largeTurnL;

    /* 180度旋回 右
     *   180度旋回 右
     * Turn - Right 180
     *   180 degree turn right
     * Default Value  = -1 */
    int largeTurnR;

    /* ステップ移動
     *   180度旋回 右
     * Step Move
     *   180 degree turn right
     * Default Value  = -1 */
    int stepMove;

    /* 飛行待機
     *   飛行待機
     * Fly Stay
     *   Flight standby
     * Default Value  = -1 */
    int flyStay;

    /* 飛行前進
     *   飛行前進
     * Fly Walk - Forward
     *   Flight advance
     * Default Value  = -1 */
    int flyWalkF;

    /* 飛行左前進
     *   飛行左前進。低回転
     * Fly Walk - Forward Left
     *   Fly left forward. Low rotation
     * Default Value  = -1 */
    int flyWalkFL;

    /* 飛行右前進
     *   飛行右前進。低回転
     * Fly Walk - Forward Right
     *   Fly right forward. Low rotation
     * Default Value  = -1 */
    int flyWalkFR;

    /* 飛行左前進2
     *   飛行左前進2。高回転
     * Fly Walk - Forward Left 2
     *   Flight left forward 2. High rotation
     * Default Value  = -1 */
    int flyWalkFL2;

    /* 飛行右前進2
     *   飛行右前進2。高回転
     * Fly Walk - Forward Right 2
     *   Flight right forward 2. High rotation
     * Default Value  = -1 */
    int flyWalkFR2;

    /* 高速飛行前進
     *   高速飛行前進
     * Fly Dash - Forward
     *   High speed flight advance
     * Default Value  = -1 */
    int flyDashF;

    /* 高速飛行左前進
     *   高速飛行左前進。低回転
     * Fly Dash - Forward Left
     *   High-speed flight left forward. Low rotation
     * Default Value  = -1 */
    int flyDashFL;

    /* 高速飛行右前進
     *   高速飛行右前進。低回転
     * Fly Dash - Forward Right
     *   High speed flight right forward. Low rotation
     * Default Value  = -1 */
    int flyDashFR;

    /* 高速飛行左前進2
     *   高速飛行左前進2。高回転
     * Fly Dash - Forward Left 2
     *   High speed flight left forward 2. High rotation
     * Default Value  = -1 */
    int flyDashFL2;

    /* 高速飛行右前進2
     *   高速飛行右前進2。高回転
     * Fly Dash - Forward Right 2
     *   High speed flight right forward 2. High rotation
     * Default Value  = -1 */
    int flyDashFR2;

    /* ダッシュ緊急回避前
     *   ダッシュ緊急回避前
     * Fly Evasion - Forward
     *   Before dash emergency avoidance
     * Default Value  = -1 */
    int dashEscapeF;

    /* ダッシュ緊急回避後
     *   ダッシュ緊急回避後
     * Fly Evasion - Backward
     *   After dash emergency avoidance
     * Default Value  = -1 */
    int dashEscapeB;

    /* ダッシュ緊急回避左
     *   ダッシュ緊急回避左
     * Fly Evasion - Left
     *   Dash emergency avoidance left
     * Default Value  = -1 */
    int dashEscapeL;

    /* ダッシュ緊急回避右
     *   ダッシュ緊急回避右
     * Fly Evasion - Right
     *   Dash emergency avoidance right
     * Default Value  = -1 */
    int dashEscapeR;

    /* アナログ移動パラＩＤ
     *   移動アニメブレンドで使用される移動アニメパラメータＩＤ
     * Analog Move Param ID
     *   Mobile animation parameter ID used in mobile animation blend
     * Default Value  = -1 */
    int analogMoveParamId;

    /* アニメなし旋回角度[deg]
     *   旋回角度がこの値以下だと旋回アニメを再生しません（敵旋回制御のみ有効）
     * No Anim Turn Angle
     *   If the turning angle is less than this value, the turning animation will not be played (only the enemy turning control is effective). */
    unsigned char turnNoAnimAngle;

    /* 45度旋回アニメ角度[deg]
     *   旋回角度がこの値以下だと45度旋回アニメを再生します（ボス2足のみ有効）
     * 45 Turn Angle
     *   If the turning angle is less than this value, the 45 degree turning animation will be played (only 2 bosses are valid). */
    unsigned char turn45Angle;

    /* 90度旋回アニメ角度[deg]
     *   旋回角度がこの値以下だと90度旋回アニメを再生します（敵旋回制御のみ有効）
     * 90 Turn Angle
     *   If the turning angle is less than this value, the 90 degree turning animation will be played (only the enemy turning control is effective). */
    unsigned char turn90Angle;

    /* 停止時アニメなし旋回角度[deg]
     *   旋回角度がこの値以下だと旋回アニメを再生しません[停止時]（ボス2足のみ有効）
     * Wait No Anim Turn Angle
     *   If the turning angle is less than this value, the turning animation will not be played [when stopped] (only valid for 2 boss legs) */
    unsigned char turnWaitNoAnimAngle;
} move_param_t;
