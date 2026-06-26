#pragma once

typedef struct er_world_map_place_name_param_s {
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

    /* 地図断片パラメータID
     *   地図断片パラメータID。この地図断片を持っていればテキストを表示する
     * World Map Piece ID
     *   Map fragment parameter ID. Display text if you have this map fragment
     * Default Value  = -1 */
    int worldMapPieceId;

    /* テキストID
     *   表示するテキストID。PlaceName.xlsm
     * Place Name - Text ID
     *   The text ID to display. PlaceName.xlsm
     * Default Value  = -1 */
    int textId;

    /* パディング */
    char pad1[4];

    /* エリア番号
     *   mAA_BB_CC_DD の AA 部分
     * Map Area
     *   AA part of mAA_BB_CC_DD */
    unsigned char areaNo;

    /* グリッドX番号
     *   mAA_BB_CC_DD の BB 部分
     * Map Block
     *   BB part of mAA_BB_CC_DD */
    unsigned char gridXNo;

    /* グリッドZ番号
     *   mAA_BB_CC_DD の CC 部分
     * Map Region
     *   CC part of mAA_BB_CC_DD */
    unsigned char gridZNo;

    /* パディング
     *   パディング */
    char pad2[1];

    /* X座標
     *   X座標
     * Map Coodinate: X
     *   X coordinate */
    float posX;

    /* Y座標
     *   Y座標（使っていない）
     * Map Coodinate: Y
     *   Y coordinate (not used) */
    float posY;

    /* Z座標
     *   Z座標
     * Map Coodinate: Z
     *   Z coordinate */
    float posZ;
} er_world_map_place_name_param_t;
