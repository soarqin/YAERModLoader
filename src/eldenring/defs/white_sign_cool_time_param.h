#pragma once

typedef struct er_white_sign_cool_time_param_s {
    /* 制限時間（通常・指なし）
     *   制限時間[sec]（通常・干からびた指無）
     * Limitation Time - Normal
     *   Time limit [sec] (normal, dry fingerless) */
    float limitationTime_Normal;

    /* 制限時間（通常・指あり）
     *   制限時間[sec]（通常・干からびた指有）
     * Limitation Time - Normal (Dried Finger)
     *   Time limit [sec] (normal / dry finger) */
    float limitationTime_NormalDriedFinger;

    /* 制限時間（マップ守護・指なし）
     *   制限時間[sec]（マップ守護・干からびた指無）
     * Limitation Time - Guardian
     *   Time limit [sec] (Map guardian, dry fingerless) */
    float limitationTime_Guardian;

    /* 制限時間（マップ守護・指あり）
     *   制限時間[sec]（マップ守護・干からびた指有）
     * Limitation Time - Guardian (Dried Finger)
     *   Time limit [sec] (Map guardian / dry finger) */
    float limitationTime_GuardianDriedFinger;
} er_white_sign_cool_time_param_t;
