#pragma once

typedef struct sound_asset_sound_obj_enable_dist_param_s {
    /* アセットサウンド音源有効距離設定[m]
     *   アセットサウンド音源有効距離[m](0より小さい:無効)
     * Sound Object - Enable Distance
     *   Asset sound sound source effective distance [m] (less than 0: invalid)
     * Default Value  = -1 */
    float SoundObjEnableDist;
} sound_asset_sound_obj_enable_dist_param_t;
