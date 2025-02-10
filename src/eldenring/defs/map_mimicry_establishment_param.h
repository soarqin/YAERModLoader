#pragma once

typedef struct map_mimicry_establishment_param_s {
    /* 擬態重み0
     *   擬態重み0
     * Mimicry Weight [0]
     *   Mimicry weight 0
     * Default Value  = -1 */
    float mimicryEstablishment0;

    /* 擬態重み1
     *   擬態重み1
     * Mimicry Weight [1]
     *   Mimicry weight 1
     * Default Value  = -1 */
    float mimicryEstablishment1;

    /* 擬態重み2
     *   擬態重み2
     * Mimicry Weight [2]
     *   Mimicry weight 2
     * Default Value  = -1 */
    float mimicryEstablishment2;

    /* 擬態0 SFXID 前振り
     *   擬態0 SFXID 前振り
     * Mimicry - Init SFX ID [0]
     *   Mimicry 0 SFXID Forward swing
     * Default Value  = -1 */
    int mimicryBeginSfxId0;

    /* 擬態0 SFXID 本体
     *   擬態0 SFXID 本体
     * Mimicry - Midst SFX ID [0]
     *   Mimicry 0 SFXID body
     * Default Value  = -1 */
    int mimicrySfxId0;

    /* 擬態0 SFXID 解除
     *   擬態0 SFXID 解除
     * Mimicry - End SFX ID [0]
     *   Mimicry 0 SFXID release
     * Default Value  = -1 */
    int mimicryEndSfxId0;

    /* 擬態1 SFXID 前振り
     *   擬態1 SFXID 前振り
     * Mimicry - Init SFX ID [1]
     *   Mimicry 1 SFXID Forward swing
     * Default Value  = -1 */
    int mimicryBeginSfxId1;

    /* 擬態1 SFXID 本体
     *   擬態1 SFXID 本体
     * Mimicry - Midst SFX ID [1]
     *   Mimicry 1 SFXID body
     * Default Value  = -1 */
    int mimicrySfxId1;

    /* 擬態1 SFXID 解除
     *   擬態1 SFXID 解除
     * Mimicry - End SFX ID [1]
     *   Mimicry 1 SFXID release
     * Default Value  = -1 */
    int mimicryEndSfxId1;

    /* 擬態2 SFXID 前振り
     *   擬態2 SFXID 前振り
     * Mimicry - Init SFX ID [2]
     *   Mimicry 2 SFXID Forward swing
     * Default Value  = -1 */
    int mimicryBeginSfxId2;

    /* 擬態2 SFXID 本体
     *   擬態2 SFXID 本体
     * Mimicry - Midst SFX ID [2]
     *   Mimicry 2 SFXID body
     * Default Value  = -1 */
    int mimicrySfxId2;

    /* 擬態2 SFXID 解除
     *   擬態2 SFXID 解除
     * Mimicry - End SFX ID [2]
     *   Mimicry 2 SFXID cancellation
     * Default Value  = -1 */
    int mimicryEndSfxId2;

    /* パッド
     *   pad */
    char pad1[16];
} map_mimicry_establishment_param_t;
