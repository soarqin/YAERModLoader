#pragma once

typedef struct bullet_create_limit_param_s {
    /* グループ内上限弾数
     *   同一グループ内での作成上限数
     * Max Amount - By Group
     *   Maximum number of creations in the same group */
    unsigned char limitNum_byGroup;

    /* オーナー毎に制限するか
     *   オーナー毎に制限するか
     * Is Limited for each Owner
     *   Is it restricted for each owner? */
    unsigned char isLimitEachOwner:1;

    /* パディング
     *   pad2 */
    char pad2:7;

    /* パディング
     *   pad3 */
    char pad[30];
} bullet_create_limit_param_t;
