#pragma once

typedef struct er_menuproperty_spec_s {
    /* 項目名テキストID
     * Caption Text ID */
    int CaptionTextID;

    /* 項目アイコンID
     * Icon ID */
    int IconID;

    /* 必要スキル
     * Required Property ID */
    unsigned int RequiredPropertyID;

    /* 優劣判定
     * Compare Type */
    char CompareType;

    /* パディング */
    char pad2[1];

    /* 書式
     * Format Type */
    unsigned short FormatType;

    /* パディング */
    char pad[16];
} er_menuproperty_spec_t;
