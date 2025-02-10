#pragma once

/* Defines the stats for a given enemy or group of enemies. Does not determine model or location.
 * Stats are often affected greatly by attached SpEffects. */
typedef struct npc_param_s {
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

    /* 行動バリエーションID
     *   行動IDを算出するときに使用するバリエーションID.
     * Behavior Variation ID
     *   Variation ID used when calculating the action ID. */
    int behaviorVariationId;

    /* 毒耐性 補正ルールID
     *   状態異常の発動時、状態異常耐性補正パラメータの設定値を使って、一時的に最大値を変動させる
     * Resist Correction - Poison
     *   When the abnormal condition is activated, the maximum value is temporarily changed by using the set value of the abnormal condition resistance correction parameter.
     * Default Value  = -1 */
    int resistCorrectId_poison;

    /* NPC名ID
     *   NPC名メッセージパラメータ用ID
     * Name ID
     *   NPC Name Message Parameter ID
     * Default Value  = -1 */
    int nameId;

    /* 旋回速度[deg/sec]
     *   1秒間に旋回できる回転速度[度/秒].
     * Turn Velocity
     *   Rotational speed [degrees / second] that can turn in 1 second. */
    float turnVellocity;

    /* 対マップあたりの高さ[m]
     *   対キャラ当たりカプセルの高さ.
     * Capsule Height
     *   The height of the capsule per character. */
    float hitHeight;

    /* 対マップあたりの半径[m]
     *   対キャラ当たりカプセルの半径.
     * Capsule Radius
     *   Radius of capsule per character. */
    float hitRadius;

    /* 重量[kg]
     *   重量.
     * Weight
     *   weight. */
    unsigned int weight;

    /* 表示位置Yオフセット[m]
     *   モデル表示位置のY（高さ）方向のオフセット。あたり位置より浮かせることができる。
     * Display Position - Height Offset
     *   Offset of the model display position in the Y (height) direction. It can be floated from the hit position. */
    float hitYOffset;

    /* ＨＰ
     *   死亡猶予.
     * Base HP
     *   Death grace. */
    unsigned int hp;

    /* ＭＰ
     *   魔法使用量.
     * Base FP
     *   Magic usage. */
    unsigned int mp;

    /* ソウル
     *   死亡時に、キャラクターが取得できるソウル量.
     * Base Runes
     *   The amount of soul that a character can get at the time of death. */
    unsigned int getSoul;

    /* アイテム抽選ID_エネミー用
     *   死亡時に取得するアイテムの抽選ID_エネミー用を指定。どちらか片方のみ設定してください。
     * Enemy Itemlot ID
     *   Specify the lottery ID_for enemies of the item to be acquired at the time of death. Please set only one of them.
     * Default Value  = -1 */
    int itemLotId_enemy;

    /* アイテム抽選ID_マップ用
     *   死亡時に取得するアイテムの抽選ID_マップ用を指定。どちらか片方のみ設定してください。
     * Map Itemlot ID
     *   Specify for the lottery ID_map of the item to be acquired at the time of death. Please set only one of them.
     * Default Value  = -1 */
    int itemLotId_map;

    /* FootIK足首の制限角度_ロール
     *   FootIK足首のロールの制限角度（-1：制限なし）
     * FootIK Ankle Roll Angle Limit
     *   FootIK Ankle roll limit angle (-1 no limit)
     * Default Value  = -1 */
    float maxAnkleRollAngle;

    /* あたりグループと使用ナビメッシュ
     *   他のキャラとのあたり判定を設定（ラグドールあたりにすると他のキャラがラグドールに当たるようになる）
     * Chr Hit Judgment
     *   Set the hit judgment with other characters (If you hit the ragdoll, other characters will hit the ragdoll) */
    unsigned char chrHitGroupAndNavimesh;

    /* NPC顔画像ID
     *   NPC顔画像ID(0:無効値(デフォルト))。「サイン閲覧メニュー」「キックメニュー」などで表示する顔画像のIDを指定する。無効値なら着せ替えモデルを表示する
     * Face Icon ID
     *   NPC face image ID (0 invalid value (default)). Specify the ID of the face image to be displayed in the Sign browsing menu, Kick menu, etc. If it is an invalid value, the dress-up model is displayed. */
    unsigned char faceIconId;

    /* ディアクティベート距離設定[m]
     *   キャラがディアクティベートされる距離（オープン配置キャラのみ有効）
     * Deactivation Distance
     *   Distance at which the character is deactivated (valid only for open placement characters)
     * Default Value  = -1 */
    short deactivateDist;

    /* キャラ出現条件パラ
     *   キャラ出現条件パラメータID
     * Chr Activate Condition Param ID
     *   Character appearance condition parameter ID */
    unsigned int chrActivateConditionParamId;

    /* FootIK見た目の上下制限値
     *   FootIK見た目の上下制限値
     * Foot IK Appearance Height Limit
     *   FootIK Appearance up / down limit */
    float footIkErrorHeightLimit;

    /* 人間性抽選ID
     *   死亡時に取得する人間性の抽選IDを指定
     * Humanity Lot ID
     *   Specify the lottery ID of human nature to be acquired at the time of death
     * Default Value  = -1 */
    int humanityLotId;

    /* 常駐特殊効果0
     *   常駐特殊効果0
     * SpEffect ID [0]
     *   Resident special effect 0
     * Default Value  = -1 */
    int spEffectID0;

    /* 常駐特殊効果1
     *   常駐特殊効果1
     * SpEffect ID [1]
     *   Resident special effect 1
     * Default Value  = -1 */
    int spEffectID1;

    /* 常駐特殊効果2
     *   常駐特殊効果2
     * SpEffect ID [2]
     *   Resident special effect 2
     * Default Value  = -1 */
    int spEffectID2;

    /* 常駐特殊効果3
     *   常駐特殊効果3
     * SpEffect ID [3]
     *   Resident special effect 3
     * Default Value  = -1 */
    int spEffectID3;

    /* 常駐特殊効果4
     *   常駐特殊効果4
     * SpEffect ID [4]
     *   Resident special effect 4
     * Default Value  = -1 */
    int spEffectID4;

    /* 常駐特殊効果5
     *   常駐特殊効果5
     * SpEffect ID [5]
     *   Resident special effect 5
     * Default Value  = -1 */
    int spEffectID5;

    /* 常駐特殊効果6
     *   常駐特殊効果6
     * SpEffect ID [6]
     *   Resident special effect 6
     * Default Value  = -1 */
    int spEffectID6;

    /* 常駐特殊効果7
     *   常駐特殊効果7
     * SpEffect ID [7]
     *   Resident special effect 7
     * Default Value  = -1 */
    int spEffectID7;

    /* 周回ボーナス用特殊効果ＩＤ
     *   周回ボーナス用特殊効果ＩＤ
     * Game Clear - SpEffect ID
     *   Special effect ID for lap bonus
     * Default Value  = -1 */
    int GameClearSpEffectID;

    /* 物理攻撃カット率[％]
     *   ガード時のダメージカット率を各攻撃ごとに設定
     * Guard Absorption % - Physical
     *   Set the damage cut rate when guarding for each attack */
    float physGuardCutRate;

    /* 魔法攻撃カット率[％]
     *   ガード攻撃でない場合は、0を入れる
     * Guard Absorption % - Magic
     *   If it is not a guard attack, enter 0 */
    float magGuardCutRate;

    /* 炎攻撃力カット率[％]
     *   炎攻撃をどれだけカットするか？
     * Guard Absorption % - Fire
     *   How much to cut the fire attack? */
    float fireGuardCutRate;

    /* 電撃攻撃力カット率[％]
     *   電撃攻撃をどれだけカットするか？
     * Guard Absorption % - Lightning
     *   How much to cut the electric shock attack? */
    float thunGuardCutRate;

    /* アニメIDオフセット1
     *   すべてのアニメをこの数だけずらしたIDで再生します。なければ元のアニメIDを参照します。
     * Anim ID Offset [1]
     *   All animations will be played with IDs shifted by this number. If not, the original anime ID is referenced. */
    int animIdOffset;

    /* ロックダミポリ0の注視点
     *   ロックオンダミポリ22Xをロックしている際に指定したダミポリを注視する（-1：無効）
     * Lock Gaze Point - Dummy Poly ID [0]
     *   Gaze at the Damipoli specified when locking the Lock-on Damipoly 22X (-1 Invalid)
     * Default Value  = -1 */
    short lockGazePoint0;

    /* ロックダミポリ1の注視点
     *   ロックオンダミポリ22Xをロックしている際に指定したダミポリを注視する（-1：無効）
     * Lock Gaze Point - Dummy Poly ID [1]
     *   Gaze at the Damipoli specified when locking the Lock-on Damipoly 22X (-1 Invalid)
     * Default Value  = -1 */
    short lockGazePoint1;

    /* ロックダミポリ2の注視点
     *   ロックオンダミポリ22Xをロックしている際に指定したダミポリを注視する（-1：無効）
     * Lock Gaze Point - Dummy Poly ID [2]
     *   Gaze at the Damipoli specified when locking the Lock-on Damipoly 22X (-1 Invalid)
     * Default Value  = -1 */
    short lockGazePoint2;

    /* ロックダミポリ3の注視点
     *   ロックオンダミポリ22Xをロックしている際に指定したダミポリを注視する（-1：無効）
     * Lock Gaze Point - Dummy Poly ID [3]
     *   Gaze at the Damipoli specified when locking the Lock-on Damipoly 22X (-1 Invalid)
     * Default Value  = -1 */
    short lockGazePoint3;

    /* ロックダミポリ4の注視点
     *   ロックオンダミポリ22Xをロックしている際に指定したダミポリを注視する（-1：無効）
     * Lock Gaze Point - Dummy Poly ID [4]
     *   Gaze at the Damipoli specified when locking the Lock-on Damipoly 22X (-1 Invalid)
     * Default Value  = -1 */
    short lockGazePoint4;

    /* ロックダミポリ5の注視点
     *   ロックオンダミポリ22Xをロックしている際に指定したダミポリを注視する（-1：無効）
     * Lock Gaze Point - Dummy Poly ID [5]
     *   Gaze at the Damipoli specified when locking the Lock-on Damipoly 22X (-1 Invalid)
     * Default Value  = -1 */
    short lockGazePoint5;

    /* ネットワークワープ判定距離[m/秒]
     *   ネットワークの同期で、補完移動でなくワープさせる距離。スピードの速い人（exドラゴン)は長めにしてあげる必要がある。
     * Network Warp Display
     *   Distance to warp instead of complementary movement in network synchronization. Faster people (ex dragons) need to be longer. */
    float networkWarpDist;

    /* R1
     *   行動パラメータツールからIDを登録し、行動を指定する.
     * Debug Action - R1
     *   Register the ID from the action parameter tool and specify the action.
     * Default Value  = -1 */
    int dbgBehaviorR1;

    /* L1
     *   行動パラメータツールからIDを登録し、行動を指定する.
     * Debug Action - L1
     *   Register the ID from the action parameter tool and specify the action.
     * Default Value  = -1 */
    int dbgBehaviorL1;

    /* R2
     *   行動パラメータツールからIDを登録し、行動を指定する.
     * Debug Action - R2
     *   Register the ID from the action parameter tool and specify the action.
     * Default Value  = -1 */
    int dbgBehaviorR2;

    /* L2
     *   行動パラメータツールからIDを登録し、行動を指定する.
     * Debug Action - L2
     *   Register the ID from the action parameter tool and specify the action.
     * Default Value  = -1 */
    int dbgBehaviorL2;

    /* □
     *   行動パラメータツールからIDを登録し、行動を指定する.
     * Debug Action - Square
     *   Register the ID from the action parameter tool and specify the action.
     * Default Value  = -1 */
    int dbgBehaviorRL;

    /* ○
     *   行動パラメータツールからIDを登録し、行動を指定する.
     * Debug Action - Circle
     *   Register the ID from the action parameter tool and specify the action.
     * Default Value  = -1 */
    int dbgBehaviorRR;

    /* ×
     *   行動パラメータツールからIDを登録し、行動を指定する.
     * Debug Action - Cross
     *   Register the ID from the action parameter tool and specify the action.
     * Default Value  = -1 */
    int dbgBehaviorRD;

    /* △
     *   行動パラメータツールからIDを登録し、行動を指定する.
     * Debug Action - Triangle
     *   Register the ID from the action parameter tool and specify the action.
     * Default Value  = -1 */
    int dbgBehaviorRU;

    /* ←
     *   行動パラメータツールからIDを登録し、行動を指定する.
     * Debug Action - Left D-Pad
     *   Register the ID from the action parameter tool and specify the action.
     * Default Value  = -1 */
    int dbgBehaviorLL;

    /* →
     *   行動パラメータツールからIDを登録し、行動を指定する.
     * Debug Action - Right D-Pad
     *   Register the ID from the action parameter tool and specify the action.
     * Default Value  = -1 */
    int dbgBehaviorLR;

    /* ↓
     *   行動パラメータツールからIDを登録し、行動を指定する.
     * Debug Action - Down D-Pad
     *   Register the ID from the action parameter tool and specify the action.
     * Default Value  = -1 */
    int dbgBehaviorLD;

    /* ↑
     *   行動パラメータツールからIDを登録し、行動を指定する.
     * Debug Action - Up D-Pad
     *   Register the ID from the action parameter tool and specify the action.
     * Default Value  = -1 */
    int dbgBehaviorLU;

    /* アニメIDオフセット2
     *   すべてのアニメをこの数だけずらしたIDで再生します。なければアニメIDオフセット1のアニメIDを参照します。
     * Anim ID Offset [2]
     *   All animations will be played with IDs shifted by this number. If not, the animation ID of the animation ID offset 1 is referred to. */
    int animIdOffset2;

    /* ダメージグループ1ダメージ倍率
     *   部位1に対するダメージ処理に適応する倍率
     * Damage % Part [1]
     *   Magnification that adapts to damage processing for part 1
     * Default Value  = 1 */
    float partsDamageRate1;

    /* ダメージグループ2ダメージ倍率
     *   部位2に対するダメージ処理に適応する倍率
     * Damage % Part [2]
     *   Magnification that adapts to damage processing for part 2
     * Default Value  = 1 */
    float partsDamageRate2;

    /* ダメージグループ3ダメージ倍率
     *   部位3に対するダメージ処理に適応する倍率
     * Damage % Part [3]
     *   Magnification that adapts to damage processing for part 3
     * Default Value  = 1 */
    float partsDamageRate3;

    /* ダメージグループ4ダメージ倍率
     *   部位4に対するダメージ処理に適応する倍率
     * Damage % Part [4]
     *   Magnification that adapts to damage processing for part 4
     * Default Value  = 1 */
    float partsDamageRate4;

    /* ダメージグループ5ダメージ倍率
     *   部位5に対するダメージ処理に適応する倍率
     * Damage % Part [5]
     *   Magnification that adapts to damage processing for part 5
     * Default Value  = 1 */
    float partsDamageRate5;

    /* ダメージグループ6ダメージ倍率
     *   部位6に対するダメージ処理に適応する倍率
     * Damage % Part [6]
     *   Magnification to adapt to damage processing for part 6
     * Default Value  = 1 */
    float partsDamageRate6;

    /* ダメージグループ7ダメージ倍率
     *   部位7に対するダメージ処理に適応する倍率
     * Damage % Part [7]
     *   Magnification that adapts to damage processing for part 7
     * Default Value  = 1 */
    float partsDamageRate7;

    /* ダメージグループ8ダメージ倍率
     *   部位8に対するダメージ処理に適応する倍率
     * Damage % Part [8]
     *   Magnification that adapts to damage processing for part 8
     * Default Value  = 1 */
    float partsDamageRate8;

    /* 弱点部位ダメージ倍率
     *   弱点部位に対するダメージ処理に適応する倍率
     * Damage % Weak Part
     *   Magnification that adapts to damage processing for weak points
     * Default Value  = 1 */
    float weakPartsDamageRate;

    /* SA回復時間補正値
     *   スーパーアーマー回復時間用の補正値
     * Poise Recovery Correction
     *   Correction value for super armor recovery time */
    float superArmorRecoverCorrection;

    /* SAブレイク時ノックバック距離
     *   SAブレイクの時だけに使えるノックバック距離
     * Poise Knockback Distance
     *   Knockback distance that can be used only at the time of SA break */
    float superArmorBrakeKnockbackDist;

    /* スタミナ
     *   スタミナ総量.
     * Stamina
     *   Total amount of stamina. */
    unsigned short stamina;

    /* スタミナ回復基本速度[point/s]
     *   スタミナ回復基本速度[point/s]
     * Stamina Recovery
     *   Stamina recovery basic speed [point / s] */
    unsigned short staminaRecoverBaseVel;

    /* 物理防御力
     *   物理攻撃に対するダメージ減少基本値.
     * Defence - Physical
     *   Damage reduction base value for physical attacks. */
    unsigned short def_phys;

    /* 斬撃防御力[％]
     *   攻撃属性を見て、斬撃属性のときは、防御力を減少させる.
     * Defence - Slash
     *   Look at the attack attribute, and if it is a slash attribute, reduce the defense power. */
    short def_slash;

    /* 打撃防御力[％]
     *   攻撃属性を見て、打撃属性のときは、防御力を減少させる.
     * Defence - Strike
     *   Look at the attack attribute, and if it is a hit attribute, reduce the defense power. */
    short def_blow;

    /* 刺突防御力[％]
     *   攻撃属性を見て、刺突属性のときは、防御力を減少させる.
     * Defence - Thrust
     *   Look at the attack attribute, and if it is a piercing attribute, reduce the defense power. */
    short def_thrust;

    /* 魔法防御力
     *   魔法攻撃に対するダメージ減少基本値.
     * Defence - Magic
     *   Damage reduction base value for magic attacks. */
    unsigned short def_mag;

    /* 炎防御力
     *   炎攻撃に対するダメージ減少基本値.
     * Defence - Fire
     *   Damage reduction base value against fire attack. */
    unsigned short def_fire;

    /* 電撃防御力
     *   電撃攻撃に対するダメージ減少基本値.
     * Defence - Lightning
     *   Damage reduction base value against electric shock attack. */
    unsigned short def_thunder;

    /* はじき防御力
     *   敵の攻撃のはじき判定に使用。//ガード以外の通常攻撃でもはじけるようにするためのものです.//硬い表皮の敵は、何もしなくてもはじかれることがある…みたいな感じ通常の敵なら関係ないです.
     * Weapon Repel Power
     *   Used to determine the repelling of enemy attacks. // It is intended to be repelled by normal attacks other than guards. // Enemies with a hard skin can be repelled without doing anything ... It doesn't matter if it is a normal enemy. */
    unsigned short defFlickPower;

    /* 毒耐性
     *   毒状態異常へのかかりにくさ
     * Resist - Poison
     *   Difficulty in getting poisonous */
    unsigned short resist_poison;

    /* 疫病耐性
     *   疫病状態異常へのかかりにくさ
     * Resist - Scarlet Rot
     *   Difficulty in getting sick */
    unsigned short resist_desease;

    /* 出血耐性
     *   出血状態異常へのかかりにくさ
     * Resist - Hemorrhage
     *   Difficulty in getting bleeding abnormalities */
    unsigned short resist_blood;

    /* 呪耐性
     *   呪状態異常へのかかりにくさ
     * Resist - Blight
     *   Difficulty in dealing with abnormal curse conditions */
    unsigned short resist_curse;

    /* 徘徊ゴースト時差し替えモデルID
     *   徘徊ゴースト化したときの差し替えモデル、テクスチャID
     * Ghost Model ID
     *   Replacement model when wandering ghost, texture ID
     * Default Value  = -1 */
    short ghostModelId;

    /* 通常時差し替えリソースID
     *   通常時のリソースID差し替え（むやみに使わないこと）
     * Override Resource Chr ID
     *   Replace resource ID during normal operation (do not use it unnecessarily)
     * Default Value  = -1 */
    short normalChangeResouceId;

    /* ガード範囲[deg]
     *   武器のガード時の防御発生範囲角度.保留中
     * Guard Angle
     *   Defense range angle when guarding weapons. Pending */
    short guardAngle;

    /* 斬撃攻撃カット率[％]
     *   攻撃タイプを見て、斬撃属性のダメージを何％カットするか？を指定
     * Guard Absorption % - Slash
     *   Looking at the attack type, what percentage of the damage of the slashing attribute is cut? Specify */
    short slashGuardCutRate;

    /* 打撃攻撃カット率[％]
     *   攻撃タイプを見て、打撃属性のダメージを何％カットするか？を指定
     * Guard Absorption % - Strike
     *   Looking at the attack type, what percentage of the damage of the hit attribute is cut? Specify */
    short blowGuardCutRate;

    /* 刺突攻撃カット率[％]
     *   攻撃タイプを見て、刺突属性のダメージを何％カットするか？を指定
     * Guard Absorption % - Thrust
     *   Looking at the attack type, what percentage of the damage of the piercing attribute is cut? Specify */
    short thrustGuardCutRate;

    /* ロックダミポリ6の注視点
     *   ロックオンダミポリ22Xをロックしている際に指定したダミポリを注視する（-1：無効）
     * Lock Gaze Point - Dummy Poly ID [6]
     *   Gaze at the Damipoli specified when locking the Lock-on Damipoly 22X (-1 Invalid)
     * Default Value  = -1 */
    short lockGazePoint6;

    /* 通常時差し替えテクスチャキャラID
     *   通常時差し替えテクスチャキャラID（むやみに使わないこと）
     * Override Texture Chr ID
     *   Normal replacement texture character ID (do not use it unnecessarily)
     * Default Value  = -1 */
    short normalChangeTexChrId;

    /* ドロップアイテムの表示形式
     *   アイテムドロップ時の表示方法(死体発光orアイテム表示)
     * Drop Type
     *   Display method when dropping an item (corpse emission or item display) */
    unsigned short dropType;

    /* ノックバックカット率[％]
     *   ノックバックダメージを受けたときの減少値／具体的には、攻撃側のノックバック初速度をカットする
     * Received Knockback %
     *   Decrease value when receiving knockback damage / Specifically, cut the initial knockback speed of the attacking side */
    unsigned char knockbackRate;

    /* ノックバックパラメータID
     *   ノックバック時に使用するパラメータIDを設定
     * Knockback Param ID
     *   Set the parameter ID used for knockback */
    unsigned char knockbackParamId;

    /* 落下ダメージ軽減補正[％]
     *   落下ダメージ軽減補正[％]
     * Fall Damage Reduction %
     *   Fall damage reduction correction [%] */
    unsigned char fallDamageDump;

    /* スタミナ攻撃カット率[％]
     *   ガード成功時に、敵のスタミナ攻撃に対する防御力
     * Guard Absorption % - Stamina
     *   Defense against enemy stamina attacks when guarding successfully */
    unsigned char staminaGuardDef;

    /* 睡眠耐性
     *   睡眠状態異常へのかかりにくさ
     * Resist - Sleep
     *   Difficulty in getting sleep abnormalities */
    unsigned short resist_sleep;

    /* 発狂耐性
     *   発狂状態異常へのかかりにくさ
     * Resist - Madness
     *   Difficulty in getting mad */
    unsigned short resist_madness;

    /* 睡眠攻撃カット率[％]
     *   睡眠に対する攻撃力（特殊効果パラメータに設定）をどれだけカットするか
     * Guard Resist - Sleep
     *   How much to cut the attack power against sleep (set as a special effect parameter) */
    char sleepGuardResist;

    /* 発狂攻撃カット率[％]
     *   発狂に対する攻撃力（特殊効果パラメータに設定）をどれだけカットするか
     * Guard Resist - Madness
     *   How much to cut the attack power against madness (set as a special effect parameter) */
    char madnessGuardResist;

    /* ロックダミポリ7の注視点
     *   ロックオンダミポリ22Xをロックしている際に指定したダミポリを注視する（-1：無効）
     * Lock Gaze Point - Dummy Poly ID [7]
     *   Gaze at the Damipoli specified when locking the Lock-on Damipoly 22X (-1 Invalid)
     * Default Value  = -1 */
    short lockGazePoint7;

    /* MP回復基本速度[％/s]
     *   MP回復基本速度[％/s]
     * FP Recovery
     *   MP recovery basic speed [% / s] */
    unsigned char mpRecoverBaseVel;

    /* はじき時ダメージ減衰率[%]
     *   攻撃をはじいた時にダメージを減衰する値を設定
     * Weapon Repel Absorption
     *   Set a value to attenuate damage when repelling an attack */
    unsigned char flickDamageCutRate;

    /* デフォルトLODパラムID
     *   デフォルトLODパラムID(-1：なし)
     * Default LOD Param ID
     *   Default LOD Param ID (-1 None)
     * Default Value  = -1 */
    char defaultLodParamId;

    /* 描画タイプ
     *   描画タイプ
     * Draw Type
     *   Drawing type */
    char drawType;

    /* NPCタイプ
     *   NPCの種類.ザコ敵/ボス敵が区別されていればOK
     * NPC Type
     *   NPC type. OK if Zako enemies / boss enemies are distinguished */
    unsigned char npcType;

    /* チームタイプ
     *   NPCの攻撃が当たる/当たらない、狙う/狙わない設定
     * Team Type
     *   NPC attack hit / not hit, aim / not aim setting */
    unsigned char teamType;

    /* 移動タイプ
     *   移動方法。これにより制御が変更される.
     * Move Type
     *   Moving method. This changes the control. */
    unsigned char moveType;

    /* ロック距離
     *   ロックオンできる距離[m]
     * Lock Distance
     *   Lock-on distance [m] */
    unsigned char lockDist;

    /* 弱点防御材質1【SE】
     *   弱点部位ダメージを受けた時に鳴らすSEを判定する。1
     * Weak Point - SE Material
     *   Determines the SE that sounds when the weak point is damaged. 1 */
    unsigned short materialSe_Weak1;

    /* 弱点防御材質1【SFX】
     *   弱点部位ダメージを受けた時に発生するSFXを判定する。1
     * Weak Point - SFX Material
     *   Determines the SFX that occurs when the weak point is damaged. 1 */
    unsigned short materialSfx_Weak1;

    /* 部位ダメージ適用攻撃
     *   部位ダメージを適用する攻撃タイプを設定する
     * Parts Damage - Attack Type
     *   Determines if weak parts (such as the head) will be affected by all attacks or just arrow attacks.\nHeadshot animation will be used for weak part attacks if it exists. */
    unsigned char partsDamageType;

    /* 誓約
     *   誓約タイプ
     * Vow Type
     *   Pledge type */
    unsigned char vowType;

    /* ガードレベル
     *   ガードしたとき、敵の攻撃をどのガードモーションで受けるか？を決める
     * Guard Level
     *   When guarding, which guard motion will the enemy attack? Decide */
    char guardLevel;

    /* 燃焼SFXタイプ
     *   燃焼時のSFXタイプ
     * Burn SFX Type
     *   SFX type at the time of combustion */
    unsigned char burnSfxType;

    /* 毒耐性カット率[％]
     *   毒にする攻撃力（特殊効果パラメータに設定）をどれだけカットするか
     * Guard Resist - Poison
     *   How much to cut the attack power to poison (set to the special effect parameter) */
    char poisonGuardResist;

    /* 疫病攻撃カット率[％]
     *   疫病にする攻撃力（特殊効果パラメータに設定）をどれだけカットするか
     * Guard Resist - Scarlet Rot
     *   How much to cut the attack power (set as a special effect parameter) to make it a plague */
    char diseaseGuardResist;

    /* 出血攻撃カット率[％]
     *   出血にする攻撃力（特殊効果パラメータに設定）をどれだけカットするか
     * Guard Resist - Hemorrhage
     *   How much to cut the attack power (set as a special effect parameter) to make bleeding */
    char bloodGuardResist;

    /* 呪攻撃カット率[％]
     *   呪にする攻撃力（特殊効果パラメータに設定）をどれだけカットするか
     * Guard Resist - Blight
     *   How much to cut the attack power (set as a special effect parameter) to make a curse */
    char curseGuardResist;

    /* パリィ攻撃力
     *   パリィ攻撃力。パリィする側が使用
     * Parry Attack Power
     *   Parry attack power. Used by the parrying side */
    unsigned char parryAttack;

    /* パリィ防御力
     *   パリィ防御力。パリィされる側が使用。
     * Parry Defence Power
     *   Parry defense. Used by the parried side. */
    unsigned char parryDefence;

    /* SFXサイズ
     *   SFXサイズ
     * SFX Size
     *   SFX size */
    unsigned char sfxSize;

    /* カメラ押し出し領域半径[m]
     *   カメラ押し出し領域半径[m]
     * Push Out Camera Region Radius
     *   Camera extrusion area radius [m]
     * Default Value  = 12 */
    unsigned char pushOutCamRegionRadius;

    /* ヒットストップするか
     *   ヒットストップ処理を行うかどうかの設定
     * Hit Stop Type
     *   Setting whether to perform hit stop processing */
    unsigned char hitStopType;

    /* はしご上終端オフセット[1/10m]
     *   はしご終端判定用オフセット上側
     * Ladder End Check Offset Top
     *   Upper side of the ladder end judgment offset
     * Default Value  = 15 */
    unsigned char ladderEndChkOffsetTop;

    /* はしご下終端オフセット[1/10m]
     *   はしご終端判定用オフセット下側
     * Ladder End Check Offset Bottom
     *   Lower side of ladder end judgment offset
     * Default Value  = 8 */
    unsigned char ladderEndChkOffsetLow;

    /* カメラヒットあたりラグドール
     *   敵のラグドールにカメラがあたるか。(プレイヤにも当たるときのみ有効)
     * Use Ragdoll Camera Hit
     *   Does the camera hit the enemy ragdoll? (Valid only when hitting the player) */
    unsigned char useRagdollCamHit:1;

    /* クロスリジッドヒットを無効
     *   クロスリジッドが自分に当たらないようにしたければ○
     * Disable Cloth Rigid Hit
     *   If you want to prevent the cross rigid from hitting you  */
    unsigned char disableClothRigidHit:1;

    /* 前後の起伏加算を使用するか
     *   前後の起伏加算を使用するか
     * Use Undulating Add Anim
     *   Whether to use front and back undulation addition */
    unsigned char useUndulationAddAnimFB:1;

    /* 特攻Aか
     *   特攻Aか。特攻Aダメージ倍率が計算に含まれるようになります
     * Enemy Type - Type A
     *   Special attack A? Special attack A damage multiplier will be included in the calculation */
    unsigned char isWeakA:1;

    /* 霊体か
     *   相手の攻撃がすり抜けるようになります。武器パラの「対霊武器」が○の武器で攻撃された時のみ攻撃が当たります。徘徊ゴーストと混同しないように注意
     * Is Ghost
     *   The opponent's attack will be able to slip through. The attack hits only when the anti-spirit weapon of the weapon para is attacked with the weapon of . Be careful not to confuse it with a wandering ghost */
    unsigned char isGhost:1;

    /* ダメージ0のときにダメージモーションなしか
     *   ダメージ0のときにダメージモーションを再生しないか。
     * Is No Damage Motion
     *   Do you not play the damage motion when the damage is 0? */
    unsigned char isNoDamageMotion:1;

    /* 起伏に角度をあわせるか
     *   キャラの前後回転を地面の起伏に合わせるか。飛行キャラの場合は使用不可
     * Is Undulating
     *   Do you match the back and forth rotation of the character with the undulations of the ground? Cannot be used for flying characters */
    unsigned char isUnduration:1;

    /* 徘徊ゴーストになるか
     *   プレイヤーがクライアントのときに徘徊ゴーストになるか
     * Is Wandering Ghost
     *   Will it be a wandering ghost when the player is a client? */
    unsigned char isChangeWanderGhost:1;

    /* モデル表示マスク0
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [0]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask0:1;

    /* モデル表示マスク1
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [1]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask1:1;

    /* モデル表示マスク2
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [2]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask2:1;

    /* モデル表示マスク3
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [3]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask3:1;

    /* モデル表示マスク4
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [4]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask4:1;

    /* モデル表示マスク5
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [5]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask5:1;

    /* モデル表示マスク6
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [6]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask6:1;

    /* モデル表示マスク7
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [7]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask7:1;

    /* モデル表示マスク8
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [8]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask8:1;

    /* モデル表示マスク9
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [9]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask9:1;

    /* モデル表示マスク10
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [10]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask10:1;

    /* モデル表示マスク11
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [11]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask11:1;

    /* モデル表示マスク12
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [12]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask12:1;

    /* モデル表示マスク13
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [13]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask13:1;

    /* モデル表示マスク14
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [14]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask14:1;

    /* モデル表示マスク15
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [15]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask15:1;

    /* 首振り有効にするか
     *   パラムウィーバで設定された首振りを有効にするか。
     * Is Enable Neck Turn
     *   Do you want to enable the swing set in Param Weaver? */
    unsigned char isEnableNeckTurn:1;

    /* リスポン禁止か
     *   リスポンを禁止するか
     * Disable Respawn upon Rest
     *   Do you ban respawn? */
    unsigned char disableRespawn:1;

    /* 移動アニメを待つか
     *   移動アニメをアニメが終わるまで再生するか。（カゲロウ龍の様に。）
     * Play Movement Anim until Over
     *   Do you want to play the moving animation until the animation is over? (Like a mayfly dragon.) */
    unsigned char isMoveAnimWait:1;

    /* 群集用処理軽減するか
     *   群集時の処理負荷軽減を行なうか。赤子用（できればファランクスも）
     * Reduce Processing Load during Crowds
     *   Do you want to reduce the processing load during crowds? For babies (preferably phalanx) */
    unsigned char isCrowd:1;

    /* 特攻Bか
     *   特攻Bか。特攻Bダメージ倍率が計算に含まれるようになります
     * Enemy Type - Type B
     *   Special attack B? Special attack B damage multiplier will be included in the calculation */
    unsigned char isWeakB:1;

    /* 特攻Cか
     *   特攻Cか。特攻Cダメージ倍率が計算に含まれるようになります
     * Enemy Type - Type C
     *   Special attack C? Special attack C damage multiplier will be included in the calculation */
    unsigned char isWeakC:1;

    /* 特攻Dか
     *   特攻Dか。特攻Dダメージ倍率が計算に含まれるようになります
     * Enemy Type - Type D
     *   Special attack D? Special attack D damage multiplier will be included in the calculation */
    unsigned char isWeakD:1;

    /* 常時特殊旋回するか
     *   常時特殊旋回を実行するか(旋回移動先にナビメッシュがない場合も特殊旋回を継続実行します)
     * Always Use Special Turn
     *   Always execute a special turn (even if there is no navigation mesh at the turn destination, the special turn is continuously executed) */
    unsigned char doesAlwaysUseSpecialTurn:1;

    /* 騎乗特攻か
     *   （騎乗中であれば）騎乗特攻の対象になるか
     * Is Ride Attack Target
     *   Will you be the target of a riding special attack (if you are riding)? */
    unsigned char isRideAtkTarget:1;

    /* 段差越え表示補間を使用するか
     *   段差越え表示補間を使用するか
     * Enable Step Display Interpolation
     *   Whether to use step-over display interpolation */
    unsigned char isEnableStepDispInterpolate:1;

    /* ステルス攻撃対象か
     *   ステルス攻撃対象か
     * Is Stealth Attack Target
     *   Is it a stealth attack target?
     * Default Value  = 1 */
    unsigned char isStealthTarget:1;

    /* 初期死亡しない
     *   初期死亡をしない場合にTRUE、殺してセーブしても死体再現されません。
     * Disable Init Dead
     *   If you do not make an initial death, TRUE, even if you kill and save it, the corpse will not be reproduced. */
    unsigned char disableInitializeDead:1;

    /* ヒット時振動するか
     *   ヒット時振動をする場合TRUE。亡者など、普通のヒットストップと変えたいときにつかう。
     * Is Hit Rumble
     *   TRUE if it vibrates when hit. Use when you want to change from a normal hit stop, such as a dead person. */
    unsigned char isHitRumble:1;

    /* スムーズ旋回するか
     *   ルート移動でのノード間旋回時、補間を行うか否か
     * Use Smooth Turning
     *   Whether to perform interpolation when turning between nodes in route movement
     * Default Value  = 1 */
    unsigned char isSmoothTurn:1;

    /* 特攻Eか
     *   特攻Eか。特攻Eダメージ倍率が計算に含まれるようになります
     * Enemy Type - Type E
     *   Special attack E? Special attack E damage multiplier will be included in the calculation */
    unsigned char isWeakE:1;

    /* 特攻Fか
     *   特攻Fか。特攻Fダメージ倍率が計算に含まれるようになります
     * Enemy Type - Type F
     *   Special attack F? Special attack F damage multiplier will be included in the calculation */
    unsigned char isWeakF:1;

    /* モデル表示マスク16
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [16]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask16:1;

    /* モデル表示マスク17
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [17]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask17:1;

    /* モデル表示マスク18
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [18]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask18:1;

    /* モデル表示マスク19
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [19]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask19:1;

    /* モデル表示マスク20
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [20]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask20:1;

    /* モデル表示マスク21
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [21]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask21:1;

    /* モデル表示マスク22
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [22]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask22:1;

    /* モデル表示マスク23
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [23]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask23:1;

    /* モデル表示マスク24
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [24]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask24:1;

    /* モデル表示マスク25
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [25]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask25:1;

    /* モデル表示マスク26
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [26]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask26:1;

    /* モデル表示マスク27
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [27]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask27:1;

    /* モデル表示マスク28
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [28]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask28:1;

    /* モデル表示マスク29
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [29]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask29:1;

    /* モデル表示マスク30
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [30]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask30:1;

    /* モデル表示マスク31
     *   表示マスクに対応するモデルを表示します。
     * Model Display Mask [31]
     *   Displays the model corresponding to the display mask. */
    unsigned char modelDispMask31:1;

    /* ドロップアイテム半径補正
     *   通常のItem検索判定の円柱半径に、補正として足し合わせる半径(敵ドロップアイテムに適用。大きなキャラなどで使用する)
     * Item Pickup Radius
     *   Radius to be added as a correction to the cylinder radius of normal Item search judgment (applicable to enemy drop items. Used for large characters etc.) */
    float itemSearchRadius;

    /* 対キャラあたりの高さ[m]
     *   対キャラ当たりカプセルの高さ.
     * Chr Capsule Height
     *   The height of the capsule per character. */
    float chrHitHeight;

    /* 対キャラあたりの半径[m]
     *   対キャラ当たりカプセルの半径.
     * Chr Capsule Radius
     *   Radius of capsule per character. */
    float chrHitRadius;

    /* 特殊旋回のタイプ
     *   特殊旋回のタイプ
     * Special Turn Type
     *   Special turning type */
    unsigned char specialTurnType;

    /* ソウルはボス入手か
     *   ソウルはボス入手か
     * Is Boss Soul Drop
     *   Do you get a boss in soul? */
    unsigned char isSoulGetByBoss:1;

    /* オブジェクト扱いの弾丸オーナか
     *   弾丸のオーナーとなった場合、弾丸に関連するダメージ計算などをオブジェのものを適用するようにするフラグ。勢力別ダメージ補正で使用。
     * Is Bullet Owner - By Object
     *   If you become the owner of a bullet, a flag that applies the object's damage calculation related to the bullet. Used for damage correction by power. */
    unsigned char isBulletOwner_byObject:1;

    /* ロウヒットFootIKを使うか？
     *   ロウヒット用のFootIkフィルターを使用するか
     * Use FootIK Filter for Low Hit
     *   Whether to use the FootIk filter for low hits */
    unsigned char isUseLowHitFootIk:1;

    /* PvPのダメージ補正制御を適用するか
     *   ダメージ計算時に「プレイヤー」としてダメージ計算するのかを決める。無効の場合は「敵」扱い。
     * Use PvP Damage Modifiers
     *   Decide whether to calculate damage as a player when calculating damage. If it is invalid, it is treated as an enemy. */
    unsigned char isCalculatePvPDamage:1;

    /* ホスト世界でアクティブ時のみアクティベート可
     *   ホスト世界でアクティブ時のみアクティベート可
     * Is Synced with Host World
     *   Can only be activated when active in the host world */
    unsigned char isHostSyncChr:1;

    /* 弱点アニメをスキップするか
     *   弱点ダメージアニメ再生をスキップするかどうか。アニメを再生しないだけで「部位ダメージ率」「防御材質」は弱点として扱われます。
     * Skip Weak Damage Anim
     *   Weakness damage Whether to skip animation playback. Part damage rate and defense material are treated as weak points just by not playing the animation. */
    unsigned char isSkipWeakDamageAnim:1;

    /* 騎乗された時、乗る側のカプセルあたりを有効にするか
     *   このパラメータが○のキャラに騎乗する際、騎乗中、キャラのアタリが残ったままになる 
     * Keep Capsule on Ride
     *   When riding on a character with this parameter , the character's Atari remains while riding. */
    unsigned char isKeepHitOnRide:1;

    /* 特殊あたりキャラか
     *   特殊あたりに当たるキャラか
     * Is Special Collider
     *   Is it a special character? */
    unsigned char isSpCollide:1;

    /* 闇防御力
     *   闇攻撃に対するダメージ減少基本値.
     * Defence - Holy
     *   Damage reduction base value for dark attacks. */
    unsigned short def_dark;

    /* 脅威度
     *   脅威度。0ならPCが見つかっても「見つかりそうFE」を表示しない
     * Threat Level
     *   Threat level. If it is 0, even if the PC is found, FE that seems to be found is not displayed.
     * Default Value  = 1 */
    unsigned int threatLv;

    /* 特殊旋回の使用距離の閾値[m]
     *   ターゲットとの距離が設定された閾値以上の場合に、特殊旋回を行う
     * Special Turn Distance Threshold
     *   Make a special turn when the distance to the target is greater than or equal to the set threshold
     * Default Value  = 4 */
    float specialTurnDistanceThreshold;

    /* フットエフェクト識別子
     *   自動フットエフェクトで使用するSFX識別子。（XYYZZZのZZZ）
     * Automatic Foot Effect - SFX ID
     *   The SFX identifier used in the automatic foot effect. (ZZZ of XYYZZZ)
     * Default Value  = -1 */
    int autoFootEffectSfxId;

    /* 防御材質1【SE】
     *   ダメージを受けたときに鳴らすＳＥを判定する。1.見た目で設定してＯＫ.
     * Damaged - Material SE [1]
     *   Determine the SE that sounds when damaged. 1. It is OK to set it by appearance. */
    unsigned short materialSe1;

    /* 防御材質1【SFX】
     *   ダメージを受けたときに発生するSFXを判定する。1.見た目で設定してＯＫ.
     * Damaged - Material SFX [1]
     *   Determine the SFX that occurs when you take damage. 1. It is OK to set it by appearance. */
    unsigned short materialSfx1;

    /* 弱点防御材質2【SE】
     *   弱点部位ダメージを受けた時に鳴らすSEを判定する。2
     * Weak Point - Material SE [2]
     *   Determines the SE that sounds when the weak point is damaged. 2 */
    unsigned short materialSe_Weak2;

    /* 弱点防御材質2【SFX】
     *   弱点部位ダメージを受けた時に発生するSFXを判定する。2
     * Weak Point - Material SFX [2]
     *   Determines the SFX that occurs when the weak point is damaged. 2 */
    unsigned short materialSfx_Weak2;

    /* 防御材質2【SE】
     *   ダメージを受けたときに鳴らすＳＥを判定する。2.見た目で設定してＯＫ.
     * Damaged - Material SE [2]
     *   Determine the SE that sounds when damaged. 2. It is OK to set it by appearance. */
    unsigned short materialSe2;

    /* 防御材質2【SFX】
     *   ダメージを受けたときに発生するSFXを判定する。2.見た目で設定してＯＫ.
     * Damaged - Material SFX [2]
     *   Determine the SFX that occurs when you take damage. 2. It is OK to set it by appearance. */
    unsigned short materialSfx2;

    /* 常駐特殊効果8
     *   常駐特殊効果8
     * SpEffect ID [8]
     *   Resident special effect 8
     * Default Value  = -1 */
    int spEffectID8;

    /* 常駐特殊効果9
     *   常駐特殊効果9
     * SpEffect ID [9]
     *   Resident special effect 9
     * Default Value  = -1 */
    int spEffectID9;

    /* 常駐特殊効果10
     *   常駐特殊効果10
     * SpEffect ID [10]
     *   Resident special effect 10
     * Default Value  = -1 */
    int spEffectID10;

    /* 常駐特殊効果11
     *   常駐特殊効果11
     * SpEffect ID [11]
     *   Resident special effects 11
     * Default Value  = -1 */
    int spEffectID11;

    /* 常駐特殊効果12
     *   常駐特殊効果12
     * SpEffect ID [12]
     *   Resident special effect 12
     * Default Value  = -1 */
    int spEffectID12;

    /* 常駐特殊効果13
     *   常駐特殊効果13
     * SpEffect ID [13]
     *   Resident special effect 13
     * Default Value  = -1 */
    int spEffectID13;

    /* 常駐特殊効果14
     *   常駐特殊効果14
     * SpEffect ID [14]
     *   Resident special effect 14
     * Default Value  = -1 */
    int spEffectID14;

    /* 常駐特殊効果15
     *   常駐特殊効果15
     * SpEffect ID [15]
     *   Resident special effects 15
     * Default Value  = -1 */
    int spEffectID15;

    /* フットデカール識別子1
     *   フットエフェクト発生時に貼られるデカール。床材質も考慮される
     * Automatic Foot Effect - Decal Base ID [1]
     *   Decal to be attached when a foot effect occurs. Floor material is also taken into consideration
     * Default Value  = -1 */
    int autoFootEffectDecalBaseId1;

    /* 強靭度
     *   強靭度の基本値
     * Toughness
     *   Basic value of toughness */
    unsigned int toughness;

    /* 強靭度 回復時間補正値
     *   強靭度の回復時間用の補正値
     * Toughness Correction
     *   Correction value for toughness recovery time */
    float toughnessRecoverCorrection;

    /* 無属性ダメージ倍率
     *   無属性ダメージ倍率。ダメージ計算結果にこの値をかけた値が最終ダメージ値になります。
     * Absorption % - Standard
     *   Non-attribute damage multiplier. The final damage value is the value obtained by multiplying the damage calculation result by this value.
     * Default Value  = 1 */
    float neutralDamageCutRate;

    /* 斬撃ダメージ倍率
     *   斬撃ダメージ倍率。ダメージ計算結果にこの値をかけた値が最終ダメージ値になります。
     * Absorption % - Slash
     *   Slash damage multiplier. The final damage value is the value obtained by multiplying the damage calculation result by this value.
     * Default Value  = 1 */
    float slashDamageCutRate;

    /* 打撃ダメージ倍率
     *   打撃ダメージ倍率。ダメージ計算結果にこの値をかけた値が最終ダメージ値になります。
     * Absorption % - Strike
     *   Batter damage multiplier. The final damage value is the value obtained by multiplying the damage calculation result by this value.
     * Default Value  = 1 */
    float blowDamageCutRate;

    /* 刺突ダメージ倍率
     *   刺突ダメージ倍率。ダメージ計算結果にこの値をかけた値が最終ダメージ値になります。
     * Absorption % - Thrust
     *   Puncture damage ratio. The final damage value is the value obtained by multiplying the damage calculation result by this value.
     * Default Value  = 1 */
    float thrustDamageCutRate;

    /* 魔法ダメージ倍率
     *   魔法ダメージ倍率。ダメージ計算結果にこの値をかけた値が最終ダメージ値になります。
     * Absorption % - Magic
     *   Magic damage multiplier. The final damage value is the value obtained by multiplying the damage calculation result by this value.
     * Default Value  = 1 */
    float magicDamageCutRate;

    /* 火炎ダメージ倍率
     *   火炎ダメージ倍率。ダメージ計算結果にこの値をかけた値が最終ダメージ値になります。
     * Absorption % - Fire
     *   Flame damage multiplier. The final damage value is the value obtained by multiplying the damage calculation result by this value.
     * Default Value  = 1 */
    float fireDamageCutRate;

    /* 電撃ダメージ倍率
     *   電撃ダメージ倍率。ダメージ計算結果にこの値をかけた値が最終ダメージ値になります。
     * Absorption % - Lightning
     *   Electric shock damage ratio. The final damage value is the value obtained by multiplying the damage calculation result by this value.
     * Default Value  = 1 */
    float thunderDamageCutRate;

    /* 闇ダメージ倍率
     *   闇ダメージ倍率。ダメージ計算結果にこの値をかけた値が最終ダメージ値になります。
     * Absorption % - Holy
     *   Dark damage multiplier. The final damage value is the value obtained by multiplying the damage calculation result by this value.
     * Default Value  = 1 */
    float darkDamageCutRate;

    /* 闇攻撃力カット率[％]
     *   闇攻撃をどれだけカットするか？
     * Guard Absorption % - Holy
     *   How much to cut the dark attack? */
    float darkGuardCutRate;

    /* クロス更新優先度オフセット[m]
     *   クロス更新優先度オフセット[m]
     * Cloth Update Offset
     *   Cross update priority offset [m] */
    char clothUpdateOffset;

    /* NPCプレイヤー時重量設定
     *   NPCプレイヤーのときに適用される装備重量タイプ
     * NPC Player Weight Type
     *   Equipment weight type applied for NPC players */
    unsigned char npcPlayerWeightType;

    /* 通常時差し替えモデルID
     *   通常時の差し替えモデル、テクスチャID
     * Replacement Change - Model ID
     *   Normal replacement model, texture ID
     * Default Value  = -1 */
    short normalChangeModelId;

    /* 通常時差し替えアニメキャラID
     *   対象のアニメを指定IDのAnibndで差し替える
     * Replacement Change - Anim Chr ID
     *   Replace the target animation with the specified ID Anibnd
     * Default Value  = -1 */
    short normalChangeAnimChrId;

    /* ペイントレンダーターゲットサイズ[pix]
     *   ペイントレンダーターゲットサイズ[pix]
     * Paint Render Target Size
     *   Paint render target size [pix]
     * Default Value  = 256 */
    unsigned short paintRenderTargetSize;

    /* 疫病耐性 補正ルールID
     *   状態異常の発動時、状態異常耐性補正パラメータの設定値を使って、一時的に最大値を変動させる
     * Resist Correction - Scarlet Rot
     *   When the abnormal condition is activated, the maximum value is temporarily changed by using the set value of the abnormal condition resistance correction parameter.
     * Default Value  = -1 */
    int resistCorrectId_disease;

    /* 適用シェーダーID
     *   適用するファントムパラメータ.xlsmのID
     * Phantom Shader ID
     *   ID of the phantom parameter .xlsm to apply
     * Default Value  = -1 */
    int phantomShaderId;

    /* マルチプレイ補正パラメータID
     *   マルチプレイ補正パラメータID
     * Multiplayer Correction Param ID
     *   Multiplayer correction parameter ID
     * Default Value  = -1 */
    int multiPlayCorrectionParamId;

    /* FootIK足首の制限角度_ピッチ
     *   FootIK足首のピッチの制限角度（-1：制限なし）。HATでFoot End L Sを設定していない場合はこの角度がロールと共通で使用される。
     * FootIK Ankle Pitch Limit Angle
     *   FootIK Ankle pitch limit angle (-1 no limit). If you have not set Foot End L S in HAT, this angle is used in common with rolls.
     * Default Value  = -1 */
    float maxAnklePitchAngle;

    /* 冷気耐性
     *   冷気状態異常へのかかりにくさ
     * Resist - Frostbite
     *   Difficulty in getting cold air condition abnormal */
    unsigned short resist_freeze;

    /* 冷気攻撃カット率[％]
     *   冷気に対する攻撃力（特殊効果パラメータに設定）をどれだけカットするか
     * Guard Resist - Frostbite
     *   How much to cut the attack power against cold air (set as a special effect parameter) */
    char freezeGuardResist;

    /* HP Burn Damage %
     *   Adjusts the amount of HP Burn suffered from Destined Death/Black Flame sources. */
    unsigned char hpBurnDamageRate;

    /* ロックカメラパラメータID
     *   ロックオンされた際にカメラに適用させるロックカメラパラメータのID。最も優先度が高い。-1なら未使用
     * Lock Camera Param ID
     *   The ID of the lock camera parameter applied to the camera when locked on. Highest priority. Unused if -1
     * Default Value  = -1 */
    int lockCameraParamId;

    /* 常駐特殊効果16
     *   常駐特殊効果16
     * SpEffect ID [16]
     *   Resident special effects 16
     * Default Value  = -1 */
    int spEffectID16;

    /* 常駐特殊効果17
     *   常駐特殊効果17
     * SpEffect ID [17]
     *   Resident special effects 17
     * Default Value  = -1 */
    int spEffectID17;

    /* 常駐特殊効果18
     *   常駐特殊効果18
     * SpEffect ID [18]
     *   Resident special effects 18
     * Default Value  = -1 */
    int spEffectID18;

    /* 常駐特殊効果19
     *   常駐特殊効果19
     * SpEffect ID [19]
     *   Resident special effects 19
     * Default Value  = -1 */
    int spEffectID19;

    /* 常駐特殊効果20
     *   常駐特殊効果20
     * SpEffect ID [20]
     *   Resident special effect 20
     * Default Value  = -1 */
    int spEffectID20;

    /* 常駐特殊効果21
     *   常駐特殊効果21
     * SpEffect ID [21]
     *   Resident special effect 21
     * Default Value  = -1 */
    int spEffectID21;

    /* 常駐特殊効果22
     *   常駐特殊効果22
     * SpEffect ID [22]
     *   Resident special effect 22
     * Default Value  = -1 */
    int spEffectID22;

    /* 常駐特殊効果23
     *   常駐特殊効果23
     * SpEffect ID [23]
     *   Resident special effect 23
     * Default Value  = -1 */
    int spEffectID23;

    /* 常駐特殊効果24
     *   常駐特殊効果24
     * SpEffect ID [24]
     *   Resident special effect 24
     * Default Value  = -1 */
    int spEffectID24;

    /* 常駐特殊効果25
     *   常駐特殊効果25
     * SpEffect ID [25]
     *   Resident special effects 25
     * Default Value  = -1 */
    int spEffectID25;

    /* 常駐特殊効果26
     *   常駐特殊効果26
     * SpEffect ID [26]
     *   Resident special effect 26
     * Default Value  = -1 */
    int spEffectID26;

    /* 常駐特殊効果27
     *   常駐特殊効果27
     * SpEffect ID [27]
     *   Resident special effect 27
     * Default Value  = -1 */
    int spEffectID27;

    /* 常駐特殊効果28
     *   常駐特殊効果28
     * SpEffect ID [28]
     *   Resident special effects 28
     * Default Value  = -1 */
    int spEffectID28;

    /* 常駐特殊効果29
     *   常駐特殊効果29
     * SpEffect ID [29]
     *   Resident special effect 29
     * Default Value  = -1 */
    int spEffectID29;

    /* 常駐特殊効果30
     *   常駐特殊効果30
     * SpEffect ID [30]
     *   Resident special effect 30
     * Default Value  = -1 */
    int spEffectID30;

    /* 常駐特殊効果31
     *   常駐特殊効果31
     * SpEffect ID [31]
     *   Resident special effects 31
     * Default Value  = -1 */
    int spEffectID31;

    /* ロック不可領域の中心角[deg]
     *   敵の真下に円錐状のロックオン不可領域を作る。円錐の広さの角度。TAEから一時的に変更可能
     * Disable Lock-on Angle
     *   Create a conical lock-on non-lockable area beneath the enemy. The angle of the size of the cone. Can be changed temporarily from TAE */
    float disableLockOnAng;

    /* クロスOffLODレベル
     *   クロスの処理を切るLODレベルを設定する
     * LOD Level to Disable Cloth Processing
     *   Set the LOD level to turn off cross processing
     * Default Value  = -1 */
    char clothOffLodLevel;

    /* 起伏にあわせるのにFootIK結果を用いるか
     *   キャラを地面の起伏に合わせる際に、FootIK結果を用いるか。飛行キャラの場合は使用不可
     * Use Foot IK for Undulating Character
     *   Do you use the FootIK result to match your character to the undulations of the ground? Cannot be used for flying characters */
    unsigned char isUseFootIKNormalByUnduration:1;

    /* 初期死亡時にカプセル接地するか
     *   初期死亡時にカプセル接地するか
     * Attach to Ground upon Death
     *   Whether to ground the capsule at the time of initial death */
    unsigned char attachHitInitializeDead:1;

    /* グループ報酬判定から外すか
     *   グループ報酬：「全員死亡」の判定において、このパラメータが○のキャラは判定から除外する 
     * Exclude Group Reward Check
     *   Group reward In the judgment of all dead, characters with this parameter  are excluded from the judgment. */
    unsigned char excludeGroupRewardCheck:1;

    /* ロックダミポリ(エネミー用)212が有効か
     *   ロックダミポリ(エネミー用)212が有効か
     * Enable AI Lock Dummy Poly [212]
     *   Is Rock Damipoli (for Enemy) 212 Effective?
     * Default Value  = 1 */
    unsigned char enableAILockDmyPoly_212:1;

    /* ロックダミポリ(エネミー用)213が有効か
     *   ロックダミポリ(エネミー用)213が有効か
     * Enable AI Lock Dummy Poly [213]
     *   Is Rock Damipoli (for Enemy) 213 Effective?
     * Default Value  = 1 */
    unsigned char enableAILockDmyPoly_213:1;

    /* ロックダミポリ(エネミー用)214が有効か
     *   ロックダミポリ(エネミー用)214が有効か
     * Enable AI Lock Dummy Poly [214]
     *   Is Rock Damipoli (for Enemy) 214 Effective?
     * Default Value  = 1 */
    unsigned char enableAILockDmyPoly_214:1;

    /* オープン_XB1から除外
     *   オープン_XB1から除外
     * Disable Open Activation - XB1
     *   Excluded from open_XB1 */
    unsigned char disableActivateOpen_xb1:1;

    /* レガシー_XB1から除外
     *   レガシー_XB1から除外
     * Disable Legacy Activation - XB1
     *   Excluded from Legacy_XB1 */
    unsigned char disableActivateLegacy_xb1:1;

    /* HPエスト瓶／MPエスト瓶回復数パラメータID
     *   キャラクター死亡時に値と同じ エスト使用回数回復パラメータ.xlsm　のデータIDを取得してエスト瓶を回復させる。 -1なら未使用
     * Flask Recovery Param ID
     *   When the character dies, the data ID of the est usage count recovery parameter .xlsm, which is the same as the value, is acquired and the est bottle is recovered. Unused if -1
     * Default Value  = -1 */
    short estusFlaskRecoveryParamId;

    /* ロール名テキストID
     *   召喚時のロール名を指定する。-1:対象霊体のデフォルトロール名を使用。0:表示なし。1以上:テキストＩＤとして利用。
     * Role Name ID
     *   Specify the role name at the time of summoning. -1 Use the default role name of the target spirit body. 0 No display. 1 or more Used as a text ID.
     * Default Value  = -1 */
    int roleNameId;

    /* HP&MPエスト瓶回復 抽選確率
     *   敵を倒した際のHP/MPエストの回復確率。10000 を分母とし、分子をNPCパラから取得する。 
     * HP/FP Flask Recovery Chance
     *   HP / MP est recovery probability when defeating an enemy. The numerator is obtained from the NPC para with 10000 as the denominator. */
    unsigned short estusFlaskLotPoint;

    /* HPエスト瓶回復 抽選確率
     *   敵を倒した際のMPエストの回復確率。10000 を分母とし、分子をNPCパラから取得する。 
     * HP Flask Recovery Chance
     *   Recovery probability of MP Est when defeating an enemy. The numerator is obtained from the NPC para with 10000 as the denominator. */
    unsigned short hpEstusFlaskLotPoint;

    /* MPエスト瓶回復 抽選確率
     *   敵を倒した際のMPエストの回復確率。10000 を分母とし、分子をNPCパラから取得する。 
     * FP Flask Recovery Chance
     *   Recovery probability of MP Est when defeating an enemy. The numerator is obtained from the NPC para with 10000 as the denominator. */
    unsigned short mpEstusFlaskLotPoint;

    /* HP&MPエスト瓶回復 落選時 加算抽選確率
     *   HP/MPエスト回復抽選に外れた際の次回確率上昇値。分子の加算値。
     * Missed HP/FP Flask Recovery - Bonus Chance
     *   Next time probability increase value when you miss the HP / MP est recovery lottery. Addition value of numerator. */
    unsigned short estusFlaskRecovery_failedLotPointAdd;

    /* HPエスト瓶回復 落選時 加算抽選確率
     *   HPエスト回復抽選に外れた際の次回確率上昇値。分子の加算値。
     * Missed HP Flask Recovery - Bonus Chance
     *   The next probability increase value when you miss the HP Est Recovery Lottery. Addition value of numerator. */
    unsigned short hpEstusFlaskRecovery_failedLotPointAdd;

    /* MPエスト瓶回復 落選時 加算抽選確率
     *   MPエスト回復抽選に外れた際の次回確率上昇値。分子の加算値。
     * Missed FP Flask Recovery - Bonus Chance
     *   The next probability increase value when the MP est recovery lottery is missed. Addition value of numerator. */
    unsigned short mpEstusFlaskRecovery_failedLotPointAdd;

    /* ファントムシェーダを使用して徘徊ゴーストになるか
     *   ゲスト側でだけ指定されたIDのファントムシェーダIDを指定して幻影化
     * Wandering Ghost Phantom ID
     *   Phantom shader with ID specified only on the guest side Specify the phantom shader ID and make it an illusion
     * Default Value  = -1 */
    int WanderGhostPhantomId;

    /* 聴覚用 頭のサイズ[m]
     *   聴覚判定時のカプセルオフセットの代わりに、設定するオフセットサイズ。0以上が設定されている場合のみ、この値をオフセットとして使用。
     * Listen Head Size
     *   The offset size to be set instead of the capsule offset at the time of hearing judgment. Use this value as an offset only if it is set to 0 or higher.
     * Default Value  = -1 */
    float hearingHeadSize;

    /* サウンドバンクID
     *   サウンドバンクIDが指定できます -1：キャラID(リソース名)のバンクを使用
     * Sound Bank ID
     *   Sound bank ID can be specified -1 Use the bank of character ID (resource name)
     * Default Value  = -1 */
    short SoundBankId;

    /* 起伏にあわせる最大前後角度
     *   起伏に前後の角度を合わせる場合の上限角度。全長が長い場合には低めに設定したほうがよいです。
     * Forward Undulation Limit
     *   The upper limit angle when adjusting the front-back angle to the undulation. If the total length is long, it is better to set it lower. */
    unsigned char forwardUndulationLimit;

    /* 起伏にあわせる最大左右角度
     *   起伏に左右の角度を合わせる場合の上限角度。全長が長い場合には低めに設定したほうがよいです。
     * Side Undulation Limit
     *   Upper limit angle when adjusting the left and right angles to the undulations. If the total length is long, it is better to set it lower. */
    unsigned char sideUndulationLimit;

    /* 小隊ディアクティブ移動の移動速度[m/s]
     *   小隊ディアクティブ移動の移動速度[m/s]
     * Platoon - Deactivation Movement Speed
     *   Platoon Deactive Movement Speed [m / s] */
    float deactiveMoveSpeed;

    /* 小隊ディアクティブ移動に切り替わる距離[m]
     *   小隊ディアクティブ移動に切り替わる距離[m]
     * Platoon - Deactivation Distance
     *   Distance to switch to platoon deactive movement [m] */
    float deactiveMoveDist;

    /* サウンド音源有効距離[m]
     *   キャラ音源が有効なプレイヤーからの距離です。-1：全距離で有効
     * Sound Source Validity - Player Distance
     *   The distance from the player for which the character sound source is valid. -1 Effective at all distances
     * Default Value  = 48 */
    float enableSoundObjDist;

    /* 起伏にあわせる補正ゲイン値
     *   起伏に角度を合わせる際の速度を設定する
     * Undulation Angle Correction
     *   Set the speed when adjusting the angle to the undulations
     * Default Value  = 0.1 */
    float undulationCorrectGain;

    /* フットデカール識別子2
     *   フットエフェクト発生時に貼られるデカール。床材質も考慮される
     * Automatic Foot Effect - Decal Base ID [2]
     *   Decal to be attached when a foot effect occurs. Floor material is also taken into consideration
     * Default Value  = -1 */
    short autoFootEffectDecalBaseId2;

    /* フットデカール識別子3
     *   フットエフェクト発生時に貼られるデカール。床材質も考慮される
     * Automatic Foot Effect - Decal Base ID [3]
     *   Decal to be attached when a foot effect occurs. Floor material is also taken into consideration
     * Default Value  = -1 */
    short autoFootEffectDecalBaseId3;

    /* リターゲット参照キャラID
     *   モーションのリターゲット先の指定の際に参照するキャラID
     * Motion Re-target Reference Chr ID
     *   Character ID to be referred to when specifying the motion retarget destination
     * Default Value  = -1 */
    short RetargetReferenceChrId;

    /* SFXリソースバンクID
     *   SFXリソースバンクIDが指定できます -1：キャラID(リソース名)のバンクを使用
     * SFX Resource Bank ID
     *   SFX resource bank ID can be specified -1 Use the bank of character ID (resource name)
     * Default Value  = -1 */
    short SfxResBankId;

    /* 更新とアクティベイトの優先度
     *   アクティベート・更新レベルの決定に使用する。大きいほどプレイヤーから離れていても更新レベルが下がらない。
     * Activation Update Priority
     *   Used to determine the activation / renewal level. The larger it is, the lower the update level will be even if you are far from the player.
     * Default Value  = 1 */
    float updateActivatePriolity;

    /* 死亡前ナビメッシュフラグ
     *   キャラクターが生存してる間、触れているナビメッシュに値のフラグを設定する。移動に追従しない。
     * Chr Navmesh Flag - Alive
     *   Flag the value of the touching Nav Mesh while the character is alive. Does not follow the movement. */
    unsigned char chrNavimeshFlag_Alive;

    /* 死亡後ナビメッシュフラグ
     *   キャラクターが死亡してる間、触れているナビメッシュに値のフラグを設定する。移動に追従しない。
     * Chr Navmesh Flag - Dead
     *   Flag the value on the touching Nav Mesh while the character is dying. Does not follow the movement. */
    unsigned char chrNavimeshFlag_Dead;

    /* Is Considered Undead
     *   Appears to determine whether an NPC is affected by anti-Undead effects. */
    unsigned char isConsideredUndead;

    /* 車輪制御タイプ
     *   車輪制御タイプ
     * Wheel Rotation Type
     *   Wheel control type */
    unsigned char wheelRotType;

    /* 車輪の半径
     *   車輪の半径を指定[m]
     * Wheel Rotation Radius
     *   Specify the radius of the wheel [m] */
    float wheelRotRadius;

    /* リターゲット移動量倍率
     *   リターゲット時の移動量の倍率
     * Retarget Movement Rate
     *   Magnification of movement amount at the time of retargeting
     * Default Value  = 1 */
    float retargetMoveRate;

    /* はしごワープ位置オフセット
     *   指定された値でダミポリZ軸方向にオフセットします。正数・負数どちらも指定可能です。
     * Ladder - Warp Z Offset
     *   Offsets along the Damipoly Z-axis at the specified value. Both positive and negative numbers can be specified. */
    float ladderWarpOffset;

    /* 読み込みアセットID
     *   キャラロード時に関連して読み込むアセットID（キャラが動的に生成するなど用。
     * Load Asset ID
     *   Asset ID to be read in connection with character loading (for dynamic generation of characters, etc.).
     * Default Value  = -1 */
    int loadAssetId;

    /* オーバーラップカメラ対象ロックダミポリID
     *   オーバーラップカメラを有効にするダミポリID(220～227)を設定します。-1の場合は無効になります。
     * Overlap Camera - Dummy Poly ID
     *   Set the Damipoly ID (220-227) to enable the overlap camera. If it is -1, it will be invalid.
     * Default Value  = -1 */
    int overlapCameraDmypolyId;

    /* 常駐マテリアル拡張パラID0
     *   常駐マテリアル拡張パラID0
     * Material Ex Param ID [0]
     *   Resident Material Expansion Para ID0
     * Default Value  = -1 */
    int residentMaterialExParamId00;

    /* 常駐マテリアル拡張パラID1
     *   常駐マテリアル拡張パラID1
     * Material Ex Param ID [1]
     *   Resident Material Expansion Para ID1
     * Default Value  = -1 */
    int residentMaterialExParamId01;

    /* 常駐マテリアル拡張パラID2
     *   常駐マテリアル拡張パラID2
     * Material Ex Param ID [2]
     *   Resident Material Expansion Para ID2
     * Default Value  = -1 */
    int residentMaterialExParamId02;

    /* 常駐マテリアル拡張パラID3
     *   常駐マテリアル拡張パラID3
     * Material Ex Param ID [3]
     *   Resident Material Expansion Para ID3
     * Default Value  = -1 */
    int residentMaterialExParamId03;

    /* 常駐マテリアル拡張パラID4
     *   常駐マテリアル拡張パラID4
     * Material Ex Param ID [4]
     *   Resident Material Expansion Para ID4
     * Default Value  = -1 */
    int residentMaterialExParamId04;

    /* ネムリ時アイテム抽選ID_エネミー用
     *   ネムリ収集時に取得するアイテムの抽選ID_エネミー用を指定。どちらか片方のみ設定してください。
     * Sleep Collector - Enemy Item Lot
     *   Specify the lottery ID_for enemies of the item to be acquired when collecting Nemuri. Please set only one of them.
     * Default Value  = -1 */
    int sleepCollectorItemLotId_enemy;

    /* ネムリ時アイテム抽選ID_マップ用
     *   ネムリ収集時に取得するアイテムの抽選ID_マップ用を指定。どちらか片方のみ設定してください。
     * Sleep Collector - Map Item Lot
     *   Specify for the lottery ID_map of the item to be acquired when collecting Nemuri. Please set only one of them.
     * Default Value  = -1 */
    int sleepCollectorItemLotId_map;

    /* FootIK見た目の高さ補正ONゲイン値
     *   FootIK見た目の高さ補正ONゲイン値
     * Foot IK - Error On Gain
     *   FootIK Appearance height correction ON gain value
     * Default Value  = 0.1 */
    float footIkErrorOnGain;

    /* FootIK見た目の高さ補正OFFゲイン値
     *   FootIK見た目の高さ補正OFFゲイン値
     * Foot IK - Error Off Gain
     *   FootIK Appearance height correction OFF gain value
     * Default Value  = 0.4 */
    float footIkErrorOffGain;

    /* 追加サウンドバンクID
     *   追加のサウンドバンクIDが指定できます -1 or 0：追加なし(SEQ16135)
     * Sound Add Bank ID
     *   You can specify an additional sound bank ID -1 or 0 No addition (SEQ 16135)
     * Default Value  = -1 */
    short SoundAddBankId;

    /* 防御材質バリエーション値
     *   防御材質と組み合わせて状態異常、ダメージSFX,SEのバリエーション分けに使用する値です。SEQ16473
     * Material Variation Value
     *   It is a value used in combination with the defense material to classify abnormal conditions, damage SFX, and SE. SEQ16473 */
    unsigned char materialVariationValue;

    /* 弱点防御材質バリエーション値
     *   弱点防御材質と組み合わせて状態異常、ダメージSFX,SEのバリエーション分けに使用する値です。SEQ16473
     * Weak Point - Material Variation Value
     *   It is a value used for variation of abnormal condition, damage SFX, SE in combination with weak point defense material. SEQ16473 */
    unsigned char materialVariationValue_Weak;

    /* SA耐久力
     *   スーパーアーマー耐久値
     * Poise
     *   Super armor durability value */
    float superArmorDurability;

    /* SA回復速度補正値
     *   SA基礎回復量に乗算してSA回復速度を補正する
     * Poise Recovery
     *   Correct the SA recovery speed by multiplying the SA basic recovery amount
     * Default Value  = 1 */
    float saRecoveryRate;

    /* SA攻撃カット率[％]
     *   ガード成功時のSＡダメージのカット率
     * Guard Absorption % - Poise Damage
     *   Cut rate of SA damage when guard is successful */
    float saGuardCutRate;

    /* 出血耐性 補正ルールID
     *   状態異常の発動時、状態異常耐性補正パラメータの設定値を使って、一時的に最大値を変動させる
     * Resist Correction - Hemorrhage
     *   When the abnormal condition is activated, the maximum value is temporarily changed by using the setting value of the abnormal condition resistance correction parameter.
     * Default Value  = -1 */
    int resistCorrectId_blood;

    /* 呪耐性 補正ルールID
     *   状態異常の発動時、状態異常耐性補正パラメータの設定値を使って、一時的に最大値を変動させる
     * Resist Correction - Blight
     *   When the abnormal condition is activated, the maximum value is temporarily changed by using the set value of the abnormal condition resistance correction parameter.
     * Default Value  = -1 */
    int resistCorrectId_curse;

    /* 冷気耐性 補正ルールID
     *   状態異常の発動時、状態異常耐性補正パラメータの設定値を使って、一時的に最大値を変動させる
     * Resist Correction - Frostbite
     *   When the abnormal condition is activated, the maximum value is temporarily changed by using the setting value of the abnormal condition resistance correction parameter.
     * Default Value  = -1 */
    int resistCorrectId_freeze;

    /* 睡眠耐性 補正ルールID
     *   状態異常の発動時、状態異常耐性補正パラメータの設定値を使って、一時的に最大値を変動させる
     * Resist Correction - Sleep
     *   When the abnormal condition is activated, the maximum value is temporarily changed by using the set value of the abnormal condition resistance correction parameter.
     * Default Value  = -1 */
    int resistCorrectId_sleep;

    /* 発狂耐性 補正ルールID
     *   状態異常の発動時、状態異常耐性補正パラメータの設定値を使って、一時的に最大値を変動させる
     * Resist Correction - Madness
     *   When the abnormal condition is activated, the maximum value is temporarily changed by using the set value of the abnormal condition resistance correction parameter.
     * Default Value  = -1 */
    int resistCorrectId_madness;

    /* キャラ死亡チュートリアル判定フラグID
     *   初めてキャラ倒した時のチュートリアル用のイベントフラグID。キャラ死亡時にフラグON。
     * Chr Dead Tutorial Flag ID
     *   Event flag ID for the tutorial when the character is defeated for the first time. Flag ON when the character dies. */
    unsigned int chrDeadTutorialFlagId;

    /* 段差越え表示補間時間
     *   段差越え表示補間時間
     * Step Display Interpolation Time
     *   Step crossing display interpolation time
     * Default Value  = 0.5 */
    float stepDispInterpolateTime;

    /* 段差越え表示起動判定値
     *   段差越え表示起動判定値
     * Step Display Interpolation Trigger Value
     *   Step crossing display activation judgment value
     * Default Value  = 0.6 */
    float stepDispInterpolateTriggerValue;

    /* ロックスコア補正値
     *   ロックスコア補正値
     * Lock Score Offset
     *   Lock score correction value */
    float lockScoreOffset;

    /* DLC Completion SpEffect ID
     *   Game Clear SpEffect applied after completing the DLC. Only applies once, does not ramp up per NG+ cycle. */
    int dlcGameClearSpEffectID;

    /* パディング12 */
    char pad12[4];
} npc_param_t;
