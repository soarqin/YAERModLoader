#pragma once

typedef struct game_system_common_param_s {
    /* 基本強靭度耐久値回復時間
     *   強靭度回復時間の基本値です。（秒）
     * Base Toughness Recovery Time
     *   This is the basic value of toughness recovery time. (Seconds) */
    float baseToughnessRecoverTime;

    /* キャラのイベント旋回アニメーション（左90°）
     *   「キャラの旋回」イベント用の左90°旋回アニメーションです。
     * Chr Event Turn - By Left 90
     *   This is a 90  left turn animation for the Character Turn event. */
    int chrEventTrun_byLeft90;

    /* キャラのイベント旋回アニメーション（右90°）
     *   「キャラの旋回」イベント用の右90°旋回アニメーションです。
     * Chr Event Turn - By Right 90
     *   This is a 90  right turn animation for the Character Turn event. */
    int chrEventTrun_byRight90;

    /* キャラのイベント旋回アニメーション（左180°）
     *   「キャラの旋回」イベント用の左180°旋回アニメーションです。
     * Chr Event Turn - By Left 180
     *   This is a 180  left turn animation for the Character Turn event. */
    int chrEventTrun_byLeft180;

    /* キャラのイベント旋回アニメーション（右180°）
     *   「キャラの旋回」イベント用の右180°旋回アニメーションです。
     * Chr Event Turn - By Right 180
     *   This is a 180  right turn animation for the Character Turn event. */
    int chrEventTrun_byRight180;

    /* キャラのイベント旋回90°アニメーション開始角度
     *   「キャラの旋回」イベント用の90°旋回アニメーションを適用する角度の開始角度。この角度より小さい角度でイベントが始まった場合は、システム旋回が行われます
     * Chr Event Turn - 90 Turn Start Angle
     *   The starting angle of the angle to which the 90  swivel animation for the Character Swirl event is applied. If the event starts at an angle smaller than this angle, a system turn will occur. */
    short chrEventTrun_90TurnStartAngle;

    /* キャラのイベント旋回180°アニメーション開始角度
     *   「キャラの旋回」イベント用の180°旋回アニメーションを適用する角度の開始角度。
     * Chr Event Turn - 180 Turn Start Angle
     *   The starting angle of the angle to which the 180  swivel animation for the Character Swirl event is applied. */
    short chrEventTrun_180TurnStartAngle;

    /* ステルス攻撃被ダメージ倍率
     *   ステルス攻撃被ダメージ倍率
     * Stealth Attack Multiplier
     *   Stealth attack damage multiplier */
    float stealthAtkDamageRate;

    /* はじかれ時ガード成功時ダメージカット率
     *   はじかれ時ガード成功時ダメージカット率。最終ダメージに乗算
     * Weapon Rebel Absorption on Successful Guard
     *   Damage cut rate when the guard is successful when repelled. Multiply the final damage */
    float flickDamageCutRateSuccessGurad;

    /* NPC会話のアニメ再生開始する差分角度
     *   NPC会話の会話中モーションのアニメ再生開始する差分角度です。
     * NPC Talk Anim - Start Diff Angle
     *   This is the difference angle at which the animation playback of the motion during the conversation of the NPC conversation starts. */
    float npcTalkAnimBeginDiffAngle;

    /* NPC会話のアニメ再生停止する差分角度
     *   NPC会話の会話中モーションのアニメ再生停止する差分角度です。
     * NPC Talk Anim - End Diff Angle
     *   This is the difference angle at which the animation playback of the motion during the conversation of the NPC conversation is stopped. */
    float npcTalkAnimEndDiffAngle;

    /* ネムリアイテム取得範囲_アクションボタンパラID
     *   ネムリアイテム取得範囲_アクションボタンパラID。TAEフラグ「イベント＞ネムリアイテム登録」で上書きしないときのデフォルト値として使われる。
     * Sleep Collector Item Action Button Param ID
     *   Nemuri Item Acquisition Range_Action Button Para ID. TAE flag Used as the default value when not overwriting with Event> Nemuri item registration.
     * Default Value  = -1 */
    int sleepCollectorItemActionButtonParamId;

    /* バディアイテム許可_SFX発生間隔[s]
     *   バディアイテム許可_SFX発生間隔[s]
     * Spirit Summon Item - SFX Interval
     *   Buddy item permission_SFX occurrence interval [s] */
    float allowUseBuddyItem_sfxInterval;

    /* バディアイテム許可_SFX発生PCダミポリID
     *   バディアイテム許可_SFX発生PCダミポリID
     * Spirit Summon Item - SFX Dummy Poly ID
     *   Buddy Item Permission_SFX Occurrence PC Damipoli ID
     * Default Value  = -1 */
    int allowUseBuddyItem_sfxDmyPolyId;

    /* バディアイテム許可_SFX発生馬ダミポリID_騎乗時
     *   バディアイテム許可_SFX発生馬ダミポリID_騎乗時
     * Spirit Summon Item - SFX Dummy Poly ID (Horse)
     *   Buddy item permission_SFX generated horse Damipoli ID_when riding
     * Default Value  = -1 */
    int allowUseBuddyItem_sfxDmyPolyId_horse;

    /* バディアイテム許可_発生SFXID
     *   バディアイテム許可_発生SFXID
     * Spirit Summon Item - SFX ID
     *   Buddy Item Permission_Occurrence SFXID
     * Default Value  = -1 */
    int allowUseBuddyItem_sfxId;

    /* バディ召喚中_起動範囲内_SFX発生間隔[s]
     *   バディ召喚中_起動範囲内_SFX発生間隔[s]
     * Spirit Summon - Activation Range - SFX Interval
     *   Buddy Summoning_Initial Range_SFX Occurrence Interval [s] */
    float onBuddySummon_inActivateRange_sfxInterval;

    /* バディ召喚中_起動範囲内_SFX発生PCダミポリID
     *   バディ召喚中_起動範囲内_SFX発生PCダミポリID
     * Spirit Summon - Activation Range - SFX Dummy Poly ID
     *   Buddy Summoning_Initial Range_SFX Occurrence PC Damipoli ID
     * Default Value  = -1 */
    int onBuddySummon_inActivateRange_sfxDmyPolyId;

    /* バディ召喚中_起動範囲内_SFX発生馬ダミポリID_騎乗時
     *   バディ召喚中_起動範囲内_SFX発生馬ダミポリID_騎乗時
     * Spirit Summon - Activation Range - SFX Dummy Poly ID (Horse)
     *   Buddy Summoning_Initial Range_SFX Generated Horse Damipoli ID_When Riding
     * Default Value  = -1 */
    int onBuddySummon_inActivateRange_sfxDmyPolyId_horse;

    /* バディ召喚中_起動範囲内_発生SFXID
     *   バディ召喚中_起動範囲内_発生SFXID
     * Spirit Summon - Activation Range - SFX ID
     *   Buddy Summoning_Initial Range_Occurrence SFXID
     * Default Value  = -1 */
    int onBuddySummon_inActivateRange_sfxId;

    /* バディ召喚中_起動範囲内特殊効果ID_PC用
     *   バディ召喚中_起動範囲内特殊効果ID_PC用
     * Spirit Summon - Activation Range - Player SpEffect ID
     *   Buddy Summoning_Initial range Special effect ID_For PC
     * Default Value  = -1 */
    int onBuddySummon_inActivateRange_spEffectId_pc;

    /* バディ召喚中_警告範囲内特殊効果ID_PC用
     *   バディ召喚中_警告範囲内特殊効果ID_PC用
     * Spirit Summon - Warn Range - Player SpEffect ID
     *   Buddy Summoning_Warning Range Special Effect ID_For PC
     * Default Value  = -1 */
    int onBuddySummon_inWarnRange_spEffectId_pc;

    /* バディ召喚中_バディ帰還時特殊効果ID_PC用
     *   バディ召喚中_バディ帰還時特殊効果ID_PC用
     * Spirit Summon - Unsummoned - Player SpEffect ID
     *   Buddy Summoning_Buddy Return Special Effect ID_For PC
     * Default Value  = -1 */
    int onBuddySummon_atBuddyUnsummon_spEffectId_pc;

    /* バディ召喚中_警告範囲内特殊効果ID_バディ用
     *   バディ召喚中_警告範囲内特殊効果ID_バディ用
     * Spirit Summon - Warn Range - Spirit SpEffect ID
     *   Buddy Summoning_Warning Range Special Effect ID_For Buddy
     * Default Value  = -1 */
    int onBuddySummon_inWarnRange_spEffectId_buddy;

    /* 朝のインゲーム時間（時）
     *   朝のインゲーム時間（時）。会話で使用します。
     * Morning - In-game Hour
     *   Morning in-game time (hours). Used in conversation. */
    unsigned char morningIngameHour;

    /* 朝のインゲーム時間（分）
     *   朝のインゲーム時間（分）。会話で使用します。
     * Morning - In-game Minute
     *   Morning in-game time (minutes). Used in conversation. */
    unsigned char morningIngameMinute;

    /* 朝のインゲーム時間（秒）
     *   朝のインゲーム時間（秒）。会話で使用します。
     * Morning - In-game Second
     *   Morning in-game time (seconds). Used in conversation. */
    unsigned char morningIngameSecond;

    /* 昼のインゲーム時間（時）
     *   昼のインゲーム時間（時）。会話で使用します。
     * Noon - In-game Hour
     *   Daytime in-game time (hours). Used in conversation. */
    unsigned char noonIngameHour;

    /* 昼のインゲーム時間（分）
     *   昼のインゲーム時間（分）。会話で使用します。
     * Noon - In-game Minute
     *   Daytime in-game time (minutes). Used in conversation. */
    unsigned char noonIngameMinute;

    /* 昼のインゲーム時間（秒）
     *   昼のインゲーム時間（秒）。会話で使用します。
     * Noon - In-game Second
     *   Daytime in-game time (seconds). Used in conversation. */
    unsigned char noonIngameSecond;

    /* 夜のインゲーム時間（時）
     *   夜のインゲーム時間（時）。会話で使用します。
     * Night - In-game Hour
     *   Night in-game time (hours). Used in conversation. */
    unsigned char nightIngameHour;

    /* 夜のインゲーム時間（分）
     *   夜のインゲーム時間（分）。会話で使用します。
     * Night - In-game Minute
     *   Night in-game time (minutes). Used in conversation. */
    unsigned char nightIngameMinute;

    /* 夜のインゲーム時間（秒）
     *   夜のインゲーム時間（秒）。会話で使用します。
     * Night - In-game Second
     *   Night in-game time (seconds). Used in conversation. */
    unsigned char nightIngameSecond;

    /* AI視界倍率_朝_開始時刻(時)
     *   AI視界倍率_朝_開始時刻(時)
     * AI Sight Rate Start - Morning Hour
     *   AI visibility magnification_morning_start time (hour) */
    unsigned char aiSightRateStart_Morning_Hour;

    /* AI視界倍率_朝_開始時刻(分)
     *   AI視界倍率_朝_開始時刻(分)
     * AI Sight Rate Start - Morning Minute
     *   AI visibility magnification_morning_start time (minutes) */
    unsigned char aiSightRateStart_Morning_Minute;

    /* AI視界倍率_昼_開始時刻(時)
     *   AI視界倍率_昼_開始時刻(時)
     * AI Sight Rate Start - Noon Hour
     *   AI visibility magnification_day_start time (hour) */
    unsigned char aiSightRateStart_Noon_Hour;

    /* AI視界倍率_昼_開始時刻(分)
     *   AI視界倍率_昼_開始時刻(分)
     * AI Sight Rate Start - Noon Minute
     *   AI visibility magnification_day_start time (minutes) */
    unsigned char aiSightRateStart_Noon_Minute;

    /* AI視界倍率_夕_開始時刻(時)
     *   AI視界倍率_夕_開始時刻(時)
     * AI Sight Rate Start - Evening Hour
     *   AI visibility magnification_evening_start time (hour) */
    unsigned char aiSightRateStart_Evening_Hour;

    /* AI視界倍率_夕_開始時刻(分)
     *   AI視界倍率_夕_開始時刻(分)
     * AI Sight Rate Start - Evening Minute
     *   AI visibility magnification_evening_start time (minutes) */
    unsigned char aiSightRateStart_Evening_Minute;

    /* AI視界倍率_夜_開始時刻(時)
     *   AI視界倍率_夜_開始時刻(時)
     * AI Sight Rate Start - Night Hour
     *   AI visibility magnification_night_start time (hour) */
    unsigned char aiSightRateStart_Night_Hour;

    /* AI視界倍率_夜_開始時刻(分)
     *   AI視界倍率_夜_開始時刻(分)
     * AI Sight Rate Start - Night Minute
     *   AI visibility magnification_night_start time (minutes) */
    unsigned char aiSightRateStart_Night_Minute;

    /* AI視界倍率_深夜_開始時刻(時)
     *   AI視界倍率_深夜_開始時刻(時)
     * AI Sight Rate Start - Midnight Hour
     *   AI visibility magnification_midnight_start time (hour) */
    unsigned char aiSightRateStart_Midnight_Hour;

    /* AI視界倍率_深夜_開始時刻(分)
     *   AI視界倍率_深夜_開始時刻(分)
     * AI Sight Rate Start - Midnight Minute
     *   AI visibility magnification_midnight_start time (minutes) */
    unsigned char aiSightRateStart_Midnight_Minute;

    /* SA大ダメージヒット演出SFX_発生条件SAダメージ閾値比率[％]
     *   SA大ダメージヒット演出SFX_発生条件SAダメージ閾値比率[％]
     * Poise - Large Damage Hit SFX Threshold
     *   SA large damage hit production SFX_ Occurrence condition SA damage threshold ratio [%] */
    unsigned char saLargeDamageHitSfx_Threshold;

    /* SA大ダメージヒット演出SFX_SFXID
     *   SA大ダメージヒット演出SFX_SFXID
     * Poise - Large Damage Hit SFX ID
     *   SA heavy damage hit production SFX_SFXID */
    int saLargeDamageHitSfx_SfxId;

    /* 安全位置から離れてサインを作成できる距離[m]
     *   PCの最後の安全位置から離れてサインを作成できる距離[m]
     * Sign Creatable Distance from Safe Position
     *   Distance at which you can create a sign away from the last safe position on your PC [m] */
    float signCreatableDistFromSafePos;

    /* 再召喚が発生するホストとゲストの距離[m]
     *   再召喚が発生するホストとゲストの距離[m]
     * Guest Resummon Distance
     *   Distance between host and guest where resummoning occurs [m] */
    float guestResummonDist;

    /* ゲストがホストから離れそうになってることを通知する距離[m]
     *   ゲストがホストから離れそうになってることを通知する距離[m]。この距離より離れたら通知する。
     * Guest Leaving Message - Max Distance
     *   Distance [m] to notify the guest that they are about to leave the host. Notify me when I'm farther than this distance. */
    float guestLeavingMessageDistMax;

    /* ゲストがホストから離れそうになってることを再通知可能にする距離[m]
     *   ゲストがホストから離れそうになってることを再通知可能にする距離[m]。この距離より近づくまで再通知しない。
     * Guest Leaving Message - Min Distance
     *   Distance [m] that allows the guest to be re-notified that they are about to leave the host. Do not re-notify until closer than this distance. */
    float guestLeavingMessageDistMin;

    /* ゲストがホストから離れられる最大距離[m] 
     *   ゲストがホストから離れられる最大距離[m]。この距離より離れた状態で一定時間経過するとセッション脱退する。
     * Guest Leave Session Distance
     *   Maximum distance [m] that a guest can leave the host. If a certain period of time elapses while the distance is longer than this distance, the session will be withdrawn. */
    float guestLeaveSessionDist;

    /* リトライエリア半径_デフォルト値(m)
     *   リトライエリア半径_デフォルト値(m)。MapStudioのイベントタイプ「リトライポイント」で半径も領域も未設定の場合のデフォルト値として使われる。
     * Marika Stake Area Radius
     *   Retry area radius_default value (m). It is used as the default value when the radius and area are not set in the event type Retry Point of MapStudio.
     * Default Value  = -1 */
    float retryPointAreaRadius;

    /* ネムリアイテム取得可能時に発動する特殊効果ID
     *   ネムリアイテム取得可能時に発動する特殊効果ID。TAEフラグ「イベント＞ネムリアイテム登録」で上書きしないときのデフォルト値として使われる。
     * Sleep Collector SpEffect ID
     *   A special effect ID that activates when a Nemuri item can be acquired. TAE flag Used as the default value when not overwriting with Event> Nemuri item registration.
     * Default Value  = -1 */
    int sleepCollectorSpEffectId;

    /* 「HP最大以下で回復」特殊効果完了通知特殊効果ID
     *   「HP最大以下で回復」が完了したことを通知する特殊効果のID。主にマルチの同期用に使われる。 
     * Recovery below HP Max - Notification SpEffect ID
     *   ID of the special effect that notifies that Recovery below HP maximum is completed. Mainly used for multi synchronization. */
    int recoverBelowMaxHpCompletionNoticeSpEffectId;

    /* HPエスト吸収演出SFXID
     *   侵入者撃破時などにHPエスト瓶の使用回数を回復する際の吸収演出SFXID
     * HP Flask - Absorption SFX ID for Intruder Flask Restoration
     *   Absorption effect SFXID when recovering the number of times the HP Est bottle has been used when defeating an intruder */
    int estusFlaskRecovery_AbsorptionProductionSfxId_byHp;

    /* MPエスト吸収演出SFXID
     *   侵入者撃破時などにMPエスト瓶の使用回数を回復する際の吸収演出SFXID
     * FP Flask - Absorption SFX ID for Intruder Flask Restoration
     *   Absorption effect SFXID when recovering the number of times the MP Est bottle has been used when defeating an intruder */
    int estusFlaskRecovery_AbsorptionProductionSfxId_byMp;

    /* 復活特殊効果発動判定用特殊効果ID
     *   復活特殊効果が発動したことを通知する特殊効果のID。主にマルチの同期用に使われる。 
     * Resurrection - Notification SpEffect ID
     *   ID of the special effect that notifies that the resurrection special effect has been activated. Mainly used for multi synchronization. */
    int respawnSpecialEffectActiveCheckerSpEffectId;

    /* バディ召喚中_起動範囲内特殊効果ID_バディ用
     *   バディ召喚中_起動範囲内特殊効果ID_バディ用
     * Spirit Summon - Activation Range - Spirit SpEffect ID
     *   Buddy Summoning_Initial Range Special Effect ID_For Buddy
     * Default Value  = -1 */
    int onBuddySummon_inActivateRange_spEffectId_buddy;

    /* エスト吸収SFX再生開始からエスト追加処理を行うまでの時間
     *   エスト吸収SFX再生開始からエスト追加処理を行うまでの時間
     * Flask - Absorption SFX Playback Time
     *   Time from the start of est absorption SFX playback to the start of est addition processing */
    float estusFlaskRecovery_AddEstusTime;

    /* マルチ時エネミー撃破時取得ソウル補正値_ホスト
     *   マルチプレイで通常敵を撃破した時のホストの取得ソウル量の補正値
     * Rune Absorption Multiplier - Normal Enemy - Host
     *   Correction value of the amount of soul acquired by the host when defeating a normal enemy in multiplayer */
    float defeatMultiModeEnemyOfSoulCorrectRate_byHost;

    /* マルチ時エネミー撃破時取得ソウル補正値_協力霊
     *   マルチプレイで通常敵を撃破した時の協力霊の取得ソウル量の補正値
     * Rune Absorption Multiplier - Normal Enemy - Friendly Phantom
     *   Correction value of the amount of soul acquired by cooperating spirits when defeating a normal enemy in multiplayer */
    float defeatMultiModeEnemyOfSoulCorrectRate_byTeamGhost;

    /* マルチ時ボス撃破時取得ソウル補正値_ホスト
     *   マルチプレイでボスを撃破した時のホストの取得ソウル量の補正値
     * Rune Absorption Multiplier - Boss - Host
     *   Correction value of the amount of soul acquired by the host when defeating the boss in multiplayer */
    float defeatMultiModeBossOfSoulCorrectRate_byHost;

    /* マルチ時ボス撃破時取得ソウル補正値_協力霊
     *   マルチプレイでボスを撃破した時の協力霊の取得ソウル量の補正値
     * Rune Absorption Multiplier - Boss - Friendly Phantom
     *   Correction value of the amount of soul acquired when the boss is defeated in multiplayer */
    float defeatMultiModeBossOfSoulCorrectRate_byTeamGhost;

    /* 敵キャラのHPゲージが画面上に見切れないようにするためのオフセット
     *   敵のHPゲージが画面上に見切れた時に画面内に収めるオフセット値[pixel]（FullHD基準）
     * Enemy HP Gauge - Cutoff Pixel Offset
     *   Offset value [pixel] (FullHD standard) that fits in the screen when the enemy's HP gauge is cut off on the screen */
    unsigned short enemyHpGaugeScreenOffset_byUp;

    /* プレイ領域収集半径
     *   PC周辺のプレイ領域の収集半径
     * Play Region Collection Distance
     *   Collection radius of the play area around the PC */
    unsigned short playRegionCollectDist;

    /* 「敵探知」時弾丸発射位置ダミポリID
     *   探知弾丸の発射位置ダミポリID
     * Enemy Detection - Shoot Bullet Dummy Poly ID
     *   Detect bullet firing position Damipoli ID */
    unsigned short enemyDetectionSpEffect_ShootBulletDummypolyId;

    /* 大ルーン：グレーターデーモン侵入時付与道具個数
     *   大ルーン：グレーターデーモン侵入時付与道具個数
     * Phantom Great Rune - Amount given for Invasion
     *   Large Rune Number of tools granted when the Greater Demon invades */
    unsigned short bigRuneGreaterDemonBreakInGoodsNum;

    /* 大ルーン：グレーターデーモン侵入時付与道具アイテムID
     *   大ルーン：グレーターデーモン侵入時付与道具アイテムID
     * Phantom Great Rune - Goods ID
     *   Large Rune Greater Demon Invasion Tool Item ID
     * Default Value  = -1 */
    int bigRuneGreaterDemonBreakInGoodsId;

    /* 大ジャンプ領域SFXID
     *   騎乗大ジャンプ領域のSFXID
     * Spiritspring Jump SFX ID
     *   SFX ID in the riding large jump area */
    int rideJumpRegionDefaultSfxId;

    /* 共通_騎乗特攻倍率
     *   騎乗特攻時に補正する倍率
     * Poise Damage - Vs. Ride Attack
     *   Magnification to be corrected at the time of riding special attack
     * Default Value  = 1 */
    float saAttackRate_forVsRideAtk;

    /* ネムリアイテム抽選時に敵側にかかる特殊効果
     *   ネムリアイテム抽選時に敵側にかかる特殊効果
     * Sleep Collector Item Lot - Enemy SpEffect ID
     *   Special effects on the enemy side when drawing Nemuri items
     * Default Value  = -1 */
    int enemySpEffectIdAfterSleepCollectorItemLot;

    /* 周回保留時マップUID
     *   周回保留時マップUID、8桁で入力（例…m60_42_36_00 -> 60423600）
     * After Ending Map UID
     *   Map UID on hold for lap, enter in 8 digits (example ... m60_42_36_00-> 60423600) */
    int afterEndingMapUid;

    /* 周回保留時復帰ポイント
     *   周回保留時復帰ポイントのエンティティID
     * After Ending Return Point Entity ID
     *   Entity ID of return point on hold */
    unsigned int afterEndingReturnPointEntityId;

    /* 「敵探知」時発射弾丸ID_協力指輪_赤狩り
     *   敵の勢力/タイプによって飛ばす弾丸のID(マルチ自動発射でも使う)
     * Enemy Detection - Bullet ID (Co-op/Anti-Invader)
     *   Bullet ID to fly depending on enemy power / type (also used for multi-automatic firing) */
    int enemyDetectionSpEffect_BulletId_byCoopRing_RedHunter;

    /* 「敵探知」時発射弾丸ID_侵入オーブ_なし
     *   敵の勢力/タイプによって飛ばす弾丸のID(マルチ自動発射でも使う)
     * Enemy Detection - Bullet ID (Invader)
     *   Bullet ID to fly depending on enemy power / type (also used for multi-automatic firing) */
    int enemyDetectionSpEffect_BulletId_byInvadeOrb_None;

    /* チュートリアル判定用：遠見台にアクセスした時にONにするイベントフラグ
     *   チュートリアル判定用：遠見台にアクセスした時にONにするイベントフラグ
     * Tutorial Flag Accessing Birdseye Telescope
     *   For tutorial judgment Event flag to turn on when accessing the distant view */
    unsigned int tutorialFlagOnAccessDistView;

    /* チュートリアル判定用：リトライポイントにアクセスした時にONにするイベントフラグ
     *   チュートリアル判定用：リトライポイントにアクセスした時にONにするイベントフラグ
     * Tutorial Flag Accessing Marika Stake
     *   For tutorial judgment Event flag to turn on when accessing the retry point */
    unsigned int tutorialFlagOnAccessRetryPoint;

    /* チュートリアル判定用：集団を倒してグループ報酬が入った時にONにするイベントフラグ
     *   チュートリアル判定用：集団を倒してグループ報酬が入った時にONにするイベントフラグ
     * Tutorial Flag Enemy Group Flask Restoration
     *   For tutorial judgment Event flag to turn on when group reward is entered after defeating a group */
    unsigned int tutorialFlagOnGetGroupReward;

    /* チュートリアル判定用：騎乗大ジャンプポイントに入った時にONにするイベントフラグ
     *   チュートリアル判定用：騎乗大ジャンプポイントに入った時にONにするイベントフラグ
     * Tutorial Flag Entering Spiritspring Jump
     *   For tutorial judgment Event flag to turn on when entering the riding big jump point */
    unsigned int tutorialFlagOnEnterRideJumpRegion;

    /* チュートリアル判定用：騎乗大ジャンプポイントを○[m]拡張して内外判定
     *   チュートリアル判定用：騎乗大ジャンプポイントを○[m]拡張して内外判定。○[m]の値をここに設定する。
     * Tutorial Check Spiritspring Jump Region Range
     *   For tutorial judgment The riding large jump point is expanded by  [m] to judge inside and outside.  Set the value of [m] here. */
    float tutorialCheckRideJumpRegionExpandRange;

    /* リトライポイント起動時のPCアニメID
     *   リトライポイント起動時のPCアニメID。-1の場合は再生しない。
     * Activated Marika Stake Player Animation ID
     *   PC animation ID when retry point is started. If it is -1, it will not be played.
     * Default Value  = -1 */
    int retryPointActivatedPcAnimId;

    /* リトライポイント起動時のダイアログ表示の遅延時間[秒]
     *   リトライポイント起動時のダイアログ表示の遅延時間[秒]
     * Activated Marika Stake Dialog Display Delay
     *   Delay time of dialog display when retry point is started [seconds] */
    float retryPointActivatedDialogDelayTime;

    /* リトライポイント起動時のダイアログのテキストID
     *   リトライポイント起動時のダイアログのテキストID。EventText_ForMap.xlsm のテキストを設定する。-1の場合はダイアログを出さない。
     * Activated Marika Stake Dialog Text ID
     *   The text ID of the dialog when the retry point is started. Set the text in EventText_ForMap.xlsm. If it is -1, the dialog is not displayed.
     * Default Value  = -1 */
    int retryPointActivatedDialogTextId;

    /* サイン溜まり起動時のPCアニメID
     *   サイン溜まり起動時のPCアニメID。-1の場合は再生しない。
     * Opened Summoning Pool Player Animation ID
     *   PC animation ID at the time of sign accumulation startup. If it is -1, it will not be played.
     * Default Value  = -1 */
    int signPuddleOpenPcAnimId;

    /* サイン溜まり起動時のダイアログ表示の遅延時間[秒]
     *   サイン溜まり起動時のダイアログ表示の遅延時間[秒]
     * Opened Summoning Pool Dialog Display Delay
     *   Delay time of dialog display at startup of sign accumulation [seconds] */
    float signPuddleOpenDialogDelayTime;

    /* 「死者の活性」特殊効果発動時弾丸ID
     *   「死者の活性」特殊効果が発動したときに発射する弾丸ID
     * Corpse Explosion - Bullet ID
     *   Bullet ID fired when the Activity of the Dead special effect is activated */
    int activityOfDeadSpEffect_BulletId;

    /* 「死者の活性」特殊効果発動時弾丸発生位置ダミポリID
     *   「死者の活性」特殊効果が発動したときに弾丸が発生する位置のダミポリID
     * Corpse Explosion - Bullet Dummy Poly ID
     *   Damipoli ID at the position where the bullet is generated when the Activity of the Dead special effect is activated */
    int activityOfDeadSpEffect_ShootBulletDummypolyId;

    /* 「死者の活性」特殊効果発動時の死体のフェードアウト時間
     *   「死者の活性」特殊効果が発動したときに死体がフェードアウトする際のフェード時間
     * Corpse Explosion - Dead Fadeout Time
     *   Fade time when the corpse fades out when the Activity of the Dead special effect is activated */
    float activityOfDeadSpEffect_DeadFadeOutTime;

    /* 投げ開始時のネットワーク情報による遷移を無視する時間
     *   投げ開始時のネットワーク情報による遷移を無視する時間
     * Ignore Network State Sync Time for Throw
     *   Time to ignore transitions due to network information at the start of throwing */
    float ignorNetStateSyncTime_ForThrow;

    /* マルチプレペナルティ：LAN切断
     *   マルチプレペナルティ：LAN切断
     * Muliplayer Disconnect LAN Disconnect Penalty Points
     *   Multi-pre-penalty LAN disconnection */
    unsigned short netPenaltyPointLanDisconnect;

    /* マルチプレペナルティ：プロフィールサインアウト
     *   マルチプレペナルティ：プロフィールサインアウト
     * Muliplayer Disconnect Profile Signout Penalty Points
     *   Multi-pre-penalty Profile sign-out */
    unsigned short netPenaltyPointProfileSignout;

    /* マルチプレペナルティ：電源断
     *   マルチプレペナルティ：電源断
     * Muliplayer Disconnect Reboot Penalty Points
     *   Multi-pre-penalty Power off */
    unsigned short netPenaltyPointReboot;

    /* マルチプレペナルティ：サスペンド・一時停止
     *   マルチプレペナルティ：サスペンド・一時停止
     * Muliplayer Disconnect Suspend Penalty Points
     *   Multi-pre-penalty Suspend / Pause */
    unsigned short netPnaltyPointSuspend;

    /* マルチプレペナルティ：理の骨の生成（販売）開始待ち時間
     *   マルチプレペナルティ：理の骨の生成（販売）開始待ち時間(秒)
     * Muliplayer Disconnect Delay before White Ring is given
     *   Multi-pre-penalty Waiting time (seconds) to start the generation (sale) of the bone of reason */
    float netPenaltyForgiveItemLimitTime;

    /* マルチプレペナルティ：ペナルティ判定ポイント
     *   マルチプレペナルティ：ペナルティ判定ポイント
     * Multiplayer Disconnect Point Threshold
     *   Multi-pre-penalty Penalty judgment points */
    unsigned short netPenaltyPointThreshold;

    /* 未操作判定時間
     *   マルチで一定期間操作ない人を退出させるためのもの。単位は秒。
     * Multiplayer Timeout due to lack of Activity
     *   It is for leaving people who have not operated for a certain period of time in multiplayer. The unit is seconds. */
    unsigned short uncontrolledMoveThresholdTime;

    /* 「敵探知」時発射弾丸ID_敵対NPC/敵キャラ
     *   敵意の探知に失敗したときに敵対NPC/敵キャラに飛ばす弾丸のID
     * Enemy Detection - Bullet ID (NPC Enemy)
     *   Bullet ID to shoot to hostile NPCs / enemy characters when hostility detection fails */
    int enemyDetectionSpEffect_BulletId_byNpcEnemy;

    /* 「死者の活性ターゲット検索」対象にかける特殊効果ID 
     *   検索した対象にかける特殊効果
     * Corpse Explosion - On Hit SpEffect
     *   Special effects applied to the searched target */
    int activityOfDeadTargetSearchSpEffect_OnHitSpEffect;

    /* 「死者の活性ターゲット検索」距離 
     *   検索可能最大距離
     * Corpse Explosion - Max Length
     *   Maximum searchable distance */
    float activityOfDeadTargetSearchSpEffect_MaxLength;

    /* 視界_最低保証距離[倍率換算]
     *   視界_最低保証距離[倍率換算]
     * Field of View - Minimum Guaranteed Distance
     *   Field of view_Minimum guaranteed distance [magnification conversion] */
    float sightRangeLowerPromiseRate;

    /* SA大ダメージヒット演出SFX_発生条件SAダメージ必要最低値[pt]
     *   SA大ダメージヒット演出SFX_発生条件SAダメージ必要最低値[pt]
     * Poise Large Damage Hit SFX - Minimum Damage
     *   SA large damage hit production SFX_ Occurrence condition SA damage minimum required [pt]
     * Default Value  = -1 */
    short saLargeDamageHitSfx_MinDamage;

    /* SA大ダメージヒット演出SFX_発生条件SAダメージ強制発生最低値[pt]
     *   SA大ダメージヒット演出SFX_発生条件SAダメージ強制発生最低値[pt]
     * Poise Large Damage Hit SFX - Force Damage
     *   SA large damage hit production SFX_ Occurrence condition SA damage forced occurrence minimum value [pt]
     * Default Value  = -1 */
    short saLargeDamageHitSfx_ForceDamage;

    /* ソロ侵入最大ポイント
     *   ソロ侵入ポイントの最大値。この値を越えたときにソロで侵入されるようになる
     * Maximum Solo Intrusion Point
     *   Maximum solo intrusion point. When this value is exceeded, it will be invaded solo. */
    unsigned int soloBreakInMaxPoint;

    /* NPC会話のボイス再生タイムアウト時間
     *   NPC会話のボイス再生タイムアウト時間。この時間経過してもボイス再生が終わらない場合は次のメッセージへ進む
     * NPC Talk Timeout Threshold
     *   Voice playback timeout for NPC conversations. If voice playback does not end after this time, proceed to the next message. */
    float npcTalkTimeOutThreshold;

    /* プレイログの送信間隔
     *   アイテム使用ログ などをサーバーへ送信する間隔
     * Send Play Log Interval
     *   Interval to send item usage log etc. to the server */
    float sendPlayLogIntervalTime;

    /* 七色石の最大設置数
     *   七色石の最大設置数
     * Rainbow Stone - Max SFX Count
     *   Maximum number of seven-colored stones installed */
    unsigned char item370_MaxSfxNum;

    /* キャラディアクティベート中にアクティベート許可する距離[m]
     *   キャラディアクティベート中にアクティベート許可する距離（オープン配置キャラのみ有効）
     * Chr Activate Distance - For Leave Player
     *   Distance allowed to activate during character deactivation (valid only for open placement characters) */
    unsigned char chrActivateDist_forLeavePC;

    /* マルチ弱体化レベル補正係数１
     *   マルチ時ステータス弱体化。ホストのレベル加算補正
     * Coop - Host Level Addition Correction
     *   Weakened stats when multiplayer. Host level addition correction */
    short summonDataCoopMatchingLevelUpperAbs;

    /* マルチ弱体化レベル補正係数２
     *   マルチ時ステータス弱体化。ホストのレベル倍率補正
     * Coop - Host Level Magnification Correction
     *   Weakened stats when multiplayer. Host level magnification correction */
    short summonDataCoopMatchingLevelUpperRel;

    /* マルチ弱体化最大武器補正係数
     *   マルチ時ステータス弱体化。最大武器強化レベル補正
     * Coop - Maximum Weapon Reinforcement Correction
     *   Weakened stats when multiplayer. Maximum weapon enhancement level correction */
    short summonDataCoopMatchingWepLevelMul;

    /* バーサーカーサインを拾った時のまたたび効果用弾丸ID
     *   サイン位置に特殊効果用の弾丸を発生させる際の弾丸ID
     * Pickup Berserker Sign - Bullet ID
     *   Bullet ID when generating a bullet for special effects at the sign position */
    int pickUpBerserkerSignSpEffectBulletId;

    /* バーサーカーがPC自力殺害に成功演出用特殊効果ID
     *   バーサーカーがPC自力殺害に成功した際に専用の演出を再生する特殊効果
     * Berserker Success Player Kill - SpEffect ID
     *   Special effect to play a special effect when Berserker succeeds in killing the PC by himself */
    int succeedBerserkerSelfKillingEffectId;

    /* レベルシンク適用判定係数１白
     *   レベルシンク適用するかどうかのソウルレベル係数
     * Friendly Phantom - Level Coefficient 1
     *   Soul level coefficient of whether to apply level sync */
    unsigned char machingLevelWhiteSignUpperRel;

    /* レベルシンク適用判定係数２白
     *   レベルシンク適用するかどうかのソウルレベル係数
     * Friendly Phantom - Level Coefficient 2
     *   Soul level coefficient of whether to apply level sync */
    unsigned char machingLevelWhiteSignUpperAbs;

    /* レベルシンク適用判定係数１赤
     *   レベルシンク適用するかどうかのソウルレベル係数
     * Hostile Phantom - Level Coefficient 1
     *   Soul level coefficient of whether to apply level sync */
    unsigned char machingLevelRedSignUpperRel;

    /* レベルシンク適用判定係数２赤
     *   レベルシンク適用するかどうかのソウルレベル係数
     * Hostile Phantom - Level Coefficient 2
     *   Soul level coefficient of whether to apply level sync */
    unsigned char machingLevelRedSignUpperAbs;

    /* レベルシンク適用判定最大武器強化レベル係数０白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 0
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_0;

    /* レベルシンク適用判定最大武器強化レベル係数１白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 1
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_1;

    /* レベルシンク適用判定最大武器強化レベル係数２白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 2
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_2;

    /* レベルシンク適用判定最大武器強化レベル係数３白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 3
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_3;

    /* レベルシンク適用判定最大武器強化レベル係数４白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 4
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_4;

    /* レベルシンク適用判定最大武器強化レベル係数５白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 5
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_5;

    /* レベルシンク適用判定最大武器強化レベル係数６白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 6
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_6;

    /* レベルシンク適用判定最大武器強化レベル係数７白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 7
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_7;

    /* レベルシンク適用判定最大武器強化レベル係数８白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 8
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_8;

    /* レベルシンク適用判定最大武器強化レベル係数９白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 9
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_9;

    /* レベルシンク適用判定最大武器強化レベル係数１０白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 10
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_10;

    /* レベルシンク適用判定最大武器強化レベル係数０赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 0
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_0;

    /* レベルシンク適用判定最大武器強化レベル係数１赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 1
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_1;

    /* レベルシンク適用判定最大武器強化レベル係数２赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 2
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_2;

    /* レベルシンク適用判定最大武器強化レベル係数３赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 3
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_3;

    /* レベルシンク適用判定最大武器強化レベル係数４赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 4
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_4;

    /* レベルシンク適用判定最大武器強化レベル係数５赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 5
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_5;

    /* レベルシンク適用判定最大武器強化レベル係数６赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 6
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_6;

    /* レベルシンク適用判定最大武器強化レベル係数７赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 7
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_7;

    /* レベルシンク適用判定最大武器強化レベル係数８赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 8
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_8;

    /* レベルシンク適用判定最大武器強化レベル係数９赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 9
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_9;

    /* レベルシンク適用判定最大武器強化レベル係数１０赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 10
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_10;

    /* 侵入ポイントの自動配置間隔
     *   侵入ポイントの自動配置間隔
     * Automatic Invasion Point - Generation Distance
     *   Automatic placement interval of intrusion points
     * Default Value  = 40 */
    unsigned char autoInvadePoint_generateDist;

    /* 侵入ポイント自動配置取り消し範囲
     *   侵入ポイント自動配置取り消し範囲
     * Automatic Invasion Point - Cancel Distance
     *   Intrusion point automatic placement cancellation range
     * Default Value  = 20 */
    unsigned char autoInvadePoint_cancelDist;

    /* グローバルイベントログの送信間隔
     *   グローバルイベントログ をサーバーへ送信する間隔
     * Send Global Event Log Interval
     *   Interval to send global event log to server */
    float sendGlobalEventLogIntervalTime;

    /* ソロ侵入ポイント加算値_白サイン
     *   ソロ侵入ポイント加算値_白サイン
     * Solo Intrusion Point - White Phantom
     *   Solo intrusion point addition value_white sign */
    unsigned short addSoloBreakInPoint_White;

    /* ソロ侵入ポイント加算値_赤サイン
     *   ソロ侵入ポイント加算値_赤サイン
     * Solo Intrusion Point - Black Phantom
     *   Solo intrusion point addition value_red sign */
    unsigned short addSoloBreakInPoint_Black;

    /* ソロ侵入ポイント加算値_乱入
     *   ソロ侵入ポイント加算値_乱入
     * Solo Intrusion Point - Force Join
     *   Solo intrusion point addition value_intrusion */
    unsigned short addSoloBreakInPoint_ForceJoin;

    /* ソロ侵入ポイント加算値_マップ守護訪問
     *   ソロ侵入ポイント加算値_マップ守護訪問
     * Solo Intrusion Point - Visitor Guardian
     *   Solo intrusion point addition value_Map guardian visit */
    unsigned short addSoloBreakInPoint_VisitorGuardian;

    /* ソロ侵入ポイント加算値_赤狩り訪問
     *   ソロ侵入ポイント加算値_赤狩り訪問
     * Solo Intrusion Point - Red Hunter
     *   Solo intrusion point addition value_Red Scare visit */
    unsigned short addSoloBreakInPoint_VisitorRedHunter;

    /* 初期同期PC用の無敵タイマー
     *   初期同期PC用の無敵タイマー
     * Invincibility Timer for Initial Player Sync
     *   Invincible timer for initial sync PC */
    unsigned char invincibleTimer_forNetPC_initSync;

    /* 初期同期PC以外用の無敵タイマー
     *   初期同期PC以外用の無敵タイマー
     * Invincibility Timer for Non-Initial Player Sync
     *   Invincible timer for non-initial sync PCs
     * Default Value  = 10 */
    unsigned char invincibleTimer_forNetPC;

    /* 【赤狩り】ホストが白扉を通過した際にもらえるソウル率
     *   ホストが白扉を通過した時に赤狩りがもらえるソウル=赤狩りが一つ前のLvから現在Lvになるために必要なソウル*この倍率
     * Red Hunter - Host Boss Area Soul Absorption
     *   Soul that you can get red hunting when the host passes through the white door = Soul required for red hunting to change from the previous Lv to the current Lv * This magnification */
    float redHunter_HostBossAreaGetSoulRate;

    /* 徘徊幻影の痕跡のデカールパラメータID
     *   徘徊幻影が移動中に出す痕跡のデカールパラメータID
     * Ghost Footprint Decal Param ID
     *   Decal parameter ID of the trace that the wandering illusion puts out while moving */
    int ghostFootprintDecalParamId;

    /* マルチプレイ制限距離外の警告メッセージ表示のカウント時間[秒]
     *   マルチプレイ制限距離外に出たままこのカウント時間経過したらマルチプレイの解散を行う
     * Exceeded Multiplayer Limit Distance - Warning Time
     *   If this count time elapses while you are out of the multiplayer limit distance, the multiplayer will be disbanded. */
    float leaveAroundHostWarningTime;

    /* ホスト化コストアイテムID
     *   ホスト化をONにした際に消費するコストアイテムのID
     * Host Mode Cost Item ID
     *   ID of the cost item consumed when hosting is turned on */
    int hostModeCostItemId;

    /* AIジャンプ減速パラメータ
     *   AIジャンプ用減速パラメータ(0.0：等速運動、1.0：最大減速、目標地点で速度0)
     * AI Jump - Deceleration
     *   Deceleration parameters for AI jump (0.0 constant velocity motion, 1.0 maximum deceleration, speed 0 at target point) */
    float aIJump_DecelerateParam;

    /* バディインスタンス削除保証時間
     *   死亡フラグから実際にインスタンスが消滅するまでの時間
     * Spirit Summon - Disappearance Delay
     *   The time from the death flag to the actual disappearance of the instance */
    float buddyDisappearDelaySec;

    /* AIジャンプ飛び降り時Y移動量補正率
     *   AIジャンプ飛び降り時Y移動量補正率
     * AI Jump - Y Movement Amount Correction
     *   AI jump jumping Y movement amount correction factor */
    float aIJump_AnimYMoveCorrectRate_onJumpOff;

    /* ステルス視界倍率_ステルス効果無しでしゃがみ
     *   ステルス視界倍率_ステルス効果無しでしゃがみ
     * Stealth Visibility - Crouch - No Stealth Effect
     *   Stealth visibility magnification_Crouching without stealth effect
     * Default Value  = 1 */
    float stealthSystemSightRate_NotInStealthRigid_NotSightHide_StealthMode;

    /* ステルス視界倍率_ステルスレイ遮蔽地帯で立ち
     *   ステルス視界倍率_ステルスレイ遮蔽地帯で立ち
     * Stealth Visibility - Stand - Stealth Ray Effect
     *   Stealth visibility magnification_Standing in stealth ray shielded area
     * Default Value  = 1 */
    float stealthSystemSightRate_NotInStealthRigid_SightHide_NotStealthMode;

    /* ステルス視界倍率_ステルスレイ遮蔽地帯でしゃがみ
     *   ステルス視界倍率_ステルスレイ遮蔽地帯でしゃがみ
     * Stealth Visibility - Crouch - Stealth Ray Effect
     *   Stealth visibility magnification_Crouching in stealth ray shielded area
     * Default Value  = 1 */
    float stealthSystemSightRate_NotInStealthRigid_SightHide_StealthMode;

    /* ステルス視界倍率_ステルスヒット内で立ち
     *   ステルス視界倍率_ステルスヒット内で立ち
     * Stealth Visibility - Stand - Stealth Hit
     *   Stealth visibility magnification_Standing within a stealth hit
     * Default Value  = 1 */
    float stealthSystemSightRate_InStealthRigid_NotSightHide_NotStealthMode;

    /* ステルス視界倍率_ステルスヒット内でしゃがみ
     *   ステルス視界倍率_ステルスヒット内でしゃがみ
     * Stealth Visibility - Crouch - Stealth Hit
     *   Stealth visibility magnification_Crouching within a stealth hit
     * Default Value  = 1 */
    float stealthSystemSightRate_InStealthRigid_NotSightHide_StealthMode;

    /* ステルス視界倍率_ステルスレイ遮蔽地帯＋ステルスヒット内で立ち
     *   ステルス視界倍率_ステルスレイ遮蔽地帯＋ステルスヒット内で立ち
     * Stealth Visibility - Stealth Ray + Stand in Stealth Hit
     *   Stealth visibility magnification_Stealth ray shielded area + standing in stealth hit
     * Default Value  = 1 */
    float stealthSystemSightRate_InStealthRigid_SightHide_NotStealthMode;

    /* ステルス視界倍率_ステルスレイ遮蔽地帯＋ステルスヒット内でしゃがみ
     *   ステルス視界倍率_ステルスレイ遮蔽地帯＋ステルスヒット内でしゃがみ
     * Stealth Visibility - Stealth Ray + Crouch in Stealth Hit
     *   Stealth visibility magnification_Stealth ray shielded area + crouching in stealth hit
     * Default Value  = 1 */
    float stealthSystemSightRate_InStealthRigid_SightHide_StealthMode;

    /* 宝死体のデフォルトアクションボタンパラメータID
     *   MapStudioイベントのOBJ用宝箱情報の宝箱タイプで「宝死体」を選択したときのデフォルトアクションボタンパラメータID
     * Treasure Corpse - Default Action Button ID
     *   Default action button parameter ID when Treasure corpse is selected in the treasure box type of treasure box information for OBJ of MapStudio event */
    int msbEventGeomTreasureInfo_actionButtonParamId_corpse;

    /* 宝死体のデフォルトアイテム取得時アニメID
     *   MapStudioイベントのOBJ用宝箱情報の宝箱タイプで「宝死体」を選択したときのデフォルトアイテム取得時アニメID
     * Treasure Corpse - Item Get Anim ID
     *   When Treasure corpse is selected in the treasure box type of the treasure box information for OBJ of the MapStudio event, the default item is acquired. Animation ID */
    int msbEventGeomTreasureInfo_itemGetAnimId_corpse;

    /* 宝箱のデフォルトアクションボタンパラメータID
     *   MapStudioイベントのOBJ用宝箱情報の宝箱タイプで「宝箱」を選択したときのデフォルトアクションボタンパラメータID
     * Treasure Chest - Default Action Button ID
     *   Default action button parameter ID when Treasure chest is selected in the treasure chest type of treasure chest information for OBJ of MapStudio event */
    int msbEventGeomTreasureInfo_actionButtonParamId_box;

    /* 宝箱のデフォルトアイテム取得時アニメID
     *   MapStudioイベントのOBJ用宝箱情報の宝箱タイプで「宝箱」を選択したときのデフォルトアイテム取得時アニメID
     * Treasure Chest - Item Get Anim ID
     *   When Treasure chest is selected in the treasure chest type of the treasure chest information for OBJ of the MapStudio event, the default item acquisition animation ID */
    int msbEventGeomTreasureInfo_itemGetAnimId_box;

    /* アイテム光のデフォルトアクションボタンパラメータID
     *   MapStudioイベントのOBJ用宝箱情報の宝箱タイプで「アイテム光」を選択したときのデフォルトアクションボタンパラメータID
     * FFX Treasure - Default Action Button ID
     *   Default action button parameter ID when Item light is selected in the treasure chest type of treasure chest information for OBJ of MapStudio event */
    int msbEventGeomTreasureInfo_actionButtonParamId_shine;

    /* アイテム光のデフォルトアイテム取得時アニメID
     *   MapStudioイベントのOBJ用宝箱情報の宝箱タイプで「アイテム光」を選択したときのデフォルトアイテム取得時アニメID
     * FFX Treasure - Item Get Anim ID
     *   When Item Hikari is selected as the treasure chest type of the treasure chest information for OBJ of the MapStudio event, the default item acquisition animation ID */
    int msbEventGeomTreasureInfo_itemGetAnimId_shine;

    /* サイン溜まり：アセットID
     *   サイン溜まりに使うアセット
     * Summoning Pool - Asset ID
     *   Assets used for sign collection */
    int signPuddleAssetId;

    /* サイン溜まり：サイン出現ダミポリ0
     *   サイン溜まりのサインの表示位置を決定するのに使うダミポリ
     * Summoning Pool - Dummy Poly ID [0]
     *   Damipoli used to determine the display position of the sign in the sign pool */
    int signPuddleAppearDmypolyId0;

    /* サイン溜まり：サイン出現ダミポリ1
     *   サイン溜まりのサインの表示位置を決定するのに使うダミポリ
     * Summoning Pool - Dummy Poly ID [1]
     *   Damipoli used to determine the display position of the sign in the sign pool */
    int signPuddleAppearDmypolyId1;

    /* サイン溜まり：サイン出現ダミポリ2
     *   サイン溜まりのサインの表示位置を決定するのに使うダミポリ
     * Summoning Pool - Dummy Poly ID [2]
     *   Damipoli used to determine the display position of the sign in the sign pool */
    int signPuddleAppearDmypolyId2;

    /* サイン溜まり：サイン出現ダミポリ3
     *   サイン溜まりのサインの表示位置を決定するのに使うダミポリ
     * Summoning Pool - Dummy Poly ID [3]
     *   Damipoli used to determine the display position of the sign in the sign pool */
    int signPuddleAppearDmypolyId3;

    /* 騎乗者の落下ダメージ倍率補正_PC用
     *   騎乗者の落下ダメージ倍率補正_PC用
     * Fall Damage Multiplier - Mounted Player
     *   Rider's fall damage multiplier correction_for PC
     * Default Value  = 1 */
    float fallDamageRate_forRidePC;

    /* 騎乗者の落下ダメージ倍率補正_NPC用
     *   騎乗者の落下ダメージ倍率補正_NPC用
     * Fall Damage Multiplier - Mounted NPC
     *   Rider's Fall Damage Multiplier Correction_for NPCs
     * Default Value  = 1 */
    float fallDamageRate_forRideNPC;

    /* 黄衣の翁サイン作成時特殊効果ID
     *   黄衣の翁サイン作成時特殊効果ID
     * Old Monk of Yellow - Create Sign SpEffect ID
     *   Special effect ID when creating the old man sign of yellow robe */
    int OldMonkOfYellow_CreateSignSpEffectId;

    /* 敗残兵起動距離
     *   敗残兵起動距離
     * Straggler - Activation Distance
     *   Defeated soldier activation distance */
    float StragglerActivateDist;

    /* 敗残兵アイテム使用許可_PC用特殊効果
     *   敗残兵アイテム使用許可_PC用特殊効果
     * Straggler - Enable Item Use SpEffect ID
     *   Permission to use defeated soldier items_Special effects for PC
     * Default Value  = -1 */
    int SpEffectId_EnableUseItem_StragglerActivate;

    /* 敗残兵起動_敗残兵キャラ用特殊効果
     *   敗残兵起動_敗残兵キャラ用特殊効果
     * Straggler - Wake Up SpEffect ID
     *   Activate defeated soldiers_Special effects for defeated soldier characters
     * Default Value  = -1 */
    int SpEffectId_StragglerWakeUp;

    /* 敗残兵_討伐対象用特殊効果
     *   敗残兵_討伐対象用特殊効果
     * Straggler - Target SpEffect ID
     *   Defeated soldiers_Special effects for subjugation targets
     * Default Value  = -1 */
    int SpEffectId_StragglerTarget;

    /* 敗残兵_敵対後特殊効果
     *   敗残兵_敵対後特殊効果
     * Straggler - Oppose SpEffect ID
     *   Defeated soldiers_Special effects after hostility
     * Default Value  = -1 */
    int SpEffectId_StragglerOppose;

    /* レイ遮断でバディがプレイヤーにワープする時間[s]
     *   レイ遮断でバディがプレイヤーにワープする時間[s]
     * Spirit Summon - Trigger Time for Warp when Raycast is blocked
     *   Time for a buddy to warp a player with a ray block [s]
     * Default Value  = 10 */
    float buddyWarp_TriggerTimeRayBlocked;

    /* 直線距離でバディがプレイヤーにワープする距離[m]
     *   直線距離でバディがプレイヤーにワープする距離[m]
     * Spirit Summon - Trigger Warp Distance to Player
     *   Distance at which the buddy warps the player at a straight line distance [m]
     * Default Value  = 25 */
    float buddyWarp_TriggerDistToPlayer;

    /* バディがパス移動で詰まった判定する時間[s]
     *   バディがパス移動で詰まった判定する時間[s]
     * Spirit Summon - Time Threshold for Stuck Spirit
     *   Judgment time when the buddy is stuck in the pass movement [s]
     * Default Value  = 5 */
    float buddyWarp_ThresholdTimePathStacked;

    /* バディがパス移動で詰まっているとみなす距離[m]
     *   バディがパス移動で詰まっているとみなす距離[m]
     * Spirit Summon - Distance Threshold for Stuck Spirit
     *   Distance [m] that the buddy considers to be clogged with a pass move
     * Default Value  = 1 */
    float buddyWarp_ThresholdRangePathStacked;

    /* [朝]AI視界倍率
     *   [朝]AI視界倍率
     * AI Sight Multiplier - Morning
     *   [Morning] AI visibility magnification
     * Default Value  = 1 */
    float aiSightRate_morning;

    /* [昼]AI視界倍率
     *   [昼]AI視界倍率
     * AI Sight Multiplier - Noon
     *   [Day] AI visibility magnification
     * Default Value  = 1 */
    float aiSightRate_noonA;

    /* バディとプレイヤーがぶつかって、すり抜け始める時間[s]
     *   バディとプレイヤーがぶつかって、すり抜け始める時間[s]
     * Spirit Summon - Pass through Player Trigger Time
     *   Time when the buddy and the player collide and start slipping through [s]
     * Default Value  = 0.5 */
    float buddyPassThroughTriggerTime;

    /* [夕]AI視界倍率
     *   [夕]AI視界倍率
     * AI Sight Multiplier - Evening
     *   [Evening] AI visibility magnification
     * Default Value  = 1 */
    float aiSightRate_evening;

    /* [夜]AI視界倍率
     *   [夜]AI視界倍率
     * AI Sight Multiplier - Night
     *   [Night] AI visibility magnification
     * Default Value  = 1 */
    float aiSightRate_night;

    /* [深夜]AI視界倍率
     *   [深夜]AI視界倍率
     * AI Sight Multiplier - Midnight
     *   [Midnight] AI visibility magnification
     * Default Value  = 1 */
    float aiSightRate_midnightA;

    int unknown_0x230;

    /* AI視界倍率_太陽が見えない場所(明るい)
     *   AI視界倍率_太陽が見えない場所(明るい)
     * AI Sight Multiplier - Sunloss - Light
     *   AI visibility magnification_place where the sun cannot be seen (bright)
     * Default Value  = 1 */
    float aiSightRate_sunloss_light;

    /* AI視界倍率_太陽が見えない場所(暗闇)
     *   AI視界倍率_太陽が見えない場所(暗闇)
     * AI Sight Multiplier - Sunloss - Darkness
     *   AI visibility magnification_place where the sun cannot be seen (darkness)
     * Default Value  = 1 */
    float aiSightRate_sunloss_dark;

    /* AI視界倍率_太陽が見えない場所(真っ暗闇)
     *   AI視界倍率_太陽が見えない場所(真っ暗闇)
     * AI Sight Multiplier - Sunloss - Total Darkness
     *   AI visibility magnification_place where the sun cannot be seen (total darkness)
     * Default Value  = 1 */
    float aiSightRate_sunloss_veryDark;

    /* ステルス視界角度減衰率_ステルス効果無しでしゃがみ
     *   ステルス視界角度減衰率_ステルス効果無しでしゃがみ
     * Stealth View Angle Attenuation - Crouch - No Stealth Effect
     *   Stealth view angle attenuation factor_ crouching without stealth effect */
    float stealthSystemSightAngleReduceRate_NotInStealthRigid_NotSightHide_StealthMode;

    /* ステルス視界角度減衰率_ステルスレイ遮蔽地帯で立ち
     *   ステルス視界角度減衰率_ステルスレイ遮蔽地帯で立ち
     * Stealth View Angle Attenuation - Stand - Stealth Ray
     *   Stealth view angle attenuation rate_Standing in stealth ray shielded area */
    float stealthSystemSightAngleReduceRate_NotInStealthRigid_SightHide_NotStealthMode;

    /* ステルス視界角度減衰率_ステルスレイ遮蔽地帯でしゃがみ
     *   ステルス視界角度減衰率_ステルスレイ遮蔽地帯でしゃがみ
     * Stealth View Angle Attenuation - Crouch - Stealth Ray
     *   Stealth visibility angle attenuation _ crouching in stealth ray shielded area */
    float stealthSystemSightAngleReduceRate_NotInStealthRigid_SightHide_StealthMode;

    /* ステルス視界角度減衰率_ステルスヒット内で立ち
     *   ステルス視界角度減衰率_ステルスヒット内で立ち
     * Stealth View Angle Attenuation - Stand - Stealth Hit
     *   Stealth view angle attenuation rate_Standing within stealth hit */
    float stealthSystemSightAngleReduceRate_InStealthRigid_NotSightHide_NotStealthMode;

    /* ステルス視界角度減衰率_ステルスヒット内でしゃがみ
     *   ステルス視界角度減衰率_ステルスヒット内でしゃがみ
     * Stealth View Angle Attenuation - Crouch - Stealth Hit
     *   Stealth view angle attenuation rate_ crouching within stealth hit */
    float stealthSystemSightAngleReduceRate_InStealthRigid_NotSightHide_StealthMode;

    /* ステルス視界角度減衰率_ステルスレイ遮蔽地帯＋ステルスヒット内で立ち
     *   ステルス視界角度減衰率_ステルスレイ遮蔽地帯＋ステルスヒット内で立ち
     * Stealth View Angle Attenuation - Stand - Stealth Ray + Stealth Hit
     *   Stealth view angle attenuation rate_Stealth ray shielded area + standing in stealth hit */
    float stealthSystemSightAngleReduceRate_InStealthRigid_SightHide_NotStealthMode;

    /* ステルス視界角度減衰率_ステルスレイ遮蔽地帯＋ステルスヒット内でしゃがみ
     *   ステルス視界角度減衰率_ステルスレイ遮蔽地帯＋ステルスヒット内でしゃがみ
     * Stealth View Angle Attenuation - Crouch - Stealth Ray + Stealth Hit
     *   Stealth view angle attenuation rate_Stealth ray shielded area + crouching in stealth hit */
    float stealthSystemSightAngleReduceRate_InStealthRigid_SightHide_StealthMode;

    /* 天候抽選条件_朝_開始時刻_時
     *   天候抽選条件_朝_開始時刻_時(SEQ09371)
     * Weather Lottery Condition - Morning Hour
     *   Weather lottery conditions_morning_start time_hour (SEQ09371)
     * Default Value  = 7 */
    unsigned char weatherLotConditionStart_Morning_Hour;

    /* 天候抽選条件_朝_開始時刻_分
     *   天候抽選条件_朝_開始時刻_分(SEQ09371)
     * Weather Lottery Condition - Morning Minute
     *   Weather lottery conditions_morning_start time_minutes (SEQ09371) */
    unsigned char weatherLotConditionStart_Morning_Minute;

    /* 天候抽選条件_昼_開始時刻_時
     *   天候抽選条件_昼_開始時刻_時(SEQ09371)
     * Weather Lottery Condition - Day Hour
     *   Weather lottery conditions_day_start time_hour (SEQ09371)
     * Default Value  = 12 */
    unsigned char weatherLotConditionStart_Day_Hour;

    /* 天候抽選条件_昼_開始時刻_分
     *   天候抽選条件_昼_開始時刻_分(SEQ09371)
     * Weather Lottery Condition - Day Minute
     *   Weather lottery conditions_day_start time_minutes (SEQ09371) */
    unsigned char weatherLotConditionStart_Day_Minute;

    /* 天候抽選条件_夕_開始時刻_時
     *   天候抽選条件_夕_開始時刻_時(SEQ09371)
     * Weather Lottery Condition - Evening Hour
     *   Weather lottery conditions_evening_start time_hour (SEQ09371)
     * Default Value  = 17 */
    unsigned char weatherLotConditionStart_Evening_Hour;

    /* 天候抽選条件_夕_開始時刻_分
     *   天候抽選条件_夕_開始時刻_分(SEQ09371)
     * Weather Lottery Condition - Evening Minute
     *   Weather lottery conditions_evening_start time_minutes (SEQ09371) */
    unsigned char weatherLotConditionStart_Evening_Minute;

    /* 天候抽選条件_夜_開始時刻_時
     *   天候抽選条件_夜_開始時刻_時(SEQ09371)
     * Weather Lottery Condition - Night Hour
     *   Weather lottery conditions_night_start time_hour (SEQ09371)
     * Default Value  = 19 */
    unsigned char weatherLotConditionStart_Night_Hour;

    /* 天候抽選条件_夜_開始時刻_分
     *   天候抽選条件_夜_開始時刻_分(SEQ09371)
     * Weather Lottery Condition - Night Minute
     *   Weather lottery conditions_night_start time_minutes (SEQ09371) */
    unsigned char weatherLotConditionStart_Night_Minute;

    /* 天候抽選条件_夜明け_開始時刻_時
     *   天候抽選条件_夜明け_開始時刻_時(SEQ09371)
     * Weather Lottery Condition - Dawn Hour
     *   Weather lottery conditions_dawn_start time_hour (SEQ09371)
     * Default Value  = 5 */
    unsigned char weatherLotConditionStart_DayBreak_Hour;

    /* 天候抽選条件_夜明け_開始時刻_分
     *   天候抽選条件_夜明け_開始時刻_分(SEQ09371)
     * Weather Lottery Condition - Dawn Minute
     *   Weather lottery conditions_dawn_start time_minutes (SEQ09371) */
    unsigned char weatherLotConditionStart_DayBreak_Minute;

    /* 天候抽選条件_予約
     *   (dummy8) */
    char weatherLotCondition_reserved[2];

    /* Playerライト強度スケール変更時間帯_開始時刻_時
     *   Playerライト強度スケール変更時間帯_開始時刻_時(SEQ16562)
     * Player Light Intensity Scale - Start Hour
     *   Player Light Intensity Scale Change Time Zone_Start Time_Hour (SEQ16562)
     * Default Value  = 18 */
    unsigned char pclightScaleChangeStart_Hour;

    /* Playerライト強度スケール変更時間帯_開始時刻_分
     *   Playerライト強度スケール変更時間帯_開始時刻_分(SEQ16562)
     * Player Light Intensity Scale - Start Minute
     *   Player Light Intensity Scale Change Time Zone_Start Time_Minute (SEQ16562) */
    unsigned char pclightScaleChangeStart_Minute;

    /* Playerライト強度スケール変更時間帯_終了時刻_時
     *   Playerライト強度スケール変更時間帯_終了時刻_時(SEQ16562)
     * Player Light Intensity Scale - End Hour
     *   Player Light intensity scale change time zone_end time_hour (SEQ16562)
     * Default Value  = 5 */
    unsigned char pclightScaleChangeEnd_Hour;

    /* Playerライト強度スケール変更時間帯_終了時刻_分
     *   Playerライト強度スケール変更時間帯_終了時刻_分(SEQ16562)
     * Player Light Intensity Scale - End Minute
     *   Player Light Intensity Scale Change Time Zone_End Time_Minute (SEQ16562) */
    unsigned char pclightScaleChangeEnd_Minute;

    /* 時間帯Playerライト強度スケール変更値
     *   時間帯Playerライト強度スケール変更値(SEQ16562)
     * Player Light Intensity Scale - Timezone
     *   Time zone Player light intensity scale change value (SEQ16562)
     * Default Value  = 1 */
    float pclightScaleByTimezone;

    /* 大ルーン：グレーターデーモンバディ召喚時バディ付与特殊効果ID
     *   大ルーン：グレーターデーモンバディ召喚時バディ付与特殊効果ID
     * Great Rune - Greater Demon Spirit Summon - Spirit SpEffect ID
     *   Large Rune Greater Demon Buddy Summon Buddy Special Effect ID
     * Default Value  = -1 */
    int bigRuneGreaterDemon_SummonBuddySpecialEffectId_Buddy;

    /* 大ルーン：グレーターデーモンバディ召喚時PC付与特殊効果ID
     *   大ルーン：グレーターデーモンバディ召喚時PC付与特殊効果ID
     * Great Rune - Greater Demon Spirit Summon - Player SpEffect ID
     *   Large Rune Special effect ID given to PC when summoning Greater Demon Buddy
     * Default Value  = -1 */
    int bigRuneGreaterDemon_SummonBuddySpecialEffectId_Pc;

    /* 拠点篝火ワープID
     *   拠点篝火の篝火ワープパラメータID
     * Base Bonfire Warp Param ID
     *   Base bonfire bonfire warp parameter ID */
    int homeBonfireParamId;

    /* レベルシンク適用判定最大武器強化レベル係数１１白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 11
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_11;

    /* レベルシンク適用判定最大武器強化レベル係数１２白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 12
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_12;

    /* レベルシンク適用判定最大武器強化レベル係数１３白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 13
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_13;

    /* レベルシンク適用判定最大武器強化レベル係数１４白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 14
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_14;

    /* レベルシンク適用判定最大武器強化レベル係数１５白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 15
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_15;

    /* レベルシンク適用判定最大武器強化レベル係数１６白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 16
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_16;

    /* レベルシンク適用判定最大武器強化レベル係数１７白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 17
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_17;

    /* レベルシンク適用判定最大武器強化レベル係数１８白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 18
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_18;

    /* レベルシンク適用判定最大武器強化レベル係数１９白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 19
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_19;

    /* レベルシンク適用判定最大武器強化レベル係数２０白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 20
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_20;

    /* レベルシンク適用判定最大武器強化レベル係数２１白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 21
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_21;

    /* レベルシンク適用判定最大武器強化レベル係数２２白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 22
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_22;

    /* レベルシンク適用判定最大武器強化レベル係数２３白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 23
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_23;

    /* レベルシンク適用判定最大武器強化レベル係数２４白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 24
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_24;

    /* レベルシンク適用判定最大武器強化レベル係数２５白
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Friendly Phantom - Max Reinforcement Coefficient 25
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperWhiteSign_25;

    /* レベルシンク適用判定最大武器強化レベル係数１１赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 11
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_11;

    /* レベルシンク適用判定最大武器強化レベル係数１２赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 12
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_12;

    /* レベルシンク適用判定最大武器強化レベル係数１３赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 13
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_13;

    /* レベルシンク適用判定最大武器強化レベル係数１４赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 14
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_14;

    /* レベルシンク適用判定最大武器強化レベル係数１５赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 15
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_15;

    /* レベルシンク適用判定最大武器強化レベル係数１６赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 16
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_16;

    /* レベルシンク適用判定最大武器強化レベル係数１７赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 17
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_17;

    /* レベルシンク適用判定最大武器強化レベル係数１８赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 18
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_18;

    /* レベルシンク適用判定最大武器強化レベル係数１９赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 19
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_19;

    /* レベルシンク適用判定最大武器強化レベル係数２０赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 20
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_20;

    /* レベルシンク適用判定最大武器強化レベル係数２１赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 21
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_21;

    /* レベルシンク適用判定最大武器強化レベル係数２２赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 22
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_22;

    /* レベルシンク適用判定最大武器強化レベル係数２３赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 23
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_23;

    /* レベルシンク適用判定最大武器強化レベル係数２４赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 24
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_24;

    /* レベルシンク適用判定最大武器強化レベル係数２５赤
     *   レベルシンク適用するかどうかの最大武器強化レベル係数
     * Hostile Phantom - Max Reinforcement Coefficient 25
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char machingWeaponLevelUpperRedSign_25;

    /* メニュー用時間帯表示_朝_開始時刻_時
     *   メニュー用時間帯表示_朝_開始時刻_時(SEQ22108)
     * Menu Timezone - Morning Hour
     *   Menu time zone display_morning_start time_hour (SEQ22108)
     * Default Value  = 7 */
    unsigned char menuTimezoneStart_Morning_Hour;

    /* メニュー用時間帯表示_朝_開始時刻_分
     *   メニュー用時間帯表示_朝_開始時刻_分(SEQ22108)
     * Menu Timezone - Morning Minute
     *   Menu time zone display_morning_start time_minute (SEQ22108) */
    unsigned char menuTimezoneStart_Morning_Minute;

    /* メニュー用時間帯表示_昼1_開始時刻_時
     *   メニュー用時間帯表示_昼1_開始時刻_時(SEQ22108)
     * Menu Timezone - Day 1 Hour
     *   Menu time zone display_day 1_start time_hour (SEQ22108)
     * Default Value  = 12 */
    unsigned char menuTimezoneStart_Day1_Hour;

    /* メニュー用時間帯表示_昼1_開始時刻_分
     *   メニュー用時間帯表示_昼1_開始時刻_分(SEQ22108)
     * Menu Timezone - Day 1 Minute
     *   Menu time zone display_day 1_start time_minute (SEQ22108) */
    unsigned char menuTimezoneStart_Day1_Minute;

    /* メニュー用時間帯表示_昼2_開始時刻_時
     *   メニュー用時間帯表示_昼2_開始時刻_時(SEQ22108)
     * Menu Timezone - Day 2 Hour
     *   Menu time zone display_day 2_start time_hour (SEQ22108)
     * Default Value  = 12 */
    unsigned char menuTimezoneStart_Day2_Hour;

    /* メニュー用時間帯表示_昼2_開始時刻_分
     *   メニュー用時間帯表示_昼2_開始時刻_分(SEQ22108)
     * Menu Timezone - Day 2 Minute
     *   Time zone display for menu_Lunch 2_Start time_Minute (SEQ22108) */
    unsigned char menuTimezoneStart_Day2_Minute;

    /* メニュー用時間帯表示_夕_開始時刻_時
     *   メニュー用時間帯表示_夕_開始時刻_時(SEQ22108)
     * Menu Timezone - Evening Hour
     *   Menu time zone display_evening_start time_hour (SEQ22108)
     * Default Value  = 17 */
    unsigned char menuTimezoneStart_Evening_Hour;

    /* メニュー用時間帯表示_夕_開始時刻_分
     *   メニュー用時間帯表示_夕_開始時刻_分(SEQ22108)
     * Menu Timezone - Evening Minute
     *   Menu time zone display_evening_start time_minute (SEQ22108) */
    unsigned char menuTimezoneStart_Evening_Minute;

    /* メニュー用時間帯表示_夜_開始時刻_時
     *   メニュー用時間帯表示_夜_開始時刻_時(SEQ22108)
     * Menu Timezone - Night Hour
     *   Menu time zone display_night_start time_hour (SEQ22108)
     * Default Value  = 19 */
    unsigned char menuTimezoneStart_Night_Hour;

    /* メニュー用時間帯表示_夜_開始時刻_分
     *   メニュー用時間帯表示_夜_開始時刻_分(SEQ22108)
     * Menu Timezone - Night Minute
     *   Menu time zone display_night_start time_minute (SEQ22108) */
    unsigned char menuTimezoneStart_Night_Minute;

    /* メニュー用時間帯表示_深夜_開始時刻_時
     *   メニュー用時間帯表示_深夜_開始時刻_時(SEQ22108)
     * Menu Timezone - Midnight Hour
     *   Menu time zone display_midnight_start time_hour (SEQ22108)
     * Default Value  = 5 */
    unsigned char menuTimezoneStart_Midnight_Hour;

    /* メニュー用時間帯表示_深夜_開始時刻_分
     *   メニュー用時間帯表示_深夜_開始時刻_分(SEQ22108)
     * Menu Timezone - Midnight Minute
     *   Menu time zone display_midnight_start time_minute (SEQ22108) */
    unsigned char menuTimezoneStart_Midnight_Minute;

    /* ネットワークPC脅威度通知_脅威度
     *   ネットワークPC脅威度通知_脅威度(SEQ21950)
     * Network Player Threat Notification - Threat Level
     *   Network PC Threat Level Notification_Threat Level (SEQ21950) */
    unsigned short remotePlayerThreatLvNotify_ThreatLv;

    /* ネットワークPC脅威度通知_通知距離[m]
     *   ネットワークPC脅威度通知_通知距離[m](SEQ21950)
     * Network Player Threat Notification - Notify Distance
     *   Network PC Threat Level Notification_Notification Distance [m] (SEQ21950) */
    float remotePlayerThreatLvNotify_NotifyDist;

    /* ネットワークPC脅威度通知_通知終了距離[m]
     *   ネットワークPC脅威度通知_通知終了距離[m](SEQ21950)
     * Network Player Threat Notification - Max Notify Distance
     *   Network PC threat level notification_notification end distance [m] (SEQ21950) */
    float remotePlayerThreatLvNotify_EndNotifyDist;

    /* 地図ポイント発見領域のデフォルト拡張距離[m]
     *   地図ポイントの発見領域のデフォルトの拡張距離。地図ポイントの"発見領域 上書き領域"が無効(-1)のときに、自身の領域から拡張して発見領域が生成される。その拡張距離
     * World Map Point - Discovery Expand Range
     *   The default extended distance for the map point discovery area. When the discovery area overwrite area of the map point is invalid (-1), the discovery area is generated by expanding from its own area. Its extended distance */
    float worldMapPointDiscoveryExpandRange;

    /* 地図ポイント出場領域のデフォルト拡張距離[m]
     *   地図ポイントの出場領域のデフォルトの拡張距離。地図ポイントの"出場領域 上書き領域"が無効(-1)のときに、自身の領域から拡張して出場領域が生成される。その拡張距離
     * World Map Point - Re-entry Expand Range
     *   The default extended distance for the map point's entry area. When the participation area overwrite area of the map point is invalid (-1), the participation area is generated by expanding from its own area. Its extended distance */
    float worldMapPointReentryExpandRange;

    /* ネットワークPC脅威度通知_通知時間[秒]
     *   ネットワークPC脅威度通知_通知時間[秒](SEQ21950)
     * Network Player Threat Notification - Notify Time
     *   Network PC Threat Level Notification_Notification Time [seconds] (SEQ21950) */
    unsigned short remotePlayerThreatLvNotify_NotifyTime;

    /* 侵入時に付与する"再侵入アイテム"の付与個数：侵入アイテム_グレーター系（ID102）
     *   侵入時に付与する"再侵入アイテム"の付与個数：侵入アイテム_グレーター系（ID102）
     * Phantom Bloody Finger - Count
     *   Number of re-invasion items to be given at the time of intrusion Intrusion item_Greater system (ID102) */
    unsigned short breakIn_A_rebreakInGoodsNum;

    /* 侵入時に付与する"再侵入アイテム"の道具アイテムID：侵入アイテム_グレーター系（ID102）
     *   侵入時に付与する"再侵入アイテム"の道具アイテムID：侵入アイテム_グレーター系（ID102）
     * Phantom Bloody Finger - Goods ID
     *   Tool item ID of re-invasion item given at the time of intrusion Invasion item_Greater system (ID102)
     * Default Value  = -1 */
    int breakIn_A_rebreakInGoodsId;

    /* 降りる大ジャンプ_上空SFXID
     *   降りる大ジャンプ_上空SFXID
     * Spiritspring SFX ID
     *   Big jump to get off _ sky SFXID
     * Default Value  = -1 */
    int rideJumpoff_SfxId;

    /* 降りる大ジャンプ_上空SFX基点オフセット
     *   降りる大ジャンプ_上空SFX基点オフセット
     * Spiritspring SFX Height Offset
     *   Big jump to get off_SFX base point offset in the sky */
    float rideJumpoff_SfxHeightOffset;

    /* 降りる大ジャンプ領域内_PC馬にかかる特殊効果ID
     *   降りる大ジャンプ領域内_PC馬にかかる特殊効果ID
     * Spiritspring SpEffect ID (Horse)
     *   In the big jump area to get off _ Special effect ID for PC horse
     * Default Value  = -1 */
    int rideJumpoff_SpEffectId;

    /* 降りる大ジャンプ領域内_PCにかかる特殊効果ID
     *   降りる大ジャンプ領域内_PCにかかる特殊効果ID
     * Spiritspring SpEffect ID (Player)
     *   Special effect ID for _PC in the big jump area to get off
     * Default Value  = -1 */
    int rideJumpoff_SpEffectIdPc;

    /* メインメニュー_アイテム作成_開放イベントフラグ
     *   メインメニュー→アイテム作成メニューをアンロックするイベントフラグ
     * Unlock Exchange Menu - Event Flag ID
     *   Main menu  Event flag to unlock the item creation menu */
    unsigned int unlockExchangeMenuEventFlagId;

    /* メインメニュー_メッセージ_開放イベントフラグ
     *   メインメニュー→メッセージメニューをアンロックするイベントフラグ
     * Unlock Message Menu - Event Flag ID
     *   Main menu  Event flag to unlock the message menu */
    unsigned int unlockMessageMenuEventFlagId;

    /* 侵入時に付与する"再侵入アイテム"の付与個数：侵入アイテム_グレーター系使い捨て（ID111）
     *   侵入時に付与する"再侵入アイテム"の付与個数：侵入アイテム_グレーター系使い捨て（ID111）
     * Phantom Bloody Finger - Count
     *   Number of re-invasion items to be given at the time of intrusion Intrusion item_Greater disposable (ID111) */
    unsigned short breakInOnce_A_rebreakInGoodsNum;

    /* 侵入時に付与する"再侵入アイテム"の付与個数：侵入アイテム_火山館系（ID112）
     *   侵入時に付与する"再侵入アイテム"の付与個数：侵入アイテム_火山館系（ID112）
     * Phantom Recusant Finger - Count
     *   Number of re-invasion items to be given at the time of invasion Invasion item_Volcano building system (ID112) */
    unsigned short breakIn_B_rebreakInGoodsNum;

    /* 侵入時に付与する"再侵入アイテム"の道具アイテムID：侵入アイテム_グレーター系使い捨て（ID111）
     *   侵入時に付与する"再侵入アイテム"の道具アイテムID：侵入アイテム_グレーター系使い捨て（ID111）
     * Phantom Bloody Finger - Goods ID
     *   Tool item ID of re-invasion item given at the time of intrusion Invasion item_Greater disposable (ID111)
     * Default Value  = -1 */
    int breakInOnce_A_rebreakInGoodsId;

    /* 侵入時に付与する"再侵入アイテム"の道具アイテムID：侵入アイテム_火山館系（ID112）
     *   侵入時に付与する"再侵入アイテム"の道具アイテムID：侵入アイテム_火山館系（ID112）
     * Phantom Recusant Finger - Goods ID
     *   Tool item ID of re-invasion item given at the time of invasion Invasion item_Volcano building system (ID112)
     * Default Value  = -1 */
    int breakIn_B_rebreakInGoodsId;

    /* アクションボタン押しっぱなしでアクションボタン操作を無効化する時間
     *   アクションボタン押しっぱなしでアクションボタン操作を無効化する時間
     * Action Button Input Cancel Time
     *   Time to disable action button operation by holding down the action button
     * Default Value  = -1 */
    float actionButtonInputCancelTime;

    /* ボス撃破処理後クリアボーナス取得遅延時間
     *   ボス撃破処理後クリアボーナス取得遅延時間
     * Boss Kill - Rune Acquisition Delay Time
     *   Clear bonus acquisition delay time after boss defeat processing
     * Default Value  = 7 */
    float blockClearBonusDelayTime;

    /* 【未使用】(SEQ25048参照）敵による篝火無効化を判定するPCから篝火までの距離[m]
     *   【未使用】(SEQ25048参照）敵による篝火無効化を判定するPCから篝火までの距離[m](0以下：PC距離チェックしない。全距離でチェック)
     * Bonfire Check Enemy Range
     *   [Unused] (Refer to SEQ25048) Distance from PC to bonfire that determines invalidation of bonfire by enemy [m] (0 or less PC distance is not checked. Checked at all distances)
     * Default Value  = -1 */
    float bonfireCheckEnemyRange;

    int unknown_0x2f0;

    /* Chr Type 13 Phantom - Level Coefficient 1
     *   Soul level coefficient of whether to apply level sync */
    unsigned char matchingLevelUnkUpperRel;

    /* Chr Type 13 Phantom - Level Coefficient 2
     *   Soul level coefficient of whether to apply level sync */
    unsigned char matchingLevelUnkUpperAbs;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 0
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_0;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 1
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_1;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 2
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_2;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 3
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_3;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 4
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_4;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 5
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_5;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 6
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_6;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 7
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_7;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 8
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_8;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 9
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_9;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 10
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_10;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 11
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_11;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 12
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_12;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 13
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_13;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 14
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_14;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 15
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_15;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 16
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_16;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 17
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_17;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 18
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_18;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 19
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_19;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 20
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_20;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 21
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_21;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 22
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_22;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 23
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_23;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 24
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_24;

    /* Chr Type 13 Phantom - Max Reinforcement Coefficient 25
     *   Maximum weapon enhancement level factor for whether to apply level sync */
    unsigned char matchingWeaponLevelUpperUnk_25;

    float unknown_0x310;

    float unknown_0x314;

    float unknown_0x318;

    float unknown_0x31c;

    float unknown_0x320;

    float unknown_0x324;

    float unknown_0x328;

    float unknown_0x32c;

    float unknown_0x330;

    float unknown_0x334;

    float unknown_0x338;

    float unknown_0x33c;

    float unknown_0x340;

    float unknown_0x344;

    int unknown_0x34c;

    int unknown_0x350;

    int unknown_0x354;

    int unknown_0x358;

    int unknown_0x35c;

    /* Base Scadu Blessing SpEffect ID */
    int baseScaduBlessingSpEffectId;

    /* Base Revered Spirit Ash Blessing SpEffect ID */
    int baseReveredSpiritAshBlessingSpEffectId;

    int unknown_0x368;

    int unknown_0x36c;

    int unknown_0x370;

    /* Player Riding Poise - Absorption %
     *   Applied to isAddBaseAtk attacks only */
    float ridingSAReceivedRatePlayer;

    /* Enemy Riding Poise - Absorption %
     *   Applied to isAddBaseAtk attacks only */
    float ridingSAReceivedRateNotPlayer;

    /* Glovewort Crystal Spirit Buff SpEffect ID */
    int glovewortCrystalSpiritBuffSpEffectId;

    int unknown_0x380;

    float unknown_0x384;

    /* Unknown SpEffect ID */
    int unknownSpEffectId_0x388;

    /* Unknown SpEffect ID */
    int unknownSpEffectId_0x38c;

    /* Unknown SpEffect ID */
    int unknownSpEffectId_0x390;

    /* Base Revered Spirit Torrent Blessing SpEffect ID */
    int baseReveredSpiritTorrentBlessingSpEffectId;

    char endPad[108];
} game_system_common_param_t;
