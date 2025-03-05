#pragma once

/* Defines upgrades of Armor. Unused in Elden Ring.
 * Tailoring is handled by a shop and functions as total item replacement, not variation. */
typedef struct er_reinforce_param_protector_s {
    /* 物理防御力
     *   物理防御力の補正値
     * Defence %: Physical
     *   Physical defense correction value
     * Default Value  = 1 */
    float physicsDefRate;

    /* 魔法防御力
     *   魔法防御力の補正値
     * Defence %: Magic
     *   Magic defense correction value
     * Default Value  = 1 */
    float magicDefRate;

    /* 炎防御力
     *   炎防御力の補正値
     * Defence %: Fire
     *   Fire defense correction value
     * Default Value  = 1 */
    float fireDefRate;

    /* 電撃防御力
     *   電撃防御力の補正値
     * Defence %: Lightning
     *   Electric shock defense correction value
     * Default Value  = 1 */
    float thunderDefRate;

    /* 斬撃防御力
     *   斬撃防御力の補正値
     * Defence %: Slash
     *   Slash defense correction value
     * Default Value  = 1 */
    float slashDefRate;

    /* 打撃防御力
     *   打撃防御力の補正値
     * Defence %: Strike
     *   Impact defense correction value
     * Default Value  = 1 */
    float blowDefRate;

    /* 刺突防御力
     *   刺突防御力の補正値
     * Defence %: Thrust
     *   Correction value of piercing defense power
     * Default Value  = 1 */
    float thrustDefRate;

    /* 毒耐性
     *   毒耐性の補正値
     * Aux Resist %: Poison
     *   Poison resistance correction value
     * Default Value  = 1 */
    float resistPoisonRate;

    /* 疫病耐性
     *   疫病耐性の補正値
     * Aux Resist %: Scarlet Rot
     *   Epidemic resistance correction value
     * Default Value  = 1 */
    float resistDiseaseRate;

    /* 出血耐性
     *   出血耐性の補正値
     * Aux Resist %: Hemorrhage
     *   Bleeding resistance correction value
     * Default Value  = 1 */
    float resistBloodRate;

    /* 呪耐性
     *   呪耐性の補正値
     * Aux Resist %: Blight
     *   Curse resistance correction value
     * Default Value  = 1 */
    float resistCurseRate;

    /* 常駐特殊効果ID1
     *   常駐特殊効果ID1の加算補正値
     * Passive SpEffect ID [1] Offset
     *   Addition correction value for resident special effect ID1 */
    unsigned char residentSpEffectId1;

    /* 常駐特殊効果ID2
     *   常駐特殊効果ID2の加算補正値
     * Passive SpEffect ID [2] Offset
     *   Addition correction value for resident special effect ID2 */
    unsigned char residentSpEffectId2;

    /* 常駐特殊効果ID3
     *   常駐特殊効果ID3の加算補正値
     * Passive SpEffect ID [3] Offset
     *   Addition correction value for resident special effect ID3 */
    unsigned char residentSpEffectId3;

    /* 素材ID加算値
     *   素材パラメータIDの加算補正値
     * Reinforcement Material Set ID
     *   Addition correction value of material parameter ID */
    unsigned char materialSetId;

    /* 闇防御力
     *   闇防御力の補正値
     * Absorption %: Holy
     *   Dark defense correction value
     * Default Value  = 1 */
    float darkDefRate;

    /* 冷気耐性
     *   冷気耐性の補正値
     * Aux Resist %: Frost
     *   Cold resistance correction value
     * Default Value  = 1 */
    float resistFreezeRate;

    /* 睡眠耐性
     *   睡眠耐性の補正値
     * Aux Resist %: Sleep
     *   Correction value for sleep tolerance
     * Default Value  = 1 */
    float resistSleepRate;

    /* 発狂耐性
     *   発狂耐性の補正値
     * Aux Resist %: Madness
     *   Madness resistance correction value
     * Default Value  = 1 */
    float resistMadnessRate;
} er_reinforce_param_protector_t;
