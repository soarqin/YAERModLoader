#pragma once

typedef struct er_map_default_info_param_s {
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

    /* ファストトラベル許可フラグID
     *   ファストトラベル許可フラグID
     * Enable Fast Travel Event Flag ID
     *   Fast travel permission flag ID */
    unsigned int EnableFastTravelEventFlagId;

    /* 天候抽選時間オフセット(インゲーム秒)
     *   天候抽選時間にかかるオフセット(単位：インゲーム秒)。ゲームプロパティのインゲーム時間スケールで割ると現実時間になります
     * Weather Lot - Time Offset
     *   Offset for weather lottery time (unit - in-game seconds). Divide by the in-game time scale of the game properties to get real time */
    int WeatherLotTimeOffsetIngameSeconds;

    /* 天候生成アセット生成制限用ID
     *   天候アセット生成パラメータ.xlsmで生成されるアセットの生成制限に使うID
     * Weather Create Asset Limit ID
     *   ID used to limit the generation of assets generated by the weather asset generation parameter .xlsm
     * Default Value  = -1 */
    char WeatherCreateAssetLimitId;

    /* マップ視界タイプ
     *   マップ視界タイプ
     * Map Visibility Type
     *   Map visibility type */
    unsigned char MapAiSightType;

    /* サウンド屋内、完全屋内振り分け
     *   マップGD設定の「屋内」をサウンド用の「屋内」、「完全屋内」どちらに振り分けるかを設定します(SEQ09833)
     * Sound Indoor Type
     *   Set whether to divide the map GD setting indoor into indoor or completely indoor for sound (SEQ09833). */
    unsigned char SoundIndoorType;

    /* リバーブデフォルト設定
     *   このマップのリバーブデフォルトタイプを指定します
     * Reverb Default Type
     *   Specifies the reverb default type for this map
     * Default Value  = -1 */
    char ReverbDefaultType;

    /* BGM用場所情報
     *   BGM用の場所デフォルト情報を指定します
     * BGM Location Info
     *   Specify location default information for BGM */
    short BgmPlaceInfo;

    /* 環境音用場所情報
     *   環境音用の場所デフォルト情報を指定します
     * Environmental Location Info
     *   Specifies location default information for ambient sounds */
    short EnvPlaceInfo;

    /* マップ追加バンクID
     *   追加で読み込むサウンドの「マップ追加バンク」のIDを指定します(-1:マップ追加バンクなし)(SEQ15725)
     * Map Additional Sound Bank ID
     *   Specify the ID of the map addition bank of the sound to be additionally loaded (-1 - no map addition bank) (SEQ15725)
     * Default Value  = -1 */
    int MapAdditionalSoundBankId;

    /* サウンド用マップ高さ情報[m]
     *   サウンド用マップ高さ情報[m](SEQ15727)
     * Map Height Info for Sound
     *   Map height information for sound [m] (SEQ15727) */
    short MapHeightForSound;

    /* 【レガシー用】マップ環境マップ時間ブレンド有効か？
     *   環境マップの時間ブレンドを行うかを指定します。0番の時間帯のTexureだけが撮影、使用されます。GPU負荷,メモリが軽減されます。レガシー(m00-m49)のみ有効な設定です(SEQ16464)
     * Enable Blend Timezone Envmap
     *   Specifies whether to time blend the environment map. Only Texure in the 0th time zone is shot and used. GPU load and memory are reduced. This setting is valid only for Legacy (m00-m49) (SEQ16464).
     * Default Value  = 1 */
    unsigned char IsEnableBlendTimezoneEnvmap;

    /* GI解像度上書き設定_XSSプラット
     *   XSS(Xbox SeriesS,Lockhart)で使用するGI解像度上書きします
     * Override GI Resolution - XSS
     *   Overwrites the GI resolution used in XSS (Xbox SeriesS, Lockhart)
     * Default Value  = -1 */
    char OverrideGIResolution_XSS;

    /* マップハイヒット切り替判定AABB_幅奥行き(XZ)[m]
     *   マップハイヒット切り替判定AABB_幅奥行き(XZ)[m](SEQ16295)
     * Map High Hit Switch - AABB Depth
     *   Map high hit switching judgment AABB_width Depth (XZ) [m] (SEQ16295)
     * Default Value  = 40 */
    float MapLoHiChangeBorderDist_XZ;

    /* マップハイヒット切り替え判定AABB_高さ(Y)[m]
     *   マップハイヒット切り替え判定AABB_高さ(Y)[m](SEQ16295)
     * Map High Hit Switch - AABB Height
     *   Map high hit switching judgment AABB_ height (Y) [m] (SEQ16295)
     * Default Value  = 40 */
    float MapLoHiChangeBorderDist_Y;

    /* マップハイヒット切り替え判定遊び距離[m]
     *   マップハイヒット切り替え判定遊び距離[m]。通常はデフォルトでいいはず。小さいAABBの場合は必要に応じて調整してください。遊びがあまりに小さいと頻繁に切り替えが起こります。AABBサイズより大きい場合は想定してません(SEQ16295)
     * Map High Hit Switch - Play Distance
     *   Map high hit switching judgment play distance [m]. Normally the default should be fine. For smaller AABB, adjust as needed. If the play is too small, switching will occur frequently. Not expected if larger than AABB size (SEQ 16295)
     * Default Value  = 5 */
    float MapLoHiChangePlayDist;

    /* 自動描画グループ計算で、裏面判定となるピクセル数
     *   自動描画グループ計算で、裏面判定となるピクセル数
     * Automatic Draw Group - Back Side Pixel Count
     *   Number of pixels to be judged on the back side in automatic drawing group calculation
     * Default Value  = 32400 */
    unsigned int MapAutoDrawGroupBackFacePixelNum;

    /* Playerライト強度スケール値
     *   このマップでPC、PC馬常駐光源にかけるスケールを指定します(SEQ16562)
     * Player Light Scale
     *   Specify the scale to be applied to the PC and PC horse resident light source on this map (SEQ16562).
     * Default Value  = 1 */
    float PlayerLigntScale;

    /* 時間帯によるPlayerライト強度スケール変化をするか？
     *   このマップでPC、PC馬常駐光源、時間帯によるPlayerライト強度スケール変化をするか？を指定します(SEQ16562)
     * Enable Timezone Player Light Scale
     *   Does this map change the Player light intensity scale depending on the PC, PC horse resident light source, and time zone? (SEQ 16562)
     * Default Value  = 1 */
    unsigned char IsEnableTimezonnePlayerLigntScale;

    /* 自動崖風SE無効にするか？
     *   自動崖風SE無効にするか？(SEQ15729)
     * Disable Automatic Cliff Wind
     *   Do you want to disable automatic cliff wind SE? (SEQ15729) */
    unsigned char isDisableAutoCliffWind;

    /* オープンキャラアクティベート制限_評価値閾値
     *   オープンキャラアクティベート制限_評価値閾値
     * Open Character Activation Threshold
     *   Open character activation limit_evaluation value threshold
     * Default Value  = -1 */
    short OpenChrActivateThreshold;

    /* マップ別擬態確率パラメータID
     *   マップ別擬態確率パラメータID(SEQ22471)
     * Map Mimicry Establishment Param ID
     *   Mimicry probability parameter ID by map (SEQ22471)
     * Default Value  = -1 */
    int MapMimicryEstablishmentParamId;

    /* GI解像度上書き設定_XSXプラット
     *   XSX(Xbox SeriesX,Anaconda)で使用するGI解像度上書きします
     * Override GI Resolution - XSX
     *   Overwrites the GI resolution used on XSX (Xbox Series X, Anaconda)
     * Default Value  = -1 */
    char OverrideGIResolution_XSX;

    /* リザーブ
     *   リザーブ */
    char Reserve[7];
} er_map_default_info_param_t;
