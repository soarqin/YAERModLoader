#pragma once

typedef struct menu_value_table_spec_s {
    /* 比較する値
     *   比較する値
     * Value
     *   Value to compare */
    int value;

    /* 変換後のテキストID
     *   変換後のテキストID
     * Text ID
     *   Converted text ID */
    int textId;

    /* 比較タイプ
     *   比較タイプ
     * Compare Type
     *   Comparison type */
    char compareType;

    /* パディング
     *   パディング */
    char padding[3];
} menu_value_table_spec_t;
