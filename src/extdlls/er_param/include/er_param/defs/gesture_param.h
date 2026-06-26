#pragma once

typedef struct er_gesture_param_s {
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

    /* 参照アイテムID
     *   参照アイテムID。各メニューでのジェスチャのテキストID、アイコンID、ソートIDを持ってくるのに使用される。装備品パラメータの道具IDを登録します
     * Item ID
     *   Reference item ID. Used to bring in the gesture text ID, icon ID, and sort ID for each menu. Register the tool ID of the equipment parameter */
    int itemId;

    /* メッセージ添付用アニメID
     *   メッセージ添付用アニメID。メッセージ添付時のアニメIDを指定します
     * Message Anim ID
     *   Anime ID for attaching messages. Specify the animation ID when attaching a message */
    int msgAnimId;

    /* 騎乗中使用禁止か
     *   騎乗中使用禁止か(デフォルト:×)。○なら騎乗中に使用できない
     * Cannot Use while Riding
     *   Is it prohibited to use while riding (default )? If , it cannot be used while riding */
    unsigned char cannotUseRiding:1;

    /* 予約領域 */
    char pad2:7;

    /* 予約領域 */
    char pad1[3];
} er_gesture_param_t;
