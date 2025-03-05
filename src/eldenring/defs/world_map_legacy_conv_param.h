#pragma once

typedef struct er_world_map_legacy_conv_param_s {
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

    /* 変換元マップID：エリア番号
     *   変換元マップID：エリア番号
     * Source Map Area
     *   Conversion source map ID: Area number */
    unsigned char srcAreaNo;

    /* 変換元マップID：グリッドX
     *   変換元マップID：グリッドX
     * Source Map Block
     *   Source map ID: Grid X */
    unsigned char srcGridXNo;

    /* 変換元マップID：グリッドZ
     *   変換元マップID：グリッドZ
     * Source Map Region
     *   Source map ID: Grid Z */
    unsigned char srcGridZNo;

    /* パディング１
     *   パディング１ */
    char pad1[1];

    /* 変換元マップ基準座標X
     *   変換元マップ基準座標X
     * Source Map Coordinate: X
     *   Source map reference coordinates X */
    float srcPosX;

    /* 変換元マップ基準座標Y
     *   変換元マップ基準座標Y
     * Source Map Coordinate: Y
     *   Source map reference coordinates Y */
    float srcPosY;

    /* 変換元マップ基準座標Z
     *   変換元マップ基準座標Z
     * Source Map Coordinate: Z
     *   Source map reference coordinates Z */
    float srcPosZ;

    /* 変換先マップID：エリア番号
     *   変換先マップID：エリア番号
     * Destination Map Area
     *   Conversion destination map ID: Area number */
    unsigned char dstAreaNo;

    /* 変換先マップID：グリッドX
     *   変換先マップID：グリッドX
     * Destination Map Block
     *   Destination map ID: Grid X */
    unsigned char dstGridXNo;

    /* 変換先マップID：グリッドZ
     *   変換先マップID：グリッドZ
     * Destination Map Region
     *   Destination map ID: Grid Z */
    unsigned char dstGridZNo;

    /* パディング２
     *   パディング２ */
    char pad2[1];

    /* 変換先マップ基準座標X
     *   変換先マップ基準座標X
     * Destination Map Coordinate: X
     *   Destination map reference coordinates X */
    float dstPosX;

    /* 変換先マップ基準座標Y
     *   変換先マップ基準座標Y
     * Destination Map Coordinate: Y
     *   Destination map reference coordinates Y */
    float dstPosY;

    /* 変換先マップ基準座標Z
     *   変換先マップ基準座標Z
     * Destination Map Coordinate: Z
     *   Destination map reference coordinates Z */
    float dstPosZ;

    /* 基準となる接続点か
     *   基準となる接続点か。１つの変換元マップIDには必ず一つは基準となる接続点が設定される
     * Is Reference Connection Point
     *   Is it a reference connection point? One reference connection point is always set for one conversion source map ID. */
    unsigned char isBasePoint:1;

    /* パディング３
     *   パディング３ */
    char pad3:7;

    /* パディング４
     *   パディング４ */
    char pad4[11];
} er_world_map_legacy_conv_param_t;
