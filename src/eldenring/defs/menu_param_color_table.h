#pragma once

typedef struct menu_param_color_table_s {
    /* 補間方法
     *   補間方法
     * Lerp Mode
     *   Interpolation method */
    unsigned char lerpMode;

    /* パッド */
    char pad1[3];

    /* 色相
     *   色相。補間では固定値として扱う
     * Hue
     *   Hue. Treat as a fixed value in interpolation */
    unsigned short h;

    /* パッド */
    char pad2[2];

    /* 彩度
     *   彩度1。補間の1点目として扱われる
     * Saturation [1]
     *   Saturation 1. Treated as the first point of interpolation
     * Default Value  = 1 */
    float s1;

    /* 明度
     *   明度1。補間の1点目として扱われる
     * Brightness [1]
     *   Brightness 1. Treated as the first point of interpolation
     * Default Value  = 1 */
    float v1;

    /* 彩度
     *   彩度2。補間の2点目として扱われる
     * Saturation [2]
     *   Saturation 2. Treated as the second point of interpolation
     * Default Value  = 1 */
    float s2;

    /* 明度
     *   明度2。補間の2点目として扱われる
     * Brightness [2]
     *   Brightness 2. Treated as the second point of interpolation
     * Default Value  = 1 */
    float v2;

    /* 彩度
     *   彩度3。補間の3点目として扱われる
     * Saturation [3]
     *   Saturation 3. Treated as the third point of interpolation
     * Default Value  = 1 */
    float s3;

    /* 明度
     *   明度3。補間の3点目として扱われる
     * Brightness [3]
     *   Brightness 3. Treated as the third point of interpolation
     * Default Value  = 1 */
    float v3;
} menu_param_color_table_t;
