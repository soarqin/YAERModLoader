#pragma once

typedef struct er_weather_lot_tex_param_s {
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

    /* R
     *   変換前の地図画像のカラー情報（R）。RGB値が一致したピクセルとこのパラメータが紐づく
     * Pre-conversion - Map Color: R
     *   Color information (R) of the map image before conversion. Pixels with matching RGB values are associated with this parameter */
    unsigned char srcR;

    /* G
     *   変換前の地図画像のカラー情報（G）。RGB値が一致したピクセルとこのパラメータが紐づく
     * Pre-conversion - Map Color: G
     *   Color information (G) of the map image before conversion. Pixels with matching RGB values are associated with this parameter */
    unsigned char srcG;

    /* B
     *   変換前の地図画像のカラー情報（B）。RGB値が一致したピクセルとこのパラメータが紐づく
     * Pre-conversion - Map Color: B
     *   Color information (B) of the map image before conversion. Pixels with matching RGB values are associated with this parameter */
    unsigned char srcB;

    /* パッド
     *   パッド。一応「画像色情報（A）」用で空けておく */
    char pad1[1];

    /* 天候抽選ID
     *   天候抽選ID(-1:設定なし(デフォルト値))
     * Weather Lottery ID
     *   Weather lottery ID (-1: No setting (default value))
     * Default Value  = -1 */
    int weatherLogId;

    /* パッド2 */
    char pad2[4];
} er_weather_lot_tex_param_t;
