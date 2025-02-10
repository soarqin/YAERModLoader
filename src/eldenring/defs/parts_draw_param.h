#pragma once

typedef struct parts_draw_param_s {
    /* LODレベル0-1境界距離[m]
     *   切り替わる中心
     * LOD 0-1 Boundry Distance
     *   Switching center
     * Default Value  = 5 */
    float lv01_BorderDist;

    /* LODレベル0-1遊び距離[m]
     *   境界中心で±遊び
     * LOD 0-1 Play Distance
     *    play at the center of the boundary
     * Default Value  = 1 */
    float lv01_PlayDist;

    /* LODレベル1-2境界距離[m]
     *   切り替わる中心
     * LOD 1-2 Boundry Distance
     *   Switching center
     * Default Value  = 20 */
    float lv12_BorderDist;

    /* LODレベル1-2遊び距離[m]
     *   境界中心で±遊び
     * LOD 1-2 Play Distance
     *    play at the center of the boundary
     * Default Value  = 2 */
    float lv12_PlayDist;

    /* LODレベル2-3境界距離[m]
     *   切り替わる中心
     * LOD 2-3 Boundry Distance
     *   Switching center
     * Default Value  = 30 */
    float lv23_BorderDist;

    /* LODレベル2-3遊び距離[m]
     *   境界中心で±遊び
     * LOD 2-3 Play Distance
     *    play at the center of the boundary */
    float lv23_PlayDist;

    /* LODレベル3-4境界距離[m]
     *   切り替わる中心
     * LOD 3-4 Boundry Distance
     *   Switching center
     * Default Value  = 9999 */
    float lv34_BorderDist;

    /* LODレベル3-4遊び距離[m]
     *   境界中心で±遊び
     * LOD 3-4 Play Distance
     *    play at the center of the boundary */
    float lv34_PlayDist;

    /* LODレベル4-5境界距離[m]
     *   切り替わる中心
     * LOD 4-5 Boundry Distance
     *   Switching center
     * Default Value  = 9999 */
    float lv45_BorderDist;

    /* LODレベル4-5遊び距離[m]
     *   境界中心で±遊び
     * LOD 4-5 Play Distance
     *    play at the center of the boundary */
    float lv45_PlayDist;

    /* TextureLODレベル0-1境界距離[m]
     *   Texture切り替わる中心(0でTexureLOD無効)
     * Texture Switch - LOD 0-1 Boundry Distance
     *   Texture switching center (Texure LOD disabled at 0)
     * Default Value  = 30 */
    float tex_lv01_BorderDist;

    /* TextureLODレベル0-1遊び距離[m]
     *   Texture境界中心で±遊び
     * Texture Switch - LOD 0-1 Play Distance
     *   Texture Play around the boundary
     * Default Value  = 1 */
    float tex_lv01_PlayDist;

    /* クロスフェード有効
     *   クロスフェード有効か(0:無効,1:有効)
     * Enable Crossfade
     *   Is crossfade enabled (0: disabled, 1: enabled)? */
    unsigned int enableCrossFade:1;

    /* 描画距離[m]
     *   描画最大距離。オープンではアクティベート距離に利用されます
     * Draw - Max Distance
     *   Maximum drawing distance. In the open, it will be used for the activation distance
     * Default Value  = 9999 */
    float drawDist;

    /* フェード範囲[m]
     *   描画最大距離から、実際に消えるまでのフェード距離
     * Draw - Fade Range
     *   Fade distance from the maximum drawing distance to the actual disappearance */
    float drawFadeRange;

    /* 影描画距離[m]
     *   影の描画最大距離
     * Shadow Draw - Max Distance
     *   Maximum shadow drawing distance
     * Default Value  = 9999 */
    float shadowDrawDist;

    /* 影フェード範囲[m]
     *   影の描画最大距離から、実際に消えるまでのフェード距離
     * Shadow Draw - Fade Range
     *   Fade distance from the maximum shadow drawing distance to the actual disappearance */
    float shadowFadeRange;

    /* モーションブラー描画境界距離[m]
     *   モーションブラーが有効になる距離
     * Motion Blur - Max Distance
     *   Distance at which motion blur is enabled
     * Default Value  = 20 */
    float motionBlur_BorderDist;

    /* 点光源の影を落とす
     *   点光源の影を落とす
     * Is Point Light Shadow Source
     *   Cast the shadow of a point light source */
    char isPointLightShadowSrc;

    /* 平行光源の影を落とす
     *   平行光源の影を落とす
     * Is Directional Light Shadow Source
     *   Cast the shadow of a parallel light source */
    char isDirLightShadowSrc;

    /* 影を受ける
     *   影を受ける
     * Is Shadow Destination
     *   Receive a shadow */
    char isShadowDst;

    /* 影描画のみ
     *   影描画のみ
     * Is Shadow Only
     *   Shadow drawing only */
    char isShadowOnly;

    /* 映り込む
     *   映り込む
     * Drawn by Reflection Camera
     *   Reflected */
    char drawByReflectCam;

    /* 映り込み描画のみ
     *   映り込み描画のみ
     * Drawn only by Reflection Camera
     *   Reflection drawing only */
    char drawOnlyReflectCam;

    /* どのレベルのLodMapまで含めるか
     *   どのレベルのLodMapまで含めるか
     * Include LOD Map Level
     *   What level of LodMap to include
     * Default Value  = -1 */
    char IncludeLodMapLv;

    /* FarClipしない
     *   ファークリップを無効にし、常にクリップ空間の一番奥の深度に描画する。主に天球用
     * Disable Far Clip Draw
     *   Disable fur clips and always draw at the innermost depth of the clip space. Mainly for celestial sphere */
    unsigned char isNoFarClipDraw;

    /* LODタイプ
     *   LOD対象の種類、大きさ
     * LOD Type
     *   Type and size of LOD target */
    unsigned char lodType;

    /* 影描画LODレベルオフセット
     *   影描画時のLODレベルオフセット値
     * Shadow Draw LOD Offset
     *   LOD level offset value when drawing shadows */
    char shadowDrawLodOffset;

    /* カメラをXZ平面上で追従する
     *   カメラをXZ平面上で追従する(GR SEQ09242)
     * Follow Camera on XZ Plane
     *   Follow the camera on the XZ plane (GR SEQ09242) */
    unsigned char isTraceCameraXZ;

    /* 天球描画フェイズに切り替え
     *   描画フェイズを天球に設定する(GR SEQ09242)
     * Is Celestial Sphere Draw Phase
     *   Set the drawing phase to the celestial sphere (GR SEQ09242) */
    unsigned char isSkydomeDrawPhase;

    /* 遠景切り替え距離[m]
     *   遠景切り替え距離[m]
     * Distant LOD - Boundry Distance
     *   Distance switching distance [m]
     * Default Value  = 30 */
    float DistantViewModel_BorderDist;

    /* 遠景切り替え遊び距離[m]
     *   遠景切り替え遊び距離[m]
     * Distant LOD - Play Distance
     *   Distant view switching play distance [m]
     * Default Value  = 5 */
    float DistantViewModel_PlayDist;

    /* オープン用構築制限距離[m]
     *   オープン用構築制限距離[m]。オープンにおいてカメラとの距離がこの距離未満だと構築されないようになります。遠景アセット用の機能です。-1:機能無効(デフォルト)
     * Open-world - Minimum Boundry Distance
     *   Construction limit distance for open [m]. If the distance to the camera is less than this distance in the open, it will not be built. This is a function for distant view assets. -1: Function disabled (default)
     * Default Value  = -1 */
    float LimtedActivate_BorderDist_forGrid;

    /* オープン用構築制限遊び距離[m]
     *   オープン構築制限遊び距離[m]
     * Open-world - Minimum Play Distance
     *   Open construction limit play distance [m]
     * Default Value  = 10 */
    float LimtedActivate_PlayDist_forGrid;

    /* Zソートオフセット
     *   同じ描画フェーズ内でカメラからの距離が同じ場合、半透明系は小さいほうが手前、不透明系は値が大きいほうが手前に描画されます。 オフセットの基点は天球描画フェーズのものは原点。それ以外はModelAABB中心。(GR SEQ09242)
     * Z Sort Offset for No Far Clip Draw
     *   If the distance from the camera is the same in the same drawing phase, the smaller translucent system is drawn in the foreground, and the opaque system is drawn in the larger value. The base point of the offset is the origin in the celestial sphere drawing phase. Other than that, it is mainly Model AABB. (GR SEQ09242) */
    float zSortOffsetForNoFarClipDraw;

    /* 影描画アルファテスト有効距離[m]
     *   影描画時にアルファテストを行う距離[m]
     * Shadow Draw Alpha Test Distance
     *   Distance to perform alpha test when drawing shadow [m]
     * Default Value  = 9999 */
    float shadowDrawAlphaTestDist;

    /* Forward描画物の環境マップブレンドタイプ
     *   Forward描画物の環境マップブレンドタイプ
     * Forward Draw Envmap Blend Type
     *   Forward Drawing environment map Blend type */
    unsigned char fowardDrawEnvmapBlendType;

    /* 描画距離スケールパラメータID
     *   ロードバランサー描画距離スケールパラメータID
     * Load Balancer - Draw Distance Scale Param ID
     *   Load balancer drawing distance scale parameter ID */
    unsigned char LBDrawDistScaleParamID;

    /* 予約
     *   予約 */
    char resereve[34];
} parts_draw_param_t;
