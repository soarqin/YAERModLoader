#pragma once

typedef struct direction_camera_param_s {
    /* オプションの影響を受けるか
     *   演出カメラON/OFFオプションの影響を受けるか？
     * Is Use Option
     *   Is it affected by the production camera ON / OFF option? */
    unsigned char isUseOption:1;

    /* パッド
     *   pad */
    char pad2:3;

    /* パッド
     *   pad */
    char pad1[15];
} direction_camera_param_t;
