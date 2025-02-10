#pragma once

/* Defines a pairing of Weapon and Ash of War (Gem) for use from CharaInitParam.
 * For loot and shops, change the default AoW/Gem on the weapon. */
typedef struct equip_param_custom_weapon_s {
    /* 武器ベースID
     *   武器ベースID
     * Base Weapon ID
     *   Weapon base ID */
    int baseWepId;

    /* 魔石ID
     *   魔石ID
     * Gem ID
     *   Magic stone ID */
    int gemId;

    /* 強化値
     *   強化値
     * Reinforcement Level
     *   Enhancement value */
    unsigned char reinforceLv;

    char pad[7];
} equip_param_custom_weapon_t;
