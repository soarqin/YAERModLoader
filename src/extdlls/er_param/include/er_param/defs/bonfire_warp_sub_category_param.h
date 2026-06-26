#pragma once

typedef struct er_bonfire_warp_sub_category_param_s {
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

    /* テキストID
     *   サブカテゴリの表示名テキストID[MenuText]
     * Text ID
     *   Subcategory display name Text ID [MenuText] */
    int textId;

    /* 篝火ワープタブID
     *   篝火ワープタブID。このサブカテゴリが所属するタブのID
     * Tab ID
     *   Kagaribi Warp Tab ID. ID of the tab to which this subcategory belongs */
    unsigned short tabId;

    /* 篝火ワープタブソートID
     *   篝火ワープタブソートID。タブの中サブカテゴリの表示順
     * Tab Sort ID
     *   Bonfire Warp Tab Sort ID. Display order of subcategories in tabs */
    unsigned short sortId;

    char pad[4];
} er_bonfire_warp_sub_category_param_t;
