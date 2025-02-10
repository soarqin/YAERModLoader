#pragma once

typedef struct npc_think_param_s {
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

    /* ロジックスクリプトID
     *   スクリプトで作成したロジックのIDを設定します。
     * Logic ID
     *   Set the ID of the logic created by the script.
     * Default Value  = -1 */
    int logicId;

    /* 戦闘ゴールID
     *   戦闘ゴールID
     * Battle Goal ID
     *   Battle goal ID
     * Default Value  = -1 */
    int battleGoalID;

    /* 索敵視覚_距離[m]
     *   索敵視覚による索敵範囲.
     * Vision - Distance
     *   Search range by visual search. */
    unsigned short searchEye_dist;

    /* 索敵視覚_角度（幅）[deg]
     *   索敵視覚による索敵範囲.
     * Vision - Width
     *   Search range by visual search. */
    unsigned char searchEye_angY;

    /* 巨大敵を迂回しないか
     *   巨大敵を迂回しないか
     * Don't Avoid Giant Enemy
     *   Do you not detour a huge enemy? */
    unsigned char isNoAvoidHugeEnemy:1;

    /* 納刀抜刀するか
     *   納刀抜刀するか
     * Enable Weapon Switch
     *   Do you want to pull out the sword? */
    unsigned char enableWeaponOnOff:1;

    /* ロックダミポリ(エネミー用)を狙うか
     *   ロックダミポリ(エネミー用)を狙うか
     * Aim for AI Target Lock Dummy Poly ID
     *   Do you aim for Rock Damipoli (for enemies)?
     * Default Value  = 1 */
    unsigned char targetAILockDmyPoly:1;

    /* パディング */
    char pad8:5;

    /* 遠隔攻撃用特殊効果ID
     *   遠隔攻撃用特殊効果ID
     * Ranged Attack - SpEffect ID
     *   Special effects ID for ranged attacks
     * Default Value  = -1 */
    int spEffectId_RangedAttack;

    /* 索敵Lv1ターゲット忘れる時間[sec]
     *   索敵Lv1ターゲット忘れる時間。
     * Search Forget Time - Level 1
     *   Search enemy Lv1 Target Time to forget.
     * Default Value  = 5 */
    float searchTargetLv1ForgetTime;

    /* 索敵Lv2ターゲット忘れる時間[sec]
     *   索敵Lv2ターゲット忘れる時間。
     * Search Forget Time - Level 2
     *   Search enemy Lv2 time to forget the target.
     * Default Value  = 8 */
    float searchTargetLv2ForgetTime;

    /* 敵壁接触時のBackHome時間[sec]
     *   ブロックをさえぎる敵壁に接触したとき、BackToHomeゴールの寿命
     * Back Home Time on Touching Enemy Wall
     *   The life of the BackToHome goal when it touches an enemy wall that blocks the block
     * Default Value  = 5 */
    float BackHomeLife_OnHitEneWal;

    /* 視覚ターゲット忘れる時間[sec]
     *   視覚ターゲット忘れる時間。
     * Vision - Search Forget Time
     *   Time to forget the visual target.
     * Default Value  = 600 */
    float SightTargetForgetTime;

    /* 動けなくなったときに行うEzState番号
     *   破壊可能なオブジェクトによって動きが止まっている場合、自動的に実行する行動。
     * Blocked Movement - Anim ID
     *   An action that automatically takes place when a destructible object stops it. */
    int idAttackCannotMove;

    /* 聴覚_距離[m]
     *   聴覚による索敵範囲.。
     * Listen - Distance
     *   Hearing search range ... */
    float ear_dist;

    /* 仲間呼び 応答アクションアニメID
     *   応答する時のアニメID(EzStateAnimID)
     * Call Help - Action Animation ID
     *   Animation ID (EzStateAnimID) when responding
     * Default Value  = -1 */
    int callHelp_ActionAnimId;

    /* 仲間呼び_仲間呼びアクションID
     *   仲間呼ぶときのアクションID(EzStateAnimID)
     * Call Help - Call Action ID
     *   Action ID (EzStateAnimID) when calling a friend
     * Default Value  = -1 */
    int callHelp_CallActionId;

    /* 視覚_距離[m]
     *   視覚による索敵範囲.
     * Vision - Distance
     *   Visual search range. */
    unsigned short eye_dist;

    /* 行動時ガード使用するか
     *   行動にガードするか（帰宅時、ターゲットの方を見ている時想定）
     * Use Guard during Action
     *   Whether to guard against actions (assumed when returning home, looking toward the target) */
    unsigned char isGuard_Act;

    /* パディング */
    char pad6[1];

    /* 聴覚　影響カット距離[m]
     *   音源のサイズを小さくする距離。この距離未満の音が聞こえなくなります。
     * Listen - Sound Cutoff Distance
     *   The distance to reduce the size of the sound source. You will not hear any sound below this distance. */
    unsigned short ear_soundcut_dist;

    /* 嗅覚_距離[m]
     *   嗅覚による索敵範囲.
     * Sense - Distance
     *   Search range by smell. */
    unsigned short nose_dist;

    /* 何があっても帰宅する距離[m]
     *   COMMON_SetBattleActLogicの引き数
     * Retreat Home - Max Distance
     *   COMMON_SetBattleActLogic argument */
    unsigned short maxBackhomeDist;

    /* 戦闘しつつ帰宅する距離[m]
     *   COMMON_SetBattleActLogicの引き数
     * Retreat Home - Distance
     *   COMMON_SetBattleActLogic argument */
    unsigned short backhomeDist;

    /* 巣に帰るのをあきらめて戦闘する距離[m]
     *   COMMON_SetBattleActLogicの引き数
     * Retreat Home - Battle Distance
     *   COMMON_SetBattleActLogic argument */
    unsigned short backhomeBattleDist;

    /* 敵を意識しているときの非戦闘行動時間[sec]
     *   COMMON_SetBattleActLogicの引き数
     * Non-Battle Act Duration when in Combat
     *   COMMON_SetBattleActLogic argument */
    unsigned short nonBattleActLife;

    /* 帰宅時：ターゲットを見ている時間[sec]
     *   帰宅時：ターゲットを見ている時間[sec]
     * Retreat Home - Look for Target Time
     *   When returning home: Time to look at the target [sec]
     * Default Value  = 3 */
    unsigned short BackHome_LookTargetTime;

    /* 帰宅時：ターゲットを見ている距離[m]
     *   帰宅時：ターゲットを見ている距離[m]
     * Retreat Home - Look for Target Distance
     *   When returning home: Distance to see the target [m]
     * Default Value  = 10 */
    unsigned short BackHome_LookTargetDist;

    /* 音ターゲット忘れる時間[sec]
     *   音ターゲット忘れる時間。
     * Listen - Search Forget Time
     *   Time to forget the sound target.
     * Default Value  = 3 */
    float SoundTargetForgetTime;

    /* 戦闘開始距離[m]
     * Battle - Start Distance */
    unsigned short BattleStartDist;

    /* 仲間呼び 自分の仲間グループID
     *   自分の仲間グループID
     * Call Help - My Peer ID
     *   My fellow group ID */
    unsigned short callHelp_MyPeerId;

    /* 仲間呼び 呼ぶ仲間グループID
     *   仲間を呼ぶ対象となる仲間グループID
     * Call Help - Call Peer ID
     *   Companion group ID to call a companion */
    unsigned short callHelp_CallPeerId;

    /* ダメージ影響率[％]
     *   ダメージ影響率取得(ターゲットシステム評価情報)
     * Target System - Damage Effect Rate
     *   Damage impact rate acquisition (target system evaluation information)
     * Default Value  = 100 */
    unsigned short targetSys_DmgEffectRate;

    /* チーム攻撃影響力[0-100]
     *   チーム内の同時攻撃人数を決めるための値。値を大きくすると、同時に攻撃参加できる人数が少なくなる。
     * Team Attack Effectivity
     *   A value for determining the number of simultaneous attacks in a team. Increasing the value reduces the number of people who can participate in the attack at the same time.
     * Default Value  = 25 */
    unsigned char TeamAttackEffectivity;

    /* 視覚_角度（高さ）[deg]
     *   視覚による索敵範囲.
     * Vision - Height Angle
     *   Visual search range. */
    unsigned char eye_angX;

    /* 視覚_角度（幅）[deg]
     *   視覚による索敵範囲.
     * Vision - Width Angle
     *   Visual search range. */
    unsigned char eye_angY;

    /* 暗闇影響しない
     *   警戒視覚_距離、戦闘開始距離が暗闇による影響を受けないようにするか
     * Disable Darkness Modifier to Distance
     *   Whether the alert vision_distance and battle start distance are not affected by the darkness */
    unsigned char disableDark;

    /* キャラバンでの役割
     *   キャラバンでの役割
     * Caravan Role
     *   Role in the caravan */
    unsigned char caravanRole;

    /* 仲間呼び_ターゲットとの最低距離[m]
     *   この値より近い場合は仲間呼びできない.
     * Call Help - Valid Target Min Distance
     *   If it is closer than this value, you cannot call a friend.
     * Default Value  = 5 */
    unsigned char callHelp_CallValidMinDistTarget;

    /* 仲間呼び_仲間を呼ぶ有効距離[m]
     *   この値より仲間が遠い場合は呼ばない。
     * Call Help - Valid Target Range
     *   Do not call if the companion is farther than this value.
     * Default Value  = 15 */
    unsigned char callHelp_CallValidRange;

    /* 仲間呼び 応答してから忘れる時間[sec]
     *   応答する時間
     * Call Help - Forget Time by Arrival
     *   Time to respond */
    unsigned char callHelp_ForgetTimeByArrival;

    /* 応答時の待機最小時間[ssm=>ss．mSec]
     *   応答ゴールの最初の待機ゴールでの最小時間[101=>10．1sec]
     * Call Help - Min Wait Time
     *   Minimum time for the first wait goal of the response goal [101 => 10.1sec] */
    unsigned char callHelp_MinWaitTime;

    /* 応答時の待機最大時間[ssm=>ss．mSec]
     *   応答ゴールの最初の待機ゴールでの最大時間[101=>10．1sec]
     * Call Help - Max Wait Time
     *   Maximum time for the first waiting goal of the response goal [101 => 10.1sec] */
    unsigned char callHelp_MaxWaitTime;

    /* ゴールアクション：警戒状態/通常音
     *   ゴールアクション：ターゲットが通常音の感知により警戒状態になった
     * Goal Action - To Caution (Sound)
     *   Goal action: Target becomes alert due to normal sound detection */
    unsigned char goalAction_ToCaution;

    /* 聴覚_可聴AI音レベル
     *   どれくらい耳が良いのか
     * Listen - Listen Level
     *   How good your ears are
     * Default Value  = 128 */
    unsigned char ear_listenLevel;

    /* 仲間呼び 応答後の行動タイプ
     *   応答後、目標位置までの行動タイプ
     * Call Help - Reply Behavior Type
     *   Action type to target position after response */
    unsigned char callHelp_ReplyBehaviorType;

    /* パス移動しない
     *   パス移動命令が来てもパスを辿らずに直接移動するか
     * Disable Path Move
     *   Whether to move directly without following the path even if a path move command comes */
    unsigned char disablePathMove;

    /* 視線による到着判定をスキップするか？
     *   視線による到着判定をスキップするか？Onにすると、視線が通っていなくても、到着判定を行う。
     * Skip Arrival Visibility Check
     *   Do you want to skip the arrival judgment by the line of sight? When set to On, arrival judgment is performed even if the line of sight does not pass. */
    unsigned char skipArrivalVisibleCheck;

    /* 取巻き役になるか？
     *   思考属性：ＯＮにすると取巻き役を演じます。
     * Think Attribute - Do Admirer
     *   Thinking attribute: When turned on, it plays a role of surrounding. */
    unsigned char thinkAttr_doAdmirer;

    /* フラグ「崖」通れるか？
     *   ノード「崖」を通過できるか？(def:1)
     * Navigation - Edge
     *   Can you pass through the node cliff? (def: 1)
     * Default Value  = 1 */
    unsigned char enableNaviFlg_Edge:1;

    /* フラグ「広い」通れるか？
     *   ノード「広い」を通過できるか？(def:1)
     * Navigation - Large Space
     *   Can you pass through the node wide? (def: 1)
     * Default Value  = 1 */
    unsigned char enableNaviFlg_LargeSpace:1;

    /* フラグ「梯子」通れるか？
     *   ノード「梯子」を通過できるか？(def:0)
     * Navigation - Ladder
     *   Can you pass through the node ladder? (def: 0) */
    unsigned char enableNaviFlg_Ladder:1;

    /* フラグ「穴」通れるか？
     *   ノード「穴」を通過できるか？(def:0)
     * Navigation - Hole
     *   Can you go through the node hole? (def: 0) */
    unsigned char enableNaviFlg_Hole:1;

    /* フラグ「扉」通れるか？
     *   ノード「扉」を通過できるか？(def:0)
     * Navigation - Door
     *   Can you pass through the node door? (def: 0) */
    unsigned char enableNaviFlg_Door:1;

    /* フラグ「壁中」通れるか？
     *   ノード「壁中」を通過できるか？(def:0)
     * Navigation - Ignore Navmesh Wall
     *   Can you pass through the node in the wall? (def: 0) */
    unsigned char enableNaviFlg_InSideWall:1;

    /* フラグ「溶岩」通れるか？
     *   ノード「溶岩」を通過できるか？(def:0)
     * Navigation - Lava
     *   Can you pass through the node lava? (def: 0) */
    unsigned char enableNaviFlg_Lava:1;

    /* フラグ「崖」通れるか？（通常／警戒状態）
     *   通常／警戒状態でノード「崖」を通過できるか？(def:1)
     * Navigation - Cliff Edge
     *   Can you pass the node cliff under normal / alert conditions? (def: 1)
     * Default Value  = 1 */
    unsigned char enableNaviFlg_Edge_Ordinary:1;

    /* ほんとに予約
     *   フラグが新しく必要になったらここにいれます（NotPadding) */
    char enableNaviFlg_reserve1[3];

    /* 索敵Lv0→Lv1の閾値
     *   索敵Lv0→Lv1の閾値
     * Search Threshold - Level 0 to Level 1
     *   Search enemy Lv0  Lv1 threshold
     * Default Value  = 10 */
    int searchThreshold_Lv0toLv1;

    /* 索敵Lv1→Lv2の閾値
     *   索敵Lv1→Lv2の閾値
     * Search Threshold - Level 1 to Level 2
     *   Search enemy Lv1  Lv2 threshold
     * Default Value  = 70 */
    int searchThreshold_Lv1toLv2;

    /* 小隊反応遅延時間[sec]
     *   小隊反応遅延時間[sec]
     * Platoon - Reply Time
     *   Platoon reaction delay time [sec] */
    float platoonReplyTime;

    /* 小隊反応追加ランダム時間[sec]
     *   小隊反応追加ランダム時間[sec]
     * Platoon - Reply Add Random Time
     *   Platoon reaction additional random time [sec] */
    float platoonReplyAddRandomTime;

    /* 索敵視覚_角度(高さ)[deg]
     *   索敵視覚_角度(高さ)[deg]
     * Vision - Search Height Angle
     *   Searching enemy vision_angle (height) [deg] */
    unsigned char searchEye_angX;

    /* 戦闘視界を上書きするか？
     *   戦闘視界を上書きするか
     * Update Battle Vision
     *   Do you want to overwrite the battle view? */
    unsigned char isUpdateBattleSight;

    /* 戦闘視覚_上書き距離[m]
     *   戦闘視覚_上書き距離[m]
     * Battle Vision - Overwrite Distance
     *   Battle Vision_Overwrite Distance [m] */
    unsigned short battleEye_updateDist;

    /* 戦闘視覚_上書き角度(高さ)[deg]
     *   戦闘視覚_上書き角度(高さ)[deg]
     * Battle Vision - Overwrite Height Angle
     *   Battle Vision_Overwrite Angle (Height) [deg] */
    unsigned char battleEye_updateAngX;

    /* 戦闘視覚_上書き角度(幅)[deg]
     *   戦闘視覚_上書き角度(幅)[deg]
     * Battle Vision - Overwrite Width Angle
     *   Battle Vision_Overwrite Angle (Width) [deg] */
    unsigned char battleEye_updateAngY;

    /* パディング */
    char pad4[16];

    /* 視覚_発生距離[m]
     *   キャラの中心からこの距離後ろが視角開始位置になる
     * Vision - Start Position - Backward Offset
     *   The viewing angle start position is behind this distance from the center of the character. */
    unsigned short eye_BackOffsetDist;

    /* 視覚_カット距離[m]
     *   視角発生位置からこの距離は認識しない
     * Vision - Start Distance
     *   This distance is not recognized from the viewing angle generation position */
    unsigned short eye_BeginDist;

    /* パス検索失敗/帰巣限界時の行動種別
     *   パス検索失敗時、代替パスの終点に到達した際/帰巣限界距離まで到達した際に行うデフォルトの行動種別
     * Act Type on Failed Path
     *   Default action type to be performed when the path search fails, when the end point of the alternative path is reached / when the homecoming limit distance is reached */
    unsigned char actTypeOnFailedPath;

    /* ゴールアクション：警戒状態/重要音
     *   ゴールアクション：ターゲットが重要音の感知により警戒状態になった
     * Goal Action - Target Alerted by Important Sound
     *   Goal action: Target becomes alert due to detection of important sound */
    unsigned char goalAction_ToCautionImportant;

    /* 遠隔攻撃用持ち替えアニメID
     *   AI攻撃パラメータの参照ID
     * Shift Animation ID on Ranged Attack
     *   Reference ID for AI attack parameters
     * Default Value  = -1 */
    int shiftAnimeId_RangedAttack;

    /* パス検索失敗時の挙動（非戦闘中）
     *   ターゲット【なし】時に、現在地点を巣に書き換えた後に取る行動 
     * Act Type on Non-BTL Failed Path
     *   Target [None] Sometimes, the action to be taken after rewriting the current location to a nest */
    unsigned char actTypeOnNonBtlFailedPath;

    /* バディAI
     *   バディ用の思考か
     * Is Spirit Summon AI
     *   Thinking for a buddy */
    unsigned char isBuddyAI;

    /* ゴールアクション：索敵Lv1
     *   ゴールアクション：ターゲットが索敵Lv1になった
     * Goal Action - Target Search Level 1
     *   Goal action: Target becomes Lv1 */
    unsigned char goalAction_ToSearchLv1;

    /* ゴールアクション：索敵Lv2
     *   ゴールアクション：ターゲットが索敵Lv2になった
     * Goal Action - Target Search Level 2
     *   Goal action: Target became enemy Lv2 */
    unsigned char goalAction_ToSearchLv2;

    /* エッジ「ジャンプ」使うか（非戦闘状態）
     *   ジャンプ用ユーザーエッジを飛び越えて移動するか(非戦闘状態)
     * Jump Move Type
     *   Whether to jump over the user edge for jumping (non-combat state) */
    unsigned char enableJumpMove;

    /* 回避移動しない
     *   他のキャラクターを回避しながら移動しようとする挙動(ローカルステアリング)をオフにするか？
     * Disable Local Steering
     *   Do you want to turn off the behavior (local steering) that tries to move while avoiding other characters? */
    unsigned char disableLocalSteering;

    /* ゴールアクション：記憶ターゲット状態
     *   ゴールアクション：ターゲットを見失った
     * Goal Action - Target Lost
     *   Goal action: Lost target */
    unsigned char goalAction_ToDisappear;

    /* ゴールアクション：通常状態開始
     *   通常状態に遷移したときのアクション
     * Change State Action - To Normal
     *   Action when transitioning to the normal state */
    unsigned char changeStateAction_ToNormal;

    /* 記憶ターゲット忘れる時間[sec]
     *   記憶ターゲット忘れる時間。
     * Time to Forget Target
     *   Time to forget the memory target.
     * Default Value  = 150 */
    float MemoryTargetForgetTime;

    /* 遠隔攻撃アニメID
     *   遠隔攻撃する際にエネミーが出す攻撃IDを指定するパラメータ
     * Attack ID - On Ranged Attack
     *   A parameter that specifies the attack ID issued by the enemy when making a ranged attack
     * Default Value  = -1 */
    int rangedAttackId;

    /* エッジ「飛び降り」使うか（非戦闘状態）
     *   AIが非戦闘状態で、飛び降りエッジを通行できるようにする
     * Use Fall Jump - Outside of Combat
     *   Allows AI to pass the jumping edge in non-combat state
     * Default Value  = 2 */
    unsigned char useFall_onNormalCaution;

    /* エッジ「飛び降り」使うか（戦闘状態）
     *   AIが戦闘状態で、飛び降りエッジを通行できるようにする 
     * Use Fall Jump - In Combat
     *   Allow AI to pass through the jumping edge in combat
     * Default Value  = 2 */
    unsigned char useFall_onSearchBattle;

    /* エッジ「ジャンプ」使うか（戦闘状態）
     *   ジャンプ用ユーザーエッジを飛び越えて移動するか(戦闘状態)
     * Enable Jump - In Combat
     *   Whether to jump over the user edge for jumping (combat state) */
    unsigned char enableJumpMove_onBattle;

    /* 帰巣限界でハマった時の挙動
     *   帰巣限界でハマった時の挙動
     * Back to Home Stuck Act
     *   Behavior when addicted to the homecoming limit */
    unsigned char backToHomeStuckAct;

    /* パディング
     *   pad */
    char pad3[4];

    /* 振る舞いID1
     *   聴くことのできる音ターゲットの振る舞いIDに対応
     * Sound Behavior ID [1]
     *   Corresponds to the behavior ID of the sound target that can be heard
     * Default Value  = -1 */
    int soundBehaviorId01;

    /* 振る舞いID2
     *   聴くことのできる音ターゲットの振る舞いIDに対応
     * Sound Behavior ID [2]
     *   Corresponds to the behavior ID of the sound target that can be heard
     * Default Value  = -1 */
    int soundBehaviorId02;

    /* 振る舞いID3
     *   聴くことのできる音ターゲットの振る舞いIDに対応
     * Sound Behavior ID [3]
     *   Corresponds to the behavior ID of the sound target that can be heard
     * Default Value  = -1 */
    int soundBehaviorId03;

    /* 振る舞いID4
     *   聴くことのできる音ターゲットの振る舞いIDに対応
     * Sound Behavior ID [4]
     *   Corresponds to the behavior ID of the sound target that can be heard
     * Default Value  = -1 */
    int soundBehaviorId04;

    /* 振る舞いID5
     *   聴くことのできる音ターゲットの振る舞いIDに対応
     * Sound Behavior ID [5]
     *   Corresponds to the behavior ID of the sound target that can be heard
     * Default Value  = -1 */
    int soundBehaviorId05;

    /* 振る舞いID6
     *   聴くことのできる音ターゲットの振る舞いIDに対応
     * Sound Behavior ID [6]
     *   Corresponds to the behavior ID of the sound target that can be heard
     * Default Value  = -1 */
    int soundBehaviorId06;

    /* 振る舞いID7
     *   聴くことのできる音ターゲットの振る舞いIDに対応
     * Sound Behavior ID [7]
     *   Corresponds to the behavior ID of the sound target that can be heard
     * Default Value  = -1 */
    int soundBehaviorId07;

    /* 振る舞いID8
     *   聴くことのできる音ターゲットの振る舞いIDに対応
     * Sound Behavior ID [8]
     *   Corresponds to the behavior ID of the sound target that can be heard
     * Default Value  = -1 */
    int soundBehaviorId08;

    /* 納刀時特殊効果ID
     *   納刀時特殊効果ID
     * Weapon Switch Out - SpEffect ID
     *   Special effect ID at the time of sword delivery
     * Default Value  = -1 */
    int weaponOffSpecialEffectId;

    /* 抜刀時特殊効果ID
     *   抜刀時特殊効果ID
     * Weapon Switch In - SpEffect ID
     *   Special effect ID when pulling out a sword
     * Default Value  = -1 */
    int weaponOnSpecialEffectId;

    /* 納刀アニメID
     *   納刀アニメID
     * Weapon Switch Out - Animation ID
     *   Katana Anime ID
     * Default Value  = -1 */
    int weaponOffAnimId;

    /* 抜刀アニメID
     *   抜刀アニメID
     * Weapon Switch In - Animation ID
     *   Sword animation ID
     * Default Value  = -1 */
    int weaponOnAnimId;

    /* 驚くアニメID
     *   驚くアニメID
     * Stealth Attack - Animation ID
     *   Amazing anime ID
     * Default Value  = -1 */
    int surpriseAnimId;
} npc_think_param_t;
