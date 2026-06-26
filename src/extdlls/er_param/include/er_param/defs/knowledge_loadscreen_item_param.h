#pragma once

typedef struct er_knowledge_loadscreen_item_param_s {
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

    /* 解禁フラグ
     *   解禁フラグ(default: 0)。このイベントフラグが立っていれば解禁される（ローディング画面に表示される）。0なら常に解禁されている。無効フラグの方が優先される
     * Unlock Flag ID
     *   Lifting flag (default 0). If this event flag is set, the ban will be lifted (displayed on the loading screen). If it is 0, the ban is always lifted. The invalid flag has priority */
    unsigned int unlockFlagId;

    /* 無効フラグ
     *   無効フラグ(default: 0)。このイベントフラグが立っていると無効化（ローディング画面に表示されなくなる）。0なら常にこのフラグは立っていないものとする
     * Invalid Flag ID
     *   Invalid flag (default 0). If this event flag is set, it will be disabled (it will not be displayed on the loading screen). If it is 0, this flag is not always set. */
    unsigned int invalidFlagId;

    /* テキストID
     *   テキストID(Loading Text.xlsx)。ローディングタイトルとローディングテキスト両方に使われる
     * Message ID
     *   Text ID (Loading Text.xlsx). Used for both loading titles and loading text */
    int msgId;
} er_knowledge_loadscreen_item_param_t;
