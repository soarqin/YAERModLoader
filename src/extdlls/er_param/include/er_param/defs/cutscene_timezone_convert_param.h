#pragma once

typedef struct er_cutscene_timezone_convert_param_s {
    /* 変換前時間帯開始時刻[hour]
     *   カットシーン時刻に変換する時間帯の開始時刻[hour]
     * Source - Timezone Start
     *   Start time of the time zone to be converted to cutscene time [hour] */
    float SrcTimezoneStart;

    /* 変換後カットシーン時刻[hour]
     *   カットシーン再生中に使われる時刻を時間単位で入力[hour]
     * Destination - Cutscene Time
     *   Enter the time used during cutscene playback in hours [hour] */
    float DstCutscenTime;
} er_cutscene_timezone_convert_param_t;
