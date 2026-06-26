#pragma once

typedef struct er_network_msg_param_s {
    /* 優先度
     *   優先度
     * Priority
     *   priority */
    unsigned short priority;

    /* 強制割り込み
     *   強制割り込み
     * Force Play
     *   Forced interrupt */
    unsigned char forcePlay;

    /* 予約
     *   予約 */
    char pad1[1];

    /* 白霊（白サイン）
     *   白霊（白サイン）
     * White Phantom - Normal
     *   White spirit (white sign)
     * Default Value  = -1 */
    int normalWhite;

    /* 太陽霊（白サイン）
     *   太陽霊（白サイン）
     * White Phantom - Gold
     *   Sun spirit (white sign)
     * Default Value  = -1 */
    int umbasaWhite;

    /* バーサーカー霊（白サイン）
     *   バーサーカー霊（白サイン）
     * White Phantom - Berseker
     *   Berserker spirit (white sign)
     * Default Value  = -1 */
    int berserkerWhite;

    /* 罪人英雄霊（白サイン ）
     *   罪人英雄霊（白サイン ）
     * White Phantom - Sinner Hero
     *   Sinner Hero Spirit (white sign)
     * Default Value  = -1 */
    int sinnerHeroWhite;

    /* 闇霊（赤サイン）
     *   闇霊（赤サイン）
     * Black Phantom - Normal
     *   Dark spirit (red sign)
     * Default Value  = -1 */
    int normalBlack;

    /* 太陽霊（赤サイン）
     *   太陽霊（赤サイン）
     * Black Phantom - Gold
     *   Sun spirit (red sign)
     * Default Value  = -1 */
    int umbasaBlack;

    /* バーサーカー霊（赤サイン）
     *   バーサーカー霊（赤サイン）
     * Black Phantom - Berserker
     *   Berserker spirit (red sign)
     * Default Value  = -1 */
    int berserkerBlack;

    /* 侵入_A
     *   侵入_A
     * Invasion - Black Phantom - Normal
     *   Intrusion_A
     * Default Value  = -1 */
    int forceJoinBlack;

    /* 太陽霊（乱入）
     *   太陽霊（乱入）
     * Invasion - Black Phantom - Gold
     *   Sun spirit (intrusion)
     * Default Value  = -1 */
    int forceJoinUmbasaBlack;

    /* バーサーカー霊（乱入）
     *   バーサーカー霊（乱入）
     * Invasion - Black Phantom - Berserker
     *   Berserker spirit (intrusion)
     * Default Value  = -1 */
    int forceJoinBerserkerBlack;

    /* 罪人狩り霊（訪問）
     *   罪人狩り霊（訪問）
     * Sinner Hunter Visitor
     *   Sinner hunting spirit (visit)
     * Default Value  = -1 */
    int sinnerHunterVisitor;

    /* 赤狩り霊（訪問）
     *   赤狩り霊（訪問）
     * Red Hunter 1 Visitor
     *   Red Scare Spirit (Visit)
     * Default Value  = -1 */
    int redHunterVisitor;

    /* ボス守護霊（訪問）
     *   ボス守護霊（訪問）
     * Boss Guardian Visitor
     *   Boss guardian spirit (visit)
     * Default Value  = -1 */
    int guardianOfBossVisitor;

    /* マップ守護霊_森（訪問）
     *   マップ守護霊_森（訪問）
     * Forest Hunter Visitor
     *   Map Guardian Spirit_Forest (Visit)
     * Default Value  = -1 */
    int guardianOfForestMapVisitor;

    /* マップ守護霊_アノール（訪問）
     *   マップ守護霊_アノール（訪問）
     * Darkmoon Blade Visitor
     *   Map Guardian_Anor (Visit)
     * Default Value  = -1 */
    int guardianOfAnolisVisitor;

    /* ロザリア霊（赤サイン）
     *   ロザリア霊（赤サイン）
     * Black Phantom - Rosalia
     *   Rosalia spirit (red sign)
     * Default Value  = -1 */
    int rosaliaBlack;

    /* ロザリア霊（乱入）
     *   ロザリア霊（乱入）
     * Invasion - Black Phantom - Rosalia
     *   Rosalia spirit (intrusion)
     * Default Value  = -1 */
    int forceJoinRosaliaBlack;

    /* 赤狩り霊2（訪問）
     *   赤狩り霊2（訪問）
     * Red Hunter 2 Visitor
     *   Red Scare Spirit 2 (Visit)
     * Default Value  = -1 */
    int redHunterVisitor2;

    /* NPC擬似マルチ1
     *   NPC擬似マルチ1
     * NPC [1]
     *   NPC Pseudo Multi 1
     * Default Value  = -1 */
    int npc1;

    /* NPC擬似マルチ2
     *   NPC擬似マルチ2
     * NPC [2]
     *   NPC Pseudo Multi 2
     * Default Value  = -1 */
    int npc2;

    /* NPC擬似マルチ3
     *   NPC擬似マルチ3
     * NPC [3]
     *   NPC Pseudo Multi 3
     * Default Value  = -1 */
    int npc3;

    /* NPC擬似マルチ4
     *   NPC擬似マルチ4
     * NPC [4]
     *   NPC Pseudo Multi 4
     * Default Value  = -1 */
    int npc4;

    /* バトルロイヤル
     *   バトルロイヤル
     * Arena
     *   Battle royale
     * Default Value  = -1 */
    int battleRoyal;

    /* NPC擬似マルチ5
     *   NPC擬似マルチ5
     * NPC [5]
     *   NPC Pseudo Multi 5
     * Default Value  = -1 */
    int npc5;

    /* NPC擬似マルチ6
     *   NPC擬似マルチ6
     * NPC [6]
     *   NPC Pseudo Multi 6
     * Default Value  = -1 */
    int npc6;

    /* NPC擬似マルチ7
     *   NPC擬似マルチ7
     * NPC [7]
     *   NPC Pseudo Multi 7
     * Default Value  = -1 */
    int npc7;

    /* NPC擬似マルチ8
     *   NPC擬似マルチ8
     * NPC [8]
     *   NPC Pseudo Multi 8
     * Default Value  = -1 */
    int npc8;

    /* NPC擬似マルチ9
     *   NPC擬似マルチ9
     * NPC [9]
     *   NPC Pseudo Multi 9
     * Default Value  = -1 */
    int npc9;

    /* NPC擬似マルチ10
     *   NPC擬似マルチ10
     * NPC [10]
     *   NPC Pseudo Multi 10
     * Default Value  = -1 */
    int npc10;

    /* NPC擬似マルチ11
     *   NPC擬似マルチ11
     * NPC [11]
     *   NPC Pseudo Multi 11
     * Default Value  = -1 */
    int npc11;

    /* NPC擬似マルチ12
     *   NPC擬似マルチ12
     * NPC [12]
     *   NPC Pseudo Multi 12
     * Default Value  = -1 */
    int npc12;

    /* NPC擬似マルチ13
     *   NPC擬似マルチ13
     * NPC [13]
     *   NPC Pseudo Multi 13
     * Default Value  = -1 */
    int npc13;

    /* NPC擬似マルチ14
     *   NPC擬似マルチ14
     * NPC [14]
     *   NPC Pseudo Multi 14
     * Default Value  = -1 */
    int npc14;

    /* NPC擬似マルチ15
     *   NPC擬似マルチ15
     * NPC [15]
     *   NPC Pseudo Multi 15
     * Default Value  = -1 */
    int npc15;

    /* NPC擬似マルチ16
     *   NPC擬似マルチ16
     * NPC [16]
     *   NPC Pseudo Multi 16
     * Default Value  = -1 */
    int npc16;

    /* 侵入_B
     *   侵入_B
     * Invasion - Black Phantom - B
     *   Intrusion_B
     * Default Value  = -1 */
    int forceJoinBlack_B;

    /* 白霊（白サイン）_NPC用
     *   白霊（白サイン）_NPC用
     * NPC - White Phantom
     *   White spirit (white sign) for NPCs
     * Default Value  = -1 */
    int normalWhite_Npc;

    /* 侵入_A_NPC用
     *   侵入_A_NPC用
     * NPC - Black Phantom - Invasion
     *   For intrusion_A_NPCs
     * Default Value  = -1 */
    int forceJoinBlack_Npc;

    /* 侵入_B_NPC用
     *   侵入_B_NPC用
     * NPC - Black Phantom B - Invasion
     *   For intrusion_B_NPCs
     * Default Value  = -1 */
    int forceJoinBlack_B_Npc;

    /* 侵入_C_NPC用
     *   侵入_C_NPC用
     * NPC - Black Phantom C - Invasion
     *   For intrusion_C_NPCs
     * Default Value  = -1 */
    int forceJoinBlack_C_Npc;

    int unknown_0xa4;

    int unknown_0xa8;

    int unknown_0xac;

    int unknown_0xb0;

    int unknown_0xb4;

    /* 予約
     *   予約 */
    char pad2_new[8];
} er_network_msg_param_t;
