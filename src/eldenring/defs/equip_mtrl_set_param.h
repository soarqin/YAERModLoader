#pragma once

/* Defines costs associated with trades or upgrades. ID incrementation is used in places. */
typedef struct er_equip_mtrl_set_param_s {
    /* 必要素材アイテムID01
     *   武具強化に必要な素材アイテムIDです。
     * Material ID [1]
     *   Material item ID required to strengthen armor.
     * Default Value  = -1 */
    int materialId01;

    /* 必要素材アイテムID02
     *   武具強化に必要な素材アイテムIDです。
     * Material ID [2]
     *   Material item ID required to strengthen armor.
     * Default Value  = -1 */
    int materialId02;

    /* 必要素材アイテムID03
     *   武具強化に必要な素材アイテムIDです。
     * Material ID [3]
     *   Material item ID required to strengthen armor.
     * Default Value  = -1 */
    int materialId03;

    /* 必要素材アイテムID04
     *   武具強化に必要な素材アイテムIDです。
     * Material ID [4]
     *   Material item ID required to strengthen armor.
     * Default Value  = -1 */
    int materialId04;

    /* 必要素材アイテムID05
     *   武具強化に必要な素材アイテムIDです。
     * Material ID [5]
     *   Material item ID required to strengthen armor.
     * Default Value  = -1 */
    int materialId05;

    /* 必要素材アイテムID06
     *   武具強化に必要な素材アイテムIDです。
     * Material ID [6]
     *   Material item ID required to strengthen armor.
     * Default Value  = -1 */
    int materialId06;

    /* パディング
     *   パディング。素材アイテムIDが増えたとき用 */
    char pad_id[8];

    /* 必要個数01
     *   武具強化に必要な素材アイテムの個数です。
     * Material Amount [1]
     *   The number of material items required to strengthen armor.
     * Default Value  = -1 */
    char itemNum01;

    /* 必要個数02
     *   武具強化に必要な素材アイテムの個数です。
     * Material Amount [2]
     *   The number of material items required to strengthen armor.
     * Default Value  = -1 */
    char itemNum02;

    /* 必要個数03
     *   武具強化に必要な素材アイテムの個数です。
     * Material Amount [3]
     *   The number of material items required to strengthen armor.
     * Default Value  = -1 */
    char itemNum03;

    /* 必要個数04
     *   武具強化に必要な素材アイテムの個数です。
     * Material Amount [4]
     *   The number of material items required to strengthen armor.
     * Default Value  = -1 */
    char itemNum04;

    /* 必要個数05
     *   武具強化に必要な素材アイテムの個数です。
     * Material Amount [5]
     *   The number of material items required to strengthen armor.
     * Default Value  = -1 */
    char itemNum05;

    /* 必要個数06
     *   武具強化に必要な素材アイテムの個数です。
     * Material Amount [6]
     *   The number of material items required to strengthen armor.
     * Default Value  = -1 */
    char itemNum06;

    /* パディング
     *   パディング。アイテムの個数が増えたとき用 */
    char pad_num[2];

    /* 必要素材アイテムカテゴリ01
     *   武具強化に必要な素材アイテムのカテゴリです。
     * Material Category [1]
     *   This is a category of material items required for strengthening armor.
     * Default Value  = 4 */
    unsigned char materialCate01;

    /* 必要素材アイテムカテゴリ02
     *   武具強化に必要な素材アイテムのカテゴリです。
     * Material Category [2]
     *   This is a category of material items required for strengthening armor.
     * Default Value  = 4 */
    unsigned char materialCate02;

    /* 必要素材アイテムカテゴリ03
     *   武具強化に必要な素材アイテムのカテゴリです。
     * Material Category [3]
     *   This is a category of material items required for strengthening armor.
     * Default Value  = 4 */
    unsigned char materialCate03;

    /* 必要素材アイテムカテゴリ04
     *   武具強化に必要な素材アイテムのカテゴリです。
     * Material Category [4]
     *   This is a category of material items required for strengthening armor.
     * Default Value  = 4 */
    unsigned char materialCate04;

    /* 必要素材アイテムカテゴリ05
     *   武具強化に必要な素材アイテムのカテゴリです。
     * Material Category [5]
     *   This is a category of material items required for strengthening armor.
     * Default Value  = 4 */
    unsigned char materialCate05;

    /* 必要素材アイテムカテゴリ06
     *   武具強化に必要な素材アイテムのカテゴリです。
     * Material Category [6]
     *   This is a category of material items required for strengthening armor.
     * Default Value  = 4 */
    unsigned char materialCate06;

    /* パディング
     *   パディング。カテゴリが増えたとき用 */
    char pad_cate[2];

    /* 個数表示を無効化01
     *   個数表示を無効化するか(強化ショップ用)
     * Disable Display Number [1]
     *   Disable the number display (for enhanced shops) */
    unsigned char isDisableDispNum01:1;

    /* 個数表示を無効化02
     *   個数表示を無効化するか
     * Disable Display Number [2]
     *   Whether to disable the number display */
    unsigned char isDisableDispNum02:1;

    /* 個数表示を無効化03
     *   個数表示を無効化するか
     * Disable Display Number [3]
     *   Whether to disable the number display */
    unsigned char isDisableDispNum03:1;

    /* 個数表示を無効化04
     *   個数表示を無効化するか
     * Disable Display Number [4]
     *   Whether to disable the number display */
    unsigned char isDisableDispNum04:1;

    /* 個数表示を無効化05
     *   個数表示を無効化するか
     * Disable Display Number [5]
     *   Whether to disable the number display */
    unsigned char isDisableDispNum05:1;

    /* 個数表示を無効化06
     *   個数表示を無効化するか
     * Disable Display Number [6]
     *   Whether to disable the number display */
    unsigned char isDisableDispNum06:1;

    /* パディング
     *   パディングです。 */
    char pad[3];
} er_equip_mtrl_set_param_t;
