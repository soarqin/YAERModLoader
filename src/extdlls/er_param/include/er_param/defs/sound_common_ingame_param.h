#pragma once

typedef struct er_sound_common_ingame_param_s {
    /* パラメータのKey文字列
     *   パラメータのKey文字列です
     * Param Key
     *   Key string of the parameter */
    char ParamKeyStr[32];

    /* パラメータのValue文字列
     *   パラメータのValue文字列です
     * Param Value
     *   Value string of the parameter */
    char ParamValueStr[32];
} er_sound_common_ingame_param_t;
