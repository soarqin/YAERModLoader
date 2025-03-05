#pragma once

typedef struct er_object_param_s {
    /* HP
     *   破壊までの耐久力(-1:破壊不可)
     * HP
     *   Durability until destruction (-1 Indestructible)
     * Default Value  = -1 */
    short hp;

    /* 防御力
     *   この値以下の攻撃力はダメージなし
     * Defence
     *   Attack power below this value is no damage */
    unsigned short defense;

    /* 外部参照テクスチャID
     *   mAA/mAA_????.tpf(-1:なし)(AA:エリア番号)
     * External Texture ID
     *   mAA / mAA_ ????. Tpf (-1 None) (AA Area number)
     * Default Value  = -1 */
    short extRefTexId;

    /* 材質ID
     *   マテリアルID。床材質と同じ扱い。-1のときは今までと同じ挙動
     * Material ID
     *   Material ID. Treated the same as the floor material. When -1, the same behavior as before
     * Default Value  = -1 */
    short materialId;

    /* アニメ破壊ID最大値
     *   アニメ破壊IDが0番から何番までか
     * Destruction Animation ID
     *   What is the animation destruction ID from 0 to what? */
    unsigned char animBreakIdMax;

    /* カメラが当たるか
     *   カメラが当たるか(0:当たらない, 1:当たる)
     * Is Camera Hit
     *   Does the camera hit (0 not hit, 1 hit) */
    unsigned char isCamHit:1;

    /* プレイヤ衝突で壊れるか
     *   プレイヤが接触したときに壊れ(0:ない, 1:る)
     * Is Broken by Player Collision
     *   Broken when the player touches (0 no, 1) */
    unsigned char isBreakByPlayerCollide:1;

    /* アニメ破壊か
     *   アニメ破壊か(0:物理破壊, 1:アニメ破壊)
     * Is Animated Destruction
     *   Is it animation destruction (0 physical destruction, 1 animation destruction) */
    unsigned char isAnimBreak:1;

    /* 貫通弾丸が当たるか
     *   貫通弾丸が当たるか(0:当たらない, 1:当たる)
     * Is Hit by Penetrating Bullets
     *   Will the penetrating bullet hit (0 not hit, 1 hit) */
    unsigned char isPenetrationBulletHit:1;

    /* キャラが当たるか
     *   キャラが当たるか(0:当たらない, 1:当たる)
     * Is Character Hit
     *   Does the character win (0 not hit, 1 hit)
     * Default Value  = 1 */
    unsigned char isChrHit:1;

    /* 攻撃を弾くか
     *   攻撃を弾くか(0:弾かない, 1:弾く)
     * Is Attack Backlash
     *   Do you play the attack (0 do not play, 1 play)
     * Default Value  = 1 */
    unsigned char isAttackBacklash:1;

    /* 初期出現用破壊禁止
     *   プレイヤの初期出現で壊れ(0:る, 1:ない)
     * Is Disable Destruction on First Appearance
     *   Broken at the initial appearance of the player (0 ru, 1 no) */
    unsigned char isDisableBreakForFirstAppear:1;

    /* ハシゴか
     *   ハシゴか(0:ちがう, 1:そう)
     * Is Ladder
     *   Is it a ladder (0 different, 1 yes) */
    unsigned char isLadder:1;

    /* ポリ劇中アニメを停止するか
     *   ポリ劇中アニメを停止するか(0:しない, 1:する)
     * Is Animation Paused in Cutscene
     *   Do you want to stop the animation during the poly play (0 not, 1 do) */
    unsigned char isAnimPauseOnRemoPlay:1;

    /* ダメージが当たらないか
     *   ダメージが当たらない(0:当たる, 1:当たらない)
     * Is Damage No Hit
     *   No damage (0 hit, 1 not hit) */
    unsigned char isDamageNoHit:1;

    /* 移動オブジェか
     *   移動オブジェか(0:ちがう, 1:そう)
     * Is Moving Object
     *   Is it a moving object (0 different, 1 yes) */
    unsigned char isMoveObj:1;

    /* 吊り橋オブジェクトか
     *   吊り橋オブジェクトか(0:ちがう, 1:そう)
     * Is Rope Bridge
     *   Suspension bridge object (0 different, 1 yes) */
    unsigned char isRopeBridge:1;

    /* ダメージによって剛体が吹き飛ぶか
     *   ダメージによって剛体が吹き飛ぶか(0:吹き飛ばない, 1:吹き飛ぶ)
     * Is Rigid Body affected by Damage Blow
     *   Does the damage blow the rigid body (0 do not blow, 1 blow) */
    unsigned char isAddRigidImpulse_ByDamage:1;

    /* キャラが乗ったら壊れるか
     *   キャラが乗ったら壊れるか(0:壊れるない 1:壊れる)
     * Is Destroyed by Riding Character
     *   Will it break if the character gets on (0 it won't break 1 it will break) */
    unsigned char isBreak_ByChrRide:1;

    /* 燃焼するか
     *   燃焼するか(0:しない, 1:する)
     * Is Flammable
     *   Will it burn (0 not, 1) */
    unsigned char isBurn:1;

    /* 敵キャラ衝突で壊れるか
     *   敵キャラが接触したときに壊れ(0:ない, 1:る)
     * Is Destroyed by Enemy Collision
     *   Broken when an enemy character touches (0 No, 1 Ru) */
    unsigned char isBreakByEnemyCollide:1;

    /* デフォルトLODパラムID
     *   デフォルトLODパラムID(-1：なし)
     * Default LOD Param ID
     *   Default LOD Param ID (-1 None)
     * Default Value  = -1 */
    char defaultLodParamId;

    /* 破壊時SFXID
     *   オブジェ破壊時のSFXID(-1:デフォルト(810030))
     * Destruction - SFX ID
     *   SFXID when destroying an object (-1 default (810030))
     * Default Value  = -1 */
    int breakSfxId;

    /* 破壊時SFXダミポリID
     *   オブジェ破壊時SFXの発生位置ダミポリID(-1：配置位置）
     * Destruction - Dummy Poly ID
     *   SFX generation position when the object is destroyed Damipoly ID (-1 placement position)
     * Default Value  = -1 */
    int breakSfxCpId;

    /* 破壊時 弾発生 行動パラメータID
     *   破壊時[弾]の行動パラメータ(-1:発生しない)
     * Destruction - Bullet Behavior ID
     *   Action parameter of [bullet] at the time of destruction (-1 does not occur)
     * Default Value  = -1 */
    int breakBulletBehaviorId;

    /* 破壊時 弾発生 ダミポリID
     *   破壊時[弾]の発生位置ダミポリID(-1:配置位置)
     * Destruction - Bullet Dummy Poly ID
     *   Location of [bullet] at the time of destruction Damipoli ID (-1 placement position)
     * Default Value  = -1 */
    int breakBulletCpId;

    /* 落下破壊高さ(m)
     *   落下時にオブジェクトが壊れる高さ（0：落下では壊れない)
     * Fall Destruction Height
     *   Height at which the object breaks when dropped (0 does not break when dropped) */
    unsigned char breakFallHeight;

    /* 風影響タイプ(破壊前)
     *   風影響タイプ(破壊前)
     * Wind Effect Type - Pre-Destruction
     *   Wind effect type (before destruction) */
    unsigned char windEffectType_0;

    /* 風影響タイプ(破壊後)
     *   風影響タイプ(破壊後)
     * Wind Effect Type - Post-Destruction
     *   Wind effect type (after destruction) */
    unsigned char windEffectType_1;

    /* カメラ回避設定
     *   オブジェクトがカメラ・プレイヤー間を遮蔽した場合の対処方法
     * Camera Avoidance Type
     *   What to do if an object blocks between the camera and player
     * Default Value  = 1 */
    unsigned char camAvoidType;

    /* 風係数(破壊前)
     *   風係数(破壊前)
     * Wind Coefficient - Pre-Destruction
     *   Wind coefficient (before destruction)
     * Default Value  = 0.5 */
    float windEffectRate_0;

    /* 風係数(破壊後)
     *   風係数(破壊後)
     * Wind Coefficient - Post-Destruction
     *   Wind coefficient (after destruction)
     * Default Value  = 0.5 */
    float windEffectRate_1;

    /* 破壊後強制停止時間
     *   破壊されてから剛体を強制的に停止するまでの時間（0で強制停止しない）
     * Destruction Stop time
     *   Time from destruction to forced stop of rigid body (do not force stop at 0) */
    float breakStopTime;

    /* 燃焼時間(秒)
     *   燃焼時間(秒)(0で燃え続ける)
     * Burn Time
     *   Burning time (seconds) (continues to burn at 0) */
    float burnTime;

    /* 燃焼 破壊判定進行度
     *   破壊状態に切り替わる燃焼度の閾値
     * Burn Destruction Rate
     *   Burnup threshold for switching to the ruptured state
     * Default Value  = 0.5 */
    float burnBraekRate;

    /* 燃焼 SFXID：0
     *   燃焼時のSFXID：0 (-1：SFXなし)
     * Burn - SFX ID [0]
     *   SFX ID at the time of combustion 0 (-1 No SFX)
     * Default Value  = -1 */
    int burnSfxId;

    /* 燃焼 SFXID：1
     *   燃焼時のSFXID：1 (-1：SFXなし)
     * Burn - SFX ID [1]
     *   SFX ID at the time of combustion 1 (-1 No SFX)
     * Default Value  = -1 */
    int burnSfxId_1;

    /* 燃焼 SFXID：2
     *   燃焼時のSFXID：2 (-1：SFXなし)
     * Burn - SFX ID [2]
     *   SFX ID at the time of combustion 2 (-1 No SFX)
     * Default Value  = -1 */
    int burnSfxId_2;

    /* 燃焼 SFXID：3
     *   燃焼時のSFXID：3 (-1：SFXなし)
     * Burn - SFX ID [3]
     *   SFX ID at the time of combustion 3 (-1 No SFX)
     * Default Value  = -1 */
    int burnSfxId_3;

    /* 燃焼 弾発生 行動パラメータ：0
     *   燃焼時の弾発生行動パラメータ：0(-1:発生しない)
     * Burn - Bullet Behavior ID [0]
     *   Bullet generation behavior parameter at the time of burning 0 (-1 does not occur)
     * Default Value  = -1 */
    int burnBulletBehaviorId;

    /* 燃焼 弾発生 行動パラメータ：1
     *   燃焼時の弾発生行動パラメータ：1(-1:発生しない)
     * Burn - Bullet Behavior ID [1]
     *   Bullet generation behavior parameter at the time of burning 1 (-1 does not occur)
     * Default Value  = -1 */
    int burnBulletBehaviorId_1;

    /* 燃焼 弾発生 行動パラメータ：2
     *   燃焼時の弾発生行動パラメータ：2(-1:発生しない)
     * Burn - Bullet Behavior ID [2]
     *   Bullet generation behavior parameter at the time of burning 2 (-1 does not occur)
     * Default Value  = -1 */
    int burnBulletBehaviorId_2;

    /* 燃焼 弾発生 行動パラメータ：3
     *   燃焼時の弾発生行動パラメータ：3(-1:発生しない)
     * Burn - Bullet Behavior ID [3]
     *   Bullet generation behavior parameter at the time of burning 3 (-1 does not occur)
     * Default Value  = -1 */
    int burnBulletBehaviorId_3;

    /* 燃焼 弾発生間隔(フレーム)
     *   延焼用の弾を発生する間隔(フレーム)
     * Burn - Bullet Interval
     *   Interval (frame) to generate bullets for spreading fire
     * Default Value  = 30 */
    unsigned short burnBulletInterval;

    /* ナビメッシュフラグ
     *   オブジェから設定されるナビメッシュフラグ
     * Navimesh Flag
     *   Navigation mesh flag set from the object */
    unsigned char navimeshFlag;

    /* 衝突判定タイプ
     *   衝突判定タイプ
     * Collision Detection Type
     *   Collision detection type */
    unsigned char collisionType;

    /* 燃焼 弾発生遅延時間(秒)
     *   延焼用の弾発生を遅らせる時間(秒)
     * Burn - Bullet Generation Delay Time
     *   Time to delay the generation of bullets for fire spread (seconds) */
    float burnBulletDelayTime;

    /* 燃焼 SFX発生遅延 開始時間(秒)：0
     *   燃焼時のSFX発生遅延時間 開始～終了時間の間でランダムに決まる
     * Burn - Bullet Generation Delay Time [0] (Minimum)
     *   SFX generation delay time during combustion Randomly determined between start and end times */
    float burnSfxDelayTimeMin;

    /* 燃焼 SFX発生遅延 開始時間(秒)：1
     *   燃焼時のSFX発生遅延時間 開始～終了時間の間でランダムに決まる
     * Burn - Bullet Generation Delay Time [1] (Minimum)
     *   SFX generation delay time during combustion Randomly determined between start and end times */
    float burnSfxDelayTimeMin_1;

    /* 燃焼 SFX発生遅延 開始時間(秒)：2
     *   燃焼時のSFX発生遅延時間 開始～終了時間の間でランダムに決まる
     * Burn - Bullet Generation Delay Time [2] (Minimum)
     *   SFX generation delay time during combustion Randomly determined between start and end times */
    float burnSfxDelayTimeMin_2;

    /* 燃焼 SFX発生遅延 開始時間(秒)：3
     *   燃焼時のSFX発生遅延時間 開始～終了時間の間でランダムに決まる
     * Burn - Bullet Generation Delay Time [3] (Minimum)
     *   SFX generation delay time during combustion Randomly determined between start and end times */
    float burnSfxDelayTimeMin_3;

    /* 燃焼 SFX発生遅延 終了時間(秒)：0
     *   燃焼時のSFX発生遅延時間 開始～終了時間の間でランダムに決まる
     * Burn - Bullet Generation Delay Time [0] (Maximum)
     *   SFX generation delay time during combustion Randomly determined between start and end times */
    float burnSfxDelayTimeMax;

    /* 燃焼 SFX発生遅延 終了時間(秒)：1
     *   燃焼時のSFX発生遅延時間 開始～終了時間の間でランダムに決まる
     * Burn - Bullet Generation Delay Time [1] (Maximum)
     *   SFX generation delay time during combustion Randomly determined between start and end times */
    float burnSfxDelayTimeMax_1;

    /* 燃焼 SFX発生遅延 終了時間(秒)：2
     *   燃焼時のSFX発生遅延時間 開始～終了時間の間でランダムに決まる
     * Burn - Bullet Generation Delay Time [2] (Maximum)
     *   SFX generation delay time during combustion Randomly determined between start and end times */
    float burnSfxDelayTimeMax_2;

    /* 燃焼 SFX発生遅延 終了時間(秒)：3
     *   燃焼時のSFX発生遅延時間 開始～終了時間の間でランダムに決まる
     * Burn - Bullet Generation Delay Time [3] (Maximum)
     *   SFX generation delay time during combustion Randomly determined between start and end times */
    float burnSfxDelayTimeMax_3;

    /* 破壊時発生AI音ID
     *   破壊時に発生させるAI音ID
     * Destruction AI Sound ID
     *   AI sound ID generated at the time of destruction */
    int BreakAiSoundID;

    /* 破片非表示 待機時間(秒)
     *   破片のマテリアルID(-1：非表示処理を行なわない)
     * Hidden Debris - Wait Time
     *   Material ID of debris (-1 Do not hide) */
    float FragmentInvisibleWaitTime;

    /* 破片非表示 時間(秒)
     *   破片を非表示にさせる時間(秒)
     * Hidden Debris - Invisibility Time
     *   Time to hide debris (seconds) */
    float FragmentInvisibleTime;

    /* パディング
     *   破片のマテリアルID(-1：非表示処理を行なわない)
     * Default Value  = -1 */
    char pad_3[16];

    /* 剛体 衝突点距離係数 [柔らかい]
     *   剛体ソフトコンタクト設定 衝突点距離係数 [柔らかい]
     * Rigid Body Collision - Soft
     *   Rigid body soft contact setting Collision point distance coefficient [soft] */
    float RigidPenetrationScale_Soft;

    /* 剛体 衝突点距離係数 [通常]
     *   剛体ソフトコンタクト設定 衝突点距離係数 [通常]
     * Rigid Body Collision - Normal
     *   Rigid soft contact setting Collision point distance coefficient [Normal] */
    float RigidPenetrationScale_Normal;

    /* 剛体 衝突点距離係数 [固い]
     *   剛体ソフトコンタクト設定 衝突点距離係数 [固い]
     * Rigid Body Collision - Hard
     *   Rigid soft contact setting Collision point distance coefficient [hard] */
    float RigidPenetrationScale_Hard;

    /* 地形接触時のSFXID
     *   地形接触時のSFXID(-1:地形のマテリアルによりオフセット)
     * Land Touch - SFX ID
     *   SFX ID at terrain contact (-1 offset by terrain material)
     * Default Value  = -1 */
    int LandTouchSfxId;

    /* ダメージを遮蔽するか
     *   ダメージを受けたときに、そのダメージを反対側に通さないかどうか　(0:通す, 1:通さない)
     * Is Damage blocked after Passing Through
     *   Whether to pass the damage to the other side when receiving damage (0 pass, 1 do not pass) */
    unsigned char isDamageCover:1;

    /* パディング */
    char pad_4[1];

    /* ペイントデカールターゲットサイズ
     *   ペイントデカールターゲットサイズ(0～4096 ２のべき乗のみ許可)
     * Paint Decal Size
     *   Paint decal target size (only powers of 0 to 4096 2 allowed)
     * Default Value  = 256 */
    unsigned short paintDecalTargetTextureSize;

    /* 動的生成Objの寿命(秒)
     *   動的生成Objが生成後に消滅するまでの時間 (0:消滅しない)
     * Dynamic Object Duration
     *   Time until dynamically generated Obj disappears after generation (0 does not disappear) */
    float lifeTime_forDC;

    /* クロス更新距離(m)
     *   havokClothの更新を行なうカメラからの距離(0:必ず更新する)
     * Cloth Update Distance from Camera
     *   Distance from the camera to update havokCloth (0 always update) */
    float clothUpdateDist;

    /* プレイヤー接触時SE ID
     *   自分が操作するローカルプレイヤーが触れた際に再生するSEのID(-1:再生しない)
     * Player Touch - SE ID
     *   SE ID to play when touched by a local player operated by you (-1 Do not play)
     * Default Value  = -1 */
    int contactSeId;

    /* 破壊後着地時SFX識別子
     *   破壊された後、最初に着地した際に再生するオブジェ材質依存SFXの識別子(-1:発生しない)
     * Landing Destruction - SFX ID
     *   Object material-dependent SFX identifier that regenerates when first landing after being destroyed (-1 does not occur)
     * Default Value  = -1 */
    int breakLandingSfxId;

    /* ウェイポイントダミポリID_0
     *   ウェイポイントダミポリID_0(-1:なし)
     * Waypoint Dummy Poly ID
     *   Waypoint Damipoli ID_0 (-1 None)
     * Default Value  = -1 */
    int waypointDummyPolyId_0;

    /* ウェイポイントパラメータID_0
     *   ウェイポイントパラメータID_0(-1:なし)
     * Waypoint Param ID
     *   Waypoint parameter ID_0 (-1 none)
     * Default Value  = -1 */
    int waypointParamId_0;

    /* サウンドのバンクID
     *   サウンドのバンクID(-1:バンクなし, それ以外:指定したIDのバンク)
     * Sound Bank ID
     *   Sound bank ID (-1 no bank, other bank with specified ID)
     * Default Value  = -1 */
    int soundBankId;

    /* 描画パラメータ参照ID
     *   描画パラメータの参照ID
     * Reference Draw Param ID
     *   Reference ID of drawing parameter
     * Default Value  = -1 */
    int refDrawParamId;

    /* 自動生成出現高さオフセット[m]
     *   マップ自動生成OBJの出現高さオフセット[m]、レイキャストが当たったところから度ぐらい浮かすか
     * Automatica Generation - Appearance Height Offset
     *   Map automatic generation OBJ appearance height offset [m], does it float from where the ray cast hits?
     * Default Value  = 0.1 */
    float autoCreateDynamicOffsetHeight;

    /* リザーブ
     *   リザーブ
     * Default Value  = -1 */
    int reserved0;

    /* 破壊音SEID
     *   破壊音SEID(9桁) -1：objIdから生成
     * Destruction - SE ID
     *   Destruction sound SEID (9 digits) -1 Generated from objId
     * Default Value  = -1 */
    int soundBreakSEId;

    /* パディング */
    char pad_5[40];
} er_object_param_t;
