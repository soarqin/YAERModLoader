#pragma once

typedef struct camera_fade_param_s {
    /* 透明になりきる距離(m)
     *   Nearフェード最小距離(m) : α = 0になる距離
     * Proximity Fade: Minimum Near Distance
     *   Near Fade minimum distance (m): Distance where  = 0 */
    float NearMinDist;

    /* 透明になり始める距離(m)
     *   Nearフェード最大距離(m) : α = MiddelAlphaとなる間の開始距離
     * Proximity Fade: Maximum Near Distance
     *   Near fade maximum distance (m): Starting distance between  = Middel Alpha */
    float NearMaxDist;

    /* 半透明状態になりきる距離(m)
     *   Farフェードの最小距離(m) : α = MiddleAlphaとなる間の終了距離
     * Proximity Fade: Minimum Far Distance
     *   Minimum distance of Far fade (m): End distance between  = Middle Alpha */
    float FarMinDist;

    /* 半透明状態になり始める距離(m)
     *   Farフェードの最大距離(m) : α = 1になる距離
     * Proximity Fade: Maximum Far Distance
     *   Maximum Far Fade Distance (m): Distance where  = 1 */
    float FarMaxDist;

    /* 半透明状態の濃さ(α値)
     *   中間のα値
     * Proximity Fade: Alpha
     *   Intermediate  value */
    float MiddleAlpha;

    /* ダミー */
    char dummy[12];
} camera_fade_param_t;
