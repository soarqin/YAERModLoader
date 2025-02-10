#pragma once

typedef struct cutscene_gparam_time_param_s {
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

    /* 朝
     *   朝(変換時刻はカットシーン時間変換設定シートを参照）
     * Destination Timezone: Morning
     *   Morning (Refer to the cutscene time conversion setting sheet for the conversion time) */
    unsigned char DstTimezone_Morning;

    /* 昼A
     *   昼A(変換時刻はカットシーン時間変換設定シートを参照）
     * Destination Timezone: Noon
     *   Day A (Refer to the cutscene time conversion setting sheet for the conversion time) */
    unsigned char DstTimezone_Noon;

    /* 昼B
     *   昼B(変換時刻はカットシーン時間変換設定シートを参照）
     * Destination Timezone: Afternoon
     *   Noon-B (Refer to the cutscene time conversion setting sheet for the conversion time) */
    unsigned char DstTimezone_AfterNoon;

    /* 夕
     *   夕(変換時刻はカットシーン時間変換設定シートを参照）
     * Destination Timezone: Evening
     *   Evening (Refer to the cutscene time conversion setting sheet for the conversion time) */
    unsigned char DstTimezone_Evening;

    /* 夜
     *   夜(変換時刻はカットシーン時間変換設定シートを参照）
     * Destination Timezone: Night
     *   Night (Refer to the cutscene time conversion setting sheet for the conversion time) */
    unsigned char DstTimezone_Night;

    /* 深夜A
     *   深夜A(変換時刻はカットシーン時間変換設定シートを参照）
     * Destination Timezone: Deep Night A
     *   Midnight A (Refer to the cutscene time conversion setting sheet for the conversion time) */
    unsigned char DstTimezone_DeepNightA;

    /* 深夜B
     *   深夜B(変換時刻はカットシーン時間変換設定シートを参照）
     * Destination Timezone: Deep Night B
     *   Midnight B (Refer to the cutscene time conversion setting sheet for the conversion time) */
    unsigned char DstTimezone_DeepNightB;

    char reserved[1];

    /* 再生終了時のインゲーム時刻指定[hour]
     *   再生終了時のインゲーム時刻指定[hour][-1.0～24.0](-1(0より小さい)：何もしない)
     * Post Cutscene In-game Time
     *   Specify in-game time at the end of playback [hour] [-1.0 to 24.0] (-1 (less than 0): do nothing)
     * Default Value  = -1 */
    float PostPlayIngameTime;
} cutscene_gparam_time_param_t;
