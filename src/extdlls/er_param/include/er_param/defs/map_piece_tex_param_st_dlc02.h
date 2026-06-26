#pragma once

typedef struct er_map_piece_tex_param_st_dlc02_s {
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

    /* マップ名ID_セーブデータ表示用
     *   セーブデータ表示用のマップ名ID[PlaceName](0:無効値)
     * Save Map Name ID
     *   Map name ID for displaying save data [PlaceName] (0 - invalid value)
     * Default Value  = -1 */
    int saveMapNameId;

    /* マルチプレイエリアID
     *   マルチプレイエリアID(-1:無効値)
     * Multiplayer Area ID
     *   Multiplayer area ID (-1 - invalid value)
     * Default Value  = -1 */
    int multiPlayAreaId;

    int unknown_0x10;

    int unknown_0x14;

    int unknown_0x18;

    int unknown_0x1c;

    /* Multiplayer Area ID [1] */
    int unknownPlayRegion_1;

    /* Multiplayer Area ID [2] */
    int unknownPlayRegion_2;
} er_map_piece_tex_param_st_dlc02_t;
