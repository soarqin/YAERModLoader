#pragma once

/* Provides growth functions for various mechanics. Handles all stat scaling. */
typedef struct cacl_correct_graph_s {
    /* 閾値ポイント0
     *   仕様書に「n次閾値[point]」と書いてあるもの
     * Threshold Point [0]
     *   Stat Level Cap corresponds to the level of a certain stat */
    float stageMaxVal0;

    /* 閾値ポイント1
     *   仕様書に「n次閾値[point]」と書いてあるもの
     * Threshold Point [1]
     *   Stage cap corresponds to the level of a certain stat */
    float stageMaxVal1;

    /* 閾値ポイント2
     *   仕様書に「n次閾値[point]」と書いてあるもの
     * Threshold Point [2]
     *   Stage cap corresponds to the level of a certain stat */
    float stageMaxVal2;

    /* 閾値ポイント3
     *   仕様書に「n次閾値[point]」と書いてあるもの
     * Threshold Point [3]
     *   Stage cap corresponds to the level of a certain stat */
    float stageMaxVal3;

    /* 閾値ポイント4
     *   仕様書に「n次閾値[point]」と書いてあるもの
     * Threshold Point [4]
     *   Stage cap corresponds to the level of a certain stat */
    float stageMaxVal4;

    /* 閾値係数0
     *   仕様書に「n次閾値[係数]」と書いてあるもの
     * Threshold Coefficient [0]
     *   Stage growth is a multiplier of the maximum growth that will occur in a certain stage, as an example a chart such as this:\nGrowth Stage 0 - Growth = 20 - 20%% of the total scaling is reached at stage 0.\nGrowth Stage 1 - Growth = 25 - 25%% of the total scaling is reached at stage 1.\nGrowth Stage 2 - Growth = 50 - 50%% of the total scaling is reached at stage 2.\nGrowth Stage 3 - Growth = 80 - 80%% of the total scaling is reached at stage 3.\nGrowth Stage 4 - Growth = 90 - 90%% of the total scaling is reached at stage 4.\nAs you can see, in this specific chart 100%% is never reached, 100%% could be reached if only the value of growth stage 4 was 100%\nThis is not limited to 100%% as an example growth stage 4 could reach 200%%.\nThe level cap of a growth stage is specified in the corresponding Stat Level Cap Field */
    float stageMaxGrowVal0;

    /* 閾値係数1
     *   仕様書に「n次閾値[係数]」と書いてあるもの
     * Threshold Coefficient [1]
     *   Stage growth is a multiplier of the maximum growth that will occur in a certain stage, as an example a chart such as this:\nGrowth Stage 0 - Growth = 20 - 20%% of the total scaling is reached at stage 0.\nGrowth Stage 1 - Growth = 25 - 25%% of the total scaling is reached at stage 1.\nGrowth Stage 2 - Growth = 50 - 50%% of the total scaling is reached at stage 2.\nGrowth Stage 3 - Growth = 80 - 80%% of the total scaling is reached at stage 3.\nGrowth Stage 4 - Growth = 90 - 90%% of the total scaling is reached at stage 4.\nAs you can see, in this specific chart 100%% is never reached, 100%% could be reached if only the value of growth stage 4 was 100%\nThis is not limited to 100%% as an example growth stage 4 could reach 200%%.\nThe level cap of a growth stage is specified in the corresponding Stat Level Cap Field */
    float stageMaxGrowVal1;

    /* 閾値係数2
     *   仕様書に「n次閾値[係数]」と書いてあるもの
     * Threshold Coefficient [2]
     *   Stage growth is a multiplier of the maximum growth that will occur in a certain stage, as an example a chart such as this:\nGrowth Stage 0 - Growth = 20 - 20%% of the total scaling is reached at stage 0.\nGrowth Stage 1 - Growth = 25 - 25%% of the total scaling is reached at stage 1.\nGrowth Stage 2 - Growth = 50 - 50%% of the total scaling is reached at stage 2.\nGrowth Stage 3 - Growth = 80 - 80%% of the total scaling is reached at stage 3.\nGrowth Stage 4 - Growth = 90 - 90%% of the total scaling is reached at stage 4.\nAs you can see, in this specific chart 100%% is never reached, 100%% could be reached if only the value of growth stage 4 was 100%\nThis is not limited to 100%% as an example growth stage 4 could reach 200%%.\nThe level cap of a growth stage is specified in the corresponding Stat Level Cap Field */
    float stageMaxGrowVal2;

    /* 閾値係数3
     *   仕様書に「n次閾値[係数]」と書いてあるもの
     * Threshold Coefficient [3]
     *   Stage growth is a multiplier of the maximum growth that will occur in a certain stage, as an example a chart such as this:\nGrowth Stage 0 - Growth = 20 - 20%% of the total scaling is reached at stage 0.\nGrowth Stage 1 - Growth = 25 - 25%% of the total scaling is reached at stage 1.\nGrowth Stage 2 - Growth = 50 - 50%% of the total scaling is reached at stage 2.\nGrowth Stage 3 - Growth = 80 - 80%% of the total scaling is reached at stage 3.\nGrowth Stage 4 - Growth = 90 - 90%% of the total scaling is reached at stage 4.\nAs you can see, in this specific chart 100%% is never reached, 100%% could be reached if only the value of growth stage 4 was 100%\nThis is not limited to 100%% as an example growth stage 4 could reach 200%%.\nThe level cap of a growth stage is specified in the corresponding Stat Level Cap Field */
    float stageMaxGrowVal3;

    /* 閾値係数4
     *   仕様書に「n次閾値[係数]」と書いてあるもの
     * Threshold Coefficient [4]
     *   Stage growth is a multiplier of the maximum growth that will occur in a certain stage, as an example a chart such as this:\nGrowth Stage 0 - Growth = 20 - 20%% of the total scaling is reached at stage 0.\nGrowth Stage 1 - Growth = 25 - 25%% of the total scaling is reached at stage 1.\nGrowth Stage 2 - Growth = 50 - 50%% of the total scaling is reached at stage 2.\nGrowth Stage 3 - Growth = 80 - 80%% of the total scaling is reached at stage 3.\nGrowth Stage 4 - Growth = 90 - 90%% of the total scaling is reached at stage 4.\nAs you can see, in this specific chart 100%% is never reached, 100%% could be reached if only the value of growth stage 4 was 100%\nThis is not limited to 100%% as an example growth stage 4 could reach 200%%.\nThe level cap of a growth stage is specified in the corresponding Stat Level Cap Field */
    float stageMaxGrowVal4;

    /* 調整係数0
     *   調整係数
     * Adjustment Factor [0]
     *   Determines the exponent used to calculate the curve.\nThe growth values are normalised to be between the level range and the growth range dictated,\nSuch that: \n0 level is the lower bound of the stage, and 1 level is the upper bound\n0 growth is the lower bound of the stage, and 1 growth is the upper bound\nThis curve is, at a value of 1, linear, meaning direct proportion between each stage.\nAt a value of 2, it is quadratic (in fact, it will be flat exactly at 0, and have steepness 2 at 1)\nNote that a steepness of 2 means the growth per level is double the average growth per level.\nAt a value of 0.5, it is a square root.\nBelow 0, negative powers are not used as this would create asymptotes and infinite values.\nInstead, the axes are flipped. If you consider the graph 0 to 1 by 0 to 1, it is rotated 180 degrees.\nAt a value of -1, it is linear again.\nAt a value of -2, it is quadratic, however the origin is at the upper bound.\nNote this means there is a steepness of 2 at the lower bound and it is flat at the upper bound.\nAt a value of -0.5, it is a square root graph again, but rotated 180. */
    float adjPt_maxGrowVal0;

    /* 調整係数1
     *   調整係数
     * Adjustment Factor [1]
     *   Determines the exponent used to calculate the curve.\nThe growth values are normalised to be between the level range and the growth range dictated,\nSuch that: \n0 level is the lower bound of the stage, and 1 level is the upper bound\n0 growth is the lower bound of the stage, and 1 growth is the upper bound\nThis curve is, at a value of 1, linear, meaning direct proportion between each stage.\nAt a value of 2, it is quadratic (in fact, it will be flat exactly at 0, and have steepness 2 at 1)\nNote that a steepness of 2 means the growth per level is double the average growth per level.\nAt a value of 0.5, it is a square root.\nBelow 0, negative powers are not used as this would create asymptotes and infinite values.\nInstead, the axes are flipped. If you consider the graph 0 to 1 by 0 to 1, it is rotated 180 degrees.\nAt a value of -1, it is linear again.\nAt a value of -2, it is quadratic, however the origin is at the upper bound.\nNote this means there is a steepness of 2 at the lower bound and it is flat at the upper bound.\nAt a value of -0.5, it is a square root graph again, but rotated 180. */
    float adjPt_maxGrowVal1;

    /* 調整係数2
     *   調整係数
     * Adjustment Factor [2]
     *   Determines the exponent used to calculate the curve.\nThe growth values are normalised to be between the level range and the growth range dictated,\nSuch that: \n0 level is the lower bound of the stage, and 1 level is the upper bound\n0 growth is the lower bound of the stage, and 1 growth is the upper bound\nThis curve is, at a value of 1, linear, meaning direct proportion between each stage.\nAt a value of 2, it is quadratic (in fact, it will be flat exactly at 0, and have steepness 2 at 1)\nNote that a steepness of 2 means the growth per level is double the average growth per level.\nAt a value of 0.5, it is a square root.\nBelow 0, negative powers are not used as this would create asymptotes and infinite values.\nInstead, the axes are flipped. If you consider the graph 0 to 1 by 0 to 1, it is rotated 180 degrees.\nAt a value of -1, it is linear again.\nAt a value of -2, it is quadratic, however the origin is at the upper bound.\nNote this means there is a steepness of 2 at the lower bound and it is flat at the upper bound.\nAt a value of -0.5, it is a square root graph again, but rotated 180. */
    float adjPt_maxGrowVal2;

    /* 調整係数3
     *   調整係数
     * Adjustment Factor [3]
     *   Determines the exponent used to calculate the curve.\nThe growth values are normalised to be between the level range and the growth range dictated,\nSuch that: \n0 level is the lower bound of the stage, and 1 level is the upper bound\n0 growth is the lower bound of the stage, and 1 growth is the upper bound\nThis curve is, at a value of 1, linear, meaning direct proportion between each stage.\nAt a value of 2, it is quadratic (in fact, it will be flat exactly at 0, and have steepness 2 at 1)\nNote that a steepness of 2 means the growth per level is double the average growth per level.\nAt a value of 0.5, it is a square root.\nBelow 0, negative powers are not used as this would create asymptotes and infinite values.\nInstead, the axes are flipped. If you consider the graph 0 to 1 by 0 to 1, it is rotated 180 degrees.\nAt a value of -1, it is linear again.\nAt a value of -2, it is quadratic, however the origin is at the upper bound.\nNote this means there is a steepness of 2 at the lower bound and it is flat at the upper bound.\nAt a value of -0.5, it is a square root graph again, but rotated 180. */
    float adjPt_maxGrowVal3;

    /* 調整係数4
     *   調整係数
     * Adjustment Factor [4]
     *   This value is not used. */
    float adjPt_maxGrowVal4;

    /* 成長ソウル 初期のグラフの傾きα1
     *   成長ソウル 初期のグラフの傾きα1
     * Leveling Cost - Initial Cost
     *   Growth Soul Slope of the early graph 1 */
    float init_inclination_soul;

    /* 成長ソウル 初期のsoul調整α2
     *   成長ソウル 初期のsoul調整α2
     * Leveling Cost - Initial Offset
     *   Growth soul Early soul adjustment 2 */
    float adjustment_value;

    /* 成長ソウル 閾値後のグラフの傾きに影響α3
     *   成長ソウル 閾値後のグラフの傾きに影響α3
     * Leveling Cost - Cost Increase
     *   Affects the slope of the graph after the growth soul threshold 3 */
    float boundry_inclination_soul;

    /* 成長ソウル 閾値 t
     *   成長ソウル 閾値 t
     * Leveling Cost - Increase Interval
     *   Growth soul threshold t */
    float boundry_value;

    /* パディング */
    char pad[4];
} cacl_correct_graph_t;
