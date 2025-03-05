#pragma once

typedef struct er_knockback_param_s {
    /* 極小ダメージ_速度維持時間[s]
     *   極小ダメージアニメの時に使用される維持時間を設定
     * Damage Level - Minimum - Maintenance Time
     *   Set the maintenance time used for tiny damage animation */
    float damage_Min_ContTime;

    /* 小ダメージ_速度維持時間[s]
     *   小ダメージアニメの時に使用される維持時間を設定
     * Damage Level - Small - Maintenance Time
     *   Set the maintenance time used for small damage animation */
    float damage_S_ContTime;

    /* 中ダメージ_速度維持時間[s]
     *   中ダメージアニメの時に使用される維持時間を設定
     * Damage Level - Medium - Maintenance Time
     *   Set the maintenance time used for medium damage animation */
    float damage_M_ContTime;

    /* 大ダメージ_速度維持時間[s]
     *   大ダメージアニメの時に使用される維持時間を設定
     * Damage Level - Heavy - Maintenance Time
     *   Set the maintenance time used for heavy damage animation */
    float damage_L_ContTime;

    /* 小吹っ飛び_速度維持時間[s]
     *   小吹っ飛びダメージアニメの時に使用される維持時間を設定
     * Damage Level - Small Blow-off - Maintenance Time
     *   Set the maintenance time used for small blow-off damage animation */
    float damage_BlowS_ContTime;

    /* 大吹っ飛び_速度維持時間[s]
     *   大吹っ飛びダメージアニメの時に使用される維持時間を設定
     * Damage Level - Heavy Blow-off - Maintenance Time
     *   Set the maintenance time used during the big blow damage animation */
    float damage_BlowM_ContTime;

    /* 叩きつけ_速度維持時間[s]
     *   叩きつけダメージアニメの時に使用される維持時間を設定
     * Damage Level - Strike - Maintenance Time
     *   Set the maintenance time used for slamming damage animation */
    float damage_Strike_ContTime;

    /* 打ち上げ_速度維持時間[s]
     *   打ち上げダメージアニメの時に使用される維持時間を設定
     * Damage Level - Uppercut - Maintenance Time
     *   Set the maintenance time used for launch damage animation */
    float damage_Uppercut_ContTime;

    /* プッシュ_速度維持時間[s]
     *   プッシュダメージアニメの時に使用される維持時間を設定
     * Damage Level - Push - Maintenance Time
     *   Set the maintenance time used for push damage animation */
    float damage_Push_ContTime;

    /* ブレス_速度維持時間[s]
     *   ブレスダメージアニメの時に使用される維持時間を設定
     * Damage Level - Breath - Maintenance Time
     *   Set the maintenance time used for breath damage animation */
    float damage_Breath_ContTime;

    /* ヘッドショット_速度維持時間[s]
     *   ヘッドショットダメージアニメの時に使用される維持時間を設定
     * Damage Level - Headshot - Maintenance Time
     *   Headshot damage Set the maintenance time used during animation */
    float damage_HeadShot_ContTime;

    /* ガード受け小_速度維持時間[s]
     *   ガード受け小アニメの時に使用される維持時間を設定
     * Guard Damage Level - Small - Maintenance Time
     *   Set the maintenance time used for guard receiving small animation */
    float guard_S_ContTime;

    /* ガード受け大_速度維持時間[s]
     *   ガード受け大アニメの時に使用される維持時間を設定
     * Guard Damage Level - Heavy - Maintenance Time
     *   Set the maintenance time used at the time of guard receiving large animation */
    float guard_L_ContTime;

    /* ガード受け特大_速度維持時間[s]
     *   ガード受け特大アニメの時に使用される維持時間を設定
     * Guard Damage Level - Very Heavy - Maintenance Time
     *   Set the maintenance time used for guard receiving oversized animation */
    float guard_LL_ContTime;

    /* ガードくずされ_速度維持時間[s]
     *   ガードくずされアニメの時に仕様される維持時間を設定
     * Guard Damage Level - Break - Maintenance Time
     *   Set the maintenance time specified at the time of guard scraping animation */
    float guardBrake_ContTime;

    /* 極小ダメージ_減速時間[s]
     *   極小ダメージアニメの時に使用される減速時間を設定
     * Damage Level - Minimum - Deceleration Time
     *   Set the deceleration time used for minimal damage animation */
    float damage_Min_DecTime;

    /* 小ダメージ_減速時間[s]
     *   小ダメージアニメの時に使用される減速時間を設定
     * Damage Level - Small - Deceleration Time
     *   Set the deceleration time used for small damage animation */
    float damage_S_DecTime;

    /* 中ダメージ_減速時間[s]
     *   中ダメージアニメの時に使用される減速時間を設定
     * Damage Level - Medium - Deceleration Time
     *   Set the deceleration time used for medium damage animation */
    float damage_M_DecTime;

    /* 大ダメージ_減速時間[s]
     *   大ダメージアニメの時に使用される減速時間を設定
     * Damage Level - Heavy - Deceleration Time
     *   Set the deceleration time used for heavy damage animation */
    float damage_L_DecTime;

    /* 小吹っ飛び_減速時間[s]
     *   小吹っ飛びダメージアニメの時に使用される減速時間を設定
     * Damage Level - Small Blow-off - Deceleration Time
     *   Set the deceleration time used for small blow-off damage animation */
    float damage_BlowS_DecTime;

    /* 大吹っ飛び_減速時間[s]
     *   大吹っ飛びダメージアニメの時に使用される減速時間を設定
     * Damage Level - Heavy Blow-off - Deceleration Time
     *   Large blow-off damage Set the deceleration time used during animation */
    float damage_BlowM_DecTime;

    /* 叩きつけ_減速時間[s]
     *   叩きつけダメージアニメの時に使用される減速時間を設定
     * Damage Level - Strike - Deceleration Time
     *   Set the deceleration time used during slamming damage animation */
    float damage_Strike_DecTime;

    /* 打ち上げ_減速時間[s]
     *   打ち上げダメージアニメの時に使用される減速時間を設定
     * Damage Level - Uppercut - Deceleration Time
     *   Set the deceleration time used during launch damage animation */
    float damage_Uppercut_DecTime;

    /* プッシュ_減速時間[s]
     *   プッシュダメージアニメの時に使用される減速時間を設定
     * Damage Level - Push - Deceleration Time
     *   Set the deceleration time used during push damage animation */
    float damage_Push_DecTime;

    /* ブレス_減速時間[s]
     *   ブレスダメージアニメの時に使用される減速時間を設定
     * Damage Level - Breath - Deceleration Time
     *   Set the deceleration time used during breath damage animation */
    float damage_Breath_DecTime;

    /* ヘッドショット_減速時間[s]
     *   ヘッドショットダメージアニメの時に使用される減速時間を設定
     * Damage Level - Headshot - Deceleration Time
     *   Headshot damage Set the deceleration time used during animation */
    float damage_HeadShot_DecTime;

    /* ガード受け小_減速時間[s]
     *   ガード受け小アニメの時に使用される減速時間を設定
     * Guard Damage Level - Small - Deceleration Time
     *   Set the deceleration time used for guard receiving small animation */
    float guard_S_DecTime;

    /* ガード受け大_減速時間[s]
     *   ガード受け大アニメの時に使用される減速時間を設定
     * Guard Damage Level - Heavy - Deceleration Time
     *   Set the deceleration time used for guard receiving large animation */
    float guard_L_DecTime;

    /* ガード受け特大_減速時間[s]
     *   ガード受け特大アニメの時に使用される減速時間を設定
     * Guard Damage Level - Very Break - Deceleration Time
     *   Set the deceleration time used for guard receiving oversized animation */
    float guard_LL_DecTime;

    /* ガードくずされ_減速時間[s]
     *   ガードくずされアニメの時に仕様される減速時間を設定
     * Guard Damage Level - Break - Deceleration Time
     *   Set the deceleration time specified at the time of guard breaking animation */
    float guardBrake_DecTime;

    /* pading */
    char pad[8];
} er_knockback_param_t;
