#pragma once

typedef struct cool_time_param_s {
    /* 制限時間（協力霊数0）
     *   制限時間[sec]（協力霊数0）
     * Limitation Time - 0 Co-op Phantoms
     *   Time limit [sec] (number of cooperating spirits 0) */
    float limitationTime_0;

    /* 監視時間（協力霊数0）
     *   監視時間[sec]（協力霊数0）
     * Observation Time - 0 Co-op Phantoms
     *   Monitoring time [sec] (number of cooperating spirits 0) */
    float observeTime_0;

    /* 制限時間（協力霊数1）
     *   制限時間[sec]（協力霊数1）
     * Limitation Time - 1 Co-op Phantoms
     *   Time limit [sec] (number of cooperating spirits 1) */
    float limitationTime_1;

    /* 監視時間（協力霊数1）
     *   監視時間[sec]（協力霊数1）
     * Observation Time - 1 Co-op Phantoms
     *   Monitoring time [sec] (number of cooperating spirits 1) */
    float observeTime_1;

    /* 制限時間（協力霊数2）
     *   制限時間[sec]（協力霊数2）
     * Limitation Time - 2 Co-op Phantoms
     *   Time limit [sec] (number of cooperating spirits 2) */
    float limitationTime_2;

    /* 監視時間（協力霊数2）
     *   監視時間[sec]（協力霊数2）
     * Observation Time - 2 Co-op Phantoms
     *   Monitoring time [sec] (number of cooperating spirits 2) */
    float observeTime_2;

    /* 制限時間（協力霊数3）
     *   制限時間[sec]（協力霊数3）
     * Limitation Time - 3 Co-op Phantoms
     *   Time limit [sec] (number of cooperating spirits 3) */
    float limitationTime_3;

    /* 監視時間（協力霊数3）
     *   監視時間[sec]（協力霊数3）
     * Observation Time - 3 Co-op Phantoms
     *   Monitoring time [sec] (number of cooperating spirits 3) */
    float observeTime_3;
} cool_time_param_t;
