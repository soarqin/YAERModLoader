#pragma once

typedef struct player_common_param_s {
    /* プレイヤーの自動フットエフェクトのSFX識別子[3桁]
     *   自動フットエフェクトのSFXIDに使われる識別子です。XYYZZZのZZZにあたります。
     * Automatic Foot Effect SFX Identifier
     *   The identifier used for the SFX ID of the automatic foot effect. It corresponds to ZZZ of XYYZZZ. */
    int playerFootEffect_bySFX;

    /* 精密射撃時プレイヤー非表示フェード時間
     *   精密射撃時にプレイヤーを非表示にするときのフェード時間です。単位は秒
     * Precision Shoot - Player Model Fade Time
     *   The fade time when hiding the player during precision shooting. The unit is seconds */
    float snipeModeDrawAlpha_FadeTime;

    /* プレイヤー強靭度 回復時間補正値
     *   プレイヤーの強靭度回復時間の計算に使われる補正値です。
     * Toughness Recovery Correction
     *   A correction value used to calculate the player's toughness recovery time. */
    float toughnessRecoverCorrection;

    /* 魔法記憶スロット初期値
     *   魔法記憶スロット初期値
     * Base Memory Slot Count
     *   Magic memory slot initial value */
    unsigned char baseMagicSlotSize;

    /* タリスマン装備スロット初期値
     *   タリスマン装備スロット初期値
     * Base Talisman Slot Count
     *   Talisman equipment slot initial value */
    unsigned char baseAccSlotNum;

    /* 予約
     *   (dummy8) */
    char reserved02[2];

    /* ドロップアイテム取得アニメーションID
     *   ドロップアイテムを拾った時のアニメーションID
     * Item Pick-up - Animation ID
     *   Animation ID when picking up a drop item */
    int animeID_DropItemPick;

    /* プレイヤー耐性値回復量_睡眠[point/s]
     *   プレイヤー耐性値回復量_睡眠[point/s]
     * Player Resist Recovery - Sleep
     *   Player resistance value recovery amount_sleep point / s */
    float resistRecoverPoint_Sleep_Player;

    /* フレア上書き誘導性能[deg/s]
     *   フレア上書き誘導性能[deg/s](-1:上書きなし)
     * Flare Overwrite Homing Angle
     *   Flare overwrite guidance performance deg / s (-1 no overwrite)
     * Default Value  = -1 */
    int flareOverrideHomingAngle;

    /* フレア上書き誘導停止距離[m]
     *   フレア上書き誘導停止距離[m](-1:上書きなし)
     * Flare Overwrite Homing Stop Range
     *   Flare overwrite guidance stop distance m (-1 no overwrite)
     * Default Value  = -1 */
    float flareOverrideHomingStopRange;

    /* ネムリアイテム取得時のアニメーションID
     *   ネムリアイテム取得時のアニメーションID
     * Sleep Collector Item Pick-up - Animation ID
     *   Animation ID when acquiring Nemuri item */
    int animeID_SleepCollectorItemPick;

    /* 武器属性解禁イベントフラグベースID
     *   武器属性解禁イベントフラグベースID
     * Weapon Affinity Unlock - Base Event Flag ID
     *   Weapon attribute ban event flag base ID */
    unsigned int unlockEventFlagBaseId_forWepAttr;

    /* システム経由大ルーン発動用特殊効果ID
     *   システムからの大ルーン発動の際に呼び出す特殊効果Id
     * Great Rune Activation - SpEffect ID
     *   Special effect Id to call when a large rune is activated from the system */
    int systemEnchant_BigRune;

    /* ステータス不足 基本攻撃力低下量
     *   ステータス不足 基本攻撃力低下量
     * Insufficient Stats - Attack Power Reduction
     *   Insufficient status Basic attack power reduction */
    float lowStatus_AtkPowDown;

    /* ステータス不足 スタミナ消費倍率
     *   ステータス不足 スタミナ消費倍率
     * Insufficient Stats - Stamina Consumption
     *   Insufficient status Stamina consumption ratio */
    float lowStatus_ConsumeStaminaRate;

    /* ステータス不足 弾き攻撃力
     *   ステータス不足 弾き攻撃力
     * Insufficient Stats - Stamina Damage Reduction
     *   Insufficient status Playing attack power */
    short lowStatus_AtkGuardBreak;

    /* 盾ステータス補正 判定ステータス最大値
     *   盾の性能のステータス補正値を計算するときに使う、性能が上昇する最大ステータス値
     * Guard Boost Correction - Max Value
     *   Maximum status value to increase performance used when calculating the status correction value of shield performance */
    short guardStatusCorrect_MaxStatusVal;

    /* 武器属性解禁イベントフラグステップ数
     *   ベースIDから武器属性IDごとにどのぐらい間隔を空けるか。武器属性解禁イベントフラグID＝《武器属性解禁イベントフラグベースID》＋武器属性ID×《武器属性解禁イベントフラグステップ数》
     * Weapon Affinity Unlock - Event Flag Step Offset
     *   How much space is left for each weapon attribute ID from the base ID. Weapon attribute ban event flag ID = Weapon attribute ban event flag base ID + Weapon attribute ID x Weapon attribute ban event flag number of steps
     * Default Value  = 1 */
    unsigned short unlockEventFlagStepNum_forWepAttr;

    /* 因果応報_反撃までの被ダメージ回数
     *   因果応報_反撃までの被ダメージ回数
     * Retribution Magic - Damage Trigger Count
     *   Causal Retribution_Number of Damages Before Counterattack */
    unsigned short retributionMagic_damageCountNum;

    /* 因果応報_反撃までの被ダメージ回数存続時間[s]
     *   因果応報_反撃までの被ダメージ回数存続時間[s]
     * Retribution Magic - Damage Trigger Duration
     *   Causal response_Number of damages until counterattack Duration s */
    unsigned short retributionMagic_damageCountRemainTime;

    /* 因果応報_反撃魔法ダミポリID
     *   因果応報_反撃魔法ダミポリID
     * Retribution Magic - Explosion Dummy Poly ID
     *   Causal Retribution_Counterattack Magic Damipoli ID */
    unsigned short retributionMagic_burstDmypolyId;

    /* 因果応報_反撃魔法パラムID
     *   因果応報_反撃魔法パラムID
     * Retribution Magic - Explosion Magic Param ID
     *   Causal Retribution_Counterattack Magic Param ID
     * Default Value  = -1 */
    int retributionMagic_burstMagicParamId;

    /* 騎乗精密射撃カメラオフセット高さ
     *   騎乗精密射撃カメラオフセット高さ
     * Mounted Precision Shoot - Camera Offset Height
     *   Riding precision shooting camera offset height */
    float chrAimCam_rideOffsetHeight;

    /* 予約
     *   (dummy8) */
    char reserved23[4];

    /* 矢筒の吸着ダミポリID
     *   矢筒の吸着ダミポリID
     * Quiver Dummy Poly ID
     *   Quiver adsorption Damipoly ID */
    int arrowCaseWepBindDmypolyId;

    /* ボルト筒の吸着ダミポリID
     *   ボルト筒の吸着ダミポリID（ただしボルト筒単独の場合は矢筒のダミポリIDが使われる）
     * Bolt Case Dummy Poly ID
     *   Bolt cylinder adsorption Damipoly ID (However, if the bolt cylinder is used alone, the quiver Damipoly ID is used) */
    int boltPouchWepBindDmypolyId;

    /* マルチ時クライアント瓶補正倍率
     *   マルチ時クライアント瓶補正倍率(0.5指定で所持数半分に)
     * Multiplayer Flask Reduction
     *   Multi-time client bottle correction magnification (0.5 specified to halve the number of possessions) */
    float estusFlaskAllocateRate;

    /* 予約
     *   (dummy8) */
    char reserved38[2];

    /* プレイヤー正面から見てキックを出せる角度
     *   プレイヤー正面から見てキックを出せる角度
     * Kick Acceptance Angle
     *   Angle at which a kick can be taken when viewed from the front of the player */
    unsigned char kickAcceptanceDeg;

    /* NPCプレイヤー用アナログ重量比率_軽量
     *   NPCプレイヤー用アナログ重量比率[%]。軽量。
     * NPC Player - Weight Rate Light
     *   Analog weight ratio for NPC players %. lightweight. */
    unsigned char npcPlayerAnalogWeightRate_Light;

    /* NPCプレイヤー用アナログ重量比率_中量
     *   NPCプレイヤー用アナログ重量比率[%]。中量。
     * NPC Player - Weight Rate Normal
     *   Analog weight ratio for NPC players %. Medium weight. */
    unsigned char npcPlayerAnalogWeightRate_Normal;

    /* NPCプレイヤー用アナログ重量比率_重量
     *   NPCプレイヤー用アナログ重量比率[%]。重量。
     * NPC Player - Weight Rate Heavy
     *   Analog weight ratio for NPC players %. weight. */
    unsigned char npcPlayerAnalogWeightRate_Heavy;

    /* NPCプレイヤー用アナログ重量比率_重量過多
     *   NPCプレイヤー用アナログ重量比率[%]。重量過多。
     * NPC Player - Weight Rate Encumbered
     *   Analog weight ratio for NPC players %. Overweight. */
    unsigned char npcPlayerAnalogWeightRate_WeightOver;

    /* NPCプレイヤー用アナログ重量比率_超軽量
     *   NPCプレイヤー用アナログ重量比率[%]。超軽量。
     * NPC Player - Weight Rate Ninja
     *   Analog weight ratio for NPC players %. Super lightweight. */
    unsigned char npcPlayerAnalogWeightRate_SuperLight;

    /* 予約
     *   (dummy8) */
    char reserved45[4];

    /* 周回補正特殊効果基準ID
     *   周回補正のためにかける特殊効果の基準ID
     * Game Clear - Base SpEffect ID
     *   Criteria ID for special effects applied for lap correction */
    int clearCountCorrectBaseSpEffectId;

    /* 矢、ボルトのモデルIdオフセット
     *   矢、ボルトモデルを表示する際に、スロット１に装備された場合のモデルIDに加えるオフセット。（モデルId+オフセット値）
     * Ammunition Model ID Offset
     *   Offset added to the model ID when equipped in slot 1 when displaying the arrow and bolt models. (Model Id + offset value) */
    int arrowBoltModelIdOffset;

    /* 矢、ボルトの残量によるモデルマスクの残数閾値_1段階[%]
     *   矢、ボルトモデルを表示する際に、本数による表示マスクをかけるときの閾値の１段階判定値[%]。（この値より多ければ１段階表示）
     * Ammunition Count Model Mask Threshold 1
     *   When displaying the arrow and bolt models, the one-step judgment value % of the threshold value when applying the display mask by the number. (If it is more than this value, it is displayed in one step) */
    char arrowBoltRemainingNumModelMaskThreshold1;

    /* 矢、ボルトの残量によるモデルマスクの残数閾値_2段階[%]
     *   矢、ボルトモデルを表示する際に、本数による表示マスクをかけるときの閾値の２段階判定値[%]。（この値より多ければ２段階表示）
     * Ammunition Count Model Mask Threshold 2
     *   Two-step judgment value % of the threshold value when applying a display mask based on the number of arrows and bolt models. (If it is more than this value, it is displayed in 2 steps) */
    char arrowBoltRemainingNumModelMaskThreshold2;

    /* 予約
     *   (dummy8) */
    char reserved27[2];

    /* プレイヤー耐性値回復量_毒[point/s]
     *   プレイヤー耐性値回復量_毒[point/s]
     * Player Resist Recovery - Poison
     *   Player resistance recovery amount_poison point / s */
    float resistRecoverPoint_Poision_Player;

    /* プレイヤー耐性値回復量_疫病[point/s]
     *   プレイヤー耐性値回復量_疫病[point/s]
     * Player Resist Recovery - Scarlet Rot
     *   Player resistance value recovery amount_plague point / s */
    float resistRecoverPoint_Desease_Player;

    /* プレイヤー耐性値回復量_出血[point/s]
     *   プレイヤー耐性値回復量_出血[point/s]
     * Player Resist Recovery - Hemorrhage
     *   Player resistance recovery amount_bleeding point / s */
    float resistRecoverPoint_Blood_Player;

    /* プレイヤー耐性値回復量_呪い[point/s]
     *   プレイヤー耐性値回復量_呪い[point/s]
     * Player Resist Recovery - Blight
     *   Player resistance recovery amount_curse point / s */
    float resistRecoverPoint_Curse_Player;

    /* プレイヤー耐性値回復量_冷気[point/s]
     *   プレイヤー耐性値回復量_冷気[point/s]
     * Player Resist Recovery - Frostbite
     *   Player resistance value recovery amount_cold air point / s */
    float resistRecoverPoint_Freeze_Player;

    /* 敵耐性値回復量_毒[point/s]
     *   敵耐性値回復量_毒[point/s]
     * Enemy Resist Recovery - Poison
     *   Enemy resistance recovery amount_poison point / s */
    float resistRecoverPoint_Poision_Enemy;

    /* 敵耐性値回復量_疫病[point/s]
     *   敵耐性値回復量_疫病[point/s]
     * Enemy Resist Recovery - Scarlet Rot
     *   Enemy resistance value recovery amount_plague point / s */
    float resistRecoverPoint_Desease_Enemy;

    /* 敵耐性値回復量_出血[point/s]
     *   敵耐性値回復量_出血[point/s]
     * Enemy Resist Recovery - Hemorrhage
     *   Enemy resistance recovery amount_bleeding point / s */
    float resistRecoverPoint_Blood_Enemy;

    /* 敵耐性値回復量_呪い[point/s]
     *   敵耐性値回復量_呪い[point/s]
     * Enemy Resist Recovery - Blight
     *   Enemy resistance recovery amount_curse point / s */
    float resistRecoverPoint_Curse_Enemy;

    /* 敵耐性値回復量_冷気[point/s]
     *   敵耐性値回復量_冷気[point/s]
     * Enemy Resist Recovery - Frostbite
     *   Enemy resistance value recovery amount_cold air point / s */
    float resistRecoverPoint_Freeze_Enemy;

    /* 左手両手持ちリクエストのボタン長押し時間[s]
     *   左手両手持ちするときのボタン入力時間
     * Button Input Time for Both-Hand Left
     *   Button input time when holding both left hand */
    float requestTimeLeftBothHand;

    /* プレイヤー耐性値回復量_発狂[point/s]
     *   プレイヤー耐性値回復量_発狂[point/s]
     * Player Resist Recovery - Madness
     *   Player resistance value recovery amount_madness point / s */
    float resistRecoverPoint_Madness_Player;

    /* 素材アイテム取得アニメーションID
     *   素材アイテムを拾った時のアニメーションID
     * Material Pick-up - Animation ID
     *   Animation ID when picking up a material item */
    int animeID_MaterialItemPick;

    /* 黄衣HPエスト瓶補正倍率 
     *   黄衣HPエスト瓶補正倍率 
     * HP Flask Reduction - Yellow Monk
     *   Yellow Cloth HP Est Bottle Correction Magnification */
    float hpEstusFlaskAllocateRateForYellowMonk;

    /* 黄衣HPエスト瓶オフセット
     *   黄衣HPエスト瓶オフセット
     * HP Flask Offset - Yellow Monk
     *   Yellow Cloth HP Est Bottle Offset */
    int hpEstusFlaskAllocateOffsetForYellowMonk;

    /* 黄衣MPエスト瓶補正倍率
     *   黄衣MPエスト瓶補正倍率
     * FP Flask Reduction - Yellow Monk
     *   Yellow Cloth MP Est Bottle Correction Magnification */
    float mpEstusFlaskAllocateRateForYellowMonk;

    /* 黄衣MPエスト瓶オフセット
     *   黄衣MPエスト瓶オフセット
     * FP Flask Offset - Yellow Monk
     *   Yellow Cloth MP Est Bottle Offset */
    int mpEstusFlaskAllocateOffsetForYellowMonk;

    /* 敵耐性値回復量_睡眠[point/s]
     *   敵耐性値回復量_睡眠[point/s]
     * Enemy Resist Recovery - Sleep
     *   Enemy resistance value recovery amount_sleep point / s */
    float resistRecoverPoint_Sleep_Enemy;

    /* 敵耐性値回復量_発狂[point/s]
     *   敵耐性値回復量_発狂[point/s]
     * Enemy Resist Recovery - Madness
     *   Enemy resistance value recovery amount_madness point / s */
    float resistRecoverPoint_Madness_Enemy;

    /* 状態異常_即死_即死アイテムID
     *   状態異常_即死_即死アイテムID
     * Resist Blight Item ID
     *   Abnormal condition_immediate death_immediate death Item ID
     * Default Value  = -1 */
    int resistCurseItemId;

    /* 状態異常_即死_即死アイテム最大数
     *   状態異常_即死_即死アイテム最大数
     * Resist Blight Item Max Count
     *   Abnormal condition_immediate death_maximum number of instant death items */
    unsigned char resistCurseItemMaxNum;

    /* 予約
     *   (dummy8) */
    char reserved_123[3];

    /* 状態異常_即死_即死アイテム所持特殊効果ベースID
     *   状態異常_即死_即死アイテム所持特殊効果ベースID
     * Resist Blight Item - Base SpEffect ID
     *   Abnormal condition_Instant death_Instant death Item possession Special effect base ID
     * Default Value  = -1 */
    int resistCurseItemSpEffectBaseId;

    /* 状態異常_即死_即死時アイテム抽選ID_マップ用
     *   状態異常_即死_即死時アイテム抽選ID_マップ用
     * Resist Blight Item - Map Item Lot ID
     *   Abnormal condition_immediate death_immediate death item lottery ID_for map
     * Default Value  = -1 */
    int resistCurseItemLotParamId_map;

    int unknown_0xcc;

    int unknown_0xd0;

    int unknown_0xd4;

    int unknown_0xd8;

    int unknown_0xdc;

    int unknown_0xe0;

    /* 予約
     *   (dummy8) */
    char reserved41[28];
} player_common_param_t;
