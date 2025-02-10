#pragma once

/* Governs which damage types scale with which stats. Includes correction values. */
typedef struct attack_element_correct_param_s {
    /* 筋力補正するか（物理）
     * Physical Correction: STR */
    unsigned char isStrengthCorrect_byPhysics:1;

    /* 技量補正するか（物理）
     * Physical Correction: DEX */
    unsigned char isDexterityCorrect_byPhysics:1;

    /* 理力補正するか（物理）
     * Physical Correction: INT */
    unsigned char isMagicCorrect_byPhysics:1;

    /* 信仰補正するか（物理）
     * Physical Correction: FTH */
    unsigned char isFaithCorrect_byPhysics:1;

    /* 運補正するか（物理）
     * Physical Correction: ARC */
    unsigned char isLuckCorrect_byPhysics:1;

    /* 筋力補正するか（魔法）
     * Magic Correction: STR */
    unsigned char isStrengthCorrect_byMagic:1;

    /* 技量補正するか（魔法）
     * Magic Correction: DEX */
    unsigned char isDexterityCorrect_byMagic:1;

    /* 理力補正するか（魔法）
     * Magic Correction: INT */
    unsigned char isMagicCorrect_byMagic:1;

    /* 信仰補正するか（魔法）
     * Magic Correction: FTH */
    unsigned char isFaithCorrect_byMagic:1;

    /* 運補正するか（魔法）
     * Magic Correction: ARC */
    unsigned char isLuckCorrect_byMagic:1;

    /* 筋力補正するか（炎）
     * Fire Correction: STR */
    unsigned char isStrengthCorrect_byFire:1;

    /* 技量補正するか（炎）
     * Fire Correction: DEX */
    unsigned char isDexterityCorrect_byFire:1;

    /* 理力補正するか（炎）
     * Fire Correction: INT */
    unsigned char isMagicCorrect_byFire:1;

    /* 信仰補正するか（炎）
     * Fire Correction: FTH */
    unsigned char isFaithCorrect_byFire:1;

    /* 運補正するか（炎）
     * Fire Correction: ARC */
    unsigned char isLuckCorrect_byFire:1;

    /* 筋力補正するか（雷）
     * Lightning Correction: STR */
    unsigned char isStrengthCorrect_byThunder:1;

    /* 技量補正するか（雷）
     * Lightning Correction: DEX */
    unsigned char isDexterityCorrect_byThunder:1;

    /* 理力補正するか（雷）
     * Lightning Correction: INT */
    unsigned char isMagicCorrect_byThunder:1;

    /* 信仰補正するか（雷）
     * Lightning Correction: FTH */
    unsigned char isFaithCorrect_byThunder:1;

    /* 運補正するか（雷）
     * Lightning Correction: ARC */
    unsigned char isLuckCorrect_byThunder:1;

    /* 筋力補正するか（闇）
     * Holy Correction: STR */
    unsigned char isStrengthCorrect_byDark:1;

    /* 技量補正するか（闇）
     * Holy Correction: DEX */
    unsigned char isDexterityCorrect_byDark:1;

    /* 理力補正するか（闇）
     * Holy Correction: INT */
    unsigned char isMagicCorrect_byDark:1;

    /* 信仰補正するか（闇）
     * Holy Correction: FTH */
    unsigned char isFaithCorrect_byDark:1;

    /* 運補正するか（闇）
     * Holy Correction: ARC */
    unsigned char isLuckCorrect_byDark:1;

    /* パディング */
    char pad1:7;

    /* 筋力補正値上書き（物理）
     * Physical Replacement Correction: STR
     * Default Value  = -1 */
    short overwriteStrengthCorrectRate_byPhysics;

    /* 技量補正値上書き（物理）
     * Physical Replacement Correction: DEX
     * Default Value  = -1 */
    short overwriteDexterityCorrectRate_byPhysics;

    /* 理力補正値上書き（物理）
     * Physical Replacement Correction: INT
     * Default Value  = -1 */
    short overwriteMagicCorrectRate_byPhysics;

    /* 信仰補正値上書き（物理）
     * Physical Replacement Correction: FTH
     * Default Value  = -1 */
    short overwriteFaithCorrectRate_byPhysics;

    /* 運補正値上書き（物理）
     * Physical Replacement Correction: ARC
     * Default Value  = -1 */
    short overwriteLuckCorrectRate_byPhysics;

    /* 筋力補正値上書き（魔法）
     * Magic Replacement Correction: STR
     * Default Value  = -1 */
    short overwriteStrengthCorrectRate_byMagic;

    /* 技量補正値上書き（魔法）
     * Magic Replacement Correction: DEX
     * Default Value  = -1 */
    short overwriteDexterityCorrectRate_byMagic;

    /* 理力補正値上書き（魔法）
     * Magic Replacement Correction: INT
     * Default Value  = -1 */
    short overwriteMagicCorrectRate_byMagic;

    /* 信仰補正値上書き（魔法）
     * Magic Replacement Correction: FTH
     * Default Value  = -1 */
    short overwriteFaithCorrectRate_byMagic;

    /* 運補正値上書き（魔法）
     * Magic Replacement Correction: ARC
     * Default Value  = -1 */
    short overwriteLuckCorrectRate_byMagic;

    /* 筋力補正値上書き（炎）
     * Fire Replacement Correction: STR
     * Default Value  = -1 */
    short overwriteStrengthCorrectRate_byFire;

    /* 技量補正値上書き（炎）
     * Fire Replacement Correction: DEX
     * Default Value  = -1 */
    short overwriteDexterityCorrectRate_byFire;

    /* 理力補正値上書き（炎）
     * Fire Replacement Correction: INT
     * Default Value  = -1 */
    short overwriteMagicCorrectRate_byFire;

    /* 信仰補正値上書き（炎）
     * Fire Replacement Correction: FTH
     * Default Value  = -1 */
    short overwriteFaithCorrectRate_byFire;

    /* 運補正値上書き（炎）
     * Fire Replacement Correction: ARC
     * Default Value  = -1 */
    short overwriteLuckCorrectRate_byFire;

    /* 筋力補正値上書き（雷）
     * Lightning Replacement Correction: STR
     * Default Value  = -1 */
    short overwriteStrengthCorrectRate_byThunder;

    /* 技量補正値上書き（雷）
     * Lightning Replacement Correction: DEX
     * Default Value  = -1 */
    short overwriteDexterityCorrectRate_byThunder;

    /* 理力補正値上書き（雷）
     * Lightning Replacement Correction: INT
     * Default Value  = -1 */
    short overwriteMagicCorrectRate_byThunder;

    /* 信仰補正値上書き（雷）
     * Lightning Replacement Correction: FTH
     * Default Value  = -1 */
    short overwriteFaithCorrectRate_byThunder;

    /* 運補正値上書き（雷）
     * Lightning Replacement Correction: ARC
     * Default Value  = -1 */
    short overwriteLuckCorrectRate_byThunder;

    /* 筋力補正値上書き（闇）
     * Holy Replacement Correction: STR
     * Default Value  = -1 */
    short overwriteStrengthCorrectRate_byDark;

    /* 技量補正値上書き（闇）
     * Holy Replacement Correction: DEX
     * Default Value  = -1 */
    short overwriteDexterityCorrectRate_byDark;

    /* 理力補正値上書き（闇）
     * Holy Replacement Correction: INT
     * Default Value  = -1 */
    short overwriteMagicCorrectRate_byDark;

    /* 信仰補正値上書き（闇）
     * Holy Replacement Correction: FTH
     * Default Value  = -1 */
    short overwriteFaithCorrectRate_byDark;

    /* 運補正値上書き（闇）
     * Holy Replacement Correction: ARC
     * Default Value  = -1 */
    short overwriteLuckCorrectRate_byDark;

    /* 筋力補正値影響率（物理）
     *   補正率の影響割合。
     * Physical Correction Ratio: STR
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceStrengthCorrectRate_byPhysics;

    /* 技量補正値影響率（物理）
     *   補正率の影響割合。
     * Physical Correction Ratio: DEX
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceDexterityCorrectRate_byPhysics;

    /* 理力補正値影響率（物理）
     *   補正率の影響割合。
     * Physical Correction Ratio: INT
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceMagicCorrectRate_byPhysics;

    /* 信仰補正値影響率（物理）
     *   補正率の影響割合。
     * Physical Correction Ratio: FTH
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceFaithCorrectRate_byPhysics;

    /* 運補正値影響率（物理）
     *   補正率の影響割合。
     * Physical Correction Ratio: ARC
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceLuckCorrectRate_byPhysics;

    /* 筋力補正値影響率（魔法）
     *   補正率の影響割合。
     * Magic Correction Ratio: STR
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceStrengthCorrectRate_byMagic;

    /* 技量補正値影響率（魔法）
     *   補正率の影響割合。
     * Magic Correction Ratio: DEX
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceDexterityCorrectRate_byMagic;

    /* 理力補正値影響率（魔法）
     *   補正率の影響割合。
     * Magic Correction Ratio: INT
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceMagicCorrectRate_byMagic;

    /* 信仰補正値影響率（魔法）
     *   補正率の影響割合。
     * Magic Correction Ratio: FTH
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceFaithCorrectRate_byMagic;

    /* 運補正値影響率（魔法）
     *   補正率の影響割合。
     * Magic Correction Ratio: ARC
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceLuckCorrectRate_byMagic;

    /* 筋力補正値影響率（炎）
     *   補正率の影響割合。
     * Fire Correction Ratio: STR
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceStrengthCorrectRate_byFire;

    /* 技量補正値影響率（炎）
     *   補正率の影響割合。
     * Fire Correction Ratio: DEX
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceDexterityCorrectRate_byFire;

    /* 理力補正値影響率（炎）
     *   補正率の影響割合。
     * Fire Correction Ratio: INT
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceMagicCorrectRate_byFire;

    /* 信仰補正値影響率（炎）
     *   補正率の影響割合。
     * Fire Correction Ratio: FTH
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceFaithCorrectRate_byFire;

    /* 運補正値影響率（炎）
     *   補正率の影響割合。
     * Fire Correction Ratio: ARC
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceLuckCorrectRate_byFire;

    /* 筋力補正値影響率（雷）
     *   補正率の影響割合。
     * Lightning Correction Ratio: STR
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceStrengthCorrectRate_byThunder;

    /* 技量補正値影響率（雷）
     *   補正率の影響割合。
     * Lightning Correction Ratio: DEX
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceDexterityCorrectRate_byThunder;

    /* 理力補正値影響率（雷）
     *   補正率の影響割合。
     * Lightning Correction Ratio: INT
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceMagicCorrectRate_byThunder;

    /* 信仰補正値影響率（雷）
     *   補正率の影響割合。
     * Lightning Correction Ratio: FTH
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceFaithCorrectRate_byThunder;

    /* 運補正値影響率（雷）
     *   補正率の影響割合。
     * Lightning Correction Ratio: ARC
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceLuckCorrectRate_byThunder;

    /* 筋力補正値影響率（闇）
     *   補正率の影響割合。
     * Holy Correction Ratio: STR
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceStrengthCorrectRate_byDark;

    /* 技量補正値影響率（闇）
     *   補正率の影響割合。
     * Holy Correction Ratio: DEX
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceDexterityCorrectRate_byDark;

    /* 理力補正値影響率（闇）
     *   補正率の影響割合。
     * Holy Correction Ratio: INT
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceMagicCorrectRate_byDark;

    /* 信仰補正値影響率（闇）
     *   補正率の影響割合。
     * Holy Correction Ratio: FTH
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceFaithCorrectRate_byDark;

    /* 運補正値影響率（闇）
     *   補正率の影響割合。
     * Holy Correction Ratio: ARC
     *   The rate of influence of the correction factor.
     * Default Value  = 100 */
    short InfluenceLuckCorrectRate_byDark;

    /* パディング */
    char pad2[24];
} attack_element_correct_param_t;
