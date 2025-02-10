#pragma once

typedef struct estus_flask_recovery_param_s {
    /* ホスト
     *   ホストのエスト回復数
     * Host
     *   Number of host est recovery */
    unsigned char host;

    /* 侵入経路_オーブ_なし
     *   侵入経路がオーブの勢力のエスト回復数
     * Invasion Orb - None
     *   The number of est recovery of the power of the orb whose invasion route is */
    unsigned char invadeOrb_None;

    /* 侵入経路_オーブ_太陽
     *   侵入経路がオーブの勢力のエスト回復数
     * Invasion Orb - Gold
     *   The number of est recovery of the power of the orb whose invasion route is */
    unsigned char invadeOrb_Umbasa;

    /* 侵入経路_オーブ_バーサーカー
     *   侵入経路がオーブの勢力のエスト回復数
     * Invasion Orb - Berserker
     *   The number of est recovery of the power of the orb whose invasion route is */
    unsigned char invadeOrb_Berserker;

    /* 侵入経路_オーブ_罪人
     *   侵入経路がオーブの勢力のエスト回復数
     * Invasion Orb - Sinner
     *   The number of est recovery of the power of the orb whose invasion route is */
    unsigned char invadeOrb_Sinners;

    /* 侵入経路_サイン_なし
     *   侵入経路がサインの勢力のエスト回復数
     * Invasion Sign - None
     *   The number of est recovery of the power whose invasion route is a sign */
    unsigned char invadeSign_None;

    /* 侵入経路_サイン_太陽
     *   侵入経路がサインの勢力のエスト回復数
     * Invasion Sign - Gold
     *   The number of est recovery of the power whose invasion route is a sign */
    unsigned char invadeSign_Umbasa;

    /* 侵入経路_サイン_バーサーカー
     *   侵入経路がサインの勢力のエスト回復数
     * Invasion Sign - Berserker
     *   The number of est recovery of the power whose invasion route is a sign */
    unsigned char invadeSign_Berserker;

    /* 侵入経路_サイン_罪人
     *   侵入経路がサインの勢力のエスト回復数
     * Invasion Sign - Sinner
     *   The number of est recovery of the power whose invasion route is a sign */
    unsigned char invadeSign_Sinners;

    /* 侵入経路_指輪_罪人
     *   侵入経路が指輪の勢力のエスト回復数
     * Invasion Ring - Sinner
     *   The number of est recovery of the power of the ring whose invasion route is */
    unsigned char invadeRing_Sinners;

    /* 侵入経路_指輪_ボス守(ロザリア)
     *   侵入経路が指輪の勢力のエスト回復数
     * Invasion Ring - Rosalia
     *   The number of est recovery of the power of the ring whose invasion route is */
    unsigned char invadeRing_Rosalia;

    /* 侵入経路_指輪_マップ守(森)
     *   侵入経路が指輪の勢力のエスト回復数
     * Invasion Ring - Forest
     *   The number of est recovery of the power of the ring whose invasion route is */
    unsigned char invadeRing_Forest;

    /* 協力経路_サイン_なし
     *   協力経路がサインの勢力のエスト回復数
     * Coop Sign - None
     *   The number of est recovery of the power whose cooperation route is a sign */
    unsigned char coopSign_None;

    /* 協力経路_サイン_太陽
     *   協力経路がサインの勢力のエスト回復数
     * Coop Sign - Gold
     *   The number of est recovery of the power whose cooperation route is a sign */
    unsigned char coopSign_Umbasa;

    /* 協力経路_サイン_バーサーカー
     *   協力経路がサインの勢力のエスト回復数
     * Coop Sign - Berserker
     *   The number of est recovery of the power whose cooperation route is a sign */
    unsigned char coopSign_Berserker;

    /* 協力経路_サイン_罪人
     *   協力経路がサインの勢力のエスト回復数
     * Coop Sign - Sinner
     *   The number of est recovery of the power whose cooperation route is a sign */
    unsigned char coopSign_Sinners;

    /* 協力経路_指輪 _赤狩り
     *   協力経路が指輪の勢力のエスト回復数
     * Coop Sign - Red Hunter
     *   Cooperation route is the number of est recovery of the power of the ring */
    unsigned char coopRing_RedHunter;

    /* 侵入経路_指輪_マップ守(アノール)
     *   侵入経路が指輪の勢力のエスト回復数
     * Invasion Ring - Darkmoon Blade
     *   The number of est recovery of the power of the ring whose invasion route is */
    unsigned char invadeRing_Anor;

    /* 回復数パラメータ差し替え率
     *   回復数パラメータ差し替え率
     * Replacement Rate
     *   Recovery number Parameter replacement rate */
    unsigned short paramReplaceRate;

    /* 回復数パラメータ差し替え先ID
     *   回復数パラメータ差し替え先ID
     * Replace ID
     *   Recovery number Parameter replacement destination ID
     * Default Value  = -1 */
    int paramReplaceId;

    char pad[8];
} estus_flask_recovery_param_t;
