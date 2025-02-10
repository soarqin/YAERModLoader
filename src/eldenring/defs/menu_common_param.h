#pragma once

typedef struct menu_common_param_s {
    /* ソロプレイ死亡時フェードアウト開始時間[秒]
     *   ソロプレイ死亡時で「YOU DIED」表示後、何秒経過したらフェードアウトを開始するか
     * [YOU DIED] Fade Out Duration - Host
     *   How many seconds have passed after YOU DIED is displayed at the time of death of solo play to start fading out? */
    float soloPlayDeath_ToFadeOutTime;

    /* ホワイト、ブラックゴースト死亡時フェードアウト開始時間[秒]
     *   ホワイト、ブラックゴースト死亡時で「YOU DIED」表示後、何秒経過したらフェードアウトを開始するか
     * [YOU DIED] Fade Out Duration - Phnatom
     *   How many seconds have passed after YOU DIED is displayed when a white or black ghost dies to start fading out? */
    float partyGhostDeath_ToFadeOutTime;

    /* プレイヤー最大HPの上限
     *   HPゲージ表示の際に、リソースで用意されたゲージの長さの何％を使うかを算出するために使われます。
     * HP Bar - Visual Scale
     *   It is used to calculate what percentage of the gauge length provided by the resource is used when displaying the HP gauge. */
    int playerMaxHpLimit;

    /* プレイヤー最大MPの上限
     *   MPゲージ表示の際に、リソースで用意されたゲージの長さの何％を使うかを算出するために使われます。
     * FP Bar - Visual Scale
     *   It is used to calculate what percentage of the gauge length provided by the resource is used when displaying the MP gauge. */
    int playerMaxMpLimit;

    /* プレイヤー最大SPの上限
     *   SPゲージ表示の際に、リソースで用意されたゲージの長さの何％を使うかを算出するために使われます。
     * Stamina Bar - Visual Scale
     *   It is used to calculate what percentage of the gauge length provided by the resource is used when displaying the SP gauge. */
    int playerMaxSpLimit;

    /* アクションパネル切り替え判定_プレイヤー速度[m/sec]
     *   アクションパネル切り替え可能なプレイヤーの速度。この速度以下なら切り替え可能
     * Action Panel Change Threshold - Velocity
     *   Action panel Switchable player speed. Switchable if below this speed */
    float actionPanelChangeThreshold_Vel;

    /* アクションパネル切り替え判定_プレイヤー速度判定時間[sec]
     *   アクションパネル切り替え可能なプレイヤーの速度を出すための考慮時間。この時間の平均速度を使う(システム的に最大４秒)
     * Action Panel Change Threshold - Pass Time
     *   Action panel Consideration time to increase the speed of switchable players. Use the average speed of this time (systematically up to 4 seconds) */
    float actionPanelChangeThreshold_PassTime;

    /* キーガイドアイコンの上下位置
     *   キーガイドアイコンの上下位置(+:上, -:下)
     * Vertical Position of Key Guide Icon
     *   Vertical position of key guide icon (+ - top,- - bottom) */
    int kgIconVspace;

    /* カーソルの選択半径[px]
     *   カーソル位置がこの半径以内にあれば選択していることになる
     * World Map - Cursor Select Radius
     *   If the cursor position is within this radius, it means that it is selected.
     * Default Value  = 0.1 */
    float worldMapCursorSelectRadius;

    /* 予約
     *   (dummy8) */
    char reserved8[4];

    /* デカールオフセット（左右）
     *   デカールの表示位置オフセット左右方向
     * Decal Position Offset - X
     *   Decal display position offset left and right */
    int decalPosOffsetX;

    /* デカールオフセット（上下）
     *   デカールの表示位置オフセット上下方向
     * Decal Position Offset - Y
     *   Decal display position offset vertical direction */
    int decalPosOffsetY;

    /* 見つかりそうFE：Searchアイコンの表示時間[秒]
     *   見つかりそうFEのSearchアイコンがフェードインし始めてから、フェードアウトされ始めるまでの秒数
     * FE Search Icon Fade Time
     *   The number of seconds it takes for the FE Search icon to start fading in and then fading out. */
    float targetStateSearchDurationTime;

    /* 見つかりそうFE：Battleアイコンの表示時間[秒]
     *   見つかりそうFEのBattleアイコンがフェードインし始めてから、フェードアウトされ始めるまでの秒数
     * FE Battle Icon Fade Time
     *   The number of seconds it takes for the FE Battle icon to start fading in and then fading out. */
    float targetStateBattleDurationTime;

    /* カーソルの移動スピード[px/sec]
     *   スムーズに移動するときの移動スピード
     * World Map - Cursor Speed
     *   Movement speed when moving smoothly [px]
     * Default Value  = 1 */
    float worldMapCursorSpeed;

    /* カーソルの１回目の移動距離[px]
     *   最初の入力のときに、カッと一度だけ移動する距離
     * World Map - Cursor First Distance
     *   Distance to move only once at the first input [px]
     * Default Value  = 1 */
    float worldMapCursorFirstDistance;

    /* カーソルの1回目の移動の遅延時間[sec]
     *   最初の入力のときに、カッと一度だけ移動するときにかかる時間
     * World Map - Cursor First Delay
     *   The time it takes to move only once at the first input [sec]
     * Default Value  = 0.01 */
    float worldMapCursorFirstDelay;

    /* カーソルの移動までのウェイト[sec]
     *   入力してから、スムーズに移動するまでの待機時間
     * World Map - Cursor Wait Time
     *   Waiting time from input to smooth movement [sec] */
    float worldMapCursorWaitTime;

    /* カーソルのスナップ半径[px]
     *   この半径よりも近くにカーソルを移動すると吸着を開始する（スナップモード用）
     * World Map - Cursor Snap Radius
     *   Move the cursor closer than this radius to start adsorption (for snap mode) [px]
     * Default Value  = 0.1 */
    float worldMapCursorSnapRadius;

    /* カーソルのスナップ時間[sec]
     *   吸着を開始して、完了するまでにかかる時間
     * World Map - Cursor Snap Time
     *   The time it takes to start and complete adsorption [sec]
     * Default Value  = 0.01 */
    float worldMapCursorSnapTime;

    /* アイテム取得ログ：１行の表示時間[sec]
     *   １行分のログを追加してフェードアウトするまでの時間。行ごとにタイマーがある
     * Item Get Log Alive Time
     *   Time to add one line of log and fade out. There is a timer for each line [sec]
     * Default Value  = 0.01 */
    float itemGetLogAliveTime;

    /* プレイヤー最大SA（体幹値）の上限
     *   SAゲージ表示の際に、リソースで用意されたゲージの長さの何％を使うかを算出するために使われます。
     * Player Max Poise Guage Length
     *   It is used to calculate what percentage of the gauge length provided by the resource is used when displaying the SA gauge. */
    int playerMaxSaLimit;

    /* 地下地図切り替え可能イベントフラグID
     *   地下地図に切り替え可能かを管理するイベントフラグIDを指定する。このイベントフラグIDがONのときに、地下地図への切り替えが可能になる
     * World Map - Underground Layer Event Flag ID
     *   Specify the event flag ID that manages whether it is possible to switch to the underground map. When this event flag ID is ON, it is possible to switch to the underground map. */
    unsigned int worldMap_IsChangeableLayerEventFlagId;

    /* 踏破範囲の追加解禁距離[m]
     *   プレイヤーを中心として4方向へ拡張する距離(m)。この範囲を踏破したことにする
     * World Map - Travel Margin
     *   Distance (m) that extends in four directions around the player. I decided to break through this range */
    float worldMap_TravelMargin;

    /* スクロール前後の待機時間[sec]
     *   運営告知の長い文章をスクロールする前後に待機する秒数。例えば3秒なら前と後ろとで合計6秒待機する
     * System Announcement - Scroll Buffer Time
     *   The number of seconds to wait before and after scrolling through the long text of the operation announcement. For example, if it is 3 seconds, wait for a total of 6 seconds before and after. */
    float systemAnnounceScrollBufferTime;

    /* スクロールする速度[px/sec]
     *   運営告知の長い文章をスクロールするときのスクロール速度（ピクセル/秒）。画面サイズに依存しない。メニュー全体を1920x1080として考える
     * System Announcement - Scroll Speed
     *   Scrolling speed (pixels / second) when scrolling long sentences in the operation announcement. It does not depend on the screen size. Think of the entire menu as 1920x1080
     * Default Value  = 100 */
    int systemAnnounceScrollSpeed;

    /* スクロールしないときの表示時間[sec]
     *   運営告知のスクロールを必要としない短い文章だったときに表示する秒数
     * System Announcement - No Scroll Wait Time
     *   The number of seconds to display when it is a short sentence that does not require scrolling of the operation announcement */
    float systemAnnounceNoScrollWaitTime;

    /* スクロールする回数
     *   運営告知の長い文章をスクロールするときに繰り返す回数
     * System Announcement - Scroll Count
     *   Number of times to repeat when scrolling long sentences of management announcement
     * Default Value  = 1 */
    unsigned char systemAnnounceScrollCount;

    /* 予約
     *   (dummy8) */
    char reserved17[3];

    /* 表示距離_メモマーカー[m]
     *   コンパスに表示するメモマーカーの表示距離[m]。この距離よりも近いものは表示される
     * Compass Memo Display Distance
     *   Display distance [m] of the memo marker displayed on the compass. Anything closer than this distance will be displayed
     * Default Value  = 50 */
    float compassMemoDispDistance;

    /* 表示距離_篝火[m]
     *   コンパスに表示する篝火の表示距離[m]。この距離よりも近いものは表示される
     * Compass Bonfire Display Distance
     *   The display distance of the bonfire displayed on the compass [m]. Anything closer than this distance will be displayed
     * Default Value  = 50 */
    float compassBonfireDispDistance;

    /* 目的地マーカーのゴール判定距離[m]
     *   目的地マーカーのゴール判定距離[m]。この距離よりも近付いたときに目的地マーカーは消える
     * Destination Marrker Threshold
     *   Goal judgment distance [m] of the destination marker. The destination marker disappears when you get closer than this distance */
    float markerGoalThreshold;

    /* 彩度・明度スライダーの移動量[%/sec]
     *   カラーコントロールの彩度・明度スライダーの移動量[%/sec]。それぞれの値を0%～100%としたときに1秒で移動する最大量。アナログスティックで操作するため、入力値で割合になる
     * Saturation/Brightness Slider Step
     *   Amount of movement of the saturation / brightness slider of the color control [% / sec]. Maximum amount to move in 1 second when each value is 0% to 100%. Since it is operated with an analog stick, it becomes a ratio by the input value.
     * Default Value  = 10 */
    float svSliderStep;

    /* OPムービー前のウェイト[sec]
     *   OPムービー再生前のウェイト時間。＞SEQ 15261
     * Pre-opening Movie - Wait Time
     *   Wait time before playing the OP movie. > SEQ 15261 */
    float preOpeningMovie_WaitSec;

    /* キーガイドアイコンのスケール[%]
     *   キーガイドアイコンのスケール値。100%がテクスチャサイズそのまま
     * Key Guide Icon - Scale
     *   The scale value of the key guide icon. 100% is the texture size as it is
     * Default Value  = 100 */
    float kgIconScale;

    /* パッド操作一覧用のキーガイドアイコンのスケール[%]
     *   パッド操作一覧用のキーガイドアイコンのスケール値。100%がテクスチャサイズそのまま
     * Key Guide Icon for Table - Scale
     *   Scale value of the key guide icon for the pad operation list. 100% is the texture size as it is
     * Default Value  = 100 */
    float kgIconScale_forTable;

    /* パッド操作一覧用のキーガイドアイコンの上下位置
     *   パッド操作一覧用のキーガイドアイコンの上下位置(+:上, -:下)
     * Key Guide Icon for Table - Vertical Position
     *   Vertical position of the key guide icon for the pad operation list (+ - top,- - bottom) */
    int kgIconVspace_forTable;

    /* キーコンフィグ用のキーガイドアイコンのスケール[%]
     *   キーコンフィグ用のキーガイドアイコンのスケール値。100%がテクスチャサイズそのまま
     * Key Guide Icon for Key Config - Scale
     *   The scale value of the key guide icon for the key config. 100% is the texture size as it is
     * Default Value  = 100 */
    float kgIconScale_forConfig;

    /* キーコンフィグ用のキーガイドアイコンの上下位置
     *   キーコンフィグ用のキーガイドアイコンの上下位置(+:上, -:下)
     * Key Guide Icon for Key Config - Vertical Position
     *   Vertical position of key guide icon for key config (+ - top,- - bottom) */
    int kgIconVspace_forConfig;

    /* 未探索マスク_探索済み範囲[m]
     *   未探索マスクを探索済みにする範囲[m]（半径）。プレイヤーを中心とした円形を探索済みとする
     * World Map Search Radius
     *   Range [m] (radius) that makes unsearched masks searched. It is assumed that the circle centered on the player has been searched.
     * Default Value  = 256 */
    float worldMap_SearchRadius;

    /* トースト表示時間[sec]
     *   チュートリアル（トースト通知）の表示時間[sec]。この時間が経過したら自動的に閉じられる
     * Tutorial Display Time
     *   Tutorial (toast notification) display time [sec]. It will be closed automatically after this time has passed
     * Default Value  = 3 */
    float tutorialDisplayTime;

    /* 表示距離_協力/救援ゲスト側：ホスト
     *   コンパスに表示する他プレイヤー（味方ホスト）の表示距離[m]。この距離以上離れているとコンパスに表示される
     * Compass Friendly Phantom Display Distance
     *   Display distance [m] of other players (friendly hosts) to be displayed on the compass. If you are more than this distance, it will be displayed on the compass. */
    float compassFriendHostInnerDistance;

    /* 表示距離_敵対ゲスト側：ホスト
     *   コンパスに表示する他プレイヤー（敵ホスト）の表示距離[m]。この距離以上離れているとコンパスに表示される
     * Compass Hostile Phantom Display Distance
     *   Display distance [m] of other players (enemy hosts) displayed on the compass. If you are more than this distance, it will be displayed on the compass. */
    float compassEnemyHostInnerDistance;

    /* 表示距離_ホスト/協力/救援ホスト側：協力/救援ゲスト
     *   コンパスに表示する他プレイヤー（味方ゲスト）の表示距離[m]。この距離以上離れているとコンパスに表示される
     * Compass Guest Phantom Display Distance
     *   Display distance [m] of other players (friendly guests) to be displayed on the compass. If you are more than this distance, it will be displayed on the compass. */
    float compassFriendGuestInnerDistance;

    /* カットシーンのキーガイド表示時間[秒]
     *   カットシーンスキップの事前入力があってからキーガイドを表示し続ける時間。キーガイドを表示中しかスキップ入力は受け付けないため、スキップ入力受付時間とも言える
     * Cutscene Key Guide - Display Time
     *   The amount of time that the key guide will continue to be displayed after the cutscene skip has been pre-entered. Since skip input is accepted only while the key guide is displayed, it can be said that it is the skip input acceptance time.
     * Default Value  = 5 */
    float cutsceneKeyGuideAliveTime;

    /* HPゲージ：常に表示する割合[%]
     *   [HUD:Auto設定]HP割合。HP割合がこの数値以下なら、HPゲージを常に表示する。割合と現在値はOR条件（どちらかを満たせば表示）
     * Auto HUD - HP Ratio to display HUD
     *   [HUD - Auto setting] HP ratio. If the HP ratio is below this value, the HP gauge will always be displayed. Percentage and current value are OR conditions (displayed if either is satisfied)
     * Default Value  = -1 */
    float autoHideHpThresholdRatio;

    /* HPゲージ：常に表示する現在値
     *   [HUD:Auto設定]HP現在値。HP現在値がこの数値以下なら、HPゲージを常に表示する。割合と現在値はOR条件（どちらかを満たせば表示）
     * Auto HUD - Display HUD when below X HP
     *   [HUD - Auto setting] HP current value. If the current HP value is less than or equal to this value, the HP gauge will always be displayed. Percentage and current value are OR conditions (displayed if either is satisfied)
     * Default Value  = -1 */
    int autoHideHpThresholdValue;

    /* MPゲージ：常に表示する割合[%]
     *   [HUD:Auto設定]MP割合。MP割合がこの数値以下なら、MPゲージを常に表示する。割合と現在値はOR条件（どちらかを満たせば表示）
     * Auto HUD - FP Ratio to display HUD
     *   [HUD - Auto setting] MP ratio. If the MP ratio is below this value, the MP gauge is always displayed. Percentage and current value are OR conditions (displayed if either is satisfied)
     * Default Value  = -1 */
    float autoHideMpThresholdRatio;

    /* MPゲージ：常に表示する現在値
     *   [HUD:Auto設定]MP現在値。MP現在値がこの数値以下なら、MPゲージを常に表示する。割合と現在値はOR条件（どちらかを満たせば表示）
     * Auto HUD - Display HUD when below X FP
     *   [HUD - Auto setting] MP current value. If the current MP value is less than or equal to this value, the MP gauge is always displayed. Percentage and current value are OR conditions (displayed if either is satisfied)
     * Default Value  = -1 */
    int autoHideMpThresholdValue;

    /* SPゲージ：常に表示する割合[%]
     *   [HUD:Auto設定]SP割合。SP割合がこの数値以下なら、SPゲージを常に表示する。割合と現在値はOR条件（どちらかを満たせば表示）
     * Auto HUD - Stamina Ratio to display HUD
     *   [HUD - Auto setting] SP ratio. If the SP ratio is less than or equal to this value, the SP gauge is always displayed. Percentage and current value are OR conditions (displayed if either is satisfied)
     * Default Value  = -1 */
    float autoHideSpThresholdRatio;

    /* SPゲージ：常に表示する現在値
     *   [HUD:Auto設定]SP現在値。SP現在値がこの数値以下なら、SPゲージを常に表示する。割合と現在値はOR条件（どちらかを満たせば表示）
     * Auto HUD - Display HUD when below X Stamina
     *   [HUD - Auto setting] SP current value. If the current SP value is less than or equal to this value, the SP gauge is always displayed. Percentage and current value are OR conditions (displayed if either is satisfied)
     * Default Value  = -1 */
    int autoHideSpThresholdValue;

    /* ズームアニメーション時間[秒]
     *   世界地図：ズームアニメーションをする時間[秒]
     * World Map Zoom Animation Time
     *   World map - Time to zoom animation [seconds]
     * Default Value  = 0.5 */
    float worldMapZoomAnimationTime;

    /* 最小アイコン表示倍率
     *   世界地図：ズームステップ0のときの地図ポイントアイコンの表示倍率(0.0～1.0)。ズームステップ2のときに等倍(1.0)。そこから拡大率に合わせてアイコン倍率も補間される
     * World Map Icon Minimum Scale
     *   World map - Display magnification of the map point icon at zoom step 0 (0.0 to 1.0). 1x (1.0) at zoom step 2. From there, the icon magnification is also interpolated according to the enlargement ratio.
     * Default Value  = 1 */
    float worldMapIconScaleMin;

    /* 地図ポイント単位踏破範囲解禁時の追加解禁距離[m]
     *   世界地図：地図ポイント単位踏破範囲解禁時の追加解禁距離[m]。遠見台など地図ポイントが解禁されたときに踏破範囲を解禁する。地図ポイントを中心に4方向に追加で拡張する距離
     * World Map - Travel Margin Point
     *   World map - Additional ban distance [m] when the ban is lifted in map point units. When the ban on map points such as the distant view stand is lifted, the ban on the traversal range will be lifted. Distance to be additionally extended in 4 directions around the map point */
    float worldMap_TravelMargin_Point;

    /* 表示可能領域（左端）
     *   敵HPゲージの中心座標がどこまで左端にいけるか。中心座標なのでゲージ本体のサイズも含む
     * Enemy HP Guage - Max Left Justification
     *   How far can the center coordinates of the enemy HP gauge go to the left end? Since it is the center coordinate, the size of the gauge body is included. */
    unsigned short enemyTagSafeLeft;

    /* 表示可能領域（右端）
     *   敵HPゲージの中心座標がどこまで右端にいけるか。中心座標なのでゲージ本体のサイズも含む
     * Enemy HP Guage - Max Right Justification
     *   How far can the center coordinates of the enemy HP gauge go to the right end? Since it is the center coordinate, the size of the gauge body is included.
     * Default Value  = 1920 */
    unsigned short enemyTagSafeRight;

    /* 表示可能領域（上端）
     *   敵HPゲージの中心座標がどこまで上端にいけるか。中心座標なのでゲージ本体のサイズも含む
     * Enemy HP Guage - Max Top Justification
     *   How far can the center coordinates of the enemy HP gauge go to the upper end? Since it is the center coordinate, the size of the gauge body is included. */
    unsigned short enemyTagSafeTop;

    /* 表示可能領域（下端）
     *   敵HPゲージの中心座標がどこまで下端にいけるか。中心座標なのでゲージ本体のサイズも含む
     * Enemy HP Guage - Max Bottom Justification
     *   How far can the center coordinates of the enemy HP gauge go to the lower end? Since it is the center coordinate, the size of the gauge body is included.
     * Default Value  = 1080 */
    unsigned short enemyTagSafeBottom;

    /* 表示回復量の閾値
     *   回復時にPC馬HPゲージを表示するかの閾値。「一度に一定値以上増加したらHPバーを表示する」の”一定値”
     * HP Threshold to display Horse HP
     *   Threshold for displaying the PC horse HP gauge at the time of recovery. Constant value of Display HP bar when it increases more than a certain value at a time */
    unsigned int pcHorseHpRecoverDispThreshold;

    unsigned char unknown_0xe0;

    unsigned char unknown_0xe1;

    unsigned char unknown_0xe2;

    unsigned char unknown_0xe3;

    unsigned char unknown_0xe4;

    unsigned char unknown_0xe5;

    unsigned char unknown_0xe6;

    unsigned char unknown_0xe7;

    unsigned char unknown_0xe8;

    unsigned char unknown_0xe9;

    unsigned char unknown_0xea;

    unsigned char unknown_0xeb;

    unsigned char unknown_0xec;

    unsigned char unknown_0xed;

    unsigned char unknown_0xee;

    /* 予約
     *   (dummy8) */
    char reserved33[17];
} menu_common_param_t;
