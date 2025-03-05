#pragma once

typedef struct er_play_region_param_s {
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

    /* 簡易マッチエリアID
     *   簡易マッチエリアID
     * Match Area ID
     *   Simple match area ID */
    int matchAreaId;

    /* マルチプレイ開始制限イベントフラグID
     *   マルチプレイ開始制限イベントフラグID
     * Multiplayer Start Limit - Event Flag ID
     *   Multiplayer start limit event flag ID */
    unsigned int multiPlayStartLimitEventFlagId;

    /* その他霊侵入不可能距離
     *   その他霊侵入不可能距離。ホスト位置から「その他霊侵入不可能距離」～「その他霊侵入範囲上限」以内の侵入ポイントを対象に侵入位置検索を行う。
     * Disable Intrusion if Other Ghost In Range
     *   Other distances that cannot be invaded by spirits. The intrusion position is searched for the intrusion points within the other ghost invasion impossible distance to the other ghost invasion range upper limit from the host position. */
    float otherDisableDistance;

    /* PC位置セーブ制限イベントフラグID
     *   PC位置セーブ制限イベントフラグID　（フラグON：PC位置セーブ有効　フラグOFF：PC位置セーブ無効　0：PC位置セーブ常に有効）
     * Player Position Save Limit - Event Flag ID
     *   PC position save restriction event flag ID (flag ON - PC position save valid flag OFF - PC position save invalid 0 - PC position save always valid) */
    unsigned int pcPositionSaveLimitEventFlagId;

    /* ボスエリアID
     *   このIDが同じものを設定された領域同士は、同一のボスエリアとして扱う。
     * Boss Area ID
     *   Areas with the same ID are treated as the same boss area. */
    unsigned int bossAreaId;

    /* NPC白霊召喚儀式の召還NPCのエンティティIDの自由枠ID
     *   NPC白霊召喚儀式の召還NPCのエンティティIDとして使われる自由枠IDの先頭
     * White Phantom Entity ID - Free Frame
     *   NPC White Spirit Summon Ritual Summon The beginning of the free frame ID used as the NPC's entity ID
     * Default Value  = -1 */
    short cultNpcWhiteGhostEntityId_byFree;

    /* マップ守護領域か？
     *   マップ守護領域の枠の増減にするか
     * Is Map Guardian Region
     *   Whether to increase or decrease the frame of the map protection area */
    unsigned char bMapGuradianRegion;

    /* 黄衣の翁サイン領域か？
     *   黄衣の翁サイン領域か？
     * Is Yellow Monk Region
     *   Is it the old man sign area of yellow robe? */
    unsigned char bYellowCostumeRegion:1;

    /* 制限するフラグ状態
     *   「マルチプレイ開始制限イベントフラグID」の制限を行うフラグ状態
     * Target Flag State - Multiplayer Start Limit ID [1]
     *   Flag state that limits multiplayer start restriction event flag ID
     * Default Value  = 1 */
    unsigned char multiPlayStartLimitEventFlagId_targetFlagState:1;

    /* 制限するフラグ状態
     *   「侵入制限イベントフラグID1」の制限を行うフラグ状態
     * Target Flag State - Invasion Start Limit ID [1]
     *   Flag state that limits intrusion restriction event flag ID1
     * Default Value  = 1 */
    unsigned char breakInLimitEventFlagId_1_targetFlagState:1;

    /* 制限するフラグ状態
     *   「白サイン制限イベントフラグID1」の制限を行うフラグ状態
     * Target Flag State - White Sign Start Limit ID [1]
     *   Flag state that limits white sign restriction event flag ID1
     * Default Value  = 1 */
    unsigned char whiteSignLimitEventFlagId_1_targetFlagState:1;

    /* 制限するフラグ状態
     *   「赤サイン制限イベントフラグID1」の制限を行うフラグ状態
     * Target Flag State - Red Sign Start Limit ID [1]
     *   Flag state that limits red sign limit event flag ID1
     * Default Value  = 1 */
    unsigned char redSignLimitEventFlagId_1_targetFlagState:1;

    /* 制限するフラグ状態
     *   「侵入制限イベントフラグID2」の制限を行うフラグ状態
     * Target Flag State - Invasion Start Limit ID [2]
     *   Flag state that limits intrusion restriction event flag ID2
     * Default Value  = 1 */
    unsigned char breakInLimitEventFlagId_2_targetFlagState:1;

    /* 制限するフラグ状態
     *   「侵入制限イベントフラグID3」の制限を行うフラグ状態
     * Target Flag State - Invasion Start Limit ID [3]
     *   Flag state that limits intrusion restriction event flag ID3
     * Default Value  = 1 */
    unsigned char breakInLimitEventFlagId_3_targetFlagState:1;

    /* 制限するフラグ状態
     *   「白サイン制限イベントフラグID2」の制限を行うフラグ状態
     * Target Flag State - White Sign Start Limit ID [2]
     *   Flag state that limits white sign restriction event flag ID2
     * Default Value  = 1 */
    unsigned char whiteSignLimitEventFlagId_2_targetFlagState:1;

    /* ワープアイテム許可篝火ID1
     *   ワープアイテムの使用を許可する判定に使う篝火のエンティティID1
     * Warp Item Usage Permitted - Bonfire ID [1]
     *   Bonfire entity ID1 used to determine whether to allow the use of warp items */
    unsigned int warpItemUsePermitBonfireId_1;

    /* ワープアイテム許可篝火ID2
     *   ワープアイテムの使用を許可する判定に使う篝火のエンティティID2
     * Warp Item Usage Permitted - Bonfire ID [2]
     *   Bonfire entity ID 2 used to determine permission to use warp items */
    unsigned int warpItemUsePermitBonfireId_2;

    /* ワープアイテム許可篝火ID3
     *   ワープアイテムの使用を許可する判定に使う篝火のエンティティID3
     * Warp Item Usage Permitted - Bonfire ID [3]
     *   Bonfire entity ID 3 used to determine permission to use warp items */
    unsigned int warpItemUsePermitBonfireId_3;

    /* ワープアイテム許可篝火ID4
     *   ワープアイテムの使用を許可する判定に使う篝火のエンティティID4
     * Warp Item Usage Permitted - Bonfire ID [4]
     *   Bonfire entity ID 4 used to determine permission to use warp items */
    unsigned int warpItemUsePermitBonfireId_4;

    /* ワープアイテム許可篝火ID5
     *   ワープアイテムの使用を許可する判定に使う篝火のエンティティID5
     * Warp Item Usage Permitted - Bonfire ID [5]
     *   Bonfire entity ID 5 used to determine permission to use warp items */
    unsigned int warpItemUsePermitBonfireId_5;

    /* ワープアイテム禁止イベントフラグID1
     *   ワープアイテムの使用禁止を判定するイベントフラグID1。ワープアイテム許可篝火IDによる判定より優先度が上
     * Warp Item Prohibition - Event Flag ID [1]
     *   Event flag ID 1 to determine the prohibition of warp items. Warp item permission Higher priority than judgment by bonfire ID */
    unsigned int warpItemProhibitionEventFlagId_1;

    /* ワープアイテム禁止イベントフラグID2
     *   ワープアイテムの使用禁止を判定するイベントフラグID2。ワープアイテム許可篝火IDによる判定より優先度が上
     * Warp Item Prohibition - Event Flag ID [2]
     *   Event flag ID 2 to determine the prohibition of warp items. Warp item permission Higher priority than judgment by bonfire ID */
    unsigned int warpItemProhibitionEventFlagId_2;

    /* ワープアイテム禁止イベントフラグID3
     *   ワープアイテムの使用禁止を判定するイベントフラグID3。ワープアイテム許可篝火IDによる判定より優先度が上
     * Warp Item Prohibition - Event Flag ID [3]
     *   Event flag ID 3 to determine the prohibition of warp items. Warp item permission Higher priority than judgment by bonfire ID */
    unsigned int warpItemProhibitionEventFlagId_3;

    /* ワープアイテム禁止イベントフラグID4
     *   ワープアイテムの使用禁止を判定するイベントフラグID4。ワープアイテム許可篝火IDによる判定より優先度が上
     * Warp Item Prohibition - Event Flag ID [4]
     *   Event flag ID 4 to determine the prohibition of warp items. Warp item permission Higher priority than judgment by bonfire ID */
    unsigned int warpItemProhibitionEventFlagId_4;

    /* ワープアイテム禁止イベントフラグID5
     *   ワープアイテムの使用禁止を判定するイベントフラグID5。ワープアイテム許可篝火IDによる判定より優先度が上
     * Warp Item Prohibition - Event Flag ID [5]
     *   Event flag ID 5 to determine the prohibition of warp items. Warp item permission Higher priority than judgment by bonfire ID */
    unsigned int warpItemProhibitionEventFlagId_5;

    /* 血痕・死亡幻影有効
     *   血痕・死亡幻影有効
     * Enable Bloodstain
     *   Effective bloodstain / death illusion
     * Default Value  = 1 */
    unsigned char enableBloodstain:1;

    /* 血文字有効
     *   血文字有効
     * Enable Blood Message
     *   Blood character valid
     * Default Value  = 1 */
    unsigned char enableBloodMessage:1;

    /* 幻影有効
     *   幻影有効
     * Enable Ghost
     *   Phantom effective
     * Default Value  = 1 */
    unsigned char enableGhost:1;

    /* 地図表示用_表示設定M00
     *   地図M00で表示するか
     * Display Mask M00
     *   Whether to display on map M00 */
    unsigned char dispMask00:1;

    /* 地図表示用_表示設定M01
     *   地図M01で表示するか
     * Display Mask M01
     *   Whether to display on map M01 */
    unsigned char dispMask01:1;

    /* 制限するフラグ状態
     *   「白サイン制限イベントフラグID3」の制限を行うフラグ状態
     * Target Flag State - White Sign Start Limit ID [3]
     *   Flag state that limits white sign restriction event flag ID3
     * Default Value  = 1 */
    unsigned char whiteSignLimitEventFlagId_3_targetFlagState:1;

    /* 制限するフラグ状態
     *   「赤サイン制限イベントフラグID2」の制限を行うフラグ状態
     * Target Flag State - Red Sign Start Limit ID [2]
     *   Flag state that limits red sign limit event flag ID2
     * Default Value  = 1 */
    unsigned char redSignLimitEventFlagId_2_targetFlagState:1;

    /* 制限するフラグ状態
     *   「赤サイン制限イベントフラグID3」の制限を行うフラグ状態
     * Target Flag State - Red Sign Start Limit ID [3]
     *   Flag state that limits red sign limit event flag ID3
     * Default Value  = 1 */
    unsigned char redSignLimitEventFlagId_3_targetFlagState:1;

    /* 侵入ポイント自動生成か
     *   侵入ポイント自動生成か。○にした場合は自動生成された侵入ポイント用のロジックで侵入位置を検索。
     * Is Automatic Invasion Point
     *   Is it an intrusion point automatic generation? If it is set to , the intrusion position is searched by the automatically generated logic for the intrusion point. */
    unsigned char isAutoIntrudePoint:1;

    unsigned char unknown_0x45_1:1;

    char pad1:6;

    char pad2[2];

    /* 黄衣の翁ホスト制限イベントフラグ
     *   黄衣の翁ホスト制限イベントフラグ：このフラグがONになると黄衣の翁のホストとしてのマルチプレイが禁止される。ブロッククリアフラグを入れる想定。0：制限しない
     * Block Yellow Monk Multiplayer - Event Flag ID
     *   Yellow Coat Host Restriction Event Flag - When this flag is turned on, multiplayer as a host of Yellow Coat is prohibited. It is assumed that the block clear flag will be inserted. 0 - No limit */
    unsigned int multiPlayHASHostLimitEventFlagId;

    /* その他霊侵入範囲上限
     *   その他霊侵入範囲上限。ホスト位置から「その他霊侵入不可能距離」～「その他霊侵入範囲上限」以内の侵入ポイントを対象に侵入位置検索を行う。
     * Other Ghost Invasion Range - Max Limit
     *   Other ghost invasion range upper limit. The intrusion position is searched for the intrusion points within the other ghost invasion impossible distance to the other ghost invasion range upper limit from the host position.
     * Default Value  = 1000 */
    float otherMaxDistance;

    /* サイン溜まり解放イベントフラグID
     *   サイン溜まり解放イベントフラグID
     * Summoning Pool Open - Event Flag ID
     *   Sign accumulation release event flag ID */
    unsigned int signPuddleOpenEventFlagId;

    /* 地図表示用_エリア番号（mXX_00_00_00）
     *   エリア番号（mXX_00_00_00）。地図メニューでの表示位置を指定するためのデータ
     * Map Area
     *   Area number (mXX_00_00_00). Data for specifying the display position in the map menu */
    unsigned char areaNo;

    /* 地図表示用_グリッドX番号（m00_XX_00_00）
     *   グリッドX番号（m00_XX_00_00）。地図メニューでの表示位置を指定するためのデータ
     * Map Block
     *   Grid X number (m00_XX_00_00). Data for specifying the display position in the map menu */
    unsigned char gridXNo;

    /* 地図表示用_グリッドZ番号（m00_00_XX_00）
     *   グリッドZ番号（m00_00_XX_00）。地図メニューでの表示位置を指定するためのデータ
     * Map Region
     *   Grid Z number (m00_00_XX_00). Data for specifying the display position in the map menu */
    unsigned char gridZNo;

    char pad4[1];

    /* 地図表示用_X座標
     *   X座標（指定したマップからの相対座標）。地図メニューでの表示位置を指定するためのデータ
     * Coordinate - X
     *   X coordinates (relative coordinates from the specified map). Data for specifying the display position in the map menu */
    float posX;

    /* 地図表示用_Y座標
     *   Y座標（指定したマップからの相対座標）。地図メニューでの表示位置を指定するためのデータ。実際には使われていないがXYZ一揃えにしておく
     * Coordinate - Y
     *   Y coordinates (relative coordinates from the specified map). Data for specifying the display position in the map menu. Not actually used, but keep XYZ aligned */
    float posY;

    /* 地図表示用_Z座標
     *   Z座標（指定したマップからの相対座標）。地図メニューでの表示位置を指定するためのデータ
     * Coordinate - Z
     *   Z coordinates (relative coordinates from the specified map). Data for specifying the display position in the map menu */
    float posZ;

    /* 侵入制限イベントフラグID1
     *   侵入制限イベントフラグID1
     * Invasion Restriction - Event Flag ID [1]
     *   Intrusion restriction event flag ID1 */
    unsigned int breakInLimitEventFlagId_1;

    /* 白サイン制限イベントフラグID1
     *   白サイン制限イベントフラグID1
     * Summon Restriction - Event Flag ID [1]
     *   White sign limit event flag ID1 */
    unsigned int whiteSignLimitEventFlagId_1;

    /* サイン溜まり登録制限イベントフラグID
     *   サイン溜まり登録制限イベントフラグID　（フラグON：サイン溜まり登録を許可　フラグOFF：サイン溜まり登録を禁止　0：サイン溜まり登録を常に許可）
     * Summoning Pool Restriction - Event Flag ID
     *   Sign accumulation registration restriction Event flag ID (Flag ON - Sign accumulation registration is permitted Flag OFF - Sign accumulation registration is prohibited 0 - Sign accumulation registration is always permitted) */
    unsigned int matchAreaSignCreateLimitEventFlagId;

    /* マルチ目的ID01
     *   目的設定時にリストに表示するマルチ目的ID
     * Sign Aim ID [1]
     *   Multi-purpose ID to be displayed in the list when setting the purpose */
    unsigned int signAimId_1;

    /* マルチ目的ID02
     *   目的設定時にリストに表示するマルチ目的ID
     * Sign Aim ID [2]
     *   Multi-purpose ID to be displayed in the list when setting the purpose */
    unsigned int signAimId_2;

    /* マルチ目的ID03
     *   目的設定時にリストに表示するマルチ目的ID
     * Sign Aim ID [3]
     *   Multi-purpose ID to be displayed in the list when setting the purpose */
    unsigned int signAimId_3;

    /* マルチ目的ID04
     *   目的設定時にリストに表示するマルチ目的ID
     * Sign Aim ID [4]
     *   Multi-purpose ID to be displayed in the list when setting the purpose */
    unsigned int signAimId_4;

    /* マルチ目的ID05
     *   目的設定時にリストに表示するマルチ目的ID
     * Sign Aim ID [5]
     *   Multi-purpose ID to be displayed in the list when setting the purpose */
    unsigned int signAimId_5;

    /* マルチ目的ID06
     *   目的設定時にリストに表示するマルチ目的ID
     * Sign Aim ID [6]
     *   Multi-purpose ID to be displayed in the list when setting the purpose */
    unsigned int signAimId_6;

    /* マルチ目的ID07
     *   目的設定時にリストに表示するマルチ目的ID
     * Sign Aim ID [7]
     *   Multi-purpose ID to be displayed in the list when setting the purpose */
    unsigned int signAimId_7;

    /* マルチ目的ID08
     *   目的設定時にリストに表示するマルチ目的ID
     * Sign Aim ID [8]
     *   Multi-purpose ID to be displayed in the list when setting the purpose */
    unsigned int signAimId_8;

    /* 赤サイン制限イベントフラグID1
     *   赤サイン制限イベントフラグID1
     * Red Sign Limit - Event Flag ID [1]
     *   Red sign limit event flag ID1 */
    unsigned int redSignLimitEventFlagId_1;

    /* 侵入制限イベントフラグID2
     *   侵入制限イベントフラグID2
     * Invasion Limit - Event Flag ID [2]
     *   Intrusion restriction event flag ID2 */
    unsigned int breakInLimitEventFlagId_2;

    /* 侵入制限イベントフラグID3
     *   侵入制限イベントフラグID3
     * Invasion Limit - Event Flag ID [3]
     *   Intrusion restriction event flag ID3 */
    unsigned int breakInLimitEventFlagId_3;

    /* 白サイン制限イベントフラグID2
     *   白サイン制限イベントフラグID2
     * White Sign Limit - Event Flag ID [2]
     *   White sign limit event flag ID2 */
    unsigned int whiteSignLimitEventFlagId_2;

    /* 白サイン制限イベントフラグID3
     *   白サイン制限イベントフラグID3
     * White Sign Limit - Event Flag ID [3]
     *   White sign limit event flag ID3 */
    unsigned int whiteSignLimitEventFlagId_3;

    /* 赤サイン制限イベントフラグID2
     *   赤サイン制限イベントフラグID2
     * Red Sign Limit - Event Flag ID [2]
     *   Red sign limit event flag ID2 */
    unsigned int redSignLimitEventFlagId_2;

    /* 赤サイン制限イベントフラグID3
     *   赤サイン制限イベントフラグID3
     * Red Sign Limit - Event Flag ID [3]
     *   Red sign limit event flag ID3 */
    unsigned int redSignLimitEventFlagId_3;

    /* 領域内ボスID01
     *   領域内ボスID。「侵入ポイント自動生成か」が○のときに目的とするボスを選ぶのに使われる。
     * Boss ID [1]
     *   Area boss ID. It is used to select the target boss when Is the intrusion point automatically generated? Is . */
    unsigned int bossId_1;

    /* 領域内ボスID02
     *   領域内ボスID。「侵入ポイント自動生成か」が○のときに目的とするボスを選ぶのに使われる。
     * Boss ID [2]
     *   Area boss ID. It is used to select the target boss when Is the intrusion point automatically generated? Is . */
    unsigned int bossId_2;

    /* 領域内ボスID03
     *   領域内ボスID。「侵入ポイント自動生成か」が○のときに目的とするボスを選ぶのに使われる。
     * Boss ID [3]
     *   Area boss ID. It is used to select the target boss when Is the intrusion point automatically generated? Is . */
    unsigned int bossId_3;

    /* 領域内ボスID04
     *   領域内ボスID。「侵入ポイント自動生成か」が○のときに目的とするボスを選ぶのに使われる。
     * Boss ID [4]
     *   Area boss ID. It is used to select the target boss when Is the intrusion point automatically generated? Is . */
    unsigned int bossId_4;

    /* 領域内ボスID05
     *   領域内ボスID。「侵入ポイント自動生成か」が○のときに目的とするボスを選ぶのに使われる。
     * Boss ID [5]
     *   Area boss ID. It is used to select the target boss when Is the intrusion point automatically generated? Is . */
    unsigned int bossId_5;

    /* 領域内ボスID06
     *   領域内ボスID。「侵入ポイント自動生成か」が○のときに目的とするボスを選ぶのに使われる。
     * Boss ID [6]
     *   Area boss ID. It is used to select the target boss when Is the intrusion point automatically generated? Is . */
    unsigned int bossId_6;

    /* 領域内ボスID07
     *   領域内ボスID。「侵入ポイント自動生成か」が○のときに目的とするボスを選ぶのに使われる。
     * Boss ID [7]
     *   Area boss ID. It is used to select the target boss when Is the intrusion point automatically generated? Is . */
    unsigned int bossId_7;

    /* 領域内ボスID08
     *   領域内ボスID。「侵入ポイント自動生成か」が○のときに目的とするボスを選ぶのに使われる。
     * Boss ID [8]
     *   Area boss ID. It is used to select the target boss when Is the intrusion point automatically generated? Is . */
    unsigned int bossId_8;

    /* 領域内ボスID09
     *   領域内ボスID。「侵入ポイント自動生成か」が○のときに目的とするボスを選ぶのに使われる。
     * Boss ID [9]
     *   Area boss ID. It is used to select the target boss when Is the intrusion point automatically generated? Is . */
    unsigned int bossId_9;

    /* 領域内ボスID10
     *   領域内ボスID。「侵入ポイント自動生成か」が○のときに目的とするボスを選ぶのに使われる。
     * Boss ID [10]
     *   Area boss ID. It is used to select the target boss when Is the intrusion point automatically generated? Is . */
    unsigned int bossId_10;

    /* 領域内ボスID11
     *   領域内ボスID。「侵入ポイント自動生成か」が○のときに目的とするボスを選ぶのに使われる。
     * Boss ID [11]
     *   Area boss ID. It is used to select the target boss when Is the intrusion point automatically generated? Is . */
    unsigned int bossId_11;

    /* 領域内ボスID12
     *   領域内ボスID。「侵入ポイント自動生成か」が○のときに目的とするボスを選ぶのに使われる。
     * Boss ID [12]
     *   Area boss ID. It is used to select the target boss when Is the intrusion point automatically generated? Is . */
    unsigned int bossId_12;

    /* 領域内ボスID13
     *   領域内ボスID。「侵入ポイント自動生成か」が○のときに目的とするボスを選ぶのに使われる。
     * Boss ID [13]
     *   Area boss ID. It is used to select the target boss when Is the intrusion point automatically generated? Is . */
    unsigned int bossId_13;

    /* 領域内ボスID14
     *   領域内ボスID。「侵入ポイント自動生成か」が○のときに目的とするボスを選ぶのに使われる。
     * Boss ID [14]
     *   Area boss ID. It is used to select the target boss when Is the intrusion point automatically generated? Is . */
    unsigned int bossId_14;

    /* 領域内ボスID15
     *   領域内ボスID。「侵入ポイント自動生成か」が○のときに目的とするボスを選ぶのに使われる。
     * Boss ID [15]
     *   Area boss ID. It is used to select the target boss when Is the intrusion point automatically generated? Is . */
    unsigned int bossId_15;

    /* 領域内ボスID16
     *   領域内ボスID。「侵入ポイント自動生成か」が○のときに目的とするボスを選ぶのに使われる。
     * Boss ID [16]
     *   Area boss ID. It is used to select the target boss when Is the intrusion point automatically generated? Is . */
    unsigned int bossId_16;

    /* 地図表示用_イベントフラグID
     *   地図表示用_イベントフラグID(0:常に表示)。このイベントフラグが立っているときだけ、マップメニューに賑わい表示される
     * Map Menu Unlock - Event Flag ID
     *   Map display_event flag ID (0 - always displayed). Only when this event flag is set, it will be displayed in a lively manner in the map menu. */
    unsigned int mapMenuUnlockEventId;

    char pad5[32];
} er_play_region_param_t;
