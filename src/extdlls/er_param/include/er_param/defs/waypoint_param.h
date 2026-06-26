#pragma once

typedef struct er_waypoint_param_s {
    /* 属性1
     * Attribute [1]
     * Default Value  = -1 */
    short attribute1;

    /* 属性2
     * Attribute [2]
     * Default Value  = -1 */
    short attribute2;

    /* 属性3
     * Attribute [3]
     * Default Value  = -1 */
    short attribute3;

    /* 属性4
     * Attribute [4]
     * Default Value  = -1 */
    short attribute4;

    /* パディング4 */
    char padding4[8];
} er_waypoint_param_t;
