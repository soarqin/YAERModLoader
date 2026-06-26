#pragma once

/* Governs motion, hitbox and appearance of projetiles. Can reference AtkParam for damage. */
typedef struct er_bullet_param_s {
    /* 攻撃ID
     *   攻撃パラメータのＩＤをそれぞれ登録する.→攻撃タイプ／攻撃材質／物理攻撃力／魔法攻撃力／スタミナ攻撃力／ノックバック距離.
     * AtkParam ID
     *   Register each attack parameter ID.  Attack type / Attack material / Physical attack power / Magic attack power / Stamina attack power / Knockback distance.
     * Default Value  = -1 */
    int atkId_Bullet;

    /* SFXID【弾】
     *   【弾】用SFX IDを入れる。-1は発生しない。
     * Projectile SFX ID
     *   Enter the SFX ID for [Bullet]. -1 does not occur.
     * Default Value  = -1 */
    int sfxId_Bullet;

    /* SFXID【着弾】
     *   【着弾】SFXIDを入れる。-1は発生しない。
     * Impact SFX ID
     *   [Impact] Enter the SFX ID. -1 does not occur.
     * Default Value  = -1 */
    int sfxId_Hit;

    /* SFXID【はじき時】
     *   【はじき時】SFXIDを入れる。-1は発生しない。
     * Repel SFX ID
     *   [At the time of repelling] Enter the SFX ID. -1 does not occur.
     * Default Value  = -1 */
    int sfxId_Flick;

    /* 寿命[s]
     *   飛び道具が存在し続けられる時間（-1なら無限）.
     * Duration
     *   Time for missiles to continue to exist (-1 is infinite).
     * Default Value  = -1 */
    float life;

    /* 射程距離[m]
     *   減衰が開始される距離（実際の飛距離ではない）.
     * Attenuation Range
     *   Distance at which attenuation begins (not actual flight distance). */
    float dist;

    /* 発射間隔[s]
     *   飛び道具を何秒間隔で発射するかを指定.
     * Shoot Interval
     *   Specify how many seconds the missile will be fired. */
    float shootInterval;

    /* 射程距離内重力[m/s^2]
     *   射程距離内での下向きにかかる重力.
     * Gravity: In Range
     *   Downward gravity within range. */
    float gravityInRange;

    /* 射程距離外重力[m/s^2]
     *   減衰がはじまったときの下向きにかかる重力（ポトンと落ちる感じを表現.
     * Gravity: Out of Range
     *   Gravity applied downward when damping begins (expresses the feeling of falling down. */
    float gravityOutRange;

    /* 誘導停止距離[m]
     *   誘導を停止するターゲットとの距離。誘導弾で当たり過ぎないようにするパラメータ。
     * Homing Stop Range
     *   The distance to the target to stop the guidance. A parameter that prevents you from hitting too much with a guided bullet. */
    float hormingStopRange;

    /* 初速[m/s]
     *   ＳＦＸの初速度.
     * Initial Velocity
     *   Initial speed of SFX. */
    float initVellocity;

    /* 射程距離内加速度[m/s^2]
     *   ＳＦＸの射程内の加速度.
     * Acceleration: In Range
     *   Acceleration within SFX range. */
    float accelInRange;

    /* 射程距離外加速度[m/s^2]
     *   ＳＦＸが射程距離外に出たときの加速度.
     * Acceleration: Out of Range
     *   Acceleration when SFX goes out of range. */
    float accelOutRange;

    /* 最高速度[m/s]
     *   最高速度.
     * Max Velocity
     *   maximum speed. */
    float maxVellocity;

    /* 最低速度[m/s]
     *   最低保証速度.
     * Min Velocity
     *   Minimum guaranteed speed. */
    float minVellocity;

    /* 加速開始時間[s]
     *   この時間までは、加速しない（ロケット弾みたいな魔法を撃つことができるようにしておく）.
     * Acceleration Duration
     *   Until this time, do not accelerate (make sure you can shoot magic like rockets). */
    float accelTime;

    /* 誘導開始距離[m]
     *   何ｍ進んだ地点から誘導を開始するか.
     * Homing Start Distance
     *   How many meters should the guidance start? */
    float homingBeginDist;

    /* 初期弾半径[m]
     *   当たり球の半径を設定する.
     * Initial Hit Radius
     *   Set the radius of the hit ball.
     * Default Value  = -1 */
    float hitRadius;

    /* 最大弾半径[m]
     *   あたり球の最大半径（－1の場合、初期半径と同じにする／デフォルト）
     * Final Hit Radius
     *   Maximum radius of the hit sphere (If -1, make it the same as the initial radius / default)
     * Default Value  = -1 */
    float hitRadiusMax;

    /* 範囲拡散時間[s]
     *   範囲半径が細大にまで広がる時間.
     * Radius Spread Time
     *   The time when the radius of the range expands to a small extent. */
    float spreadTime;

    /* 発動遅延[s]
     *   着弾後、爆発までの時間（０の場合はすぐに爆発）.
     * Expansion Delay
     *   Time from landing to expand (if 0, it expands immediately). */
    float expDelay;

    /* 誘導ずらし量[m]
     *   ０だと正確。射撃時にXYZ各成分を、この量だけずらして狙うようにする。
     * Homing Offset Range
     *   It is accurate if it is 0. At the time of shooting, each component of XYZ should be aimed by shifting this amount. */
    float hormingOffsetRange;

    /* ダメージヒット履歴の生存時間[s]
     *   ダメージヒット履歴の生存時間[sec](<=0.0f：無期限)
     * Damage Hit Duration
     *   Damage hit history survival time [sec] ( 0.0f: indefinite) */
    float dmgHitRecordLifeTime;

    /* 外力[m/s^2]
     *   射撃時の方向にかかる外力.(Y軸は抜いている)
     * External Force in Bullet Direction
     *   External force applied in the direction of shooting. (Y-axis is removed) */
    float externalForce;

    /* 射撃した人にかける特殊効果
     *   射撃した人にかける特殊効果
     * Shooter SpEffect ID
     *   Special effects on the person who shot
     * Default Value  = -1 */
    int spEffectIDForShooter;

    /* ファンネルNPC思考ID
     *   ファンネルがターゲットの検索使用するパラメータ
     * Bullet AI
     *   Parameters used by the funnel to search for the target */
    int autoSearchNPCThinkID;

    /* 発生弾丸ID
     *   弾丸パラメータから、新しく弾丸パラメータを発生させるときにＩＤを指定する
     * Hit Bullet ID
     *   Specify the ID when generating a new bullet parameter from the bullet parameter
     * Default Value  = -1 */
    int HitBulletID;

    /* 特殊効果ID0
     *   特殊効果パラメータのＩＤをそれぞれ登録する.→特殊効果全般.
     * Target SpEffect ID [0]
     *   Register each special effect parameter ID.  General special effects.
     * Default Value  = -1 */
    int spEffectId0;

    /* 特殊効果ID1
     *   特殊効果パラメータのＩＤをそれぞれ登録する.→特殊効果全般.
     * Target SpEffect ID [1]
     *   Register each special effect parameter ID.  General special effects.
     * Default Value  = -1 */
    int spEffectId1;

    /* 特殊効果ID2
     *   特殊効果パラメータのＩＤをそれぞれ登録する.→特殊効果全般.
     * Target SpEffect ID [2]
     *   Register each special effect parameter ID.  General special effects.
     * Default Value  = -1 */
    int spEffectId2;

    /* 特殊効果ID3
     *   特殊効果パラメータのＩＤをそれぞれ登録する.→特殊効果全般.
     * Target SpEffect ID [3]
     *   Register each special effect parameter ID.  General special effects.
     * Default Value  = -1 */
    int spEffectId3;

    /* 特殊効果ID4
     *   特殊効果パラメータのＩＤをそれぞれ登録する.→特殊効果全般.
     * Target SpEffect ID [4]
     *   Register each special effect parameter ID.  General special effects.
     * Default Value  = -1 */
    int spEffectId4;

    /* 発射数
     *   一度に発射する飛び道具の数.
     * Bullet Count
     *   The number of missiles fired at one time. */
    unsigned short numShoot;

    /* 誘導性能[deg/s]
     *   1秒間に何度まで補正するか？.
     * Homing Angle
     *   How many corrections per second? .. */
    short homingAngle;

    /* 発射角度[deg]
     *   飛び道具を前方何度に向かって発射するかを指定.
     * Launch Angle
     *   Specify how many times the missile is fired forward. */
    short shootAngle;

    /* 発射角度間隔[deg]
     *   飛び道具を複数発射する場合、何度間隔で発射するかを指定.(Y軸)
     * Launch Angle Interval
     *   When firing multiple missiles, specify how often to fire them. (Y-axis) */
    short shootAngleInterval;

    /* 発射仰角間隔[deg]
     *   飛び道具を複数発射する場合、何度間隔で発射するかを指定.(X軸)
     * Launch Elevation Interval
     *   When firing multiple missiles, specify how often to fire them. (X-axis) */
    short shootAngleXInterval;

    /* 物理攻撃力減衰率[%/s]
     *   減衰距離以降、1秒間に減少する補正値.
     * Damage Falloff %: Physical
     *   Correction value that decreases in 1 second after the attenuation distance. */
    char damageDamp;

    /* 魔法攻撃力減衰率[%/s]
     *   減衰距離以降、1秒間に減少する補正値.
     * Damage Falloff %: Magic
     *   Correction value that decreases in 1 second after the attenuation distance. */
    char spelDamageDamp;

    /* 炎攻撃力減衰率[%/s]
     *   減衰距離以降、1秒間に減少する補正値.
     * Damage Falloff %: Fire
     *   Correction value that decreases in 1 second after the attenuation distance. */
    char fireDamageDamp;

    /* 電撃攻撃力減衰率[%/s]
     *   減衰距離以降、1秒間に減少する補正値.
     * Damage Falloff %: Lightning
     *   Correction value that decreases in 1 second after the attenuation distance. */
    char thunderDamageDamp;

    /* スタミナダメージ減衰率[%/s]
     *   減衰距離以降、1秒間に減少する補正値.
     * Damage Falloff %: Stamina
     *   Correction value that decreases in 1 second after the attenuation distance. */
    char staminaDamp;

    /* ノックバック減衰率[%/s]
     *   減衰距離以降、1秒間に減少する補正値.
     * Damage Falloff %: Knockback
     *   Correction value that decreases in 1 second after the attenuation distance. */
    char knockbackDamp;

    /* 発射仰角[deg]
     *   水平方向からの追加仰角。
     * Launch Elevation Angle
     *   Additional elevation angle from the horizontal. */
    char shootAngleXZ;

    /* ロック方向制限角度
     *   ロック方向を向かせるときの制限角度
     * Lock Direction Limit Angle
     *   Limit angle when facing the lock direction */
    unsigned char lockShootLimitAng;

    /* pad */
    char pad2[1];

    /* 前回の移動方向加算率[%]
     *   滑る弾が壁にヒット時に前回の移動方向を今の方向へ加算する比率
     * Previous Velocity Direction Rate
     *   Ratio to add the previous movement direction to the current direction when the sliding bullet hits the wall */
    unsigned char prevVelocityDirRate;

    /* 物理属性
     *   弾丸に設定する物理属性を設定
     * Attack Attribute
     *   Set the physical attributes to set for the bullet
     * Default Value  = 254 */
    unsigned char atkAttribute;

    /* 特殊属性
     *   弾丸に設定する特殊属性を設定
     * Special Attribute
     *   Set special attributes to set for bullets
     * Default Value  = 254 */
    unsigned char spAttribute;

    /* 攻撃属性[SFX/SE]
     *   攻撃属性が何かを指定する
     * Material Attack Type
     *   Specify what the attack attribute is
     * Default Value  = 254 */
    unsigned char Material_AttackType;

    /* 攻撃材質[SFX/SE]
     *   攻撃時のSFX/ＳＥに使用
     * Material Attack Material
     *   Used for SFX / SE during attack
     * Default Value  = 254 */
    unsigned char Material_AttackMaterial;

    /* キャラを貫通？
     *   ONであればキャラに当たったときに着弾せず貫通する
     * Is Penetrate Character
     *   If it is ON, it will penetrate without landing when it hits the character. */
    unsigned char isPenetrateChr:1;

    /* オブジェを貫通？
     *   ONであれば動的/部分破壊アセットに当たったときに着弾せず貫通する
     * Is Penetrate Object
     *   If it is ON, it will penetrate without landing when hitting a dynamic / partial destruction asset. */
    unsigned char isPenetrateObj:1;

    /* Can be Remotely Detonated
     *   Bullets with Attach Type 6 will cause this bullet to be detonated if this bullet is within their hit radius. */
    unsigned char mayRemoteDetonate:1;

    char pad:5;

    /* 発生条件
     *   着弾・寿命消滅時に弾を発生させるか判定する条件を指定
     * Launch Condition Type
     *   Specify the condition to judge whether to generate a bullet when it lands or the life is extinguished */
    unsigned char launchConditionType;

    /* 追従タイプ
     *   追従タイプ。「追従しない」がデフォルト。
     * Follow Type
     *   Follow-up type. Do not follow is the default. */
    unsigned char FollowType:3;

    /* 発生源タイプ
     *   発生源タイプ。ダミポリからが通常。（メテオを判定するために導入）
     * Emitter Source Type
     *   Source type. Usually from Damipoli. (Introduced to judge meteo) */
    unsigned char EmittePosType:3;

    /* 刺さったままになるか
     *   矢などの弾丸が、キャラクターに刺さったままになるかどうかを設定する
     * Is Persistent Attack SFX
     *   Set whether bullets such as arrows will remain stuck in the character */
    unsigned char isAttackSFX:1;

    /* あたり続けるか？
     *   あたり続けるか？
     * Is Continuous Hit
     *   Do you keep hitting? */
    unsigned char isEndlessHit:1;

    /* マップを貫通？
     *   ONであればヒット/静的アセットに当たったときに着弾せず貫通する
     * Is Penetrate Map
     *   If it is ON, it will penetrate without landing when hitting a hit / static asset. */
    unsigned char isPenetrateMap:1;

    /* 敵味方共にあたる？
     *   敵味方共にあたるか？（徘徊ゴーストにはあたらない）
     * Is Hit Both Teams
     *   Are you an enemy or an ally? (Not a wandering ghost) */
    unsigned char isHitBothTeam:1;

    /* ヒットリストを共有するか？
     *   ヒットリストを共有するかを指定
     * Is Use Shared Hit List
     *   Specify whether to share the hit list */
    unsigned char isUseSharedHitList:1;

    /* 複数のダミポリを使うか？
     *   弾配置時に同一ダミポリIDを複数使うか？
     * Use Multiple Dummy Polys for Placement
     *   Do you use the same Damipoly ID more than once when placing bullets? */
    unsigned char isUseMultiDmyPolyIfPlace:1;

    /* 他弾強制消去Aに当たるか
     *   他弾強制消去Aに当たるか
     * Force Erase Bullet A if Hit by Other Bullet
     *   Does it hit other bullets forced erasure A? */
    unsigned char isHitOtherBulletForceEraseA:1;

    /* 他弾強制消去Bに当たるか
     *   他弾強制消去Bに当たるか
     * Force Erase Bullet B if Hit by Other Bullet
     *   Does it hit the other bullet forced erasure B? */
    unsigned char isHitOtherBulletForceEraseB:1;

    /* フォース魔法に当たるか
     *   フォース魔法に当たるか
     * Is Bullet deflected by Magic
     *   Do you hit the force magic? */
    unsigned char isHitForceMagic:1;

    /* 水面衝突時のエフェクト無視するか
     *   水面に当たった場合はエフェクト無視するか
     * Is SFX ignored on Water Hit
     *   Should I ignore the effect if it hits the surface of the water? */
    unsigned char isIgnoreSfxIfHitWater:1;

    /* 水面衝突時の状態遷移を無視するか
     *   水に当たっても状態遷移を無視するか
     * Is Move State Ignored on Water Hit
     *   Whether to ignore the state transition even if it hits water */
    unsigned char isIgnoreMoveStateIfHitWater:1;

    /* 闇フォース魔法に当たるか
     *   闇フォース魔法に当たるか
     * Is Bullet deflected by Bullet Deflection
     *   Do you hit the dark force magic? */
    unsigned char isHitDarkForceMagic:1;

    /* ダメージ計算サイド
     *   ダメージ計算サイド。　マルチプレイ時に、ダメージの計算を、与えた側 or 受けた側を切り替えるためのもの。
     * Damage Calculation Side
     *   Damage calculation side. During multiplayer, the damage calculation is for switching between the giving side and the receiving side. */
    unsigned char dmgCalcSide:2;

    /* 弾丸自動捕捉許可
     *   非ロックオン時に自動追従するか
     * Is Auto Homing Enabled
     *   Whether to automatically follow when not locked on */
    unsigned char isEnableAutoHoming:1;

    /* 同期弾丸の場合、ダミポリ位置での再計算を行うか
     *   同期生成された弾丸の場合、弾丸生成時にダミポリ位置による姿勢の再計算を行わず、同期時のエミッタ姿勢を使用する。
     * Is Emitter Source Synced with Bullet
     *   In the case of a synchronously generated bullet, the emitter attitude at the time of synchronization is used without recalculating the attitude due to the Damipoli position when the bullet is generated. */
    unsigned char isSyncBulletCulcDumypolyPos:1;

    /* 弾丸の基準方向をオーナーに上書きするか？
     *   子弾丸のみ有効。ONなら基準方向をオーナーにする。
     * Is Direction Inherited by Child Bullet
     *   Only valid for sub-bullets. If it is ON, the reference direction is the owner. */
    unsigned char isOwnerOverrideInitAngle:1;

    /* 子弾にSFXを引き継ぐか
     *   親弾のSFXを引き継ぐ。子弾に設定されたSFXIDは無視する 
     * Is SFX Inherited by Child Bullet
     *   Take over the SFX of the parent bullet. Ignore the SFX ID set for the sub bullet */
    unsigned char isInheritSfxToChild:1;

    /* 闇攻撃力減衰率[%/s]
     *   減衰距離以降、1秒間に減少する補正値.
     * Damage Falloff %: Holy
     *   Correction value that decreases in 1 second after the attenuation distance. */
    char darkDamageDamp;

    /* 着弾時の弾丸SFX消滅タイプ
     *   着弾or弾き時の弾丸SFX消滅タイプ
     * Bullet SFX Delete Type - By Hit
     *   Bullet SFX extinction type when landing or playing */
    char bulletSfxDeleteType_byHit;

    /* 寿命時の弾丸SFX消滅タイプ
     *   寿命時の弾丸SFX消滅タイプ
     * Bullet SFX Delete Type - By Expiration
     *   Bullet SFX extinction type at the end of life */
    char bulletSfxDeleteType_byLifeDead;

    /* 目標上下オフセット[m]
     *   着弾位置の上下オフセット。発射時とホーミング中のターゲット位置を上下にずらす。（-n～n）
     * Target Vertical Offset
     *   Vertical offset of landing position. Shift the target position up and down at the time of launch and during homing. (-N ~ n) */
    float targetYOffsetRange;

    /* 発射角度乱数[deg]
     *   発射角度乱数の上限（0～360）
     * Random Launch Angle - Max
     *   Upper limit of random number of firing angle (0 to 360) */
    float shootAngleYMaxRandom;

    /* 発射仰角乱数[deg]
     *   発射仰角乱数の上限（0～360）
     * Random Elevation Angle - Max
     *   Upper limit of firing elevation random number (0 to 360) */
    float shootAngleXMaxRandom;

    /* 間隔指定発生弾丸ID
     *   一定間隔で弾丸を作る時に使う、弾丸のID
     * Bullet Emitter: Bullet ID
     *   Bullet ID used when making bullets at regular intervals
     * Default Value  = -1 */
    int intervalCreateBulletId;

    /* 発生間隔：最小時間[s]
     *   一定間隔で弾丸を作る間隔の最小（0～n）
     * Bullet Emitter: Minimum Shoot Interval
     *   Minimum interval for making bullets at regular intervals (0 to n) */
    float intervalCreateTimeMin;

    /* 発生間隔：最大時間[s]
     *   一定間隔で弾丸を作る間隔の最大（0～n 0なら機能無効）
     * Bullet Emitter: Maximum Shoot Interval
     *   Maximum interval for making bullets at regular intervals (function is disabled if 0 to n 0) */
    float intervalCreateTimeMax;

    /* 予測射撃の速度観測時間[s]
     *   予測射撃機能の平均速度観測時間（0～4 0なら機能無効）
     * Prediction Shoot Observe Time
     *   Average speed observation time of predicted shooting function (function is invalid if 0 to 40) */
    float predictionShootObserveTime;

    /* 間隔指定発生開始待ち時間[s]
     *   一定間隔で弾丸を作り始めるまでの待ち時間
     * Bullet Emitter: Initial Wait Time
     *   Waiting time to start making bullets at regular intervals */
    float intervalCreateWaitTime;

    /* 弾丸から発生したSFXの姿勢のタイプ
     *   弾丸から作成されたSFXまたは子弾丸の初期姿勢を設定する
     * SFX Posture Type
     *   Set the initial attitude of an SFX or sub-bullet created from a bullet */
    unsigned char sfxPostureType;

    /* 作成制限グループId
     *   0なら未使用。同一のグループIdに設定された弾丸を作成するときに上限に達していたらその弾丸を作成しない。（ネットワークで同期作成された弾は関係なく出る）
     * Create Limit Group ID
     *   If it is 0, it is unused. If the upper limit is reached when creating a bullet set in the same group Id, that bullet will not be created. (Bullets created synchronously on the network will be released regardless) */
    unsigned char createLimitGroupId;

    /* pad */
    char pad5[1];

    /* 子弾に速度を引き継ぐか
     *   子弾に差し替わるタイミングの速度を引き継ぐ。子弾に設定された速度は無視する
     * Is Speed Inherited by Child Bullet
     *   Take over the speed of the timing to replace the submunition. Ignore the speed set for the submunition */
    unsigned char isInheritSpeedToChild:1;

    /* キャラ・OBJヒット時着弾SFXを再生しない
     *   ONの時、キャラクター/オブジェクトに着弾しても弾丸パラメータの「着弾SFX」を再生しない
     * Is SFX Disabled on Chr/Object Hit
     *   When ON, the bullet parameter landing SFX does not play even if it hits a character / object. */
    unsigned char isDisableHitSfx_byChrAndObj:1;

    /* 発射位置壁めり込み判定をキャラ中心を平行に結ぶレイを飛ばして行う
     *   弾丸発射時めり込み判定に不具合があったので、それのエラーハンドリング用。SEQ23101 【自キャラ】ロックオン位置の高いキャラに密着してソウルの短矢、強いソウルの短矢を使うと弾丸の方向が反転する
     * Is Wall Checked by Center Ray
     *   There was a problem with the digging judgment when firing a bullet, so it is for error handling. SEQ23101 [Own character] If you use a soul short arrow or a strong soul short arrow in close contact with a character with a high lock-on position, the direction of the bullet will be reversed. */
    unsigned char isCheckWall_byCenterRay:1;

    /* フレア魔法に当たるか
     *   フレア魔法に当たるか
     * Is Hit Flare
     *   Do you hit flare magic? */
    unsigned char isHitFlare:1;

    /* 原始魔法アタリを使うか？
     *   原始魔法アタリを使うか？原始魔法専用アタリに当たるフィルタに変わります。
     * Is Bullet Wall Filter Used
     *   Do you use primitive magic Atari? It will change to a filter that corresponds to the Atari dedicated to primitive magic. */
    unsigned char isUseBulletWallFilter:1;

    /* pad */
    unsigned char unknown_0xc3_5:1;

    /* PCのファンネル数が理力で変動しない
     *   PCのファンネル数が理力で変動しない。発射数になる
     * Is Follow Bullet Count not scaled by INT
     *   The number of funnels on the PC does not fluctuate by force. Become the number of shots */
    unsigned char isNonDependenceMagicForFunnleNum:1;

    /* AI弾丸反応するか（攻撃力0でも）
     *   AI弾丸反応するか（攻撃力0でも）
     * Is AI Interrupted by Bullet
     *   Does it react to AI bullets (even with 0 attack power)? */
    unsigned char isAiInterruptShootNoDamageBullet:1;

    /* ランダム発生時の発生範囲(半径)[m]
     *   発生源タイプがランダムな位置に発生する設定の場合に利用される、弾丸の発生範囲。
     * Emitter Source Radius
     *   The range of bullets used when the source type is set to occur at random locations. */
    float randomCreateRadius;

    /* ファンネル追従位置_基点高さ[m]
     *   ファンネル追従位置_基点高さ[m]
     * Follow Bullet - Height Offset
     *   Funnel tracking position_base point height [m] */
    float followOffset_BaseHeight;

    /* 着弾時に発生するアセット番号
     *   着弾時に発生させるアセットの番号。-1：生成しない。アセット番号はアセットの下6桁の数値です。例： AEG999_999 = 999999
     * Asset Generated on Hit
     *   The number of the asset to be generated at the time of landing. -1: Do not generate. The asset number is the last 6 digits of the asset. Example: AEG999_999 = 999999
     * Default Value  = -1 */
    int assetNo_Hit;

    /* 寿命乱数[s]
     *   「寿命[s]」に対して、設定した時間の振れ幅を持つ乱数秒を加える
     * Duration - Random Range
     *   Add a random number of seconds with a set time fluctuation range to the lifetime [s]. */
    float lifeRandomRange;

    /* 誘導性能（X軸個別）[deg/s]
     *   誘導性能のX軸成分だけを変えます。-1で変えません
     * Homing Angle: X
     *   Only the X-axis component of the inductive performance is changed. Do not change with -1
     * Default Value  = -1 */
    short homingAngleX;

    /* 弾道計算タイプ
     *   弾道計算タイプ
     * Ballistic Calculation Type
     *   Initial shoot direction */
    unsigned char ballisticCalcType;

    /* アタッチ効果タイプ
     *   アタッチする効果タイプ
     * Attach Effect Type
     *   Effect type to attach */
    unsigned char attachEffectType;

    /* SEID1【弾】
     *   【弾】用SE ID1 を入れる。-1：生成しない　9桁。サウンドタイプはs：SFX固定。
     * Insert SE ID - Bullet [1]
     *   Insert SE ID1 for [Bullet]. -1: Not generated 9 digits. Sound type is fixed to s: SFX.
     * Default Value  = -1 */
    int seId_Bullet1;

    /* SEID2【弾】
     *   【弾】用SE ID2 を入れる。-1：生成しない　9桁。サウンドタイプはs：SFX固定。
     * Insert SE ID - Bullet [2]
     *   Insert SE ID 2 for [Bullet]. -1: Not generated 9 digits. Sound type is fixed to s: SFX.
     * Default Value  = -1 */
    int seId_Bullet2;

    /* SEID【着弾】
     *   【着弾】用SE ID1 を入れる。-1は発生しない。 9桁。サウンドタイプはs：SFX固定。
     * Insert SE ID - Hit
     *   Insert SE ID 1 for [landing]. -1 does not occur. 9 digits. Sound type is fixed to s: SFX.
     * Default Value  = -1 */
    int seId_Hit;

    /* SEID【はじき時】
     *   【はじき時】用SE ID1 を入れる。-1は発生しない。 9桁。サウンドタイプはs：SFX固定。
     * Insert SE ID - Repel
     *   [At the time of repelling] Enter SE ID1 for. -1 does not occur. 9 digits. Sound type is fixed to s: SFX.
     * Default Value  = -1 */
    int seId_Flick;

    /* 【曲射】発射仰角制限_下限[deg]
     *   【曲射】曲射計算の適用前の発射仰角を基準(0deg)とした下限[deg]。
     * Howitzer - Launch Elevation Limit - Min
     *   [Curly fire] The lower limit [deg] with the firing elevation angle as a reference (0 deg) before applying the curve fire calculation. */
    short howitzerShootAngleXMin;

    /* 【曲射】発射仰角制限_上限[deg]
     *   【曲射】曲射計算の適用前の発射仰角を基準(0deg)とした上限[deg]。
     * Howitzer - Launch Elevation Limit - Max
     *   [Sky firing] The upper limit [deg] based on the firing elevation angle (0deg) before applying the bending firing calculation. */
    short howitzerShootAngleXMax;

    /* 【曲射】最低制限速度[m/s]
     *   【曲射】曲射計算の最低制限速度[m/s]。
     * Howitzer - Initial Min Velocity
     *   [Song firing] The minimum speed limit for song firing calculation [m / s]. */
    float howitzerInitMinVelocity;

    /* 【曲射】最高制限速度[m/s]
     *   【曲射】曲射計算の最高制限速度[m/s]。
     * Howitzer - Initial Max Velocity
     *   [Song firing] Maximum speed limit for song firing calculation [m / s]. */
    float howitzerInitMaxVelocity;

    /* SFXID【強制消去時】
     *   強制消去時SFXID。-1は発生しない。
     * SFX ID - Force Erase
     *   SFX ID at the time of forced erasure. -1 does not occur.
     * Default Value  = -1 */
    int sfxId_ForceErase;

    /* 強制消去時の弾丸SFX消滅タイプ
     *   強制消去時の弾丸SFX消滅タイプ
     * Bullet SFX Delete Type - By Force Erase
     *   Bullet SFX extinction type at the time of forced erasure */
    char bulletSfxDeleteType_byForceErase;

    /* パディング3
     *   pad3 */
    char pad3[1];

    /* 追従時SFX方向指定ダミポリ
     *   追従時SFX方向指定ダミポリ
     * Follow Bullet - Dummy Poly for SFX Pose
     *   SFX direction specification when following Damipoli
     * Default Value  = -1 */
    short followDmypoly_forSfxPose;

    /* ファンネル追従位置_半径[m]
     *   ファンネル追従位置_半径[m]
     * Follow Bullet - Radius Offset
     *   Funnel tracking position_radius [m] */
    float followOffset_Radius;

    /* 特殊効果飛距離補正倍率
     *   特殊効果飛距離補正倍率
     * SpEffect Bullet Distance - Magnification
     *   Special effect flight distance correction magnification
     * Default Value  = 1 */
    float spBulletDistUpRate;

    /* 非ロック時ターゲット射程距離[m]
     *   非ロック時ターゲット射程距離（-1：「射程距離」を参照する、0：ターゲットなし）
     * Target Range when Unlocked
     *   Target range when unlocked (-1: Refer to range, 0: No target) */
    float nolockTargetDist;

    /* pad */
    char pad4[8];
} er_bullet_param_t;
