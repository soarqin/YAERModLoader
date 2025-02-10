#pragma once

/* PvP corrections */
typedef struct final_damage_rate_param_s {
    /* Physical Rate
     *   Unk
     * Damage %: Physical */
    float physRate;

    /* Magic Rate
     *   Unk
     * Damage %: Magic */
    float magRate;

    /* Fire Rate
     *   Unk
     * Damage %: Fire */
    float fireRate;

    /* Lightning Rate
     *   Unk
     * Damage %: Lightning */
    float thunRate;

    /* Dark Rate
     *   Unk
     * Damage %: Holy */
    float darkRate;

    /* Stamina Rate
     *   Unk
     * Damage %: Stamina */
    float staminaRate;

    /* Super Armor Rate
     *   Unk
     * Damage %: Poise */
    float saRate;
} final_damage_rate_param_t;
