#pragma once

typedef struct er_charmakemenu_listitem_param_s {
    /* 値
     *   プログラム側に扱う値。1つのグループ内で通し番号にする
     * Value
     *   The value handled by the program. Make serial numbers within one group */
    int value;

    /* 項目テキストID
     *   表示するテキストのID
     * Caption ID
     *   ID of the text to be displayed */
    int captionId;

    /* アイコンID
     *   表示するアイコンのID
     * Icon ID
     *   ID of the icon to be displayed */
    unsigned char iconId;

    /* 予約 */
    char reserved[7];
} er_charmakemenu_listitem_param_t;
