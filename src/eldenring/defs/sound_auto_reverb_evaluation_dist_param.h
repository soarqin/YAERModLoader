#pragma once

typedef struct sound_auto_reverb_evaluation_dist_param_s {
    /* NoHitとする距離[m]
     *   この距離[m]以上の衝突点をNoHitとして判定する(0より小さい:無効)
     * No Hit Distance
     *   Collision points above this distance [m] are judged as No Hit (less than 0: invalid)
     * Default Value  = -1 */
    float NoHitDist;

    /* NoHitの衝突点含めるか？
     *   NoHitの衝突点含めるか？
     * Include Collision Point of No Hit
     *   Do you include NoHit collision points? */
    unsigned char isCollectNoHitPoint;

    /* 屋外の衝突点含めるか？
     *   屋外の衝突点含めるか？
     * Include Outdoor Collision Point
     *   Do you include outdoor collision points? */
    unsigned char isCollectOutdoorPoint;

    /* 床の衝突点含めるか？
     *   床の衝突点含めるか？
     * Include Floor Collision Point
     *   Do you include floor collision points? */
    unsigned char isCollectFloorPoint;

    /* 評価距離計算タイプ
     *   評価距離計算タイプ(0:通常,1:Maxからの平均)
     * Evaluation Distance Calculation Type
     *   Evaluation distance calculation type (0: normal, average from 1: Max) */
    unsigned char distValCalcType;

    /* 有効な衝突点寿命[秒]
     *   この寿命[秒]以上の衝突点は無効扱いにする。共通設定の寿命以下に設定すること
     * Invalidate after Duration
     *   Collision points longer than this life [second] are treated as invalid. Set to be less than or equal to the life of the common setting
     * Default Value  = -1 */
    float enableLifeTime;

    /* Max衝突点レコード数
     *   Max衝突点レコード数
     * Max Collision Point Count
     *   Max Number of collision point records
     * Default Value  = 20 */
    unsigned int maxDistRecordNum;

    /* Max距離間引き数
     *   Max距離間引き数(0:間引かない)(「Max衝突点レコード数-1」の値に設定する必要がある。不正な値は修正される)
     * Max Distance until Ignore
     *   Max distance decimation number (0: not decimation) (must be set to the value of Max collision point record number-1. Incorrect value will be corrected) */
    unsigned int ignoreDistNumForMax;
} sound_auto_reverb_evaluation_dist_param_t;
