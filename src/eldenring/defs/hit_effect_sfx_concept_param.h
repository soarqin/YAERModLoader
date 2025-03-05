#pragma once

typedef struct er_hit_effect_sfx_concept_param_s {
    /* 鉄製：概念１
     *   鉄製：概念１
     * Iron [1]
     *   Iron: Concept 1 */
    short atkIron_1;

    /* 鉄製：概念２
     *   鉄製：概念２
     * Iron [2]
     *   Iron: Concept 2 */
    short atkIron_2;

    /* 革製：概念１
     *   革：概念１
     * Leather [1]
     *   Leather: Concept 1 */
    short atkLeather_1;

    /* 革製：概念２
     *   革：概念２
     * Leather [2]
     *   Leather: Concept 2 */
    short atkLeather_2;

    /* 木製：概念１
     *   木製：概念１
     * Wood [1]
     *   Wooden: Concept 1 */
    short atkWood_1;

    /* 木製：概念２
     *   木製：概念２
     * Wood [2]
     *   Wooden: Concept 2 */
    short atkWood_2;

    /* 肉：概念１
     *   肉：概念１
     * Flesh [1]
     *   Meat: Concept 1 */
    short atkBody_1;

    /* 肉：概念２
     *   肉：概念２
     * Flesh [2]
     *   Meat: Concept 2 */
    short atkBody_2;

    /* 石製：概念１
     *   蝕：概念１
     * Stone [1]
     *   Corrosion: Concept 1 */
    short atkStone_1;

    /* 石製：概念２
     *   蝕：概念２
     * Stone [2]
     *   Corrosion: Concept 2 */
    short atkStone_2;

    char pad[4];

    /* なし：概念１
     *   なし：概念１
     * None [1]
     *   None: Concept 1 */
    short atkNone_1;

    /* なし：概念２
     *   なし：概念２
     * None [2]
     *   None: Concept 2 */
    short atkNone_2;

    /* 予約領域 */
    char reserve[52];
} er_hit_effect_sfx_concept_param_t;
