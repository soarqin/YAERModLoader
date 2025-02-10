#pragma once

typedef struct auto_create_env_sound_param_s {
    /* 出現距離Min[m]
     *   出現距離Min[m]
     * Appearance Distance - Min
     *   Appearance distance Min [m]
     * Default Value  = 10 */
    float RangeMin;

    /* 出現距離Max[m]
     *   出現距離Max[
     * Appearance Distance - Max
     *   Appearance distance Max [
     * Default Value  = 25 */
    float RangeMax;

    /* 寿命Min[秒]
     *   寿命Min[秒]
     * Duration - Min
     *   Lifespan Min [seconds]
     * Default Value  = 30 */
    float LifeTimeMin;

    /* 寿命Max[秒]
     *   寿命Max[秒]
     * Duration - Max
     *   Lifespan Max [seconds]
     * Default Value  = 30 */
    float LifeTimeMax;

    /* 削除距離[m]
     *   削除距離[m]
     * Delete Distance
     *   Delete distance [m]
     * Default Value  = 30 */
    float DeleteDist;

    /* 近傍判定距離[m]
     *   近傍判定距離[m]
     * Near Distance
     *   Neighborhood judgment distance [m]
     * Default Value  = 15 */
    float NearDist;

    /* 生成角度制限Min[度]
     *   角度制限Min[度](カメラの前方のY軸角度+-の指定。180なら全方位) 
     * Generation Angle Limit - Min
     *   Angle limit Min [degree] (Specify the Y-axis angle +-in front of the camera. 180 is omnidirectional) */
    float LimiteRotateMin;

    /* 生成角度制限Max[度]
     *   角度制限Max[度](カメラの前方のY軸角度+-の指定。180なら全方位) 
     * Generation Angle Limit - Max
     *   Angle limit Max [degree] (Specify the Y-axis angle +-in front of the camera. 180 is omnidirectional)
     * Default Value  = 180 */
    float LimiteRotateMax;
} auto_create_env_sound_param_t;
