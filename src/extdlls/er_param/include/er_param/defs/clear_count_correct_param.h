#pragma once

typedef struct er_clear_count_correct_param_s {
    /* 《最大HP倍率[%]》
     *   最大HP倍率[%]
     * Max HP %
     *   Maximum HP magnification [%]
     * Default Value  = 1 */
    float MaxHpRate;

    /* 《最大MP倍率[%]》
     *   最大MP倍率[%]
     * Max FP %
     *   Maximum MP magnification [%]
     * Default Value  = 1 */
    float MaxMpRate;

    /* 《最大スタミナ倍率[%]》
     *   最大スタミナ倍率[%]
     * Max Stamina %
     *   Maximum stamina magnification [%]
     * Default Value  = 1 */
    float MaxStaminaRate;

    /* 《物理攻撃力倍率》
     *   物理攻撃力倍率
     * Damage %: Physical
     *   Physical attack power multiplier
     * Default Value  = 1 */
    float PhysicsAttackRate;

    /* 《斬撃攻撃力倍率》
     *   斬撃攻撃力倍率
     * Damage %: Slash
     *   Slash attack power multiplier
     * Default Value  = 1 */
    float SlashAttackRate;

    /* 《打撃攻撃力倍率》
     *   打撃攻撃力倍率
     * Damage %: Strike
     *   Batter attack power multiplier
     * Default Value  = 1 */
    float BlowAttackRate;

    /* 《刺突攻撃力倍率》
     *   刺突攻撃力倍率
     * Damage %: Thrust
     *   Puncture attack power multiplier
     * Default Value  = 1 */
    float ThrustAttackRate;

    /* 《無属性攻撃力倍率》
     *   無属性攻撃力倍率
     * Damage %: Standard
     *   Non-attribute attack power multiplier
     * Default Value  = 1 */
    float NeturalAttackRate;

    /* 《魔法攻撃力倍率》
     *   魔法攻撃力倍率
     * Damage %: Magic
     *   Magic attack power multiplier
     * Default Value  = 1 */
    float MagicAttackRate;

    /* 《炎攻撃力倍率》
     *   炎攻撃力倍率
     * Damage %: Fire
     *   Fire attack power multiplier
     * Default Value  = 1 */
    float FireAttackRate;

    /* 《電撃攻撃力倍率》
     *   電撃攻撃力倍率
     * Damage %: Lightning
     *   Electric shock attack power multiplier
     * Default Value  = 1 */
    float ThunderAttackRate;

    /* 《闇攻撃力倍率》
     *   闇攻撃力倍率
     * Damage %: Holy
     *   Dark attack power multiplier
     * Default Value  = 1 */
    float DarkAttackRate;

    /* 《物理防御力倍率》
     *   物理防御力倍率
     * Defence %: Physical
     *   Physical defense power multiplier
     * Default Value  = 1 */
    float PhysicsDefenseRate;

    /* 《魔法防御力倍率》
     *   魔法防御力倍率
     * Defence %: Magic
     *   Magic defense multiplier
     * Default Value  = 1 */
    float MagicDefenseRate;

    /* 《炎防御力倍率》
     *   炎防御力倍率
     * Defence %: Fire
     *   Fire defense multiplier
     * Default Value  = 1 */
    float FireDefenseRate;

    /* 《電撃防御力倍率》
     *   電撃防御力倍率
     * Defence %: Lightning
     *   Electric shock defense power multiplier
     * Default Value  = 1 */
    float ThunderDefenseRate;

    /* 《闇防御力倍率》
     *   闇防御力倍率
     * Defence %: Holy
     *   Dark defense multiplier
     * Default Value  = 1 */
    float DarkDefenseRate;

    /* 《スタミナ攻撃力倍率》
     *   スタミナ攻撃力倍率
     * Damage %: Stamina
     *   Stamina attack power multiplier
     * Default Value  = 1 */
    float StaminaAttackRate;

    /* 《所持ソウル率》
     *   所持ソウル率
     * Rune Multiplier
     *   Possession soul rate
     * Default Value  = 1 */
    float SoulRate;

    /* 《毒耐性変化倍率》
     *   毒耐性変化倍率
     * Resist %: Poison
     *   Poison resistance change rate
     * Default Value  = 1 */
    float PoisionResistRate;

    /* 《疫病耐性変化倍率》
     *   疫病耐性変化倍率
     * Resist %: Scarlet Rot
     *   Epidemic resistance change rate
     * Default Value  = 1 */
    float DiseaseResistRate;

    /* 《出血耐性変化倍率》
     *   出血耐性変化倍率
     * Resist %: Hemorrhage
     *   Bleeding resistance change rate
     * Default Value  = 1 */
    float BloodResistRate;

    /* 《呪耐性変化倍率》
     *   呪耐性変化倍率
     * Resist %: Blight
     *   Curse resistance change rate
     * Default Value  = 1 */
    float CurseResistRate;

    /* 《冷気耐性変化倍率》
     *   冷気耐性変化倍率
     * Resist %: Frostbite
     *   Cold resistance change rate
     * Default Value  = 1 */
    float FreezeResistRate;

    /* 《出血ダメージ補正倍率》
     *   出血ダメージ補正倍率
     * Damage %: Hemorrhage
     *   Bleeding damage correction factor
     * Default Value  = 1 */
    float BloodDamageRate;

    /* 《SAダメージ補正倍率》
     *   SAダメージ補正倍率
     * Damage %: Poise
     *   SA damage correction factor
     * Default Value  = 1 */
    float SuperArmorDamageRate;

    /* 《冷気ダメージ補正倍率》
     *   冷気ダメージ補正倍率
     * Damage %: Frostbite
     *   Cold damage correction factor
     * Default Value  = 1 */
    float FreezeDamageRate;

    /* 《睡眠耐性変化倍率》
     *   睡眠耐性変化倍率
     * Resist %: Sleep
     *   Sleep tolerance change rate
     * Default Value  = 1 */
    float SleepResistRate;

    /* 《発狂耐性変化倍率》
     *   発狂耐性変化倍率
     * Resist %: Madness
     *   Madness resistance change rate
     * Default Value  = 1 */
    float MadnessResistRate;

    /* 《睡眠ダメージ補正倍率》
     *   睡眠ダメージ補正倍率
     * Damage %: Sleep
     *   Sleep damage correction factor
     * Default Value  = 1 */
    float SleepDamageRate;

    /* 《発狂ダメージ補正倍率》
     *   発狂ダメージ補正倍率
     * Damage %: Madness
     *   Mad damage correction factor
     * Default Value  = 1 */
    float MadnessDamageRate;

    /* pad */
    char pad1[4];
} er_clear_count_correct_param_t;
