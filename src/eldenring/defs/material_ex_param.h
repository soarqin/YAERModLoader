#pragma once

typedef struct material_ex_param_s {
    /* マテリアルパラメータ名
     *   マテリアルのパラメータ名を設定する。最大31文字まで
     * Material Param Name
     *   Set the parameter name of the material. Up to 31 characters */
    wchar_t paramName[32];

    /* 対象マテリアルID
     *   NPCパラ：常駐マテリアル拡張パラID用設定　-1なら全マテリアル対象
     * Material ID
     *   NPC Para - Resident Material Expansion Para ID setting -1 for all materials
     * Default Value  = -1 */
    int materialId;

    /* 上書き値1(R)
     *   NPCパラ：常駐マテリアル拡張パラID用設定
     * Material Param Value - R
     *   NPC Para - Resident Material Extended Para ID Settings */
    float materialParamValue0;

    /* 上書き値2(G)
     *   NPCパラ：常駐マテリアル拡張パラID用設定
     * Material Param Value - G
     *   NPC Para - Resident Material Expansion Para ID Settings */
    float materialParamValue1;

    /* 上書き値3(B)
     *   NPCパラ：常駐マテリアル拡張パラID用設定
     * Material Param Value - B
     *   NPC Para - Resident Material Expansion Para ID Settings */
    float materialParamValue2;

    /* 上書き値4(A)
     *   NPCパラ：常駐マテリアル拡張パラID用設定
     * Material Param Value - A
     *   NPC Para - Resident Material Extended Para ID Settings */
    float materialParamValue3;

    /* 上書き値5(I)
     *   NPCパラ：常駐マテリアル拡張パラID用設定
     * Material Param Value - I
     *   NPC Para - Resident Material Expansion Para ID Settings
     * Default Value  = 1 */
    float materialParamValue4;

    /* パディング
     *   パディング */
    char pad[8];
} material_ex_param_t;
