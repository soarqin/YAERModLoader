#pragma once

typedef struct er_world_map_piece_param_s {
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

    /* 開放イベントフラグID
     *   開放条件のイベントフラグID
     * Open - Event Flag ID
     *   Event flag ID of open condition */
    unsigned int openEventFlagId;

    /* 開放される踏破エリア：Xmin
     *   開放時に拡張する踏破エリアの座標（Xmin）
     * Open - Traversal Area - X Min
     *   Coordinates of the traversal area that expands when opened (Xmin) */
    float openTravelAreaLeft;

    /* 開放される踏破エリア：Xmax
     *   開放時に拡張する踏破エリアの座標（Xmax）
     * Open - Traversal Area - X Max
     *   Coordinates of the traversal area that expands when opened (Xmax) */
    float openTravelAreaRight;

    /* 開放される踏破エリア：Ymin
     *   開放時に拡張する踏破エリアの座標（Ymin）
     * Open - Traversal Area - Y Min
     *   Coordinates of the traversal area that expands when opened (Ymin) */
    float openTravelAreaTop;

    /* 開放される踏破エリア：Ymax
     *   開放時に拡張する踏破エリアの座標（Ymax）
     * Open - Traversal Area - Y Max
     *   Coordinates of the traversal area that expands when opened (Ymax) */
    float openTravelAreaBottom;

    /* 入手演出イベントフラグID
     *   入手演出開始条件のイベントフラグID。いずれかの地図断片ひとつのみがOnになっている想定
     * Acquisition - Event Flag ID
     *   Event flag ID of the acquisition production start condition. Assuming that only one of the map fragments is On */
    unsigned int acquisitionEventFlagId;

    /* 入手演出：表示倍率
     *   入手演出時の表示倍率
     * Acquisition - Display Scale
     *   Display magnification at the time of acquisition production
     * Default Value  = 1 */
    float acquisitionEventScale;

    /* 入手演出：中心座標X
     *   入手演出時の中心座標（X）
     * Acquisition - Center X Coordinate
     *   Center coordinates (X) at the time of acquisition production */
    float acquisitionEventCenterX;

    /* 入手演出：中心座標Y
     *   入手演出時の中心座用（Y）
     * Acquisition - Center Y Coordinate
     *   For the central seat at the time of acquisition production (Y) */
    float acquisitionEventCenterY;

    /* 入手演出：リソース倍率
     *   入手演出用目隠しリソースの表示倍率
     * Acquisition - Display Resource Scale
     *   Display magnification of blindfold resources for acquisition production
     * Default Value  = 1 */
    float acquisitionEventResScale;

    /* 入手演出：リソースオフセットX
     *   入手演出用目隠しリソースの表示位置オフセット（X）
     * Acquisition - Resource Offset X
     *   Display position offset (X) of blindfold resource for acquisition production */
    float acquisitionEventResOffsetX;

    /* 入手演出：リソースオフセットY
     *   入手演出用目隠しリソースの表示位置オフセット（Y）
     * Acquisition - Resource Offset Y
     *   Offset of display position of blindfold resource for acquisition production (Y) */
    float acquisitionEventResOffsetY;

    /* パッド */
    char pad[12];
} er_world_map_piece_param_t;
