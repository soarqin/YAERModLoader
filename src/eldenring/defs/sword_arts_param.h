#pragma once

/* Defines Ashes of War, including unique AoW. Determines AoW animation.
 * Behaviour data remains in BehaviourParam. Unique AoW data is with the weapon and not with other AoW data. */
typedef struct sword_arts_param_s {
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

    /* 剣戟ID
     *   ビヘイビアスクリプトに渡してどの剣戟か判定するためのもの
     * Sword Arts Type (Obsolete)
     *   Offset for TAE animation. 0 is a600. To pass to the behavior script to determine which swashbuckler */
    unsigned char swordArtsType;

    /* アーツ速度
     *   どのキャンセルタイミングを見るか。0：通常（左手攻撃）／1：早い／2：遅い
     * Arts Speed Type
     *   Which cancellation timing do you see? 0: Normal (left hand attack) / 1: Early / 2: Slow */
    unsigned char artsSpeedType;

    /* 関連ステータス
     *   どの系統のアーツポイントを参照するか
     * Reference Status Type
     *   Which system of arts points to refer to */
    char refStatus;

    /* 左手（片手持ち）時に右手のアーツを表示するか
     *   左手武器のアーツに設定されている場合、右手武器のアーツをFEに表示します。「武器戦技」などに使われる想定
     * Is Right-hand Arts Reference
     *   When set to the arts of the left-handed weapon, the arts of the right-handed weapon are displayed in FE. Assumed to be used for weapon maneuvers etc. */
    unsigned char isRefRightArts:1;

    /* 左手（片手持ち）時にグレーアウトするか
     *   左手（片手持ち）のアーツ名を表示するときにグレーアウトするか
     * Is Greyout Left-hand
     *   Whether to gray out when displaying the arts name of the left hand (one-handed) */
    unsigned char isGrayoutLeftHand:1;

    /* 右手（片手持ち）時にグレーアウトするか
     *   右手（片手持ち）のアーツ名を表示するときにグレーアウトするか
     * Is Greyout Right-hand
     *   Whether to gray out when displaying the arts name of the right hand (one-handed) */
    unsigned char isGrayoutRightHand:1;

    /* 両手持ち時にグレーアウトするか
     *   両手持ちのアーツ名を表示するときにグレーアウトするか
     * Is Greyout Both-hand
     *   Whether to gray out when displaying the arts name of both hands */
    unsigned char isGrayoutBothHand:1;

    /* 予約領域 */
    char reserve2:4;

    /* 消費ポイント L1
     *   L1によりアーツを出したときに消費するポイント
     * Arts Points - L1
     *   Points to spend when putting out arts by L1 */
    char usePoint_L1;

    /* 消費ポイント L2
     *   L2によりアーツを出したときに消費するポイント
     * Arts Points - L2
     *   Points to spend when putting out arts by L2 */
    char usePoint_L2;

    /* 消費ポイント R1
     *   R1によりアーツを出したときに消費するポイント
     * Arts Points - R1
     *   Points to spend when putting out arts by R1 */
    char usePoint_R1;

    /* 消費ポイント R2
     *   R2によりアーツを出したときに消費するポイント
     * Arts Points - R2
     *   Points to spend when putting out arts by R2 */
    char usePoint_R2;

    /* テキストID
     *   アーツ説明用のテキストID
     * Text ID
     *   Text ID for arts description */
    int textId;

    /* 消費MP L1
     *   L1によりアーツを出したときに消費するMP
     * FP Consumption - L1
     *   MP consumed when issuing arts by L1 */
    short useMagicPoint_L1;

    /* 消費MP L2
     *   L2によりアーツを出したときに消費するMP
     * FP Consumption - L2
     *   MP consumed when issuing arts by L2 */
    short useMagicPoint_L2;

    /* 消費MP R1
     *   R1によりアーツを出したときに消費するMP
     * FP Consumption - R1
     *   MP consumed when issuing arts by R1 */
    short useMagicPoint_R1;

    /* 消費MP R2
     *   R2によりアーツを出したときに消費するMP
     * FP Consumption - R2
     *   MP consumed when issuing arts by R2 */
    short useMagicPoint_R2;

    /* Sword Arts Type
     *   Offset for TAE animation. 0 is a600. To pass to the behavior script to determine which swashbuckler */
    unsigned short swordArtsTypeNew;

    /* アイコンID
     *   FEなどで表示するアイコンのID
     * Icon ID
     *   ID of the icon displayed in FE etc. */
    unsigned short iconId;

    /* AI使用判断ID
     *   AI使用判断ID
     * AI Usage Judgment ID
     *   AI usage judgment ID
     * Default Value  = -1 */
    int aiUsageId;
} sword_arts_param_t;
