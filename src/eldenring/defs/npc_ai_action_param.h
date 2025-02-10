#pragma once

/* Associated with the NPC_ATK enum used in AI lua scripts. */
typedef struct npc_ai_action_param_s {
    /* 移動方向入力
     *   入力する移動方向
     * Move Direction
     *   Moving direction to enter */
    unsigned char moveDir;

    /* キー入力1
     *   入力するキー
     * Key [1]
     *   Key to enter */
    unsigned char key1;

    /* キー入力2
     *   入力するキー
     * Key [2]
     *   Key to enter */
    unsigned char key2;

    /* キー入力3
     *   入力するキー
     * Key [3]
     *   Key to enter */
    unsigned char key3;

    /* 移動方向入力は長押し？
     *   入力する移動方向を長押し扱いするか
     * Handle Move Direction as Long Press
     *   Whether to handle the input movement direction as long press */
    unsigned char bMoveDirHold;

    /* キー入力1は長押し？
     *   入力するキーを長押扱いするか
     * Handle Key [1] Hold as Long Press
     *   Whether to treat the key to be entered as a long press */
    unsigned char bKeyHold1;

    /* キー入力2は長押し？
     *   入力するキーを長押扱いするか
     * Handle Key [2] Hold as Long Press
     *   Whether to treat the key to be entered as a long press */
    unsigned char bKeyHold2;

    /* キー入力3は長押し？
     *   入力するキーを長押扱いするか
     * Handle Key [3] Hold as Long Press
     *   Whether to treat the key to be entered as a long press */
    unsigned char bKeyHold3;

    /* ジェスチャーID（どれかのキー入力がGESTUREの時のみ有効）
     *   ジェスチャーID
     * Gesture ID
     *   Gesture ID */
    int gestureId;

    /* 寿命が尽きた時成功扱いにする
     *   これがONならAIのゴールが寿命まで成功にならない
     * AI Goal Waits For Duration End
     *   If this is ON, the AI goal will not be successful until the end of its life */
    unsigned char bLifeEndSuccess;

    /* パッド
     *   pad */
    char pad1[3];
} npc_ai_action_param_t;
