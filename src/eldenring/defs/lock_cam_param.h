#pragma once

typedef struct lock_cam_param_s {
    /* カメラ距離目標[m]
     *   カメラ距離目標
     * Camera Target Distance
     *   Camera distance target
     * Default Value  = 4 */
    float camDistTarget;

    /* X軸回転最小値[deg]
     *   X軸回転最小値
     * Rotation Range - Min X
     *   Minimum X-axis rotation
     * Default Value  = -40 */
    float rotRangeMinX;

    /* ロックX回転シフト率(0.0～1.0)
     *   ロックX回転シフト率
     * Lock Rotation X - Shift Ratio
     *   Lock X rotation shift rate
     * Default Value  = 0.6 */
    float lockRotXShiftRatio;

    /* キャラ基点オフセット(キャラ空間)
     *   キャラ基点オフセット
     * Character Origin - Offset Z
     *   Character base point offset
     * Default Value  = 1.42 */
    float chrOrgOffset_Y;

    /* キャラ範囲最大半径[m]
     *   キャラ範囲最大半径
     * Character Lock Range - Max Radius
     *   Maximum radius of character range
     * Default Value  = 15 */
    float chrLockRangeMaxRadius;

    /* 縦画角[deg]
     *   縦画角
     * Field of View - Vertical FOV
     *   Vertical angle of view
     * Default Value  = 43 */
    float camFovY;

    /* 暗闇用キャラ範囲最大半径[m]
     *   暗いところでのキャラのロック可能範囲
     * Character Lock Range - Max Radius (Darkness)
     *   Lockable range of characters in dark places
     * Default Value  = -1 */
    float chrLockRangeMaxRadius_forD;

    /* 真っ暗闇用キャラ範囲最大半径[m]
     *   真っ暗闇でのキャラのロック可能範囲
     * Character Lock Range - Max Radius (Total Darkness)
     *   Character lockable range in total darkness
     * Default Value  = -1 */
    float chrLockRangeMaxRadius_forPD;

    /* 近接攻撃自動捕捉 上限高さ[m]
     *   非ロックオン時の自動ロックオン判定高さ上限　近接
     * Attack Capture - Upper Limit Height
     *   Automatic lock-on judgment height upper limit when non-lock-on is close */
    float closeMaxHeight;

    /* 近接攻撃自動捕捉 下限高さ[m]
     *   非ロックオン時の自動ロックオン判定高さ下限　近接
     * Attack Capture - Lower Limit Height
     *   Automatic lock-on judgment height lower limit when not locked on Proximity */
    float closeMinHeight;

    /* 近接攻撃自動捕捉 角度範囲 左右[deg]
     *   非ロックオン時の自動ロックオン判定左右角度[deg]　近接
     * Attack Capture - Auto Acquisition - Angle Range Left
     *   Automatic lock-on judgment when non-lock-on Left / right angle [deg] Proximity */
    float closeAngRange;

    /* 近接攻撃自動捕捉 キャラ範囲最大半径[m]
     *   非ロックオン時の自動ロックオン判定距離　近接
     * Attack Capture - Auto Acquisition - Max Radius
     *   Automatic lock-on judgment distance when non-lock-on is close */
    float closeMaxRadius;

    /* 近接攻撃自動捕捉 暗闇用キャラ範囲最大半径[m]
     *   非ロックオン時の自動ロックオン判定距離_暗闇　近接
     * Attack Capture - Auto Acquisition - Max Radius (Darkness)
     *   Automatic lock-on judgment distance at non-lock-on _ darkness proximity */
    float closeMaxRadius_forD;

    /* 近接攻撃自動捕捉 真っ暗闇用キャラ範囲最大半径[m]
     *   非ロックオン時の自動ロックオン_真っ暗　近接
     * Attack Capture - Auto Acquisition - Max Radius (Total Darkness)
     *   Automatic lock-on when non-lock-on _ pitch black proximity */
    float closeMaxRadius_forPD;

    /* 弾丸自動捕捉 キャラ範囲最大半径[m]
     *   非ロックオン時の自動ロックオン判定距離　弾丸
     * Attack Capture - Bullet - Max Radius
     *   Automatic lock-on judgment distance when non-lock-on bullet */
    float bulletMaxRadius;

    /* 弾丸自動捕捉 暗闇用キャラ範囲最大半径[m]
     *   非ロックオン時の自動ロックオン判定距離_暗闇　弾丸
     * Attack Capture - Bullet - Max Radius (Dark)
     *   Automatic lock-on judgment distance at non-lock-on _ darkness bullet */
    float bulletMaxRadius_forD;

    /* 弾丸自動捕捉 真っ暗闇用キャラ範囲最大半径[m]
     *   非ロックオン時の自動ロックオン判定距離_真っ暗　弾丸
     * Attack Capture - Bullet - Max Radius (Pitch Dark
     *   Automatic lock-on judgment distance at non-lock-on _ pitch black bullet */
    float bulletMaxRadius_forPD;

    /* 弾丸自動捕捉 角度範囲 左右[deg]
     *   非ロックオン時の自動ロックオン左右角度　弾丸
     * Attack Capture - Bullet - Angle Range Left/Right
     *   Automatic lock-on left / right angle when non-lock-on bullet */
    float bulletAngRange;

    /* ロック条件を満たさなくてもロック継続する時間[s]
     *   ロック条件を満たさなくてもロック継続する時間(0.0で無効)
     * Lock Target Keep Time
     *   Time to continue locking even if the lock condition is not met (disabled at 0.0)
     * Default Value  = 2 */
    float lockTgtKeepTime;

    /* 通常用キャラ並進追尾率
     *   通常用キャラ並進追尾率(-1.0で無効)
     * Transition Chase Factor for Normal Character
     *   Normal character translation tracking rate (disabled at -1.0)
     * Default Value  = -1 */
    float chrTransChaseRateForNormal;

    /* パディング */
    char pad[48];
} lock_cam_param_t;
