#pragma once

typedef struct er_chr_activate_condition_param_s {
    /* 出現条件_晴れ
     *   天候が「晴れ」のときに出現するか
     * Appear during Weather: Sunny
     *   Will it appear when the weather is sunny?
     * Default Value  = 1 */
    unsigned char weatherSunny:1;

    /* 出現条件_快晴
     *   天候が「快晴」のときに出現するか
     * Appear during Weather: Clear Sky
     *   Will it appear when the weather is clear?
     * Default Value  = 1 */
    unsigned char weatherClearSky:1;

    /* 出現条件_薄曇り
     *   天候が「薄曇り」のときに出現するか
     * Appear during Weather: Light Cloud
     *   Will it appear when the weather is lightly cloudy?
     * Default Value  = 1 */
    unsigned char weatherWeakCloudy:1;

    /* 出現条件_曇り
     *   天候が「曇り」のときに出現するか
     * Appear during Weather: Cloud
     *   Will it appear when the weather is cloudy?
     * Default Value  = 1 */
    unsigned char weatherCloudy:1;

    /* 出現条件_雨
     *   天候が「雨」のときに出現するか
     * Appear during Weather: Rain
     *   Will it appear when the weather is rainy?
     * Default Value  = 1 */
    unsigned char weatherRain:1;

    /* 出現条件_豪雨
     *   天候が「豪雨」のときに出現するか
     * Appear during Weather: Heavy Rain
     *   Will it appear when the weather is heavy rain?
     * Default Value  = 1 */
    unsigned char weatherHeavyRain:1;

    /* 出現条件_嵐
     *   天候が「嵐」のときに出現するか
     * Appear during Weather: Storm
     *   Will it appear when the weather is stormy?
     * Default Value  = 1 */
    unsigned char weatherStorm:1;

    /* 出現条件_嵐（守護者の末裔との戦闘用）
     *   天候が「嵐（守護者の末裔との戦闘用）」のときに出現するか
     * Appear during Weather: Storm for Battle
     *   Will it appear when the weather is storm (for combat with the descendants of the guardian)?
     * Default Value  = 1 */
    unsigned char weatherStormForBattle:1;

    /* 出現条件_雪
     *   天候が「雪」のときに出現するか
     * Appear during Weather: Snow
     *   Will it appear when the weather is snow?
     * Default Value  = 1 */
    unsigned char weatherSnow:1;

    /* 出現条件_大雪
     *   天候が「大雪」のときに出現するか
     * Appear during Weather: Heavy Snow
     *   Will it appear when the weather is heavy snow?
     * Default Value  = 1 */
    unsigned char weatherHeavySnow:1;

    /* 出現条件_霧
     *   天候が「霧」のときに出現するか
     * Appear during Weather: Fog
     *   Will it appear when the weather is fog?
     * Default Value  = 1 */
    unsigned char weatherFog:1;

    /* 出現条件_濃霧
     *   天候が「濃霧」のときに出現するか
     * Appear during Weather: Heavy Fog
     *   Will it appear when the weather is dense fog?
     * Default Value  = 1 */
    unsigned char weatherHeavyFog:1;

    /* 出現条件_濃霧（雨）
     *   天候が「濃霧（雨）」のときに出現するか
     * Appear during Weather: Heavy Fog and Rain
     *   Does it appear when the weather is dense fog (rain)?
     * Default Value  = 1 */
    unsigned char weatherHeavyFogRain:1;

    /* 出現条件_砂嵐
     *   天候が「砂嵐」のときに出現するか
     * Appear during Weather: Sandstorm
     *   Will it appear when the weather is a sandstorm?
     * Default Value  = 1 */
    unsigned char weatherSandStorm:1;

    /* pad */
    char pad1:2;

    /* 出現開始インゲーム時間_時
     *   出現開始インゲーム時間_時
     * Time: Start Hour
     *   Appearance start in game time_hour */
    unsigned char timeStartHour;

    /* 出現開始インゲーム時間_分
     *   出現開始インゲーム時間_分
     * Time: Start Minute
     *   Appearance start in-game time_minutes */
    unsigned char timeStartMin;

    /* 出現終了インゲーム時間_時
     *   出現終了インゲーム時間_時
     * Time: End Hour
     *   Appearance end in game time_hour */
    unsigned char timeEndHour;

    /* 出現終了インゲーム時間_分
     *   出現終了インゲーム時間_分
     * Time: End Minute
     *   End of appearance In-game time_minutes */
    unsigned char timeEndMin;

    /* pad */
    char pad2[2];
} er_chr_activate_condition_param_t;
