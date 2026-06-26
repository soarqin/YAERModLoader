#pragma once

typedef struct er_graphics_common_param_s {
    /* HIT INSに弾丸が当たった時のデカール発生位置オフセット
     *   HIT INSに当たった時に発生するデカールの発生位置を法線方向にこの値だけオフセットする
     * Hit Bullet Decal Offset - Hit INS
     *   The position where the decal that occurs when hitting HIT INS is offset by this value in the normal direction.
     * Default Value  = 0.05 */
    float hitBulletDecalOffset_HitIns;

    /* 予約
     *   (dummy8) */
    char reserved02[8];

    /* キャラが濡れた時のデカールフェード範囲[m]
     *   キャラが濡れた時にデカールを消すフェード範囲[m]
     * Character Wet Decal Fade Range
     *   Fade range that erases decals when the character gets wet [m]
     * Default Value  = 0.6 */
    float charaWetDecalFadeRange;

    /* 予約
     *   (dummy8) */
    char reserved04[240];
} er_graphics_common_param_t;
