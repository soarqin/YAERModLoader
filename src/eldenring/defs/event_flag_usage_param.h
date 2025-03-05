#pragma once

typedef struct er_event_flag_usage_param_s {
    /* 用途
     *   フラグの用途。
     * Use
     *   Use of the flag. */
    unsigned char usageType;

    /* プレイログカテゴリ
     *   用途が「ON/OFF」の場合のみ有効。これを設定するとフラグがONになったときにプレイログを収集する。
     * Playlog category
     *   Valid only when the usage is ON / OFF. If this is set, the play log will be collected when the flag is turned ON. */
    unsigned char playlogCategory;

    /* パディング
     *   パディング */
    char padding1[2];

    /* 確保フラグ数
     *   「ON/OFF」の場合は1を設定する。「枠割り当て」「整数」の場合は「パラメータ番号～パラメータ番号+確保フラグ数-1」が確保される範囲になる。
     * Number of secured flags
     *   Set to 1 for ON / OFF. In the case of frame allocation and integer, parameter number-parameter number + number of secured flags-1 is secured.
     * Default Value  = 1 */
    int flagNum;

    /* パディング
     *   パディング */
    char padding2[24];
} er_event_flag_usage_param_t;
