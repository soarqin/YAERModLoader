#pragma once

typedef struct gparam_ref_settings_param_s {
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

    /* 参照先マップID 
     *   参照先のマップ番号を指定します。レガシー：m10_10_00_00 -> 10010000, オープン：m60_??_??_?? -> m60000000
     * Reference Target Map ID
     *   Specify the referenced map number. Legacy m10_10_00_00-> 10010000, Open m60_ ?? _ ?? _ ??-> m60000000
     * Default Value  = -1 */
    int RefTargetMapId;

    /* リザーブ
     *   リザーブ */
    char Reserve[24];
} gparam_ref_settings_param_t;
