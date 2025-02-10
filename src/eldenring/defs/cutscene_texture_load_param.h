#pragma once

typedef struct cutscene_texture_load_param_s {
    /* NT版出力から外すか
     *   ○をつけたパラメータをNT版パッケージでは除外します
     * Disable Param - Network Test
     *   Parameters marked with  are excluded in the NT version package. */
    unsigned char disableParam_NT:1;

    /* デバッグパラメータか
     *   ○をつけたパラメータは全パッケージから除外します（デバッグ用なので）
     * Disable Param - Debug
     *   Parameters marked with a circle are excluded from all packages (because they are for debugging). */
    unsigned char disableParam_Debug:1;

    /* パッケージ出力用リザーブ1
     *   パッケージ出力用リザーブ1 */
    char disableParamReserve1:6;

    /* パッケージ出力用リザーブ2
     *   パッケージ出力用リザーブ2 */
    char disableParamReserve2[3];

    /* テクスチャ名 00
     *   テクスチャ名 00
     * Texture DisplayName [00]
     *   Texture DisplayName [00] */
    char texName_00[16];

    /* テクスチャ名 01
     *   テクスチャ名 01
     * Texture DisplayName [01]
     *   Texture DisplayName [01] */
    char texName_01[16];

    /* テクスチャ名 02
     *   テクスチャ名 02
     * Texture DisplayName [02]
     *   Texture DisplayName [02] */
    char texName_02[16];

    /* テクスチャ名 03
     *   テクスチャ名 03
     * Texture DisplayName [03]
     *   Texture DisplayName [03] */
    char texName_03[16];

    /* テクスチャ名 04
     *   テクスチャ名 04
     * Texture DisplayName [04]
     *   Texture DisplayName [04] */
    char texName_04[16];

    /* テクスチャ名 05
     *   テクスチャ名 05
     * Texture DisplayName [05]
     *   Texture DisplayName [05] */
    char texName_05[16];

    /* テクスチャ名 06
     *   テクスチャ名 06
     * Texture DisplayName [06]
     *   Texture DisplayName [06] */
    char texName_06[16];

    /* テクスチャ名 07
     *   テクスチャ名 07
     * Texture DisplayName [07]
     *   Texture DisplayName [07] */
    char texName_07[16];

    /* テクスチャ名 08
     *   テクスチャ名 08
     * Texture DisplayName [08]
     *   Texture DisplayName [08] */
    char texName_08[16];

    /* テクスチャ名 09
     *   テクスチャ名 09
     * Texture DisplayName [09]
     *   Texture DisplayName [09] */
    char texName_09[16];

    /* テクスチャ名 10
     *   テクスチャ名 10
     * Texture DisplayName [10]
     *   Texture DisplayName [10] */
    char texName_10[16];

    /* テクスチャ名 11
     *   テクスチャ名 11
     * Texture DisplayName [11]
     *   Texture DisplayName [11] */
    char texName_11[16];

    /* テクスチャ名 12
     *   テクスチャ名 12
     * Texture DisplayName [12]
     *   Texture DisplayName [12] */
    char texName_12[16];

    /* テクスチャ名 13
     *   テクスチャ名 13
     * Texture DisplayName [13]
     *   Texture DisplayName [13] */
    char texName_13[16];

    /* テクスチャ名 14
     *   テクスチャ名 14
     * Texture DisplayName [14]
     *   Texture DisplayName [14] */
    char texName_14[16];

    /* テクスチャ名 15
     *   テクスチャ名 15
     * Texture DisplayName [15]
     *   Texture DisplayName [15] */
    char texName_15[16];
} cutscene_texture_load_param_t;
