#pragma once

typedef struct hit_effect_sfx_param_s {
    /* 斬撃：標準
     *   斬撃：標準
     * Slash: Standard
     *   Slash: Standard */
    int Slash_Normal;

    /* 斬撃：小
     *   斬撃：小
     * Slash: Small
     *   Slash: Small */
    int Slash_S;

    /* 斬撃：大
     *   斬撃：大
     * Slash: Large
     *   Slash: Large */
    int Slash_L;

    /* 斬撃：指定1
     *   斬撃：指定1
     * Slash: Specific 1
     *   Slash: Specific 1 */
    int Slash_Specific1;

    /* 斬撃：指定2
     *   斬撃：指定2
     * Slash: Specific 2
     *   Slash: Specific 2 */
    int Slash_Specific2;

    /* 打撃：標準
     *   打撃：標準
     * Batter: Standard
     *   Batter: Standard */
    int Blow_Normal;

    /* 打撃：小
     *   打撃：小
     * Batter: Small
     *   Batter: Small */
    int Blow_S;

    /* 打撃：大
     *   打撃：大
     * Batter: Large
     *   Batter: Large */
    int Blow_L;

    /* 打撃：指定1
     *   打撃：指定1
     * Batter: Specific 1
     *   Batter: Specific 1 */
    int Blow_Specific1;

    /* 打撃：指定2
     *   打撃：指定2
     * Batter: Specific 2
     *   Batter: Specific 2 */
    int Blow_Specific2;

    /* 刺突：標準
     *   刺突：標準
     * Piercing: Standard
     *   Piercing: Standard */
    int Thrust_Normal;

    /* 刺突：小
     *   刺突：小
     * Piercing: Small
     *   Piercing: Small */
    int Thrust_S;

    /* 刺突：大
     *   刺突：大
     * Piercing: Large
     *   Piercing: Large */
    int Thrust_L;

    /* 刺突：指定1
     *   刺突：指定1
     * Piercing: Specific 1
     *   Piercing: Specific 1 */
    int Thrust_Specific1;

    /* 刺突：指定2
     *   刺突：指定2
     * Piercing: Specific 2
     *   Piercing: Specific 2 */
    int Thrust_Specific2;

    /* 無属性：標準
     *   無属性：標準
     * Neutral: Standard
     *   Neutral: standard */
    int Neutral_Normal;

    /* 無属性：小
     *   無属性：小
     * Neutral: Small
     *   Neutral: Small */
    int Neutral_S;

    /* 無属性：大
     *   無属性：大
     * Neutral: Large
     *   Neutral: Large */
    int Neutral_L;

    /* 無属性：指定1
     *   無属性：指定1
     * Neutral: Specific 1
     *   Neutral: Specific 1 */
    int Neutral_Specific1;

    /* 無属性：指定2
     *   無属性：指定2
     * Neutral: Specific 2
     *   Neutral: Specific 2 */
    int Neutral_Specific2;
} hit_effect_sfx_param_t;
