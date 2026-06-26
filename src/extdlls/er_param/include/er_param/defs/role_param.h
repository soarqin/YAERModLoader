#pragma once

typedef struct er_role_param_s {
    /* チームタイプ
     *   チームタイプ
     * Team Type
     *   Team type */
    unsigned char teamType;

    char pad10[3];

    /* ファントムパラメータID(誓約ランク0)
     *   誓約ランクが0のときのファントムパラメータID
     * Phantom Param ID - Vow [0]
     *   Phantom parameter ID when pledge rank is 0
     * Default Value  = -1 */
    int phantomParamId;

    /* 常駐特殊効果0
     *   常駐特殊効果0
     * SpEffect ID [0]
     *   Resident special effect 0
     * Default Value  = -1 */
    int spEffectID0;

    /* 常駐特殊効果1
     *   常駐特殊効果1
     * SpEffect ID [1]
     *   Resident special effect 1
     * Default Value  = -1 */
    int spEffectID1;

    /* 常駐特殊効果2
     *   常駐特殊効果2
     * SpEffect ID [2]
     *   Resident special effect 2
     * Default Value  = -1 */
    int spEffectID2;

    /* 常駐特殊効果3
     *   常駐特殊効果3
     * SpEffect ID [3]
     *   Resident special effect 3
     * Default Value  = -1 */
    int spEffectID3;

    /* 常駐特殊効果4
     *   常駐特殊効果4
     * SpEffect ID [4]
     *   Resident special effect 4
     * Default Value  = -1 */
    int spEffectID4;

    /* 常駐特殊効果5
     *   常駐特殊効果5
     * SpEffect ID [5]
     *   Resident special effect 5
     * Default Value  = -1 */
    int spEffectID5;

    /* 常駐特殊効果6
     *   常駐特殊効果6
     * SpEffect ID [6]
     *   Resident special effect 6
     * Default Value  = -1 */
    int spEffectID6;

    /* 常駐特殊効果7
     *   常駐特殊効果7
     * SpEffect ID [7]
     *   Resident special effect 7
     * Default Value  = -1 */
    int spEffectID7;

    /* 常駐特殊効果8
     *   常駐特殊効果8
     * SpEffect ID [8]
     *   Resident special effect 8
     * Default Value  = -1 */
    int spEffectID8;

    /* 常駐特殊効果9
     *   常駐特殊効果9
     * SpEffect ID [9]
     *   Resident special effect 9
     * Default Value  = -1 */
    int spEffectID9;

    /* SOSサインSFX ID
     *   他の人が出したSOSサインSFX ID
     * Summon Sign - SFX ID
     *   SOS sign SFX ID issued by another person */
    int sosSignSfxId;

    /* 自分が出したSOSサインSFX ID
     *   自分が出したSOSサインSFX ID
     * Personal Summon Sign - SFX ID
     *   SOS sign SFX ID issued by me */
    int mySosSignSfxId;

    /* 召喚された時のアニメID(プレイヤ)
     *   プレイヤが召喚されてゲーム開始するときに再生するアニメID
     * Player Summon Start - Animation ID
     *   Anime ID to play when the player is summoned and the game starts */
    int summonStartAnimId;

    /* 報酬アイテム抽選ID_マップ用
     *   獲得報酬のアイテム抽選パラメータID_マップ用(-1で無し)
     * Map Itemlot Param ID
     *   Acquisition reward item lottery parameter ID_for map (not -1)
     * Default Value  = -1 */
    int itemlotParamId;

    /* ボイスチャットグループ
     *   ボイスチャットグループ
     * Voice Chat Group
     *   Voice chat group */
    unsigned char voiceChatGroup;

    /* ロール名テキストカラー
     *   ネットワークPCのFEに表示するロール名テキストの色
     * Role Name Color
     *   The color of the role name text displayed on the FE of the network PC */
    unsigned char roleNameColor;

    char pad1[2];

    /* ロール名テキストID
     *   ネットワークPCのFEに表示するロール名のテキストID
     * Role Name - Text ID
     *   Text ID of the role name to be displayed on the FE of the network PC */
    int roleNameId;

    /* 脅威度
     *   脅威度
     * Threat Level
     *   Threat level */
    unsigned int threatLv;

    /* ファントムパラメータID(誓約ランク1)
     *   誓約ランクが1のときのファントムパラメータID
     * Phantom Param ID - Vow Rank [1]
     *   Phantom parameter ID when pledge rank is 1
     * Default Value  = -1 */
    int phantomParamId_vowRank1;

    /* ファントムパラメータID(誓約ランク2)
     *   誓約ランクが2のときのファントムパラメータID
     * Phantom Param ID - Vow Rank [2]
     *   Phantom parameter ID when pledge rank is 2
     * Default Value  = -1 */
    int phantomParamId_vowRank2;

    /* ファントムパラメータID(誓約ランク3)
     *   誓約ランクが3のときのファントムパラメータID
     * Phantom Param ID - Vow Rank [3]
     *   Phantom parameter ID when pledge rank is 3
     * Default Value  = -1 */
    int phantomParamId_vowRank3;

    /* SFX用特殊効果ID(誓約ランク0)
     *   誓約ランク0のときのSFX用特殊効果ID
     * Phantom Param ID - Vow Rank [4]
     *   Special effect ID for SFX when pledge rank 0
     * Default Value  = -1 */
    int spEffectID_vowRank0;

    /* SFX用特殊効果ID(誓約ランク1)
     *   誓約ランク1のときのSFX用特殊効果ID
     * Phantom Param ID - Vow Rank [5]
     *   Special effect ID for SFX when pledge rank 1
     * Default Value  = -1 */
    int spEffectID_vowRank1;

    /* SFX用特殊効果ID(誓約ランク2)
     *   誓約ランク2のときのSFX用特殊効果ID
     * Phantom Param ID - Vow Rank [6]
     *   Special effect ID for SFX when pledge rank 2
     * Default Value  = -1 */
    int spEffectID_vowRank2;

    /* SFX用特殊効果ID(誓約ランク3)
     *   誓約ランク3のときのSFX用特殊効果ID
     * Phantom Param ID - Vow Rank [7]
     *   Special effect ID for SFX when pledge rank 3
     * Default Value  = -1 */
    int spEffectID_vowRank3;

    /* サイン幻影用のファントムID
     *   マルチプレイ誓約霊体用　サイン幻影用のファントムID指定
     * Ghost Phantom ID
     *   Multiplayer pledge ghost body sign phantom ID designation for illusion
     * Default Value  = -1 */
    int signPhantomId;

    /* 召喚された時のアニメID(プレイヤ以外)
     *   プレイヤ以外が召喚されてゲーム開始するときに再生するアニメID
     * NPC Summon Start - Animation ID
     *   Anime ID to play when a player other than the player is summoned and the game starts */
    int nonPlayerSummonStartAnimId;

    char pad2[16];
} er_role_param_t;
