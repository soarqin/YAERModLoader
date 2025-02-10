#pragma once

/* Defines behaviour data of spells. Do not confuse with version in EquipParamGoods. */
typedef struct magic_param_s {
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

    /* Yes/NoダイアログメッセージID
     *   魔法使用時に出すYes/NoダイアログのメッセージID
     * Dialog Message ID
     *   Message ID of Yes / No dialog issued when using magic */
    int yesNoDialogMessageId;

    /* 使用制限から外れる特殊効果ID
     *   指定した特殊効果IDが発動している時は使用制限を無視できる
     * Ignore Usage Restriction - SpEffect ID
     *   Usage restrictions can be ignored when the specified special effect ID is activated
     * Default Value  = -1 */
    int limitCancelSpEffectId;

    /* SortID
     *   ソートID(-1:集めない)
     * Sort ID
     *   Sort ID (-1: Do not collect) */
    short sortId;

    /* 装備条件【運】
     *   PCの運がこれ以上無いと装備できない
     * Requirement: ARC
     *   Can't be equipped without more PC luck */
    unsigned char requirementLuck;

    /* AI通知タイプ
     *   act("魔法発動時AI通知")でAIインタラプトが発生する
     * AI Interrupt Type
     *   AI interrupt occurs in act (AI notification when magic is activated) */
    unsigned char aiNotifyType;

    /* 消費MP[通常]
     *   消費MP
     * FP Consumption - Default
     *   MP consumption */
    short mp;

    /* 消費スタミナ[通常]
     *   消費スタミナ
     * Stamina Consumption - Default
     *   Consumption stamina */
    short stamina;

    /* アイコンID
     *   アイコンを指定　＞メニュー用
     * Icon ID
     *   Specify icon> For menu */
    short iconId;

    /* 行動ID
     *   行動IDを設定する
     * Behavior ID
     *   Set the action ID */
    short behaviorId;

    /* 必要アイテムID
     *   購入に必要なアイテムID
     * Material Item ID
     *   Item ID required for purchase
     * Default Value  = -1 */
    short mtrlItemId;

    /* 差し替える魔法ID
     *   状態変化一致時に差し替えるID(-1:無効)
     * Replace Magic ID
     *   ID to be replaced when the state change matches (-1: invalid)
     * Default Value  = -1 */
    short replaceMagicId;

    /* 最大個数
     *   １個当たりの個数(-1:無限)
     * Number of Uses
     *   Number per piece (-1: infinity) */
    short maxQuantity;

    /* IDカテゴリ
     *   呼び出しIDのカテゴリ[攻撃、飛び道具、特殊効果]
     * Reference Category [1]
     *   Call ID category [Attack, Projectile, Special Effects] */
    unsigned char refCategory1;

    /* 技量オーバー開始値
     *   技量オーバー開始値
     * Dexterity over Start Value
     *   Skill over start value */
    unsigned char overDexterity;

    /* IDカテゴリ
     *   呼び出しIDのカテゴリ[攻撃、飛び道具、特殊効果]
     * Reference Category [2]
     *   Call ID category [Attack, Projectile, Special Effects] */
    unsigned char refCategory2;

    /* 必要スロット
     *   装備に必要なスロット数 ＞メニュー用
     * Slot Usage
     *   Number of slots required for equipment> For menu */
    unsigned char slotLength;

    /* 装備条件【知力】
     *   PCの知力がこれ以上無いと装備できない
     * Requirement: INT
     *   Can't be equipped without more PC intelligence */
    unsigned char requirementIntellect;

    /* 装備条件【理力】
     *   PCの理力がこれ以上無いと装備できない
     * Requirement: FTH
     *   It cannot be equipped without the power of the PC any more. */
    unsigned char requirementFaith;

    /* アナログ最低技量
     *   モーションキャンセルアナログ化：最低技量値
     * Casting Speed - DEX Start Range
     *   Motion cancel analog: Minimum skill value */
    unsigned char analogDexterityMin;

    /* アナログ最大技量
     *   モーションキャンセルアナログ化：最高技量値
     * Casting Speed - DEX End Range
     *   Motion cancel analog: Maximum skill value */
    unsigned char analogDexterityMax;

    /* カテゴリ
     *   並べ替えに使用　＞メニュー用
     * Magic School Type
     *   Used for sorting> For menu */
    unsigned char ezStateBehaviorType;

    /* IDカテゴリ
     *   呼び出しIDのカテゴリ[攻撃、飛び道具、特殊効果]
     * Reference Category [3]
     *   Call ID category [Attack, Projectile, Special Effects] */
    unsigned char refCategory3;

    /* 特殊効果カテゴリ
     *   スキルや、魔法、アイテムなどで、パラメータが変動する効果（エンチャントウェポンなど）があるので、│定した効果が、「武器攻撃のみをパワーアップする」といった効果に対応できるように行動ごとに設定するバリスタなど、設定の必要のないものは「なし」を設定する

     * SpEffect Category
     *   Since there are effects (enchantment weapons, etc.) whose parameters fluctuate depending on skills, magic, items, etc., set each action so that the determined effect can correspond to the effect such as power up only weapon attack. Set None for items that do not need to be set, such as varistor. */
    unsigned char spEffectCategory;

    /* モーションカテゴリ
     *   モーションを指定　＞EzState用
     * Motion Category
     *   Specify motion> For EzState */
    unsigned char refType;

    /* 使用時メニュータイプ
     *   魔法使用時に出すメニュータイプ
     * Open Menu Type
     *   Menu type to be displayed when using magic */
    unsigned char opmeMenuType;

    /* IDカテゴリ
     *   呼び出しIDのカテゴリ[攻撃、飛び道具、特殊効果]
     * Reference Category [4]
     *   Call ID category [Attack, Projectile, Special Effects] */
    unsigned char refCategory4;

    /* どの常態か？
     *   魔法IDを差し替える必要がある状態変化を指定
     * Has SpEffect Type
     *   Specify the state change that needs to replace the magic ID */
    unsigned short hasSpEffectType;

    /* 差し替えカテゴリ
     *   魔法IDを差し替える時の追加条件
     * Replace Category
     *   Additional conditions when replacing the magic ID */
    unsigned char replaceCategory;

    /* 特殊効果カテゴリによる使用制限
     *   特殊効果によって使用可能かどうかを制御する為に指定
     * Use Limit Category
     *   Specified to control availability by special effects */
    unsigned char useLimitCategory;

    /* 誓約0
     *   誓約0
     * Vow Type [0]
     *   Pledge 0 */
    unsigned char vowType0:1;

    /* 誓約1
     *   誓約1
     * Vow Type [1]
     *   Pledge 1 */
    unsigned char vowType1:1;

    /* 誓約2
     *   誓約2
     * Vow Type [2]
     *   Pledge 2 */
    unsigned char vowType2:1;

    /* 誓約3
     *   誓約3
     * Vow Type [3]
     *   Pledge 3 */
    unsigned char vowType3:1;

    /* 誓約4
     *   誓約4
     * Vow Type [4]
     *   Pledge 4 */
    unsigned char vowType4:1;

    /* 誓約5
     *   誓約5
     * Vow Type [5]
     *   Pledge 5 */
    unsigned char vowType5:1;

    /* 誓約6
     *   誓約6
     * Vow Type [6]
     *   Pledge 6 */
    unsigned char vowType6:1;

    /* 誓約7
     *   誓約7
     * Vow Type [7]
     *   Pledge 7 */
    unsigned char vowType7:1;

    /* マルチでも使用可能か
     *   マルチでも使用できるか。シングル、マルチ両方で使える
     * Allow in Multiplayer
     *   Can it be used in multi? Can be used for both single and multi */
    unsigned char enable_multi:1;

    /* マルチ専用か
     *   マルチ専用か。シングルのときには使えない。マルチのときは使える。
     * Allow only in Multiplayer
     *   Is it only for multi? It cannot be used when it is a single. It can be used when it is multi. */
    unsigned char enable_multi_only:1;

    /* エンチャントか
     *   エンチャントする魔法か
     * Is Weapon Enchantment
     *   Is it magic to enchant? */
    unsigned char isEnchant:1;

    /* 盾エンチャントか
     *   ガード・盾エンチャントする魔法か
     * Is Shield Enchantment
     *   Is it magic to enchant guards and shields? */
    unsigned char isShieldEnchant:1;

    /* 生存使用可
     *   生存キャラが使用可能か
     * Enable Live
     *   Can surviving characters be used? */
    unsigned char enable_live:1;

    /* グレイ使用可
     *   グレイキャラが使用可能か
     * Enable Gray
     *   Can gray characters be used? */
    unsigned char enable_gray:1;

    /* 白使用可
     *   白ゴーストキャラが使用可能か
     * Enable White
     *   Can white ghost characters be used? */
    unsigned char enable_white:1;

    /* 黒使用可
     *   黒ゴーストキャラが使用可能か
     * Enable Black
     *   Can black ghost characters be used? */
    unsigned char enable_black:1;

    /* オフラインで使用不可か
     *   オフラインで使用不可か
     * Disable Offline
     *   Is it unavailable offline? */
    unsigned char disableOffline:1;

    /* 共鳴魔法配信するか
     *   共鳴魔法配信するか
     * Cast Resonance Magic
     *   Do you deliver resonance magic? */
    unsigned char castResonanceMagic:1;

    /* 防具SAダメージ倍率が初期値でも有効か？
     *   防具SAが初期値でも強靭度計算が行われるかどうか。詳細は強靭度仕様書.xlsxを確認してください
     * Is Toughness Perfomed if Poise is Initial Value
     *   Whether the toughness calculation is performed even if the armor SA is the initial value. Check the toughness specification .xlsx for details */
    unsigned char isValidTough_ProtSADmg:1;

    /* ワープ魔法か
     *   ワープする魔法か。ここにチェックが入っている魔法は特殊効果「ワープ禁止」により使用が禁止されます
     * Is Blocked by Warp Prohibition Effect
     *   Is it magic to warp? Magic with a check mark here is prohibited by the special effect Warp Prohibition. */
    unsigned char isWarpMagic:1;

    /* 騎乗中使用可能か
     *   騎乗中使用可能か
     * Usable while Riding
     *   Can it be used while riding? */
    unsigned char enableRiding:1;

    /* 非騎乗中使用禁止か
     *   非騎乗中使用禁止か
     * Not Usable while Riding
     *   Is it prohibited to use while not riding? */
    unsigned char disableRiding:1;

    /* 攻撃禁止区域で使用できるか
     *   攻撃禁止区域で使用できるか
     * Usable in No Attack Region
     *   Can it be used in an attack-prohibited area? */
    unsigned char isUseNoAttackRegion:1;

    /* pading */
    char pad_1:1;

    /* 誓約8
     *   誓約8
     * Vow Type [8]
     *   Pledge 8 */
    unsigned char vowType8:1;

    /* 誓約9
     *   誓約9
     * Vow Type [9]
     *   Pledge 9 */
    unsigned char vowType9:1;

    /* 誓約10
     *   誓約10
     * Vow Type [10]
     *   Pledge 10 */
    unsigned char vowType10:1;

    /* 誓約11
     *   誓約11
     * Vow Type [11]
     *   Pledge 11 */
    unsigned char vowType11:1;

    /* 誓約12
     *   誓約12
     * Vow Type [12]
     *   Pledge 12 */
    unsigned char vowType12:1;

    /* 誓約13
     *   誓約13
     * Vow Type [13]
     *   Pledge 13 */
    unsigned char vowType13:1;

    /* 誓約14
     *   誓約14
     * Vow Type [14]
     *   Pledge 14 */
    unsigned char vowType14:1;

    /* 誓約15
     *   誓約15
     * Vow Type [15]
     *   Pledge 15 */
    unsigned char vowType15:1;

    /* 詠唱SFXID
     *   魔法詠唱中のSFXID
     * SFX ID - Cast
     *   SFXID during magical chanting
     * Default Value  = -1 */
    int castSfxId;

    /* 発動SFXID
     *   魔法発動時のSFXID
     * SFX ID - Fire
     *   SFX ID when magic is activated
     * Default Value  = -1 */
    int fireSfxId;

    /* 効果SFXID
     *   魔法効果中のSFXID
     * SFX ID - Effect
     *   SFXID during magic effect
     * Default Value  = -1 */
    int effectSfxId;

    /* 強靭度 補正倍率
     *   強靭度の基本値を補正する倍率です
     * Toughness Correction
     *   It is a magnification that corrects the basic value of toughness. */
    float toughnessCorrectRate;

    /* 差し替えステータスタイプ
     *   差し替えステータスタイプ
     * Replacement Status Type
     *   Replacement status type */
    unsigned char ReplacementStatusType;

    /* 差し替えステータス値1
     *   差し替えステータス値1
     * Replacement Threshold [1]
     *   Replacement status value 1
     * Default Value  = -1 */
    char ReplacementStatus1;

    /* 差し替えステータス値2
     *   差し替えステータス値2
     * Replacement Threshold [2]
     *   Replacement status value 2
     * Default Value  = -1 */
    char ReplacementStatus2;

    /* 差し替えステータス値3
     *   差し替えステータス値3
     * Replacement Threshold [3]
     *   Replacement status value 3
     * Default Value  = -1 */
    char ReplacementStatus3;

    /* 差し替えステータス値4
     *   差し替えステータス値4
     * Replacement Threshold [4]
     *   Replacement status value 4
     * Default Value  = -1 */
    char ReplacementStatus4;

    /* IDカテゴリ
     *   呼び出しIDのカテゴリ[攻撃、飛び道具、特殊効果]
     * Reference Category [5]
     *   Call ID category [Attack, Projectile, Special Effects] */
    unsigned char refCategory5;

    /* 消費SA[通常/溜め]
     *   消費SA量[通常/溜め]
     * Poise Consumption
     *   SA consumption [normal / reservoir] */
    short consumeSA;

    /* 差し替えID1
     *   差し替えID1
     * Replacement Magic ID [1]
     *   Replacement ID1
     * Default Value  = -1 */
    int ReplacementMagic1;

    /* 差し替えID2
     *   差し替えID2
     * Replacement Magic ID [2]
     *   Replacement ID2
     * Default Value  = -1 */
    int ReplacementMagic2;

    /* 差し替えID3
     *   差し替えID3
     * Replacement Magic ID [3]
     *   Replacement ID3
     * Default Value  = -1 */
    int ReplacementMagic3;

    /* 差し替えID4
     *   差し替えID4
     * Replacement Magic ID [4]
     *   Replacement ID 4
     * Default Value  = -1 */
    int ReplacementMagic4;

    /* 消費MP[溜め]
     *   消費MP[溜め]
     * FP Consumption - Charged
     *   MP consumption [reservoir] */
    short mp_charge;

    /* 消費スタミナ[溜め]
     *   消費スタミナ[溜め]
     * Stamina Consumption - Charged
     *   Consumption stamina [reservoir] */
    short stamina_charge;

    /* 作成制限グループId
     *   0なら未使用。指定したグループIdの弾丸作成数を確認し、上限に達していたら魔法の使用をできなくする。
     * Create Limit Group ID
     *   If it is 0, it is unused. Check the number of bullets created for the specified group Id, and if the upper limit is reached, you will not be able to use magic. */
    unsigned char createLimitGroupId;

    /* IDカテゴリ
     *   呼び出しIDのカテゴリ[攻撃、飛び道具、特殊効果]
     * Reference Category [6]
     *   Call ID category [Attack, Projectile, Special Effects] */
    unsigned char refCategory6;

    /* サブカテゴリ1
     *   サブカテゴリ1
     * Conditional Category [1]
     *   Subcategory 1 */
    unsigned char subCategory1;

    /* サブカテゴリ2
     *   サブカテゴリ2
     * Conditional Category [2]
     *   Subcategory 2 */
    unsigned char subCategory2;

    /* IDカテゴリ
     *   呼び出しIDのカテゴリ[攻撃、飛び道具、特殊効果]
     * Reference Category [7]
     *   Call ID category [Attack, Projectile, Special Effects] */
    unsigned char refCategory7;

    /* IDカテゴリ
     *   呼び出しIDのカテゴリ[攻撃、飛び道具、特殊効果]
     * Reference Category [8]
     *   Call ID category [Attack, Projectile, Special Effects] */
    unsigned char refCategory8;

    /* IDカテゴリ
     *   呼び出しIDのカテゴリ[攻撃、飛び道具、特殊効果]
     * Reference Category [9]
     *   Call ID category [Attack, Projectile, Special Effects] */
    unsigned char refCategory9;

    /* IDカテゴリ
     *   呼び出しIDのカテゴリ[攻撃、飛び道具、特殊効果]
     * Reference Category [10]
     *   Call ID category [Attack, Projectile, Special Effects] */
    unsigned char refCategory10;

    /* 呼び出しID
     *   魔法から呼び出すID
     * Reference ID [1]
     *   ID called from magic
     * Default Value  = -1 */
    int refId1;

    /* 呼び出しID
     *   魔法から呼び出すID
     * Reference ID [2]
     *   ID called from magic
     * Default Value  = -1 */
    int refId2;

    /* 呼び出しID
     *   魔法から呼び出すID
     * Reference ID [3]
     *   ID called from magic
     * Default Value  = -1 */
    int refId3;

    /* AI使用判断ID
     *   AI使用判断ID
     * AI Usage Judgment ID
     *   AI usage judgment ID
     * Default Value  = -1 */
    int aiUseJudgeId;

    /* 呼び出しID
     *   魔法から呼び出すID
     * Reference ID [4]
     *   ID called from magic
     * Default Value  = -1 */
    int refId4;

    /* 呼び出しID
     *   魔法から呼び出すID
     * Reference ID [5]
     *   ID called from magic
     * Default Value  = -1 */
    int refId5;

    /* 呼び出しID
     *   魔法から呼び出すID
     * Reference ID [6]
     *   ID called from magic
     * Default Value  = -1 */
    int refId6;

    /* 呼び出しID
     *   魔法から呼び出すID
     * Reference ID [7]
     *   ID called from magic
     * Default Value  = -1 */
    int refId7;

    /* 呼び出しID
     *   魔法から呼び出すID
     * Reference ID [8]
     *   ID called from magic
     * Default Value  = -1 */
    int refId8;

    /* 呼び出しID
     *   魔法から呼び出すID
     * Reference ID [9]
     *   ID called from magic
     * Default Value  = -1 */
    int refId9;

    /* 呼び出しID
     *   魔法から呼び出すID
     * Reference ID [10]
     *   ID called from magic
     * Default Value  = -1 */
    int refId10;

    /* 消費タイプ
     *   消費タイプ
     * Consumption Type [1]
     *   When Reference ID [1] is called, consume FP/Stamina according to the configured cost. */
    unsigned char consumeType1;

    /* 消費タイプ
     *   消費タイプ
     * Consumption Type [2]
     *   When Reference ID [2] is called, consume FP/Stamina according to the configured cost. */
    unsigned char consumeType2;

    /* 消費タイプ
     *   消費タイプ
     * Consumption Type [3]
     *   When Reference ID [3] is called, consume FP/Stamina according to the configured cost. */
    unsigned char consumeType3;

    /* 消費タイプ
     *   消費タイプ
     * Consumption Type [4]
     *   When Reference ID [4] is called, consume FP/Stamina according to the configured cost. */
    unsigned char consumeType4;

    /* 消費タイプ
     *   消費タイプ
     * Consumption Type [5]
     *   When Reference ID [5] is called, consume FP/Stamina according to the configured cost. */
    unsigned char consumeType5;

    /* 消費タイプ
     *   消費タイプ
     * Consumption Type [6]
     *   When Reference ID [6] is called, consume FP/Stamina according to the configured cost. */
    unsigned char consumeType6;

    /* 消費タイプ
     *   消費タイプ
     * Consumption Type [7]
     *   When Reference ID [7] is called, consume FP/Stamina according to the configured cost. */
    unsigned char consumeType7;

    /* 消費タイプ
     *   消費タイプ
     * Consumption Type [8]
     *   When Reference ID [8] is called, consume FP/Stamina according to the configured cost. */
    unsigned char consumeType8;

    /* 消費タイプ
     *   消費タイプ
     * Consumption Type [9]
     *   When Reference ID [9] is called, consume FP/Stamina according to the configured cost. */
    unsigned char consumeType9;

    /* 消費タイプ
     *   消費タイプ
     * Consumption Type [10]
     *   When Reference ID [10] is called, consume FP/Stamina according to the configured cost. */
    unsigned char consumeType10;

    /* メニュー補足表示用消費MP
     *   メニュー補足表示用消費MP
     * FP Consumption Loop - For Menu Display
     *   MP consumption for menu supplement display
     * Default Value  = -1 */
    short consumeLoopMP_forMenu;

    /* PAD12
     *   PAD12 */
    char pad[8];
} magic_param_t;
