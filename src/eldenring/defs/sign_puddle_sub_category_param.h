#pragma once

typedef struct sign_puddle_sub_category_param_s {
    char startPad[4];

    /* Sign Puddle Category Text ID */
    int signPuddleCategoryText;

    /* Tab ID */
    unsigned short signPuddleTabId;

    unsigned short unknown_0xa;

    char endPad[4];
} sign_puddle_sub_category_param_t;
