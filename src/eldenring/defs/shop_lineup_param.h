#pragma once

/* Defines trades available in shops.
 * Available trades in a given shop are determined by a range defined in ESD and by game flags.
 * Items sold for less than their sell price will not appear in shops.
 * Material costs may not be shown in shop variants. */
typedef struct shop_lineup_param_s {
    /* 装備ID
     *   販売している装備品のID
     * Reference ID
     *   ID of the equipment for sale */
    int equipId;

    /* 価格
     *   上書きする販売価格(-1:上書きしない)
     * Sell Price Overwrite
     *   Selling price to overwrite (-1: Do not overwrite)
     * Default Value  = -1 */
    int value;

    /* 購入に必要な素材ID
     *   購入に必要な素材ID(-1:なし)
     * Required Material ID
     *   Material ID required for purchase (-1: None)
     * Default Value  = -1 */
    int mtrlId;

    /* 個数保持イベントフラグ
     *   個数を保持してあるイベントフラグ値
     * Quantity - Event Flag ID
     *   Event flag value that holds the number */
    unsigned int eventFlag_forStock;

    /* 販売解禁イベントフラグ
     *   販売解禁イベントフラグ
     * Visibility - Event Flag ID
     *   Sales ban event flag */
    unsigned int eventFlag_forRelease;

    /* 販売個数
     *   販売個数
     * Amount to Sell
     *   Number of units sold
     * Default Value  = -1 */
    short sellQuantity;

    /* パディング */
    char pad3[1];

    /* 装備タイプ
     *   販売している装備品の種類
     * Equipment Type
     *   Types of equipment for sale */
    unsigned char equipType;

    /* 価格タイプ
     *   価格の種類。販売価格を上書きするときだけ適用される
     * Currency Type
     *   Price type. Applies only when overwriting the selling price */
    unsigned char costType;

    /* パディング */
    char pad1[1];

    /* 販売セット数
     *   販売セット数。1回の購入で手に入る個数（デフォルト: 1）
     * Amount on Purchase
     *   Number of sets sold. Number of pieces you can get with one purchase (default: 1)
     * Default Value  = 1 */
    unsigned short setNum;

    /* 加算
     *   装備品の販売価格に対する補正（加算）。装備品パラの販売価格×倍率＋加算
     * Price Addition
     *   Correction (addition) to the selling price of equipment. Equipment para selling price x magnification + addition */
    int value_Add;

    /* 倍率
     *   装備品の販売価格に対する補正（倍率）。装備品パラの販売価格×倍率＋加算
     * Price Multiplier
     *   Correction (magnification) to the selling price of equipment. Equipment para selling price x magnification + addition
     * Default Value  = 1 */
    float value_Magnification;

    /* アイコンID
     *   メニュー表示用_アイコンID(-1:上書きしない)
     * Icon ID
     *   Menu icon ID
     * Default Value  = -1 */
    int iconId;

    /* テキストID
     *   メニュー表示用_テキストID(-1:上書きしない)
     * Name - Text ID
     *   Menu display_text ID (-1: do not overwrite)
     * Default Value  = -1 */
    int nameMsgId;

    /* メニュータイトルテキストID
     *   ショップのメニュータイトルのテキストID(-1:上書きしない)。ショップを起動するときに渡されたパラID範囲の中で最初に見つかったパラのこの値が参照されます
     * Menu Title - Text ID
     *   Text ID of the shop menu title (-1: Do not overwrite). This value of the first para found in the para ID range passed when launching the shop is referenced
     * Default Value  = -1 */
    int menuTitleMsgId;

    /* メニューアイコンID
     *   ショップのメニューアイコンID(-1:上書きしない)。ショップを起動するときに渡されたパラID範囲の中で最初に見つかったパラのこの値が参照されます
     * Menu Icon ID
     *   Shop menu icon ID (-1: Do not overwrite). This value of the first para found in the para ID range passed when launching the shop is referenced
     * Default Value  = -1 */
    short menuIconId;

    /* パディング */
    char pad2[2];
} shop_lineup_param_t;
