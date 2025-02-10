#pragma once

typedef struct weather_param_s {
    /* 天候SfxId(共通)
     *   天候用SfxId -1：天候Sfxなし 屋内屋外共通で出すものを設定。インタラクティブパーティクルの雨粒など、雨遮蔽(AboveShadow)で消せるものはこちらでOK
     * Weather SFX ID
     *   SfxId for weather -1: No weather Sfx Set for indoor and outdoor use. Items that can be erased with Above Shadow, such as raindrops of interactive particles, are OK here.
     * Default Value  = -1 */
    int SfxId;

    /* 風SfxId(屋外)
     *   風SfxId -1：風Sfxなし 屋外のみ作成されます
     * Wind SFX ID
     *   Wind SfxId -1: No wind Sfx Created only outdoors
     * Default Value  = -1 */
    int WindSfxId;

    /* 地面ヒットエフェクト用SfxId
     *   地面ヒットエフェクト用SfxId -1：地面ヒットエフェクト用なし
     * Ground Hit SFX ID
     *   SfxId for ground hit effect -1: None for ground hit effect
     * Default Value  = -1 */
    int GroundHitSfxId;

    /* 天候用SoundId(共通)
     *   天候用SoundId -1：Soundなし
     * Sound ID
     *   SoundId for weather -1: No Sound
     * Default Value  = -1 */
    int SoundId;

    /* 濡れ時間(秒)
     *   完全に濡れるまでの時間(m00_00_0000_WeatherBaseのウェイトが1.0になるまでの時間) -1：濡れなし(m00_00_0000_WeatherBaseは0.0のまま)
     * Wet Time
     *   Time to get completely wet (time until the weight of m00_00_0000_WeatherBase reaches 1.0) -1: No wetness (m00_00_0000_WeatherBase remains 0.0)
     * Default Value  = -1 */
    float WetTime;

    /* 天候用GparamId
     *   屋外天候用Gparam(m00_00_?XXX_WeatherOutdoor.gparamxml)のXXXの部分を指定する。天候間で使用するGparamの共有が可能。
     * GPARAM ID
     *   Specify the XXX part of Gparam (m00_00_? XXX_WeatherOutdoor.gparamxml) for outdoor weather. Gparam to be used can be shared between weather. */
    unsigned int GparamId;

    /* 次回天候抽選までの最小時間(インゲーム秒)
     *   次回天候抽選までの時間の最最小値をインゲーム秒単位で指定します。この天候に遷移時、次の天候までの時間が最小から最大の間のランダムな時間になります。
     * Next Weather Lot - Min Duration
     *   Specify the minimum time to the next weather lottery in in-game seconds. When transitioning to this weather, the time to the next weather will be a random time between the minimum and maximum.
     * Default Value  = 3600 */
    unsigned int NextLotIngameSecondsMin;

    /* 次回天候抽選までの最大時間(インゲーム秒)
     *   次回天候抽選までの時間の最大値をインゲーム秒単位で指定します。この天候に遷移時、次の天候までの時間が最小から最大の間のランダムな時間になります。
     * Next Weather Lot - Max Duration
     *   Specify the maximum time until the next weather lottery in in-game seconds. When transitioning to this weather, the time to the next weather will be a random time between the minimum and maximum.
     * Default Value  = 7200 */
    unsigned int NextLotIngameSecondsMax;

    /* 濡れ特殊効果ID_00
     *   キャラに掛かる特殊効果ID(-1：なし)
     * Wet SpEffect [0]
     *   Special effect ID on the character (-1: None)
     * Default Value  = -1 */
    int WetSpEffectId00;

    /* 濡れ特殊効果ID_01
     *   キャラに掛かる特殊効果ID(-1：なし)
     * Wet SpEffect [1]
     *   Special effect ID on the character (-1: None)
     * Default Value  = -1 */
    int WetSpEffectId01;

    /* 濡れ特殊効果ID_02
     *   キャラに掛かる特殊効果ID(-1：なし)
     * Wet SpEffect [2]
     *   Special effect ID on the character (-1: None)
     * Default Value  = -1 */
    int WetSpEffectId02;

    /* 濡れ特殊効果ID_03
     *   キャラに掛かる特殊効果ID(-1：なし)
     * Wet SpEffect [3]
     *   Special effect ID on the character (-1: None)
     * Default Value  = -1 */
    int WetSpEffectId03;

    /* 濡れ特殊効果ID_04
     *   キャラに掛かる特殊効果ID(-1：なし)
     * Wet SpEffect [4]
     *   Special effect ID on the character (-1: None)
     * Default Value  = -1 */
    int WetSpEffectId04;

    /* 天候SfxId(屋内)
     *   天候用SfxId -1：天候Sfxなし　屋内のみ
     * Weather SFX - Indoors Only - SFX ID
     *   Weather SfxId -1: No weather Sfx indoors only
     * Default Value  = -1 */
    int SfxIdInoor;

    /* 天候SfxId(屋外)
     *   天候用SfxId -1：天候Sfxなし　屋外のみ
     * Weather SFX - Outdoors Only - SFX ID
     *   Weather SfxId -1: No weather Sfx, outdoor only
     * Default Value  = -1 */
    int SfxIdOutdoor;

    /* AI視界倍率
     *   AI視界倍率
     * AI Sight Rate
     *   AI field of view magnification
     * Default Value  = 1 */
    float aiSightRate;

    /* 遠見台カメラ中ウェイト値上書き
     *   遠見台カメラ中ウェイト値上書き(SEQ16724)
     * Overwrite Weight Valuue in Distant View Camera
     *   Overwrite weight value in distant view camera (SEQ16724)
     * Default Value  = -1 */
    float DistViewWeatherGparamOverrideWeight;
} weather_param_t;
