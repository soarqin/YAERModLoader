#pragma once

typedef struct se_activation_range_param_s {
    /* アクティベート距離
     *   配置SEを有効化する距離(m) (0以下：常に有効化)
     * Activation Range
     *   Distance to enable placement SE (m) (0 or less: always enabled) */
    float activateRange;
} se_activation_range_param_t;
