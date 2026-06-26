#pragma once

typedef struct er_performance_check_param_s {
    /* 報告先_職種タグ
     *   報告先_職種タグ
     * Report destination_Job type tag
     *   Report destination_Job type tag */
    unsigned char workTag;

    /* 報告先_カテゴリタグ
     *   報告先_カテゴリタグ
     * Report destination_category tag
     *   Report destination_category tag */
    unsigned char categoryTag;

    /* 比較記号
     *   比較記号
     * Comparison symbol
     *   Comparison symbol */
    unsigned char compareType;

    /* 予約1
     *   予約1 */
    char dummy1[1];

    /* 比較数値
     *   比較数値
     * Comparison value
     *   Comparison value */
    float compareValue;

    /* 予約2
     *   予約2 */
    char dummy2[8];

    /* 報告先_userタグ
     *   報告先_パフォーマンス人物タグ
     * Report destination_user tag
     *   Report to_Performance person tag */
    wchar_t userTag[16];
} er_performance_check_param_t;
