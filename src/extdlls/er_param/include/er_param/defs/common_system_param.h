#pragma once

typedef struct er_common_system_param_s {
    /* ゲーム開始時マップ名ID_セーブデータ用
     *   ゲーム開始時マップ名ID_セーブデータ用(SEQ15052)
     * Save Data - Game Start: Map Name
     *   At the start of the game Map name ID_for save data (SEQ15052) */
    unsigned int mapSaveMapNameIdOnGameStart;

    /* リザーブ
     *   リザーブ */
    char reserve0[60];
} er_common_system_param_t;
