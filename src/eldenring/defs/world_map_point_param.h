#pragma once

typedef struct er_world_map_point_param_s {
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

    /* 開放イベントフラグID
     *   開放条件のイベントフラグID
     * Open - Event Flag ID
     *   Event flag ID of open condition */
    unsigned int eventFlagId;

    /* 遠見台発見イベントフラグID
     *   遠見台で発見した際に立てるイベントフラグID
     * Distant View - Event Flag ID
     *   Event flag ID to be set when found on the distant view */
    unsigned int distViewEventFlagId;

    /* アイコンID
     *   アイコンID
     * Icon ID
     *   Icon ID */
    unsigned short iconId;

    /* BGM用場所情報（入場領域内）
     *   Bgm場所タイプ
     * BGM Location Type
     *   Bgm location type */
    short bgmPlaceType;

    /* 範囲アイコンか
     *   範囲を表すアイコンか。地図に対して等倍になる
     * Is Area Icon
     *   Is it an icon that represents a range? Same size as the map */
    unsigned char isAreaIcon:1;

    /* 遠見台目印_座標上書きするか
     *   遠見台目印として使うときに座標を上書きするか
     * Overwrite Coordinates when Distant View Marker
     *   Whether to overwrite the coordinates when using it as a distant view marker */
    unsigned char isOverrideDistViewMarkPos:1;

    /* テキストが無いときに表示するか
     *   テキストが無いときにも表示するか。基本的にはテキストがなければポイントは表示しない。このフラグが有効なときにはテキストがなくても表示する
     * Enable with No Text
     *   Do you want to display it even when there is no text? Basically, points are not displayed without text. Display without text when this flag is enabled */
    unsigned char isEnableNoText:1;

    /* パッド3 */
    char pad3:5;

    /* 遠見台目印上書き_エリア番号
     *   mAA_BB_CC_DD の AA 部分
     * Distant View Marker - Map Area
     *   AA part of mAA_BB_CC_DD */
    unsigned char areaNo_forDistViewMark;

    /* 遠見台目印上書き_グリッドX番号
     *   mAA_BB_CC_DD の BB 部分
     * Distant View Marker - Map Block
     *   BB part of mAA_BB_CC_DD */
    unsigned char gridXNo_forDistViewMark;

    /* 遠見台目印上書き_グリッドZ番号
     *   mAA_BB_CC_DD の CC 部分
     * Distant View Marker - Map Region
     *   CC part of mAA_BB_CC_DD */
    unsigned char gridZNo_forDistViewMark;

    /* クリア済イベントフラグID
     *   クリア済みイベントフラグID(0:常にクリア済み扱い)
     * Cleared - Event Flag ID
     *   Cleared event flag ID (0: always treated as cleared) */
    unsigned int clearedEventFlagId;

    /* 表示設定M00
     *   M00で表示するか
     * Display Mask M00
     *   Whether to display with M00 */
    unsigned char dispMask00:1;

    /* 表示設定M01
     *   M01で表示するか
     * Display Mask M01
     *   Whether to display with M01 */
    unsigned char dispMask01:1;

    /* Display Mask M02
     *   Whether to display with M02 */
    unsigned char dispMask02:1;

    /* パッド
     *   pad2_0 */
    char pad2_0:5;

    /* パッド
     *   pad2 */
    char pad2[1];

    /* 遠見台発見時アイコンID
     *   遠見台発見時アイコンID
     * Distant View - Icon ID
     *   Icon ID when distant view is found */
    unsigned short distViewIconId;

    /* アイコン角度[deg]
     *   表示アイコンの回転角度[deg]
     * Display Icon Angle
     *   Display icon rotation angle [deg] */
    float angle;

    /* エリア番号
     *   mAA_BB_CC_DD の AA 部分
     * Map Area
     *   AA part of mAA_BB_CC_DD */
    unsigned char areaNo;

    /* グリッドX番号
     *   mAA_BB_CC_DD の BB 部分
     * Map Block
     *   BB part of mAA_BB_CC_DD */
    unsigned char gridXNo;

    /* グリッドZ番号
     *   mAA_BB_CC_DD の CC 部分
     * Map Region
     *   CC part of mAA_BB_CC_DD */
    unsigned char gridZNo;

    /* パディング
     *   パディング */
    char pad[1];

    /* X座標
     *   X座標
     * Map Coordinate: X
     *   X coordinate */
    float posX;

    /* Y座標
     *   Y座標（使っていない）
     * Map Coordinate: Y
     *   Y coordinate (not used) */
    float posY;

    /* Z座標
     *   Z座標
     * Map Coordinate: Z
     *   Z coordinate */
    float posZ;

    /* テキストID
     *   表示するテキストID。無効値(-1)なら、何も表示しない
     * Text ID [1]
     *   The text ID to display. If the value is invalid (-1), nothing is displayed.
     * Default Value  = -1 */
    int textId1;

    /* 出現イベントフラグID
     *   テキストの表示イベントフラグID。イベントフラグがOnなら表示する。無効なイベントフラグID(0)なら、On扱いされる
     * Text Enable Flag [1]
     *   Display text Event flag ID. Display if the event flag is On. If the event flag ID (0) is invalid, it will be treated as On. */
    unsigned int textEnableFlagId1;

    /* 非表示イベントフラグID
     *   テキストの非表示イベントフラグID。イベントフラグがOnなら表示しない。表示イベントフラグIDよりも優先される。無効なイベントフラグID(0)なら、Off扱いされる
     * Text Disable Flag [1]
     *   Hidden event flag ID of the text. If the event flag is On, it will not be displayed. It takes precedence over the display event flag ID. If the event flag ID (0) is invalid, it will be treated as Off. */
    unsigned int textDisableFlagId1;

    /* テキストID
     *   表示するテキストID。無効値(-2)なら、何も表示しない
     * Text ID [2]
     *   The text ID to display. If it is an invalid value (-2), nothing is displayed.
     * Default Value  = -1 */
    int textId2;

    /* 出現イベントフラグID
     *   テキストの表示イベントフラグID。イベントフラグがOnなら表示する。無効なイベントフラグID(1)なら、On扱いされる
     * Text Enable Flag [2]
     *   Display text Event flag ID. Display if the event flag is On. If the event flag ID (1) is invalid, it will be treated as On. */
    unsigned int textEnableFlagId2;

    /* 非表示イベントフラグID
     *   テキストの非表示イベントフラグID。イベントフラグがOnなら表示しない。表示イベントフラグIDよりも優先される。無効なイベントフラグID(1)なら、Off扱いされる
     * Text Disable Flag [2]
     *   Hidden event flag ID of the text. If the event flag is On, it will not be displayed. It takes precedence over the display event flag ID. If the event flag ID (1) is invalid, it will be treated as Off. */
    unsigned int textDisableFlagId2;

    /* テキストID
     *   表示するテキストID。無効値(-3)なら、何も表示しない
     * Text ID [3]
     *   The text ID to display. If it is an invalid value (-3), nothing is displayed.
     * Default Value  = -1 */
    int textId3;

    /* 出現イベントフラグID
     *   テキストの表示イベントフラグID。イベントフラグがOnなら表示する。無効なイベントフラグID(2)なら、On扱いされる
     * Text Enable Flag [3]
     *   Display text Event flag ID. Display if the event flag is On. If the event flag ID (2) is invalid, it will be treated as On. */
    unsigned int textEnableFlagId3;

    /* 非表示イベントフラグID
     *   テキストの非表示イベントフラグID。イベントフラグがOnなら表示しない。表示イベントフラグIDよりも優先される。無効なイベントフラグID(2)なら、Off扱いされる
     * Text Disable Flag [3]
     *   Hidden event flag ID of the text. If the event flag is On, it will not be displayed. It takes precedence over the display event flag ID. If the event flag ID (2) is invalid, it will be treated as Off. */
    unsigned int textDisableFlagId3;

    /* テキストID
     *   表示するテキストID。無効値(-4)なら、何も表示しない
     * Text ID [4]
     *   The text ID to display. If it is an invalid value (-4), nothing is displayed.
     * Default Value  = -1 */
    int textId4;

    /* 出現イベントフラグID
     *   テキストの表示イベントフラグID。イベントフラグがOnなら表示する。無効なイベントフラグID(3)なら、On扱いされる
     * Text Enable Flag [4]
     *   Display text Event flag ID. Display if the event flag is On. If the event flag ID (3) is invalid, it will be treated as On. */
    unsigned int textEnableFlagId4;

    /* 非表示イベントフラグID
     *   テキストの非表示イベントフラグID。イベントフラグがOnなら表示しない。表示イベントフラグIDよりも優先される。無効なイベントフラグID(3)なら、Off扱いされる
     * Text Disable Flag [4]
     *   Hidden event flag ID of the text. If the event flag is On, it will not be displayed. It takes precedence over the display event flag ID. If the event flag ID (3) is invalid, it will be treated as Off. */
    unsigned int textDisableFlagId4;

    /* テキストID
     *   表示するテキストID。無効値(-5)なら、何も表示しない
     * Text ID [5]
     *   The text ID to display. If it is an invalid value (-5), nothing is displayed.
     * Default Value  = -1 */
    int textId5;

    /* 出現イベントフラグID
     *   テキストの表示イベントフラグID。イベントフラグがOnなら表示する。無効なイベントフラグID(4)なら、On扱いされる
     * Text Enable Flag [5]
     *   Display text Event flag ID. Display if the event flag is On. If the event flag ID (4) is invalid, it will be treated as On. */
    unsigned int textEnableFlagId5;

    /* 非表示イベントフラグID
     *   テキストの非表示イベントフラグID。イベントフラグがOnなら表示しない。表示イベントフラグIDよりも優先される。無効なイベントフラグID(4)なら、Off扱いされる
     * Text Disable Flag [5]
     *   Hidden event flag ID of the text. If the event flag is On, it will not be displayed. It takes precedence over the display event flag ID. If the event flag ID (4) is invalid, it will be treated as Off. */
    unsigned int textDisableFlagId5;

    /* テキストID
     *   表示するテキストID。無効値(-6)なら、何も表示しない
     * Text ID [6]
     *   The text ID to display. If it is an invalid value (-6), nothing is displayed.
     * Default Value  = -1 */
    int textId6;

    /* 出現イベントフラグID
     *   テキストの表示イベントフラグID。イベントフラグがOnなら表示する。無効なイベントフラグID(5)なら、On扱いされる
     * Text Enable Flag [6]
     *   Display text Event flag ID. Display if the event flag is On. If the event flag ID (5) is invalid, it will be treated as On. */
    unsigned int textEnableFlagId6;

    /* 非表示イベントフラグID
     *   テキストの非表示イベントフラグID。イベントフラグがOnなら表示しない。表示イベントフラグIDよりも優先される。無効なイベントフラグID(5)なら、Off扱いされる
     * Text Disable Flag [6]
     *   Hidden event flag ID of the text. If the event flag is On, it will not be displayed. It takes precedence over the display event flag ID. If the event flag ID (5) is invalid, it will be treated as Off. */
    unsigned int textDisableFlagId6;

    /* テキストID
     *   表示するテキストID。無効値(-7)なら、何も表示しない
     * Text ID [7]
     *   The text ID to display. If it is an invalid value (-7), nothing is displayed.
     * Default Value  = -1 */
    int textId7;

    /* 出現イベントフラグID
     *   テキストの表示イベントフラグID。イベントフラグがOnなら表示する。無効なイベントフラグID(6)なら、On扱いされる
     * Text Enable Flag [7]
     *   Display text Event flag ID. Display if the event flag is On. If the event flag ID (6) is invalid, it will be treated as On. */
    unsigned int textEnableFlagId7;

    /* 非表示イベントフラグID
     *   テキストの非表示イベントフラグID。イベントフラグがOnなら表示しない。表示イベントフラグIDよりも優先される。無効なイベントフラグID(6)なら、Off扱いされる
     * Text Disable Flag [7]
     *   Hidden event flag ID of the text. If the event flag is On, it will not be displayed. It takes precedence over the display event flag ID. If the event flag ID (6) is invalid, it will be treated as Off. */
    unsigned int textDisableFlagId7;

    /* テキストID
     *   表示するテキストID。無効値(-8)なら、何も表示しない
     * Text ID [8]
     *   The text ID to display. If it is an invalid value (-8), nothing is displayed.
     * Default Value  = -1 */
    int textId8;

    /* 出現イベントフラグID
     *   テキストの表示イベントフラグID。イベントフラグがOnなら表示する。無効なイベントフラグID(7)なら、On扱いされる
     * Text Enable Flag [8]
     *   Display text Event flag ID. Display if the event flag is On. If the event flag ID (7) is invalid, it will be treated as On. */
    unsigned int textEnableFlagId8;

    /* 非表示イベントフラグID
     *   テキストの非表示イベントフラグID。イベントフラグがOnなら表示しない。表示イベントフラグIDよりも優先される。無効なイベントフラグID(7)なら、Off扱いされる
     * Text Disable Flag [8]
     *   Hidden event flag ID of the text. If the event flag is On, it will not be displayed. It takes precedence over the display event flag ID. If the event flag ID (7) is invalid, it will be treated as Off. */
    unsigned int textDisableFlagId8;

    /* テキスト種別
     *   テキストの種別(地名,NPC名,...)
     * Text Type [1]
     *   Text type (place name, NPC name, ...) */
    unsigned char textType1;

    /* テキスト種別
     *   テキストの種別(地名,NPC名,...)
     * Text Type [2]
     *   Text type (place name, NPC name, ...) */
    unsigned char textType2;

    /* テキスト種別
     *   テキストの種別(地名,NPC名,...)
     * Text Type [3]
     *   Text type (place name, NPC name, ...) */
    unsigned char textType3;

    /* テキスト種別
     *   テキストの種別(地名,NPC名,...)
     * Text Type [4]
     *   Text type (place name, NPC name, ...) */
    unsigned char textType4;

    /* テキスト種別
     *   テキストの種別(地名,NPC名,...)
     * Text Type [5]
     *   Text type (place name, NPC name, ...) */
    unsigned char textType5;

    /* テキスト種別
     *   テキストの種別(地名,NPC名,...)
     * Text Type [6]
     *   Text type (place name, NPC name, ...) */
    unsigned char textType6;

    /* テキスト種別
     *   テキストの種別(地名,NPC名,...)
     * Text Type [7]
     *   Text type (place name, NPC name, ...) */
    unsigned char textType7;

    /* テキスト種別
     *   テキストの種別(地名,NPC名,...)
     * Text Type [8]
     *   Text type (place name, NPC name, ...) */
    unsigned char textType8;

    /* 遠見台ID0
     *   遠見台ID
     * Distant View ID [0]
     *   Distance stand ID
     * Default Value  = -1 */
    int distViewId;

    /* 遠見台目印上書き_X座標
     *   X座標
     * Distant View Marker - Coordinate: X
     *   X coordinate */
    float posX_forDistViewMark;

    /* 遠見台目印上書きY座標
     *   Y座標
     * Distant View Marker - Coordinate: Y
     *   Y coordinate */
    float posY_forDistViewMark;

    /* 遠見台目印上書きZ座標
     *   Z座標
     * Distant View Marker - Coordinate: Z
     *   Z coordinate */
    float posZ_forDistViewMark;

    /* 遠見台ID1
     *   遠見台ID
     * Distant View ID [1]
     *   Distance stand ID
     * Default Value  = -1 */
    int distViewId1;

    /* 遠見台ID2
     *   遠見台ID
     * Distant View ID [2]
     *   Distance stand ID
     * Default Value  = -1 */
    int distViewId2;

    /* 遠見台ID3
     *   遠見台ID
     * Distant View ID [3]
     *   Distance stand ID
     * Default Value  = -1 */
    int distViewId3;

    /* 表示ズームステップ
     *   地図ポイントを表示するズームステップ（一番ズームアウトした状態が0、ズームするごとに+1）。「《表示ズームステップ》≦ 現在のズームステップ 」のときに表示される。デフォルトは 0（常に表示）
     * Display - Min Zoom Step
     *   Zoom step to display map points (0 when zoomed out most, +1 for each zoom). Displayed when Display zoom step  Current zoom step. Default is 0 (always displayed) */
    unsigned char dispMinZoomStep;

    /* 選択可能ズームステップ
     *   地図ポイントを選択可能なズームステップ（一番ズームアウトした状態が0、ズームするごとに+1）。「《選択可能ズームステップ》≦ 現在の拡大段階 」のときに選択可能。デフォルトは 0（常に選択可能）
     * Selection - Min Zoom Step
     *   Zoom step where map points can be selected (0 when zoomed out most, +1 for each zoom). Selectable when Selectable zoom step  Current enlargement stage. Default is 0 (always selectable) */
    unsigned char selectMinZoomStep;

    /* 入場表示形式
     *   入場表示形式。入場時に表示する地図ポイント入場FEの種類
     * Entry FE Type
     *   Admission display format. Map points to be displayed at the time of admission Types of admission FE */
    unsigned char entryFEType;

    unsigned char unknown_0xb7;

    /* Alternate Icon ID
     *   Icon ID that applies when a Text Enable Flag ID is true and it's corrosponding Text Type is set to 1 */
    unsigned short altIconId;

    /* パッド
     *   pad3 */
    char pad4[6];

    /* Text Enable Flag ID 2 [1]
     *   Display text Event flag ID. Display if the event flag is On. If the event flag ID (0) is invalid, it will be treated as On. */
    int textEnableFlag2Id1;

    /* Text Enable Flag ID 2 [2]
     *   Display text Event flag ID. Display if the event flag is On. If the event flag ID (0) is invalid, it will be treated as On. */
    int textEnableFlag2Id2;

    /* Text Enable Flag ID 2 [3]
     *   Display text Event flag ID. Display if the event flag is On. If the event flag ID (0) is invalid, it will be treated as On. */
    int textEnableFlag2Id3;

    /* Text Enable Flag ID 2 [4]
     *   Display text Event flag ID. Display if the event flag is On. If the event flag ID (0) is invalid, it will be treated as On. */
    int textEnableFlag2Id4;

    /* Text Enable Flag ID 2 [5]
     *   Display text Event flag ID. Display if the event flag is On. If the event flag ID (0) is invalid, it will be treated as On. */
    int textEnableFlag2Id5;

    /* Text Enable Flag ID 2 [6]
     *   Display text Event flag ID. Display if the event flag is On. If the event flag ID (0) is invalid, it will be treated as On. */
    int textEnableFlag2Id6;

    /* Text Enable Flag ID 2 [7]
     *   Display text Event flag ID. Display if the event flag is On. If the event flag ID (0) is invalid, it will be treated as On. */
    int textEnableFlag2Id7;

    /* Text Enable Flag ID 2 [8]
     *   Display text Event flag ID. Display if the event flag is On. If the event flag ID (0) is invalid, it will be treated as On. */
    int textEnableFlag2Id8;

    /* Text Disable Flag ID 2 [1]
     *   Hidden event flag ID of the text. If the event flag is On, it will not be displayed. It takes precedence over the display event flag ID. If the event flag ID (0) is invalid, it will be treated as Off. */
    int textDisableFlag2Id1;

    /* Text Disable Flag ID 2 [2]
     *   Hidden event flag ID of the text. If the event flag is On, it will not be displayed. It takes precedence over the display event flag ID. If the event flag ID (0) is invalid, it will be treated as Off. */
    int textDisableFlag2Id2;

    /* Text Disable Flag ID 2 [3]
     *   Hidden event flag ID of the text. If the event flag is On, it will not be displayed. It takes precedence over the display event flag ID. If the event flag ID (0) is invalid, it will be treated as Off. */
    int textDisableFlag2Id3;

    /* Text Disable Flag ID 2 [4]
     *   Hidden event flag ID of the text. If the event flag is On, it will not be displayed. It takes precedence over the display event flag ID. If the event flag ID (0) is invalid, it will be treated as Off. */
    int textDisableFlag2Id4;

    /* Text Disable Flag ID 2 [5]
     *   Hidden event flag ID of the text. If the event flag is On, it will not be displayed. It takes precedence over the display event flag ID. If the event flag ID (0) is invalid, it will be treated as Off. */
    int textDisableFlag2Id5;

    /* Text Disable Flag ID 2 [6]
     *   Hidden event flag ID of the text. If the event flag is On, it will not be displayed. It takes precedence over the display event flag ID. If the event flag ID (0) is invalid, it will be treated as Off. */
    int textDisableFlag2Id6;

    /* Text Disable Flag ID 2 [7]
     *   Hidden event flag ID of the text. If the event flag is On, it will not be displayed. It takes precedence over the display event flag ID. If the event flag ID (0) is invalid, it will be treated as Off. */
    int textDisableFlag2Id7;

    /* Text Disable Flag ID 2 [8]
     *   Hidden event flag ID of the text. If the event flag is On, it will not be displayed. It takes precedence over the display event flag ID. If the event flag ID (0) is invalid, it will be treated as Off. */
    int textDisableFlag2Id8;
} er_world_map_point_param_t;
