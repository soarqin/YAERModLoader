#pragma once

typedef struct npc_ai_behavior_probability_param_s {
    /* 右手近接_R1コンボ
     *   右手近接行動
     * Right-hand - R1 Combo
     *   Right-handed proximity behavior */
    short param000;

    /* 右手近接_R2コンボ
     *   右手近接行動
     * Right-hand - R2 Combo
     *   Right-handed proximity behavior */
    short param001;

    /* 右手近接_ダッシュ攻撃
     *   右手近接行動
     * Right-hand - Dash Attack
     *   Right-handed proximity behavior */
    short param002;

    /* 右手近接_前ローリング攻撃
     *   右手近接行動
     * Right-hand - Forward Roll Attack
     *   Right-handed proximity behavior */
    short param003;

    /* 右手近接_左右ローリング攻撃
     *   右手近接行動
     * Right-hand - Side Roll Attack
     *   Right-handed proximity behavior */
    short param004;

    /* 右手近接_後ローリング攻撃
     *   右手近接行動
     * Right-hand - Backward Roll Attack
     *   Right-handed proximity behavior */
    short param005;

    /* 右手近接_バックステップ攻撃
     *   右手近接行動
     * Right-hand - Backstep Attack
     *   Right-handed proximity behavior */
    short param006;

    /* 右手近接_ジャンプ攻撃
     *   右手近接行動
     * Right-hand - Jump Attack
     *   Right-handed proximity behavior */
    short param007;

    /* 右手近接_ダッシュジャンプ攻撃
     *   右手近接行動
     * Right-hand - Dash Jump Attack
     *   Right-handed proximity behavior */
    short param008;

    /* 未使用
     * Unused */
    short param009;

    /* 右手遠距離_R1射撃
     *   右手遠距離武器行動
     * Right-hand - R1 Shoot (Bow)
     *   Right-handed long-range weapon action */
    short param010;

    /* 右手遠距離_R2射撃
     *   右手遠距離武器行動
     * Right-hand - R2 Shoot (Bow)
     *   Right-handed long-range weapon action */
    short param011;

    /* 未使用
     * Unused */
    short param012;

    /* 右手魔法_遠距離魔法_前移動
     *   右手魔法行動
     * Right-hand - Forward Move (Magic)
     *   Right hand magic action */
    short param013;

    /* 右手魔法_遠距離魔法_後ろ移動
     *   右手魔法行動
     * Right-hand - Backward Move (Magic)
     *   Right hand magic action */
    short param014;

    /* 左右移動[CloseDrawBow]
     *   弓構え中に近づかれたインタラプト
     * Right-hand - Side Move (Bow)
     *   Interrupt approached while holding a bow */
    short param015;

    /* 左右ローリング[CloseDrawBow]
     *   弓構え中に近づかれたインタラプト
     * Right-hand - Side Roll (Bow)
     *   Interrupt approached while holding a bow */
    short param016;

    /* 割り込まない[CloseDrawBow]
     *   弓構え中に近づかれたインタラプト
     * Right-hand - No Interrupt (Bow)
     *   Interrupt approached while holding a bow */
    short param017;

    /* 未使用
     * Unused */
    short param018;

    /* 未使用
     * Unused */
    short param019;

    /* 右手魔法_近接魔法_左右
     *   右手魔法行動
     * Right-hand - Side Move (Melee Magic)
     *   Right hand magic action */
    short param020;

    /* 右手魔法_中距離魔法_左右
     *   右手魔法行動
     * Right-hand - Side Move (Medium Magic)
     *   Right hand magic action */
    short param021;

    /* 右手魔法_遠距離魔法_左右
     *   右手魔法行動
     * Right-hand - Side Move (Long Magic)
     *   Right hand magic action */
    short param022;

    /* 右手魔法_HP回復魔法
     *   右手魔法行動
     * Right-hand - HP Recovery (Magic)
     *   Right hand magic action */
    short param023;

    /* 右手魔法_バフ魔法
     *   右手魔法行動
     * Right-hand - Buff (Magic)
     *   Right hand magic action */
    short param024;

    /* 右手魔法_近接魔法_前移動
     *   右手魔法行動
     * Right-hand - Forward Move (Melee Magic)
     *   Right hand magic action */
    short param025;

    /* 右手魔法_近接魔法_後ろ移動
     *   右手魔法行動
     * Right-hand - Backward Move (Melee Magic)
     *   Right hand magic action */
    short param026;

    /* 右手魔法_中距離魔法_前移動
     *   右手魔法行動
     * Right-hand - Forward Move (Medium Magic)
     *   Right hand magic action */
    short param027;

    /* 右手魔法_中距離魔法_後ろ移動
     *   右手魔法行動
     * Right-hand - Backward Move (Medium Magic)
     *   Right hand magic action */
    short param028;

    /* 未使用
     * Unused */
    short param029;

    /* 右手盾_R1攻撃
     *   右手盾行動
     * Right-hand - R1 Attack (Shield)
     *   Right hand shield action */
    short param030;

    /* 右手盾_R2攻撃
     *   右手盾行動
     * Right-hand - R2 Attack (Shield)
     *   Right hand shield action */
    short param031;

    /* 未使用
     * Unused */
    short param032;

    /* 未使用
     * Unused */
    short param033;

    /* 未使用
     * Unused */
    short param034;

    /* バックステップ[SuccessGuard]
     *   ガード成功インタラプト
     * Right-hand - Backstep (Guard Succcess)
     *   Guard success interrupt */
    short param035;

    /* 割り込まない[SuccessGuard]
     *   ガード成功インタラプト
     * Right-hand - No Interrupt (Guard Succcess)
     *   Guard success interrupt */
    short param036;

    /* ガードカウンター攻撃[SuccessGuard]
     *   ガード成功インタラプト
     * Right-hand - Guard Counter (Guard Succcess)
     *   Guard success interrupt */
    short param037;

    /* 未使用
     * Unused */
    short param038;

    /* 未使用
     * Unused */
    short param039;

    /* 左手近接_R1コンボ(両手持ちのみ)
     *   左手近接行動
     * Left-hand - R1 Combo (2H Only)
     *   Left hand proximity behavior */
    short param040;

    /* 左手近接_R2コンボ(両手持ちのみ)
     *   左手近接行動
     * Left-hand - R2 Combo (2H Only)
     *   Left hand proximity behavior */
    short param041;

    /* 左手近接_L1コンボ(片手持ちのみ)
     *   左手近接行動
     * Left-hand - L1 Combo (1H Only)
     *   Left hand proximity behavior */
    short param042;

    /* 左手近接_ダッシュ攻撃(両手持ちのみ)
     *   左手近接行動
     * Left-hand - Dash Attack (2H Only)
     *   Left hand proximity behavior */
    short param043;

    /* 左手近接_前ローリング攻撃(両手持ちのみ)
     *   左手近接行動
     * Left-hand - Forward Roll (2H Only)
     *   Left hand proximity behavior */
    short param044;

    /* 左手近接_左右ローリング攻撃(両手持ちのみ)
     *   左手近接行動
     * Left-hand - Side Roll (2H Only)
     *   Left hand proximity behavior */
    short param045;

    /* 左手近接_後ローリング攻撃(両手持ちのみ)
     *   左手近接行動
     * Left-hand - Backward Roll (2H Only)
     *   Left hand proximity behavior */
    short param046;

    /* 左手近接_バックステップ攻撃(両手持ちのみ)
     *   左手近接行動
     * Left-hand - Backstep Attack (2H Only)
     *   Left hand proximity behavior */
    short param047;

    /* 左手近接_ジャンプ攻撃(両手持ちのみ)
     *   左手近接行動
     * Left-hand - Jump Attack (2H Only)
     *   Left hand proximity behavior */
    short param048;

    /* 左手近接_ダッシュジャンプ攻撃(両手持ちのみ)
     *   左手近接行動
     * Left-hand - Dash Jump Attack (2H Only)
     *   Left hand proximity behavior */
    short param049;

    /* 左手遠距離_R1射撃
     *   左手遠距離武器行動
     * Left-hand - R1 Shoot (Bow)
     *   Left-handed long-range weapon action */
    short param050;

    /* 左手遠距離_R2射撃
     *   左手遠距離武器行動
     * Left-hand - R2 Shoot (Bow)
     *   Left-handed long-range weapon action */
    short param051;

    /* 未使用
     * Unused */
    short param052;

    /* 左手魔法_遠距離魔法_前移動
     *   左手魔法行動
     * Left-hand - Forward Move (Long Magic)
     *   Left hand magic action */
    short param053;

    /* 左手魔法_遠距離魔法_後ろ移動
     *   左手魔法行動
     * Left-hand - Backward Move (Long Magic)
     *   Left hand magic action */
    short param054;

    /* 致命攻撃[SuccessParry]
     *   パリィ成功インタラプト
     * Left-hand - Parry Attack (Parry Success)
     *   Parry Success Interrupt */
    short param055;

    /* 割り込まない[SuccessParry]
     *   パリィ成功インタラプト
     * Left-hand - No Interrupt (Parry Success)
     *   Parry Success Interrupt */
    short param056;

    /* 未使用
     * Unused */
    short param057;

    /* 未使用
     * Unused */
    short param058;

    /* 未使用
     * Unused */
    short param059;

    /* 左手魔法_近接魔法_左右
     *   左手魔法行動
     * Left-hand - Side Move (Melee Magic)
     *   Left hand magic action */
    short param060;

    /* 左手魔法_中距離魔法_左右
     *   左手魔法行動
     * Left-hand - Side Move (Medium Magic)
     *   Left hand magic action */
    short param061;

    /* 左手魔法_遠距離魔法_左右
     *   左手魔法行動
     * Left-hand - Side Move (Long Magic)
     *   Left hand magic action */
    short param062;

    /* 左手魔法_HP回復魔法
     *   左手魔法行動
     * Left-hand - HP Recovery (Magic)
     *   Left hand magic action */
    short param063;

    /* 左手魔法_バフ魔法
     *   左手魔法行動
     * Left-hand - Buff (Magic)
     *   Left hand magic action */
    short param064;

    /* 左手魔法_近接魔法_前移動
     *   左手魔法行動
     * Left-hand - Forward Move (Melee Magic)
     *   Left hand magic action */
    short param065;

    /* 左手魔法_近接魔法_後ろ移動
     *   左手魔法行動
     * Left-hand - Backward Move (Melee Magic)
     *   Left hand magic action */
    short param066;

    /* 左手魔法_中距離魔法_前移動
     *   左手魔法行動
     * Left-hand - Forward Move (Medium Magic)
     *   Left hand magic action */
    short param067;

    /* 左手魔法_中距離魔法_後ろ移動
     *   左手魔法行動
     * Left-hand - Backward Move (Medium Magic)
     *   Left hand magic action */
    short param068;

    /* 未使用
     * Unused */
    short param069;

    /* バックステップ
     *   共通行動
     * Backstep
     *   Common behavior */
    short param070;

    /* 前ローリング
     *   共通行動
     * Forward Roll
     *   Common behavior */
    short param071;

    /* 左右ローリング
     *   共通行動
     * Side Roll
     *   Common behavior */
    short param072;

    /* 後ろローリング
     *   共通行動
     * Backward Roll
     *   Common behavior */
    short param073;

    /* 左右移動
     *   共通行動
     * Side Move
     *   Common behavior */
    short param074;

    /* 後退
     *   共通行動
     * Common - Back
     *   Common behavior */
    short param075;

    /* ダッシュ接近
     *   共通行動
     * Common - Backstep
     *   Common behavior */
    short param076;

    /* 待機
     *   共通行動
     * Common - Standby
     *   Common behavior */
    short param077;

    /* 右手両手持ちに持ち替え
     *   共通行動
     * Common - 2H Right Switch
     *   Common behavior */
    short param078;

    /* 左手両手持ちに持ち替え
     *   共通行動
     * Common - 2H Left Switch
     *   Common behavior */
    short param079;

    /* 片手持ちに持ち替え
     *   共通行動
     * Common - 1H Switch
     *   Common behavior */
    short param080;

    /* 戦闘距離までアプローチ
     *   共通行動
     * Common - Approach Battle Distance
     *   Common behavior */
    short param081;

    /* 未使用
     * Unused */
    short param082;

    /* 未使用
     * Unused */
    short param083;

    /* 未使用
     * Unused */
    short param084;

    /* 致命攻撃[GuardBreak]
     *   ガードブレイクインタラプト
     * Guard Break - Deadly Attack
     *   Guard break interrupt */
    short param085;

    /* ダッシュ攻撃[GuardBreak]
     *   ガードブレイクインタラプト
     * Guard Break - Dash Attack
     *   Guard break interrupt */
    short param086;

    /* 魔法_近接魔法[GuardBreak]
     *   ガードブレイクインタラプト
     * Guard Break - Melee Magic
     *   Guard break interrupt */
    short param087;

    /* 割り込まない[GuardBreak]
     *   ガードブレイクインタラプト
     * Guard Break - No Interrupt
     *   Guard break interrupt */
    short param088;

    /* 未使用
     * Unused */
    short param089;

    /* 盾チク
     *   特殊行動
     * Special - Shield Bash
     *   Special behavior */
    short param090;

    /* 未使用
     * Unused */
    short param091;

    /* 未使用
     * Unused */
    short param092;

    /* 未使用
     * Unused */
    short param093;

    /* 未使用
     * Unused */
    short param094;

    /* ダッシュ攻撃[Estus]
     *   エストを飲んだインタラプト
     * Flask Interrupt - Dash Attack
     *   Interrupt who drank Est */
    short param095;

    /* 投擲アイテム[Estus]
     *   エストを飲んだインタラプト
     * Flask Interrupt - Throwable Item
     *   Interrupt who drank Est */
    short param096;

    /* 割り込まない[Estus]
     *   エストを飲んだインタラプト
     * Flask Interrupt - No Interrupt
     *   Interrupt who drank Est */
    short param097;

    /* 未使用
     * Unused */
    short param098;

    /* 未使用
     * Unused */
    short param099;

    /* パリィ[Parrytime]
     *   パリィタイミングインタラプト
     * Parry Interrupt - Parry
     *   Parry Timing Interrupt */
    short param100;

    /* 前ローリング[Parrytime]
     *   パリィタイミングインタラプト
     * Parry Interrupt - Forward Roll
     *   Parry Timing Interrupt */
    short param101;

    /* 左右ローリング[Parrytime]
     *   パリィタイミングインタラプト
     * Parry Interrupt - Side Roll
     *   Parry Timing Interrupt */
    short param102;

    /* 後ろローリング[Parrytime]
     *   パリィタイミングインタラプト
     * Parry Interrupt - Backward Roll
     *   Parry Timing Interrupt */
    short param103;

    /* バックステップ攻撃[Parrytime]
     *   パリィタイミングインタラプト
     * Parry Interrupt - Backstep Attack
     *   Parry Timing Interrupt */
    short param104;

    /* その場ガード[Parrytime]
     *   パリィタイミングインタラプト
     * Parry Interrupt - Stationary Guard
     *   Parry Timing Interrupt */
    short param105;

    /* 割り込まない[Parrytime]
     *   パリィタイミングインタラプト
     * Parry Interrupt - No Interrupt
     *   Parry Timing Interrupt */
    short param106;

    /* 未使用
     * Unused */
    short param107;

    /* 未使用
     * Unused */
    short param108;

    /* 未使用
     * Unused */
    short param109;

    /* 後ろローリング[Damaged]
     *   被ダメージインタラプト
     * Damaged Interrupt - Backward Roll
     *   Damaged interrupt */
    short param110;

    /* 左右ローリング[Damaged]
     *   被ダメージインタラプト
     * Damaged Interrupt - Side Roll
     *   Damaged interrupt */
    short param111;

    /* 後ろガード移動[Damaged]
     *   被ダメージインタラプト
     * Damaged Interrupt - Backward Guard Move
     *   Damaged interrupt */
    short param112;

    /* 左右ガード移動[Damaged]
     *   被ダメージインタラプト
     * Damaged Interrupt - Side Move
     *   Damaged interrupt */
    short param113;

    /* 割り込まない[Damaged]
     *   被ダメージインタラプト
     * Damaged Interrupt - No Interrupt
     *   Damaged interrupt */
    short param114;

    /* R1コンボ[Damaged]
     *   被ダメージインタラプト
     * Damaged Interrupt - R1 Combo
     *   Damaged interrupt */
    short param115;

    /* 前ローリング[Damaged]
     *   被ダメージインタラプト
     * Damaged Interrupt - Forward Roll
     *   Damaged interrupt */
    short param116;

    /* バックステップ[Damaged]
     *   被ダメージインタラプト
     * Damaged Interrupt - Backstep
     *   Damaged interrupt */
    short param117;

    /* 前ガード移動[Damaged]
     *   被ダメージインタラプト
     * Damaged Interrupt - Forward Guard Move
     *   Damaged interrupt */
    short param118;

    /* 未使用
     * Unused */
    short param119;

    /* 前ローリング[Shoot]
     *   飛び道具発見インタラプト
     * Bullet Interrupt - Forward Roll
     *   Projectile discovery interrupt */
    short param120;

    /* 左右ローリング[Shoot]
     *   飛び道具発見インタラプト
     * Bullet Interrupt - Side Roll
     *   Projectile discovery interrupt */
    short param121;

    /* 前ガード移動[Shoot]
     *   飛び道具発見インタラプト
     * Bullet Interrupt - Forward Guard Move
     *   Projectile discovery interrupt */
    short param122;

    /* 左右ガード移動[Shoot]
     *   飛び道具発見インタラプト
     * Bullet Interrupt - Side Move
     *   Projectile discovery interrupt */
    short param123;

    /* 割り込まない[Shoot]
     *   飛び道具発見インタラプト
     * Bullet Interrupt - No Interrupt
     *   Projectile discovery interrupt */
    short param124;

    /* 後ローリング[Shoot]
     *   飛び道具発見インタラプト
     * Bullet Interrupt - After Roll
     *   Projectile discovery interrupt */
    short param125;

    /* ダッシュ接近[Shoot]
     *   飛び道具発見インタラプト
     * Bullet Interrupt - Dash Approach
     *   Projectile discovery interrupt */
    short param126;

    /* 未使用
     * Unused */
    short param127;

    /* 未使用
     * Unused */
    short param128;

    /* 未使用
     * Unused */
    short param129;

    /* バックステップ[FindAttack]
     *   攻撃発見インタラプト
     * Attack Interrupt - Backstep
     *   Attack detection interrupt */
    short param130;

    /* 前ローリング[FindAttack]
     *   攻撃発見インタラプト
     * Attack Interrupt - Forward Roll
     *   Attack detection interrupt */
    short param131;

    /* 左右ローリング[FindAttack]
     *   攻撃発見インタラプト
     * Attack Interrupt - Side Roll
     *   Attack detection interrupt */
    short param132;

    /* 後ローリング[FindAttack]
     *   攻撃発見インタラプト
     * Attack Interrupt - After Roll
     *   Attack detection interrupt */
    short param133;

    /* 前ガード移動[FindAttack]
     *   攻撃発見インタラプト
     * Attack Interrupt - Forward Guard Move
     *   Attack detection interrupt */
    short param134;

    /* 左右ガード移動[FindAttack]
     *   攻撃発見インタラプト
     * Attack Interrupt - Side Guard Move
     *   Attack detection interrupt */
    short param135;

    /* その場ガード[FindAttack]
     *   攻撃発見インタラプト
     * Attack Interrupt - Stationary Guard
     *   Attack detection interrupt */
    short param136;

    /* 盾チク[FindAttack]
     *   攻撃発見インタラプト
     * Attack Interrupt - Shield Bash
     *   Attack detection interrupt */
    short param137;

    /* 割り込まない[FindAttack]
     *   攻撃発見インタラプト
     * Attack Interrupt - No Interrupt
     *   Attack detection interrupt */
    short param138;

    /* その場回避アーツ[FindAttack]
     *   攻撃発見インタラプト
     * Attack Interrupt - Avoidance Weapon Art
     *   Attack detection interrupt */
    short param139;

    /* R1コンボ時両手持ち確率
     *   その他の確率補正
     * Misc - 2H R1 Combo
     *   Other probability corrections */
    short param140;

    /* R2コンボ時両手持ち確率
     *   その他の確率補正
     * Misc - 2H R2 Combo
     *   Other probability corrections */
    short param141;

    /* プランニング行動時の移動時ガード確率
     *   その他の確率補正
     * Misc - Guard during Move
     *   Other probability corrections */
    short param142;

    /* R1攻撃を二刀攻撃に置き換える確率
     *   その他の確率補正
     * Misc - Dual-wield R1 Attack
     *   Other probability corrections */
    short param143;

    /* 回避を特殊ローリングアーツに置き換える確率
     *   その他の確率補正
     * Misc - Replace Roll with Movement Art
     *   Other probability corrections */
    short param144;

    /* 投擲系アイテムの使用
     *   アイテム使用系
     * Misc - Use Throwable Item
     *   Item usage system */
    short param145;

    /* HP回復アイテムの使用
     *   アイテム使用系
     * Misc - Use HP Recovery Item
     *   Item usage system */
    short param146;

    /* バフアイテムの使用
     *   アイテム使用系
     * Misc - Use Buff Item
     *   Item usage system */
    short param147;

    /* 薬包コンボ攻撃
     *   アイテム使用系
     * Misc - Use Buff Combo Attack
     *   Item usage system */
    short param148;

    /* 未使用
     * Unused */
    short param149;

    /* アーツ_近距離攻撃
     *   アーツ行動系
     * Weapon Art - Short Range Attack
     *   Arts behavior system */
    short param150;

    /* アーツ_中距離攻撃
     *   アーツ行動系
     * Weapon Art - Medium Range Attack
     *   Arts behavior system */
    short param151;

    /* アーツ_遠距離攻撃
     *   アーツ行動系
     * Weapon Art - Ranged Attack
     *   Arts behavior system */
    short param152;

    /* アーツ_回復
     *   アーツ行動系
     * Weapon Art - Recovery
     *   Arts behavior system */
    short param153;

    /* アーツ_バフ
     *   アーツ行動系
     * Weapon Art - Buff
     *   Arts behavior system */
    short param154;

    /* 未使用
     *   アーツ行動系
     * Unused
     *   Arts behavior system */
    short param155;

    /* 未使用
     * Unused */
    short param156;

    /* 未使用
     * Unused */
    short param157;

    /* 未使用
     * Unused */
    short param158;

    /* 未使用
     * Unused */
    short param159;

    /* 未使用
     * Unused */
    short param160;

    /* 未使用
     * Unused */
    short param161;

    /* 未使用
     * Unused */
    short param162;

    /* 未使用
     * Unused */
    short param163;

    /* 未使用
     * Unused */
    short param164;

    /* 未使用
     * Unused */
    short param165;

    /* 未使用
     * Unused */
    short param166;

    /* 未使用
     * Unused */
    short param167;

    /* 未使用
     * Unused */
    short param168;

    /* 未使用
     * Unused */
    short param169;

    /* 未使用
     * Unused */
    short param170;

    /* 未使用
     * Unused */
    short param171;

    /* 未使用
     * Unused */
    short param172;

    /* 未使用
     * Unused */
    short param173;

    /* 未使用
     * Unused */
    short param174;

    /* 未使用
     * Unused */
    short param175;

    /* 未使用
     * Unused */
    short param176;

    /* 未使用
     * Unused */
    short param177;

    /* 未使用
     * Unused */
    short param178;

    /* 未使用
     * Unused */
    short param179;

    /* 未使用
     * Unused */
    short param180;

    /* 未使用
     * Unused */
    short param181;

    /* 未使用
     * Unused */
    short param182;

    /* 未使用
     * Unused */
    short param183;

    /* 未使用
     * Unused */
    short param184;

    /* 未使用
     * Unused */
    short param185;

    /* 未使用
     * Unused */
    short param186;

    /* 未使用
     * Unused */
    short param187;

    /* 未使用
     * Unused */
    short param188;

    /* 未使用
     * Unused */
    short param189;

    /* 未使用
     * Unused */
    short param190;

    /* 未使用
     * Unused */
    short param191;

    /* 未使用
     * Unused */
    short param192;

    /* 未使用
     * Unused */
    short param193;

    /* 未使用
     * Unused */
    short param194;

    /* 未使用
     * Unused */
    short param195;

    /* 未使用
     * Unused */
    short param196;

    /* 未使用
     * Unused */
    short param197;

    /* 未使用
     * Unused */
    short param198;

    /* 未使用
     * Unused */
    short param199;
} npc_ai_behavior_probability_param_t;
