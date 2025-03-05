#pragma once

typedef struct er_multi_estus_flask_bonus_param_s {
    /* ホスト
     *   ホストのエスト回復数
     * Flask Recovery - Host
     *   Number of host est recovery */
    unsigned char host;

    /* 白サイン
     *   協力サインの白霊のエスト回復数
     * Flask Recovery - White Phantom - None
     *   Number of white spirits recovering from the cooperation sign */
    unsigned char WhiteGhost_None;

    /* 金霊（太陽）
     *   協力サインの金霊のエスト回復数
     * Flask Recovery - White Phantom - Gold
     *   Number of est recovery of gold spirits of cooperation sign */
    unsigned char WhiteGhost_Umbasa;

    /* 白バーサーカー
     *   協力サインの白バーサーカーのエスト回復数
     * Flask Recovery - White Phantom - Berserker
     *   Number of recovery of white Berserker's est of cooperation sign */
    unsigned char WhiteGhost_Berserker;

    /* 赤サイン
     *   敵対サインの赤霊のエスト回復数
     * Flask Recovery - Black Phantom - None
     *   Number of est recovery of red spirits of hostile sign */
    unsigned char BlackGhost_None_Sign;

    /* 赤金霊（サイン）
     *   敵対サインの赤金霊のエスト回復数
     * Flask Recovery - Black Phantom - Gold
     *   Number of est recovery of red gold spirit of hostile sign */
    unsigned char BlackGhost_Umbasa_Sign;

    /* 赤バーサーカー（サイン）
     *   敵対サインの赤バーサーカーのエスト回復数
     * Flask Recovery - Black Phantom - Berserker
     *   Number of est recovery of red Berserker of hostile sign */
    unsigned char BlackGhost_Berserker_Sign;

    /* 侵入
     *   侵入のエスト回復数
     * Flask Recovery - Black Phantom - None - Invasion
     *   Number of intrusion est recovery */
    unsigned char BlackGhost_None_Invade;

    /* 赤金霊（侵入）
     *   侵入オーブの赤金霊のエスト回復数
     * Flask Recovery - Black Phantom - Gold - Invasion
     *   Number of est recovery of red gold spirits of invading orbs */
    unsigned char BlackGhost_Umbasa_Invade;

    /* 赤バーサーカー（侵入）
     *   侵入オーブの赤バーサーカーのエスト回復数
     * Flask Recovery - Black Phantom - Berserker - Invasion
     *   Invasion Orb Red Berserker Est Recovery Number */
    unsigned char BlackGhost_Berserker_Invade;

    /* 救援ゲスト
     *   救援ゲストのエスト回復数
     * Flask Recovery - Red Hunter [1]
     *   Number of rescue guests' est recovery */
    unsigned char RedHunter1;

    /* 赤狩り霊２
     *   赤狩り霊２のエスト回復数
     * Flask Recovery - Red Hunter [2]
     *   Number of est recovery of Red Scare Spirit 2 */
    unsigned char RedHunter2;

    /* マップ守護霊(森)
     *   マップ守護霊（森）のエスト回復数
     * Flask Recovery - Forest Guardian
     *   Map guardian spirit (forest) est recovery number */
    unsigned char GuardianOfForest;

    /* マップ守護霊(アノール)
     *   マップ守護霊(アノール)のエスト回復数
     * Flask Recovery - Darkmoon Blade
     *   Map Guardian Spirit (Anor) Est Recovery Number */
    unsigned char GuardianOfAnor;

    /* 闘技場
     *   闘技場のエスト回復数
     * Flask Recovery - Arena
     *   Number of est recovery in the arena */
    unsigned char BattleRoyal;

    /* 黄衣の翁
     *   黄衣の翁のエスト回復数
     * Flask Recovery - Yellow Monk
     *   The number of est recovery of the old man in yellow */
    unsigned char YellowMonk;

    /* pad */
    char pad1[48];
} er_multi_estus_flask_bonus_param_t;
