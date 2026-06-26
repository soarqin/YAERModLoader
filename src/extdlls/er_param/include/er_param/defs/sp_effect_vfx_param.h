#pragma once

typedef struct er_sp_effect_vfx_param_s {
    /* 効果中SfxID
     *   効果中SfxID(-1：無効)
     * Midst SFX ID
     *   In effect SfxID (-1: invalid)
     * Default Value  = -1 */
    int midstSfxId;

    /* 効果中SeID
     *   効果中SeID(-1：無効)
     * Midst SE ID
     *   In effect SeID (-1: invalid)
     * Default Value  = -1 */
    int midstSeId;

    /* 発動時SfxID
     *   発動時SfxID(-1：無効)
     * Start SFX ID
     *   SfxID at activation (-1: invalid)
     * Default Value  = -1 */
    int initSfxId;

    /* 発動時SeID
     *   発動時SeID(-1：無効)
     * Start SE ID
     *   When activated SeID (-1: invalid)
     * Default Value  = -1 */
    int initSeId;

    /* 解除時SfxID
     *   解除時SfxID(-1：無効)
     * End SFX ID
     *   SfxID at the time of cancellation (-1: invalid)
     * Default Value  = -1 */
    int finishSfxId;

    /* 解除時SeID
     *   解除時SeID(-1：無効)
     * End SE ID
     *   SeID at the time of release (-1: invalid)
     * Default Value  = -1 */
    int finishSeId;

    /* 姿隠し開始距離[m]
     *   カムフラージュ開始距離です
     * Camouflage - Start Distance
     *   It is the camouflage start distance
     * Default Value  = -1 */
    float camouflageBeginDist;

    /* 姿隠し終了距離[m]
     *   カムフラージュ終了距離です
     * Camouflage - End Distance
     *   It is the camouflage end distance
     * Default Value  = -1 */
    float camouflageEndDist;

    /* 変身防具ID
     *   変身防具ID(-1：なし)
     * Transform - Protector ID
     *   Makeover Armor ID (-1: None)
     * Default Value  = -1 */
    int transformProtectorId;

    /* 効果中ダミポリID
     *   効果中ダミポリID(-1：ルート)
     * Midst Dummy Poly ID
     *   In effect Damipoli ID (-1: Root)
     * Default Value  = -1 */
    short midstDmyId;

    /* 発動時ダミポリID
     *   発動時ダミポリID(-1：ルート)
     * Start Dummy Poly ID
     *   Damipoli ID at the time of activation (-1: root)
     * Default Value  = -1 */
    short initDmyId;

    /* 解除時ダミポリID
     *   解除時ダミポリID(-1：ルート)
     * End Dummy Poly ID
     *   Damipoli ID at the time of cancellation (-1: root)
     * Default Value  = -1 */
    short finishDmyId;

    /* エフェクトタイプ
     *   エフェクトタイプ
     * Effect Type
     *   Effect type */
    unsigned char effectType;

    /* 武器エンチャント用ソウルパラムID
     *   武器エンチャント用ソウルパラムID(-1：なし).適用されるファントムパラムを変更します。
     * Weapon Enchant - Soul Param ID
     *   Soul Param ID for Weapon Enchantment (-1: None). Change the applied Phantom Param. */
    unsigned char soulParamIdForWepEnchant;

    /* VFX再生カテゴリ
     *   重複効果によるエフェクト再生を制御します
     * Play Category
     *   Controls effect playback due to duplicate effects */
    unsigned char playCategory;

    /* カテゴリ内優先度
     *   カテゴリ一致した場合の再生優先度を設定(低い方が優先)
     * Play Priority
     *   Set the playback priority when the categories match (lower one has priority) */
    unsigned char playPriority;

    /* 大型用エフェクトがあるか
     *   大型用エフェクトがあるか
     * Large Effect Exists
     *   Is there a large effect? */
    unsigned char existEffectForLarge:1;

    /* ソウル体用エフェクトがあるか
     *   ソウル体用エフェクトがあるか
     * Soul Effect Exists
     *   Is there an effect for the soul body? */
    unsigned char existEffectForSoul:1;

    /* 姿隠し時にエフェクトを非表示にするか
     *   姿隠し時にエフェクトを非表示にするか
     * Camouflage - Invisible while Active
     *   Whether to hide the effect when hiding */
    unsigned char effectInvisibleAtCamouflage:1;

    /* 姿隠しするか
     *   姿隠しするか
     * Camouflage - Enable
     *   Do you hide */
    unsigned char useCamouflage:1;

    /* 姿隠し時に味方でも非表示か
     *   姿隠し時に味方でも非表示か
     * Camouflage - Invisible for Friend
     *   Is it hidden even by allies when hiding? */
    unsigned char invisibleAtFriendCamouflage:1;

    /* 姿隠し時にフットエフェクトを消すか
     *   姿隠し時にフットエフェクトを消すか
     * Camouflage - Hide Foot Effect
     *   Do you want to turn off the foot effect when hiding? */
    unsigned char isHideFootEffect_forCamouflage:1;

    /* 半透明の姿隠しか
     *   半透明の姿隠しか
     * Camouflage - Translucent Appearance
     *   Only translucent appearance */
    unsigned char halfCamouflage:1;

    /* 変身防具IDが全身用か
     *   変身防具IDが全身用か
     * Is Full Body Protector ID
     *   Is the transformation armor ID for the whole body? */
    unsigned char isFullBodyTransformProtectorId:1;

    /* 武器エンチャント用インビジブルウェポンか
     *   武器エンチャント用インビジブルウェポンか(0:武器表示, 1:武器非表示)
     * Is Invisible Weapon
     *   Invisible Weapon for Weapon Enchantment (0: Weapon Show, 1: Weapon Hide) */
    unsigned char isInvisibleWeapon:1;

    /* サイレンスか
     *   サイレンスか(0:ちがう, 1:そう)
     * Is Silent
     *   Is it silence? (0: No, 1: Yes) */
    unsigned char isSilence:1;

    /* 全身か（効果中）
     *   効果中SFXを装備用全身ダミポリを使用するか。1の時に胴:190,頭:191,手:192,脚:193からSFXを再生する
     * Is Midst SFX Full Body
     *   Do you use whole body Damipoli for equipping SFX during effect? Play SFX from torso: 190, head: 191, hands: 192, legs: 193 at 1 */
    unsigned char isMidstFullbody:1;

    /* 全身か（発動時）
     *   発動中SFXを装備用全身ダミポリを使用するか。1の時に胴:190,頭:191,手:192,脚:193からSFXを再生する
     * Is Start SFX Full Body
     *   Do you use the whole body Damipoli for equipping SFX during activation? Play SFX from torso: 190, head: 191, hands: 192, legs: 193 at 1 */
    unsigned char isInitFullbody:1;

    /* 全身か（解除時）
     *   解除時SFXを装備用全身ダミポリを使用するか。1の時に胴:190,頭:191,手:192,脚:193からSFXを再生する
     * Is End SFX Full Body
     *   Do you use the whole body Damipoli for equipping SFX at the time of release? Play SFX from torso: 190, head: 191, hands: 192, legs: 193 at 1 */
    unsigned char isFinishFullbody:1;

    /* 死体時でも表示を行うか
     *   ○の場合、死体時でもVFXが表示されるようになります。
     * Is Visible on Dead Chr
     *   If , VFX will be displayed even when the corpse is dead. */
    unsigned char isVisibleDeadChr:1;

    /* エンチャントSFXサイズオフセット適応か
     *   武器パラの「エンチャントSfxサイズ」に従ってSfxIdをオフセットするか
     * Use Enchant SFX Size to Offset SFX ID
     *   Whether to offset the SfxId according to the enchantment Sfx size of the weapon para */
    unsigned char isUseOffsetEnchantSfxSize:1;

    /* パディング
     *   パディング */
    unsigned char unknown_0x2f_7:1;

    /* デカールID1
     *   デカールID1(-1：無効)
     * Decal ID [0]
     *   Decal ID 1 (-1: invalid)
     * Default Value  = -1 */
    int decalId1;

    /* デカールID2
     *   デカールID2(-1：無効)
     * Decal ID [1]
     *   Decal ID 2 (-1: invalid)
     * Default Value  = -1 */
    int decalId2;

    /* フットエフェクト優先度
     *   フットエフェクトオフセットの優先度(低いほうが優先)
     * Foot Effect Priority
     *   Foot effect offset priority (lower is higher) */
    unsigned char footEffectPriority;

    /* フットエフェクトオフセット
     *   この特殊効果がかかっている場合にフットエフェクトIDにオフセットする量
     * Foot Effect Offset
     *   Amount offset to foot effect ID when this special effect is applied */
    unsigned char footEffectOffset;

    /* 剣閃SFXIDオフセットタイプ
     *   剣閃SFXIDにかけるオフセット値です。エンチャントと剣の軌跡エフェクトに使われる
     * Trace SFX ID Offset Type
     *   The offset value applied to the sword flash SFX ID. Used for enchantment and sword trajectory effects */
    unsigned char traceSfxIdOffsetType;

    /* プレイヤー見た目強制上書き
     *   キャラクターの見た目を強制的に生者/亡者にできる機能
     * Force Deceased Type
     *   A function that can force the appearance of a character to be alive / dead */
    unsigned char forceDeceasedType;

    /* エンチャント時根元ダミポリID＿０
     *   エンチャント時の根元に発生させるダミポリID
     * Enchant SFX Start - Dummy Poly ID [0]
     *   Damipoli ID generated at the base of enchantment
     * Default Value  = -1 */
    int enchantStartDmyId_0;

    /* エンチャント時剣先ダミポリID＿０
     *   エンチャント時の剣先に発生させるダミポリID。-1指定で自動的に連番になってるところまで出す。
     * Enchant SFX end - Dummy Poly ID [0]
     *   Damipoli ID generated at the tip of the sword at the time of enchantment. -1 If specified, it will be automatically put out to the point where it is a serial number.
     * Default Value  = -1 */
    int enchantEndDmyId_0;

    /* エンチャント時根元ダミポリID＿１
     *   エンチャント時の根元に発生させるダミポリID
     * Enchant SFX Start - Dummy Poly ID [1]
     *   Damipoli ID generated at the base of enchantment
     * Default Value  = -1 */
    int enchantStartDmyId_1;

    /* エンチャント時剣先ダミポリID＿１
     *   エンチャント時の剣先に発生させるダミポリID。-1指定で自動的に連番になってるところまで出す。
     * Enchant SFX End - Dummy Poly ID [1]
     *   Damipoli ID generated at the tip of the sword at the time of enchantment. -1 If specified, it will be automatically put out to the point where it is a serial number.
     * Default Value  = -1 */
    int enchantEndDmyId_1;

    /* エンチャント時根元ダミポリID＿２
     *   エンチャント時の根元に発生させるダミポリID
     * Enchant SFX Start - Dummy Poly ID [2]
     *   Damipoli ID generated at the base of enchantment
     * Default Value  = -1 */
    int enchantStartDmyId_2;

    /* エンチャント時剣先ダミポリID＿２
     *   エンチャント時の剣先に発生させるダミポリID。-1指定で自動的に連番になってるところまで出す。
     * Enchant SFX End - Dummy Poly ID [2]
     *   Damipoli ID generated at the tip of the sword at the time of enchantment. -1 If specified, it will be automatically put out to the point where it is a serial number.
     * Default Value  = -1 */
    int enchantEndDmyId_2;

    /* エンチャント時根元ダミポリID＿３
     *   エンチャント時の根元に発生させるダミポリID
     * Enchant SFX Start - Dummy Poly ID [3]
     *   Damipoli ID generated at the base of enchantment
     * Default Value  = -1 */
    int enchantStartDmyId_3;

    /* エンチャント時剣先ダミポリID＿３
     *   エンチャント時の剣先に発生させるダミポリID。-1指定で自動的に連番になってるところまで出す。
     * Enchant SFX End - Dummy Poly ID [3]
     *   Damipoli ID generated at the tip of the sword at the time of enchantment. -1 If specified, it will be automatically put out to the point where it is a serial number.
     * Default Value  = -1 */
    int enchantEndDmyId_3;

    /* エンチャント時根元ダミポリID＿４
     *   エンチャント時の根元に発生させるダミポリID
     * Enchant SFX Start - Dummy Poly ID [4]
     *   Damipoli ID generated at the base of enchantment
     * Default Value  = -1 */
    int enchantStartDmyId_4;

    /* エンチャント時剣先ダミポリID＿４
     *   エンチャント時の剣先に発生させるダミポリID。-1指定で自動的に連番になってるところまで出す。
     * Enchant SFX End - Dummy Poly ID [4]
     *   Damipoli ID generated at the tip of the sword at the time of enchantment. -1 If specified, it will be automatically put out to the point where it is a serial number.
     * Default Value  = -1 */
    int enchantEndDmyId_4;

    /* エンチャント時根元ダミポリID＿５
     *   エンチャント時の根元に発生させるダミポリID
     * Enchant SFX Start - Dummy Poly ID [5]
     *   Damipoli ID generated at the base of enchantment
     * Default Value  = -1 */
    int enchantStartDmyId_5;

    /* エンチャント時剣先ダミポリID＿５
     *   エンチャント時の剣先に発生させるダミポリID。-1指定で自動的に連番になってるところまで出す。
     * Enchant SFX End - Dummy Poly ID [5]
     *   Damipoli ID generated at the tip of the sword at the time of enchantment. -1 If specified, it will be automatically put out to the point where it is a serial number.
     * Default Value  = -1 */
    int enchantEndDmyId_5;

    /* エンチャント時根元ダミポリID＿６
     *   エンチャント時の根元に発生させるダミポリID
     * Enchant SFX Start - Dummy Poly ID [6]
     *   Damipoli ID generated at the base of enchantment
     * Default Value  = -1 */
    int enchantStartDmyId_6;

    /* エンチャント時剣先ダミポリID＿６
     *   エンチャント時の剣先に発生させるダミポリID。-1指定で自動的に連番になってるところまで出す。
     * Enchant SFX End - Dummy Poly ID [6]
     *   Damipoli ID generated at the tip of the sword at the time of enchantment. -1 If specified, it will be automatically put out to the point where it is a serial number.
     * Default Value  = -1 */
    int enchantEndDmyId_6;

    /* エンチャント時根元ダミポリID＿７
     *   エンチャント時の根元に発生させるダミポリID
     * Enchant SFX Start - Dummy Poly ID [7]
     *   Damipoli ID generated at the base of enchantment
     * Default Value  = -1 */
    int enchantStartDmyId_7;

    /* エンチャント時剣先ダミポリID＿７
     *   エンチャント時の剣先に発生させるダミポリID。-1指定で自動的に連番になってるところまで出す。
     * Enchant SFX End - Dummy Poly ID [7]
     *   Damipoli ID generated at the tip of the sword at the time of enchantment. -1 If specified, it will be automatically put out to the point where it is a serial number.
     * Default Value  = -1 */
    int enchantEndDmyId_7;

    /* SfxIDオフセットタイプ
     *   SfxIDオフセットタイプ
     * SFX ID Offset Type
     *   SfxID offset type */
    unsigned char SfxIdOffsetType;

    /* ファントムパラメータ強制指定
     *   ファントムパラメータの強制上書きタイプ
     * Phantom Param Overwrite Type
     *   Forced overwrite type of phantom parameters */
    unsigned char phantomParamOverwriteType;

    /* 姿隠し時最小α値[%]
     *   姿隠し時最小α値[%]
     * Camouflage - Min Alpha
     *   Minimum  value when hiding [%] */
    unsigned char camouflageMinAlpha;

    /* 水濡れ効果
     *   ウェットパラメータを参照して水濡れ表現を発生させる
     * Wet Aspect Type
     *   Generate a wet expression by referring to the wet parameter */
    unsigned char wetAspectType;

    /* ファントムパラメータ上書きID
     *   ファントムパラメータの強制Id
     * Phantom Param Overwrite ID
     *   Forced Id of phantom parameter */
    int phantomParamOverwriteId;

    /* マテリアル拡張パラメータID
     *   ID0～99はGSの予約IDです。ID100以降を指定した場合、マテリアル拡張パラメータを参照します（-1：無効値）
     * Material Param ID
     *   ID0-99 are GS reservation IDs. If ID100 or later is specified, the material extension parameter is referenced (-1: invalid value).
     * Default Value  = -1 */
    int materialParamId;

    /* マテリアルパラメータの初期値
     *   マテリアルパラメータのフェード開始時の値。対象はマテリアルパラメータIDで指定する。マテリアルパラメータIDが -1 なら何もしない
     * Material Param - Start Fade
     *   The value at the start of the fade of the material parameter. The target is specified by the material parameter ID. If the material parameter ID is -1, do nothing */
    float materialParamInitValue;

    /* マテリアルパラメータの目標値
     *   マテリアルパラメータのフェード終了時の値。対象はマテリアルパラメータIDで指定する。マテリアルパラメータIDが -1 なら何もしない
     * Material Param - End Fade
     *   The value at the end of the fade of the material parameter. The target is specified by the material parameter ID. If the material parameter ID is -1, do nothing */
    float materialParamTargetValue;

    /* マテリアルパラメータ値のフェード時間
     *   マテリアルパラメータ値のフェード時間。この時間かけて徐々に目標値へ行く。マテリアルパラメータIDが -1 なら何もしない
     * Material Param - Fade Time
     *   Fade time for material parameter values. Gradually reach the target value over this time. If the material parameter ID is -1, do nothing */
    float materialParamFadeTime;

    /* フットデカール材質オフセット強制上書きID 
     *   フットデカールの床材質IDオフセットを強制的に書き換える（-1未使用）
     * Foot Decal Material Offset Overwrite ID
     *   Forcibly rewrite the floor material ID offset of the foot decal (-1 unused)
     * Default Value  = -1 */
    short footDecalMaterialOffsetOverwriteId;

    unsigned char unknown_0x96;

    unsigned char unknown_0x97;

    unsigned char unknown_0x98;

    unsigned char unknown_0x99;

    unsigned char unknown_0x9a;

    /* パディング
     *   パディング */
    char pad[9];
} er_sp_effect_vfx_param_t;
