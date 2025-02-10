#pragma once

/* Defines weapon types and each affinity.
 * Includes arrows and bolts. Responsible for scaling shown on certain consumables.
 * IDs not ending in a multiple of 100 are ignored.
 * Permitting affinities on a weapon without affinity rows at the correct IDs will result in the nearest 10000 being used.
 * SpEffects specified here can be modified by upgrades in ReinforceParamWeapon. */
typedef struct equip_param_weapon_s {
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

    /* 行動バリエーションID
     *   攻撃時に参照する行動パラメータIDを決定するときに使う
     * Behavior Variation ID
     *   Used when determining the action parameter ID to be referenced during an attack */
    int behaviorVariationId;

    /* ソートID
     *   ソートID(-1:集めない)(プログラム内で強化レベルを加味するため s32 では７桁が限界)
     * Sort ID
     *   Sort ID (-1: Do not collect) (7 digits is the limit in s32 to add the enhancement level in the program) */
    int sortId;

    /* 徘徊装備ID
     *   徘徊ゴースト用の差し替え装備ID.
     * Wandering Equip ID
     *   Replacement equipment ID for wandering ghosts. */
    unsigned int wanderingEquipId;

    /* 重量[kg]
     *   重量[kg].
     * Weight
     *   Weight [kg].
     * Default Value  = 1 */
    float weight;

    /* 装備重量比率
     *   装備重量比率
     * Weapon Weight %
     *   Equipment weight ratio */
    float weaponWeightRate;

    /* 修理価格
     *   修理基本価格
     * Repair Price
     *   Basic repair price */
    int fixPrice;

    /* 強化価格
     *   強化価格
     * Reinforcement Price
     *   Enhanced price */
    int reinforcePrice;

    /* 売却価格
     *   販売価格
     * Sell Price
     *   Selling price */
    int sellValue;

    /* 筋力補正
     *   キャラパラ補正値.
     * Correction: STR
     *   Charapara correction value. */
    float correctStrength;

    /* 俊敏補正
     *   キャラパラ補正値.
     * Correction: DEX
     *   Charapara correction value. */
    float correctAgility;

    /* 魔力補正
     *   キャラパラ補正値.
     * Correction: INT
     *   Charapara correction value. */
    float correctMagic;

    /* 信仰補正
     *   キャラパラ補正値.
     * Correction: FTH
     *   Charapara correction value. */
    float correctFaith;

    /* ガード時物理攻撃カット率
     *   ガード時のダメージカット率を各攻撃ごとに設定
     * Guard Absorption: Physical
     *   Set the damage cut rate when guarding for each attack */
    float physGuardCutRate;

    /* ガード時魔法攻撃カット率
     *   ガード攻撃でない場合は、0を入れる
     * Guard Absorption: Magic
     *   If it is not a guard attack, enter 0 */
    float magGuardCutRate;

    /* ガード時炎攻撃力カット率
     *   炎攻撃をどれだけカットするか？
     * Guard Absorption: Fire
     *   How much to cut the fire attack? */
    float fireGuardCutRate;

    /* ガード時電撃攻撃力カット率
     *   電撃攻撃をどれだけカットするか？
     * Guard Absorption: Lightning
     *   How much to cut the electric shock attack? */
    float thunGuardCutRate;

    /* 攻撃ヒット時特殊効果ID0
     *   武器に特殊効果を追加するときに登録する
     * Behavior SpEffect 1
     *   Register when adding special effects to weapons
     * Default Value  = -1 */
    int spEffectBehaviorId0;

    /* 攻撃ヒット時特殊効果ID1
     *   武器に特殊効果を追加するときに登録する
     * Behavior SpEffect 2
     *   Register when adding special effects to weapons
     * Default Value  = -1 */
    int spEffectBehaviorId1;

    /* 攻撃ヒット時特殊効果ID2
     *   武器に特殊効果を追加するときに登録する
     * Behavior SpEffect 3
     *   Register when adding special effects to weapons
     * Default Value  = -1 */
    int spEffectBehaviorId2;

    /* 常駐特殊効果ID
     *   常駐特殊効果ID0
     * Passive SpEffect 1
     *   Resident special effect ID0
     * Default Value  = -1 */
    int residentSpEffectId;

    /* 常駐特殊効果ID1
     *   常駐特殊効果ID1
     * Passive SpEffect 2
     *   Resident special effect ID1
     * Default Value  = -1 */
    int residentSpEffectId1;

    /* 常駐特殊効果ID2
     *   常駐特殊効果ID2
     * Passive SpEffect 3
     *   Resident special effect ID2
     * Default Value  = -1 */
    int residentSpEffectId2;

    /* 素材ID
     *   武器強化に必要な素材パラメータID
     * Reinforcement Material Set ID
     *   Material parameter ID required for weapon enhancement
     * Default Value  = -1 */
    int materialSetId;

    /* 派生元
     *   この武器の強化元武器ID
     * Origin Weapon +0
     *   This weapon's enhancement source weapon ID
     * Default Value  = -1 */
    int originEquipWep;

    /* 派生元 強化+1
     *   この武器の強化元武器ID1
     * Origin Weapon +1
     *   This weapon's enhancement source weapon ID1
     * Default Value  = -1 */
    int originEquipWep1;

    /* 派生元 強化+2
     *   この武器の強化元武器ID2
     * Origin Weapon +2
     *   This weapon's enhancement source weapon ID2
     * Default Value  = -1 */
    int originEquipWep2;

    /* 派生元 強化+3
     *   この武器の強化元武器ID3
     * Origin Weapon +3
     *   This weapon's enhancement source weapon ID3
     * Default Value  = -1 */
    int originEquipWep3;

    /* 派生元 強化+4
     *   この武器の強化元武器ID4
     * Origin Weapon +4
     *   This weapon's enhancement source weapon ID 4
     * Default Value  = -1 */
    int originEquipWep4;

    /* 派生元 強化+5
     *   この武器の強化元武器ID5
     * Origin Weapon +5
     *   This weapon's enhancement source weapon ID 5
     * Default Value  = -1 */
    int originEquipWep5;

    /* 派生元 強化+6
     *   この武器の強化元武器ID6
     * Origin Weapon +6
     *   This weapon's enhancement source weapon ID 6
     * Default Value  = -1 */
    int originEquipWep6;

    /* 派生元 強化+7
     *   この武器の強化元武器ID7
     * Origin Weapon +7
     *   This weapon's enhancement source weapon ID 7
     * Default Value  = -1 */
    int originEquipWep7;

    /* 派生元 強化+8
     *   この武器の強化元武器ID8
     * Origin Weapon +8
     *   This weapon's enhancement source weapon ID8
     * Default Value  = -1 */
    int originEquipWep8;

    /* 派生元 強化+9
     *   この武器の強化元武器ID9
     * Origin Weapon +9
     *   This weapon's enhancement source weapon ID 9
     * Default Value  = -1 */
    int originEquipWep9;

    /* 派生元 強化+10
     *   この武器の強化元武器ID10
     * Origin Weapon +10
     *   This weapon's enhancement source weapon ID 10
     * Default Value  = -1 */
    int originEquipWep10;

    /* 派生元 強化+11
     *   この武器の強化元武器ID11
     * Origin Weapon +11
     *   This weapon's enhancement source weapon ID 11
     * Default Value  = -1 */
    int originEquipWep11;

    /* 派生元 強化+12
     *   この武器の強化元武器ID12
     * Origin Weapon +12
     *   This weapon's enhancement source weapon ID 12
     * Default Value  = -1 */
    int originEquipWep12;

    /* 派生元 強化+13
     *   この武器の強化元武器ID13
     * Origin Weapon +13
     *   This weapon's enhancement source weapon ID 13
     * Default Value  = -1 */
    int originEquipWep13;

    /* 派生元 強化+14
     *   この武器の強化元武器ID14
     * Origin Weapon +14
     *   This weapon's enhancement source weapon ID14
     * Default Value  = -1 */
    int originEquipWep14;

    /* 派生元 強化+15
     *   この武器の強化元武器ID15
     * Origin Weapon +15
     *   This weapon's enhancement source weapon ID 15
     * Default Value  = -1 */
    int originEquipWep15;

    /* 特攻Aダメージ倍率
     *   特攻A用のダメージ倍率
     * Damage Multiplier %: Type A
     *   Damage multiplier for special attack A
     * Default Value  = 1 */
    float weakA_DamageRate;

    /* 特攻Bダメージ倍率
     *   特攻B用のダメージ倍率
     * Damage Multiplier %: Type B
     *   Damage multiplier for special attack B
     * Default Value  = 1 */
    float weakB_DamageRate;

    /* 特攻Cダメージ倍率
     *   特攻C用のダメージ倍率
     * Damage Multiplier %: Type C
     *   Damage multiplier for special attack C
     * Default Value  = 1 */
    float weakC_DamageRate;

    /* 特攻Dダメージ倍率
     *   特攻D用のダメージ倍率
     * Damage Multiplier %: Type D
     *   Damage multiplier for special attack D
     * Default Value  = 1 */
    float weakD_DamageRate;

    /* 睡眠耐性カット率_最大補正値
     *   睡眠に対する攻撃力（特殊効果パラメータに設定）のカット率補正値の最大値
     * Max Correction: Sleep Guard Resist
     *   Maximum value of cut rate correction value for attack power against sleep (set as special effect parameter) */
    float sleepGuardResist_MaxCorrect;

    /* 発狂耐性カット率_最大補正値
     *   発狂に対する攻撃力（特殊効果パラメータに設定）のカット率補正値の最大値
     * Max Correction: Madness Guard Resist
     *   Maximum value of cut rate correction value for attack power against madness (set as special effect parameter) */
    float madnessGuardResist_MaxCorrect;

    /* SA武器攻撃力
     *   スーパーアーマー基本攻撃力
     * Poise Damage
     *   Super Armor Basic Attack Power */
    float saWeaponDamage;

    /* 装備モデル番号
     *   装備モデルの番号.
     * Equip Model ID
     *   Equipment model number. */
    unsigned short equipModelId;

    /* アイコンID
     *   メニューアイコンID.
     * Icon ID
     *   Menu icon ID. */
    unsigned short iconId;

    /* 耐久度
     *   初期耐久度.
     * Durability
     *   Initial durability.
     * Default Value  = 100 */
    unsigned short durability;

    /* 耐久度最大値
     *   新品耐久度.
     * Max Durability
     *   New durability.
     * Default Value  = 100 */
    unsigned short durabilityMax;

    /* 投げ抜け攻撃力基本値
     *   投げ抜け攻撃力の基本値
     * Throw Escape Damage
     *   Basic value of throw-through attack power */
    unsigned short attackThrowEscape;

    /* パリィ発生時間[frame]
     *   パリィダメージの寿命を制限する。TimeActで設定されている以上には持続しない。
     * Parry Occurrence Duration
     *   Limit the life of parry damage. It does not last longer than it is set in TimeAct.
     * Default Value  = -1 */
    short parryDamageLife;

    /* 物理攻撃力基本値
     *   敵のＨＰにダメージを与える物理属性攻撃の基本値
     * Damage: Physical
     *   Basic value of physical attribute attack that damages the enemy's HP
     * Default Value  = 100 */
    unsigned short attackBasePhysics;

    /* 魔法攻撃力基本値
     *   敵のＨＰにダメージを与える魔法属性攻撃の基本値
     * Damage: Magic
     *   Basic value of magic attribute attack that damages the enemy's HP
     * Default Value  = 100 */
    unsigned short attackBaseMagic;

    /* 炎攻撃力基本値
     *   敵のＨＰにダメージを与える炎属性攻撃の基本値
     * Damage: Fire
     *   Basic value of fire attribute attack that damages the enemy's HP
     * Default Value  = 100 */
    unsigned short attackBaseFire;

    /* 電撃攻撃力基本値
     *   敵のＨＰにダメージを与える電撃属性攻撃の基本値
     * Damage: Lightning
     *   Basic value of electric shock attribute attack that damages the enemy's HP
     * Default Value  = 100 */
    unsigned short attackBaseThunder;

    /* スタミナ攻撃力
     *   敵へのスタミナ攻撃力
     * Damage: Stamina
     *   Stamina attack power against the enemy
     * Default Value  = 100 */
    unsigned short attackBaseStamina;

    /* ガード範囲[deg]
     *   武器のガード時の防御発生範囲角度
     * Guard Angle
     *   Defense occurrence range angle when guarding weapons */
    short guardAngle;

    /* SA耐久値
     *   攻撃モーション中に使われる追加SA耐久値
     * Poise Durability
     *   Additional SA durability used during attack motion */
    float saDurability;

    /* ガード時スタミナ防御力
     *   ガード成功時に、敵のスタミナ攻撃に対する防御力
     * Guard Stability
     *   Defense against enemy stamina attacks when guarding successfully */
    short staminaGuardDef;

    /* 強化タイプID
     *   強化タイプID
     * Reinforce Type ID
     *   Enhanced type ID */
    short reinforceTypeId;

    /* トロフィーＳグレードID
     *   トロフィーシステムに関係あるか？
     * Achievement ID [1]
     *   Is it related to the trophy system?
     * Default Value  = -1 */
    short trophySGradeId;

    /* トロフィーSEQ番号
     *   トロフィーのSEQ番号（１３～２９）
     * Achievement ID [2]
     *   Trophy SEQ number (13-29)
     * Default Value  = -1 */
    short trophySeqId;

    /* 投げ攻撃力倍率
     *   投げの攻撃力倍率
     * Critical Multiplier
     *   Throw attack power multiplier */
    short throwAtkRate;

    /* 弓飛距離補正[％]
     *   飛距離を伸ばすアップ％
     * Bow Distance %
     *   Up% to extend the flight distance */
    short bowDistRate;

    /* 装備モデル種別
     *   装備モデルの種別.
     * Equip Model Category
     *   Equipment model type.
     * Default Value  = 7 */
    unsigned char equipModelCategory;

    /* 装備モデル性別
     *   装備モデルの性別.
     * Equip Model Gender
     *   Gender of equipment model. */
    unsigned char equipModelGender;

    /* 武器カテゴリ
     *   武器のカテゴリ.
     * Weapon Category
     *   Weapon category. */
    unsigned char weaponCategory;

    /* 武器モーションカテゴリ
     *   武器モーションのカテゴリ.
     * Weapon Motion Category
     *   Weapon motion category. */
    unsigned char wepmotionCategory;

    /* ガードモーションカテゴリ
     *   ガードモーションのカテゴリ
     * Guard Motion Category
     *   Guard motion category */
    unsigned char guardmotionCategory;

    /* 攻撃材質
     *   攻撃パラから使用される攻撃材質
     * Attack Material
     *   Attack material used from attack para */
    unsigned char atkMaterial;

    /* 防御SE材質1
     *   攻撃パラから使用される防御SE材質1
     * Defence SE Material [1]
     *   Defense SE material used from attack para 1 */
    unsigned short defSeMaterial1;

    /* 補正タイプ（物理攻撃力）
     *   一次パラメータによる物理攻撃力の補正グラフのタイプを決める
     * Correction Type: Physical
     *   Correcting physical attack power by primary parameters Determines the type of graph */
    unsigned char correctType_Physics;

    /* 特殊属性
     *   武器の特殊属性値
     * Special Attribute
     *   Weapon special attribute value */
    unsigned char spAttribute;

    /* 特殊攻撃カテゴリ
     *   特殊攻撃カテゴリ（50～999まで可能)
     * Special Motion Category
     *   Special attack category (possible from 50 to 999) */
    unsigned short spAtkcategory;

    /* 武器モーション片手ID
     *   片手装備時の基本モーションID.
     * Weapon Motion Position - 1H
     *   Basic motion ID when equipped with one hand. */
    unsigned char wepmotionOneHandId;

    /* 武器モーション両手ID
     *   両手装備時の基本モーションID.
     * Weapon Motion Position - 2H
     *   Basic motion ID when equipped with both hands. */
    unsigned char wepmotionBothHandId;

    /* 装備適正筋力
     *   装備適正値.
     * Requirement: STR
     *   Equipment appropriate value. */
    unsigned char properStrength;

    /* 装備適正俊敏
     *   装備適正値.
     * Requirement: DEX
     *   Equipment appropriate value. */
    unsigned char properAgility;

    /* 装備適正魔力
     *   装備適正値.
     * Requirement: INT
     *   Equipment appropriate value. */
    unsigned char properMagic;

    /* 装備適正信仰
     *   装備適正値.
     * Requirement: FTH
     *   Equipment appropriate value. */
    unsigned char properFaith;

    /* 筋力オーバー開始値
     *   筋力オーバー開始値
     * Strength over Start Value
     *   Strength over start value */
    unsigned char overStrength;

    /* パリィ攻撃基本値
     *   敵のパリィをやぶるための基本値
     * Base Parry Attack
     *   Basic value to defeat the enemy's parry */
    unsigned char attackBaseParry;

    /* パリィ防御値
     *   パリィ判定時に、パリィになるかガードになるかの判定に利用
     * Base Parry Defens
     *   Used to judge whether to be a parry or a guard at the time of parry judgment */
    unsigned char defenseBaseParry;

    /* はじき防御力基本値
     *   敵の攻撃をガードしたときに、はじけるかどうかの判定に利用
     * Base Guard Repel
     *   Used to determine if it will pop when guarding an enemy attack */
    unsigned char guardBaseRepel;

    /* はじき攻撃力基本値
     *   ガード敵を攻撃した時に、はじかれるかどうかの判定に利用
     * Base Attack Repel
     *   Guard Used to determine whether or not to be repelled when attacking an enemy */
    unsigned char attackBaseRepel;

    /* ガードカット無効化倍率
     *   相手のガードカットを無効化させる倍率。-100で完全無効。100で相手の防御効果倍増。
     * Guard Bypass %
     *   Magnification that invalidates the opponent's guard cut. -100 is completely invalid. Double the defense effect of the opponent at 100. */
    char guardCutCancelRate;

    /* ガードレベル
     *   ガードしたとき、敵の攻撃をどのガードモーションで受けるか？を決める
     * Guard Level
     *   When guarding, which guard motion will the enemy attack? Decide */
    char guardLevel;

    /* 斬撃攻撃カット率
     *   攻撃タイプを見て、斬撃属性のダメージを何％カットするか？を指定
     * Guard Absorption: Slash
     *   Looking at the attack type, what percentage of the damage of the slashing attribute is cut? Specify */
    char slashGuardCutRate;

    /* 打撃攻撃カット率
     *   攻撃タイプを見て、打撃属性のダメージを何％カットするか？を指定
     * Guard Absorption: Strike
     *   Looking at the attack type, what percentage of the damage of the hit attribute is cut? Specify */
    char blowGuardCutRate;

    /* 刺突攻撃カット率
     *   攻撃タイプを見て、刺突属性のダメージを何％カットするか？を指定
     * Guard Absorption: Thrust
     *   Looking at the attack type, what percentage of the damage of the piercing attribute is cut? Specify */
    char thrustGuardCutRate;

    /* 毒耐性カット率
     *   毒にする攻撃力（特殊効果パラメータに設定）をどれだけカットするか
     * Guard Resist: Poison
     *   How much to cut the attack power to poison (set to the special effect parameter) */
    char poisonGuardResist;

    /* 疫病攻撃カット率
     *   疫病にする攻撃力（特殊効果パラメータに設定）をどれだけカットするか
     * Guard Resist: Scarlet Rot
     *   How much to cut the attack power (set as a special effect parameter) to make it a plague */
    char diseaseGuardResist;

    /* 出血攻撃カット率
     *   出血にする攻撃力（特殊効果パラメータに設定）をどれだけカットするか
     * Guard Resist: Hemorrhage
     *   How much to cut the attack power (set as a special effect parameter) to make bleeding */
    char bloodGuardResist;

    /* 呪攻撃カット率
     *   呪いにする攻撃力（特殊効果パラメータに設定）をどれだけカットするか
     * Guard Resist: Blight
     *   How much to cut the attack power (set as a special effect parameter) to curse */
    char curseGuardResist;

    /* 物理属性1
     *   物理属性1
     * Attack Attribute [1]
     *   Physical attribute 1 */
    unsigned char atkAttribute;

    /* 右手装備
     *   右手装備可能か.
     * Can wield in Right Hand
     *   Is it possible to equip it with the right hand? */
    unsigned char rightHandEquipable:1;

    /* 左手装備
     *   左手装備可能か.
     * Can wield in Left Hand
     *   Is it possible to equip it with the left hand? */
    unsigned char leftHandEquipable:1;

    /* 両手装備
     *   両手装備可能か.
     * Can wield in Both Hands
     *   Is it possible to equip with both hands? */
    unsigned char bothHandEquipable:1;

    /* 弓矢弾装備
     *   弓用矢弾装備可能か.
     * Can wield in Arrow Slot
     *   Is it possible to equip a bow bullet? */
    unsigned char arrowSlotEquipable:1;

    /* 弩矢弾装備
     *   弩用矢弾装備可能か.
     * Can wield in Bolt Slot
     *   Is it possible to equip a crossbow bullet? */
    unsigned char boltSlotEquipable:1;

    /* ガード可能
     *   左手装備時L1でガード
     * Enables Guard
     *   Guard with L1 when equipped with left hand */
    unsigned char enableGuard:1;

    /* パリィ可能
     *   左手装備時L2でパリィ
     * Enables Parry
     *   Parry with L2 when equipped with left hand */
    unsigned char enableParry:1;

    /* 魔法可能
     *   攻撃時に魔法発動
     * Enables Sorcery
     *   Activates magic when attacking */
    unsigned char enableMagic:1;

    /* 呪術可能
     *   攻撃時に呪術発動
     * Enables Pyromancy
     *   Cast magic when attacking */
    unsigned char enableSorcery:1;

    /* 奇蹟可能
     *   攻撃時に奇蹟発動
     * Enables Incantations
     *   Miracle activated when attacking */
    unsigned char enableMiracle:1;

    /* 誓約魔法可能
     *   攻撃時に誓約魔法発動
     * Enables Vow Magic
     *   Activates pledge magic when attacking */
    unsigned char enableVowMagic:1;

    /* 通常
     *   メニュー表示用攻撃タイプ。通常か
     * Type Display: Normal
     *   Attack type for menu display. Is it normal? */
    unsigned char isNormalAttackType:1;

    /* 打撃
     *   メニュー表示用攻撃タイプ。打撃か
     * Type Display: Strike
     *   Attack type for menu display. Is it a blow? */
    unsigned char isBlowAttackType:1;

    /* 斬撃
     *   メニュー表示用攻撃タイプ。斬撃か
     * Type Display: Slash
     *   Attack type for menu display. Is it a slash? */
    unsigned char isSlashAttackType:1;

    /* 刺突
     *   メニュー表示用攻撃タイプ。刺突か
     * Type Display: Thrust
     *   Attack type for menu display. Is it a piercing? */
    unsigned char isThrustAttackType:1;

    /* エンチャント可能か？
     *   松脂などで、強化可能か？
     * Is Buffable
     *   Can it be strengthened with pine fat? */
    unsigned char isEnhance:1;

    /* 人間性補正あるか
     *   人間性による攻撃力補正があるか
     * Is Arcane Correction
     *   Is there an attack power correction by human nature? */
    unsigned char isHeroPointCorrect:1;

    /* 強化できるか？
     *   強化ショップで強化対象リストに並ぶ(仕様変更で削除するかも？)
     * Is Reinforcable
     *   Listed in the enhancement target list at the enhancement shop (may be deleted due to specification changes?) */
    unsigned char isCustom:1;

    /* 転職リセット禁止か
     *   転職リセット禁止か
     * Disable Base Change Reset
     *   Is job change reset prohibited? */
    unsigned char disableBaseChangeReset:1;

    /* 修理禁止か
     *   修理禁止か
     * Repair is Disabled
     *   Is repair prohibited? */
    unsigned char disableRepair:1;

    /* ダークハンドか
     *   ダークハンドか
     * Is Dark Hand
     *   Is it a dark hand? */
    unsigned char isDarkHand:1;

    /* DLC用シンプルモデルありか
     *   ＤＬＣ用シンプルモデルが存在しているか
     * Is Simple Model for DLC
     *   Is there a simple model for DLC? */
    unsigned char simpleModelForDlc:1;

    /* ランタン武器
     *   ランタン武器か
     * Is a Light Source
     *   Is it a lantern weapon? */
    unsigned char lanternWep:1;

    /* 対霊武器
     *   NPCパラの「霊体か」が○の相手に攻撃を当たるようになります。また、攻撃パラの「霊体攻撃か」が○の攻撃をガードできるようになります。
     * Can Hit Ghost Enemy
     *   NPC Para's spirit body will now hit the opponent of . Also, the attack para Is it a ghost attack? Will be able to guard the attack of . */
    unsigned char isVersusGhostWep:1;

    /* 武器転職カテゴリ
     *   武器転職カテゴリ。属性アイコン表示に使用します。
     * Base Change Category
     *   Weapon career change category. Used to display the attribute icon. */
    unsigned char baseChangeCategory:6;

    /* 竜狩りか
     *   竜狩り武器か
     * Is Dragonslayer
     *   Is it a dragon hunting weapon? */
    unsigned char isDragonSlayer:1;

    /* 預けれるか
     *   倉庫に預けれるか
     * Can Deposit
     *   Can you leave it in the warehouse? */
    unsigned char isDeposit:1;

    /* マルチドロップ共有禁止か
     *   マルチドロップ共有禁止か
     * Cannot Drop in Multiplayer
     *   Is multi-drop sharing prohibited? */
    unsigned char disableMultiDropShare:1;

    /* 捨てれるか
     *   アイテムを捨てれるか？TRUE=捨てれる
     * Can Discard
     *   Can you throw away the item? TRUE = thrown away */
    unsigned char isDiscard:1;

    /* その場に置けるか
     *   アイテムをその場に置けるか？TRUE=置ける
     * Can Drop
     *   Can I put the item on the spot? TRUE = can be placed */
    unsigned char isDrop:1;

    /* 取得ログ表示条件
     *   アイテム取得時にアイテム取得ログに表示するか（未入力: ○）
     * Item Acquisition Log Condition Type
     *   Whether to display in the item acquisition log when acquiring the item (not entered: )
     * Default Value  = 1 */
    unsigned char showLogCondType:1;

    /* 投げ可能
     *   投げ可能な武器かどうか
     * Enable Throw
     *   Whether it is a throwable weapon */
    unsigned char enableThrow:1;

    /* 取得ダイアログ表示条件
     *   アイテム取得時にアイテム取得ダイアログに表示するか（未入力: newのみ）
     * Item Acquisition Dialog Condition Type
     *   Whether to display it in the item acquisition dialog when acquiring an item (not entered: new only)
     * Default Value  = 2 */
    unsigned char showDialogCondType:2;

    /* 魔石属性変更禁止か
     *   魔石属性変更禁止か
     * Prevent Affinity Change
     *   Is it prohibited to change the magic stone attribute? */
    unsigned char disableGemAttr:1;

    /* 防御SFX材質1
     *   攻撃パラから使用される防御SFX材質1
     * Defence SFX Material [1]
     *   Defensive SFX material used from attack para 1 */
    unsigned short defSfxMaterial1;

    /* 武器コライダブル設定
     *   武器のコライダブル設定
     * Weapon Collidable Type [0]
     *   Weapon collaborative setting
     * Default Value  = 1 */
    unsigned char wepCollidableType0;

    /* 武器1コライダブル設定
     *   武器1のコライダブル設定
     * Weapon Collidable Type [1]
     *   Weapon 1 collaborative setting
     * Default Value  = 1 */
    unsigned char wepCollidableType1;

    /* 姿勢制御ID(右手)
     *   姿勢制御ID(右手)
     * Posture Control ID - Weapon Right
     *   Attitude control ID (right hand) */
    unsigned char postureControlId_Right;

    /* 姿勢制御ID(左手)
     *   姿勢制御ID(左手)
     * Posture Control ID - Weapon Left
     *   Attitude control ID (left hand) */
    unsigned char postureControlId_Left;

    /* 剣閃SfxID_０
     *   剣閃SfxID_０(-1無効)
     * Trace SFX ID [0]
     *   Sword flash SfxID_0 (-1 invalid)
     * Default Value  = -1 */
    int traceSfxId0;

    /* 根元剣閃ダミポリID_０
     *   剣閃根元ダミポリID_０(-1無効)
     * Trace SFX ID [0] - Dummy Poly ID - Head
     *   Sword flash root Damipoli ID_0 (-1 invalid)
     * Default Value  = -1 */
    int traceDmyIdHead0;

    /* 剣先剣閃ダミポリID_０
     *   剣閃剣先ダミポリID_０
     * Trace SFX ID [0] - Dummy Poly ID - Tail
     *   Sword Flash Sword Tip Damipoli ID_0
     * Default Value  = -1 */
    int traceDmyIdTail0;

    /* 剣閃SfxID_１
     *   剣閃SfxID_１(-1無効)
     * Trace SFX ID [1]
     *   Sword flash SfxID_1 (-1 invalid)
     * Default Value  = -1 */
    int traceSfxId1;

    /* 根元剣閃ダミポリID_１
     *   剣閃根元ダミポリID_１(-1無効)
     * Trace SFX ID [1] - Dummy Poly ID - Head
     *   Sword Flash Root Damipoli ID_1 (-1 invalid)
     * Default Value  = -1 */
    int traceDmyIdHead1;

    /* 剣先剣閃ダミポリID_１
     *   剣閃剣先ダミポリID_１
     * Trace SFX ID [1] - Dummy Poly ID - Tail
     *   Sword Flash Sword Tip Damipoli ID_1
     * Default Value  = -1 */
    int traceDmyIdTail1;

    /* 剣閃SfxID_２
     *   剣閃SfxID_２(-1無効)
     * Trace SFX ID [2]
     *   Sword flash SfxID_2 (-1 invalid)
     * Default Value  = -1 */
    int traceSfxId2;

    /* 根元剣閃ダミポリID_２
     *   剣閃根元ダミポリID_２(-1無効)
     * Trace SFX ID [2] - Dummy Poly ID - Head
     *   Sword Flash Root Damipoli ID_2 (-1 invalid)
     * Default Value  = -1 */
    int traceDmyIdHead2;

    /* 剣先剣閃ダミポリID_２
     *   剣閃剣先ダミポリID_２
     * Trace SFX ID [2] - Dummy Poly ID - Tail
     *   Sword Flash Sword Tip Damipoli ID_2
     * Default Value  = -1 */
    int traceDmyIdTail2;

    /* 剣閃SfxID_３
     *   剣閃SfxID_３(-1無効)
     * Trace SFX ID [3]
     *   Sword Flash SfxID_3 (-1 invalid)
     * Default Value  = -1 */
    int traceSfxId3;

    /* 根元剣閃ダミポリID_３
     *   剣閃根元ダミポリID_３(-1無効)
     * Trace SFX ID [3] - Dummy Poly ID - Head
     *   Sword flash root Damipoli ID_3 (-1 invalid)
     * Default Value  = -1 */
    int traceDmyIdHead3;

    /* 剣先剣閃ダミポリID_３
     *   剣閃剣先ダミポリID_３
     * Trace SFX ID [3] - Dummy Poly ID - Tail
     *   Sword Flash Sword Tip Damipoli ID_3
     * Default Value  = -1 */
    int traceDmyIdTail3;

    /* 剣閃SfxID_４
     *   剣閃SfxID_４(-1無効)
     * Trace SFX ID [4]
     *   Sword Flash SfxID_4 (-1 invalid)
     * Default Value  = -1 */
    int traceSfxId4;

    /* 根元剣閃ダミポリID_４
     *   剣閃根元ダミポリID_４(-1無効)
     * Trace SFX ID [4] - Dummy Poly ID - Head
     *   Sword flash root Damipoli ID_4 (-1 invalid)
     * Default Value  = -1 */
    int traceDmyIdHead4;

    /* 剣先剣閃ダミポリID_４
     *   剣閃剣先ダミポリID_４
     * Trace SFX ID [4] - Dummy Poly ID - Tail
     *   Sword Flash Sword Tip Damipoli ID_4
     * Default Value  = -1 */
    int traceDmyIdTail4;

    /* 剣閃SfxID_５
     *   剣閃SfxID_５(-1無効)
     * Trace SFX ID [5]
     *   Sword Flash SfxID_5 (-1 invalid)
     * Default Value  = -1 */
    int traceSfxId5;

    /* 根元剣閃ダミポリID_５
     *   剣閃根元ダミポリID_５(-1無効)
     * Trace SFX ID [5] - Dummy Poly ID - Head
     *   Sword Flash Root Damipoli ID_5 (-1 invalid)
     * Default Value  = -1 */
    int traceDmyIdHead5;

    /* 剣先剣閃ダミポリID_５
     *   剣閃剣先ダミポリID_５
     * Trace SFX ID [5] - Dummy Poly ID - Tail
     *   Sword Flash Sword Tip Damipoli ID_5
     * Default Value  = -1 */
    int traceDmyIdTail5;

    /* 剣閃SfxID_６
     *   剣閃SfxID_６(-1無効)
     * Trace SFX ID [6]
     *   Sword Flash SfxID_6 (-1 invalid)
     * Default Value  = -1 */
    int traceSfxId6;

    /* 根元剣閃ダミポリID_６
     *   剣閃根元ダミポリID_６(-1無効)
     * Trace SFX ID [6] - Dummy Poly ID - Head
     *   Sword Flash Root Damipoli ID_6 (-1 invalid)
     * Default Value  = -1 */
    int traceDmyIdHead6;

    /* 剣先剣閃ダミポリID_６
     *   剣閃剣先ダミポリID_６
     * Trace SFX ID [6] - Dummy Poly ID - Tail
     *   Sword Flash Sword Tip Damipoli ID_6
     * Default Value  = -1 */
    int traceDmyIdTail6;

    /* 剣閃SfxID_７
     *   剣閃SfxID_７(-1無効)
     * Trace SFX ID [7]
     *   Sword Flash SfxID_7 (-1 invalid)
     * Default Value  = -1 */
    int traceSfxId7;

    /* 根元剣閃ダミポリID_７
     *   剣閃根元ダミポリID_７(-1無効)
     * Trace SFX ID [7] - Dummy Poly ID - Head
     *   Sword Flash Root Damipoli ID_7 (-1 invalid)
     * Default Value  = -1 */
    int traceDmyIdHead7;

    /* 剣先剣閃ダミポリID_７
     *   剣閃剣先ダミポリID_７
     * Trace SFX ID [7] - Dummy Poly ID - Tail
     *   Sword Flash Sword Tip Damipoli ID_7
     * Default Value  = -1 */
    int traceDmyIdTail7;

    /* 防御SFX材質2
     *   攻撃パラから使用される防御SFX材質2
     * Defence SFX Material [2]
     *   Defensive SFX material used from attack para 2 */
    unsigned short defSfxMaterial2;

    /* 防御SE材質2
     *   攻撃パラから使用される防御SE材質2
     * Defence SE Material [2]
     *   Defense SE material used from attack para 2 */
    unsigned short defSeMaterial2;

    /* 吸着位置Id
     *   武器吸着位置パラメータのId。この値により武器が吸着する位置を決定する(-1：旧ソースコード直書きの値を参照する)
     * Weapon Sheath Position ID
     *   Weapon adsorption position parameter Id. This value determines the position where the weapon is attracted (-1: Refer to the value written directly in the old source code).
     * Default Value  = -1 */
    int absorpParamId;

    /* 強靭度 補正倍率
     *   強靭度の基本値を補正する倍率です
     * Toughness Correction
     *   It is a magnification that corrects the basic value of toughness. */
    float toughnessCorrectRate;

    /* 防具SAダメージ倍率が初期値でも有効か？
     *   防具SAが初期値でも強靭度計算が行われるかどうか。詳細は強靭度仕様書.xlsxを確認してください
     * Is Toughness Perfomed if Poise is Initial Value
     *   Whether the toughness calculation is performed even if the armor SA is the initial value. Check the toughness specification .xlsx for details */
    unsigned char isValidTough_ProtSADmg:1;

    /* 双剣か
     *   この武器は双剣か。
     * Is Dual Weapon
     *   Is this weapon a twin sword? */
    unsigned char isDualBlade:1;

    /* 自動装填可能か
     *   矢・ボルトのみ有効。新しくこの武器を拾っ時に対象装備スロットが空の場合に自動で装備するかどうか
     * Is Auto Equipped
     *   Only valid for arrows and bolts. Whether to automatically equip this weapon if the target equipment slot is empty when picking up this weapon */
    unsigned char isAutoEquip:1;

    /* 緊急回避可能か
     *   緊急回避可能な武器かどうか。ビヘイビアスクリプトに渡す。
     * Is Emergency Avoidance Possible
     *   Is it an emergency avoidable weapon? Pass it to the behavior script. */
    unsigned char isEnableEmergencyStep:1;

    /* カットシーン中非表示か
     *   カットシーン中非表示か
     * Is Hidden in Cutscene
     *   Is it hidden during cutscenes? */
    unsigned char invisibleOnRemo:1;

    unsigned char unknown_0x17c_5:1;

    /* Is Arrow
     *   [DLC] Is on by default for arrows. */
    unsigned char isArrow:1;

    /* Is Weapon Catalyst
     *   [DLC] Is on by default for Carian Sorcery Sword. */
    unsigned char isWeaponCatalyst:1;

    /* 補正タイプ（魔法攻撃力）
     *   一次パラメータによる魔法攻撃力の補正グラフのタイプを決める
     * Correction Type: Magic
     *   Determining the type of magic attack power correction graph with primary parameters */
    unsigned char correctType_Magic;

    /* 補正タイプ（炎攻撃力）
     *   一次パラメータによる炎攻撃力の補正グラフのタイプを決める
     * Correction Type: Fire
     *   Determine the type of flame attack power correction graph with primary parameters */
    unsigned char correctType_Fire;

    /* 補正タイプ（雷攻撃力）
     *   一次パラメータによる雷攻撃力の補正グラフのタイプを決める
     * Correction Type: Lightning
     *   Determine the type of lightning attack power correction graph with primary parameters */
    unsigned char correctType_Thunder;

    /* 特攻Eダメージ倍率
     *   特攻E用のダメージ倍率
     * Damage Multiplier %: Type E
     *   Damage multiplier for special attack E
     * Default Value  = 1 */
    float weakE_DamageRate;

    /* 特攻Fダメージ倍率
     *   特攻F用のダメージ倍率
     * Damage Multiplier %: Type F
     *   Damage multiplier for special attack F
     * Default Value  = 1 */
    float weakF_DamageRate;

    /* ガード時闇攻撃力カット率
     *   闇攻撃をどれだけカットするか？
     * Guard Absorption: Holy
     *   How much to cut the dark attack? */
    float darkGuardCutRate;

    /* 闇攻撃力基本値
     *   敵のＨＰにダメージを与える闇属性攻撃の基本値
     * Damage: Holy
     *   Basic value of darkness attack that damages the enemy's HP */
    unsigned short attackBaseDark;

    /* 補正タイプ（闇攻撃力）
     *   一次パラメータによる闇攻撃力の補正グラフのタイプを決める
     * Correction Type: Holy
     *   Determine the type of darkness attack power correction graph with primary parameters */
    unsigned char correctType_Dark;

    /* 補正タイプ（毒攻撃力）
     *   一次パラメータによる毒攻撃力の補正グラフのタイプを決める
     * Correction Type: Poison
     *   Determining the type of poison attack power correction graph with primary parameters */
    unsigned char correctType_Poison;

    /* ソートアイテム種別ID
     *   ソートアイテム種別ID。ソート「アイテム種別順」にて、同じIDは同じグループとしてまとめて表示されます
     * Sort Group ID
     *   Sort item type ID. In the sort Item type order, the same ID is displayed together as the same group.
     * Default Value  = 255 */
    unsigned char sortGroupId;

    /* 物理属性2
     *   物理属性2
     * Attack Attribute [2]
     *   Physical attribute referred to in the AtkParam */
    unsigned char atkAttribute2;

    /* 睡眠攻撃カット率
     *   睡眠にする攻撃力（特殊効果パラメータに設定）をどれだけカットするか
     * Guard Resist: Sleep
     *   How much to cut the attack power (set as a special effect parameter) to sleep */
    char sleepGuardResist;

    /* 発狂攻撃カット率
     *   発狂にする攻撃力（特殊効果パラメータに設定）をどれだけカットするか
     * Guard Resist: Madness
     *   How much to cut the attack power (set to the special effect parameter) that makes you go mad */
    char madnessGuardResist;

    /* 補正タイプ（出血攻撃力）
     *   一次パラメータによる出血攻撃力の補正グラフのタイプを決める
     * Correction Type: Hemorrhage
     *   Determine the type of bleeding attack power correction graph with primary parameters */
    unsigned char correctType_Blood;

    /* 装備適正運
     *   装備適正値.
     * Requirement: ARC
     *   Equipment appropriate value. */
    unsigned char properLuck;

    /* 冷気攻撃カット率
     *   冷気にする攻撃力（特殊効果パラメータに設定）をどれだけカットするか
     * Guard Resist: Frostbite
     *   How much to cut the attack power (set to the special effect parameter) to cool down */
    char freezeGuardResist;

    /* 自動補充タイプ
     *   自動補充する/しないの可否およびデフォルト設定をコントロールします
     * Auto Replenish Type
     *   Controls whether or not to automatically replenish and default settings */
    unsigned char autoReplenishType;

    /* アーツパラメータID
     *   アーツパラメータのID
     * Sword Arts Param ID
     *   Arts parameter ID */
    int swordArtsParamId;

    /* 運補正
     *   キャラパラ補正値.
     * Correction: ARC
     *   Charapara correction value. */
    float correctLuck;

    /* 矢筒(弾倉)表示モデル用装備ID
     *   矢筒(弾倉)表示モデルの装備品番号。弓の場合は矢筒、弩の場合は弾倉として表示する。
     * Ammunition Equip ID
     *   Equipment number of the quiver (magazine) display model. In the case of a bow, it is displayed as a quiver, and in the case of a crossbow, it is displayed as a magazine. */
    unsigned int arrowBoltEquipId;

    /* 還元時レベル設定
     *   武器を還元・派生させるときに強化レベルをどう設定するかの種別
     * Derivation Level Type
     *   Type of how to set the enhancement level when returning or deriving a weapon */
    unsigned char DerivationLevelType;

    /* エンチャントSfxサイズ
     *   エンチャントSfxIdにオフセットする値
     * Enchantment SFX Size
     *   Value offset to enchantment SfxId */
    unsigned char enchantSfxSize;

    /* 武器種別
     *   武器種別。テキストと、魔石の紐付けに使われる（※テキスト以外にも使われるようになった）
     * Weapon Type
     *   Weapon type. Used for linking text and magic stones (* It is now used for other than text) */
    unsigned short wepType;

    /* ガード時物理攻撃カット率_最大補正値
     *   ガード時のダメージ物理カット率の補正値の最大値
     * Max Correction: Physical Guard Absorption
     *   Maximum damage physical cut rate correction value when guarding */
    float physGuardCutRate_MaxCorrect;

    /* ガード時魔法攻撃カット率_最大補正値
     *   ガード時のダメージ魔法カット率の補正値の最大値
     * Max Correction: Magic Guard Absorption
     *   Maximum value of correction value of damage magic cut rate when guarding */
    float magGuardCutRate_MaxCorrect;

    /* ガード時炎攻撃力カット率_最大補正値
     *   ガード時のダメージ炎カット率の補正値の最大値
     * Max Correction: Fire Guard Absorption
     *   Maximum value of correction value of damage flame cut rate when guarding */
    float fireGuardCutRate_MaxCorrect;

    /* ガード時電撃攻撃力カット率_最大補正値
     *   ガード時のダメージ電撃カット率の補正値の最大値
     * Max Correction: Lightning Guard Absorption
     *   Maximum value of correction value of damage electric shock cut rate when guarding */
    float thunGuardCutRate_MaxCorrect;

    /* ガード時闇攻撃力カット率_最大補正値
     *   ガード時のダメージ闇カット率の補正値の最大値
     * Max Correction: Holy Guard Absorption
     *   Maximum value of correction value of damage darkness cut rate when guarding */
    float darkGuardCutRate_MaxCorrect;

    /* 毒耐性カット率_最大補正値
     *   毒に対する攻撃力（特殊効果パラメータに設定）のカット率補正値の最大値
     * Max Correction: Poison Guard Absorption
     *   Maximum value of cut rate correction value for attack power against poison (set as special effect parameter) */
    float poisonGuardResist_MaxCorrect;

    /* 疫病耐性カット率_最大補正値
     *   疫病に対する攻撃力（特殊効果パラメータに設定）のカット率補正値の最大値
     * Max Correction: Scarlet Rot Guard Absorption
     *   Maximum value of cut rate correction value for attack power against plague (set as special effect parameter) */
    float diseaseGuardResist_MaxCorrect;

    /* 出血耐性カット率_最大補正値
     *   出血に対する攻撃力（特殊効果パラメータに設定）のカット率補正値の最大値
     * Max Correction: Hemorrhage Guard Absorption
     *   Maximum value of cut rate correction value for attack power against bleeding (set as special effect parameter) */
    float bloodGuardResist_MaxCorrect;

    /* 呪耐性カット率_最大補正値
     *   呪いに対する攻撃力（特殊効果パラメータに設定）のカット率補正値の最大値
     * Max Correction: Blight Guard Absorption
     *   Maximum value of cut rate correction value for attack power against curse (set as special effect parameter) */
    float curseGuardResist_MaxCorrect;

    /* 冷気耐性カット率_最大補正値
     *   冷気に対する攻撃力（特殊効果パラメータに設定）のカット率補正値の最大値
     * Max Correction: Frostbite Guard Absorption
     *   Maximum value of cut rate correction value for attack power against cold air (set as special effect parameter) */
    float freezeGuardResist_MaxCorrect;

    /* ガード時スタミナ防御力_最大補正値
     *   ガード成功時に、敵のスタミナ攻撃に対する防御力の補正値の最大値
     * Max Correction: Guard Stability
     *   When the guard is successful, the maximum value of the defense power correction value against the enemy's stamina attack */
    float staminaGuardDef_MaxCorrect;

    /* 常駐SfxId１
     *   常駐SfxId1
     * Resident SFX [1]
     *   Resident SfxId1
     * Default Value  = -1 */
    int residentSfxId_1;

    /* 常駐SfxId２
     *   常駐SfxId2
     * Resident SFX [2]
     *   Resident SfxId2
     * Default Value  = -1 */
    int residentSfxId_2;

    /* 常駐SfxId３
     *   常駐SfxId3
     * Resident SFX [3]
     *   Resident SfxId3
     * Default Value  = -1 */
    int residentSfxId_3;

    /* 常駐SfxId４
     *   常駐SfxId4
     * Resident SFX [4]
     *   Resident SfxId4
     * Default Value  = -1 */
    int residentSfxId_4;

    /* 常駐SfxダミポリId１
     *   常駐SfxダミポリId１
     * Resident SFX - Dummy Poly [1]
     *   Resident Sfx Damipoli Id1
     * Default Value  = -1 */
    int residentSfx_DmyId_1;

    /* 常駐SfxダミポリId２
     *   常駐SfxダミポリId２
     * Resident SFX - Dummy Poly [2]
     *   Resident Sfx Damipoli Id2
     * Default Value  = -1 */
    int residentSfx_DmyId_2;

    /* 常駐SfxダミポリId３
     *   常駐SfxダミポリId３
     * Resident SFX - Dummy Poly [3]
     *   Resident Sfx Damipoli Id3
     * Default Value  = -1 */
    int residentSfx_DmyId_3;

    /* 常駐SfxダミポリId４
     *   常駐SfxダミポリId４
     * Resident SFX - Dummy Poly [4]
     *   Resident Sfx Damipoli Id4
     * Default Value  = -1 */
    int residentSfx_DmyId_4;

    /* スタミナ消費量倍率
     *   スタミナ消費量倍率
     * Stamina Consumption %
     *   Stamina consumption ratio
     * Default Value  = 1 */
    float staminaConsumptionRate;

    /* 対プレイヤー 物理ダメージ補正倍率
     *   プレイヤーに対する攻撃のみ、与えるダメージを補正する。
     * Vs. Player - Physical Damage %
     *   Only attacks on the player will correct the damage done.
     * Default Value  = 1 */
    float vsPlayerDmgCorrectRate_Physics;

    /* 対プレイヤー 魔法ダメージ補正倍率
     *   プレイヤーに対する攻撃のみ、与えるダメージを補正する。
     * Vs. Player - Magic Damage %
     *   Only attacks on the player will correct the damage done.
     * Default Value  = 1 */
    float vsPlayerDmgCorrectRate_Magic;

    /* 対プレイヤー 炎ダメージ補正倍率
     *   プレイヤーに対する攻撃のみ、与えるダメージを補正する。
     * Vs. Player - Fire Damage %
     *   Only attacks on the player will correct the damage done.
     * Default Value  = 1 */
    float vsPlayerDmgCorrectRate_Fire;

    /* 対プレイヤー 雷ダメージ補正倍率
     *   プレイヤーに対する攻撃のみ、与えるダメージを補正する。
     * Vs. Player - Lightning Damage %
     *   Only attacks on the player will correct the damage done.
     * Default Value  = 1 */
    float vsPlayerDmgCorrectRate_Thunder;

    /* 対プレイヤー 闇ダメージ補正倍率
     *   プレイヤーに対する攻撃のみ、与えるダメージを補正する。
     * Vs. Player - Holy Damage %
     *   Only attacks on the player will correct the damage done.
     * Default Value  = 1 */
    float vsPlayerDmgCorrectRate_Dark;

    /* 対プレイヤー 毒ダメージ補正倍率
     *   プレイヤーに対する攻撃のみ、与えるダメージを補正する。
     * Vs. Player - Poison Damage %
     *   Only attacks on the player will correct the damage done.
     * Default Value  = 1 */
    float vsPlayerDmgCorrectRate_Poison;

    /* 対プレイヤー 出血ダメージ補正倍率
     *   プレイヤーに対する攻撃のみ、与えるダメージを補正する。
     * Vs. Player - Hemorrhage Damage %
     *   Only attacks on the player will correct the damage done.
     * Default Value  = 1 */
    float vsPlayerDmgCorrectRate_Blood;

    /* 対プレイヤー 冷気ダメージ補正倍率
     *   プレイヤーに対する攻撃のみ、与えるダメージを補正する。
     * Vs. Player - Frostbite Damage %
     *   Only attacks on the player will correct the damage done.
     * Default Value  = 1 */
    float vsPlayerDmgCorrectRate_Freeze;

    /* 武器能力解放ステータス値：筋力
     *   特定の武器を使った際、ステータスがX以上だとR2攻撃が特殊なアクションに変わるようするためのもの
     * Unique R2 Attack - STR Requirement
     *   To change the R2 attack into a special action when the status is X or higher when using a specific weapon.
     * Default Value  = -1 */
    int attainmentWepStatusStr;

    /* 武器能力解放ステータス値：技量
     *   特定の武器を使った際、ステータスがX以上だとR2攻撃が特殊なアクションに変わるようするためのもの
     * Unique R2 Attack - DEX Requirement
     *   To change the R2 attack into a special action when the status is X or higher when using a specific weapon.
     * Default Value  = -1 */
    int attainmentWepStatusDex;

    /* 武器能力解放ステータス値：理力
     *   特定の武器を使った際、ステータスがX以上だとR2攻撃が特殊なアクションに変わるようするためのもの
     * Unique R2 Attack - INT Requirement
     *   To change the R2 attack into a special action when the status is X or higher when using a specific weapon.
     * Default Value  = -1 */
    int attainmentWepStatusMag;

    /* 武器能力解放ステータス値：信仰
     *   特定の武器を使った際、ステータスがX以上だとR2攻撃が特殊なアクションに変わるようするためのもの
     * Unique R2 Attack - FTH Requirement
     *   This is to change the R2 attack into a special action when the status is X or higher when using a specific weapon.
     * Default Value  = -1 */
    int attainmentWepStatusFai;

    /* 武器能力解放ステータス値：運
     *   特定の武器を使った際、ステータスがX以上だとR2攻撃が特殊なアクションに変わるようするためのもの
     * Unique R2 Attack - ARC Requirement
     *   This is to change the R2 attack into a special action when the status is X or higher when using a specific weapon.
     * Default Value  = -1 */
    int attainmentWepStatusLuc;

    /* 攻撃属性補正ID
     *   攻撃属性を補正するパラメータのID
     * Attack Element Correct ID
     *   ID of the parameter that corrects the attack attribute */
    int attackElementCorrectId;

    /* 販売価格
     *   販売価格
     * Sale Value
     *   Selling price
     * Default Value  = -1 */
    int saleValue;

    /* 強化ショップカテゴリ
     *   強化ショップカテゴリ
     * Reinforcement Menu Type
     *   Enhanced shop category */
    unsigned char reinforceShopCategory;

    /* 矢の最大所持数
     *   矢の最大所持数
     * Max Ammunition Held
     *   Maximum number of arrows
     * Default Value  = 1 */
    unsigned char maxArrowQuantity;

    /* 常駐SFX1納刀時表示するか
     *   「常駐SFX1納刀時表示するか」がtrueの場合、武器が納刀された時に「常駐SFXID1」に設定されているSFXを非表示にする
     * Hide Resident SFX [1] when Sheathed
     *   If Do you want to display when resident SFX1 is delivered? Is true, hide the SFX set to resident SFX ID1 when the weapon is delivered. */
    unsigned char residentSfx_1_IsVisibleForHang:1;

    /* 常駐SFX2納刀時表示するか
     *   「常駐SFX2納刀時表示するか」がtrueの場合、武器が納刀された時に「常駐SFXID2」に設定されているSFXを非表示にする
     * Hide Resident SFX [2] when Sheathed
     *   If Do you want to display when resident SFX2 is delivered? Is true, hide the SFX set to resident SFX ID2 when the weapon is delivered. */
    unsigned char residentSfx_2_IsVisibleForHang:1;

    /* 常駐SFX3納刀時表示するか
     *   「常駐SFX3納刀時表示するか」がtrueの場合、武器が納刀された時に「常駐SFXID3」に設定されているSFXを非表示にする
     * Hide Resident SFX [3] when Sheathed
     *   If Do you want to display when resident SFX3 is delivered? Is true, hide the SFX set to resident SFX ID3 when the weapon is delivered. */
    unsigned char residentSfx_3_IsVisibleForHang:1;

    /* 常駐SFX4納刀時表示するか
     *   「常駐SFX4納刀時表示するか」がtrueの場合、武器が納刀された時に「常駐SFXID4」に設定されているSFXを非表示にする
     * Hide Resident SFX [4] when Sheathed
     *   If Do you want to display when resident SFX4 is delivered? Is true, hide the SFX set to resident SFX ID 4 when the weapon is delivered. */
    unsigned char residentSfx_4_IsVisibleForHang:1;

    /* モデル_0 ソウルパラムID差し替え可能か
     *   vfxパラメータの「武器エンチャント用ソウルパラムID」と「武器エンチャント用インビジブルウェポンか」設定が適応されるか
     * Apply Weapon VFX Parameters [0]
     *   Whether the vfx parameter Soul Param ID for Weapon Enchantment and Invisible Weapon for Weapon Enchantment settings are applied
     * Default Value  = 1 */
    unsigned char isSoulParamIdChange_model0:1;

    /* モデル_1 ソウルパラムID差し替え可能か
     *   vfxパラメータの「武器エンチャント用ソウルパラムID」と「武器エンチャント用インビジブルウェポンか」設定が適応されるか
     * Apply Weapon VFX Parameters [1]
     *   Whether the vfx parameter Soul Param ID for Weapon Enchantment and Invisible Weapon for Weapon Enchantment settings are applied
     * Default Value  = 1 */
    unsigned char isSoulParamIdChange_model1:1;

    /* モデル_2 ソウルパラムID差し替え可能か
     *   vfxパラメータの「武器エンチャント用ソウルパラムID」と「武器エンチャント用インビジブルウェポンか」設定が適応されるか
     * Apply Weapon VFX Parameters [2]
     *   Whether the vfx parameter Soul Param ID for Weapon Enchantment and Invisible Weapon for Weapon Enchantment settings are applied
     * Default Value  = 1 */
    unsigned char isSoulParamIdChange_model2:1;

    /* モデル_3 ソウルパラムID差し替え可能か
     *   vfxパラメータの「武器エンチャント用ソウルパラムID」と「武器エンチャント用インビジブルウェポンか」設定が適応されるか
     * Apply Weapon VFX Parameters [3]
     *   Whether the vfx parameter Soul Param ID for Weapon Enchantment and Invisible Weapon for Weapon Enchantment settings are applied
     * Default Value  = 1 */
    unsigned char isSoulParamIdChange_model3:1;

    /* 武器SEIDオフセット値
     *   SEIDのオフセット値 
     * Weapon SE ID Offset
     *   SEID offset value */
    char wepSeIdOffset;

    /* 進化価格
     *   進化価格
     * Affinity Price
     *   Evolution price */
    int baseChangePrice;

    /* レベルシンク補正ID
     *   レベルシンク補正ID
     * Level Sync Correction ID
     *   Level sync correction ID
     * Default Value  = -1 */
    short levelSyncCorrectId;

    /* 補正タイプ（睡眠攻撃力）
     *   一次パラメータによる睡眠攻撃力の補正グラフのタイプを決める
     * Correction Type: Sleep
     *   Determine the type of sleep attack correction graph with primary parameters */
    unsigned char correctType_Sleep;

    /* 補正タイプ（発狂攻撃力）
     *   一次パラメータによる発狂攻撃力の補正グラフのタイプを決める
     * Correction Type: Mandesss
     *   Determining the type of mad attack power correction graph with primary parameters */
    unsigned char correctType_Madness;

    /* レア度
     *   アイテム取得ログで使うレア度
     * Rarity
     *   Rarity used in item acquisition logs */
    unsigned char rarity;

    /* 魔石装着可能か
     *   魔石装着可能か
     * Ash of War Type
     *   Is it possible to attach magic stones? */
    unsigned char gemMountType;

    /* 武器リゲイン量
     *   武器リゲイン量
     * Weapon Regain HP Amount
     *   Weapon regain amount */
    unsigned short wepRegainHp;

    /* 効果テキストID00
     *   効果テキストID00(Weapon_Effect)。ステータスに表示する武器固有効果のテキスト
     * SpEffect Message ID [0]
     *   Effect text ID 00 (Weapon_Effect). Weapon-specific effect text to display in status
     * Default Value  = -1 */
    int spEffectMsgId0;

    /* 効果テキストID01
     *   効果テキストID01(Weapon_Effect)。ステータスに表示する武器固有効果のテキスト
     * SpEffect Message ID [1]
     *   Effect text ID 01 (Weapon_Effect). Weapon-specific effect text to display in status
     * Default Value  = -1 */
    int spEffectMsgId1;

    /* 効果テキストID02
     *   効果テキストID02(Weapon_Effect)。ステータスに表示する武器固有効果のテキスト
     * SpEffect Message ID [2]
     *   Effect text ID 02 (Weapon_Effect). Weapon-specific effect text to display in status
     * Default Value  = -1 */
    int spEffectMsgId2;

    /* 派生元 強化+16
     *   この武器の強化元武器ID16
     * Origin Weapon +16
     *   This weapon's enhancement source weapon ID 16
     * Default Value  = -1 */
    int originEquipWep16;

    /* 派生元 強化+17
     *   この武器の強化元武器ID17
     * Origin Weapon +17
     *   This weapon's enhancement source weapon ID 17
     * Default Value  = -1 */
    int originEquipWep17;

    /* 派生元 強化+18
     *   この武器の強化元武器ID18
     * Origin Weapon +18
     *   This weapon's enhancement source weapon ID18
     * Default Value  = -1 */
    int originEquipWep18;

    /* 派生元 強化+19
     *   この武器の強化元武器ID19
     * Origin Weapon +19
     *   This weapon's enhancement source weapon ID 19
     * Default Value  = -1 */
    int originEquipWep19;

    /* 派生元 強化+20
     *   この武器の強化元武器ID20
     * Origin Weapon +20
     *   This weapon's enhancement source weapon ID 20
     * Default Value  = -1 */
    int originEquipWep20;

    /* 派生元 強化+21
     *   この武器の強化元武器ID21
     * Origin Weapon +21
     *   This weapon's enhancement source weapon ID21
     * Default Value  = -1 */
    int originEquipWep21;

    /* 派生元 強化+22
     *   この武器の強化元武器ID22
     * Origin Weapon +22
     *   This weapon's enhancement source weapon ID 22
     * Default Value  = -1 */
    int originEquipWep22;

    /* 派生元 強化+23
     *   この武器の強化元武器ID23
     * Origin Weapon +23
     *   This weapon's enhancement source weapon ID 23
     * Default Value  = -1 */
    int originEquipWep23;

    /* 派生元 強化+24
     *   この武器の強化元武器ID24
     * Origin Weapon +24
     *   This weapon's enhancement source weapon ID 24
     * Default Value  = -1 */
    int originEquipWep24;

    /* 派生元 強化+25
     *   この武器の強化元武器ID25
     * Origin Weapon +25
     *   This weapon's enhancement source weapon ID 25
     * Default Value  = -1 */
    int originEquipWep25;

    /* 対プレイヤー 睡眠ダメージ補正倍率
     *   プレイヤーに対する攻撃のみ、与えるダメージを補正する。
     * Vs. Player - Sleep Damage %
     *   Only attacks on the player will correct the damage done.
     * Default Value  = 1 */
    float vsPlayerDmgCorrectRate_Sleep;

    /* 対プレイヤー 発狂ダメージ補正倍率
     *   プレイヤーに対する攻撃のみ、与えるダメージを補正する。
     * Vs. Player - Madness Damage %
     *   Only attacks on the player will correct the damage done.
     * Default Value  = 1 */
    float vsPlayerDmgCorrectRate_Madness;

    /* ガード時SA攻撃カット率
     *   ガード成功時のSAダメージのカット率
     * Poise Damage - Guard Absorption
     *   SA damage cut rate when guard is successful */
    float saGuardCutRate;

    /* 防御材質バリエーション値
     *   ガード時に使用される防御材質と組み合わせてダメージSFX,SEのバリエーション分けに使用する値です。SEQ16473
     * Defence Material - Variation Value
     *   It is a value used to divide the damage SFX and SE into variations in combination with the defense material used when guarding. SEQ16473 */
    unsigned char defMaterialVariationValue;

    /* 特殊属性バリエーション値
     *   武器の特殊属性と組み合わせて状態異常SFX,SEなどにバリエーションを持たせるために使用する値です。SEQ16473
     * Special Attribute - Variation Value
     *   It is a value used to give variation to abnormal state SFX, SE, etc. in combination with the special attribute of the weapon. SEQ16473 */
    unsigned char spAttributeVariationValue;

    /* ステルス攻撃力倍率
     *   ステルス攻撃力倍率
     * Stealth Attack Multiplier
     *   Stealth attack power multiplier */
    short stealthAtkRate;

    /* 対プレイヤー 疫病ダメージ補正倍率
     *   プレイヤーに対する攻撃のみ、与えるダメージを補正する。
     * Vs. Player - Scarlet Rot Damage %
     *   Only attacks on the player will correct the damage done.
     * Default Value  = 1 */
    float vsPlayerDmgCorrectRate_Disease;

    /* 対プレイヤー 呪ダメージ補正倍率
     *   プレイヤーに対する攻撃のみ、与えるダメージを補正する。
     * Vs. Player - Blight Damage %
     *   Only attacks on the player will correct the damage done.
     * Default Value  = 1 */
    float vsPlayerDmgCorrectRate_Curse;

    /* Restrict Special Ashes of War
     *   If set to true, then ashes of war in EquipParamGem with isSpecialSwordArt set to 1 cannot be applied to this weapon. */
    unsigned char restrictSpecialSwordArt;

    char pad[7];
} equip_param_weapon_t;
