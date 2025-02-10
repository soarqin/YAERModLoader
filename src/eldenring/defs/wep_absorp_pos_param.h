#pragma once

typedef struct wep_absorp_pos_param_s {
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

    /* 格納場所タイプ
     *   この値によって納刀時アニメが変わります
     * Sheath Position Type
     *   The animation at the time of sword delivery changes depending on this value */
    unsigned char hangPosType;

    /* スケルトン結合するか
     *   スケルトン結合するか
     * Is Skeleton Bind
     *   Do you want to combine skeletons? */
    unsigned char isSkeletonBind;

    /* パディング */
    char pad0[2];

    /* モデル0_右手時吸着ダミポリ
     *   武器を右手に片手で持っているときのモデル0の吸着ダミポリ。
     * Right Hand - Dummy Poly - Model [0]
     *   Model 0 adsorption Damipoli when holding the weapon in one hand. */
    short right_0;

    /* モデル0_左手時吸着ダミポリ
     *   武器を左手に片手で持っているときのモデル0の吸着ダミポリ。
     * Left Hand - Dummy Poly - Model [0]
     *   Model 0 adsorption Damipoli when holding the weapon in one hand. */
    short left_0;

    /* モデル0_右手両手時吸着ダミポリ
     *   右手武器を両手で持っているときのモデル0の吸着ダミポリ。
     * Both Hand - Dummy Poly - Model [0]
     *   Model 0 adsorption Damipoli when holding a right-handed weapon with both hands. */
    short both_0;

    /* モデル0_左手納刀時吸着ダミポリ
     *   武器を左手に持っていて、その武器を納刀しているときのモデル0の吸着ダミポリ。
     * Left Sheath - Dummy Poly - Model [0]
     *   Model 0 adsorption Damipoli when holding a weapon in the left hand and delivering the weapon. */
    short leftHang_0;

    /* モデル0_右手納刀時吸着ダミポリ
     *   武器を右手に持っていて、その武器を納刀しているときのモデル0の吸着ダミポリ。
     * Right Sheath - Dummy Poly - Model [0]
     *   Model 0 adsorption Damipoli when holding a weapon in the right hand and delivering the weapon. */
    short rightHang_0;

    /* モデル1_右手時吸着ダミポリ
     *   武器を右手に片手で持っているときのモデル1の吸着ダミポリ。
     * Right Hand - Dummy Poly - Model [1]
     *   Model 1 adsorption Damipoli when holding the weapon in one hand. */
    short right_1;

    /* モデル1_左手時吸着ダミポリ
     *   武器を左手に片手で持っているときのモデル1の吸着ダミポリ。
     * Left Hand - Dummy Poly - Model [1]
     *   Model 1 adsorption Damipoli when holding the weapon in one hand. */
    short left_1;

    /* モデル1_右手両手時吸着ダミポリ
     *   右手武器を両手で持っているときのモデル1の吸着ダミポリ。
     * Both Hand - Dummy Poly - Model [1]
     *   Model 1 adsorption Damipoli when holding a right-handed weapon with both hands. */
    short both_1;

    /* モデル1_左手納刀時吸着ダミポリ
     *   武器を左手に持っていて、その武器を納刀しているときのモデル1の吸着ダミポリ。
     * Left Sheath - Dummy Poly - Model [1]
     *   Model 1 adsorption Damipoli when holding a weapon in the left hand and delivering the weapon. */
    short leftHang_1;

    /* モデル1_右手納刀時吸着ダミポリ
     *   武器を右手に持っていて、その武器を納刀しているときのモデル1の吸着ダミポリ。
     * Right Sheath - Dummy Poly - Model [1]
     *   Model 1 adsorption Damipoli when holding a weapon in the right hand and delivering the weapon. */
    short rightHang_1;

    /* モデル2_右手時吸着ダミポリ
     *   武器を右手に片手で持っているときのモデル2の吸着ダミポリ。
     * Right Hand - Dummy Poly - Model [2]
     *   Model 2 adsorption Damipoli when holding the weapon in one hand. */
    short right_2;

    /* モデル2_左手時吸着ダミポリ
     *   武器を左手に片手で持っているときのモデル2の吸着ダミポリ。
     * Left Hand - Dummy Poly - Model [2]
     *   Model 2 adsorption Damipoli when holding the weapon in one hand. */
    short left_2;

    /* モデル2_右手両手時吸着ダミポリ
     *   右手武器を両手で持っているときのモデル2の吸着ダミポリ。
     * Both Hand - Dummy Poly - Model [2]
     *   Model 2 adsorption Damipoli when holding a right-handed weapon with both hands. */
    short both_2;

    /* モデル2_左手納刀時吸着ダミポリ
     *   武器を左手に持っていて、その武器を納刀しているときのモデル2の吸着ダミポリ。
     * Left Sheath - Dummy Poly - Model [2]
     *   Model 2 adsorption Damipoli when holding a weapon in the left hand and delivering the weapon. */
    short leftHang_2;

    /* モデル2_右手納刀時吸着ダミポリ
     *   武器を右手に持っていて、その武器を納刀しているときのモデル2の吸着ダミポリ。
     * Right Sheath - Dummy Poly - Model [2]
     *   Model 2 adsorption Damipoli when holding a weapon in the right hand and delivering the weapon. */
    short rightHang_2;

    /* モデル3_右手時吸着ダミポリ
     *   武器を右手に片手で持っているときのモデル3の吸着ダミポリ。
     * Right Hand - Dummy Poly - Model [3]
     *   Model 3 adsorption Damipoli when holding the weapon in one hand. */
    short right_3;

    /* モデル3_左手時吸着ダミポリ
     *   武器を左手に片手で持っているときのモデル3の吸着ダミポリ。
     * Left Hand - Dummy Poly - Model [3]
     *   Model 3 adsorption Damipoli when holding the weapon in one hand. */
    short left_3;

    /* モデル3_右手両手時吸着ダミポリ
     *   右手武器を両手で持っているときのモデル3の吸着ダミポリ。
     * Both Hand - Dummy Poly - Model [3]
     *   Model 3 adsorption Damipoli when holding a right-handed weapon with both hands. */
    short both_3;

    /* モデル3_左手納刀時吸着ダミポリ
     *   武器を左手に持っていて、その武器を納刀しているときのモデル3の吸着ダミポリ。
     * Left Sheath - Dummy Poly - Model [3]
     *   Model 3 Adsorption Damipoli when holding a weapon in the left hand and delivering the weapon. */
    short leftHang_3;

    /* モデル3_右手納刀時吸着ダミポリ
     *   武器を右手に持っていて、その武器を納刀しているときのモデル3の吸着ダミポリ。
     * Right Sheath - Dummy Poly - Model [3]
     *   Model 3 Adsorption Damipoli when holding a weapon in his right hand and delivering the weapon. */
    short rightHang_3;

    /* モデル0_武器非表示タイプ
     *   モデル0の非表示タイプ。TAEで武器非表示にする際にこれと一致するものを消す
     * Hidden Type - Model [0]
     *   Hidden type of model 0. When hiding a weapon with TAE, erase the one that matches this */
    unsigned char wepInvisibleType_0;

    /* モデル1_武器非表示タイプ
     *   モデル1の非表示タイプ。TAEで武器非表示にする際にこれと一致するものを消す
     * Hidden Type - Model [1]
     *   Hidden type of model 1. When hiding a weapon with TAE, erase the one that matches this */
    unsigned char wepInvisibleType_1;

    /* モデル2_武器非表示タイプ
     *   モデル2の非表示タイプ。TAEで武器非表示にする際にこれと一致するものを消す
     * Hidden Type - Model [2]
     *   Hidden type of model 2. When hiding a weapon with TAE, erase the one that matches this */
    unsigned char wepInvisibleType_2;

    /* モデル3_武器非表示タイプ
     *   モデル3の非表示タイプ。TAEで武器非表示にする際にこれと一致するものを消す
     * Hidden Type - Model [3]
     *   Model 3 hidden type. When hiding a weapon with TAE, erase the one that matches this */
    unsigned char wepInvisibleType_3;

    /* モデル0_左手両手時吸着ダミポリ
     *   左手武器を両手で持っているときのモデル0の吸着ダミポリ。
     * Left Both-Hand - Dummy Poly - Model [0]
     *   Model 0 adsorption Damipoli when holding a left-handed weapon with both hands. */
    short leftBoth_0;

    /* モデル1_左手両手時吸着ダミポリ
     *   左手武器を両手で持っているときのモデル1の吸着ダミポリ。
     * Left Both-Hand - Dummy Poly - Model [1]
     *   Model 1 adsorption Damipoli when holding a left-handed weapon with both hands. */
    short leftBoth_1;

    /* モデル2_左手両手時吸着ダミポリ
     *   左手武器を両手で持っているときのモデル2の吸着ダミポリ。
     * Left Both-Hand - Dummy Poly - Model [2]
     *   Model 2 adsorption Damipoli when holding a left-handed weapon with both hands. */
    short leftBoth_2;

    /* モデル3_左手両手時吸着ダミポリ
     *   左手武器を両手で持っているときのモデル3の吸着ダミポリ。
     * Left Both-Hand - Dummy Poly - Model [3]
     *   Model 3 adsorption Damipoli when holding a left-handed weapon with both hands. */
    short leftBoth_3;

    /* モデル0_右手時表示位置
     *   モデル0_右手時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Right Hand - Model [0]
     *   Model 0_ Right-hand display position (used to specify hidden position from TAE) */
    unsigned char dispPosType_right_0;

    /* モデル0_左手時表示位置
     *   モデル0_左手時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Left Hand - Model [0]
     *   Model 0_Left hand display position (used to specify hidden position from TAE) */
    unsigned char dispPosType_left_0;

    /* モデル0_右手両手時表示位置
     *   モデル0_右手両手時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Right Both-hand - Model [0]
     *   Model 0_Right-handed two-handed display position (used to specify hidden position from TAE) */
    unsigned char dispPosType_rightBoth_0;

    /* モデル0_左手両手時表示位置
     *   モデル0_左手両手時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Left Both-Hand - Model [0]
     *   Model 0_ Left-handed two-handed display position (used to specify hidden position from TAE) */
    unsigned char dispPosType_leftBoth_0;

    /* モデル0_右手納刀時表示位置
     *   モデル0_右手納刀時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Right Sheath - Model [0]
     *   Model 0_ Right-handed sword display position (used to specify the non-display position from TAE) */
    unsigned char dispPosType_rightHang_0;

    /* モデル0_左手納刀時表示位置
     *   モデル0_左手納刀時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Left Sheath - Model [0]
     *   Model 0_ Left hand sword display position (used to specify the non-display position from TAE) */
    unsigned char dispPosType_leftHang_0;

    /* モデル1_右手時表示位置
     *   モデル1_右手時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Right Hand - Model [1]
     *   Model 1_ Right-hand display position (used to specify hidden position from TAE) */
    unsigned char dispPosType_right_1;

    /* モデル1_左手時表示位置
     *   モデル1_左手時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Left Hand - Model [1]
     *   Model 1_Left hand display position (used to specify hidden position from TAE) */
    unsigned char dispPosType_left_1;

    /* モデル1_右手両手時表示位置
     *   モデル1_右手両手時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Right Both-hand - Model [1]
     *   Model 1_Right-handed two-handed display position (used to specify hidden position from TAE) */
    unsigned char dispPosType_rightBoth_1;

    /* モデル1_左手両手時表示位置
     *   モデル1_左手両手時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Left Both-Hand - Model [1]
     *   Model 1_ Left-handed two-handed display position (used to specify hidden position from TAE) */
    unsigned char dispPosType_leftBoth_1;

    /* モデル1_右手納刀時表示位置
     *   モデル1_右手納刀時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Right Sheath - Model [1]
     *   Model 1_ Right-handed sword display position (used to specify the non-display position from TAE) */
    unsigned char dispPosType_rightHang_1;

    /* モデル1_左手納刀時表示位置
     *   モデル1_左手納刀時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Left Sheath - Model [1]
     *   Model 1_ Left hand sword display position (used to specify the non-display position from TAE) */
    unsigned char dispPosType_leftHang_1;

    /* モデル2_右手時表示位置
     *   モデル2_右手時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Right Hand - Model [2]
     *   Model 2_ Right-hand display position (used to specify hidden position from TAE) */
    unsigned char dispPosType_right_2;

    /* モデル2_左手時表示位置
     *   モデル2_左手時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Left Hand - Model [2]
     *   Model 2_Left hand display position (used to specify hidden position from TAE) */
    unsigned char dispPosType_left_2;

    /* モデル2_右手両手時表示位置
     *   モデル2_右手両手時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Right Both-hand - Model [2]
     *   Model 2_Right-handed two-handed display position (used to specify hidden position from TAE) */
    unsigned char dispPosType_rightBoth_2;

    /* モデル2_左手両手時表示位置
     *   モデル2_左手両手時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Left Both-Hand - Model [2]
     *   Model 2_ Left-handed two-handed display position (used to specify hidden position from TAE) */
    unsigned char dispPosType_leftBoth_2;

    /* モデル2_右手納刀時表示位置
     *   モデル2_右手納刀時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Right Sheath - Model [2]
     *   Model 2_Right-handed sword display position (used to specify the non-display position from TAE) */
    unsigned char dispPosType_rightHang_2;

    /* モデル2_左手納刀時表示位置
     *   モデル2_左手納刀時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Left Sheath - Model [2]
     *   Model 2_ Left hand sword display position (used to specify the non-display position from TAE) */
    unsigned char dispPosType_leftHang_2;

    /* モデル3_右手時表示位置
     *   モデル3_右手時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Right Hand - Model [3]
     *   Model 3_ Right-hand display position (used to specify hidden position from TAE) */
    unsigned char dispPosType_right_3;

    /* モデル3_左手時表示位置
     *   モデル3_左手時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Left Hand - Model [3]
     *   Model 3_Left hand display position (used to specify hidden position from TAE) */
    unsigned char dispPosType_left_3;

    /* モデル3_右手両手時表示位置
     *   モデル3_右手両手時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Right Both-hand - Model [3]
     *   Model 3_Right-handed two-handed display position (used to specify hidden position from TAE) */
    unsigned char dispPosType_rightBoth_3;

    /* モデル3_左手両手時表示位置
     *   モデル3_左手両手時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Left Both-Hand - Model [3]
     *   Model 3_ Left-handed two-handed display position (used to specify hidden position from TAE) */
    unsigned char dispPosType_leftBoth_3;

    /* モデル3_右手納刀時表示位置
     *   モデル3_右手納刀時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Right Sheath - Model [3]
     *   Model 3_Right-handed sword display position (used to specify the non-display position from TAE) */
    unsigned char dispPosType_rightHang_3;

    /* モデル3_左手納刀時表示位置
     *   モデル3_左手納刀時表示位置(TAE から非表示位置を指定するのに使用する)
     * Display Position - Left Sheath - Model [3]
     *   Model 3_ Left hand sword display position (used to specify the non-display position from TAE) */
    unsigned char dispPosType_leftHang_3;

    char unknown_0x54;

    char unknown_0x55;

    char unknown_0x56;

    char unknown_0x57;

    /* 予約領域 */
    char reserve[8];
} wep_absorp_pos_param_t;
