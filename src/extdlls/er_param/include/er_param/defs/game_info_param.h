#pragma once

typedef struct er_game_info_param_s {
    /* タイトルのMsgID
     *   タイトル名
     * Title Message ID
     *   Title name */
    int titleMsgId;

    /* 内容のMsgID
     *   内容
     * Content Messae ID
     *   Contents */
    int contentMsgId;

    /* 価格
     *   価格
     * Price
     *   price */
    int value;

    /* ソートID
     *   ソートID
     * Sort ID
     *   Sort ID */
    int sortId;

    /* アクションID
     *   販売状況を判断するアクションIDです。
     * Action ID
     *   This is the action ID that determines the sales status. */
    int eventId;

    /* パディング
     *   パディング */
    char Pad[12];
} er_game_info_param_t;
