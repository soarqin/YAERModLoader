#pragma once

typedef struct er_cutscene_weather_override_gparam_id_convert_param_s {
    /* カットシーン天候上書きGparamサフィックスID
     *   s00_00_0000_WeatherOverride_??.gparamの??の部分のIDです
     * Weather Override GPARAM ID
     *   The ID of the ?? part of s00_00_0000_WeatherOverride_ ??. Gparam */
    unsigned int weatherOverrideGparamId;
} er_cutscene_weather_override_gparam_id_convert_param_t;
