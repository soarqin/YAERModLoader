#pragma once

typedef struct er_wet_aspect_param_s {
    /* ベースカラー 値R
     *   ベースカラー色Rです。
     * Base Color: R
     *   Base color color R. */
    unsigned char baseColorR;

    /* ベースカラー 値G
     *   ベースカラー色Gです。
     * Base Color: G
     *   Base color color G. */
    unsigned char baseColorG;

    /* ベースカラー 値B
     *   ベースカラー色Bです。
     * Base Color: B
     *   Base color color B. */
    unsigned char baseColorB;

    /* 予備1 */
    char reserve_0[1];

    /* ベースカラー ％
     *   ベースカラーのオーバーライド率です。 
     * Base Color: Alpha
     *   Base color override rate. */
    float baseColorA;

    /* メタリック 値
     *   メタリックです。
     * Metallic
     *   It's metallic. */
    unsigned char metallic;

    /* 予備2 */
    char reserve_1[1];

    /* 予備3 */
    char reserve_2[1];

    /* 予備4 */
    char reserve_3[1];

    /* メタリック ％
     *   メタリックのオーバーライド率です。
     * Metallic Override Rate
     *   Metallic override rate. */
    float metallicRate;

    /* シャイニネス ％
     *   シャイニネスのオーバーライド率です。
     * Shininess Override Rate
     *   Shininess override rate. */
    float shininessRate;

    /* シャイニネス 値
     *   シャイニネスです。 
     * Shininess
     *   Shininess. */
    unsigned char shininess;

    /* 予備5 */
    char reserve_4[11];
} er_wet_aspect_param_t;
