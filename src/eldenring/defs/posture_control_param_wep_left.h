#pragma once

typedef struct er_posture_control_param_wep_left_s {
    /* 左腕_前後
     *   左腕_前後
     * [a000] Left Arm - Front/Back
     *   Left arm_front and back */
    short a000_leftArmFB;

    /* 左手首_前後
     *   左手首_前後
     * [a000] Left Wrist - Front/Back
     *   Left wrist_front and back */
    short a000_leftWristFB;

    /* 左手首_内外
     *   左手首_内外
     * [a000] Left Wrist - Inside/Outside
     *   Left wrist_inside and outside */
    short a000_leftWristIO;

    /* 左腕_前後
     *   左腕_前後
     * [a000] Left Weapon Rotation */
    short a000_leftWeaponRotation;

    /* 左手首_前後
     *   左手首_前後
     * [a002] Left Arm - Front/Back
     *   Left arm_front and back */
    short a002_leftArmFB;

    /* 左手首_内外
     *   左手首_内外
     * [a002] Left Wrist - Front/Back
     *   Left wrist_front and back */
    short a002_leftWristFB;

    /* 左腕_前後
     *   左腕_前後
     * [a002] Left Wrist - Inside/Outside
     *   Left wrist_inside and outside */
    short a002_leftWristIO;

    /* 左手首_前後
     *   左手首_前後
     * [a002] Left Weapon Rotation */
    short a002_leftWeaponRotation;

    /* 左手首_内外
     *   左手首_内外
     * [a003] Left Arm - Front/Back
     *   Left arm_front and back */
    short a003_leftArmFB;

    /* [a003] Left Wrist - Front/Back
     *   Left wrist_front and back */
    short a003_leftWristFB;

    /* [a003] Left Wrist - Inside/Outside
     *   Left wrist_inside and outside */
    short a003_leftWristIO;

    /* [a003] Left Weapon Rotation */
    short a003_leftWeaponRotation;

    char pad[8];
} er_posture_control_param_wep_left_t;
