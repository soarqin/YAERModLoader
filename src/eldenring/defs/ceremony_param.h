#pragma once

typedef struct ceremony_param_s {
    /* イベントレイヤーID
     *   イベントメーカーのレイヤーID
     * Event Layer ID
     *   Event maker layer ID */
    int eventLayerId;

    /* MapStudioレイヤーID
     *   MapStudioのレイヤーID
     * Map Studio Layer ID
     *   Map Studio Layer ID */
    int mapStudioLayerId;

    /* マルチプレイエリアオフセット
     *   マルチプレイエリアIDのオフセット。例えば「100」と入れるとマルチプレイエリアIDが「100」オフセットされる。
     * Play Region ID Offset
     *   Multiplayer area ID offset. For example, if you enter 100, the multiplayer area ID will be offset by 100. */
    int multiPlayAreaOffset;

    /* マップ名ID上書き_地名表示
     *   マップ名ID_地名表示を指定IDに上書きする。-1:上書き無し、-2以下,0以上:そのIDに上書き。
     * Override Map Place Name ID
     *   Override the map name ID_place name display with the specified ID. -1: No overwrite, -2 or less, 0 or more: Overwrite the ID.
     * Default Value  = -1 */
    int overrideMapPlaceNameId;

    /* マップ名ID上書き_セーブデータ表示
     *   マップ名ID_セーブデータ表示を指定IDに上書きする。-1:上書き無し、-2以下,0以上:そのIDに上書き。
     * Override Save Map Name ID
     *   Map name ID_Overwrites the save data display with the specified ID. -1: No overwrite, -2 or less, 0 or more: Overwrite the ID.
     * Default Value  = -1 */
    int overrideSaveMapNameId;

    char pad2[16];
} ceremony_param_t;
