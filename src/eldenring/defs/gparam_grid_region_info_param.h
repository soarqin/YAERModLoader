#pragma once

typedef struct gparam_grid_region_info_param_s {
    /* MapGparam用オープン地方ID 
     *   MapGparam用オープンの地方ID。m60_00_00XX.gparamxmlのXXの部分に使用される
     * GPARAM Grid Region ID
     *   Open local ID for MapGparam. Used for the XX part of m60_00_00XX.gparamxml */
    unsigned int GparamGridRegionId;

    /* リザーブ
     *   リザーブ */
    char Reserve[28];
} gparam_grid_region_info_param_t;
