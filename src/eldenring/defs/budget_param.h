#pragma once

typedef struct budget_param_s {
    /* VRAM:ALL
     *   VRAM:ALL(単位はMB)
     * VRAM: ALL
     *   VRAM: ALL (unit is MB)
     * Default Value  = 1 */
    float vram_all;

    /* VRAM:マップ/オブジェ テクスチャ
     *   VRAM:マップ/オブジェ テクスチャ(単位はMB)
     * VRAM: Map / Object Texture
     *   VRAM: Map / Object Texture (Unit: MB)
     * Default Value  = 1 */
    float vram_mapobj_tex;

    /* VRAM:マップ/オブジェ モデル
     *   VRAM:マップ/オブジェ モデル(単位はMB)
     * VRAM: Map / Object Model
     *   VRAM: Map / object model (in MB)
     * Default Value  = 1 */
    float vram_mapobj_mdl;

    /* VRAM:マップ
     *   VRAM:マップ(単位はMB)
     * VRAM: map
     *   VRAM: Map (in MB)
     * Default Value  = 1 */
    float vram_map;

    /* VRAM:キャラ
     *   VRAM:キャラ(単位はMB)
     * VRAM: Character
     *   VRAM: Character (unit is MB)
     * Default Value  = 1 */
    float vram_chr;

    /* VRAM:パーツ
     *   VRAM:パーツ(単位はMB)
     * VRAM: Parts
     *   VRAM: Parts (unit is MB)
     * Default Value  = 1 */
    float vram_parts;

    /* VRAM:SFX
     *   VRAM:SFX(単位はMB)
     * VRAM: SFX
     *   VRAM: SFX (unit is MB)
     * Default Value  = 1 */
    float vram_sfx;

    /* VRAM:キャラ テクスチャ
     *   VRAM:キャラ テクスチャ(単位はMB)
     * VRAM: Character texture
     *   VRAM: Character texture (unit is MB)
     * Default Value  = 1 */
    float vram_chr_tex;

    /* VRAM:キャラ モデル
     *   VRAM:キャラ モデル(単位はMB)
     * VRAM: Character model
     *   VRAM: Character model (unit is MB)
     * Default Value  = 1 */
    float vram_chr_mdl;

    /* VRAM:パーツ テクスチャ
     *   VRAM:パーツ テクスチャ(単位はMB)
     * VRAM: Parts texture
     *   VRAM: Parts texture (unit is MB)
     * Default Value  = 1 */
    float vram_parts_tex;

    /* VRAM:パーツ モデル
     *   VRAM:パーツ モデル(単位はMB)
     * VRAM: Parts model
     *   VRAM: Parts model (unit is MB)
     * Default Value  = 1 */
    float vram_parts_mdl;

    /* VRAM:SFX テクスチャ
     *   VRAM:SFX テクスチャ(単位はMB)
     * VRAM: SFX texture
     *   VRAM: SFX texture (unit is MB)
     * Default Value  = 1 */
    float vram_sfx_tex;

    /* VRAM:SFX モデル
     *   VRAM:SFX モデル(単位はMB)
     * VRAM: SFX model
     *   VRAM: SFX model (in MB)
     * Default Value  = 1 */
    float vram_sfx_mdl;

    /* VRAM:Gi
     *   VRAM:Gi(単位はMB)
     * VRAM: Gi
     *   VRAM: Gi (unit is MB)
     * Default Value  = 1 */
    float vram_gi;

    /* VRAM:メニュー
     *   VRAM:メニュー(単位はMB)
     * VRAM: Menu
     *   VRAM: Menu (unit is MB)
     * Default Value  = 1 */
    float vram_menu_tex;

    /* VRAM:DECAL_RT
     *   VRAM:DECALレンダーターゲット(単位はMB)
     * VRAM: DECAL_RT
     *   VRAM: DECAL render target (unit is MB)
     * Default Value  = 1 */
    float vram_decal_rt;

    /* VRAM:DECAL
     *   VRAM:DECAL(単位はMB)
     * VRAM: DECAL
     *   VRAM: DECAL (unit is MB)
     * Default Value  = 1 */
    float vram_decal;

    /* 予約領域 */
    char reserve_0[4];

    /* VRAM:その他 テクスチャ
     *   VRAM:その他 モデル(単位はMB)
     * VRAM: Other textures
     *   VRAM: Other models (in MB)
     * Default Value  = 1 */
    float vram_other_tex;

    /* VRAM:その他 モデル
     *   VRAM:その他 テクスチャ(単位はMB)
     * VRAM: Other models
     *   VRAM: Other textures (in MB)
     * Default Value  = 1 */
    float vram_other_mdl;

    /* HAVOK:アニメ
     *   HAVOK:アニメ(単位はMB)
     * HAVOK: Animation
     *   HAVOK: Animation (unit is MB)
     * Default Value  = 1 */
    float havok_anim;

    /* HAVOK:配置
     *   HAVOK:配置(単位はMB)
     * HAVOK: Placement
     *   HAVOK: Placement (unit is MB)
     * Default Value  = 1 */
    float havok_ins;

    /* HAVOK:ヒット
     *   HAVOK:ヒット(単位はMB)
     * HAVOK: Hit
     *   HAVOK: Hit (unit is MB)
     * Default Value  = 1 */
    float havok_hit;

    /* VRAM:その他
     *   VRAM:その他(単位はMB)
     * VRAM: Other
     *   VRAM: Other (unit is MB)
     * Default Value  = 1 */
    float vram_other;

    /* VRAM:合算値
     *   VRAM:合算値(単位はMB)
     * VRAM: Total Value
     *   VRAM: Total value (unit is MB)
     * Default Value  = 1 */
    float vram_detail_all;

    /* VRAM:キャラ&パーツ
     *   VRAM:キャラとパーツ合算値(単位はMB)
     * VRAM: Characters and Parts
     *   VRAM: Total value of characters and parts (unit is MB)
     * Default Value  = 1 */
    float vram_chr_and_parts;

    /* HAVOK:ナビメッシュ
     *   HAVOK:ナビメッシュ(単位はMB)
     * HAVOK: Navimesh
     *   HAVOK: Navimesh (unit is MB)
     * Default Value  = 1 */
    float havok_navimesh;

    /* 予約領域
     *   予約領域 */
    char reserve_1[24];
} budget_param_t;
