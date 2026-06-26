#pragma once

typedef struct er_fe_text_effect_param_s {
    /* リソースID
     *   メニューリソースのインスタンス名。TextEffect_X のID
     * Resource ID
     *   Instance name of the menu resource. ID of TextEffect_X */
    short resId;

    /* パディング */
    char pad1[2];

    /* テキストID
     *   表示するテキストID(-1: テキストなし)。MenuText
     * Text ID
     *   Text ID to display (-1 No text). MenuText
     * Default Value  = -1 */
    int textId;

    /* SEのID
     *   再生するVoiceのID(-1: SEなし)
     * SE ID
     *   Voice ID to play (-1 No SE)
     * Default Value  = -1 */
    int seId;

    /* マップ名と同時に表示するか
     *   マップ名と同時に表示するか
     * Display Simultaneously with Map Name
     *   Whether to display at the same time as the map name */
    unsigned char canMixMapName:1;

    /* パディング */
    char pad3:7;

    /* パディング */
    char pad2[19];
} er_fe_text_effect_param_t;
