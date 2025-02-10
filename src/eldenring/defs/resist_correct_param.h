#pragma once

typedef struct resist_correct_param_s {
    /* 1回目発動後加算pt
     *   状態異常が1回発動した後に耐性値に加算される値
     * Additional Resistance - First Activation
     *   A value that is added to the resistance value after the abnormal condition is activated once. */
    float addPoint1;

    /* 2回目発動後加算pt
     *   状態異常が2回発動した後に耐性値に加算される値
     * Additional Resistance - Second Activation
     *   A value that is added to the resistance value after the abnormal condition is activated twice. */
    float addPoint2;

    /* 3回目発動後加算pt
     *   状態異常が3回発動した後に耐性値に加算される値
     * Additional Resistance - Third Activation
     *   A value that is added to the resistance value after the abnormal condition is activated 3 times. */
    float addPoint3;

    /* 4回目発動後加算pt
     *   状態異常が4回発動した後に耐性値に加算される値
     * Additional Resistance - Fourth Activation
     *   A value that is added to the resistance value after the abnormal condition is activated 4 times. */
    float addPoint4;

    /* 5回目発動後加算pt
     *   状態異常が5回発動した後に耐性値に加算される値
     * Additional Resistance - Fifth Activation
     *   A value that is added to the resistance value after the abnormal condition is activated 5 times. */
    float addPoint5;

    /* 1回目発動後倍率
     *   状態異常が1回発動した後に耐性値に掛かる倍率
     * Resistance Multiplier - First Activation
     *   Magnification applied to the resistance value after the abnormal condition is activated once
     * Default Value  = 1 */
    float addRate1;

    /* 2回目発動後倍率
     *   状態異常が2回発動した後に耐性値に掛かる倍率
     * Resistance Multiplier - Second Activation
     *   Magnification applied to the resistance value after the abnormal condition is activated twice
     * Default Value  = 1 */
    float addRate2;

    /* 3回目発動後倍率
     *   状態異常が3回発動した後に耐性値に掛かる倍率
     * Resistance Multiplier - Third Activation
     *   Magnification applied to the resistance value after the abnormal condition is activated 3 times
     * Default Value  = 1 */
    float addRate3;

    /* 4回目発動後倍率
     *   状態異常が4回発動した後に耐性値に掛かる倍率
     * Resistance Multiplier - Fourth Activation
     *   Magnification applied to the resistance value after the abnormal condition is activated 4 times
     * Default Value  = 1 */
    float addRate4;

    /* 5回目発動後倍率
     *   状態異常が5回発動した後に耐性値に掛かる倍率
     * Resistance Multiplier - Fifth Activation
     *   Magnification applied to the resistance value after the abnormal condition is activated 5 times
     * Default Value  = 1 */
    float addRate5;
} resist_correct_param_t;
