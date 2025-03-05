#pragma once

typedef struct er_multi_soul_bonus_rate_param_s {
    /* ホスト
     *   ホストの報酬ソウル倍率
     * Rune Reward Multiplier - Host
     *   Host reward soul multiplier */
    float host;

    /* 白サイン
     *   協力サインの白霊の報酬ソウル倍率
     * Rune Reward Multiplier - White Phantom - None
     *   Cooperation sign white spirit reward soul multiplier */
    float WhiteGhost_None;

    /* 金霊（太陽）
     *   協力サインの金霊の報酬ソウル倍率
     * Rune Reward Multiplier - White Phantom - Gold
     *   Cooperative sign gold spirit reward soul multiplier */
    float WhiteGhost_Umbasa;

    /* 白バーサーカー
     *   協力サインの白バーサーカーの報酬ソウル倍率
     * Rune Reward Multiplier - White Phantom - Berserker
     *   Cooperation sign white Berserker reward soul multiplier */
    float WhiteGhost_Berserker;

    /* 赤サイン
     *   敵対サインの赤霊の報酬ソウル倍率
     * Rune Reward Multiplier - Black Phantom - None
     *   Hostile sign red spirit reward soul multiplier */
    float BlackGhost_None_Sign;

    /* 赤金霊（サイン）
     *   敵対サインの赤金霊の報酬ソウル倍率
     * Rune Reward Multiplier - Black Phantom - Gold
     *   Hostile sign red gold spirit reward soul multiplier */
    float BlackGhost_Umbasa_Sign;

    /* 赤バーサーカー（サイン）
     *   敵対サインの赤バーサーカーの報酬ソウル倍率
     * Rune Reward Multiplier - Black Phantom - Berserker
     *   Hostile sign red berserker reward soul multiplier */
    float BlackGhost_Berserker_Sign;

    /* 侵入
     *   侵入の報酬ソウル倍率
     * Rune Reward Multiplier - Black Phantom - None - Invade
     *   Invasion reward Soul multiplier */
    float BlackGhost_None_Invade;

    /* 赤金霊（侵入）
     *   侵入オーブの赤金霊の報酬ソウル倍率
     * Rune Reward Multiplier - Black Phantom - Gold - Invade
     *   Invasion Orb's Red Gold Spirit Reward Soul Multiplier */
    float BlackGhost_Umbasa_Invade;

    /* 赤バーサーカー（侵入）
     *   侵入オーブの赤バーサーカーの報酬ソウル倍率
     * Rune Reward Multiplier - Black Phantom - Berserker - Invade
     *   Invasion Orb Red Berserker Reward Soul Multiplier */
    float BlackGhost_Berserker_Invade;

    /* 救援ゲスト
     *   救援ゲストの報酬ソウル倍率
     * Rune Reward Multiplier - Red Hunter [1]
     *   Relief guest reward soul multiplier */
    float RedHunter1;

    /* 赤狩り霊２
     *   赤狩り霊２の報酬ソウル倍率
     * Rune Reward Multiplier - Red Hunter [2]
     *   Red Scare Spirit 2 Reward Soul Multiplier */
    float RedHunter2;

    /* マップ守護霊(森)
     *   マップ守護霊（森）の報酬ソウル倍率
     * Rune Reward Multiplier - Forest Guardian
     *   Map Guardian Spirit (Forest) Reward Soul Magnification */
    float GuardianOfForest;

    /* マップ守護霊(アノール)
     *   マップ守護霊(アノール)の報酬ソウル倍率
     * Rune Reward Multiplier - Darkmoon Blade
     *   Map Guardian Spirit (Anor) Reward Soul Multiplier */
    float GuardianOfAnor;

    /* 闘技場
     *   闘技場の報酬ソウル倍率
     * Rune Reward Multiplier - Arena
     *   Arena reward soul multiplier */
    float BattleRoyal;

    /* 黄衣の翁
     *   黄衣の翁の報酬ソウル倍率
     * Rune Reward Multiplier - Yellow Monk
     *   Yellow robe's old man's reward soul multiplier */
    float YellowMonk;

    /* pad */
    char pad1[64];
} er_multi_soul_bonus_rate_param_t;
