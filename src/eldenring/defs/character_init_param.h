#pragma once

/* Defines instances of c0000 (player) characters in the game, including starting classes.
 * Note that many fields are not used and remain from earlier games, particularly with respect to starting classes.
 * Starting classes begin at 3000 with consecutive IDs, and starting gifts begin at 2400 likewise. */
typedef struct er_character_init_param_s {
    /* ＭＰ回復速度基本値[s]
     *   ＭＰが、1ポイント回復するまでの時間（小数点第一位）
     * Base FP Recovery Time
     *   Time until MP recovers 1 point (first decimal place) */
    float baseRec_mp;

    /* スタミナ回復速度基本値[s]
     *   スタミナが、1ポイント回復するまでの時間（小数点第一位）
     * Base Stamina Recovery Time
     *   Time to recover 1 point of stamina (first decimal place) */
    float baseRec_sp;

    /* 落下ダメージ軽減補正[%]
     *   他のキャラクターに上からのしかかれたときに、クッションとなりえるダメージ軽減量（％）（小数点第一位）
     * Characer Head Land - Damage Reduction
     *   Damage reduction amount (%) that can be a cushion when scolded by another character from above (first decimal place) */
    float red_Falldam;

    /* 初期ソウル
     *   初期に所持しているソウル量
     * Runes
     *   The amount of soul you have at the beginning */
    int soul;

    /* 右手武器スロット1
     *   装備品パラメータの武器ＩＤ(右手スロット１)
     * Equipped Weapon: Right Primary
     *   Weapon ID of equipment parameter (right hand slot 1)
     * Default Value  = -1 */
    int equip_Wep_Right;

    /* 右手武器スロット2
     *   装備品パラメータの武器ＩＤ(右手スロット２)
     * Equipped Weapon: Right Secondary
     *   Weapon ID of equipment parameter (right hand slot 2)
     * Default Value  = -1 */
    int equip_Subwep_Right;

    /* 左手武器スロット1
     *   装備品パラメータの武器ＩＤ(左手スロット１)
     * Equipped Weapon: Left Primary
     *   Weapon ID of equipment parameter (left hand slot 1)
     * Default Value  = -1 */
    int equip_Wep_Left;

    /* 左手武器スロット2
     *   装備品パラメータの武器ＩＤ(左手スロット２)
     * Equipped Weapon: Left Secondary
     *   Weapon ID of equipment parameter (left hand slot 2)
     * Default Value  = -1 */
    int equip_Subwep_Left;

    /* 頭防具
     *   装備品パラメータの防具ＩＤ(頭防具)
     * Equipped Armor: Head
     *   Equipment parameter armor ID (head armor)
     * Default Value  = -1 */
    int equip_Helm;

    /* 胴体防具
     *   装備品パラメータの防具ＩＤ(胴体防具)
     * Equipped Armor: Chest
     *   Equipment parameter armor ID (torso armor)
     * Default Value  = -1 */
    int equip_Armer;

    /* 腕防具
     *   装備品パラメータの防具ＩＤ(腕防具)
     * Equipped Armor: Arms
     *   Equipment parameter armor ID (arm armor)
     * Default Value  = -1 */
    int equip_Gaunt;

    /* 脚防具
     *   装備品パラメータの防具ＩＤ(脚防具)
     * Equipped Armor: Legs
     *   Equipment parameter armor ID (leg armor)
     * Default Value  = -1 */
    int equip_Leg;

    /* 矢
     *   装備品パラメータの武器ＩＤ(矢)
     * Equipped Ammunition: Arrow Primary
     *   Weapon ID (arrow) of equipment parameter
     * Default Value  = -1 */
    int equip_Arrow;

    /* ボルト
     *   装備品パラメータの武器ＩＤ(ボルト)
     * Equipped Ammunition: Bolt Primary
     *   Weapon ID (bolt) of equipment parameter
     * Default Value  = -1 */
    int equip_Bolt;

    /* 予備矢
     *   装備品パラメータの武器ＩＤ(矢予備)
     * Equipped Ammunition: Arrow Secondary
     *   Weapon ID of equipment parameter (arrow reserve)
     * Default Value  = -1 */
    int equip_SubArrow;

    /* 予備ボルト
     *   装備品パラメータの武器ＩＤ(ボルト予備)
     * Equipped Ammunition: Bolt Secondary
     *   Weapon ID of equipment parameter (spare bolt)
     * Default Value  = -1 */
    int equip_SubBolt;

    /* 装飾品1
     *   装備品パラメータの装飾品ＩＤ01
     * Equipped Accessory: Slot 1
     *   Equipment parameter decoration ID01
     * Default Value  = -1 */
    int equip_Accessory01;

    /* 装飾品2
     *   装備品パラメータの装飾品ＩＤ02
     * Equipped Accessory: Slot 2
     *   Equipment parameter decoration ID02
     * Default Value  = -1 */
    int equip_Accessory02;

    /* 装飾品3
     *   装備品パラメータの装飾品ＩＤ03
     * Equipped Accessory: Slot 3
     *   Equipment parameter decoration ID03
     * Default Value  = -1 */
    int equip_Accessory03;

    /* 装飾品4
     *   装備品パラメータの装飾品ＩＤ04
     * Equipped Accessory: Slot 4
     *   Equipment parameter decoration ID04
     * Default Value  = -1 */
    int equip_Accessory04;

    unsigned char unknown_0x50;

    unsigned char unknown_0x51;

    /* pad
     *   pad */
    char pad8[2];

    /* エリクサー用素材ID1
     *   エリクサー用素材ID1
     * Elixir Material 1
     *   Material ID1 for Elixir
     * Default Value  = -1 */
    int elixir_material00;

    /* エリクサー用素材ID2
     *   エリクサー用素材ID2
     * Elixir Material 2
     *   Material ID2 for Elixir
     * Default Value  = -1 */
    int elixir_material01;

    /* エリクサー用素材ID3
     *   エリクサー用素材ID3
     * Elixir Material 3
     *   Material ID3 for Elixir
     * Default Value  = -1 */
    int elixir_material02;

    /* 魔法・奇跡1
     *   初期配置の魔法・奇跡ID01
     * Equipped Spell: Slot 1
     *   Initial placement magic / miracle ID01
     * Default Value  = -1 */
    int equip_Spell_01;

    /* 魔法・奇跡2
     *   初期配置の魔法・奇跡ID02
     * Equipped Spell: Slot 2
     *   Initial placement magic / miracle ID02
     * Default Value  = -1 */
    int equip_Spell_02;

    /* 魔法・奇跡3
     *   初期配置の魔法・奇跡ID03
     * Equipped Spell: Slot 3
     *   Initial placement magic / miracle ID03
     * Default Value  = -1 */
    int equip_Spell_03;

    /* 魔法・奇跡4
     *   初期配置の魔法・奇跡ID04
     * Equipped Spell: Slot 4
     *   Initial placement magic / miracle ID04
     * Default Value  = -1 */
    int equip_Spell_04;

    /* 魔法・奇跡5
     *   初期配置の魔法・奇跡ID05
     * Equipped Spell: Slot 5
     *   Initial placement magic / miracle ID05
     * Default Value  = -1 */
    int equip_Spell_05;

    /* 魔法・奇跡6
     *   初期配置の魔法・奇跡ID06
     * Equipped Spell: Slot 6
     *   Initial placement magic / miracle ID06
     * Default Value  = -1 */
    int equip_Spell_06;

    /* 魔法・奇跡7
     *   初期配置の魔法・奇跡ID07
     * Equipped Spell: Slot 7
     *   Initial placement magic / miracle ID07
     * Default Value  = -1 */
    int equip_Spell_07;

    /* アイテム01
     *   初期所持のアイテムID01
     * Equipped Item: Slot 1
     *   Initial possession item ID 01
     * Default Value  = -1 */
    int item_01;

    /* アイテム02
     *   初期所持のアイテムID02
     * Equipped Item: Slot 2
     *   Initial possession item ID 02
     * Default Value  = -1 */
    int item_02;

    /* アイテム03
     *   初期所持のアイテムID03
     * Equipped Item: Slot 3
     *   Initial possession item ID 03
     * Default Value  = -1 */
    int item_03;

    /* アイテム04
     *   初期所持のアイテムID04
     * Equipped Item: Slot 4
     *   Initial possession item ID 04
     * Default Value  = -1 */
    int item_04;

    /* アイテム05
     *   初期所持のアイテムID05
     * Equipped Item: Slot 5
     *   Initial possession item ID 05
     * Default Value  = -1 */
    int item_05;

    /* アイテム06
     *   初期所持のアイテムID06
     * Equipped Item: Slot 6
     *   Initial possession item ID 06
     * Default Value  = -1 */
    int item_06;

    /* アイテム07
     *   初期所持のアイテムID07
     * Equipped Item: Slot 7
     *   Initial possession item ID 07
     * Default Value  = -1 */
    int item_07;

    /* アイテム08
     *   初期所持のアイテムID08
     * Equipped Item: Slot 8
     *   Initial possession item ID 08
     * Default Value  = -1 */
    int item_08;

    /* アイテム09
     *   初期所持のアイテムID09
     * Equipped Item: Slot 9
     *   Initial possession item ID 09
     * Default Value  = -1 */
    int item_09;

    /* アイテム10
     *   初期所持のアイテムID10
     * Equipped Item: Slot 10
     *   Initial possession item ID 10
     * Default Value  = -1 */
    int item_10;

    /* フェイスジェンパラメータID
     *   NPCプレイヤーで使用するフェイスジェンパラメータID。通常プレイヤーでは使用しません。
     * NPC Player - Face Gen ID
     *   Facegen parameter ID used by NPC players. Not used by normal players. */
    int npcPlayerFaceGenId;

    /* NPCプレイヤーの思考ID
     *   NPCプレイヤーで使用するNPC思考パラメータID。通常プレイヤーでは使用しません。
     * NPC Player - Think ID
     *   NPC Thinking Parameter ID used by NPC players. Not used by normal players. */
    int npcPlayerThinkId;

    /* ＨＰ基本値
     *   ＨＰの基本値（実際は、計算式で補正される）
     * Base HP
     *   Basic value of HP (actually, it is corrected by the calculation formula) */
    unsigned short baseHp;

    /* ＭＰ基本値
     *   ＭＰの基本値（実際は、計算式で補正される）
     * Base FP
     *   Basic value of MP (actually, it is corrected by the calculation formula) */
    unsigned short baseMp;

    /* スタミナ基本値
     *   スタミナの基本値（実際は、計算式で補正される）
     * Base Stamina
     *   Basic value of stamina (actually, it is corrected by the formula) */
    unsigned short baseSp;

    /* 矢の所持数
     *   矢の初期所持数
     * Equipped Ammunition: Arrow Primary Count
     *   Initial number of arrows */
    unsigned short arrowNum;

    /* ボルトの所持数
     *   ボルトの初期所持数
     * Equipped Ammunition: Bolt Primary Count
     *   Initial number of bolts */
    unsigned short boltNum;

    /* 予備矢の所持数
     *   矢の初期所持数
     * Equipped Ammunition: Arrow Secondary Count
     *   Initial number of arrows */
    unsigned short subArrowNum;

    /* 予備ボルトの所持数
     *   ボルトの初期所持数
     * Equipped Ammunition: Bolt Secondary Count
     *   Initial number of bolts */
    unsigned short subBoltNum;

    /* pad */
    char pad4[6];

    /* ソウルLv
     *   初期Lv
     * Level
     *   Initial Lv */
    short soulLv;

    /* 体力
     *   体力の基本値
     * Vigor
     *   Basic value of physical fitness */
    unsigned char baseVit;

    /* 精神
     *   精神の基本値
     * Attunement
     *   Basic value of spirit */
    unsigned char baseWil;

    /* 頑強
     *   頑強の基本値
     * Endurance
     *   Robust base value */
    unsigned char baseEnd;

    /* 筋力
     *   筋力の基本値
     * Strength
     *   Basic value of muscle strength */
    unsigned char baseStr;

    /* 俊敏
     *   俊敏の基本値
     * Dexterity
     *   Basic value of agility */
    unsigned char baseDex;

    /* 魔力
     *   魔力の基本値
     * Intelligence
     *   Basic value of magic power */
    unsigned char baseMag;

    /* 信仰
     *   信仰の基本値
     * Faith
     *   Basic value of faith */
    unsigned char baseFai;

    /* 運
     *   運の基本値
     * Arcane
     *   Basic value of luck */
    unsigned char baseLuc;

    /* 人間性
     *   人間性の基本値
     * Humanity
     *   Basic value of human nature */
    unsigned char baseHeroPoint;

    /* 耐久力
     *   耐久力の基本値
     * Vitality
     *   Basic value of endurance */
    unsigned char baseDurability;

    /* アイテム01の所持数
     *   初期所持のアイテム個数01
     * Equipped Item: Slot 1 Amount
     *   Initial possession number of items 01 */
    unsigned char itemNum_01;

    /* アイテム02の所持数
     *   初期所持のアイテム個数02
     * Equipped Item: Slot 2 Amount
     *   Initial possession number of items 02 */
    unsigned char itemNum_02;

    /* アイテム03の所持数
     *   初期所持のアイテム個数03
     * Equipped Item: Slot 3 Amount
     *   Initial possession number of items 03 */
    unsigned char itemNum_03;

    /* アイテム個数04
     *   初期所持のアイテム個数04
     * Equipped Item: Slot 4 Amount
     *   Initial possession number of items 04 */
    unsigned char itemNum_04;

    /* アイテム個数05
     *   初期所持のアイテム個数05
     * Equipped Item: Slot 5 Amount
     *   Initial possession number of items 05 */
    unsigned char itemNum_05;

    /* アイテム個数06
     *   初期所持のアイテム個数06
     * Equipped Item: Slot 6 Amount
     *   Initial possession number of items 06 */
    unsigned char itemNum_06;

    /* アイテム個数07
     *   初期所持のアイテム個数07
     * Equipped Item: Slot 7 Amount
     *   Initial possession number of items 07 */
    unsigned char itemNum_07;

    /* アイテム個数08
     *   初期所持のアイテム個数08
     * Equipped Item: Slot 8 Amount
     *   Initial possession number of items 08 */
    unsigned char itemNum_08;

    /* アイテム個数09
     *   初期所持のアイテム個数09
     * Equipped Item: Slot 9 Amount
     *   Initial possession number of items 09 */
    unsigned char itemNum_09;

    /* アイテム個数10
     *   初期所持のアイテム個数10
     * Equipped Item: Slot 10 Amount
     *   Initial possession number of items 10 */
    unsigned char itemNum_10;

    /* pad */
    char pad5[5];

    /* ジェスチャーID0
     *   ジェスチャー0番目(EzStateのジェスチャー0を再生したいなら0)
     * Equipped Gesture: Slot 0
     *   Gesture 0th (0 if you want to play EzState gesture 0)
     * Default Value  = -1 */
    char gestureId0;

    /* ジェスチャーID1
     *   ジェスチャー1番目(EzStateのジェスチャー0を再生したいなら0)
     * Equipped Gesture: Slot 1
     *   Gesture 1st (0 if you want to play EzState gesture 0)
     * Default Value  = -1 */
    char gestureId1;

    /* ジェスチャーID2
     *   ジェスチャー2番目(EzStateのジェスチャー0を再生したいなら0)
     * Equipped Gesture: Slot 2
     *   Gesture 2nd (0 if you want to play EzState's gesture 0)
     * Default Value  = -1 */
    char gestureId2;

    /* ジェスチャーID3
     *   ジェスチャー3番目(EzStateのジェスチャー0を再生したいなら0)
     * Equipped Gesture: Slot 3
     *   Gesture 3rd (0 if you want to play EzState gesture 0)
     * Default Value  = -1 */
    char gestureId3;

    /* ジェスチャーID4
     *   ジェスチャー4番目(EzStateのジェスチャー0を再生したいなら0)
     * Equipped Gesture: Slot 4
     *   Gesture 4th (0 if you want to play EzState's gesture 0)
     * Default Value  = -1 */
    char gestureId4;

    /* ジェスチャーID5
     *   ジェスチャー5番目(EzStateのジェスチャー0を再生したいなら0)
     * Equipped Gesture: Slot 5
     *   Gesture 5th (0 if you want to play EzState gesture 0)
     * Default Value  = -1 */
    char gestureId5;

    /* ジェスチャーID6
     *   ジェスチャー6番目(EzStateのジェスチャー0を再生したいなら0)
     * Equipped Gesture: Slot 6
     *   Gesture 6th (0 if you want to play EzState gesture 0)
     * Default Value  = -1 */
    char gestureId6;

    /* NPCプレイヤーのNPCタイプ
     *   NPCプレイヤーで使用するNPCタイプ。通常プレイヤーでは使用しません。
     * NPC Player - Type
     *   NPC type used by NPC players. Not used by normal players. */
    unsigned char npcPlayerType;

    /* NPCプレイヤーの描画タイプ
     *   NPCプレイヤーで使用する描画タイプ。通常プレイヤーでは使用しません。
     * NPC Player - Draw Type
     *   Drawing type used by NPC players. Not used by normal players. */
    char npcPlayerDrawType;

    /* NPCプレイヤーの性別
     *   NPCプレイヤーで使用する性別です。通常プレイヤーには反映しません。
     * NPC Player - Sex
     *   The gender used by NPC players. It is not reflected to normal players. */
    unsigned char npcPlayerSex;

    /* 誓約
     *   誓約タイプ(なし：0)
     * Vow Type
     *   Pledge type (None: 0) */
    unsigned char vowType:4;

    /* 送受信対象か
     *   送受信対象か（コピーNPC用）
     * Is Sync Target
     *   Is it a send / receive target (for copy NPCs)? */
    unsigned char isSyncTarget:1;

    char pad:3;

    /* pad */
    char pad6[2];

    /* 右手武器スロット1装備タイプ
     *   右手武器スロット１のパラメータ参照先
     * Weapon Param Type - Right Primary
     *   Right-handed weapon slot 1 parameter reference */
    unsigned char wepParamType_Right1;

    /* 右手武器スロット2装備タイプ
     *   右手武器スロット２のパラメータ参照先
     * Weapon Param Type - Right Secondary
     *   Right-handed weapon slot 2 parameter reference */
    unsigned char wepParamType_Right2;

    /* 右手武器スロット3装備タイプ
     *   右手武器スロット３のパラメータ参照先
     * Weapon Param Type - Right Tertiary
     *   Right-handed weapon slot 3 parameter reference */
    unsigned char wepParamType_Right3;

    /* 左手武器スロット1装備タイプ
     *   左手武器スロット１のパラメータ参照先
     * Weapon Param Type - Left Primary
     *   Parameter reference for left-handed weapon slot 1 */
    unsigned char wepParamType_Left1;

    /* 左手武器スロット2装備タイプ
     *   左手武器スロット２のパラメータ参照先
     * Weapon Param Type - Left Secondary
     *   Parameter reference for left-handed weapon slot 2 */
    unsigned char wepParamType_Left2;

    /* 左手武器スロット3装備タイプ
     *   左手武器スロット３のパラメータ参照先
     * Weapon Param Type - Left Tertiary
     *   Parameter reference for left-handed weapon slot 3 */
    unsigned char wepParamType_Left3;

    /* pad */
    char pad2[26];

    /* 右手武器スロット3
     *   装備品パラメータの武器ＩＤ(右手スロット３)
     * Equipped Weapon: Right Tertiary
     *   Weapon ID of equipment parameter (right hand slot 3)
     * Default Value  = -1 */
    int equip_Subwep_Right3;

    /* 左手武器スロット3
     *   装備品パラメータの武器ＩＤ(左手スロット３)
     * Equipped Weapon: Left Tertiary
     *   Weapon ID of equipment parameter (left hand slot 3)
     * Default Value  = -1 */
    int equip_Subwep_Left3;

    /* pad */
    char pad3[4];

    /* 第二アイテム01
     *   第二ショートカット初期所持のアイテムID01
     * Stored Item: Slot 1
     *   Item ID 01 of the second shortcut initial possession
     * Default Value  = -1 */
    int secondaryItem_01;

    /* 第二アイテム02
     *   第二ショートカット初期所持のアイテムID02
     * Stored Item: Slot 2
     *   Item ID 02 of the second shortcut initial possession
     * Default Value  = -1 */
    int secondaryItem_02;

    /* 第二アイテム03
     *   第二ショートカット初期所持のアイテムID03
     * Stored Item: Slot 3
     *   Item ID 03 of the second shortcut initial possession
     * Default Value  = -1 */
    int secondaryItem_03;

    /* 第二アイテム04
     *   第二ショートカット初期所持のアイテムID04
     * Stored Item: Slot 4
     *   Item ID 04 of the second shortcut initial possession
     * Default Value  = -1 */
    int secondaryItem_04;

    /* 第二アイテム05
     *   第二ショートカット初期所持のアイテムID05
     * Stored Item: Slot 5
     *   Item ID 05 of the second shortcut initial possession
     * Default Value  = -1 */
    int secondaryItem_05;

    /* 第二アイテム06
     *   第二ショートカット初期所持のアイテムID06
     * Stored Item: Slot 6
     *   Item ID 06 of the second shortcut initial possession
     * Default Value  = -1 */
    int secondaryItem_06;

    /* 第二アイテム01の所持数
     *   第二ショートカット初期所持のアイテム個数01
     * Stored Item: Slot 1 Count
     *   2nd Shortcut Initial possession number of items 01 */
    unsigned char secondaryItemNum_01;

    /* 第二アイテム02の所持数
     *   第二ショートカット初期所持のアイテム個数02
     * Stored Item: Slot 2 Count
     *   2nd Shortcut Initial possession number of items 02 */
    unsigned char secondaryItemNum_02;

    /* 第二アイテム03の所持数
     *   第二ショートカット初期所持のアイテム個数03
     * Stored Item: Slot 3 Count
     *   2nd Shortcut Initial possession number of items 03 */
    unsigned char secondaryItemNum_03;

    /* 第二アイテム04の所持数
     *   第二ショートカット初期所持のアイテム個数04
     * Stored Item: Slot 4 Count
     *   2nd Shortcut Initial possession number of items 04 */
    unsigned char secondaryItemNum_04;

    /* 第二アイテム05の所持数
     *   第二ショートカット初期所持のアイテム個数05
     * Stored Item: Slot 5 Count
     *   2nd Shortcut Initial possession number of items 05 */
    unsigned char secondaryItemNum_05;

    /* 第二アイテム06の所持数
     *   第二ショートカット初期所持のアイテム個数06
     * Stored Item: Slot 6 Count
     *   2nd Shortcut Initial possession number of items 06 */
    unsigned char secondaryItemNum_06;

    /* HPエスト瓶 所持限界数
     *   HPエスト瓶 所持限界数
     * HP Flask - Max Possession Limit
     *   HP Est Bottle Possession Limit
     * Default Value  = -1 */
    char HpEstMax;

    /* MPエスト瓶 所持限界数
     *   MPエスト瓶 所持限界数
     * FP Flask - Max Possession Limit
     *   MP Est Bottle Possession Limit
     * Default Value  = -1 */
    char MpEstMax;

    /* pad */
    char pad7[5];

    /* 声タイプ
     *   声タイプ
     * Voice Type
     *   Voice type */
    unsigned char voiceType;

    /* 予約領域
     *   予約領域 */
    char reserve[6];
} er_character_init_param_t;
