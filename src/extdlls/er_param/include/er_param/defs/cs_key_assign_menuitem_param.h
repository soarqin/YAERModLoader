#pragma once

typedef struct er_cs_key_assign_menuitem_param_s {
    /* テキスト
     *   キー指定あり⇒項目名、1行ヘルプのID。キー指定なし⇒カテゴリ名のID。テキスト指定なし⇒パッド/キー設定に表示しない(操作一覧表示のみ)
     * Text ID
     *   Key specified  Item name, 1-line help ID. No key specified  Category name ID. No text specified  Not displayed in pad / key settings (operation list display only) */
    int textID;

    /* キー
     *   割り当て対象のユーザー入力キー。指定が無い時はカテゴリ表示用項目として扱う
     * Key
     *   User input key to be assigned. If not specified, it will be treated as a category display item.
     * Default Value  = -1 */
    int key;

    /* 解除
     *   割り当ての解除が可能か(デフォルト:可能)
     * Allow Unassignment
     *   Is it possible to unassign (default possible)
     * Default Value  = 1 */
    unsigned char enableUnassign;

    /* パッド
     *   パッド操作の割り当て変更が可能か(デフォルト:可能)
     * Allow Pad Config
     *   Is it possible to change the pad operation assignment (default possible)?
     * Default Value  = 1 */
    unsigned char enablePadConfig;

    /* マウス
     *   マウス操作の割り当て変更が可能か(デフォルト:可能)
     * Allow Mouse Config
     *   Is it possible to change the mouse operation assignment (default possible)?
     * Default Value  = 1 */
    unsigned char enableMouseConfig;

    /* グループ
     *   割り当ての重複判定用グループ。同一グループでは重複不可
     * Group
     *   Group for determining duplicate assignments. Cannot be duplicated in the same group */
    unsigned char group;

    /* テキスト
     *   操作一覧で表示する項目名。0:：一覧に表示しない
     * Mapping Text ID
     *   Item name to be displayed in the operation list. 0  Do not display in the list */
    int mappingTextID;

    /* パッド
     *   キーコンフィグ（パッド）で表示するか(デフォルト:表示)
     * View Pad
     *   Whether to display with key config (pad) (default display)
     * Default Value  = 1 */
    unsigned char viewPad;

    /* マウス・キーボード
     *   キーコンフィグ（マウス・キーボード）で表示するか(デフォルト:表示）
     * View Keyboard/Mouse
     *   Whether to display with key config (mouse / keyboard) (default display)
     * Default Value  = 1 */
    unsigned char viewKeyboardMouse;

    char padding[6];
} er_cs_key_assign_menuitem_param_t;
