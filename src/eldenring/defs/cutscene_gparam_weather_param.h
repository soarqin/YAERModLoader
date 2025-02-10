#pragma once

typedef struct cutscene_gparam_weather_param_s {
    /* NT版出力から外すか
     *   ○をつけたパラメータをNT版パッケージでは除外します
     * Disable Param - Network Test
     *   Parameters marked with  are excluded in the NT version package. */
    unsigned char disableParam_NT:1;

    /* デバッグパラメータか
     *   ○をつけたパラメータは全パッケージから除外します（デバッグ用なので）
     * Disable Param - Debug
     *   Parameters marked with a circle are excluded from all packages (because they are for debugging). */
    unsigned char disableParam_Debug:1;

    /* パッケージ出力用リザーブ1
     *   パッケージ出力用リザーブ1 */
    char disableParamReserve1:6;

    /* パッケージ出力用リザーブ2
     *   パッケージ出力用リザーブ2 */
    char disableParamReserve2[3];

    /* 晴れ
     *   晴れ
     * Destination Weather: Sunny
     *   Sunny */
    short DstWeather_Sunny;

    /* 快晴
     *   快晴
     * Destination Weather: Clear Sky
     *   Sunny */
    short DstWeather_ClearSky;

    /* 薄曇り
     *   薄曇り
     * Destination Weather: Light Cloud
     *   Light cloudy */
    short DstWeather_WeakCloudy;

    /* 曇り
     *   曇り
     * Destination Weather: Cloud
     *   cloudy */
    short DstWeather_Cloud;

    /* 雨
     *   雨
     * Destination Weather: Rain
     *   rain */
    short DstWeather_Rain;

    /* 豪雨
     *   豪雨
     * Destination Weather: Heavy Rain
     *   Heavy rain */
    short DstWeather_HeavyRain;

    /* 嵐
     *   嵐
     * Destination Weather: Storm
     *   storm */
    short DstWeather_Storm;

    /* 嵐（守護者の末裔との戦闘用）
     *   嵐（守護者の末裔との戦闘用）
     * Destination Weather: Storm for Battle
     *   Storm (for combat with the descendants of the guardian) */
    short DstWeather_StormForBattle;

    /* 雪
     *   雪
     * Destination Weather: Snow
     *   snow */
    short DstWeather_Snow;

    /* 大雪
     *   大雪
     * Destination Weather: Heavy Snow
     *   heavy snow */
    short DstWeather_HeavySnow;

    /* 霧
     *   霧
     * Destination Weather: Fog
     *   fog */
    short DstWeather_Fog;

    /* 濃霧
     *   濃霧
     * Destination Weather: Heavy Fog
     *   Thick fog */
    short DstWeather_HeavyFog;

    /* 砂嵐
     *   砂嵐
     * Destination Weather: Sandstorm
     *   Sandstorm */
    short DstWeather_SandStorm;

    /* 濃霧（雨）
     *   濃霧（雨）
     * Destination Weather: Heavy Fog and Rain
     *   Thick fog (rain) */
    short DstWeather_HeavyFogRain;

    /* 再生終了時のインゲーム天候指定(未使用、無効)
     *   再生終了時のインゲーム天候指定(空白または「無効」の場合は何も行われない。)
     * Post Cutscene In-game Weather
     *   In-game weather specifications at the end of playback (nothing is done if blank or invalid)
     * Default Value  = -1 */
    short PostPlayIngameWeather;

    /* 屋内屋外指定
     *   屋内にすると「天候パラメータ.xlsm」の「天候SfxId(屋外)」と「風SfxId(屋外)」で指定されたSFXがカットシーン内で無効になります。
     * Indoor/Outdoor Type
     *   When indoors, the SFX specified by Weather SfxId (Outdoor) and Wind SfxId (Outdoor) in Weather Parameter.xlsm will be invalid in the cutscene. */
    unsigned char IndoorOutdoorType;

    /* インゲームの天候SFX引き継ぐか？_晴れ
     *   インゲームの天候SFX引き継ぐか？_晴れ
     * Replacement Weather: Sunny
     *   In-game weather SFX to take over? _Sunny
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_Sunny;

    /* インゲームの天候SFX引き継ぐか？_快晴
     *   インゲームの天候SFX引き継ぐか？_快晴
     * Replacement Weather: Clear Sky
     *   In-game weather SFX to take over? _ Sunny
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_ClearSky;

    /* インゲームの天候SFX引き継ぐか？_薄曇り
     *   インゲームの天候SFX引き継ぐか？_薄曇り
     * Replacement Weather: Light Cloud
     *   Will the in-game weather SFX be taken over? _ Light cloudy
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_WeakCloudy;

    /* インゲームの天候SFX引き継ぐか？_曇り
     *   インゲームの天候SFX引き継ぐか？_曇り
     * Replacement Weather: Cloud
     *   Will the in-game weather SFX be taken over? _cloudy
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_Cloud;

    /* インゲームの天候SFX引き継ぐか？_雨
     *   インゲームの天候SFX引き継ぐか？_雨
     * Replacement Weather: Rain
     *   In-game weather SFX to take over? _rain
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_Rain;

    /* インゲームの天候SFX引き継ぐか？_豪雨
     *   インゲームの天候SFX引き継ぐか？_豪雨
     * Replacement Weather: Heavy Rain
     *   In-game weather SFX to take over? _ Heavy rain
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_HeavyRain;

    /* インゲームの天候SFX引き継ぐか？_嵐
     *   インゲームの天候SFX引き継ぐか？_嵐
     * Replacement Weather: Storm
     *   In-game weather SFX to take over? _storm
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_Storm;

    /* インゲームの天候SFX引き継ぐか？_嵐（守護者の末裔との戦闘用）
     *   インゲームの天候SFX引き継ぐか？_嵐（守護者の末裔との戦闘用）
     * Replacement Weather: Storm for Battle
     *   In-game weather SFX to take over? _ Storm (for battle with the descendants of the guardian)
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_StormForBattle;

    /* インゲームの天候SFX引き継ぐか？_雪
     *   インゲームの天候SFX引き継ぐか？_雪
     * Replacement Weather: Snow
     *   In-game weather SFX to take over? _snow
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_Snow;

    /* インゲームの天候SFX引き継ぐか？_大雪
     *   インゲームの天候SFX引き継ぐか？_大雪
     * Replacement Weather: Heavy Snow
     *   In-game weather SFX to take over? _heavy snow
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_HeavySnow;

    /* インゲームの天候SFX引き継ぐか？_霧
     *   インゲームの天候SFX引き継ぐか？_霧
     * Replacement Weather: Fog
     *   Will the in-game weather SFX be taken over? _fog
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_Fog;

    /* インゲームの天候SFX引き継ぐか？_濃霧
     *   インゲームの天候SFX引き継ぐか？_濃霧
     * Replacement Weather: Heavy Fog
     *   Will the in-game weather SFX be taken over? _ Thick fog
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_HeavyFog;

    /* インゲームの天候SFX引き継ぐか？_砂嵐
     *   インゲームの天候SFX引き継ぐか？_砂嵐
     * Replacement Weather: Sandstorm
     *   In-game weather SFX to take over? _ Sandstorm
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_SandStorm;

    /* インゲームの天候SFX引き継ぐか？_濃霧（雨）
     *   インゲームの天候SFX引き継ぐか？_濃霧（雨）
     * Replacement Weather: Heavy Fog and Rain
     *   In-game weather SFX to take over? _ Thick fog (rain)
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_HeavyFogRain;

    char reserved[7];

    /* 吹雪
     *   吹雪
     * Destination Weather: Snowstorm
     *   Snowstorm */
    short DstWeather_Snowstorm;

    /* 嵐（雷）
     *   予備天候2
     * Destination Weather: Lightning Storm
     *   Preliminary weather 2 */
    short DstWeather_LightningStorm;

    /* 雪特殊(予備3)
     *   予備天候3
     * Destination Weather: Reserved 3
     *   Preliminary weather 3 */
    short DstWeather_Reserved3;

    /* 予備天候4
     *   予備天候4
     * Destination Weather: Reserved 4
     *   Preliminary weather 4 */
    short DstWeather_Reserved4;

    /* 予備天候5
     *   予備天候5
     * Destination Weather: Reserved 5
     *   Preliminary weather 5 */
    short DstWeather_Reserved5;

    /* 予備天候6
     *   予備天候6
     * Destination Weather: Reserved 6
     *   Preliminary weather 6 */
    short DstWeather_Reserved6;

    /* 予備天候7
     *   予備天候7
     * Destination Weather: Reserved 7
     *   Preliminary weather 7 */
    short DstWeather_Reserved7;

    /* 予備天候8
     *   予備天候8
     * Destination Weather: Reserved 8
     *   Preliminary weather 8 */
    short DstWeather_Reserved8;

    /* インゲームの天候SFX引き継ぐか？_吹雪
     *   インゲームの天候SFX引き継ぐか？_吹雪
     * Replacement Weather: Snowstorm
     *   In-game weather SFX to take over? _ Snowstorm
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_Snowstorm;

    /* インゲームの天候SFX引き継ぐか？_嵐（雷）
     *   インゲームの天候SFX引き継ぐか？_嵐（雷）
     * Replacement Weather: Lightning Storm
     *   In-game weather SFX to take over? _ Storm (thunder)
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_LightningStorm;

    /* インゲームの天候SFX引き継ぐか？_雪特殊(予備3)
     *   インゲームの天候SFX引き継ぐか？_予備天候3
     * Replacement Weather: Reserved 3
     *   Will the in-game weather SFX be taken over? _ Preliminary weather 3
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_Reserved3;

    /* インゲームの天候SFX引き継ぐか？_予備天候4
     *   インゲームの天候SFX引き継ぐか？_予備天候4
     * Replacement Weather: Reserved 4
     *   In-game weather SFX to take over? _ Preliminary weather 4
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_Reserved4;

    /* インゲームの天候SFX引き継ぐか？_予備天候5
     *   インゲームの天候SFX引き継ぐか？_予備天候5
     * Replacement Weather: Reserved 5
     *   Will the in-game weather SFX be taken over? _ Preliminary weather 5
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_Reserved5;

    /* インゲームの天候SFX引き継ぐか？_予備天候6
     *   インゲームの天候SFX引き継ぐか？_予備天候6
     * Replacement Weather: Reserved 6
     *   Will the in-game weather SFX be taken over? _ Preliminary weather 6
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_Reserved6;

    /* インゲームの天候SFX引き継ぐか？_予備天候7
     *   インゲームの天候SFX引き継ぐか？_予備天候7
     * Replacement Weather: Reserved 7
     *   Will the in-game weather SFX be taken over? _ Preliminary weather 7
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_Reserved7;

    /* インゲームの天候SFX引き継ぐか？_予備天候8
     *   インゲームの天候SFX引き継ぐか？_予備天候8
     * Replacement Weather: Reserved 8
     *   In-game weather SFX to take over? _ Preliminary weather 8
     * Default Value  = 1 */
    unsigned char TakeOverDstWeather_Reserved8;

    /* 天候GparamにMapGD地方IDを適用するか？
     *   カットシーン天候Gparamにインゲーム同様MapGD地方IDによる変化を適用するか？(【GR】SEQ30194)
     * Apply MapGdRegionID for GPARAM Enabled
     *   Do you want to apply the mapGD local ID changes to the cutscene weather Gparam as in the in-game? ([GR] SEQ30194) */
    unsigned char IsEnableApplyMapGdRegionIdForGparam;

    /* reserved1
     *   reserved1 ver4->5 64->96へ増量 */
    char reserved2[1];

    /* 天候GparamMapGD用地方ID上書き
     *   カットシーン天候Gparamに使用されるIDを上書きする(-1：上書きなし。カットシーン再生時のMapGD地方IDが使用される)。「天候GparamにMapGD地方IDを適用するか？」が×の場合は参照されない
     * Override MapGdRegion ID
     *   Overwrite the ID used for cutscene weather Gparam (-1: No overwrite. MapGD local ID during cutscene playback is used). If Do you want to apply MapGD local ID to weather Gparam? Is x, it is not referenced.
     * Default Value  = -1 */
    short OverrideMapGdRegionId;

    char reserved1[12];
} cutscene_gparam_weather_param_t;
