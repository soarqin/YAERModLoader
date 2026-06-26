#pragma once

/* Defines all types of equippable Armor, including no armor. Responsible for model masks. */
typedef struct er_equip_param_protector_s {
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

    /* ソートID
     *   ソートID(プログラム内で強化レベルを加味しているので s32 では７桁が限界)
     * Sort ID
     *   Sort ID (7 digits is the limit for s32 because the enhancement level is added in the program) */
    int sortId;

    /* 徘徊装備ID
     *   徘徊ゴースト用の差し替え装備ID.
     * Wandering Equip ID
     *   Replacement equipment ID for wandering ghosts. */
    unsigned int wanderingEquipId;

    /* 睡眠耐性
     *   睡眠状態異常へのかかりにくさ
     * Resist - Sleep
     *   Difficulty in getting sleep abnormalities */
    unsigned short resistSleep;

    /* 発狂耐性
     *   発狂状態異常へのかかりにくさ
     * Resist - Madness
     *   Difficulty in getting mad */
    unsigned short resistMadness;

    /* SA耐久値
     *   スーパーアーマー耐久力
     * Poise Durability
     *   Super armor endurance */
    float saDurability;

    /* 強靭度 補正倍率
     *   強靭度の基本値を補正する倍率です
     * Toughness Correction
     *   It is a magnification that corrects the basic value of toughness. */
    float toughnessCorrectRate;

    /* 修理価格
     *   修理基本価格
     * Repair Price
     *   Basic repair price */
    int fixPrice;

    /* 基本価格
     *   基本価格
     * Basic Price
     *   Basic price */
    int basicPrice;

    /* 売却価格
     *   販売価格
     * Sell Value
     *   Selling price */
    int sellValue;

    /* 重量[kg]
     *   重量[kg].
     * Weight
     *   Weight [kg].
     * Default Value  = 1 */
    float weight;

    /* 常駐特殊効果ID1
     *   常駐特殊効果ID1
     * Resident SpEffect ID [1]
     *   Resident special effect ID1 */
    int residentSpEffectId;

    /* 常駐特殊効果ID2
     *   常駐特殊効果ID2
     * Resident SpEffect ID [2]
     *   Resident special effect ID2 */
    int residentSpEffectId2;

    /* 常駐特殊効果ID3
     *   常駐特殊効果ID3
     * Resident SpEffect ID [3]
     *   Resident special effect ID3 */
    int residentSpEffectId3;

    /* 素材ID
     *   武器強化に必要な素材パラメータID
     * Upgrade Material ID
     *   Material parameter ID required for weapon enhancement
     * Default Value  = -1 */
    int materialSetId;

    /* 部位ダメージ率
     *   部位ダメージ率
     * Weak Parts Damage %
     *   Part damage rate
     * Default Value  = 1 */
    float partsDamageRate;

    /* SA回復時間補正値
     *   スーパーアーマー回復時間の補正値
     * Poise Recovery Correction
     *   Super Armor Recovery Time Correction Value */
    float corectSARecover;

    /* 派生元
     *   この防具の強化元防具ID
     * Origin Armor +0
     *   Strengthening of this armor Original armor ID
     * Default Value  = -1 */
    int originEquipPro;

    /* 派生元 強化+1
     *   この防具の強化元防具ID1
     * Origin Armor +1
     *   Strengthening this armor Original armor ID1
     * Default Value  = -1 */
    int originEquipPro1;

    /* 派生元 強化+2
     *   この防具の強化元防具ID2
     * Origin Armor +2
     *   Strengthening this armor Original armor ID2
     * Default Value  = -1 */
    int originEquipPro2;

    /* 派生元 強化+3
     *   この防具の強化元防具ID3
     * Origin Armor +3
     *   Strengthening this armor Original armor ID3
     * Default Value  = -1 */
    int originEquipPro3;

    /* 派生元 強化+4
     *   この防具の強化元防具ID4
     * Origin Armor +4
     *   Strengthening this armor Original armor ID4
     * Default Value  = -1 */
    int originEquipPro4;

    /* 派生元 強化+5
     *   この防具の強化元防具ID5
     * Origin Armor +5
     *   Strengthening this armor Original armor ID5
     * Default Value  = -1 */
    int originEquipPro5;

    /* 派生元 強化+6
     *   この防具の強化元防具ID6
     * Origin Armor +6
     *   Strengthening this armor Original armor ID6
     * Default Value  = -1 */
    int originEquipPro6;

    /* 派生元 強化+7
     *   この防具の強化元防具ID7
     * Origin Armor +7
     *   Strengthening this armor Original armor ID7
     * Default Value  = -1 */
    int originEquipPro7;

    /* 派生元 強化+8
     *   この防具の強化元防具ID8
     * Origin Armor +8
     *   Strengthening this armor Original armor ID8
     * Default Value  = -1 */
    int originEquipPro8;

    /* 派生元 強化+9
     *   この防具の強化元防具ID9
     * Origin Armor +9
     *   Strengthening this armor Original armor ID9
     * Default Value  = -1 */
    int originEquipPro9;

    /* 派生元 強化+10
     *   この防具の強化元防具ID10
     * Origin Armor +10
     *   Strengthening this armor Original armor ID10
     * Default Value  = -1 */
    int originEquipPro10;

    /* 派生元 強化+11
     *   この防具の強化元防具ID11
     * Origin Armor +11
     *   Strengthening this armor Original armor ID11
     * Default Value  = -1 */
    int originEquipPro11;

    /* 派生元 強化+12
     *   この防具の強化元防具ID12
     * Origin Armor +12
     *   Strengthening this armor Original armor ID12
     * Default Value  = -1 */
    int originEquipPro12;

    /* 派生元 強化+13
     *   この防具の強化元防具ID13
     * Origin Armor +13
     *   Strengthening this armor Original armor ID13
     * Default Value  = -1 */
    int originEquipPro13;

    /* 派生元 強化+14
     *   この防具の強化元防具ID14
     * Origin Armor +14
     *   Strengthening this armor Original armor ID14
     * Default Value  = -1 */
    int originEquipPro14;

    /* 派生元 強化+15
     *   この防具の強化元防具ID15
     * Origin Armor +15
     *   Strengthening this armor Original armor ID15
     * Default Value  = -1 */
    int originEquipPro15;

    /* 男横顔拡大スケール
     * Facescale - Male - Scale X
     * Default Value  = 1 */
    float faceScaleM_ScaleX;

    /* 男前顔拡大スケール
     * Facescale - Male - Scale Z
     * Default Value  = 1 */
    float faceScaleM_ScaleZ;

    /* 男横顔拡大最大倍率
     * Facescale - Male - Max X
     * Default Value  = 1 */
    float faceScaleM_MaxX;

    /* 男前顔拡大最大倍率
     * Facescale - Male - Max Z
     * Default Value  = 1 */
    float faceScaleM_MaxZ;

    /* 女横顔拡大スケール
     * Facescale - Female - Scale X
     * Default Value  = 1 */
    float faceScaleF_ScaleX;

    /* 女前顔拡大スケール
     * Facescale - Female - Scale Z
     * Default Value  = 1 */
    float faceScaleF_ScaleZ;

    /* 女横顔拡大最大倍率
     * Facescale - Female - Max X
     * Default Value  = 1 */
    float faceScaleF_MaxX;

    /* 女前顔拡大最大倍率
     * Facescale - Female - Max Z
     * Default Value  = 1 */
    float faceScaleF_MaxZ;

    /* QWCID
     *   QWCのパラメタID
     * QWC ID
     *   QWC parameter ID
     * Default Value  = -1 */
    int qwcId;

    /* 装備モデル番号
     *   装備モデルの番号.
     * Equip Model ID
     *   Equipment model number. */
    unsigned short equipModelId;

    /* 男用アイコンID
     *   男用メニューアイコンID.
     * Icon ID - Male
     *   Men's menu icon ID. */
    unsigned short iconIdM;

    /* 女用アイコンID
     *   女用メニューアイコンID.
     * Icon ID - Female
     *   Women's menu icon ID. */
    unsigned short iconIdF;

    /* ノックバックカット率
     *   ノックバックの減少値.
     * Knockback
     *   Knockback reduction value. */
    unsigned short knockBack;

    /* ノックバック反発率
     *   ノックバックの反発率.
     * Knockback Bounce Rate
     *   Knockback repulsion rate. */
    unsigned short knockbackBounceRate;

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

    /* pad */
    char pad03[2];

    /* はじき防御力
     *   敵の攻撃のはじき返し判定に利用.
     * Weapon Repel Power
     *   Used to determine the repulsion of enemy attacks. */
    unsigned short defFlickPower;

    /* 物理防御力
     *   物理攻撃のダメージ防御.
     * Defence - Physical
     *   Physical attack damage protection.
     * Default Value  = 100 */
    unsigned short defensePhysics;

    /* 魔法防御力
     *   魔法攻撃のダメージ防御.
     * Defence - Magic
     *   Magic attack damage protection.
     * Default Value  = 100 */
    unsigned short defenseMagic;

    /* 炎防御力
     *   炎攻撃のダメージ防御.
     * Defence - Fire
     *   Fire attack damage protection.
     * Default Value  = 100 */
    unsigned short defenseFire;

    /* 電撃防御力
     *   電撃攻撃のダメージ防御.
     * Defence - Lightning
     *   Damage protection for electric shock attacks.
     * Default Value  = 100 */
    unsigned short defenseThunder;

    /* 斬撃防御力
     *   攻撃タイプを見て、斬撃属性のときは、防御力を減少させる
     * Defence - Slash
     *   Look at the attack type, and if it is a slashing attribute, reduce the defense power */
    short defenseSlash;

    /* 打撃防御力
     *   攻撃属性を見て、打撃属性のときは、防御力を減少させる.
     * Defence - Strike
     *   Look at the attack attribute, and if it is a hit attribute, reduce the defense power. */
    short defenseBlow;

    /* 刺突防御力
     *   攻撃属性を見て、打撃属性のときは、防御力を減少させる.
     * Defence - Thrust
     *   Look at the attack attribute, and if it is a hit attribute, reduce the defense power. */
    short defenseThrust;

    /* 毒耐性
     *   毒状態異常へのかかりにくさ
     * Resist - Poison
     *   Difficulty in getting poisonous
     * Default Value  = 100 */
    unsigned short resistPoison;

    /* 疫病耐性
     *   疫病状態異常へのかかりにくさ
     * Resist - Scarlet Rot
     *   Difficulty in getting sick
     * Default Value  = 100 */
    unsigned short resistDisease;

    /* 出血耐性
     *   出血状態異常へのかかりにくさ
     * Resist - Hemorrhage
     *   Difficulty in getting bleeding abnormalities
     * Default Value  = 100 */
    unsigned short resistBlood;

    /* 呪耐性
     *   呪い状態異常へのかかりにくさ
     * Resist - Blight
     *   Difficulty in getting a curse condition
     * Default Value  = 100 */
    unsigned short resistCurse;

    /* 強化タイプID
     *   強化タイプID
     * Reinforce Type ID
     *   Enhanced type ID */
    short reinforceTypeId;

    /* トロフィー
     *   トロフィーシステムに関係あるか？
     * Achievement ID
     *   Is it related to the trophy system?
     * Default Value  = -1 */
    short trophySGradeId;

    /* ショップレベル
     *   お店で販売できるレベル
     * Shop Level
     *   Level that can be sold at the store */
    short shopLv;

    /* ノックバックパラメータID
     *   ノックバックで使用するパラメータのID
     * Knockback Param ID
     *   ID of the parameter used for knockback */
    unsigned char knockbackParamId;

    /* はじき時ダメージ減衰率[%]
     *   はじき時のダメージ減衰率に使用
     * Weapon Repel Damage %
     *   Used for damage attenuation rate when repelling */
    unsigned char flickDamageCutRate;

    /* 装備モデル種別
     *   装備モデルの種別.
     * Equip Model Category
     *   Equipment model type.
     * Default Value  = 1 */
    unsigned char equipModelCategory;

    /* 装備モデル性別
     *   装備モデルの性別.
     * Equip Model Gender
     *   Gender of equipment model. */
    unsigned char equipModelGender;

    /* 防具カテゴリ
     *   防具のカテゴリ.
     * Armor Category
     *   Armor category. */
    unsigned char protectorCategory;

    /* レア度
     *   アイテム取得ログで使うレア度
     * Rarity
     *   Rarity used in item acquisition logs */
    unsigned char rarity;

    /* ソートアイテム種別ID
     *   ソートアイテム種別ID。ソート「アイテム種別順」にて、同じIDは同じグループとしてまとめて表示されます
     * Sort Group ID
     *   Sort item type ID. In the sort Item type order, the same ID is displayed together as the same group.
     * Default Value  = 255 */
    unsigned char sortGroupId;

    /* 部位ダメージ適用攻撃
     *   部位ダメージ判定を行う攻撃タイプを設定
     * Parts Damage Type
     *   Set the attack type to judge the part damage */
    unsigned char partsDmgType;

    /* パディング */
    char pad04[2];

    /* 預けれるか
     *   倉庫に預けれるか
     * Can Deposit
     *   Can you leave it in the warehouse? */
    unsigned char isDeposit:1;

    /* 頭装備
     *   頭装備か.
     * Is Head Equipment
     *   Is it head equipment? */
    unsigned char headEquip:1;

    /* 胴装備
     *   胴装備か.
     * Is Body Equipment
     *   Is it torso equipment? */
    unsigned char bodyEquip:1;

    /* 腕装備
     *   腕装備か.
     * Is Arm Equipment
     *   Is it arm equipment? */
    unsigned char armEquip:1;

    /* 脚装備
     *   脚装備か.
     * Is Leg Equipment
     *   Is it leg equipment? */
    unsigned char legEquip:1;

    /* 顔スケールを使用するか
     *   顔スケールを使用するか
     * Use Facescale
     *   Whether to use a face scale */
    unsigned char useFaceScale:1;

    /* 弱点アニメをスキップするか
     *   弱点ダメージアニメ再生をスキップするかどうか。アニメを再生しないだけで「部位ダメージ率」「防御材質」は弱点として扱われます。
     * Skip Weak Damage Anim
     *   Weakness damage Whether to skip animation playback. Part damage rate and defense material are treated as weak points just by not playing the animation. */
    unsigned char isSkipWeakDamageAnim:1;

    /* パディング */
    char pad06:1;

    /* 弱点防御材質バリエーション値
     *   弱点防御材質と組み合わせて状態異常、ダメージSFX,SEのバリエーション分けに使用する値です。SEQ16473
     * Defence Material - Variation Value - Weak
     *   It is a value used for variation of abnormal condition, damage SFX, SE in combination with weak point defense material. SEQ16473 */
    unsigned char defenseMaterialVariationValue_Weak;

    /* フットデカール識別子2
     *   自動フットエフェクトのデカールID。床材質も考慮される。防具カテゴリ」が「脚」のときのみ利用される。
     * Auto Foot Effect Decal Base ID [2]
     *   Decal ID for automatic foot effects. Floor material is also considered. Only used when the armor category is legs.
     * Default Value  = -1 */
    short autoFootEffectDecalBaseId2;

    /* フットデカール識別子3
     *   自動フットエフェクトのデカールID。床材質も考慮される。防具カテゴリ」が「脚」のときのみ利用される。
     * Auto Foot Effect Decal Base ID [3]
     *   Decal ID for automatic foot effects. Floor material is also considered. Only used when the armor category is legs.
     * Default Value  = -1 */
    short autoFootEffectDecalBaseId3;

    /* 防御材質バリエーション値
     *   防御材質と組み合わせて状態異常、ダメージSFX,SEのバリエーション分けに使用する値です。SEQ16473
     * Defence Material - Variation Value
     *   It is a value used in combination with the defense material to classify abnormal conditions, damage SFX, and SE. SEQ16473 */
    unsigned char defenseMaterialVariationValue;

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

    /* マルチドロップ共有禁止か
     *   マルチドロップ共有禁止か
     * Cannot Drop in Multiplayer
     *   Is multi-drop sharing prohibited? */
    unsigned char disableMultiDropShare:1;

    /* DLC用シンプルモデルありか
     *   ＤＬＣ用シンプルモデルが存在しているか
     * Simple Model for DLC1
     *   Is there a simple model for DLC? */
    unsigned char simpleModelForDlc:1;

    /* 取得ログ表示条件
     *   アイテム取得時にアイテム取得ログに表示するか（未入力: ○）
     * Item Acquisition Log Condition Type
     *   Whether to display in the item acquisition log when acquiring the item (not entered: )
     * Default Value  = 1 */
    unsigned char showLogCondType:1;

    /* 取得ダイアログ表示条件
     *   アイテム取得時にアイテム取得ダイアログに表示するか（未入力: newのみ）
     * Item Acquisition Dialog Condition Type 
     *   Whether to display it in the item acquisition dialog when acquiring an item (not entered: new only)
     * Default Value  = 2 */
    unsigned char showDialogCondType:2;

    /* パディング */
    char pad:1;

    /* 無属性ダメージ倍率
     *   無属性ダメージ倍率
     * Absorption - Physical
     *   Non-attribute damage multiplier
     * Default Value  = 1 */
    float neutralDamageCutRate;

    /* 斬撃ダメージ倍率
     *   斬撃ダメージ倍率
     * Absorption - Slash
     *   Slash damage multiplier
     * Default Value  = 1 */
    float slashDamageCutRate;

    /* 打撃ダメージ倍率
     *   打撃ダメージ倍率
     * Absorption - Strike
     *   Batter damage multiplier
     * Default Value  = 1 */
    float blowDamageCutRate;

    /* 刺突ダメージ倍率
     *   刺突ダメージ倍率
     * Absorption - Thrust
     *   Puncture damage ratio
     * Default Value  = 1 */
    float thrustDamageCutRate;

    /* 魔法ダメージ倍率
     *   魔法ダメージ倍率
     * Absorption - Magic
     *   Magic damage multiplier
     * Default Value  = 1 */
    float magicDamageCutRate;

    /* 火炎ダメージ倍率
     *   火炎ダメージ倍率
     * Absorption - Fire
     *   Flame damage multiplier
     * Default Value  = 1 */
    float fireDamageCutRate;

    /* 電撃ダメージ倍率
     *   電撃ダメージ倍率
     * Absorption - Lightning
     *   Electric shock damage ratio
     * Default Value  = 1 */
    float thunderDamageCutRate;

    /* 防御材質1【SFX】
     *   移動/防御時のSFX用.1
     * Defence Material SFX [1]
     *   For SFX when moving / defending. 1
     * Default Value  = 50 */
    unsigned short defenseMaterialSfx1;

    /* 弱点防御材質1【SFX】
     *   弱点部位ダメージ時のSFX用1
     * Defence Material SFX - Weakness [1]
     *   For SFX when weak points are damaged 1
     * Default Value  = 50 */
    unsigned short defenseMaterialSfx_Weak1;

    /* 防御材質1【SE】
     *   移動/防御時のSE用.1
     * Defence Material - SE [1]
     *   For SE when moving / defending. 1
     * Default Value  = 50 */
    unsigned short defenseMaterial1;

    /* 弱点防御材質1【SE】
     *   弱点部位ダメージ時のSE用1
     * Defence Material SE - Weakness [1]
     *   For SE when weak points are damaged 1
     * Default Value  = 50 */
    unsigned short defenseMaterial_Weak1;

    /* 防御材質2【SFX】
     *   移動/防御時のSFX用.2
     * Defence Material SFX [2]
     *   For SFX when moving / defending. 2
     * Default Value  = 50 */
    unsigned short defenseMaterialSfx2;

    /* 弱点防御材質2【SFX】
     *   弱点部位ダメージ時のSFX用2
     * Defence Material SFX - Weakness [2]
     *   2 for SFX when weak points are damaged
     * Default Value  = 50 */
    unsigned short defenseMaterialSfx_Weak2;

    /* 足装備材質【SE】
     *   足装備SE用材質。足装備のみ参照される。(【GR】SEQ10061) 「139:なし」の場合は防御材質1【SE】が参照される
     * Foot Material SE
     *   Material for foot equipment SE. Only foot equipment is referenced. ([GR] SEQ10061) In the case of 139: None, the defense material 1 [SE] is referred to.
     * Default Value  = 139 */
    unsigned short footMaterialSe;

    /* 弱点防御材質2【SE】
     *   弱点部位ダメージ時のSE用2
     * Defence Material SE - Weakness [2]
     *   2 for SE when weak points are damaged
     * Default Value  = 50 */
    unsigned short defenseMaterial_Weak2;

    /* フットデカール識別子1
     *   自動フットエフェクトのデカールID。床材質も考慮される。防具カテゴリ」が「脚」のときのみ利用される。
     * Auto Foot Effect Decal Base ID [1]
     *   Decal ID for automatic foot effects. Floor material is also considered. Only used when the armor category is legs.
     * Default Value  = -1 */
    int autoFootEffectDecalBaseId1;

    /* 強靭度 被ダメージ倍率
     *   強靭度版カット率
     * Toughness Absorption
     *   Toughness version cut rate
     * Default Value  = 1 */
    float toughnessDamageCutRate;

    /* 強靭度 回復時間補正値
     *   強靭度の回復時間用の補正値
     * Toughness Recovery Correction
     *   Correction value for toughness recovery time */
    float toughnessRecoverCorrection;

    /* 闇ダメージ倍率
     *   闇ダメージ倍率
     * Absorption - Holy
     *   Dark damage multiplier
     * Default Value  = 1 */
    float darkDamageCutRate;

    /* 闇防御力
     *   闇攻撃のダメージ防御.
     * Defence - Holy
     *   Dark attack damage protection.
     * Default Value  = 100 */
    unsigned short defenseDark;

    /* PAD_元_#48#非表示
     *   元_#48#非表示 */
    char invisibleFlag48:1;

    /* PAD_元_#49#非表示
     *   元_#49#非表示 */
    char invisibleFlag49:1;

    /* PAD_元_#50#非表示
     *   元_#50#非表示 */
    char invisibleFlag50:1;

    /* PAD_元_#51#非表示
     *   元_#51#非表示 */
    char invisibleFlag51:1;

    /* PAD_元_#52#非表示
     *   元_#52#非表示 */
    char invisibleFlag52:1;

    /* PAD_元_#53#非表示
     *   元_#53#非表示 */
    char invisibleFlag53:1;

    /* PAD_元_#54#非表示
     *   元_#54#非表示 */
    char invisibleFlag54:1;

    /* PAD_元_#55#非表示
     *   元_#55#非表示 */
    char invisibleFlag55:1;

    /* PAD_元_#56#非表示
     *   元_#56#非表示 */
    char invisibleFlag56:1;

    /* PAD_元_#57#非表示
     *   元_#57#非表示 */
    char invisibleFlag57:1;

    /* PAD_元_#58#非表示
     *   元_#58#非表示 */
    char invisibleFlag58:1;

    /* PAD_元_#59#非表示
     *   元_#59#非表示 */
    char invisibleFlag59:1;

    /* PAD_元_#60#非表示
     *   元_#60#非表示 */
    char invisibleFlag60:1;

    /* PAD_元_#61#非表示
     *   元_#61#非表示 */
    char invisibleFlag61:1;

    /* PAD_元_#62#非表示
     *   元_#62#非表示 */
    char invisibleFlag62:1;

    /* PAD_元_#63#非表示
     *   元_#63#非表示 */
    char invisibleFlag63:1;

    /* PAD_元_#64#非表示
     *   元_#64#非表示 */
    char invisibleFlag64:1;

    /* PAD_元_#65#非表示
     *   元_#65#非表示 */
    char invisibleFlag65:1;

    /* PAD_元_#66#非表示
     *   元_#66#非表示 */
    char invisibleFlag66:1;

    /* PAD_元_#67#非表示
     *   元_#67#非表示 */
    char invisibleFlag67:1;

    /* PAD_元_#68#非表示
     *   元_#68#非表示 */
    char invisibleFlag68:1;

    /* PAD_元_#69#非表示
     *   元_#69#非表示 */
    char invisibleFlag69:1;

    /* PAD_元_#70#非表示
     *   元_#70#非表示 */
    char invisibleFlag70:1;

    /* PAD_元_#71#非表示
     *   元_#71#非表示 */
    char invisibleFlag71:1;

    /* PAD_元_#72#非表示
     *   元_#72#非表示 */
    char invisibleFlag72:1;

    /* PAD_元_#73#非表示
     *   元_#73#非表示 */
    char invisibleFlag73:1;

    /* PAD_元_#74#非表示
     *   元_#74#非表示 */
    char invisibleFlag74:1;

    /* PAD_元_#75#非表示
     *   元_#75#非表示 */
    char invisibleFlag75:1;

    /* PAD_元_#76#非表示
     *   元_#76#非表示 */
    char invisibleFlag76:1;

    /* PAD_元_#77#非表示
     *   元_#77#非表示 */
    char invisibleFlag77:1;

    /* PAD_元_#78#非表示
     *   元_#78#非表示 */
    char invisibleFlag78:1;

    /* PAD_元_#79#非表示
     *   元_#79#非表示 */
    char invisibleFlag79:1;

    /* PAD_元_#80#非表示
     *   元_#80#非表示 */
    char invisibleFlag80:1;

    /* パディング */
    char padbit:7;

    /* 姿勢制御ID(胴)
     *   姿勢制御ID(胴)
     * Posture Control ID
     *   Attitude control ID (torso) */
    unsigned char postureControlId;

    /* pad */
    char pad2[4];

    /* 販売価格
     *   販売価格
     * Shop Price
     *   Selling price
     * Default Value  = -1 */
    int saleValue;

    /* 冷気耐性
     *   冷気状態異常へのかかりにくさ
     * Resist - Frost
     *   Difficulty in getting cold air condition abnormal */
    unsigned short resistFreeze;

    /* #00#非表示(男女指定)
     *   前髪の先
     * Mask 00 - Upper face */
    unsigned char invisibleFlag_SexVer00;

    /* #01#非表示(男女指定)
     *   前髪の根元
     * Mask 01 - Chin */
    unsigned char invisibleFlag_SexVer01;

    /* #02#非表示(男女指定)
     *   もみあげ
     * Mask 02 - Nose and cheeks */
    unsigned char invisibleFlag_SexVer02;

    /* #03#非表示(男女指定)
     *   頭頂部
     * Mask 03 - Ears and top of head */
    unsigned char invisibleFlag_SexVer03;

    /* #04#非表示(男女指定)
     *   頭頂部
     * Mask 04 - Neck */
    unsigned char invisibleFlag_SexVer04;

    /* #05#非表示(男女指定)
     *   後ろ髪
     * Mask 05 - Lower neck */
    unsigned char invisibleFlag_SexVer05;

    /* #06#非表示(男女指定)
     *   後ろ髪の先
     * Mask 06 - Chest */
    unsigned char invisibleFlag_SexVer06;

    /* #07#非表示(男女指定)
     * Mask 07 - Upper elbows */
    unsigned char invisibleFlag_SexVer07;

    /* #08#非表示(男女指定)
     * Mask 08 - Shoulders */
    unsigned char invisibleFlag_SexVer08;

    /* #09#非表示(男女指定)
     * Mask 09 - Lower elbows */
    unsigned char invisibleFlag_SexVer09;

    /* #10#非表示(男女指定)
     *   襟
     * Mask 10 - Lower arms */
    unsigned char invisibleFlag_SexVer10;

    /* #11#非表示(男女指定)
     *   襟回り
     * Mask 11 - Right hand */
    unsigned char invisibleFlag_SexVer11;

    /* #12#非表示(男女指定)
     * Mask 12 - Waist */
    unsigned char invisibleFlag_SexVer12;

    /* #13#非表示(男女指定)
     * Mask 13 - Left hand */
    unsigned char invisibleFlag_SexVer13;

    /* #14#非表示(男女指定)
     * Mask 14 - Knees */
    unsigned char invisibleFlag_SexVer14;

    /* #15#非表示(男女指定)
     *   頭巾の裾
     * Mask 15 - Lower legs */
    unsigned char invisibleFlag_SexVer15;

    /* #16#非表示(男女指定)
     * Mask 16 - Feet */
    unsigned char invisibleFlag_SexVer16;

    /* #17#非表示(男女指定)
     * Mask 17 - Eyepatch */
    unsigned char invisibleFlag_SexVer17;

    /* #18#非表示(男女指定)
     * Mask 18 - Unknown
     *   Set on most gauntlets */
    unsigned char invisibleFlag_SexVer18;

    /* #19#非表示(男女指定)
     * Mask 19 - Unknown
     *   Set on most chests and legs */
    unsigned char invisibleFlag_SexVer19;

    /* #20#非表示(男女指定)
     *   袖A
     * Mask 20 - [ARMS] Long Gloves (Lower Arm) */
    unsigned char invisibleFlag_SexVer20;

    /* #21#非表示(男女指定)
     *   袖B
     * Mask 21 - [ARMS] Long Gloves (Full Length) */
    unsigned char invisibleFlag_SexVer21;

    /* #22#非表示(男女指定)
     * Mask 22 - Unknown
     *   Set on bare chest */
    unsigned char invisibleFlag_SexVer22;

    /* #23#非表示(男女指定)
     * Mask 23 - [BODY] Scarf / High Collar (Compressed) */
    unsigned char invisibleFlag_SexVer23;

    /* #24#非表示(男女指定)
     * Mask 24 - [BODY] Sleeves (Bunched to Elbow) */
    unsigned char invisibleFlag_SexVer24;

    /* #25#非表示(男女指定)
     *   腕
     * Mask 25 - [BODY] Sleeves (Bunched Midway) */
    unsigned char invisibleFlag_SexVer25;

    /* #26#非表示(男女指定)
     * Mask 26 - [BODY] Sleeves (Full) */
    unsigned char invisibleFlag_SexVer26;

    /* #27#非表示(男女指定)
     * Mask 27 - [BODY] Large Sleeves (Bunched to Elbow) */
    unsigned char invisibleFlag_SexVer27;

    /* #28#非表示(男女指定)
     * Mask 28 - [BODY] Large Sleeves (Full) */
    unsigned char invisibleFlag_SexVer28;

    /* #29#非表示(男女指定)
     * Mask 29 - [BODY] Sleeves (Wrist Bracelets) */
    unsigned char invisibleFlag_SexVer29;

    /* #30#非表示(男女指定)
     *   ベルト
     * Mask 30 - [BODY] Couter / Elbow Armor
     *   belt */
    unsigned char invisibleFlag_SexVer30;

    /* #31#非表示(男女指定)
     * Mask 31 - [BODY] Couter / Elbow Armor (Higher Up) */
    unsigned char invisibleFlag_SexVer31;

    /* #32#非表示(男女指定)
     * Mask 32 - [BODY] Small Collar */
    unsigned char invisibleFlag_SexVer32;

    /* #33#非表示(男女指定)
     * Mask 33 - [BODY] Small Collar (Compressed) */
    unsigned char invisibleFlag_SexVer33;

    /* #34#非表示(男女指定)
     * Mask 34 - [BODY] Scarf / High Collar (Full) */
    unsigned char invisibleFlag_SexVer34;

    /* #35#非表示(男女指定)
     * Mask 35 - [BODY] Lower Abdomen Cover */
    unsigned char invisibleFlag_SexVer35;

    /* #36#非表示(男女指定)
     * Mask 36 - [BODY] Small Hood (Down) */
    unsigned char invisibleFlag_SexVer36;

    /* #37#非表示(男女指定)
     * Mask 37 - [BODY] Small Hood (Up) */
    unsigned char invisibleFlag_SexVer37;

    /* #38#非表示(男女指定)
     * Mask 38 - [BODY] Left Pauldron / Shoulder */
    unsigned char invisibleFlag_SexVer38;

    /* #39#非表示(男女指定)
     * Mask 39 - [BODY] Right Pauldron / Shoulder */
    unsigned char invisibleFlag_SexVer39;

    /* #40#非表示(男女指定)
     * Mask 40 - [BODY] Cowl */
    unsigned char invisibleFlag_SexVer40;

    /* #41#非表示(男女指定)
     * Mask 41 - [BODY] Cowl (Long) */
    unsigned char invisibleFlag_SexVer41;

    /* #42#非表示(男女指定)
     * Mask 42 - [BODY] Cowl (Mid) */
    unsigned char invisibleFlag_SexVer42;

    /* #43#非表示(男女指定)
     * Mask 43 - [BODY] Cowl (Compressed) */
    unsigned char invisibleFlag_SexVer43;

    /* #44#非表示(男女指定)
     * Mask 44 - [HEAD] Gorget / Neckpiece */
    unsigned char invisibleFlag_SexVer44;

    /* #45#非表示(男女指定)
     * Mask 45 - [HEAD] Gorget / Neckpiece (Compressed) */
    unsigned char invisibleFlag_SexVer45;

    /* #46#非表示(男女指定)
     * Mask 46 - [HEAD] Long Hood / Plume (Low) */
    unsigned char invisibleFlag_SexVer46;

    /* #47#非表示(男女指定)
     * Mask 47 - [HEAD] Long Hood / Plume (Mid) */
    unsigned char invisibleFlag_SexVer47;

    /* #48#非表示(男女指定)
     * Mask 48 - [HEAD] Long Hood / Plume (High) */
    unsigned char invisibleFlag_SexVer48;

    /* #49#非表示(男女指定)
     * Mask 49 - [HEAD] Long Hood / Plume (Short) */
    unsigned char invisibleFlag_SexVer49;

    /* #50#非表示(男女指定)
     * Mask 50 - [LEGS] High Waistbelt */
    unsigned char invisibleFlag_SexVer50;

    /* #51#非表示(男女指定)
     * Mask 51 - [LEGS] Leggings */
    unsigned char invisibleFlag_SexVer51;

    /* #52#非表示(男女指定)
     * Mask 52 - [LEGS] Leggings (Compressed) */
    unsigned char invisibleFlag_SexVer52;

    /* #53#非表示(男女指定)
     * Mask 53 - [LEGS] Kneepads */
    unsigned char invisibleFlag_SexVer53;

    /* #54#非表示(男女指定)
     * Mask 54 - [LEGS] Kneepads (Compressed) */
    unsigned char invisibleFlag_SexVer54;

    /* #55#非表示(男女指定)
     * Mask 55 - [LEGS] Waistbelt */
    unsigned char invisibleFlag_SexVer55;

    /* #56#非表示(男女指定)
     * Mask 56 - [LEGS] Waistbelt (Compressed) */
    unsigned char invisibleFlag_SexVer56;

    /* #57#非表示(男女指定)
     * Mask 57 - [LEGS] Waistcloth */
    unsigned char invisibleFlag_SexVer57;

    /* #58#非表示(男女指定)
     * Mask 58 - [LEGS] Wiastcloth (Compressed) */
    unsigned char invisibleFlag_SexVer58;

    /* #59#非表示(男女指定)
     * Mask 59 - [LEGS] Pants Big Thighs */
    unsigned char invisibleFlag_SexVer59;

    /* #60#非表示(男女指定)
     * Mask 60 - Hair (Front) */
    unsigned char invisibleFlag_SexVer60;

    /* #61#非表示(男女指定)
     * Mask 61 - Hair (Forehead) */
    unsigned char invisibleFlag_SexVer61;

    /* #62#非表示(男女指定)
     * Mask 62 - Hair (Under Helmet) */
    unsigned char invisibleFlag_SexVer62;

    /* #63#非表示(男女指定)
     * Mask 63 - Hair (Over Headband) */
    unsigned char invisibleFlag_SexVer63;

    /* #64#非表示(男女指定)
     * Mask 64 - Hair (Full) */
    unsigned char invisibleFlag_SexVer64;

    /* #65#非表示(男女指定)
     * Mask 65 - Hair (Back of Head) */
    unsigned char invisibleFlag_SexVer65;

    /* #66#非表示(男女指定)
     * Mask 66 - Long Hair Braid / Tail (Low) */
    unsigned char invisibleFlag_SexVer66;

    /* #67#非表示(男女指定)
     * Mask 67 - Long Hair Braid / Tail (High) */
    unsigned char invisibleFlag_SexVer67;

    /* #68#非表示(男女指定)
     * Mask 68 - Long Hair Braid / Tail (Highest) */
    unsigned char invisibleFlag_SexVer68;

    /* #69#非表示(男女指定)
     * Mask 69 - Long Hair Braid / Tail (Lowest, Shortest) */
    unsigned char invisibleFlag_SexVer69;

    /* #70#非表示(男女指定)
     * Mask 70 - [HEAD] Gorget / Neckpiece (Large) */
    unsigned char invisibleFlag_SexVer70;

    /* #71#非表示(男女指定)
     * Mask 71 - [BODY] Long Shirt (Bunched up to Belt) */
    unsigned char invisibleFlag_SexVer71;

    /* #72#非表示(男女指定)
     * Mask 72 - [BODY] Long Shirt (Full Length over Waist) */
    unsigned char invisibleFlag_SexVer72;

    /* #73#非表示(男女指定)
     * Mask 73 - Bare Torso and Upper Arms */
    unsigned char invisibleFlag_SexVer73;

    /* #74#非表示(男女指定)
     * Mask 74 - [BODY] Gravekeeper Cloak Hood (Down) */
    unsigned char invisibleFlag_SexVer74;

    /* #75#非表示(男女指定)
     * Mask 75 - [BODY] Gravekeeper Cloak Hood (Up) */
    unsigned char invisibleFlag_SexVer75;

    /* #76#非表示(男女指定)
     * Mask 76 - Lower Neck Warp */
    unsigned char invisibleFlag_SexVer76;

    /* #77#非表示(男女指定)
     * Mask 77 - Unknown */
    unsigned char invisibleFlag_SexVer77;

    /* #78#非表示(男女指定)
     * Mask 78 - Beard Jaw */
    unsigned char invisibleFlag_SexVer78;

    /* #79#非表示(男女指定)
     * Mask 79 - Beard Chin */
    unsigned char invisibleFlag_SexVer79;

    /* #80#非表示(男女指定)
     * Mask 80 - Beard Stubble */
    unsigned char invisibleFlag_SexVer80;

    /* #81#非表示(男女指定)
     * Mask 81 - Unknown
     *   Used by chest armors */
    unsigned char invisibleFlag_SexVer81;

    /* #82#非表示(男女指定)
     * Mask 82 - Unknown
     *   Used by chest armors */
    unsigned char invisibleFlag_SexVer82;

    /* #83#非表示(男女指定)
     * Mask 83 - Unknown
     *   Used by chest armors */
    unsigned char invisibleFlag_SexVer83;

    /* #84#非表示(男女指定)
     * Mask 84 - Unknown
     *   Used by chest armors */
    unsigned char invisibleFlag_SexVer84;

    /* #85#非表示(男女指定)
     * Mask 85 - Unknown
     *   Used by chest armors */
    unsigned char invisibleFlag_SexVer85;

    /* #86#非表示(男女指定)
     * Mask 86 - Unknown
     *   Used by chest armors */
    unsigned char invisibleFlag_SexVer86;

    /* #87#非表示(男女指定)
     * Mask 87 - Unknown
     *   Used by chest armors */
    unsigned char invisibleFlag_SexVer87;

    /* #88#非表示(男女指定)
     * Mask 88 - Unknown
     *   Used by chest armors */
    unsigned char invisibleFlag_SexVer88;

    /* #89#非表示(男女指定)
     * Mask 89 - Unknown
     *   Used by chest armors */
    unsigned char invisibleFlag_SexVer89;

    /* #90#非表示(男女指定)
     * Mask 90 - Unknown
     *   Used by chest armors */
    unsigned char invisibleFlag_SexVer90;

    /* #91#非表示(男女指定)
     * Mask 91 - Unknown
     *   Used by chest armors */
    unsigned char invisibleFlag_SexVer91;

    /* #92#非表示(男女指定)
     * Mask 92 - Unknown
     *   Used by chest armors */
    unsigned char invisibleFlag_SexVer92;

    /* #93#非表示(男女指定)
     * Mask 93 - Unknown
     *   Used by chest armors */
    unsigned char invisibleFlag_SexVer93;

    /* #94#非表示(男女指定)
     * Mask 94 - Unknown
     *   Used by chest armors */
    unsigned char invisibleFlag_SexVer94;

    /* #95#非表示(男女指定)
     * Mask 95 - Unknown */
    unsigned char invisibleFlag_SexVer95;

    /* パディング
     *   パディング */
    char pad404[14];
} er_equip_param_protector_t;
