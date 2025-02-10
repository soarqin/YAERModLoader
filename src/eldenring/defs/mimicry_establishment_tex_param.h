#pragma once

typedef struct mimicry_establishment_tex_param_s {
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
     * Pre-conversion - Map Image R
     *   Color information (R) of the map image before conversion. Pixels with matching RGB values are associated with this parameter */
    unsigned char srcR;

    /* G
     *   変換前の地図画像のカラー情報（G）。RGB値が一致したピクセルとこのパラメータが紐づく
     * Pre-conversion - Map Image G
     *   Color information (G) of the map image before conversion. Pixels with matching RGB values are associated with this parameter */
    unsigned char srcG;

    /* B
     *   変換前の地図画像のカラー情報（B）。RGB値が一致したピクセルとこのパラメータが紐づく
     * Pre-conversion - Map Image B
     *   Color information (B) of the map image before conversion. Pixels with matching RGB values are associated with this parameter */
    unsigned char srcB;

    /* パッド
     *   パッド。一応「画像色情報（A）」用で空けておく */
    char pad1[1];

    /* マップ別擬態確率パラメータID
     *   マップ別擬態確率パラメータID(-1:設定なし(デフォルト値))。地域はMapStudioと合わせてある
     * Mimicry Establishment Param ID
     *   Mimicry probability parameter ID by map (-1 No setting (default value)). The area is combined with Map Studio
     * Default Value  = -1 */
    int mimicryEstablishmentParamId;

    /* パッド2 */
    char pad2[4];
} mimicry_establishment_tex_param_t;
