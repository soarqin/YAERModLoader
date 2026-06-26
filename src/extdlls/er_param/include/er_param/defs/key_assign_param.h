#pragma once

typedef struct er_key_assign_param_s {
    /* パッド
     *   パッド（物理キー）
     * Pad Key ID
     *   Pad (physical key)
     * Default Value  = -1 */
    int padKeyId;

    /* キーボード修飾
     *   キーボード修飾キー
     * Keyboard Modify Key
     *   Keyboard modifier keys */
    int keyboardModifyKey;

    /* キーボード
     *   キーボード（物理キー）
     * Keyboard Key ID
     *   Keyboard (physical keys)
     * Default Value  = -1 */
    int keyboardKeyId;

    /* マウス修飾
     *   マウス修飾キー
     * Mouse Modify Key
     *   Mouse modifier key */
    int mouseModifyKey;

    /* マウス
     *   マウス（物理キー）
     * Mouse Key ID
     *   Mouse (physical key) */
    int mouseKeyId;

    /* ---- */
    char reserved[12];
} er_key_assign_param_t;
