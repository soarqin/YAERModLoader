#pragma once

typedef struct er_wwise_value_to_str_convert_param_s {
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

    /* Wwiseパラメータ文字列
     *   Wwiseパラメータ文字列
     * Param String
     *   Wwise parameter string */
    char ParamStr[32];
} er_wwise_value_to_str_convert_param_t;
