#pragma once

typedef struct map_gd_region_id_param_s {
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

    /* マップ地方ID 
     *   GD用途のマップ地方識別ID[00-99：オープン、1000-9999：レガシー]
     * Map Region ID
     *   Map for GD use Local identification ID [00-99 - Open, 1000-9999 - Legacy] */
    unsigned int mapRegionId;

    /* リザーブ
     *   リザーブ */
    char Reserve[24];
} map_gd_region_id_param_t;
