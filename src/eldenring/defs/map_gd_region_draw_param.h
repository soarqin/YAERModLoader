#pragma once

typedef struct map_gd_region_draw_param_s {
    /* NT版出力から外すか
     *   ○をつけたパラメータをNT版パッケージでは除外します
     * Disable Param - Network Test
     *   Parameters marked with  are excluded in the NT version package. */
    unsigned char disableParam_NT:1;

    /* パッケージ出力用リザーブ1
     *   パッケージ出力用リザーブ1 */
    char disableParamReserve1:7;

    /* パッケージ出力用リザーブ2
     *   パッケージ出力用リザーブ2 */
    char disableParamReserve2[3];

    /* IV撮影時のローカルライトスケール上書き値
     *   IV撮影時のローカルライトスケール値(0以下：上書きなし) 【GR】SEQ13338 【イラディアンスボリューム】SFX光源のインダイレクトスケールを一律に変更したい
     * Override Irradiance Volume Local Light Scale
     *   Local light scale value at the time of IV shooting (0 or less - no overwrite) [GR] SEQ13338 [Irradiance volume] I want to change the indirect scale of the SFX light source uniformly.
     * Default Value  = -1 */
    float overrideIVLocalLightScale;
} map_gd_region_draw_param_t;
