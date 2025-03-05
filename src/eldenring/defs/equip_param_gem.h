#pragma once

/* Defines an Ash of War item. Determines what weapons it can be applied to and with what affinities.
 * Does not manage unique Ashes of War. Ashes of war may not immediately function on arbitrary weapons. */
typedef struct er_equip_param_gem_s {
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

    /* アイコンID
     *   メニュー用アイコンID
     * Icon ID
     *   Menu icon ID */
    unsigned short iconId;

    /* 魔石ランク
     *   魔石ランク
     * Rank
     *   Magic stone rank */
    char rank;

    /* ソートアイテム種別ID
     *   ソートアイテム種別ID。ソート「アイテム種別順」にて、同じIDは同じグループとしてまとめて表示されます
     * Sort Group ID
     *   Sort item type ID. In the sort Item type order, the same ID is displayed together as the same group.
     * Default Value  = 255 */
    unsigned char sortGroupId;

    /* 常駐特殊効果ID00
     *   特殊効果ID00
     * SpEffect ID [0]
     *   Special effect ID00
     * Default Value  = -1 */
    int spEffectId0;

    /* 常駐特殊効果ID01
     *   特殊効果ID01
     * SpEffect ID [1]
     *   Special effect ID01
     * Default Value  = -1 */
    int spEffectId1;

    /* 常駐特殊効果ID02
     *   特殊効果ID02
     * SpEffect ID [2]
     *   Special effect ID02
     * Default Value  = -1 */
    int spEffectId2;

    /* アイテム入手チュートリアル判定フラグID
     *   初めてアイテム入手した時のチュートリアル用のイベントフラグID。アイテム入手時にフラグON。
     * Item Get Tutorial Flag ID
     *   Event flag ID for the tutorial when you first get the item. Flag ON when item is obtained. */
    unsigned int itemGetTutorialFlagId;

    /* 変化先アーツパラメータID
     *   変化先アーツパラメータのID
     * Sword Arts ID
     *   ID of the destination arts parameter
     * Default Value  = -1 */
    int swordArtsParamId;

    /* 装着価格
     *   装着価格
     * Application Cost
     *   Installation price */
    int mountValue;

    /* 売却価格
     *   売却価格
     * Sell Value
     *   Sale price */
    int sellValue;

    /* 販売価格
     *   販売価格
     * Sale Value
     *   Selling price
     * Default Value  = -1 */
    int saleValue;

    /* ソートID
     *   ソートID(-1:集めない)
     * Sort ID
     *   Sort ID (-1: Do not collect) */
    int sortId;

    /* コンプトロフィーSEQ番号
     *   コンプリート系トロフィのSEQ番号
     * Achievement ID
     *   SEQ number of complete trophy
     * Default Value  = -1 */
    short compTrophySedId;

    /* トロフィーSEQ番号
     *   トロフィーのSEQ番号
     * Achievement Sequential ID
     *   Trophy SEQ number
     * Default Value  = -1 */
    short trophySeqId;

    /* 0
     *   設定可能武器属性ID0
     * Affinity: Standard
     *   Configurable weapon attribute ID 0 */
    unsigned char configurableWepAttr00:1;

    /* 1
     *   設定可能武器属性ID1
     * Affinity: Heavy
     *   Configurable Weapon Attribute ID 1 */
    unsigned char configurableWepAttr01:1;

    /* 2
     *   設定可能武器属性ID2
     * Affinity: Keen
     *   Configurable Weapon Attribute ID 2 */
    unsigned char configurableWepAttr02:1;

    /* 3
     *   設定可能武器属性ID3
     * Affinity: Quality
     *   Configurable Weapon Attribute ID 3 */
    unsigned char configurableWepAttr03:1;

    /* 4
     *   設定可能武器属性ID4
     * Affinity: Fire
     *   Configurable Weapon Attribute ID 4 */
    unsigned char configurableWepAttr04:1;

    /* 5
     *   設定可能武器属性ID5
     * Affinity: Flame Art
     *   Configurable Weapon Attribute ID 5 */
    unsigned char configurableWepAttr05:1;

    /* 6
     *   設定可能武器属性ID6
     * Affinity: Lightning
     *   Configurable Weapon Attribute ID 6 */
    unsigned char configurableWepAttr06:1;

    /* 7
     *   設定可能武器属性ID7
     * Affinity: Sacred
     *   Configurable Weapon Attribute ID 7 */
    unsigned char configurableWepAttr07:1;

    /* 8
     *   設定可能武器属性ID8
     * Affinity: Magic
     *   Configurable Weapon Attribute ID 8 */
    unsigned char configurableWepAttr08:1;

    /* 9
     *   設定可能武器属性ID9
     * Affinity: Cold
     *   Configurable Weapon Attribute ID 9 */
    unsigned char configurableWepAttr09:1;

    /* 10
     *   設定可能武器属性ID10
     * Affinity: Poison
     *   Configurable Weapon Attribute ID 10 */
    unsigned char configurableWepAttr10:1;

    /* 11
     *   設定可能武器属性ID11
     * Affinity: Blood
     *   Configurable Weapon Attribute ID 11 */
    unsigned char configurableWepAttr11:1;

    /* 12
     *   設定可能武器属性ID12
     * Affinity: Occult
     *   Configurable Weapon Attribute ID 12 */
    unsigned char configurableWepAttr12:1;

    /* 13
     *   設定可能武器属性ID13
     * Affinity: Unused [13]
     *   Configurable Weapon Attribute ID 13 */
    unsigned char configurableWepAttr13:1;

    /* 14
     *   設定可能武器属性ID14
     * Affinity: Unused [14]
     *   Configurable Weapon Attribute ID 14 */
    unsigned char configurableWepAttr14:1;

    /* 15
     *   設定可能武器属性ID15
     * Affinity: Unused [15]
     *   Configurable Weapon Attribute ID 15 */
    unsigned char configurableWepAttr15:1;

    /* レア度
     *   アイテム取得ログで使うレア度
     * Rarity
     *   Rarity used in item acquisition logs */
    unsigned char rarity;

    /* 16
     *   設定可能武器属性ID16
     * Affinity: Unused [16]
     *   Configurable Weapon Attribute ID 16 */
    unsigned char configurableWepAttr16:1;

    /* 17
     *   設定可能武器属性ID17
     * Affinity: Unused [17]
     *   Configurable Weapon Attribute ID 17 */
    unsigned char configurableWepAttr17:1;

    /* 18
     *   設定可能武器属性ID18
     * Affinity: Unused [18]
     *   Configurable Weapon Attribute ID 18 */
    unsigned char configurableWepAttr18:1;

    /* 19
     *   設定可能武器属性ID19
     * Affinity: Unused [19]
     *   Configurable Weapon Attribute ID 19 */
    unsigned char configurableWepAttr19:1;

    /* 20
     *   設定可能武器属性ID20
     * Affinity: Unused [20]
     *   Configurable Weapon Attribute ID 20 */
    unsigned char configurableWepAttr20:1;

    /* 21
     *   設定可能武器属性ID21
     * Affinity: Unused [21]
     *   Configurable Weapon Attribute ID 21 */
    unsigned char configurableWepAttr21:1;

    /* 22
     *   設定可能武器属性ID22
     * Affinity: Unused [22]
     *   Configurable Weapon Attribute ID 22 */
    unsigned char configurableWepAttr22:1;

    /* 23
     *   設定可能武器属性ID23
     * Affinity: Unused [23]
     *   Configurable Weapon Attribute ID 23 */
    unsigned char configurableWepAttr23:1;

    /* 捨てれるか
     *   アイテムを捨てれるか？TRUE=捨てれる
     * Is Discardable
     *   Can you throw away the item? TRUE = thrown away */
    unsigned char isDiscard:1;

    /* その場に置けるか
     *   アイテムをその場に置けるか？TRUE=置ける
     * Is Droppable
     *   Can I put the item on the spot? TRUE = can be placed */
    unsigned char isDrop:1;

    /* 預けれるか
     *   倉庫に預けれるか
     * Is Depositable
     *   Can you leave it in the warehouse? */
    unsigned char isDeposit:1;

    /* マルチドロップ共有禁止か
     *   マルチドロップ共有禁止か
     * Is Drop Disabled in Multiplayer
     *   Is multi-drop sharing prohibited? */
    unsigned char disableMultiDropShare:1;

    /* 取得ダイアログ表示条件
     *   アイテム取得時にアイテム取得ダイアログに表示するか（未入力: newのみ）
     * Item Acquisition Dialog Condition Type
     *   Whether to display it in the item acquisition dialog when acquiring an item (not entered: new only)
     * Default Value  = 2 */
    unsigned char showDialogCondType:2;

    /* 取得ログ表示条件
     *   アイテム取得時にアイテム取得ログに表示するか（未入力: ○）
     * Item Acquisition Show Condition Type
     *   Whether to display in the item acquisition log when acquiring the item (not entered: )
     * Default Value  = 1 */
    unsigned char showLogCondType:1;

    char pad:1;

    /* デフォルト武器属性ID
     *   デフォルト武器属性ID。開放されてない武器属性でも装着可能になる
     * Default Weapon Affinity
     *   Default weapon attribute ID. Can be installed even with unopened weapon attributes */
    unsigned char defaultWepAttr;

    /* Is Special Ash of War
     *   Determines whether this Ash of War is considered 'special'. Weapons with restrictSpecialSwordArt set to 1 will be unable to slot in these ashes of war. */
    unsigned char isSpecialSwordArt;

    char pad2[1];

    /* 短剣
     *   「武器種別：短剣」に装着可能か。未入力は×になる
     * Available: Dagger
     *   Can it be attached to Weapon type: Dagger? No input becomes x */
    unsigned char canMountWep_Dagger:1;

    /* 直剣
     *   「武器種別：直剣」に装着可能か。未入力は×になる
     * Available: Straight Sword
     *   Can it be attached to Weapon type: Straight sword? No input becomes x */
    unsigned char canMountWep_SwordNormal:1;

    /* 大剣
     *   「武器種別：大剣」に装着可能か。未入力は×になる
     * Available: Greatsword
     *   Can it be attached to Weapon Type: Large Sword? No input becomes x */
    unsigned char canMountWep_SwordLarge:1;

    /* 特大剣
     *   「武器種別：特大剣」に装着可能か。未入力は×になる
     * Available: Colossal Sword
     *   Can it be attached to Weapon Type: Oversized Sword? No input becomes x */
    unsigned char canMountWep_SwordGigantic:1;

    /* 曲剣 
     *   「武器種別：曲剣 」に装着可能か。未入力は×になる
     * Available: Curved Sword
     *   Can it be attached to Weapon Type: Curly Sword? No input becomes x */
    unsigned char canMountWep_SaberNormal:1;

    /* 大曲剣
     *   「武器種別：大曲剣」に装着可能か。未入力は×になる
     * Available: Curved Greatsword
     *   Can it be attached to Weapon Type: Omagari Sword? No input becomes x */
    unsigned char canMountWep_SaberLarge:1;

    /* 刀
     *   「武器種別：刀」に装着可能か。未入力は×になる
     * Available: Katana
     *   Can it be attached to Weapon type: Sword? No input becomes x */
    unsigned char canMountWep_katana:1;

    /* 両刃剣
     *   「武器種別：両刃剣」に装着可能か。未入力は×になる
     * Available: Twinblade
     *   Can it be attached to Weapon type: Double-edged sword? No input becomes x */
    unsigned char canMountWep_SwordDoubleEdge:1;

    /* 刺剣
     *   「武器種別：刺剣」に装着可能か。未入力は×になる
     * Available: Thrusting Sword
     *   Can it be attached to Weapon type: Sword? No input becomes x */
    unsigned char canMountWep_SwordPierce:1;

    /* 大刺剣
     *   「武器種別：大刺剣」に装着可能か。未入力は×になる
     * Available: Heavy Thrusting Sword
     *   Can it be attached to Weapon Type: Large Sword? No input becomes x */
    unsigned char canMountWep_RapierHeavy:1;

    /* 斧
     *   「武器種別：斧」に装着可能か。未入力は×になる
     * Available: Axe
     *   Can it be attached to Weapon Type: Ax? No input becomes x */
    unsigned char canMountWep_AxeNormal:1;

    /* 大斧
     *   「武器種別：大斧」に装着可能か。未入力は×になる
     * Available: Greataxe
     *   Can it be attached to Weapon Type: Large Ax? No input becomes x */
    unsigned char canMountWep_AxeLarge:1;

    /* 槌
     *   「武器種別：槌」に装着可能か。未入力は×になる
     * Available: Hammer
     *   Can it be attached to Weapon type: Hammer? No input becomes x */
    unsigned char canMountWep_HammerNormal:1;

    /* 大槌
     *   「武器種別：大槌」に装着可能か。未入力は×になる
     * Available: Great Hammer
     *   Can it be attached to Weapon Type: Gavel? No input becomes x */
    unsigned char canMountWep_HammerLarge:1;

    /* フレイル
     *   「武器種別：フレイル」に装着可能か。未入力は×になる
     * Available: Flail
     *   Can it be attached to Weapon Type: Frail? No input becomes x */
    unsigned char canMountWep_Flail:1;

    /* 槍
     *   「武器種別：槍」に装着可能か。未入力は×になる
     * Available: Spear
     *   Can it be attached to Weapon Type: Spear? No input becomes x */
    unsigned char canMountWep_SpearNormal:1;

    /* 長槍
     *   「武器種別：長槍」に装着可能か。未入力は×になる
     * Available: Large Spear
     *   Can it be attached to Weapon Type: Long Spear? No input becomes x */
    unsigned char canMountWep_SpearLarge:1;

    /* 大槍
     *   「武器種別：大槍」に装着可能か。未入力は×になる
     * Available: Heavy Spear
     *   Can it be attached to Weapon Type: Large Spear? No input becomes x */
    unsigned char canMountWep_SpearHeavy:1;

    /* 斧槍
     *   「武器種別：斧槍」に装着可能か。未入力は×になる
     * Available: Halberd
     *   Can it be attached to Weapon Type: Halberd? No input becomes x */
    unsigned char canMountWep_SpearAxe:1;

    /* 鎌
     *   「武器種別：鎌」に装着可能か。未入力は×になる
     * Available: Reaper
     *   Can it be attached to Weapon type: Sickle? No input becomes x */
    unsigned char canMountWep_Sickle:1;

    /* 拳
     *   「武器種別：拳」に装着可能か。未入力は×になる
     * Available: Fist
     *   Can it be attached to Weapon type: Fist? No input becomes x */
    unsigned char canMountWep_Knuckle:1;

    /* 爪
     *   「武器種別：爪」に装着可能か。未入力は×になる
     * Available: Claw
     *   Can it be attached to Weapon type: Claw? No input becomes x */
    unsigned char canMountWep_Claw:1;

    /* ムチ
     *   「武器種別：ムチ」に装着可能か。未入力は×になる
     * Available: Whip
     *   Can it be attached to Weapon type: Whip? No input becomes x */
    unsigned char canMountWep_Whip:1;

    /* 特大斧槌
     *   「武器種別：特大斧槌」に装着可能か。未入力は×になる
     * Available: Colossal Weapon
     *   Can it be attached to Weapon type: Oversized ax mallet? No input becomes x */
    unsigned char canMountWep_AxhammerLarge:1;

    /* 小弓
     *   「武器種別：小弓」に装着可能か。未入力は×になる
     * Available: Light Bow
     *   Can it be attached to Weapon type: Small bow? No input becomes x */
    unsigned char canMountWep_BowSmall:1;

    /* 弓
     *   「武器種別：弓」に装着可能か。未入力は×になる
     * Available: Bow
     *   Can it be attached to Weapon Type: Bow? No input becomes x */
    unsigned char canMountWep_BowNormal:1;

    /* 大弓
     *   「武器種別：大弓」に装着可能か。未入力は×になる
     * Available: Greatbow
     *   Can it be attached to Weapon Type: Large Bow? No input becomes x */
    unsigned char canMountWep_BowLarge:1;

    /* クロスボウ
     *   「武器種別：クロスボウ」に装着可能か。未入力は×になる
     * Available: Crossbow
     *   Can it be attached to Weapon Type: Crossbow? No input becomes x */
    unsigned char canMountWep_ClossBow:1;

    /* バリスタ
     *   「武器種別：バリスタ」に装着可能か。未入力は×になる
     * Available: Ballista
     *   Can it be attached to Weapon Type: Varistor? No input becomes x */
    unsigned char canMountWep_Ballista:1;

    /* 杖
     *   「武器種別：杖」に装着可能か。未入力は×になる
     * Available: Staff
     *   Can it be attached to Weapon type: Wand? No input becomes x */
    unsigned char canMountWep_Staff:1;

    /* 入れ墨
     *   「武器種別：入れ墨」に装着可能か。未入力は×になる
     * Available: Unused Catalyst
     *   Can it be attached to Weapon type: Tattoo? No input becomes x */
    unsigned char canMountWep_Sorcery:1;

    /* 聖印
     *   「武器種別：聖印」に装着可能か。未入力は×になる
     * Available: Seal
     *   Can it be attached to Weapon Type: Holy Mark? No input becomes x */
    unsigned char canMountWep_Talisman:1;

    /* 小盾
     *   「武器種別：小盾」に装着可能か。未入力は×になる
     * Available: Small Shield
     *   Can it be attached to Weapon Type: Small Shield? No input becomes x */
    unsigned char canMountWep_ShieldSmall:1;

    /* 中盾
     *   「武器種別：中盾」に装着可能か。未入力は×になる
     * Available: Medium Shield
     *   Can it be attached to Weapon Type: Middle Shield? No input becomes x */
    unsigned char canMountWep_ShieldNormal:1;

    /* 大盾
     *   「武器種別：大盾」に装着可能か。未入力は×になる
     * Available: Greatshield
     *   Can it be attached to Weapon Type: Large Shield? No input becomes x */
    unsigned char canMountWep_ShieldLarge:1;

    /* 松明
     *   「武器種別：松明」に装着可能か。未入力は×になる
     * Available: Torch
     *   Can it be attached to Weapon type: Torch? No input becomes x */
    unsigned char canMountWep_Torch:1;

    /* Available: Hand-to-Hand
     *   Can it be attached to Weapon type: Hand-to-Hand? No input becomes x */
    unsigned char canMountWep_HandToHand:1;

    /* Available: Perfume Bottle
     *   Can it be attached to Weapon type: Perfume Bottle? No input becomes x */
    unsigned char canMountWep_PerfumeBottle:1;

    /* Available: Thrusting Shield
     *   Can it be attached to Weapon type: Thrusting Shield? No input becomes x */
    unsigned char canMountWep_ThrustingShield:1;

    /* Available: Throwing Weapon
     *   Can it be attached to Weapon type: Throwing Weapon? No input becomes x */
    unsigned char canMountWep_ThrowingWeapon:1;

    /* Available: Reverse-hand Sword
     *   Can it be attached to Weapon type: Reverse-hand Sword? No input becomes x */
    unsigned char canMountWep_ReverseHandSword:1;

    /* Available: Light Greatsword
     *   Can it be attached to Weapon type: Throwing Weapon? No input becomes x */
    unsigned char canMountWep_LightGreatsword:1;

    /* Available: Great Katana
     *   Can it be attached to Weapon type: Great Katana? No input becomes x */
    unsigned char canMountWep_GreatKatana:1;

    /* Available: Beast Claw
     *   Can it be attached to Weapon type: Beast Claw? No input becomes x */
    unsigned char canMountWep_BeastClaw:1;

    char reserved_canMountWep_0x3d_4:4;

    char reserved2_canMountWep[2];

    /* 効果テキストID00
     *   効果テキストID00(Gem_Effect)。ステータスに表示する魔石の効果テキスト
     * SpEffect Message ID [0]
     *   Effect text ID 00 (Gem_Effect). Magic stone effect text to display in status
     * Default Value  = -1 */
    int spEffectMsgId0;

    /* 効果テキストID01
     *   効果テキストID01(Gem_Effect)。ステータスに表示する魔石の効果テキスト
     * SpEffect Message ID [1]
     *   Effect text ID 01 (Gem_Effect). Magic stone effect text to display in status
     * Default Value  = -1 */
    int spEffectMsgId1;

    /* 攻撃ヒット時特殊効果ID00
     *   攻撃ヒット時用の特殊効果パラメータID
     * SpEffect ID - Attack Hit [0]
     *   Special effect parameter ID for attack hit
     * Default Value  = -1 */
    int spEffectId_forAtk0;

    /* 攻撃ヒット時特殊効果ID01
     *   攻撃ヒット時用の特殊効果パラメータID
     * SpEffect ID - Attack Hit [1]
     *   Special effect parameter ID for attack hit
     * Default Value  = -1 */
    int spEffectId_forAtk1;

    /* 攻撃ヒット時特殊効果ID02
     *   攻撃ヒット時用の特殊効果パラメータID
     * SpEffect ID - Attack Hit [2]
     *   Special effect parameter ID for attack hit
     * Default Value  = -1 */
    int spEffectId_forAtk2;

    /* 対応武器種別上書きテキストID
     *   対応武器種別上書きテキストID(-1:上書きしない)[MenuText]
     * Mount Weapon Text ID
     *   Corresponding Weapon Type Overwrite Text ID (-1: Do not overwrite) [Menu Text]
     * Default Value  = -1 */
    int mountWepTextId;

    char pad6[8];
} er_equip_param_gem_t;
