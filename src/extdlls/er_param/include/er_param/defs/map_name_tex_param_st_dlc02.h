#pragma once

typedef struct er_map_name_tex_param_st_dlc02_s {
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
     * Pre-conversion - Map Image - R
     *   Color information (R) of the map image before conversion. Pixels with matching RGB values are associated with this parameter */
    unsigned char srcR;

    /* G
     *   変換前の地図画像のカラー情報（G）。RGB値が一致したピクセルとこのパラメータが紐づく
     * Pre-conversion - Map Image - G
     *   Color information (G) of the map image before conversion. Pixels with matching RGB values are associated with this parameter */
    unsigned char srcG;

    /* B
     *   変換前の地図画像のカラー情報（B）。RGB値が一致したピクセルとこのパラメータが紐づく
     * Pre-conversion - Map Image - B
     *   Color information (B) of the map image before conversion. Pixels with matching RGB values are associated with this parameter */
    unsigned char srcB;

    /* パッド
     *   パッド。一応「画像色情報（A）」用で空けておく */
    char pad1[1];

    /* マップ名ID_地名表示用
     *   地名表示用のマップ名ID[PlaceName](0:無効値)
     * Map Name ID
     *   Map name ID for displaying place names [PlaceName] (0 - invalid value) */
    int mapNameId;

    int unknown_0xc;

    unsigned char unknown_0x10;

    unsigned char unknown_0x11;

    unsigned char unknown_0x12;

    unsigned char unknown_0x13;

    int unknown_0x14;

    /* Location Text ID [1] */
    int unknownTextID_1;

    /* Location Text ID [2] */
    int unknownTextID_2;

    int unknown_0x20;

    int unknown_0x24;
} er_map_name_tex_param_st_dlc02_t;
