#pragma once

typedef struct er_hit_mtrl_param_s {
    /* 音半径倍率
     *   1倍のときは普通。0にすると音半径が0になる（SEとSFXは無関係のゲーム的なパラメータ）
     * AI Volume Rate
     *   Normal when 1x. When set to 0, the radius of sound becomes 0 (SE and SFX are unrelated game-like parameters).
     * Default Value  = 1 */
    float aiVolumeRate;

    /* ヒットマテリアルを踏んだ時にかかる特殊効果0
     *   キャラがヒットマテリアルを踏んだ時に、設定した特殊効果0が発揮される
     * On Hit [1] - SpEffect ID
     *   When the character steps on the hit material, the set special effect 0 is exhibited.
     * Default Value  = -1 */
    int spEffectIdOnHit0;

    /* ヒットマテリアルを踏んだ時にかかる特殊効果1
     *   キャラがヒットマテリアルを踏んだ時に、設定した特殊効果1が発揮される
     * On Hit [2] - SpEffect ID
     *   When the character steps on the hit material, the set special effect 1 is exhibited.
     * Default Value  = -1 */
    int spEffectIdOnHit1;

    /* フットエフェクトの高さタイプ
     *   フットエフェクトを発生させる高さ
     * Foot Effect Height Type
     *   Height to generate foot effect */
    unsigned char footEffectHeightType:2;

    /* フットエフェクトの向きタイプ
     *   フットエフェクトの発生向き
     * Foot Effect Direction Type
     *   Direction of foot effect */
    unsigned char footEffectDirType:2;

    /* 地面の高さタイプ
     *   水面などアイテムを浮かせるとき用
     * Floor Height Type
     *   For floating items such as the surface of the water */
    unsigned char floorHeightType:2;

    /* 落下ダメージ無効か
     *   落下ダメージを受けない床の場合に 1 を設定する
     * Disable Fall Damage
     *   Set to 1 for floors that are not subject to fall damage */
    unsigned char disableFallDamage:1;

    /* サウンド反響用硬い材質か？
     *   サウンド反響用 硬い材質か？(0:やわらかい,1:かたい)
     * Is Hardness for Sound Reverb
     *   Is it a hard material for sound echo? (0: soft, 1: hard) */
    unsigned char isHardnessForSoundReverb:1;

    /* 材質の固さタイプ
     *   材質の固さ。剛体のソフトコンタクト処理に使用。
     * Hardness Type
     *   The hardness of the material. Used for soft contact processing of rigid bodies. */
    unsigned char hardnessType;

    /* pad
     *   pad */
    char pad2[6];

    /* ヒットマテリアルを踏んだ時にかかる特殊効果0　2周目
     *   ヒットマテリアルを踏んだ時にかかる特殊効果0　2周目
     * On Hit [0] - NG+1 - SpEffect ID
     *   Special effect applied when stepping on the hit material 0 2nd lap
     * Default Value  = -1 */
    int spEffectIdOnHit0_ClearCount_2;

    /* ヒットマテリアルを踏んだ時にかかる特殊効果0　3周目
     *   ヒットマテリアルを踏んだ時にかかる特殊効果0　3周目
     * On Hit [0] - NG+2 - SpEffect ID
     *   Special effect applied when stepping on the hit material 0 3rd lap
     * Default Value  = -1 */
    int spEffectIdOnHit0_ClearCount_3;

    /* ヒットマテリアルを踏んだ時にかかる特殊効果0　4周目
     *   ヒットマテリアルを踏んだ時にかかる特殊効果0　4周目
     * On Hit [0] - NG+3 - SpEffect ID
     *   Special effect applied when stepping on the hit material 0 4th lap
     * Default Value  = -1 */
    int spEffectIdOnHit0_ClearCount_4;

    /* ヒットマテリアルを踏んだ時にかかる特殊効果0　5周目
     *   ヒットマテリアルを踏んだ時にかかる特殊効果0　5周目
     * On Hit [0] - NG+4 - SpEffect ID
     *   Special effect applied when stepping on the hit material 0 5th lap
     * Default Value  = -1 */
    int spEffectIdOnHit0_ClearCount_5;

    /* ヒットマテリアルを踏んだ時にかかる特殊効果0　6周目
     *   ヒットマテリアルを踏んだ時にかかる特殊効果0　6周目
     * On Hit [0] - NG+5 - SpEffect ID
     *   Special effect applied when stepping on the hit material 0 6th lap
     * Default Value  = -1 */
    int spEffectIdOnHit0_ClearCount_6;

    /* ヒットマテリアルを踏んだ時にかかる特殊効果0　7周目
     *   ヒットマテリアルを踏んだ時にかかる特殊効果0　7周目
     * On Hit [0] - NG+6 - SpEffect ID
     *   Special effect applied when stepping on the hit material 0 7th lap
     * Default Value  = -1 */
    int spEffectIdOnHit0_ClearCount_7;

    /* ヒットマテリアルを踏んだ時にかかる特殊効果0　8周目
     *   ヒットマテリアルを踏んだ時にかかる特殊効果0　8周目
     * On Hit [0] - NG+7 - SpEffect ID
     *   Special effect applied when stepping on the hit material 0 8th lap
     * Default Value  = -1 */
    int spEffectIdOnHit0_ClearCount_8;

    /* ヒットマテリアルを踏んだ時にかかる特殊効果1　2周目
     *   ヒットマテリアルを踏んだ時にかかる特殊効果1　2周目
     * On Hit [1] - NG+1 - SpEffect ID
     *   Special effect applied when stepping on the hit material 1st lap
     * Default Value  = -1 */
    int spEffectIdOnHit1_ClearCount_2;

    /* ヒットマテリアルを踏んだ時にかかる特殊効果1　3周目
     *   ヒットマテリアルを踏んだ時にかかる特殊効果1　3周目
     * On Hit [1] - NG+2 - SpEffect ID
     *   Special effect applied when stepping on the hit material 1 3rd lap
     * Default Value  = -1 */
    int spEffectIdOnHit1_ClearCount_3;

    /* ヒットマテリアルを踏んだ時にかかる特殊効果1　4周目
     *   ヒットマテリアルを踏んだ時にかかる特殊効果1　4周目
     * On Hit [1] - NG+3 - SpEffect ID
     *   Special effect applied when stepping on the hit material 1 4th lap
     * Default Value  = -1 */
    int spEffectIdOnHit1_ClearCount_4;

    /* ヒットマテリアルを踏んだ時にかかる特殊効果1　5周目
     *   ヒットマテリアルを踏んだ時にかかる特殊効果1　5周目
     * On Hit [1] - NG+4 - SpEffect ID
     *   Special effect applied when stepping on the hit material 1 5th lap
     * Default Value  = -1 */
    int spEffectIdOnHit1_ClearCount_5;

    /* ヒットマテリアルを踏んだ時にかかる特殊効果1　6周目
     *   ヒットマテリアルを踏んだ時にかかる特殊効果1　6周目
     * On Hit [1] - NG+5 - SpEffect ID
     *   Special effect when stepping on the hit material 1 6th lap
     * Default Value  = -1 */
    int spEffectIdOnHit1_ClearCount_6;

    /* ヒットマテリアルを踏んだ時にかかる特殊効果1　7周目
     *   ヒットマテリアルを踏んだ時にかかる特殊効果1　7周目
     * On Hit [1] - NG+6 - SpEffect ID
     *   Special effect applied when stepping on the hit material 1 7th lap
     * Default Value  = -1 */
    int spEffectIdOnHit1_ClearCount_7;

    /* ヒットマテリアルを踏んだ時にかかる特殊効果1　8周目
     *   ヒットマテリアルを踏んだ時にかかる特殊効果1　8周目
     * On Hit [1] - NG+7 - SpEffect ID
     *   Special effect applied when stepping on the hit material 1 8th lap
     * Default Value  = -1 */
    int spEffectIdOnHit1_ClearCount_8;

    /* ヒットマテリアル差し替え(雨)
     *   天候(雨)によるヒットマテリアル変更先ID(-1：変更を行なわない)
     * Rain - Replace Material ID
     *   Hit material change destination ID due to weather (rain) (-1: No change)
     * Default Value  = -1 */
    short replaceMateiralId_Rain;

    /* pad
     *   pad */
    char pad4[2];

    /* 濡れ特殊効果ID_00
     *   濡れ用特殊効果00
     * Wetness [0] - SpEffect ID
     *   Special effect for wetting 00
     * Default Value  = -1 */
    int spEffectId_forWet00;

    /* 濡れ特殊効果ID_01
     *   濡れ用特殊効果01
     * Wetness [1] - SpEffect ID
     *   Special effects for wetting 01
     * Default Value  = -1 */
    int spEffectId_forWet01;

    /* 濡れ特殊効果ID_02
     *   濡れ用特殊効果02
     * Wetness [2] - SpEffect ID
     *   Special effects for wetting 02
     * Default Value  = -1 */
    int spEffectId_forWet02;

    /* 濡れ特殊効果ID_03
     *   濡れ用特殊効果03
     * Wetness [3] - SpEffect ID
     *   Special effects for wetting 03
     * Default Value  = -1 */
    int spEffectId_forWet03;

    /* 濡れ特殊効果ID_04
     *   濡れ用特殊効果04
     * Wetness [4] - SpEffect ID
     *   Special effects for wetting 04
     * Default Value  = -1 */
    int spEffectId_forWet04;
} er_hit_mtrl_param_t;
