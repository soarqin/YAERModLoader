#pragma once

typedef struct er_network_param_s {
    /* サイン高さオフセット[m]
     * Common - Sign Height Offset */
    float signVerticalOffset;

    /* サイン位置補正最大距離[m]
     * Common - Max Sign Position Correction Range */
    float maxSignPosCorrectionRange;

    /* 召喚希望タイムアウト時間[秒]
     * Common - Summon Timeout Time */
    float summonTimeoutTime;

    /* 予約 */
    char pad_0[4];

    /* サイン溜まり登録中メッセージ表示間隔[秒]
     * Summon Sign - Sign Puddle Active Message Interval
     * Default Value  = 1 */
    float signPuddleActiveMessageIntervalSec;

    /* キーガイド垂直範囲[m]
     * Summon Sign - Key Guide Height
     * Default Value  = 1 */
    float keyGuideHeight_0;

    /* 召喚サイン再取得待機時間(過疎時)[秒]
     * Summon Sign - Reload Sign Interval Time [1]
     * Default Value  = 1 */
    float reloadSignIntervalTime1;

    /* 召喚サイン再取得待機時間[秒]
     * Summon Sign - Reload Sign Interval Time [2]
     * Default Value  = 1 */
    float reloadSignIntervalTime2;

    /* 召喚サイン所持可能数上限(全体)
     *   本当はu8くらいで十分
     * Summon Sign - Reload Sign Total Count
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int reloadSignTotalCount_0;

    /* 召喚サイン所持可能数上限(セル)
     *   本当はu8くらいで十分
     * Summon Sign - Reload Sign Cell Count
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int reloadSignCellCount_0;

    /* 召喚サイン更新待機時間[秒]
     * Summon Sign - Update Sign Interval Time
     * Default Value  = 1 */
    float updateSignIntervalTime;

    /* 召喚サイン間描画排他水平範囲[m]
     * Summon Sign - Basic Horizontal Drawing Range
     * Default Value  = 1 */
    float basicExclusiveRange_0;

    /* 召喚サイン間描画排他垂直範囲[m]
     * Summon Sign - Basic Vertical Drawing Height
     * Default Value  = 1 */
    float basicExclusiveHeight_0;

    /* 召喚サインキャラモデル描画待機時間[秒]
     * Summon Sign - Preview Chr Waiting Time
     * Default Value  = 1 */
    float previewChrWaitingTime;

    /* 召喚サインPC間描画距離[m]
     * Summon Sign - Sign Visible Range
     * Default Value  = 1 */
    float signVisibleRange_0;

    /* 召喚サイン取得セル範囲(水平)
     *   本当はu8くらいで十分
     * Summon Sign - Acquisition Cell Range (Horizontal)
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int cellGroupHorizontalRange_0;

    /* 召喚サイン取得セル範囲(上方向)
     *   本当はu8くらいで十分
     * Summon Sign - Acquisition Cell Range (Top)
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int cellGroupTopRange_0;

    /* 召喚サイン取得セル範囲(下方向)
     *   本当はu8くらいで十分
     * Summon Sign - Acquisition Cell Range (Bottom)
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int cellGroupBottomRange_0;

    /* 白霊サイン表示制限時間下限倍率
     * Summon Sign - Min White Phantom Limit Time Scale
     * Default Value  = 1 */
    float minWhitePhantomLimitTimeScale;

    /* 小霊サイン表示制限時間下限倍率
     * Summon Sign - Min Small Phantom Limit Time Scale
     * Default Value  = 1 */
    float minSmallPhantomLimitTimeScale;

    /* 白霊サインキーワード延長倍率
     * Summon Sign - White Keyword Limit Time Scale
     * Default Value  = 1 */
    float whiteKeywordLimitTimeScale;

    /* 小霊サインキーワード延長倍率
     * Summon Sign - Small Keyword Limit Time Scale
     * Default Value  = 1 */
    float smallKeywordLimitTimeScale;

    /* 闇霊サインキーワード延長倍率
     * Summon Sign - Black Keyword Limit Time Scale
     * Default Value  = 1 */
    float blackKeywordLimitTimeScale;

    /* 竜霊サインキーワード延長倍率
     * Summon Sign - Dragon Keyword Limit Time Scale
     * Default Value  = 1 */
    float dragonKeywordLimitTimeScale;

    /* サイン取得上限
     *   本当はu8くらいで十分
     * Summon Sign - Sign Get Max
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int singGetMax;

    /* サインダウンロードスパン
     * Summon Sign - Sign Download Span
     * Default Value  = 1 */
    float signDownloadSpan;

    /* サインアップロードスパン
     * Summon Sign - Sign Update Span
     * Default Value  = 1 */
    float signUpdateSpan;

    /* 予約 */
    char signPad[4];

    /* 乱入先取得数
     * Intrusion - Max Intruder List Count
     * Default Value  = 1 */
    unsigned int maxBreakInTargetListCount;

    /* 乱入リクエスト間隔[秒]
     * Intrusion - Intruder Request Interval Time
     * Default Value  = 4 */
    float breakInRequestIntervalTimeSec;

    /* 乱入リクエストタイムアウト時間[秒]
     * Intrusion - Intruder Request Timeout
     * Default Value  = 20 */
    float breakInRequestTimeOutSec;

    unsigned char unknown_0x7c;

    /* 予約 */
    char pad_1[3];

    /* キーガイド水平範囲[m]
     * Blood Message - Key Guide Horionztal Range
     * Default Value  = 1 */
    float keyGuideRange;

    /* キーガイド垂直範囲[m]
     * Blood Message - Key Guide Vertical Range
     * Default Value  = 1 */
    float keyGuideHeight_1;

    /* 血文字取得数(全体)
     *   本当はu8くらいで十分
     * Blood Message - Reload Sign Total Count
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int reloadSignTotalCount_1;

    /* 血文字取得数(セル、新順)
     *   本当はu8くらいで十分
     * Blood Message - Reload New Sign Cell Count
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int reloadNewSignCellCount;

    /* 血文字取得数(セル、ランダム )
     *   本当はu8くらいで十分
     * Blood Message - Reload Random Sign Cell Count
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int reloadRandomSignCellCount;

    /* 血文字所持可能数上限(全体)
     *   本当はu16くらいで十分
     * Blood Message - Max Sign Total Count
     *   Actually u16 is enough
     * Default Value  = 1 */
    unsigned int maxSignTotalCount_0;

    /* 血文字所持可能数上限(セル)
     *   本当はu8くらいで十分
     * Blood Message - Max Sign Cell Count
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int maxSignCellCount_0;

    /* 血文字間描画排他水平範囲[m]
     * Blood Message - Basic Exclusive Range
     * Default Value  = 1 */
    float basicExclusiveRange_1;

    /* 血文字間描画排他垂直範囲[m]
     * Blood Message - Basic Exclusive Height
     * Default Value  = 1 */
    float basicExclusiveHeight_1;

    /* 血文字PC間描画距離[m]
     * Blood Message - Sign Visible Range
     * Default Value  = 1 */
    float signVisibleRange_1;

    /* 書いた血文字履歴件数上限
     *   本当はu8くらいで十分
     * Blood Message - Max Write Sign Count
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int maxWriteSignCount;

    /* 読んだ血文字履歴件数上限
     *   本当はu8くらいで十分
     * Blood Message - Max Read Sign Count
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int maxReadSignCount;

    /* 血文字再取得待機時間[秒]
     * Blood Message - Reload Sign Interval Time
     * Default Value  = 1 */
    float reloadSignIntervalTime_0;

    /* 血文字取得セル範囲(水平)
     *   本当はu8くらいで十分
     * Blood Message - Cell Group Horizontal Range
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int cellGroupHorizontalRange_1;

    /* 血文字取得セル範囲(上方向)
     *   本当はu8くらいで十分
     * Blood Message - Cell Group Top Range
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int cellGroupTopRange_1;

    /* 血文字取得セル範囲(下方向)
     *   本当はu8くらいで十分
     * Blood Message - Cell Group Bottom Range
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int cellGroupBottomRange_1;

    /* 血文字データ保持期間上限[秒]
     *   本当はu16くらいで十分
     * Blood Message - Lifetime
     *   Actually u16 is enough
     * Default Value  = 1 */
    unsigned int lifeTime_0;

    /* 血文字ダウンロード間隔
     * Blood Message - Download Span */
    float downloadSpan_0;

    /* 血文字評価数ダウンロード間隔
     * Blood Message - Download Evaluation Span */
    float downloadEvaluationSpan;

    /* 予約 */
    char pad_2[4];

    /* 血痕位置と幻影開始位置間の許容距離[m]
     *   血痕位置と幻影開始位置の間の距離がこの値より離れている場合はサーバの登録を行わない
     * Bloodstain - Dead Ghost Start Position Threshold
     *   If the distance between the bloodstain position and the illusion start position is farther than this value, the server will not be registered.
     * Default Value  = 1 */
    float deadingGhostStartPosThreshold;

    /* キーガイド垂直範囲[m]
     * Bloodstain - Key Guide Height
     * Default Value  = 1 */
    float keyGuideHeight_2;

    /* プレイヤー血痕キーガイド水平範囲[m]
     * Bloodstain - Key Guide Range Player
     * Default Value  = 1 */
    float keyGuideRangePlayer;

    /* プレイヤー血痕キーガイド垂直範囲[m]
     * Bloodstain - Key Guide Height Player
     * Default Value  = 1 */
    float keyGuideHeightPlayer;

    /* 血痕取得数(全体)
     *   本当はu8くらいで十分
     * Bloodstain - Reload Sign Total Count
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int reloadSignTotalCount_2;

    /* 血痕取得数(セル)
     *   本当はu8くらいで十分
     * Bloodstain - Reload Sign Cell Count
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int reloadSignCellCount_1;

    /* 血痕所持可能数上限(全体)
     *   本当はu16くらいで十分
     * Bloodstain - Max Sign Total Count
     *   Actually u16 is enough
     * Default Value  = 1 */
    unsigned int maxSignTotalCount_1;

    /* 血痕所持可能数上限(セル)
     *   本当はu8くらいで十分
     * Bloodstain - Max Sign Cell Count
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int maxSignCellCount_1;

    /* 血痕再取得待機時間[秒]
     * Bloodstain - Reload Sign Interval Time
     * Default Value  = 1 */
    float reloadSignIntervalTime_1;

    /* 血痕PC間描画距離[m]
     * Bloodstain - Sign Visible Range
     * Default Value  = 1 */
    float signVisibleRange_2;

    /* 血痕間描画排他水平範囲[m]
     * Bloodstain - Basic Exclusive Range
     * Default Value  = 1 */
    float basicExclusiveRange_2;

    /* 血痕間描画排他垂直範囲[m]
     * Bloodstain - Basic Exclusive Height
     * Default Value  = 1 */
    float basicExclusiveHeight_2;

    /* 血痕取得セル範囲(水平)
     *   本当はu8くらいで十分
     * Bloodstain - Cell Group Horizontal Range
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int cellGroupHorizontalRange_2;

    /* 血痕取得セル範囲(上方向)
     *   本当はu8くらいで十分
     * Bloodstain - Cell Group Top Range
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int cellGroupTopRange_2;

    /* 血痕取得セル範囲(下方向)
     *   本当はu8くらいで十分
     * Bloodstain - Cell Group Bottom Range
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int cellGroupBottomRange_2;

    /* 血痕データ保持期間上限[秒]
     *   本当はu16くらいで十分
     * Bloodstain - Lifetime
     *   Actually u16 is enough
     * Default Value  = 1 */
    unsigned int lifeTime_1;

    /* 死亡幻影記録合計時間[秒]
     * Bloodstain - Record Dead Ghost Total Time */
    float recordDeadingGhostTotalTime;

    /* 死亡幻影の最低記録時間[秒]
     *   この記録時間未満の死亡幻影はサーバの登録を行わない
     * Bloodstain - Record Dead Ghost Min Time
     *   Death illusions less than this recording time will not register the server
     * Default Value  = 5 */
    float recordDeadingGhostMinTime;

    /* 血痕ダウンロード間隔
     * Bloodstain - Download Span */
    float downloadSpan_1;

    /* 石化血痕描画制限距離[m]
     *   オープンフィールド用。石像生成時にPC～生成位置間の距離がこの値以上ならば生成できる
     * Bloodstain - Statue Creatable Distance
     *   For open fields. When a stone statue is generated, it can be generated if the distance between the PC and the generation position is greater than or equal to this value.
     * Default Value  = 80 */
    float statueCreatableDistance;

    /* 幻影取得数(全体)
     *   本当はu8くらいで十分
     * Ghost - Reload Ghost Total Count
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int reloadGhostTotalCount;

    /* 幻影取得数(セル)
     *   本当はu8くらいで十分
     * Ghost - Reload Ghost Cell Count
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int reloadGhostCellCount;

    /* 幻影所持可能数上限(全体)
     *   本当はu16くらいで十分
     * Ghost - Max Ghost Total Count
     *   Actually u16 is enough
     * Default Value  = 1 */
    unsigned int maxGhostTotalCount;

    /* 敵対PCリプレイ記録開始距離[m]
     * Ghost - Begin Record Distance (Versus)
     * Default Value  = 1 */
    float distanceOfBeginRecordVersus;

    /* 敵対PCリプレイ記録終了距離[m]
     * Ghost - End Record Distance (Versus)
     * Default Value  = 1 */
    float distanceOfEndRecordVersus;

    /* 徘徊幻影アップロード間隔[秒]
     * Ghost - Update Wandering Ghost Interval Time
     * Default Value  = 1 */
    float updateWanderGhostIntervalTime;

    /* 対戦幻影アップロード間隔[秒]
     * Ghost - Update Versus Ghost Interval Time
     * Default Value  = 1 */
    float updateVersusGhostIntervalTime;

    /* 幻影記録時間[秒]
     * Ghost - Record Wandering Ghost Time
     * Default Value  = 1 */
    float recordWanderingGhostTime;

    /* 徘徊幻影の最低記録時間[秒]
     *   この記録時間未満の徘徊幻影はサーバの登録を行わない
     * Ghost - Record Wandering Ghost Min Time
     *   Wandering illusions less than this recording time do not register the server
     * Default Value  = 5 */
    float recordWanderingGhostMinTime;

    /* 篝火幻影アップロード間隔[秒]
     * Ghost - Update Bonfire Ghost Interval Time
     * Default Value  = 1 */
    float updateBonfireGhostIntervalTime;

    /* 幻影再生距離（視野内）[秒]
     * Ghost - Replay Ghost Range On View
     * Default Value  = 1 */
    float replayGhostRangeOnView;

    /* 幻影再生距離（視野外）[秒]
     * Ghost - Replay Ghost Range Out View
     * Default Value  = 1 */
    float replayGhostRangeOutView;

    /* 篝火幻影再生時間[秒]
     * Ghost - Replay Bonfire Ghost Time
     * Default Value  = 1 */
    float replayBonfireGhostTime;

    /* 篝火幻影配置最小距離[秒]
     *   篝火からこの距離未満の場所には篝火幻影を配置しない
     * Ghost - Bonfire Ghost Min Valid Range
     *   Do not place bonfire illusions less than this distance from the bonfire
     * Default Value  = 1 */
    float minBonfireGhostValidRange;

    /* 篝火幻影配置最大距離[秒]
     *   篝火からこの距離以上の場所には篝火幻影を配置しない
     * Ghost - Bonfire Ghost Max Valid Range
     *   Do not place bonfire illusions beyond this distance from the bonfire
     * Default Value  = 1 */
    float maxBonfireGhostValidRange;

    /* 幻影再生間隔下限[秒]
     * Ghost - Replay Interval Min Time
     * Default Value  = 1 */
    float minReplayIntervalTime;

    /* 幻影再生間隔上限[秒]
     * Ghost - Replay Interval Max Time
     * Default Value  = 1 */
    float maxReplayIntervalTime;

    /* 幻影定期取得間隔[秒]
     * Ghost - Reload Ghost Interval Time
     * Default Value  = 1 */
    float reloadGhostIntervalTime;

    /* 幻影取得セル範囲(水平)
     *   本当はu8くらいで十分
     * Ghost - Cell Group Horizontal Range
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int cellGroupHorizontalRange_3;

    /* 幻影取得セル範囲(上方向)
     *   本当はu8くらいで十分
     * Ghost - Cell Group Top Range
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int cellGroupTopRange_3;

    /* 幻影篝火モードファントムパラメータID(コードネーム)
     *   コードネーム一致のときに使われる幻影篝火モードファントムパラメータID
     * Ghost - Replay Bonfire Phantom Param ID (CodeDisplayName)
     *   Phantom bonfire mode phantom parameter ID used when codename matches */
    int replayBonfirePhantomParamIdForCodename;

    /* 幻影篝火モード再生適用距離
     * Ghost - Replay Bonfire Mode Range
     * Default Value  = 1 */
    float replayBonfireModeRange;

    /* 幻影篝火モードファントムパラメータID
     *   幻影篝火モードファントムパラメータID
     * Ghost - Replay Bonfire Phantom Param ID
     *   Phantom bonfire mode phantom parameter ID */
    int replayBonfirePhantomParamId;

    /* 予約 */
    char ghostpad[4];

    /* 指輪検索間隔[秒]
     * Visit - Reload Visit List Cool time
     * Default Value  = 1 */
    float reloadVisitListCoolTime;

    /* 救援青霊出現数上限
     *   本当はu8くらいで十分
     * Visit - Max Coop Blue Summon Count
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int maxCoopBlueSummonCount;

    /* 鐘守灰霊出現数上限
     *   本当はu8くらいで十分
     * Visit - Max Bell Guard Summon Count
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int maxBellGuardSummonCount;

    /* 指輪検索先取得数
     * Visit - Max Visit List Count
     * Default Value  = 1 */
    unsigned int maxVisitListCount;

    /* 救援青霊リロード時間　最小[sec]
     * Visit - Reload Search - Coop Blue - Min */
    float reloadSearch_CoopBlue_Min;

    /* 救援青霊リロード時間　最大[sec]
     * Visit - Reload Search - Coop Blue - Max */
    float reloadSearch_CoopBlue_Max;

    /* 鐘守リロード時間　最小[sec]
     * Visit - Reload Search - Bell Guard - Min */
    float reloadSearch_BellGuard_Min;

    /* 鐘守リロード時間　最大[sec]
     * Visit - Reload Search - Bell Guard - Max */
    float reloadSearch_BellGuard_Max;

    /* ネズミの王リロード時間　最小[sec]
     * Visit - Reload Search - Rat King - Min */
    float reloadSearch_RatKing_Min;

    /* ネズミの王リロード時間　最大[sec]
     * Visit - Reload Search - Rat King - Max */
    float reloadSearch_RatKing_Max;

    /* 予約 */
    char visitpad00[8];

    /* SRTT上限[ミリ秒]
     * Extra - SSRT Max Limit
     * Default Value  = 1000 */
    float srttMaxLimit;

    /* SRTT上限(安定時)[ミリ秒]
     * Extra - SSRT Mean Limit
     * Default Value  = 1000 */
    float srttMeanLimit;

    /* RTT平均偏差上限[ミリ秒]
     * Extra - SSRT Mean Deviation Limit
     * Default Value  = 1000 */
    float srttMeanDeviationLimit;

    /* 闇霊制限時間加速時間[秒]
     * Extra - Dark Phantom Limit Boost Time
     * Default Value  = 1000 */
    float darkPhantomLimitBoostTime;

    /* 闇霊制限時間加速時倍率
     * Extra - Dark Phantom Limit Boost Scale
     * Default Value  = 1000 */
    float darkPhantomLimitBoostScale;

    /* マルチプレイ無効化寿命
     * Extra - Multiplayer Disable Lifetime
     * Default Value  = 1 */
    float multiplayDisableLifeTime;

    /* 深淵霊マルチプレイ回数
     *   深淵エリアで、深淵霊がホストに入ってこれる回数
     * Extra - Abyss Multiplayer Limit
     *   The number of times the abyss spirit enters the host in the abyss area
     * Default Value  = 10 */
    unsigned char abyssMultiplayLimit;

    /* 霊体がワープするまでの最低時間[秒]
     * Extra - Phantom Warp Minimum Time
     * Default Value  = 5 */
    unsigned char phantomWarpMinimumTime;

    /* 黒水晶使用後に帰還するまでのディレイ時間[秒]
     * Extra - Phantom Return Delay Time
     * Default Value  = 5 */
    unsigned char phantomReturnDelayTime;

    /* 切断待ちのタイムアウト時間
     * Extra - Terminate Timeout Time
     * Default Value  = 30 */
    unsigned char terminateTimeoutTime;

    /* LAN抜きによるペナルティ加算値
     * Extra - Penalty Point LAN Disconnet */
    unsigned short penaltyPointLanDisconnect;

    /* サインアウトによるペナルティ加算値
     * Extra - Penalty Point Signout */
    unsigned short penaltyPointSignout;

    /* 電源断によるペナルティ加算値
     * Extra - Penalty Point Reboot */
    unsigned short penaltyPointReboot;

    /* ペナルティが発動するペナルティ値
     * Extra - Penalty Point Begin Penalize */
    unsigned short penaltyPointBeginPenalize;

    /* 「線の理」の販売制限時間[秒]
     * Extra - Penalty Forgive Item Limit Time */
    float penaltyForgiveItemLimitTime;

    /* 全域検索率：救援青霊[0-100]
     *   全域から侵入対象を検索する割合（％）
     * Extra - All Area Search Rate - Coop Blue
     *   Percentage of searching for intrusion targets from all areas (%) */
    unsigned char allAreaSearchRate_CoopBlue;

    /* 全域検索率：報復青霊[0-100]
     *   全域から侵入対象を検索する割合（％）
     * Extra - All Area Search Rate - Vs. Coop Blue
     *   Percentage of searching for intrusion targets from all areas (%) */
    unsigned char allAreaSearchRate_VsBlue;

    /* 全域検索率：鐘守灰霊[0-100]
     *   全域から侵入対象を検索する割合（％）
     * Extra - All Area Search Rate - Bell Guard
     *   Percentage of searching for intrusion targets from all areas (%) */
    unsigned char allAreaSearchRate_BellGuard;

    /* 血文字評価時のHP回復割合[0-100]
     * Extra - Blood Message Eval Heal Rate
     * Default Value  = 100 */
    unsigned char bloodMessageEvalHealRate;

    /* 小金霊成功帰還ホスト報酬ID
     * Extra - Small Gold Success Host Reward ID */
    unsigned int smallGoldSuccessHostRewardId;

    /* ドア付近プレイ領域無効化距離[m]
     *   マルチプレイ領域を区切る黒扉の周辺を、システム的に無効なプレイ領域（-1）にします。その際、無効領域を黒扉のOBJのバウンディングボックスの薄い方を、このパラメータで太らせます。
     * Extra - Door Invalid Play Area Extents
     *   The area around the black door that separates the multiplayer area is set to the systematically invalid play area (-1). At that time, make the invalid area thicker with this parameter on the thinner side of the OBJ's bounding box with a black door.
     * Default Value  = 1 */
    float doorInvalidPlayAreaExtents;

    /* サイン最大同時表示数
     * Extra - Sign Display Max
     * Default Value  = 10 */
    unsigned char signDisplayMax;

    /* 血痕最大同時表示数
     * Extra - Bloodstain Display Max
     * Default Value  = 7 */
    unsigned char bloodStainDisplayMax;

    /* 血文字最大同時表示数
     * Extra - Blood Message Display Max
     * Default Value  = 3 */
    unsigned char bloodMessageDisplayMax;

    /* 予約 */
    char pad00[9];

    /* 予約 */
    char pad10[32];

    /* 召喚メッセージが表示間隔[秒]
     * Quick Match - Summon Message Interval
     * Default Value  = 1 */
    float summonMessageInterval;

    /* ホスト定期更新リクエスト間隔[秒]
     * Quick Match - Host Register Update Time
     * Default Value  = 1 */
    float hostRegisterUpdateTime;

    /* ホストのゲスト参加待ちタイムアウト時間[秒]
     * Quick Match - Host Time Out Time
     * Default Value  = 1 */
    float hostTimeOutTime;

    /* ゲストのホストからの認証待ちタイムアウト時間[秒]
     * Quick Match - Guest Update Time
     * Default Value  = 1 */
    float guestUpdateTime;

    /* ゲストPlayNo同期待ちタイムアウト時間[秒]
     * Quick Match - Guest Player No Time Out Time
     * Default Value  = 1 */
    float guestPlayerNoTimeOutTime;

    /* ホストPlayNo同期待ちタイムアウト時間[秒]
     * Quick Match - Host Player No Time Out Time
     * Default Value  = 1 */
    float hostPlayerNoTimeOutTime;

    /* RequestSearchQuickMatchのlimit値
     *   本当はu8くらいで十分
     * Quick Match - Request Search Quick Match Limit
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int requestSearchQuickMatchLimit;

    /* アバター戦検索時の最大人数(未使用)
     *   本当はu8くらいで十分
     * Quick Match - Avatar Match Search Max
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int AvatarMatchSearchMax;

    /* バトルロイヤル戦検索時の最少人数(未使用)
     *   本当はu8くらいで十分
     * Quick Match - Battle Royale Match Search Min
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int BattleRoyalMatchSearchMin;

    /* バトルロイヤル戦検索時の最大人数(未使用)
     *   本当はu8くらいで十分
     * Quick Match - Battle Royale Match Search Max
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int BattleRoyalMatchSearchMax;

    /* 予約 */
    char pad11[8];

    /* 訪問対象者リスト取得最大値
     *   本当はu8くらいで十分
     * Visitor - Visitor List Max
     *   Actually u8 is enough
     * Default Value  = 1 */
    unsigned int VisitorListMax;

    /* 訪問待ちタイムアウト
     * Visitor - Visitor Time Out Time
     * Default Value  = 1 */
    float VisitorTimeOutTime;

    /* 訪問者リストダウンロード間隔[秒]
     * Visitor - Download Span
     * Default Value  = 1 */
    float DownloadSpan_2;

    /* 訪問先検索メッセージ表示間隔[秒]
     *   訪問ゲストが訪問先を探してる間に出すメッセージの表示間隔[秒]
     * Visitor - Visitor Guest Request Message Interval
     *   Display interval [seconds] of messages sent by visiting guests while searching for a destination
     * Default Value  = 1 */
    float VisitorGuestRequestMessageIntervalSec;

    /* 徘徊幻影寿命
     *   徘徊幻影寿命
     * Ghost Addition - Wandering Ghost Interval Lifetime
     *   Wandering illusion life
     * Default Value  = 40 */
    float wanderGhostIntervalLifeTime;

    /* 予約
     *   予約 */
    char pad13[12];

    /* 黄衣の翁待ちタイムアウト
     * Yellow Monk - Yellow Monk Timeout Time
     * Default Value  = 1 */
    float YellowMonkTimeOutTime;

    /* 黄衣の翁リストダウンロード間隔
     * Yellow Monk - Yellow Monk Download Span
     * Default Value  = 1 */
    float YellowMonkDownloadSpan;

    /* 黄衣の翁全体フロータイムアウト
     * Yellow Monk - Yellow Monk Overall Flow Time Out Time
     * Default Value  = 1 */
    float YellowMonkOverallFlowTimeOutTime;

    /* 予約 */
    char pad14_0[4];

    /* 予約 */
    char pad14_1[8];
} er_network_param_t;
