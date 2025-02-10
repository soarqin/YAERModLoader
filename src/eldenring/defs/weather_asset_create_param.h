#pragma once

typedef struct weather_asset_create_param_s {
    /* アセットId
     *   生成するアセットIDを指定します。AEG999_999 -> 999999
     * Asset ID
     *   Specify the asset ID to generate. AEG999_999-> 999999 */
    unsigned int AssetId;

    /* スロット番号
     *   生成制御用の番号です。同一スロットには１個のアセットのみ生成が可能です。重複して生成させたい、させたくない制御ができます。
     * Slot Number
     *   This is the number for generation control. Only one asset can be generated in the same slot. You can control whether you want to generate duplicates or not. */
    unsigned int SlotNo;

    /* 発生条件
     *   発生の条件のタイプです
     * Create Condition Type
     *   The type of condition of occurrence */
    unsigned char CreateConditionType;

    char padding0[3];

    /* 遷移元天候
     *   遷移元の天候を指定します。発生条件が「遷移」のときだけ参照されます
     * Transition Source Weather
     *   Specify the transition source weather. It is referenced only when the occurrence condition is transition. */
    short TransitionSrcWeather;

    /* 遷移先天候
     *   遷移先の天候を指定します。発生条件が「遷移」のときだけ参照されます
     * Transition Destination Weather
     *   Specify the transition destination weather. It is referenced only when the occurrence condition is transition. */
    short TransitionDstWeather;

    /* 経過時間チェック天候
     *   経過時間をチェックする天候を指定します。
     * Check Weather Elapsed Time
     *   Specify the weather to check the elapsed time. */
    short ElapsedTimeCheckweather;

    char padding1[2];

    /* 経過時間[Second]
     *   経過時間を指定します。発生条件が「時間経過」のときだけ参照されます。現実時間[秒]単位で指定します。
     * Elapsed Time
     *   Specify the elapsed time. It is referenced only when the occurrence condition is time elapsed. Real time Specify in seconds. */
    float ElapsedTime;

    /* 生成遅延時間[Second]
     *   生成が決定してから遅延する時間を指定します。遅延している間は作成したスロットは使用中になります。0以下で即時作成。
     * Create Delay Time
     *   Specifies the time to delay after the generation is determined. The created slot will be in use while it is delayed. Created immediately with 0 or less.
     * Default Value  = -1 */
    float CreateDelayTime;

    /* 発生確率[％]
     *   天候遷移、または経過時間の条件を満たした際に発生する確率を指定します
     * Create Probability
     *   Specifies the probability of occurrence when conditions for weather transitions or elapsed time are met.
     * Default Value  = 100 */
    unsigned int CreateProbability;

    /* 寿命[Second]
     *   生成したアセットの寿命を指定します。現実時間[秒]単位で指定します。
     * Duration
     *   Specifies the life of the generated asset. Real time Specify in seconds.
     * Default Value  = 600 */
    float LifeTime;

    /* フェード時間[Second]
     *   フェードイン、フェードアウトに使用される時間[秒]。0以下でフェードなし。
     * Fade Time
     *   Time [seconds] used for fade-in and fade-out. No fade below 0.
     * Default Value  = 1 */
    float FadeTime;

    /* 生成可能開始時刻[Hour]
     *   生成可能な開始時刻を指定します[0.0 - 24.0]。開始、終了どちらかに-1を入れると無制限(全時間で生成可能)の扱いになります。
     * Enable Create Time Min
     *   Specifies a start time that can be generated [0.0 --24.0]. If you put -1 in either the start or the end, it will be treated as unlimited (can be generated in all time).
     * Default Value  = -1 */
    float EnableCreateTimeMin;

    /* 生成可能終了時刻[Hour]
     *   生成可能な終了時刻を指定します[0.0 - 24.0]。開始、終了どちらかに-1を入れると無制限(全時間で生成可能)の扱いになります。
     * Enable Create Time Max
     *   Specifies the end time that can be generated [0.0 --24.0]. If you put -1 in either the start or the end, it will be treated as unlimited (can be generated in all time).
     * Default Value  = -1 */
    float EnableCreateTimeMax;

    /* 生成ポイント0
     *   生成ポイント番号を指定します。MapStudioの「天候アセット生成ポイント」の末尾3桁の数値を指定してください。-1だと無効になります
     * Create Point [0]
     *   Specify the generation point number. Specify the last 3 digits of the Weather Asset Generation Point in MapStudio. -1 will be invalid
     * Default Value  = -1 */
    short CreatePoint0;

    /* 生成ポイント1
     *   生成ポイント番号を指定します。MapStudioの「天候アセット生成ポイント」の末尾3桁の数値を指定してください。-1だと無効になります
     * Create Point [1]
     *   Specify the generation point number. Specify the last 3 digits of the Weather Asset Generation Point in MapStudio. -1 will be invalid
     * Default Value  = -1 */
    short CreatePoint1;

    /* 生成ポイント2
     *   生成ポイント番号を指定します。MapStudioの「天候アセット生成ポイント」の末尾3桁の数値を指定してください。-1だと無効になります
     * Create Point [2]
     *   Specify the generation point number. Specify the last 3 digits of the Weather Asset Generation Point in MapStudio. -1 will be invalid
     * Default Value  = -1 */
    short CreatePoint2;

    /* 生成ポイント3
     *   生成ポイント番号を指定します。MapStudioの「天候アセット生成ポイント」の末尾3桁の数値を指定してください。-1だと無効になります
     * Create Point [3]
     *   Specify the generation point number. Specify the last 3 digits of the Weather Asset Generation Point in MapStudio. -1 will be invalid
     * Default Value  = -1 */
    short CreatePoint3;

    /* 生成制限ID0
     *   生成制限用のIDです。-1:無制限。「マップデフォルトパラメータ.xlsm」の生成制限IDと一致した場合のみ生成が許可されます(SEQ08921)
     * Create Asset Limit ID [0]
     *   ID for production restriction. -1: Unlimited. Generation is allowed only if it matches the generation limit ID in Map default parameter .xlsm (SEQ08921).
     * Default Value  = -1 */
    char CreateAssetLimitId0;

    /* 生成制限ID1
     *   生成制限用のIDです。-1:無制限。「マップデフォルトパラメータ.xlsm」の生成制限IDと一致した場合のみ生成が許可されます(SEQ08921)
     * Create Asset Limit ID [1]
     *   ID for production restriction. -1: Unlimited. Generation is allowed only if it matches the generation limit ID in Map default parameter .xlsm (SEQ08921).
     * Default Value  = -1 */
    char CreateAssetLimitId1;

    /* 生成制限ID2
     *   生成制限用のIDです。-1:無制限。「マップデフォルトパラメータ.xlsm」の生成制限IDと一致した場合のみ生成が許可されます(SEQ08921)
     * Create Asset Limit ID [2]
     *   ID for production restriction. -1: Unlimited. Generation is allowed only if it matches the generation limit ID in Map default parameter .xlsm (SEQ08921).
     * Default Value  = -1 */
    char CreateAssetLimitId2;

    /* 生成制限ID3
     *   生成制限用のIDです。-1:無制限。「マップデフォルトパラメータ.xlsm」の生成制限IDと一致した場合のみ生成が許可されます(SEQ08921)
     * Create Asset Limit ID [3]
     *   ID for production restriction. -1: Unlimited. Generation is allowed only if it matches the generation limit ID in Map default parameter .xlsm (SEQ08921).
     * Default Value  = -1 */
    char CreateAssetLimitId3;

    char Reserved2[4];
} weather_asset_create_param_t;
