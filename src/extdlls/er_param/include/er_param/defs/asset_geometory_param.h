#pragma once

typedef struct er_asset_geometory_param_s {
    /* サウンドのバンクID
     *   サウンドのバンクID(-1:バンクなし, それ以外:指定したIDのバンク)
     * Sound Bank ID
     *   Sound bank ID (-1: no bank, other: bank with specified ID)
     * Default Value  = -1 */
    int soundBankId;

    /* 破壊音SEID
     *   破壊音SEID(9桁) -1：assetIdから生成
     * Sound Break SE ID
     *   Destruction sound SEID (9 digits) -1: Generated from assetId
     * Default Value  = -1 */
    int soundBreakSEId;

    /* 描画パラメータ参照ID
     *   描画パラメータ参照ID。パーツ描画パラメータ.xlsmの参照IDです。
     * Draw Param Reference ID
     *   Drawing parameter reference ID. The reference ID for the part drawing parameter .xlsm.
     * Default Value  = -1 */
    int refDrawParamId;

    /* 静的アセットヒット構築設定
     *   静的アセットのヒット構築タイプを設定します。動的アセットでは無視されます。
     * Hit Create Type
     *   Sets the hit build type for static assets. Ignored for dynamic assets. */
    char hitCreateType;

    /* アセット挙動タイプ
     *   動的(すべてのアセット機能が使用可能)、静的(旧マップ扱いの機能制限された軽いアセット)、部分静的(部分破壊アセット)
     * Asset Behavior Type
     *   Dynamic (all asset features available), static (light assets with limited functionality treated as old maps), partially static (partially destroyed assets)
     * Default Value  = 1 */
    unsigned char behaviorType;

    /* 衝突判定タイプ
     *   衝突判定タイプ。アセットが何と当たるかが設定できます。
     * Collision Detection Type
     *   Collision detection type. You can set what the asset will hit. */
    unsigned char collisionType;

    /* 雨遮断設定
     *   雨遮断のタイプです。SFXと濡れ表現の遮断設定が行えます
     * Rain Blocking Type
     *   It is a type of rain blocking. You can set the blocking of SFX and wet expression. */
    unsigned char rainBlockingType;

    /* HP
     *   破壊までの耐久力(-1:破壊不可)
     * HP
     *   Durability until destruction (-1: Indestructible)
     * Default Value  = -1 */
    short hp;

    /* 防御力
     *   この値以下の攻撃力はダメージなし
     * Defence
     *   Attack power below this value is no damage */
    unsigned short defense;

    /* 破壊後強制停止時間
     *   破壊されてから剛体を強制的に停止するまでの時間（0で強制停止しない）
     * Destruction Stop Time
     *   Time from destruction to forced stop of rigid body (do not force stop at 0)
     * Default Value  = 30 */
    float breakStopTime;

    /* 破壊時SFXID
     *   破壊時のSFXID(-1:デフォルト(810030))
     * Destruction SFX ID
     *   SFX ID on destruction (-1: default (810030))
     * Default Value  = -1 */
    int breakSfxId;

    /* 破壊時SFXダミポリID
     *   破壊時SFXの発生位置ダミポリID(-1：配置位置）
     * Destruction SFX Dummy Poly ID
     *   SFX generation position at the time of destruction Damipoly ID (-1: placement position)
     * Default Value  = -1 */
    int breakSfxCpId;

    /* 破壊後着地時SFX識別子
     *   破壊された後、最初に着地した際に再生するオブジェ材質依存SFXの識別子(-1:発生しない)
     * Destruction Landing SFX ID
     *   Object material-dependent SFX identifier that regenerates when first landing after being destroyed (-1: does not occur)
     * Default Value  = -1 */
    int breakLandingSfxId;

    /* 破壊時 弾発生 行動パラメータID
     *   破壊時[弾]の行動パラメータ(-1:発生しない)。周回によるオフセットの仕様があるので注意。(【GR】SEQ35556 )
     * Destruction Bullet Behavior ID
     *   Action parameter of [bullet] at the time of destruction (-1: does not occur). Please note that there is an offset specification due to laps. ([GR] SEQ35556)
     * Default Value  = -1 */
    int breakBulletBehaviorId;

    /* 破壊時 弾発生 ダミポリID
     *   破壊時[弾]の発生位置ダミポリID(-1:配置位置)
     * Destruction Bullet Dummy Poly ID
     *   Location of [bullet] at the time of destruction Damipoli ID (-1: placement position)
     * Default Value  = -1 */
    int breakBulletCpId;

    /* 破片非表示 待機時間(秒)
     *   破片非表示 待機時間(秒)
     * Hidden Debris - Wait Time
     *   Hidden debris Waiting time (seconds) */
    float FragmentInvisibleWaitTime;

    /* 破片非表示 時間(秒)
     *   破片を非表示にさせる時間(秒)
     * Hidden Debris - Time to Hide
     *   Time to hide debris (seconds) */
    float FragmentInvisibleTime;

    /* 破壊時発生AI音ID
     *   破壊時に発生させるAI音ID
     * Destruction AI Sound ID
     *   AI sound ID generated at the time of destruction */
    int BreakAiSoundID;

    /* 破壊時_アイテム抽選種別
     *   破壊時に抽選したアイテムの入手方法を決めるタイプ
     * Destruction Item Lot Type
     *   A type that decides how to obtain items drawn at the time of destruction */
    char breakItemLotType;

    /* アニメ破壊ID最大値
     *   アニメ破壊IDが0番から何番までか
     * Anim Break ID Max
     *   What is the animation destruction ID from 0 to what? */
    unsigned char animBreakIdMax;

    /* 破壊時 弾発生 属性ダメージ条件
     *   アセット破壊時に最後に受けたダメージがこの設定の条件を満たしていれば弾丸を生成する
     * Destruction Bullet Attribute Damage Type
     *   Generates a bullet if the last damage received when destroying an asset meets the conditions of this setting. */
    char breakBulletAttributeDamageType;

    /* プレイヤ衝突で壊れるか
     *   プレイヤが接触したときに壊れ(0:ない, 1:る)
     * Is Destroyed on Player Collision
     *   Broken when the player touches (0: no, 1:) */
    unsigned char isBreakByPlayerCollide:1;

    /* 敵キャラ衝突で壊れるか
     *   敵キャラが接触したときに壊れ(0:ない, 1:る)
     * Is Destroyed on Enemy Collision
     *   Broken when an enemy character touches (0: No, 1: Ru) */
    unsigned char isBreakByEnemyCollide:1;

    /* キャラが乗ったら壊れるか
     *   キャラが乗ったら壊れるか(0:壊れるない 1:壊れる)
     * Is Destroyed by Riding
     *   Will it break if the character gets on (0: it won't break 1: it will break) */
    unsigned char isBreak_ByChrRide:1;

    /* 初期出現用破壊禁止
     *   プレイヤの初期出現で壊れ(0:る, 1:ない)
     * Is Destroyed by Default
     *   Broken at the initial appearance of the player (0: ru, 1: no) */
    unsigned char isDisableBreakForFirstAppear:1;

    /* アニメ破壊か
     *   アニメ破壊か(0:物理破壊, 1:アニメ破壊)
     * Is Animated Destruction
     *   Is it animation destruction (0: physical destruction, 1: animation destruction) */
    unsigned char isAnimBreak:1;

    /* ダメージを遮蔽するか
     *   ダメージを受けたときに、そのダメージを反対側に通さないかどうか　(0:通す, 1:通さない)
     * Is Damage Transferred
     *   Whether to pass the damage to the other side when receiving damage (0: pass, 1: do not pass) */
    unsigned char isDamageCover:1;

    /* 攻撃を弾くか
     *   攻撃を弾くか(0:弾かない, 1:弾く)
     * Is Attack Backlash
     *   Do you play the attack (0: do not play, 1: play)
     * Default Value  = 1 */
    unsigned char isAttackBacklash:1;

    /* リザーブ2 */
    unsigned char unknown_0x3b_7:1;

    /* ハシゴか
     *   ハシゴか(0:ちがう, 1:そう)
     * Is Ladder
     *   Is it a ladder (0: different, 1: yes) */
    unsigned char isLadder:1;

    /* 移動オブジェか
     *   移動オブジェか。マルチ時の移動処理の分岐に使われるフラグです(0:ちがう, 1:そう)
     * Is Moving Object
     *   Is it a moving object? It is a flag used for branching of movement processing at the time of multi (0: different, 1: yes) */
    unsigned char isMoveObj:1;

    /* 天球扱いか
     *   天球扱いの処理(プレイヤー追従など)が行われます(0:ちがう, 1:そう)
     * Is Celestial Sphere
     *   Processing that treats the celestial sphere (player tracking, etc.) is performed (0: different, 1: yes) */
    unsigned char isSkydomeFlag:1;

    /* ポリ劇中アニメを停止するか
     *   ポリ劇中アニメを停止するか(0:しない, 1:する)
     * Is Paused during Cutscene
     *   Do you want to stop the animation during the poly play (0: not, 1: do) */
    unsigned char isAnimPauseOnRemoPlay:1;

    /* 燃焼するか
     *   燃焼するか(0:しない, 1:する)
     * Is Flammable
     *   Will it burn (0: not, 1:) */
    unsigned char isBurn:1;

    /* 再収集時変化があるか
     *   このフラグが○なら、配置単位で再度収集するアセットでは「再収集時_***」のパラメータが使われます
     * Is Repicked
     *   If this flag is , the parameter At the time of recollection _ *** will be used for the assets to be collected again in units of placement. */
    unsigned char isEnableRepick:1;

    /* 収集時破壊か
     *   ×なら収集時にアニメ再生、○なら収集時に破壊（差し替えなど含めた全ての場合において破壊）
     * Is Destroyed on Pickup
     *   If , play the animation at the time of collection, if , destroy at the time of collection (destroy in all cases including replacement) */
    unsigned char isBreakOnPickUp:1;

    /* 巨大敵衝突で壊れるか
     *   巨大敵が接触したときに壊れ(0:ない, 1:る)
     * Is Destroyed by Giant Collision
     *   Broken when a giant enemy touches (0: No, 1:) */
    unsigned char isBreakByHugeenemyCollide:1;

    /* 破壊前ナビメッシュフラグ
     *   破壊前のアセットから設定されるナビメッシュフラグ
     * Pre-destruction Navmesh Flag
     *   Navigation mesh flag set from assets before destruction */
    unsigned char navimeshFlag;

    /* 燃焼 弾発生間隔(フレーム)
     *   延焼用の弾を発生する間隔(フレーム)
     * Burn Bullet Interval
     *   Interval (frame) to generate bullets for spreading fire
     * Default Value  = 30 */
    unsigned short burnBulletInterval;

    /* クロス更新距離(m)
     *   havokClothの更新を行なうカメラからの距離(0:必ず更新する)
     * Camera Distance to Update Cloth
     *   Distance from the camera to update havokCloth (0: always update)
     * Default Value  = 30 */
    float clothUpdateDist;

    /* ランタイム生成アセットの寿命(秒)
     *   ランタイム生成アセットが生成後に消滅するまでの時間 (0:消滅しない)
     * Duration after Creation until Disappearance
     *   Runtime-generated time after creation until disappearance (0: does not disappear) */
    float lifeTime_forRuntimeCreate;

    /* プレイヤー接触時SE ID
     *   自分が操作するローカルプレイヤーが触れた際に再生するSEのID(-1:再生しない)
     * Contact SE ID
     *   SE ID to play when touched by a local player operated by you (-1: Do not play)
     * Default Value  = -1 */
    int contactSeId;

    /* 再収集時_アニメオフセット
     *   「再収集時変化があるか」が○のアセットは配置単位で再収集時、この値でオフセットしたアニメIDで未収集/収集済のアニメを再生
     * Repick Anim ID Offset
     *   When recollecting assets with Is there a change at the time of recollection? In units of placement, play the uncollected / collected animation with the anime ID offset by this value. */
    int repickAnimIdOffset;

    /* 風係数(破壊前)
     *   風係数(破壊前)
     * Wind Effect Rate - Before Destruction
     *   Wind coefficient (before destruction)
     * Default Value  = 0.5 */
    float windEffectRate_0;

    /* 風係数(破壊後)
     *   風係数(破壊後)
     * Wind Effect Rate - After Destruction
     *   Wind coefficient (after destruction)
     * Default Value  = 0.5 */
    float windEffectRate_1;

    /* 風影響タイプ(破壊前)
     *   風影響タイプ(破壊前)
     * Wind Effect Type - Before Destruction
     *   Wind effect type (before destruction) */
    unsigned char windEffectType_0;

    /* 風影響タイプ(破壊後)
     *   風影響タイプ(破壊後)
     * Wind Effect Type - After Destruction
     *   Wind effect type (after destruction) */
    unsigned char windEffectType_1;

    /* 上書き材質ID
     *   アセットの材質ID上書き設定(-1：モデルの材質IDを上書きしない 0以上：材質ID上書き)　はしご上ではこの設定でのみ材質IDが反映されます
     * Override Material ID
     *   Asset material ID overwrite setting (-1: Do not overwrite model material ID 0 or more: Material ID overwrite) On the ladder, the material ID is reflected only with this setting
     * Default Value  = -1 */
    short overrideMaterialId;

    /* 自動生成時の高さオフセット(m)
     *   マップに自動生成時にレイキャストが当たったところからどれぐらい浮かせるかの高さオフセット[m]
     * Automatic Generation Height Offset
     *   Height offset of how much it floats from where the raycast hits the map when it is automatically generated [m]
     * Default Value  = 0.1 */
    float autoCreateOffsetHeight;

    /* 燃焼時間(秒)
     *   燃焼時間(秒)(0で燃え続ける)
     * Burn Time
     *   Burning time (seconds) (continues to burn at 0) */
    float burnTime;

    /* 燃焼 破壊判定進行度
     *   破壊状態に切り替わる燃焼度の閾値
     * Burn Destroy Rate
     *   Burnup threshold for switching to the ruptured state
     * Default Value  = 0.5 */
    float burnBraekRate;

    /* 燃焼 SFXID：0
     *   燃焼時のSFXID：0 (-1：SFXなし)
     * Burn SFX ID [0]
     *   SFX ID at the time of combustion: 0 (-1: No SFX)
     * Default Value  = -1 */
    int burnSfxId;

    /* 燃焼 SFXID：1
     *   燃焼時のSFXID：1 (-1：SFXなし)
     * Burn SFX ID [1]
     *   SFX ID at the time of combustion: 1 (-1: No SFX)
     * Default Value  = -1 */
    int burnSfxId_1;

    /* 燃焼 SFXID：2
     *   燃焼時のSFXID：2 (-1：SFXなし)
     * Burn SFX ID [2]
     *   SFX ID at the time of combustion: 2 (-1: No SFX)
     * Default Value  = -1 */
    int burnSfxId_2;

    /* 燃焼 SFXID：3
     *   燃焼時のSFXID：3 (-1：SFXなし)
     * Burn SFX ID [3]
     *   SFX ID at the time of combustion: 3 (-1: No SFX)
     * Default Value  = -1 */
    int burnSfxId_3;

    /* 燃焼 SFX発生遅延 開始時間(秒)：0
     *   燃焼時のSFX発生遅延時間 開始～終了時間の間でランダムに決まる
     * Burn SFX Minimum Delay Time [0]
     *   SFX generation delay time during combustion Randomly determined between start and end times */
    float burnSfxDelayTimeMin;

    /* 燃焼 SFX発生遅延 開始時間(秒)：1
     *   燃焼時のSFX発生遅延時間 開始～終了時間の間でランダムに決まる
     * Burn SFX Minimum Delay Time [1]
     *   SFX generation delay time during combustion Randomly determined between start and end times */
    float burnSfxDelayTimeMin_1;

    /* 燃焼 SFX発生遅延 開始時間(秒)：2
     *   燃焼時のSFX発生遅延時間 開始～終了時間の間でランダムに決まる
     * Burn SFX Minimum Delay Time [2]
     *   SFX generation delay time during combustion Randomly determined between start and end times */
    float burnSfxDelayTimeMin_2;

    /* 燃焼 SFX発生遅延 開始時間(秒)：3
     *   燃焼時のSFX発生遅延時間 開始～終了時間の間でランダムに決まる
     * Burn SFX Minimum Delay Time [3]
     *   SFX generation delay time during combustion Randomly determined between start and end times */
    float burnSfxDelayTimeMin_3;

    /* 燃焼 SFX発生遅延 終了時間(秒)：0
     *   燃焼時のSFX発生遅延時間 開始～終了時間の間でランダムに決まる
     * Burn SFX Maximum Delay Time [0]
     *   SFX generation delay time during combustion Randomly determined between start and end times */
    float burnSfxDelayTimeMax;

    /* 燃焼 SFX発生遅延 終了時間(秒)：1
     *   燃焼時のSFX発生遅延時間 開始～終了時間の間でランダムに決まる
     * Burn SFX Maximum Delay Time [1]
     *   SFX generation delay time during combustion Randomly determined between start and end times */
    float burnSfxDelayTimeMax_1;

    /* 燃焼 SFX発生遅延 終了時間(秒)：2
     *   燃焼時のSFX発生遅延時間 開始～終了時間の間でランダムに決まる
     * Burn SFX Maximum Delay Time [2]
     *   SFX generation delay time during combustion Randomly determined between start and end times */
    float burnSfxDelayTimeMax_2;

    /* 燃焼 SFX発生遅延 終了時間(秒)：3
     *   燃焼時のSFX発生遅延時間 開始～終了時間の間でランダムに決まる
     * Burn SFX Maximum Delay Time [3]
     *   SFX generation delay time during combustion Randomly determined between start and end times */
    float burnSfxDelayTimeMax_3;

    /* 燃焼 弾発生 行動パラメータ：0
     *   燃焼時の弾発生行動パラメータ：0(-1:発生しない)
     * Burn Bullet Behavior ID [0]
     *   Bullet generation behavior parameter at the time of burning: 0 (-1: does not occur)
     * Default Value  = -1 */
    int burnBulletBehaviorId;

    /* 燃焼 弾発生 行動パラメータ：1
     *   燃焼時の弾発生行動パラメータ：1(-1:発生しない)
     * Burn Bullet Behavior ID [1]
     *   Bullet generation behavior parameter at the time of burning: 1 (-1: does not occur)
     * Default Value  = -1 */
    int burnBulletBehaviorId_1;

    /* 燃焼 弾発生 行動パラメータ：2
     *   燃焼時の弾発生行動パラメータ：2(-1:発生しない)
     * Burn Bullet Behavior ID [2]
     *   Bullet generation behavior parameter at the time of burning: 2 (-1: does not occur)
     * Default Value  = -1 */
    int burnBulletBehaviorId_2;

    /* 燃焼 弾発生 行動パラメータ：3
     *   燃焼時の弾発生行動パラメータ：3(-1:発生しない)
     * Burn Bullet Behavior ID [3]
     *   Bullet generation behavior parameter at the time of burning: 3 (-1: does not occur)
     * Default Value  = -1 */
    int burnBulletBehaviorId_3;

    /* 燃焼 弾発生遅延時間(秒)
     *   延焼用の弾発生を遅らせる時間(秒)
     * Burn Bullet Delay Time
     *   Time to delay the generation of bullets for fire spread (seconds) */
    float burnBulletDelayTime;

    /* ペイントデカールターゲットサイズ
     *   ペイントデカールターゲットサイズ 0：デカール無効 (0～4096 ２のべき乗 0, 2, 4, 8, … 2048 のみ有効)
     * Paint Decal Target Texture Size
     *   Paint decal target size 0: Decal disabled (0 to 4096 power of 2 0, 2, 4, 8, 2048 only valid) */
    unsigned short paintDecalTargetTextureSize;

    /* 破壊後ナビメッシュフラグ
     *   破壊後のアセットから設定されるナビメッシュフラグ
     * Post-destruction Navmesh Flag
     *   Navimesh flag set from the destroyed asset */
    unsigned char navimeshFlag_after;

    /* カメラ接近時描画
     *   カメラ接近時の描画設定。【GR】SEQ07529
     * Near Camera Behavior Type
     *   Drawing settings when approaching the camera. [GR] SEQ07529 */
    char camNearBehaviorType;

    /* 破壊時_アイテム抽選ID_マップ用
     *   破壊時に抽選させるアイテム抽選ID_マップ用　-1：抽選しない
     * Destroyed Item Lot Param ID
     *   Item to be drawn at the time of destruction Lottery ID_for map-1: No lottery
     * Default Value  = -1 */
    int breakItemLotParamId;

    /* 収集時_アクションボタンID
     *   収集で出すアクションボタンID　-1：収集機能は無効
     * Pickup Action Button Param ID
     *   Action button ID issued for collection-1: Collection function is disabled
     * Default Value  = -1 */
    int pickUpActionButtonParamId;

    /* 収集時_アイテム抽選ID_マップ用
     *   収集時に抽選させるアイテム抽選ID_マップ用　-1：収集機能は無効
     * Pickup Item Lot Param ID
     *   Item to be drawn at the time of collection For lottery ID_map-1: Collection function is invalid
     * Default Value  = -1 */
    int pickUpItemLotParamId;

    /* 自動描画グループ_裏面チェック
     *   自動描画グループ_裏面チェック
     * Auto Draw Group: Backface Check
     *   Automatic drawing group_Back side check */
    unsigned char autoDrawGroupBackFaceCheck;

    /* 自動描画グループ_遮蔽
     *   自動描画グループ_遮蔽
     * Auto Draw Group: Depth Write
     *   Auto drawing group_shield */
    unsigned char autoDrawGroupDepthWrite;

    /* 自動描画グループ_影テスト
     *   自動描画グループ_影テスト
     * Auto Draw Group: Shadow Test
     *   Automatic drawing group_shadow test */
    unsigned char autoDrawGroupShadowTest;

    /* デバッグ_許容地面高さチェック
     *   デバッグ_許容地面高さチェック 詳細はSEQ07876参照
     * Is Height Check Enabled
     *   Debug_Allow Ground Height Check See SEQ07876 for details */
    unsigned char debug_isHeightCheckEnable;

    /* 床下ナビメッシュ切り抜き対象外
     *   床（地面）のヒットより低い位置に配置された場合、床下ナビメッシュ削除対象から外すかを設定すること ツールから参照
     * Exclude from Subfloor Navmesh if below Hit
     *   If it is placed lower than the hit on the floor (ground), set whether to exclude it from the underfloor navigation mesh deletion target Refer to from the tool */
    unsigned char hitCarverCancelAreaFlag;

    /* ナビメッシュ結合制御
     *   設定されたアセットが、ナビメッシュビルド時に、ヒットパーツの結合対象から除外される
     * Block Navmesh Combine
     *   The set assets are excluded from the target of joining hit parts when building the Nav Mesh. */
    unsigned char assetNavimeshNoCombine;

    /* ナビメッシュフラグ適用先
     *   アセットから設定されるナビメッシュフラグの適用先
     * Navmesh Flag Apply Type
     *   Where to apply the navigation mesh flag set from the asset */
    unsigned char navimeshFlagApply;

    /* 破壊後ナビメッシュフラグ適用先
     *   破壊後のアセットから設定されるナビメッシュフラグの適用先
     * Navmesh Flag Apply Type - Destroyed
     *   Where to apply the navigation mesh flag set from the destroyed asset */
    unsigned char navimeshFlagApply_after;

    /* 自動描画グループ_合格ピクセル
     *   自動描画グループ_合格ピクセル（0.0～1.0に設定することで撮影時に拡大される）
     * Auto Draw Group: Pass Pixel Number
     *   Automatic drawing group_Pass pixel (set to 0.0-1.0 to enlarge at the time of shooting)
     * Default Value  = -1 */
    float autoDrawGroupPassPixelNum;

    /* 収集時_差し替えフラグ条件
     *   このイベントフラグがONの時は後続の差し替えのIDを使う　0：常に差し替えない
     * Pickup Replacement - Event Flag
     *   When this event flag is ON, use the ID of the subsequent replacement 0: Do not always replace */
    unsigned int pickUpReplacementEventFlag;

    /* 収集時_差し替えアニメオフセット
     *   「収集時_差し替えフラグ条件」がONの時、この値でオフセットしたアニメIDで未収集/収集済のアニメを再生
     * Pickup Replacement - Anim ID Offset
     *   When Collecting_replacement flag condition is ON, play the uncollected / collected animation with the animation ID offset by this value. */
    int pickUpReplacementAnimIdOffset;

    /* 収集時_差し替えアクションボタンID
     *   「収集時_差し替えフラグ条件」がONの時、このアクションボタンIDが使われる
     * Pickup Replacement - Action Button Param ID
     *   This action button ID is used when Collecting_replacement flag condition is ON.
     * Default Value  = -1 */
    int pickUpReplacementActionButtonParamId;

    /* 収集時_差し替えアイテム抽選ID_マップ用
     *   「収集時_差し替えフラグ条件」がONの時、このアイテム抽選ID_マップ用が使われる
     * Pickup Replacement - Item Lot Param ID
     *   When Collecting_replacement flag condition is ON, this item lottery ID_map is used.
     * Default Value  = -1 */
    int pickUpReplacementItemLotParamId;

    /* 地面を這う弾丸の着弾時の挙動
     *   追従タイプ「衝突しても地面を這う」の弾丸がアセットに衝突した際、着弾地点に沿う方向に曲げるか？の挙動
     * Sliding Bullet Hit Type
     *   When a bullet of the follow-up type Crawling on the ground even if it collides collides with an asset, does it bend in the direction along the landing point? Behavior */
    unsigned char slidingBulletHitType;

    /* 茂みダメージで壊れるか
     *   ◯のアセットは、 「茂みにダメージ可」◯  かつ 「オブジェ攻撃力 ＞ 防御力」の攻撃のみ、ダメージが通るようになります【GR】SEQ20617
     * Is Damaged by Special Attacks
     *    Assets can only be damaged by damage to bushes  and object attack power> defense power attacks [GR] SEQ20617 */
    unsigned char isBushesForDamage;

    /* 弾丸貫通タイプ
     *   弾丸がヒットして着弾するか？を決める時に、どの弾丸パラを参照するか？を決める値。
     * Penetration Bullet Type
     *   Will the bullet hit and land? Which bullet para to refer to when deciding? The value that determines. */
    unsigned char penetrationBulletType;

    /* リザーブ3 */
    unsigned char unkR3;

    /* リザーブ4 */
    float unkR4;

    /* 破壊音ダミポリID
     *   破壊音を再生する場所のダミポリID (-1:配置位置)
     * Destruction - Sound SE Dummy Poly ID
     *   Damipoli ID of the place where the destruction sound is played (-1: Placement position)
     * Default Value  = -1 */
    int soundBreakSECpId;

    /* デバッグ_許容地面高さ_最小[m]
     *   デバッグ_許容地面高さ_最小[m] 詳細はSEQ07876参照　最大より小さい必要あり
     * Debug - Height Check Minimum
     *   Debug_Allowable ground height_Minimum [m] See SEQ07876 for details. Must be smaller than maximum
     * Default Value  = -99 */
    float debug_HeightCheckCapacityMin;

    /* デバッグ_許容地面高さ_最大[m]
     *   デバッグ_許容地面高さ_最大[m] 詳細はSEQ07876参照　最小より大きい必要あり
     * Debug - Height Check Maximum
     *   Debug_Allowable ground height_Max [m] See SEQ07876 for details. Must be larger than minimum
     * Default Value  = 99 */
    float debug_HeightCheckCapacityMax;

    /* 再収集時_アクションボタンID
     *   「再収集時変化があるか」が○のアセットは配置単位で再収集時、このアクションボタンIDが使われる
     * Repick - Action Button ID
     *   This action button ID is used when recollecting assets whose Is there a change at the time of recollection?
     * Default Value  = -1 */
    int repickActionButtonParamId;

    /* 再収集時_アイテム抽選ID_マップ用
     *   「再収集時変化があるか」が○のアセットは配置単位で再収集時、このアイテム抽選ID_マップ用が使われる
     * Repick - Item Lot Param ID
     *   Assets with Is there a change at the time of recollection? Are used for this item lottery ID_map when recollecting in units of placement.
     * Default Value  = -1 */
    int repickItemLotParamId;

    /* 再収集時_差し替えアニメオフセット
     *   「再収集時変化があるか」が○のアセットは配置単位で再収集時、「収集時_差し替えアニメオフセット」の代わりにこのパラメータを使う
     * Repick Replacement - Anim ID Offset
     *   Use this parameter instead of At the time of collection_replacement animation offset at the time of recollection for assets whose Is there a change at the time of recollection? */
    int repickReplacementAnimIdOffset;

    /* 再収集時_差し替えアクションボタンID
     *   「再収集時変化があるか」が○のアセットは配置単位で再収集時、「収集時_差し替えアクションボタンID」の代わりにこのパラメータを使う
     * Repick Replacement - Action Button Param ID
     *   Use this parameter instead of At the time of collection_replacement action button ID when recollecting assets whose Is there a change at the time of recollection?
     * Default Value  = -1 */
    int repickReplacementActionButtonParamId;

    /* 再収集時_差し替えアイテム抽選ID_マップ用
     *   「再収集時変化があるか」が○のアセットは配置単位で再収集時、「収集時_差し替えアイテム抽選ID_マップ用」の代わりにこのパラメータを使う
     * Repick Replacement - Item Lot ID
     *   Use this parameter instead of At the time of collection_Replacement item lottery ID_For map when recollecting assets whose Is there a change at the time of recollection?
     * Default Value  = -1 */
    int repickReplacementItemLotParamId;

    /* ナビメッシュ地形内判定無効化
     *   これが設定されたAssetはCarverを作らない
     * Is Hit Carver Generation Blocked
     *   Asset with this set does not create Carver */
    unsigned char noGenerateCarver;

    /* 破壊後に巨大敵に当たらない
     *   破壊後のヒットフィルタを衝突判定タイプ巨大敵に当たらない（静○動○）相当のもので上書きする
     * Is Giant Enemy Hit by Destruction
     *   Overwrite the hit filter after destruction with a collision detection type that does not hit a huge enemy (static  dynamic ) */
    unsigned char noHitHugeAfterBreak;

    /* 破壊を同期するか
     *   これが×の場合は初期同期,マップアクティベート同期,インゲーム中のアセット破壊同期を行わないようにし、リモートPCの攻撃が当たらなくなる
     * Is Destruction Synchronized
     *   If this is x, do not perform initial synchronization, map activation synchronization, asset destruction synchronization during in-game, and the attack of the remote PC will not hit.
     * Default Value  = 1 */
    unsigned char isEnabledBreakSync:1;

    /* 再収集時_非表示
     *   配置単位で再収集時にアイテム抽選的に取れなければアセットを非表示にします
     * Is Hidden on Repick
     *   Hide assets if you can't get them by lottery when recollecting by placement unit */
    unsigned char isHiddenOnRepick:1;

    /* マルチ中のみ有効か(動的のみ)
     *   マルチ中のみ有効か。動的アセットのみ有効。(詳細：SEQ15087)
     * Is Valid for Multiplayer Only
     *   Is it valid only during multi? Only valid for dynamic assets. (Details: SEQ15087) */
    unsigned char isCreateMultiPlayOnly:1;

    /* 弾丸の着弾SFXを発生しない
     *   ○の場合、当たった弾丸が貫通しようと着弾しようと着弾SFXは発生しない
     * Is Bullet Hit SFX Disabled
     *   In the case of , the landing SFX does not occur regardless of whether the hit bullet penetrates or lands. */
    unsigned char isDisableBulletHitSfx:1;

    /* サイン／血文字作成可能か(アセット破壊前) 
     *   アセット上にいるときサイン/血文字の作成可能かを設定する(破壊前)〇：可能、×：不可能(詳細：SEQ122568)
     * Is Bloodstain/Sign Enabled before Destruction
     *   Set whether sign / blood character can be created when on the asset (before destruction) : Possible, : Impossible (Details: SEQ122568)
     * Default Value  = 1 */
    unsigned char isEnableSignPreBreak:1;

    /* サイン／血文字作成可能か(アセット破壊後) 
     *   アセット上にいるときサイン/血文字の作成可能かを設定する(破壊後)〇：可能、×：不可能(詳細：SEQ122568)
     * Is Bloodstain/Sign Enabled after Destruction
     *   Set whether sign / blood character can be created when on the asset (after destruction) : Possible, : Impossible (Details: SEQ122568)
     * Default Value  = 1 */
    unsigned char isEnableSignPostBreak:1;

    /* リザーブ1 */
    unsigned char unkR1:2;

    /* 召喚禁止/侵入禁止領域生成（ダミポリ）
     *   召喚禁止/侵入禁止領域生成（ダミポリ）
     * Multiplayer Forbidden Region Type
     *   Summoning prohibited / intrusion prohibited area generation (Damipoli) */
    unsigned char generateMultiForbiddenRegion;

    /* 常駐SEID0
     *   アセットに常駐させるサウンドID0(9桁) (-1:常駐なし)
     * Resident SE ID [0]
     *   Sound ID 0 (9 digits) to be resident in the asset (-1: No resident)
     * Default Value  = -1 */
    int residentSeId0;

    /* 常駐SEID1
     *   アセットに常駐させるサウンドID1(9桁) (-1:常駐なし)
     * Resident SE ID [1]
     *   Sound ID 1 (9 digits) to be resident in the asset (-1: No resident)
     * Default Value  = -1 */
    int residentSeId1;

    /* 常駐SEID2
     *   アセットに常駐させるサウンドID2(9桁) (-1:常駐なし)
     * Resident SE ID [2]
     *   Sound ID 2 (9 digits) to be resident in the asset (-1: No resident)
     * Default Value  = -1 */
    int residentSeId2;

    /* 常駐SEID3
     *   アセットに常駐させるサウンドID3(9桁) (-1:常駐なし)
     * Resident SE ID [3]
     *   Sound ID 3 (9 digits) to be resident in the asset (-1: not resident)
     * Default Value  = -1 */
    int residentSeId3;

    /* 常駐SEダミポリID0
     *   常駐サウンドをアタッチするダミポリID0 (-1:配置位置)
     * Resident SE ID - Dummy Poly [0]
     *   Damipoli ID0 to attach resident sound (-1: placement position)
     * Default Value  = -1 */
    short residentSeDmypolyId0;

    /* 常駐SEダミポリID1
     *   常駐サウンドをアタッチするダミポリID1 (-1:配置位置)
     * Resident SE ID - Dummy Poly [1]
     *   Damipoli ID1 to attach resident sound (-1: placement position)
     * Default Value  = -1 */
    short residentSeDmypolyId1;

    /* 常駐SEダミポリID2
     *   常駐サウンドをアタッチするダミポリID2 (-1:配置位置)
     * Resident SE ID - Dummy Poly [2]
     *   Damipoli ID2 to attach resident sound (-1: placement position)
     * Default Value  = -1 */
    short residentSeDmypolyId2;

    /* 常駐SEダミポリID3
     *   常駐サウンドをアタッチするダミポリID3 (-1:配置位置)
     * Resident SE ID - Dummy Poly [3]
     *   Damipoli ID3 to attach resident sound (-1: placement position)
     * Default Value  = -1 */
    short residentSeDmypolyId3;

    /* オープン_XB1除外割合
     *   オープン_XB1除外割合【GR】SEQ25310
     * Exclude Activate Ratio - Xbox One Grid
     *   Open_XB1 exclusion rate [GR] SEQ25310 */
    unsigned char excludeActivateRatio_Xboxone_Grid;

    /* レガシー_XB1除外割合
     *   レガシー_XB1除外割合【GR】SEQ25310
     * Exclude Activate Ratio - Xbox One Legacy
     *   Legacy_XB1 exclusion rate [GR] SEQ25310 */
    unsigned char excludeActivateRatio_Xboxone_Legacy;

    /* オープン_PS4除外割合
     *   オープン_PS4除外割合【GR】SEQ25310
     * Exclude Activate Ratio - PS4 Grid
     *   Open_PS4 exclusion rate [GR] SEQ25310 */
    unsigned char excludeActivateRatio_PS4_Grid;

    /* レガシー_PS4除外割合
     *   レガシー_PS4除外割合【GR】SEQ25310
     * Exclude Activate Ratio - PS4 Legacy
     *   Legacy_PS4 exclusion rate [GR] SEQ25310 */
    unsigned char excludeActivateRatio_PS4_Legacy;

    unsigned char unknown_0x120;

    unsigned char unknown_0x121;

    unsigned char unknown_0x122;

    unsigned char unknown_0x123;

    unsigned char unknown_0x124;

    unsigned char unknown_0x125;

    /* リザーブ0
     *   リザーブ0 */
    char Reserve_0[26];
} er_asset_geometory_param_t;
