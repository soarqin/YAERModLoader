#pragma once

typedef struct er_game_area_param_s {
    /* NT版出力から外すか
     *   ○をつけたパラメータをNT版パッケージでは除外します
     * Disable Param - Network Test
     *   Parameters marked with  are excluded in the NT version package. */
    unsigned char disableParam_NT:1;

    /* パッケージ出力用リザーブ1
     *   パッケージ出力用リザーブ1 */
    char disableParamReserve1:7;

    /* パッケージ出力用リザーブ2
     *   パッケージ出力用リザーブ2 */
    char disableParamReserve2[3];

    /* シングル時クリアボーナスソウル量
     *   エリアボスを倒したときに取得できるソウル量(シングルプレイ時)
     * Bonus Runes - Singleplayer
     *   Amount of soul that can be obtained when defeating an area boss (in single play) */
    unsigned int bonusSoul_single;

    /* マルチプレイ時クリアボーナスソウル量
     *   エリアボスを倒したときに取得できるソウル量(マルチプレイ時)
     * Bonus Runes - Multiplayer
     *   Amount of soul that can be obtained when defeating an area boss (during multiplayer) */
    unsigned int bonusSoul_multi;

    /* 人間性ドロップポイントカウント先頭フラグID
     *   人間性ドロップポイントを管理する為の先頭フラグID(20Bit使用)
     * Humanity Point Count Flag ID
     *   First flag ID for managing humanity drop points (using 20 Bit) */
    unsigned int humanityPointCountFlagIdTop;

    /* 人間性ドロップ必要ポイント1
     *   人間性を取得する為の閾値1
     * Humanity Drop Threshold [1]
     *   Threshold for acquiring humanity 1 */
    unsigned short humanityDropPoint1;

    /* 人間性ドロップ必要ポイント2
     *   人間性を取得する為の閾値2
     * Humanity Drop Threshold [2]
     *   Threshold 2 for acquiring humanity */
    unsigned short humanityDropPoint2;

    /* 人間性ドロップ必要ポイント3
     *   人間性を取得する為の閾値3
     * Humanity Drop Threshold [3]
     *   Threshold 3 for acquiring humanity */
    unsigned short humanityDropPoint3;

    /* 人間性ドロップ必要ポイント4
     *   人間性を取得する為の閾値4
     * Humanity Drop Threshold [4]
     *   Threshold 4 for acquiring humanity */
    unsigned short humanityDropPoint4;

    /* 人間性ドロップ必要ポイント5
     *   人間性を取得する為の閾値5
     * Humanity Drop Threshold [5]
     *   Threshold 5 for acquiring humanity */
    unsigned short humanityDropPoint5;

    /* 人間性ドロップ必要ポイント6
     *   人間性を取得する為の閾値6
     * Humanity Drop Threshold [6]
     *   Threshold 6 for acquiring humanity */
    unsigned short humanityDropPoint6;

    /* 人間性ドロップ必要ポイント7
     *   人間性を取得する為の閾値7
     * Humanity Drop Threshold [7]
     *   Threshold for acquiring humanity 7 */
    unsigned short humanityDropPoint7;

    /* 人間性ドロップ必要ポイント8
     *   人間性を取得する為の閾値8
     * Humanity Drop Threshold [8]
     *   Threshold for acquiring humanity 8 */
    unsigned short humanityDropPoint8;

    /* 人間性ドロップ必要ポイント9
     *   人間性を取得する為の閾値9
     * Humanity Drop Threshold [9]
     *   Threshold for acquiring humanity 9 */
    unsigned short humanityDropPoint9;

    /* 人間性ドロップ必要ポイント10
     *   人間性を取得する為の閾値10
     * Humanity Drop Threshold [10]
     *   Threshold 10 for acquiring humanity */
    unsigned short humanityDropPoint10;

    /* ソロ侵入ポイント加算値下限
     *   エリアボスを倒したときに加算するソロ侵入ポイントの最小値。
     * Min Invasion Spawns added after Boss Defeat
     *   The minimum value of solo intrusion points to be added when defeating an area boss. */
    unsigned int soloBreakInPoint_Min;

    /* ソロ侵入ポイント加算値上限
     *   エリアボスを倒したときに加算するソロ侵入ポイントの最大値。
     * Max Invasion Spawns added after Boss Defeat
     *   The maximum value of solo intrusion points to be added when defeating an area boss.
     * Default Value  = 10000 */
    unsigned int soloBreakInPoint_Max;

    /* ボス撃破済みフラグID(ホスト化時の目的表示用)
     *   このフラグがONの場合はホスト化時の目的設定のリストに表示しない。0の場合は常時表示。
     * Boss Defeat Flag - For Purpose List
     *   If this flag is ON, it will not be displayed in the list of purpose settings at the time of hosting. If it is 0, it is always displayed. */
    unsigned int defeatBossFlagId_forSignAimList;

    /* 目的表示フラグID
     * Display Purpose Flag ID */
    unsigned int displayAimFlagId;

    /* ボス発見フラグID
     * Discovered Boss Flag ID */
    unsigned int foundBossFlagId;

    /* 発見時テキストID
     * Discovered Boss Text ID
     * Default Value  = -1 */
    int foundBossTextId;

    /* 未発見時テキストID
     * Undiscovered Boss Text ID
     * Default Value  = -1 */
    int notFindBossTextId;

    /* ボス挑戦可能フラグID
     *   ボス挑戦可能フラグID。マルチプレイエリアパラの「侵入ポイント自動生成か」が○のときの侵入位置検索で目的のボスを選ぶ時にこのフラグがONのボスが対象になる。0の場合は常に対象になる。
     * Boss Challenge Flag ID
     *   Boss challengeable flag ID. When selecting the target boss in the intrusion position search when Is the intrusion point automatically generated? In the multiplayer area para is , the boss with this flag ON is targeted. If it is 0, it is always the target. */
    unsigned int bossChallengeFlagId;

    /* ボス撃破フラグID
     *   ボス撃破フラグID。マルチプレイエリアパラの「侵入ポイント自動生成か」が○のときの侵入位置検索で目的のボスを選ぶ時にこのフラグがOFFのボスが対象になる。
     * Boss Defeat Flag ID
     *   Boss defeat flag ID. When selecting the target boss in the intrusion position search when Is the intrusion point automatically generated? In the multiplayer area para is , the boss with this flag OFF is targeted. */
    unsigned int defeatBossFlagId;

    /* ボス位置_X座標
     *   ボス位置_X座標（指定したマップからの相対座標）。マルチプレイエリアパラの「侵入ポイント自動生成か」が○のときの侵入位置検索でホストとボス間の距離確認に使われる。
     * Boss Coordinate X
     *   Boss position_X coordinates (relative coordinates from the specified map). It is used to check the distance between the host and the boss in the intrusion position search when Is the intrusion point automatically generated? In the multiplayer area para. */
    float bossPosX;

    /* ボス位置_Y座標
     *   ボス位置_Y座標（指定したマップからの相対座標）。マルチプレイエリアパラの「侵入ポイント自動生成か」が○のときの侵入位置検索でホストとボス間の距離確認に使われる。
     * Boss Coordinate Y
     *   Boss position_Y coordinates (relative coordinates from the specified map). It is used to check the distance between the host and the boss in the intrusion position search when Is the intrusion point automatically generated? In the multiplayer area para. */
    float bossPosY;

    /* ボス位置_Z座標
     *   ボス位置_Z座標（指定したマップからの相対座標）。マルチプレイエリアパラの「侵入ポイント自動生成か」が○のときの侵入位置検索でホストとボス間の距離確認に使われる。
     * Boss Coordinate Z
     *   Boss position_Z coordinates (relative coordinates from the specified map). It is used to check the distance between the host and the boss in the intrusion position search when Is the intrusion point automatically generated? In the multiplayer area para. */
    float bossPosZ;

    /* ボス位置_エリア番号(mXX_00_00_00)
     *   ボス位置_エリア番号(mXX_00_00_00)。マルチプレイエリアパラの「侵入ポイント自動生成か」が○のときの侵入位置検索でホストとボス間の距離確認に使われる。
     * Map Area
     *   Boss position_area number (mXX_00_00_00). It is used to check the distance between the host and the boss in the intrusion position search when Is the intrusion point automatically generated? In the multiplayer area para. */
    unsigned char bossMapAreaNo;

    /* ボス位置_グリッドX番号(m00_XX_00_00)
     *   ボス位置_グリッドX番号(m00_XX_00_00)。マルチプレイエリアパラの「侵入ポイント自動生成か」が○のときの侵入位置検索でホストとボス間の距離確認に使われる。
     * Map Block
     *   Boss position_grid X number (m00_XX_00_00). It is used to check the distance between the host and the boss in the intrusion position search when Is the intrusion point automatically generated? In the multiplayer area para. */
    unsigned char bossMapBlockNo;

    /* ボス位置_グリッドZ番号(m00_00_XX_00)
     *   ボス位置_グリッドZ番号(m00_00_XX_00)。マルチプレイエリアパラの「侵入ポイント自動生成か」が○のときの侵入位置検索でホストとボス間の距離確認に使われる。
     * Map Region
     *   Boss position_grid Z number (m00_00_XX_00). It is used to check the distance between the host and the boss in the intrusion position search when Is the intrusion point automatically generated? In the multiplayer area para. */
    unsigned char bossMapMapNo;

    /* 予約領域
     *   予約領域 */
    char reserve[9];
} er_game_area_param_t;
