#pragma once

typedef struct tutorial_param_s {
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

    /* 表示タイプ
     *   表示するチュートリアルメニューの種類を指定します
     * Menu Type
     *   Specifies the type of tutorial menu to display */
    unsigned char menuType;

    /* 表示タイミング
     *   表示タイミング（デフォルト: 0:"-"）。このメニューを開いたときに、このチュートリアルを表示します。メニューを開いたときに表示しない場合は 0:"-" を指定します
     * Trigger Type
     *   Display timing (default: 0: -). You will see this tutorial when you open this menu. Specify 0: - if you do not want to display it when you open the menu. */
    unsigned char triggerType;

    /* 表示回数
     *   表示する回数（デフォルト: 0:ゲーム中1回）
     * Repeat Type
     *   Number of times a tutorial can be displayed */
    unsigned char repeatType;

    /* パディング */
    char pad1[1];

    /* イメージID
     *   表示するチュートリアル画像IDを指定します（デフォルト: 0）。画像を表示しない場合は、0 を指定します
     * Image ID
     *   Specifies the tutorial image ID to display (default: 0). Specify 0 if you do not want to display the image */
    unsigned short imageId;

    /* パディング */
    char pad2[2];

    /* 表示許可フラグ
     *   表示許可用のイベントフラグID（デフォルト: 0）。このフラグが立つまでは表示されません。常に許可したい場合は 0 を指定します
     * Unlock Event Flag ID
     *   Event flag ID for display permission (default: 0). It will not be displayed until this flag is set. Specify 0 if you always want to allow */
    unsigned int unlockEventFlagId;

    /* テキストID
     *   チュートリアルに表示するテキストのID[TutorialText.xlsm]。「タイトル」も「本文」もこのテキストIDが使われる
     * Text ID
     *   ID of the text to be displayed in the tutorial [TutorialText.xlsm]. This text ID is used for both Title and Body
     * Default Value  = -1 */
    int textId;

    /* 最短
     *   最短表示保障時間[秒]。イベントなどから閉じられたとしても、少なくともこの時間は表示してから閉じられるます。トースト専用なのでモーダルでは無視されます
     * Display Minimum Time
     *   Shortest display guaranteed time [seconds]. Even if it is closed due to an event etc., it will be closed after displaying at least this time. It's only for toast, so it's ignored in modals
     * Default Value  = 1 */
    float displayMinTime;

    /* 最長
     *   表示時間[秒]。トーストが表示されてからこの時間経過すると自動的に閉じられます。トースト専用なのでモーダルでは無視されます
     * Display Time
     *   Display time [seconds]. It will close automatically after this time has passed since the toast was displayed. It's only for toast, so it's ignored in modals
     * Default Value  = 3 */
    float displayTime;

    /* パディング */
    char pad3[4];
} tutorial_param_t;
