#pragma once

typedef struct er_buddy_param_s {
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

    /* 召喚特殊効果ID
     *   召喚条件になる特殊効果IDを設定します 
     * Trigger SpEffect ID
     *   Set the special effect ID that will be the summoning condition
     * Default Value  = -1 */
    int triggerSpEffectId;

    /* NPCパラメータID
     *   召喚されるバディのNPCパラメータIDを設定します
     * NPC Param ID
     *   Set the NPC parameter ID of the summoned buddy
     * Default Value  = -1 */
    int npcParamId;

    /* 思考パラメータID
     *   召喚されるバディのNPC思考パラメータIDを設定します
     * NPC Think Param ID
     *   Sets the NPC Thinking Parameter ID of the summoned buddy
     * Default Value  = -1 */
    int npcThinkParamId;

    /* 騎乗（乗られる側）：NPCパラメータID
     *   騎乗状態で召喚したいバディの場合、「乗られる側」のNPCパラメータIDを設定します 
     * NPC Param ID - Ride
     *   For buddies that you want to summon while riding, set the NPC parameter ID for the rider
     * Default Value  = -1 */
    int npcParamId_ridden;

    /* 騎乗（乗られる側）：思考パラメータID
     *   騎乗状態で召喚したいバディの場合、「乗られる側」のNPC思考パラメータIDを設定します
     * NPC Think Param ID - Ride
     *   For buddies that you want to summon while riding, set the NPC Thinking Parameter ID for the rider
     * Default Value  = -1 */
    int npcThinkParamId_ridden;

    /* X：配置座標オフセット[m]
     *   バディを召喚ポイントから、X座標にオフセットする距離をメートル単位で設定します
     * Spawn Offset: X (left/right)
     *   Sets the distance in meters to offset the buddy from the summon point to the X coordinate (left/right). */
    float x_offset;

    /* Z：配置座標オフセット[m]
     *   バディを召喚ポイントから、Z座標にオフセットする距離をメートル単位で設定します
     * Spawn Offset: Z (forward/back)
     *   Sets the distance in meters to offsets the buddy from the summon point to the Z coordinate (forwad/back). */
    float z_offset;

    /* Y：自分の配置角度[deg]
     *   Y軸を中心に、自分を回転させる角度を設定します
     * Spawn Angle: Y
     *   Sets summon position rotation. */
    float y_angle;

    /* 石碑周辺から出現するか？
     *   石碑周辺から出現するか？
     * Appear near Stone Monument
     *   Forces summon to spawn at summon monument. */
    unsigned char appearOnAroundSekihi;

    /* PCとのターゲット共有をスキップするか？
     *   PCとのターゲット共有をスキップするか？
     * Disable Player Target Share
     *   Disables summon targeting whoever PC locked-onto. */
    unsigned char disablePCTargetShare;

    /* PC追従＆ワープタイプ 
     *   PC追従＆ワープタイプ 
     * Player Follow Type
     *   Determines PC tracking and non-combat behavior. */
    unsigned char pcFollowType;

    /* リザーブ
     *   リザーブ */
    char Reserve[1];

    /* +0時ドーピング特殊効果
     *   +0時ドーピング特殊効果
     * Reinforcement SpEffect: +0
     *   SpEffect granted when reinforced to +0
     * Default Value  = -1 */
    int dopingSpEffect_lv0;

    /* +1時ドーピング特殊効果
     *   +0時ドーピング特殊効果
     * Reinforcement SpEffect: +1
     *   SpEffect granted when reinforced to +1.
     * Default Value  = -1 */
    int dopingSpEffect_lv1;

    /* +2時ドーピング特殊効果
     *   +0時ドーピング特殊効果
     * Reinforcement SpEffect: +2
     *   SpEffect granted when reinforced to +2.
     * Default Value  = -1 */
    int dopingSpEffect_lv2;

    /* +3時ドーピング特殊効果
     *   +0時ドーピング特殊効果
     * Reinforcement SpEffect: +3
     *   SpEffect granted when reinforced to +3.
     * Default Value  = -1 */
    int dopingSpEffect_lv3;

    /* +4時ドーピング特殊効果
     *   +0時ドーピング特殊効果
     * Reinforcement SpEffect: +4
     *   SpEffect granted when reinforced to +4.
     * Default Value  = -1 */
    int dopingSpEffect_lv4;

    /* +5時ドーピング特殊効果
     *   +0時ドーピング特殊効果
     * Reinforcement SpEffect: +5
     *   SpEffect granted when reinforced to +5.
     * Default Value  = -1 */
    int dopingSpEffect_lv5;

    /* +6時ドーピング特殊効果
     *   +0時ドーピング特殊効果
     * Reinforcement SpEffect: +6
     *   SpEffect granted when reinforced to +6.
     * Default Value  = -1 */
    int dopingSpEffect_lv6;

    /* +7時ドーピング特殊効果
     *   +0時ドーピング特殊効果
     * Reinforcement SpEffect: +7
     *   SpEffect granted when reinforced to +7.
     * Default Value  = -1 */
    int dopingSpEffect_lv7;

    /* +8時ドーピング特殊効果
     *   +0時ドーピング特殊効果
     * Reinforcement SpEffect: +8
     *   SpEffect granted when reinforced to +8.
     * Default Value  = -1 */
    int dopingSpEffect_lv8;

    /* +9時ドーピング特殊効果
     *   +0時ドーピング特殊効果
     * Reinforcement SpEffect: +9
     *   SpEffect granted when reinforced to +9.
     * Default Value  = -1 */
    int dopingSpEffect_lv9;

    /* +10時ドーピング特殊効果
     *   +0時ドーピング特殊効果
     * Reinforcement SpEffect: +10
     *   SpEffect granted when reinforced to +10.
     * Default Value  = -1 */
    int dopingSpEffect_lv10;

    /* アーキタイプ別初期パラメータID
     *   アーキタイプ別初期パラメータID
     * Character Init ID
     *   CharaInitParam ID this c0000 summon will use.
     * Default Value  = -1 */
    int npcPlayerInitParamId;

    /* ジェネレートアニメID
     *   ジェネレートアニメID
     * Generate Anim ID
     *   Generate Anime ID
     * Default Value  = -1 */
    int generateAnimId;

    unsigned int unknown_0x5c;

    unsigned int unknown_0x60;

    int unknown_0x64;

    int unknown_0x68;

    int unknown_0x6c;

    int unknown_0x70;

    int unknown_0x74;

    int unknown_0x78;

    int unknown_0x7c;

    int unknown_0x80;

    unsigned int unknown_0x84;

    int unknown_0x88;

    int unknown_0x8c;

    int unknown_0x90;

    int unknown_0x94;

    int unknown_0x98;

    unsigned int unknown_0x9c;
} er_buddy_param_t;
