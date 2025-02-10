#pragma once

typedef struct network_area_param_s {
    /* セルサイズX
     *   セルサイズX
     * Cell Size - X
     *   Cell size X
     * Default Value  = 30 */
    float cellSizeX;

    /* セルサイズY
     *   セルサイズY
     * Cell Size - Y
     *   Cell size Y
     * Default Value  = 8 */
    float cellSizeY;

    /* セルサイズZ
     *   セルサイズZ
     * Cell Size - Z
     *   Cell size Z
     * Default Value  = 30 */
    float cellSizeZ;

    /* セルオフセットX
     *   セルオフセットX
     * Cell Offset - X
     *   Cell offset X */
    float cellOffsetX;

    /* セルオフセットY
     *   セルオフセットY
     * Cell Offset - Y
     *   Cell offset Y */
    float cellOffsetY;

    /* セルオフセットZ
     *   セルオフセットZ
     * Cell Offset - Z
     *   Cell offset Z */
    float cellOffsetZ;

    /* 血痕・死亡幻影有効
     *   血痕・死亡幻影有効
     * Enable Bloodstain
     *   Effective bloodstain / death illusion */
    unsigned char enableBloodstain:1;

    /* 血文字有効
     *   血文字有効
     * Enable Blood Message
     *   Blood character valid */
    unsigned char enableBloodMessage:1;

    /* 幻影有効
     *   幻影有効
     * Enable Ghost
     *   Phantom effective */
    unsigned char enableGhost:1;

    /* マルチプレイ有効
     *   マルチプレイ有効
     * Enable Multiplayer
     *   Multiplayer enabled */
    unsigned char enableMultiPlay:1;

    /* 指輪検索有効
     *   指輪検索の検索対象か？（鐘守灰霊・救援青霊として呼ばれるエリア）
     * Enable Ring Search
     *   Is it a search target for ring search? (Area called Kanemori Ash Spirit / Relief Blue Spirit) */
    unsigned char enableRingSearch:1;

    /* 乱入検索有効
     *   乱入検索の対象か？
     * Enable Invasion Search
     *   Is it the target of intrusion search? */
    unsigned char enableBreakInSearch:1;

    /* ダミー */
    char dummy[3];
} network_area_param_t;
