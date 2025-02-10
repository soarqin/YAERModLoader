#pragma once

typedef struct sound_chr_physics_se_param_s {
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

    /* 地面接触SEID
     *   死亡後、地面と接触したときに発音するSEID。(-1：無効)。SEIDカテゴリーはc固定
     * Contact Land on Death - SE ID
     *   SEID pronounced when contacting the ground after death. (-1: Invalid). SEID category is fixed to c
     * Default Value  = -1 */
    int ContactLandSeId;

    /* 地面接触追加SEID(材質用)
     *   死亡後、地面と接触したときに発音する追加SEID(材質用)。(-1：無効)。SEIDカテゴリーはc固定
     * Contact Land on Death - Additional SE ID
     *   Additional SEID (for material) that sounds when it comes into contact with the ground after death. (-1: Invalid). SEID category is fixed to c
     * Default Value  = -1 */
    int ContactLandAddSeId;

    /* 地面接触発音回数
     *   死亡後、地面接触時に発音する回数
     * Contact Land on Death - Play Count
     *   Number of pronunciations when touching the ground after death
     * Default Value  = 1 */
    int ContactLandPlayNum;

    /* 地面接触発音回数を剛体単位でカウントするか？
     *   死亡後地、面接触発音回数を剛体単位でカウントするか？(〇：剛体単位、×：キャラ単位)
     * Enable Play Count per Rigid Body Unit
     *   Do you count the number of pronunciations of surface contact after death in rigid body units? (: Rigid body unit, : Character unit) */
    unsigned char IsEnablePlayCountPerRigid;

    char pad[3];

    /* 地面接触最小力積値
     *   死亡後、地面接触判定に必要な最小力積値
     * Contact Land on Death - Min Impulse
     *   Minimum impulse value required for ground contact determination after death
     * Default Value  = 20 */
    float ContactLandMinImpuse;

    /* 地面接触最小速度値
     *   死亡後、地面接触判定に必要な最小速度値
     * Contact Land on Death - Min Speed
     *   Minimum speed value required for ground contact determination after death */
    float ContactLandMinSpeed;

    /* Player接触SEID
     *   死亡後、Playerと接触したときに鳴らすSEID。(-1：無効)。SEIDカテゴリーはc固定
     * Contact Player on Death - SE ID
     *   SEID that sounds when you come into contact with Player after death. (-1: Invalid). SEID category is fixed to c
     * Default Value  = -1 */
    int ContactPlayerSeId;

    /* Player接触最小力積値
     *   死亡後、Player接触判定に必要な最小力積値
     * Contact Player on Death - Min Impulse
     *   Minimum impulse value required for Player contact judgment after death
     * Default Value  = 20 */
    float ContactPlayerMinImpuse;

    /* Player接触最小速度値
     *   死亡後、Player接触判定に必要な最小速度値
     * Contact Player on Death - Min Speed
     *   Minimum speed value required for Player contact judgment after death */
    float ContactPlayerMinSpeed;

    /* 接触判定剛体IDX0
     *   接触判定する剛体のINDEXを指定します。SEを付けたい剛体だけ指定します
     * Contact Check Rigid Index [0]
     *   Specify the INDEX of the rigid body for contact judgment. Specify only the rigid body to which you want to attach SE
     * Default Value  = -1 */
    char ContactCheckRigidIdx0;

    /* 接触判定剛体IDX1
     *   接触判定する剛体のINDEXを指定します。SEを付けたい剛体だけ指定します
     * Contact Check Rigid Index [1]
     *   Specify the INDEX of the rigid body for contact judgment. Specify only the rigid body to which you want to attach SE
     * Default Value  = -1 */
    char ContactCheckRigidIdx1;

    /* 接触判定剛体IDX2
     *   接触判定する剛体のINDEXを指定します。SEを付けたい剛体だけ指定します
     * Contact Check Rigid Index [2]
     *   Specify the INDEX of the rigid body for contact judgment. Specify only the rigid body to which you want to attach SE
     * Default Value  = -1 */
    char ContactCheckRigidIdx2;

    /* 接触判定剛体IDX3
     *   接触判定する剛体のINDEXを指定します。SEを付けたい剛体だけ指定します
     * Contact Check Rigid Index [3]
     *   Specify the INDEX of the rigid body for contact judgment. Specify only the rigid body to which you want to attach SE
     * Default Value  = -1 */
    char ContactCheckRigidIdx3;

    /* 接触判定剛体IDX4
     *   接触判定する剛体のINDEXを指定します。SEを付けたい剛体だけ指定します
     * Contact Check Rigid Index [4]
     *   Specify the INDEX of the rigid body for contact judgment. Specify only the rigid body to which you want to attach SE
     * Default Value  = -1 */
    char ContactCheckRigidIdx4;

    /* 接触判定剛体IDX5
     *   接触判定する剛体のINDEXを指定します。SEを付けたい剛体だけ指定します
     * Contact Check Rigid Index [5]
     *   Specify the INDEX of the rigid body for contact judgment. Specify only the rigid body to which you want to attach SE
     * Default Value  = -1 */
    char ContactCheckRigidIdx5;

    /* 接触判定剛体IDX6
     *   接触判定する剛体のINDEXを指定します。SEを付けたい剛体だけ指定します
     * Contact Check Rigid Index [6]
     *   Specify the INDEX of the rigid body for contact judgment. Specify only the rigid body to which you want to attach SE
     * Default Value  = -1 */
    char ContactCheckRigidIdx6;

    /* 接触判定剛体IDX7
     *   接触判定する剛体のINDEXを指定します。SEを付けたい剛体だけ指定します
     * Contact Check Rigid Index [7]
     *   Specify the INDEX of the rigid body for contact judgment. Specify only the rigid body to which you want to attach SE
     * Default Value  = -1 */
    char ContactCheckRigidIdx7;

    /* 接触判定剛体IDX8
     *   接触判定する剛体のINDEXを指定します。SEを付けたい剛体だけ指定します
     * Contact Check Rigid Index [8]
     *   Specify the INDEX of the rigid body for contact judgment. Specify only the rigid body to which you want to attach SE
     * Default Value  = -1 */
    char ContactCheckRigidIdx8;

    /* 接触判定剛体IDX9
     *   接触判定する剛体のINDEXを指定します。SEを付けたい剛体だけ指定します
     * Contact Check Rigid Index [9]
     *   Specify the INDEX of the rigid body for contact judgment. Specify only the rigid body to which you want to attach SE
     * Default Value  = -1 */
    char ContactCheckRigidIdx9;

    /* 接触判定剛体IDX10
     *   接触判定する剛体のINDEXを指定します。SEを付けたい剛体だけ指定します
     * Contact Check Rigid Index [10]
     *   Specify the INDEX of the rigid body for contact judgment. Specify only the rigid body to which you want to attach SE
     * Default Value  = -1 */
    char ContactCheckRigidIdx10;

    /* 接触判定剛体IDX11
     *   接触判定する剛体のINDEXを指定します。SEを付けたい剛体だけ指定します
     * Contact Check Rigid Index [11]
     *   Specify the INDEX of the rigid body for contact judgment. Specify only the rigid body to which you want to attach SE
     * Default Value  = -1 */
    char ContactCheckRigidIdx11;

    /* 接触判定剛体IDX12
     *   接触判定する剛体のINDEXを指定します。SEを付けたい剛体だけ指定します
     * Contact Check Rigid Index [12]
     *   Specify the INDEX of the rigid body for contact judgment. Specify only the rigid body to which you want to attach SE
     * Default Value  = -1 */
    char ContactCheckRigidIdx12;

    /* 接触判定剛体IDX13
     *   接触判定する剛体のINDEXを指定します。SEを付けたい剛体だけ指定します
     * Contact Check Rigid Index [13]
     *   Specify the INDEX of the rigid body for contact judgment. Specify only the rigid body to which you want to attach SE
     * Default Value  = -1 */
    char ContactCheckRigidIdx13;

    /* 接触判定剛体IDX14
     *   接触判定する剛体のINDEXを指定します。SEを付けたい剛体だけ指定します
     * Contact Check Rigid Index [14]
     *   Specify the INDEX of the rigid body for contact judgment. Specify only the rigid body to which you want to attach SE
     * Default Value  = -1 */
    char ContactCheckRigidIdx14;

    /* 接触判定剛体IDX15
     *   接触判定する剛体のINDEXを指定します。SEを付けたい剛体だけ指定します
     * Contact Check Rigid Index [15]
     *   Specify the INDEX of the rigid body for contact judgment. Specify only the rigid body to which you want to attach SE
     * Default Value  = -1 */
    char ContactCheckRigidIdx15;
} sound_chr_physics_se_param_t;
