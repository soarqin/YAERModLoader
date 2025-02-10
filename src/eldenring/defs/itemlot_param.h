#pragma once

/* Defines item lots that can be rolled upon item pickup, enemy death or granted via script.
 * When doing this, consecutive IDs are also rolled.
 * A single result is produced by each row.
 * A row will not be rolled if the flag is already set. */
typedef struct itemlot_param_s {
    /* １：アイテムID
     *   取得できるアイテムのID
     * 1 - Item ID
     *   Item ID that can be obtained */
    int lotItemId01;

    /* ２：アイテムID
     *   取得できるアイテムのID
     * 2 - Item ID
     *   Item ID that can be obtained */
    int lotItemId02;

    /* ３：アイテムID
     *   取得できるアイテムのID
     * 3 - Item ID
     *   Item ID that can be obtained */
    int lotItemId03;

    /* ４：アイテムID
     *   取得できるアイテムのID
     * 4 - Item ID
     *   Item ID that can be obtained */
    int lotItemId04;

    /* ５：アイテムID
     *   取得できるアイテムのID
     * 5 - Item ID
     *   Item ID that can be obtained */
    int lotItemId05;

    /* ６：アイテムID
     *   取得できるアイテムのID
     * 6 - Item ID
     *   Item ID that can be obtained */
    int lotItemId06;

    /* ７：アイテムID
     *   取得できるアイテムのID
     * 7 - Item ID
     *   Item ID that can be obtained */
    int lotItemId07;

    /* ８：アイテムID
     *   取得できるアイテムのID
     * 8 - Item ID
     *   Item ID that can be obtained */
    int lotItemId08;

    /* １：アイテムカテゴリ
     *   取得できるアイテムのカテゴリ
     * 1 - Item Category
     *   Category of items that can be obtained */
    int lotItemCategory01;

    /* ２：アイテムカテゴリ
     *   取得できるアイテムのカテゴリ
     * 2 - Item Category
     *   Category of items that can be obtained */
    int lotItemCategory02;

    /* ３：アイテムカテゴリ
     *   取得できるアイテムのカテゴリ
     * 3 - Item Category
     *   Category of items that can be obtained */
    int lotItemCategory03;

    /* ４：アイテムカテゴリ
     *   取得できるアイテムのカテゴリ
     * 4 - Item Category
     *   Category of items that can be obtained */
    int lotItemCategory04;

    /* ５：アイテムカテゴリ
     *   取得できるアイテムのカテゴリ
     * 5 - Item Category
     *   Category of items that can be obtained */
    int lotItemCategory05;

    /* ６：アイテムカテゴリ
     *   取得できるアイテムのカテゴリ
     * 6 - Item Category
     *   Category of items that can be obtained */
    int lotItemCategory06;

    /* ７：アイテムカテゴリ
     *   取得できるアイテムのカテゴリ
     * 7 - Item Category
     *   Category of items that can be obtained */
    int lotItemCategory07;

    /* ８：アイテムカテゴリ
     *   取得できるアイテムのカテゴリ
     * 8 - Item Category
     *   Category of items that can be obtained */
    int lotItemCategory08;

    /* 基本出現ポイント
     *   通常時の出現ポイント
     * 1 - Item Chance
     *   Appearance point at normal time */
    unsigned short lotItemBasePoint01;

    /* 基本出現ポイント
     *   通常時の出現ポイント
     * 2 - Item Chance
     *   Appearance point at normal time */
    unsigned short lotItemBasePoint02;

    /* 基本出現ポイント
     *   通常時の出現ポイント
     * 3 - Item Chance
     *   Appearance point at normal time */
    unsigned short lotItemBasePoint03;

    /* 基本出現ポイント
     *   通常時の出現ポイント
     * 4 - Item Chance
     *   Appearance point at normal time */
    unsigned short lotItemBasePoint04;

    /* 基本出現ポイント
     *   通常時の出現ポイント
     * 5 - Item Chance
     *   Appearance point at normal time */
    unsigned short lotItemBasePoint05;

    /* 基本出現ポイント
     *   通常時の出現ポイント
     * 6 - Item Chance
     *   Appearance point at normal time */
    unsigned short lotItemBasePoint06;

    /* 基本出現ポイント
     *   通常時の出現ポイント
     * 7 - Item Chance
     *   Appearance point at normal time */
    unsigned short lotItemBasePoint07;

    /* 基本出現ポイント
     *   通常時の出現ポイント
     * 8 - Item Chance
     *   Appearance point at normal time */
    unsigned short lotItemBasePoint08;

    /* 累積後出現ポイント
     *   最大累積時の出現ポイント
     * 1 - Item Accumulate Chance
     *   Appearance point at maximum cumulative */
    unsigned short cumulateLotPoint01;

    /* 累積後出現ポイント
     *   最大累積時の出現ポイント
     * 2 - Item Accumulate Chance
     *   Appearance point at maximum cumulative */
    unsigned short cumulateLotPoint02;

    /* 累積後出現ポイント
     *   最大累積時の出現ポイント
     * 3 - Item Accumulate Chance
     *   Appearance point at maximum cumulative */
    unsigned short cumulateLotPoint03;

    /* 累積後出現ポイント
     *   最大累積時の出現ポイント
     * 4 - Item Accumulate Chance
     *   Appearance point at maximum cumulative */
    unsigned short cumulateLotPoint04;

    /* 累積後出現ポイント
     *   最大累積時の出現ポイント
     * 5 - Item Accumulate Chance
     *   Appearance point at maximum cumulative */
    unsigned short cumulateLotPoint05;

    /* 累積後出現ポイント
     *   最大累積時の出現ポイント
     * 6 - Item Accumulate Chance
     *   Appearance point at maximum cumulative */
    unsigned short cumulateLotPoint06;

    /* 累積後出現ポイント
     *   最大累積時の出現ポイント
     * 7 - Item Accumulate Chance
     *   Appearance point at maximum cumulative */
    unsigned short cumulateLotPoint07;

    /* 累積後出現ポイント
     *   最大累積時の出現ポイント
     * 8 - Item Accumulate Chance
     *   Appearance point at maximum cumulative */
    unsigned short cumulateLotPoint08;

    /* 別ザクザクフラグID
     *   取得済みフラグとザクザク枠兼用(0:共通使用)
     * 1 - Item Acquisition Flag
     *   Combined use of acquired flag and crunchy frame (0: common use) */
    unsigned int getItemFlagId01;

    /* 別ザクザクフラグID
     *   取得済みフラグとザクザク枠兼用(0:共通使用)
     * 2 - Item Acquisition Flag
     *   Combined use of acquired flag and crunchy frame (0: common use) */
    unsigned int getItemFlagId02;

    /* 別ザクザクフラグID
     *   取得済みフラグとザクザク枠兼用(0:共通使用)
     * 3 - Item Acquisition Flag
     *   Combined use of acquired flag and crunchy frame (0: common use) */
    unsigned int getItemFlagId03;

    /* 別ザクザクフラグID
     *   取得済みフラグとザクザク枠兼用(0:共通使用)
     * 4 - Item Acquisition Flag
     *   Combined use of acquired flag and crunchy frame (0: common use) */
    unsigned int getItemFlagId04;

    /* 別ザクザクフラグID
     *   取得済みフラグとザクザク枠兼用(0:共通使用)
     * 5 - Item Acquisition Flag
     *   Combined use of acquired flag and crunchy frame (0: common use) */
    unsigned int getItemFlagId05;

    /* 別ザクザクフラグID
     *   取得済みフラグとザクザク枠兼用(0:共通使用)
     * 6 - Item Acquisition Flag
     *   Combined use of acquired flag and crunchy frame (0: common use) */
    unsigned int getItemFlagId06;

    /* 別ザクザクフラグID
     *   取得済みフラグとザクザク枠兼用(0:共通使用)
     * 7 - Item Acquisition Flag
     *   Combined use of acquired flag and crunchy frame (0: common use) */
    unsigned int getItemFlagId07;

    /* 別ザクザクフラグID
     *   取得済みフラグとザクザク枠兼用(0:共通使用)
     * 8 - Item Acquisition Flag
     *   Combined use of acquired flag and crunchy frame (0: common use) */
    unsigned int getItemFlagId08;

    /* ザクザクフラグID
     *   取得済みフラグとザクザク枠兼用(0:フラグ無効)
     * Item Acquisition Flag
     *   Combined use of acquired flag and crunchy frame (0: flag invalid) */
    unsigned int getItemFlagId;

    /* 抽選累積保存フラグID
     *   抽選回数保存用(※8フラグ連番使用)
     * Item Accumulate Flag
     *   For saving the number of lottery (* 8 flag serial number used) */
    unsigned int cumulateNumFlagId;

    /* 抽選累積最大数
     *   抽選累積最大数(0:累積なし)
     * Item Accumulate Max
     *   Maximum number of lottery cumulative (0: no cumulative) */
    unsigned char cumulateNumMax;

    /* レア度上書き
     *   宝箱などに、どれくらい貴重なアイテムが入っているかを指定する。-1の時は上書きせず装備品パラのレア度を使用する
     * Item Rarity
     *   Specify how valuable items are in the treasure chest. When -1, use the rarity of the equipment para without overwriting
     * Default Value  = -1 */
    char lotItem_Rarity;

    /* 個数
     *   取得できるアイテムの個数
     * 1 - Item Amount
     *   Number of items that can be acquired */
    unsigned char lotItemNum01;

    /* 個数
     *   取得できるアイテムの個数
     * 2 - Item Amount
     *   Number of items that can be acquired */
    unsigned char lotItemNum02;

    /* 個数
     *   取得できるアイテムの個数
     * 3 - Item Amount
     *   Number of items that can be acquired */
    unsigned char lotItemNum03;

    /* 個数
     *   取得できるアイテムの個数
     * 4 - Item Amount
     *   Number of items that can be acquired */
    unsigned char lotItemNum04;

    /* 個数
     *   取得できるアイテムの個数
     * 5 - Item Amount
     *   Number of items that can be acquired */
    unsigned char lotItemNum05;

    /* 個数
     *   取得できるアイテムの個数
     * 6 - Item Amount
     *   Number of items that can be acquired */
    unsigned char lotItemNum06;

    /* 個数
     *   取得できるアイテムの個数
     * 7 - Item Amount
     *   Number of items that can be acquired */
    unsigned char lotItemNum07;

    /* 個数
     *   取得できるアイテムの個数
     * 8 - Item Amount
     *   Number of items that can be acquired */
    unsigned char lotItemNum08;

    /* 運パラメータ有効
     *   抽選の確率をプレイヤーの運を反映させるか
     * 1 - Affected by Item Discovery
     *   Whether the probability of lottery reflects the player's luck */
    unsigned short enableLuck01:1;

    /* 運パラメータ有効
     *   抽選の確率をプレイヤーの運を反映させるか
     * 2 - Affected by Item Discovery
     *   Whether the probability of lottery reflects the player's luck */
    unsigned short enableLuck02:1;

    /* 運パラメータ有効
     *   抽選の確率をプレイヤーの運を反映させるか
     * 3 - Affected by Item Discovery
     *   Whether the probability of lottery reflects the player's luck */
    unsigned short enableLuck03:1;

    /* 運パラメータ有効
     *   抽選の確率をプレイヤーの運を反映させるか
     * 4 - Affected by Item Discovery
     *   Whether the probability of lottery reflects the player's luck */
    unsigned short enableLuck04:1;

    /* 運パラメータ有効
     *   抽選の確率をプレイヤーの運を反映させるか
     * 5 - Affected by Item Discovery
     *   Whether the probability of lottery reflects the player's luck */
    unsigned short enableLuck05:1;

    /* 運パラメータ有効
     *   抽選の確率をプレイヤーの運を反映させるか
     * 6 - Affected by Item Discovery
     *   Whether the probability of lottery reflects the player's luck */
    unsigned short enableLuck06:1;

    /* 運パラメータ有効
     *   抽選の確率をプレイヤーの運を反映させるか
     * 7 - Affected by Item Discovery
     *   Whether the probability of lottery reflects the player's luck */
    unsigned short enableLuck07:1;

    /* 運パラメータ有効
     *   抽選の確率をプレイヤーの運を反映させるか
     * 8 - Affected by Item Discovery
     *   Whether the probability of lottery reflects the player's luck */
    unsigned short enableLuck08:1;

    /* 累積リセット
     *   累積リセットするか
     * 1 - Accumulate Reset
     *   Whether to reset cumulatively */
    unsigned short cumulateReset01:1;

    /* 累積リセット
     *   累積リセットするか
     * 2 - Accumulate Reset
     *   Whether to reset cumulatively */
    unsigned short cumulateReset02:1;

    /* 累積リセット
     *   累積リセットするか
     * 3 - Accumulate Reset
     *   Whether to reset cumulatively */
    unsigned short cumulateReset03:1;

    /* 累積リセット
     *   累積リセットするか
     * 4 - Accumulate Reset
     *   Whether to reset cumulatively */
    unsigned short cumulateReset04:1;

    /* 累積リセット
     *   累積リセットするか
     * 5 - Accumulate Reset
     *   Whether to reset cumulatively */
    unsigned short cumulateReset05:1;

    /* 累積リセット
     *   累積リセットするか
     * 6 - Accumulate Reset
     *   Whether to reset cumulatively */
    unsigned short cumulateReset06:1;

    /* 累積リセット
     *   累積リセットするか
     * 7 - Accumulate Reset
     *   Whether to reset cumulatively */
    unsigned short cumulateReset07:1;

    /* 累積リセット
     *   累積リセットするか
     * 8 - Accumulate Reset
     *   Whether to reset cumulatively */
    unsigned short cumulateReset08:1;

    /* X週目以降オフセット
     *   周回プレイ時のオフセット
     * Game Clear Offset
     *   Offset during lap play
     * Default Value  = -1 */
    char GameClearOffset;

    /* 協力霊でも抽選するか
     *   自身が協力霊の時でも抽選するか
     * Can Friendly Phantom Acquire
     *   Do you draw lots even when you are a cooperating spirit? */
    unsigned char canExecByFriendlyGhost:1;

    /* 敵対霊でも抽選するか
     *   自身が敵対霊の時でも抽選するか
     * Can Hostile Phantom Acquire
     *   Do you draw lots even when you are a hostile spirit? */
    unsigned char canExecByHostileGhost:1;

    unsigned char PAD1:6;

    unsigned short PAD2;
} itemlot_param_t;
