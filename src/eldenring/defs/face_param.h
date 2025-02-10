#pragma once

/* Governs face and body data of human characters */
typedef struct face_param_s {
    /* 顔パーツID
     *   顔パーツID
     * Adjust Face Template - Bone Structure (Parts ID)
     *   Face part ID */
    unsigned char face_partsId;

    /* 肌の色(Ｒ)
     *   肌の色(Ｒ)
     * Alter Skin Color R
     *   Skin color (R)
     * Default Value  = 128 */
    unsigned char skin_color_R;

    /* 肌の色(Ｇ)
     *   肌の色(Ｇ)
     * Alter Skin Color G
     *   Skin color (G)
     * Default Value  = 128 */
    unsigned char skin_color_G;

    /* 肌の色(Ｂ)
     *   肌の色(Ｂ)
     * Alter Skin Color B
     *   Skin color (B)
     * Default Value  = 128 */
    unsigned char skin_color_B;

    /* 肌のつや
     *   肌のつや
     * Skin Features - Skin Luster
     *   Shiny skin
     * Default Value  = 128 */
    unsigned char skin_gloss;

    /* 毛穴
     *   毛穴
     * Skin Features - Pores
     *   pores
     * Default Value  = 128 */
    unsigned char skin_pores;

    /* 青ひげ
     *   青ひげ
     * Facial Hair - Stubble
     *   Blue beard
     * Default Value  = 128 */
    unsigned char face_beard;

    /* くま
     *   くま
     * Skin Features - Dark Circles
     *   Bear
     * Default Value  = 128 */
    unsigned char face_aroundEye;

    /* くまの色(R)
     *   くまの色(R)
     * Skin Features - Dark Circles Color R
     *   Bear color (R)
     * Default Value  = 128 */
    unsigned char face_aroundEyeColor_R;

    /* くまの色(G)
     *   くまの色(G)
     * Skin Features - Dark Circles Color G
     *   Bear color (G)
     * Default Value  = 128 */
    unsigned char face_aroundEyeColor_G;

    /* くまの色(B)
     *   くまの色(B)
     * Skin Features - Dark Circles Color B
     *   Bear color (B)
     * Default Value  = 128 */
    unsigned char face_aroundEyeColor_B;

    /* チーク
     *   チーク
     * Cosmetics - Cheeks
     *   cheek
     * Default Value  = 128 */
    unsigned char face_cheek;

    /* チークの色(R)
     *   チークの色(R)
     * Cosmetics - Cheek Color R
     *   Teak color (R)
     * Default Value  = 128 */
    unsigned char face_cheekColor_R;

    /* チークの色(G)
     *   チークの色(G)
     * Cosmetics - Cheek Color G
     *   Teak color (G)
     * Default Value  = 128 */
    unsigned char face_cheekColor_G;

    /* チークの色(B)
     *   チークの色(B)
     * Cosmetics - Cheek Color B
     *   Teak color (B)
     * Default Value  = 128 */
    unsigned char face_cheekColor_B;

    /* アイライン
     *   アイライン
     * Cosmetics - Eyeliner
     *   Eyeline
     * Default Value  = 128 */
    unsigned char face_eyeLine;

    /* アイラインの色(R)
     *   アイラインの色(R)
     * Cosmetics - Eyeliner Color R
     *   Eyeliner color (R)
     * Default Value  = 128 */
    unsigned char face_eyeLineColor_R;

    /* アイラインの色(G)
     *   アイラインの色(G)
     * Cosmetics - Eyeliner Color G
     *   Eyeliner color (G)
     * Default Value  = 128 */
    unsigned char face_eyeLineColor_G;

    /* アイラインの色(B)
     *   アイラインの色(B)
     * Cosmetics - Eyeliner Color B
     *   Eyeliner color (B)
     * Default Value  = 128 */
    unsigned char face_eyeLineColor_B;

    /* アイシャドウ(下)
     *   アイシャドウ(下)
     * Cosmetics - Eyeshadow (Lower)
     *   Eye shadow (bottom)
     * Default Value  = 128 */
    unsigned char face_eyeShadowDown;

    /* アイシャドウ(下)の色(R)
     *   アイシャドウ(下)の色(R)
     * Cosmetics - Eyeshadow (Lower) Color R
     *   Eyeshadow (bottom) color (R)
     * Default Value  = 128 */
    unsigned char face_eyeShadowDownColor_R;

    /* アイシャドウ(下)の色(G)
     *   アイシャドウ(下)の色(G)
     * Cosmetics - Eyeshadow (Lower) Color G
     *   Eyeshadow (bottom) color (G)
     * Default Value  = 128 */
    unsigned char face_eyeShadowDownColor_G;

    /* アイシャドウ(下)の色(B)
     *   アイシャドウ(下)の色(B)
     * Cosmetics - Eyeshadow (Lower) Color B
     *   Eyeshadow (bottom) color (B)
     * Default Value  = 128 */
    unsigned char face_eyeShadowDownColor_B;

    /* アイシャドウ(上)
     *   アイシャドウ(上)
     * Cosmetics - Eyeshadow (Upper)
     *   Eye shadow (top)
     * Default Value  = 128 */
    unsigned char face_eyeShadowUp;

    /* アイシャドウ(上)の色(R)
     *   アイシャドウ(上)の色(R)
     * Cosmetics - Eyeshadow (Upper) Color R
     *   Eyeshadow (top) color (R)
     * Default Value  = 128 */
    unsigned char face_eyeShadowUpColor_R;

    /* アイシャドウ(上)の色(G)
     *   アイシャドウ(上)の色(G)
     * Cosmetics - Eyeshadow (Upper) Color G
     *   Eyeshadow (top) color (G)
     * Default Value  = 128 */
    unsigned char face_eyeShadowUpColor_G;

    /* アイシャドウ(上)の色(B)
     *   アイシャドウ(上)の色(B)
     * Cosmetics - Eyeshadow (Upper) Color B
     *   Eyeshadow (top) color (B)
     * Default Value  = 128 */
    unsigned char face_eyeShadowUpColor_B;

    /* 口紅
     *   口紅
     * Cosmetics - Lipstick
     *   lipstick
     * Default Value  = 128 */
    unsigned char face_lip;

    /* 口紅の色(R)
     *   口紅の色(R)
     * Cosmetics - Lipstick Color R
     *   Lipstick color (R)
     * Default Value  = 128 */
    unsigned char face_lipColor_R;

    /* 口紅の色(G)
     *   口紅の色(G)
     * Cosmetics - Lipstick Color G
     *   Lipstick color (G)
     * Default Value  = 128 */
    unsigned char face_lipColor_G;

    /* 口紅の色(B)
     *   口紅の色(B)
     * Cosmetics - Lipstick Color B
     *   Lipstick color (B)
     * Default Value  = 128 */
    unsigned char face_lipColor_B;

    /* 体毛の濃さ
     *   体毛の濃さ
     * Alter Body - Body Hair
     *   Hair thickness
     * Default Value  = 128 */
    unsigned char body_hair;

    /* 体毛の色(R)
     *   体毛の色(R)
     * Alter Body - Body Hair Color R
     *   Hair color (R)
     * Default Value  = 128 */
    unsigned char body_hairColor_R;

    /* 体毛の色(G)
     *   体毛の色(G)
     * Alter Body - Body Hair Color G
     *   Hair color (G)
     * Default Value  = 128 */
    unsigned char body_hairColor_G;

    /* 体毛の色(B)
     *   体毛の色(B)
     * Alter Body - Body Hair Color B
     *   Hair color (B)
     * Default Value  = 128 */
    unsigned char body_hairColor_B;

    /* 眼球パーツID
     *   眼球パーツID
     * Eyes - Parts ID
     *   Eyeball part ID */
    unsigned char eye_partsId;

    /* 虹彩の色(Ｒ)
     *   右目の虹彩の色(Ｒ)
     * Eyes - Right Iris Color R
     *   Right eye iris color (R)
     * Default Value  = 128 */
    unsigned char eyeR_irisColor_R;

    /* 虹彩の色(Ｇ)
     *   右目の虹彩の色(Ｇ)
     * Eyes - Right Iris Color G
     *   Right eye iris color (G)
     * Default Value  = 128 */
    unsigned char eyeR_irisColor_G;

    /* 虹彩の色(Ｂ)
     *   右目の虹彩の色(Ｂ)
     * Eyes - Right Iris Color B
     *   Right eye iris color (B)
     * Default Value  = 128 */
    unsigned char eyeR_irisColor_B;

    /* 虹彩の大きさ
     *   右目の虹彩の大きさ
     * Eyes - Right Iris Size
     *   The size of the iris of the right eye
     * Default Value  = 128 */
    unsigned char eyeR_irisScale;

    /* 水晶体の濁り
     *   右目の水晶体の濁り
     * Eyes - R Eye Clouding
     *   Cloudiness of the crystalline lens of the right eye
     * Default Value  = 128 */
    unsigned char eyeR_cataract;

    /* 水晶体の濁りの色(Ｒ)
     *   右目の水晶体の濁りの色(Ｒ)
     * Eyes - R Clouding Color R
     *   The turbid color of the crystalline lens of the right eye (R)
     * Default Value  = 128 */
    unsigned char eyeR_cataractColor_R;

    /* 水晶体の濁りの色(Ｇ)
     *   右目の水晶体の濁りの色(Ｇ)
     * Eyes - R Clouding Color G
     *   The turbid color of the crystalline lens of the right eye (G)
     * Default Value  = 128 */
    unsigned char eyeR_cataractColor_G;

    /* 水晶体の濁りの色(Ｂ)
     *   右目の水晶体の濁りの色(Ｂ)
     * Eyes - R Clouding Color B
     *   The turbid color of the crystalline lens of the right eye (B)
     * Default Value  = 128 */
    unsigned char eyeR_cataractColor_B;

    /* 白目の色(Ｒ)
     *   右目の白目の色(Ｒ)
     * Eyes - R Eye White Color R
     *   White eye color of the right eye (R)
     * Default Value  = 128 */
    unsigned char eyeR_scleraColor_R;

    /* 白目の色(G)
     *   右目の白目の色(G)
     * Eyes - R Eye White Color G
     *   White eye color of the right eye (G)
     * Default Value  = 128 */
    unsigned char eyeR_scleraColor_G;

    /* 白目の色(B)
     *   右目の白目の色(B)
     * Eyes - R Eye White Color B
     *   White eye color of the right eye (B)
     * Default Value  = 128 */
    unsigned char eyeR_scleraColor_B;

    /* 虹彩の位置
     *   右目の虹彩の位置
     * Eyes - R Eye Position
     *   Position of the iris of the right eye
     * Default Value  = 128 */
    unsigned char eyeR_irisDistance;

    /* 虹彩の色(Ｒ)
     *   左目の虹彩の色(Ｒ)
     * Eyes - Left Iris Color R
     *   Left eye iris color (R)
     * Default Value  = 128 */
    unsigned char eyeL_irisColor_R;

    /* 虹彩の色(Ｇ)
     *   左目の虹彩の色(Ｇ)
     * Eyes - Left Iris Color G
     *   Left eye iris color (G)
     * Default Value  = 128 */
    unsigned char eyeL_irisColor_G;

    /* 虹彩の色(Ｂ)
     *   左目の虹彩の色(Ｂ)
     * Eyes - Left Iris Color B
     *   Left eye iris color (B)
     * Default Value  = 128 */
    unsigned char eyeL_irisColor_B;

    /* 虹彩の大きさ
     *   左目の虹彩の大きさ
     * Eyes - Left Iris Size
     *   The size of the iris of the left eye
     * Default Value  = 128 */
    unsigned char eyeL_irisScale;

    /* 水晶体の濁り
     *   左目の水晶体の濁り
     * Eyes - L Eye Clouding
     *   Cloudiness of the crystalline lens of the left eye
     * Default Value  = 128 */
    unsigned char eyeL_cataract;

    /* 水晶体の濁りの色(Ｒ)
     *   左目の水晶体の濁りの色(Ｒ)
     * Eyes - L Clouding Color R
     *   The turbid color of the crystalline lens of the left eye (R)
     * Default Value  = 128 */
    unsigned char eyeL_cataractColor_R;

    /* 水晶体の濁りの色(Ｇ)
     *   左目の水晶体の濁りの色(Ｇ)
     * Eyes - L Clouding Color G
     *   The turbid color of the crystalline lens of the left eye (G)
     * Default Value  = 128 */
    unsigned char eyeL_cataractColor_G;

    /* 水晶体の濁りの色(Ｂ)
     *   左目の水晶体の濁りの色(Ｂ)
     * Eyes - L Clouding Color B
     *   The turbid color of the crystalline lens of the left eye (B)
     * Default Value  = 128 */
    unsigned char eyeL_cataractColor_B;

    /* 白目の色(Ｒ)
     *   左目の白目の色(Ｒ)
     * Eyes - L Eye White Color R
     *   White eye color of the left eye (R)
     * Default Value  = 128 */
    unsigned char eyeL_scleraColor_R;

    /* 白目の色(G)
     *   左目の白目の色(G)
     * Eyes - L Eye White Color G
     *   White eye color of the left eye (G)
     * Default Value  = 128 */
    unsigned char eyeL_scleraColor_G;

    /* 白目の色(B)
     *   左目の白目の色(B)
     * Eyes - L Eye White Color B
     *   White eye color of the left eye (B)
     * Default Value  = 128 */
    unsigned char eyeL_scleraColor_B;

    /* 虹彩の位置
     *   左目の虹彩の位置
     * Eyes - L Eye Position
     *   Position of the iris of the left eye
     * Default Value  = 128 */
    unsigned char eyeL_irisDistance;

    /* 髪パーツID
     *   髪パーツID
     * Hair - Parts ID
     *   Hair part ID */
    unsigned char hair_partsId;

    /* 髪の色(Ｒ)
     *   髪の色(Ｒ)
     * Hair - Hair Color R
     *   Hair color (R)
     * Default Value  = 128 */
    unsigned char hair_color_R;

    /* 髪の色(Ｇ)
     *   髪の色(Ｇ)
     * Hair - Hair Color G
     *   Hair color (G)
     * Default Value  = 128 */
    unsigned char hair_color_G;

    /* 髪の色(Ｂ)
     *   髪の色(Ｂ)
     * Hair - Hair Color B
     *   Hair color (B)
     * Default Value  = 128 */
    unsigned char hair_color_B;

    /* 光沢
     *   髪の光沢
     * Hair - Luster
     *   Hair gloss
     * Default Value  = 128 */
    unsigned char hair_shininess;

    /* 根元の黒さ
     *   髪の根元の黒さ
     * Hair - Root Darkness
     *   Blackness at the base of hair
     * Default Value  = 128 */
    unsigned char hair_rootBlack;

    /* 白髪の量
     *   髪の白髪の量
     * Hair - White Hairs
     *   Amount of white hair
     * Default Value  = 128 */
    unsigned char hair_whiteDensity;

    /* 髭パーツID
     *   髭パーツID
     * Facial Hair - Beard - Parts ID
     *   Beard part ID */
    unsigned char beard_partsId;

    /* 髭の色(Ｒ)
     *   髭の色(Ｒ)
     * Facial Hair - Beard Color R
     *   Beard color (R)
     * Default Value  = 128 */
    unsigned char beard_color_R;

    /* 髭の色(Ｇ)
     *   髭の色(Ｇ)
     * Facial Hair - Beard Color G
     *   Beard color (G)
     * Default Value  = 128 */
    unsigned char beard_color_G;

    /* 髭の色(Ｂ)
     *   髭の色(Ｂ)
     * Facial Hair - Beard Color B
     *   Beard color (B)
     * Default Value  = 128 */
    unsigned char beard_color_B;

    /* 光沢
     *   髭の光沢
     * Facial Hair - Luster
     *   Beard luster
     * Default Value  = 128 */
    unsigned char beard_shininess;

    /* 根元の黒さ
     *   髭の根元の黒さ
     * Facial Hair - Root Darkness
     *   Blackness at the base of the beard
     * Default Value  = 128 */
    unsigned char beard_rootBlack;

    /* 白髪の量
     *   髭の白髪の量
     * Facial Hair - White Hairs
     *   Amount of white hair with a beard
     * Default Value  = 128 */
    unsigned char beard_whiteDensity;

    /* 眉パーツID
     *   眉パーツID
     * Eyebrows - Parts ID
     *   Eyebrow part ID */
    unsigned char eyebrow_partsId;

    /* 眉の色(Ｒ)
     *   眉の色(Ｒ)
     * Eyebrows - Brow Color R
     *   Eyebrow color (R)
     * Default Value  = 128 */
    unsigned char eyebrow_color_R;

    /* 眉の色(Ｇ)
     *   眉の色(Ｇ)
     * Eyebrows - Brow Color G
     *   Eyebrow color (G)
     * Default Value  = 128 */
    unsigned char eyebrow_color_G;

    /* 眉の色(Ｂ)
     *   眉の色(Ｂ)
     * Eyebrows - Brow Color B
     *   Eyebrow color (B)
     * Default Value  = 128 */
    unsigned char eyebrow_color_B;

    /* 光沢
     *   眉の光沢
     * Eyebrows - Luster
     *   Glossy eyebrows
     * Default Value  = 128 */
    unsigned char eyebrow_shininess;

    /* 根元の黒さ
     *   眉の根元の黒さ
     * Eyebrows - Root Darkness
     *   Blackness at the base of the eyebrows
     * Default Value  = 128 */
    unsigned char eyebrow_rootBlack;

    /* 白髪の量
     *   眉の白髪の量
     * Eyebrows - White Hairs
     *   Amount of white hair on the eyebrows
     * Default Value  = 128 */
    unsigned char eyebrow_whiteDensity;

    /* まつげパーツID
     *   まつげパーツID
     * Eyelashes - Parts ID
     *   Eyelash parts ID */
    unsigned char eyelash_partsId;

    /* まつげの色(Ｒ)
     *   まつげの色(Ｒ)
     * Eyelashes - Eyelash Color R
     *   Eyelash color (R)
     * Default Value  = 128 */
    unsigned char eyelash_color_R;

    /* まつげの色(Ｇ)
     *   まつげの色(Ｇ)
     * Eyelashes - Eyelash Color G
     *   Eyelash color (G)
     * Default Value  = 128 */
    unsigned char eyelash_color_G;

    /* まつげの色(Ｂ)
     *   まつげの色(Ｂ)
     * Eyelashes - Eyelash Color B
     *   Eyelash color (B)
     * Default Value  = 128 */
    unsigned char eyelash_color_B;

    /* 装飾パーツID
     *   装飾パーツID
     * Eyepatch - Parts ID
     *   Decorative part ID */
    unsigned char accessories_partsId;

    /* 装飾の色(Ｒ)
     *   装飾の色(Ｒ)
     * Eyepatch - Tattoo/Mark Color R
     *   Decoration color (R)
     * Default Value  = 128 */
    unsigned char accessories_color_R;

    /* 装飾の色(Ｇ)
     *   装飾の色(Ｇ)
     * Eyepatch - Tattoo/Mark Color G
     *   Decoration color (G)
     * Default Value  = 128 */
    unsigned char accessories_color_G;

    /* 装飾の色(Ｂ)
     *   装飾の色(Ｂ)
     * Eyepatch - Tattoo/Mark Color B
     *   Decorative color (B)
     * Default Value  = 128 */
    unsigned char accessories_color_B;

    /* デカールパーツID
     *   デカールパーツID
     * Tattoo/Mark - Parts ID
     *   Decal part ID */
    unsigned char decal_partsId;

    /* デカール位置(x)
     *   デカール位置(x)
     * Tweak Tattoo/Mark - Position (Horiz.)
     *   Decal position (x) */
    unsigned char decal_posX;

    /* デカール位置(y)
     *   デカール位置(y)
     * Tweak Tattoo/Mark - Position (Vert.)
     *   Decal position (y) */
    unsigned char decal_posY;

    /* デカール角度
     *   デカール角度
     * Tweak Tattoo/Mark - Angle
     *   Decal angle */
    unsigned char decal_angle;

    /* デカールスケール
     *   デカールスケール
     * Tweak Tattoo/Mark - Expansion
     *   Decal scale */
    unsigned char decal_scale;

    /* デカールの色(Ｒ)
     *   デカールの色(Ｒ)
     * Tattoo/Mark Color R
     *   Decal color (R)
     * Default Value  = 128 */
    unsigned char decal_color_R;

    /* デカールの色(Ｇ)
     *   デカールの色(Ｇ)
     * Tattoo/Mark Color G
     *   Decal color (G)
     * Default Value  = 128 */
    unsigned char decal_color_G;

    /* デカールの色(Ｂ)
     *   デカールの色(Ｂ)
     * Tattoo/Mark Color B
     *   Decal color (B)
     * Default Value  = 128 */
    unsigned char decal_color_B;

    /* デカールのつや
     *   デカールのつや
     * Tweak Tattoo/Mark - Gloss
     *   Decal gloss
     * Default Value  = 128 */
    unsigned char decal_gloss;

    /* デカールの反転
     *   デカールの反転
     * Tweak Tattoo/Mark - Flip
     *   Decal reversal */
    unsigned char decal_mirror;

    /* キャラ体型頭部スケール
     *   キャラ体型頭部スケール
     * Alter Body - Head
     *   Character body head scale
     * Default Value  = 128 */
    unsigned char chrBodyScaleHead;

    /* キャラ体型胸部スケール
     *   キャラ体型胸部スケール
     * Alter Body - Chest
     *   Character body chest scale
     * Default Value  = 128 */
    unsigned char chrBodyScaleBreast;

    /* キャラ体型腹部スケール
     *   キャラ体型腹部スケール
     * Alter Body - Abdomen
     *   Character body type abdominal scale
     * Default Value  = 128 */
    unsigned char chrBodyScaleAbdomen;

    /* キャラ体型右腕部スケール
     *   キャラ体型右腕部スケール
     * Alter Body - Right Arm
     *   Character body right arm scale
     * Default Value  = 128 */
    unsigned char chrBodyScaleRArm;

    /* キャラ体型右脚部スケール
     *   キャラ体型右脚部スケール
     * Alter Body - Right Leg
     *   Character body right leg scale
     * Default Value  = 128 */
    unsigned char chrBodyScaleRLeg;

    /* キャラ体型左腕部スケール
     *   キャラ体型左腕部スケール
     * Alter Body - Left Arm
     *   Character body shape left arm scale
     * Default Value  = 128 */
    unsigned char chrBodyScaleLArm;

    /* キャラ体型左脚部スケール
     *   キャラ体型左脚部スケール
     * Alter Body - Left Leg
     *   Character body type left leg scale
     * Default Value  = 128 */
    unsigned char chrBodyScaleLLeg;

    /* 火傷跡
     *   火傷跡
     * Alter Body - Burn Marks
     *   Burn scars */
    unsigned char burn_scar;

    /* 眼球パーツID
     *   眼球パーツIDを上書きするか
     * Override - Eyes - Left Iris - Parts ID
     *   Whether to overwrite the eyeball part ID */
    unsigned char override_eye_partsId:1;

    /* 虹彩の色
     *   虹彩の色を上書きするか
     * Override - Eyes - Left Iris Color
     *   Do you want to overwrite the color of the iris? */
    unsigned char override_eye_irisColor:1;

    /* 水晶体の濁り
     *   水晶体の濁りを上書きするか
     * Override - Eyes - L Eye Clouding
     *   Do you want to overwrite the turbidity of the crystalline lens? */
    unsigned char override_eye_cataract:1;

    /* 水晶体の濁り色
     *   水晶体の濁り色を上書きするか
     * Override - Eyes - L Clouding Color
     *   Do you want to overwrite the muddy color of the crystalline lens? */
    unsigned char override_eye_cataractColor:1;

    /* 白目の色
     *   白目の色を上書きするか
     * Override - Eyes - L Eye White Color
     *   Do you want to overwrite the white eye color? */
    unsigned char override_eye_scleraColor:1;

    /* 火傷跡
     *   火傷跡を上書きするか
     * Override - Burn Marks
     *   Do you want to overwrite the burn scars? */
    unsigned char override_burn_scar:1;

    char pad2:2;

    char pad[5];

    /* 年齢
     *   年齢
     * Adjust Face Template - Apparent Age
     *   age
     * Default Value  = 128 */
    unsigned char age;

    /* 性別
     *   性別
     * Adjust Face Template - Facial Aesthetic
     *   sex
     * Default Value  = 128 */
    unsigned char gender;

    /* 誇張（モデル）
     *   誇張（モデル）
     * Adjust Face Template - Form Emphasis
     *   Exaggeration (model)
     * Default Value  = 128 */
    unsigned char caricatureGeometry;

    /* 誇張（テクスチャ）
     *   誇張（テクスチャ）
     * Model Texture
     *   Exaggeration (texture)
     * Default Value  = 128 */
    unsigned char caricatureTexture;

    /* 顔作成ジオメトリデータ00
     *   顔作成ジオメトリデータ00
     * Brow Ridge - Brow Ridge Height
     *   Face - Geo Data [00]
     * Default Value  = 128 */
    unsigned char faceGeoData00;

    /* 顔作成ジオメトリデータ01
     *   顔作成ジオメトリデータ01
     * Brow Ridge - Inner Brow Ridge
     *   Face - Geo Data [01]
     * Default Value  = 128 */
    unsigned char faceGeoData01;

    /* 顔作成ジオメトリデータ02
     *   顔作成ジオメトリデータ02
     * Brow Ridge - Outer Brow Ridge
     *   Face - Geo Data [02]
     * Default Value  = 128 */
    unsigned char faceGeoData02;

    /* 顔作成ジオメトリデータ03
     *   顔作成ジオメトリデータ03
     * Cheeks - Cheekbone Height
     *   Face - Geo Data [03]
     * Default Value  = 128 */
    unsigned char faceGeoData03;

    /* 顔作成ジオメトリデータ04
     *   顔作成ジオメトリデータ04
     * Cheeks - Cheekbone Depth
     *   Face - Geo Data [04]
     * Default Value  = 128 */
    unsigned char faceGeoData04;

    /* 顔作成ジオメトリデータ05
     *   顔作成ジオメトリデータ05
     * Cheeks - Cheekbone Width
     *   Face - Geo Data [05]
     * Default Value  = 128 */
    unsigned char faceGeoData05;

    /* 顔作成ジオメトリデータ06
     *   顔作成ジオメトリデータ06
     * Cheeks - Cheekbone Protrusion
     *   Face - Geo Data [06]
     * Default Value  = 128 */
    unsigned char faceGeoData06;

    /* 顔作成ジオメトリデータ07
     *   顔作成ジオメトリデータ07
     * Cheeks - Cheeks
     *   Face - Geo Data [07]
     * Default Value  = 128 */
    unsigned char faceGeoData07;

    /* 顔作成ジオメトリデータ08
     *   顔作成ジオメトリデータ08
     * Chin - Chin Tip Position
     *   Face - Geo Data [08]
     * Default Value  = 128 */
    unsigned char faceGeoData08;

    /* 顔作成ジオメトリデータ09
     *   顔作成ジオメトリデータ09
     * Chin - Chin Length
     *   Face - Geo Data [09]
     * Default Value  = 128 */
    unsigned char faceGeoData09;

    /* 顔作成ジオメトリデータ10
     *   顔作成ジオメトリデータ10
     * Chin - Chin Protrusion
     *   Face - Geo Data [10]
     * Default Value  = 128 */
    unsigned char faceGeoData10;

    /* 顔作成ジオメトリデータ11
     *   顔作成ジオメトリデータ11
     * Chin - Chin Depth
     *   Face - Geo Data [11]
     * Default Value  = 128 */
    unsigned char faceGeoData11;

    /* 顔作成ジオメトリデータ12
     *   顔作成ジオメトリデータ12
     * Chin - Chin Size
     *   Face - Geo Data [12]
     * Default Value  = 128 */
    unsigned char faceGeoData12;

    /* 顔作成ジオメトリデータ13
     *   顔作成ジオメトリデータ13
     * Chin - Chin Height
     *   Face - Geo Data [13]
     * Default Value  = 128 */
    unsigned char faceGeoData13;

    /* 顔作成ジオメトリデータ14
     *   顔作成ジオメトリデータ14
     * Chin - Chin Width
     *   Face - Geo Data [14]
     * Default Value  = 128 */
    unsigned char faceGeoData14;

    /* 顔作成ジオメトリデータ15
     *   顔作成ジオメトリデータ15
     * Eyes - Eye Position
     *   Face - Geo Data [15]
     * Default Value  = 128 */
    unsigned char faceGeoData15;

    /* 顔作成ジオメトリデータ16
     *   顔作成ジオメトリデータ16
     * Eyes - Eye Size
     *   Face - Geo Data [16]
     * Default Value  = 128 */
    unsigned char faceGeoData16;

    /* 顔作成ジオメトリデータ17
     *   顔作成ジオメトリデータ17
     * Eyes - Eye Slant
     *   Face - Geo Data [17]
     * Default Value  = 128 */
    unsigned char faceGeoData17;

    /* 顔作成ジオメトリデータ18
     *   顔作成ジオメトリデータ18
     * Eyes - Eye Spacing
     *   Face - Geo Data [18]
     * Default Value  = 128 */
    unsigned char faceGeoData18;

    /* 顔作成ジオメトリデータ19
     *   顔作成ジオメトリデータ19
     * Facial Balance - Nose Size
     *   Face - Geo Data [19]
     * Default Value  = 128 */
    unsigned char faceGeoData19;

    /* 顔作成ジオメトリデータ20
     *   顔作成ジオメトリデータ20
     * Facial Balance - Nose/Forehead Ratio
     *   Face - Geo Data [20]
     * Default Value  = 128 */
    unsigned char faceGeoData20;

    /* 顔作成ジオメトリデータ21
     *   顔作成ジオメトリデータ21
     * Face - Geo Data [21]
     *   Face - Geo Data [21]
     * Default Value  = 128 */
    unsigned char faceGeoData21;

    /* 顔作成ジオメトリデータ22
     *   顔作成ジオメトリデータ22
     * Facial Balance - Face Protrusion
     *   Face - Geo Data [22]
     * Default Value  = 128 */
    unsigned char faceGeoData22;

    /* 顔作成ジオメトリデータ23
     *   顔作成ジオメトリデータ23
     * Facial Balance - Vert. Face Ratio
     *   Face - Geo Data [23]
     * Default Value  = 128 */
    unsigned char faceGeoData23;

    /* 顔作成ジオメトリデータ24
     *   顔作成ジオメトリデータ24
     * Facial Balance - Facial Feature Slant
     *   Face - Geo Data [24]
     * Default Value  = 128 */
    unsigned char faceGeoData24;

    /* 顔作成ジオメトリデータ25
     *   顔作成ジオメトリデータ25
     * Facial Balance - Horiz. Face Ratio
     *   Face - Geo Data [25]
     * Default Value  = 128 */
    unsigned char faceGeoData25;

    /* 顔作成ジオメトリデータ26
     *   顔作成ジオメトリデータ26
     * Face - Geo Data [26]
     *   Face - Geo Data [26]
     * Default Value  = 128 */
    unsigned char faceGeoData26;

    /* 顔作成ジオメトリデータ27
     *   顔作成ジオメトリデータ27
     * Forehead/Glabella - Forehead Depth
     *   Face - Geo Data [27]
     * Default Value  = 128 */
    unsigned char faceGeoData27;

    /* 顔作成ジオメトリデータ28
     *   顔作成ジオメトリデータ28
     * Forehead/Glabella - Forehead Protrusion
     *   Face - Geo Data [28]
     * Default Value  = 128 */
    unsigned char faceGeoData28;

    /* 顔作成ジオメトリデータ29
     *   顔作成ジオメトリデータ29
     * Face - Geo Data [29]
     *   Face - Geo Data [29]
     * Default Value  = 128 */
    unsigned char faceGeoData29;

    /* 顔作成ジオメトリデータ30
     *   顔作成ジオメトリデータ30
     * Jaw - Jaw Protrusion
     *   Face - Geo Data [30]
     * Default Value  = 128 */
    unsigned char faceGeoData30;

    /* 顔作成ジオメトリデータ31
     *   顔作成ジオメトリデータ31
     * Jaw - Jaw Width
     *   Face - Geo Data [31]
     * Default Value  = 128 */
    unsigned char faceGeoData31;

    /* 顔作成ジオメトリデータ32
     *   顔作成ジオメトリデータ32
     * Jaw - Lower Jaw
     *   Face - Geo Data [32]
     * Default Value  = 128 */
    unsigned char faceGeoData32;

    /* 顔作成ジオメトリデータ33
     *   顔作成ジオメトリデータ33
     * Jaw - Jaw Contour
     *   Face - Geo Data [33]
     * Default Value  = 128 */
    unsigned char faceGeoData33;

    /* 顔作成ジオメトリデータ34
     *   顔作成ジオメトリデータ34
     * Lips - Lip Shape
     *   Face - Geo Data [34]
     * Default Value  = 128 */
    unsigned char faceGeoData34;

    /* 顔作成ジオメトリデータ35
     *   顔作成ジオメトリデータ35
     * Lips - Lip Size
     *   Face - Geo Data [35]
     * Default Value  = 128 */
    unsigned char faceGeoData35;

    /* 顔作成ジオメトリデータ36
     *   顔作成ジオメトリデータ36
     * Lips - Lip Fullness
     *   Face - Geo Data [36]
     * Default Value  = 128 */
    unsigned char faceGeoData36;

    /* 顔作成ジオメトリデータ37
     *   顔作成ジオメトリデータ37
     * Lips - Mouth Expression
     *   Face - Geo Data [37]
     * Default Value  = 128 */
    unsigned char faceGeoData37;

    /* 顔作成ジオメトリデータ38
     *   顔作成ジオメトリデータ38
     * Lips - Lip Protrusion
     *   Face - Geo Data [38]
     * Default Value  = 128 */
    unsigned char faceGeoData38;

    /* 顔作成ジオメトリデータ39
     *   顔作成ジオメトリデータ39
     * Lips - Lip Thickness
     *   Face - Geo Data [39]
     * Default Value  = 128 */
    unsigned char faceGeoData39;

    /* 顔作成ジオメトリデータ40
     *   顔作成ジオメトリデータ40
     * Mouth - Mouth Protrusion
     *   Face - Geo Data [40]
     * Default Value  = 128 */
    unsigned char faceGeoData40;

    /* 顔作成ジオメトリデータ41
     *   顔作成ジオメトリデータ41
     * Mouth - Mouth Slant
     *   Face - Geo Data [41]
     * Default Value  = 128 */
    unsigned char faceGeoData41;

    /* 顔作成ジオメトリデータ42
     *   顔作成ジオメトリデータ42
     * Mouth - Occlusion
     *   Face - Geo Data [42]
     * Default Value  = 128 */
    unsigned char faceGeoData42;

    /* 顔作成ジオメトリデータ43
     *   顔作成ジオメトリデータ43
     * Mouth - Mouth Position
     *   Face - Geo Data [43]
     * Default Value  = 128 */
    unsigned char faceGeoData43;

    /* 顔作成ジオメトリデータ44
     *   顔作成ジオメトリデータ44
     * Mouth - Mouth Width
     *   Face - Geo Data [44]
     * Default Value  = 128 */
    unsigned char faceGeoData44;

    /* 顔作成ジオメトリデータ45
     *   顔作成ジオメトリデータ45
     * Mouth - Mouth-Chin Distance
     *   Face - Geo Data [45]
     * Default Value  = 128 */
    unsigned char faceGeoData45;

    /* 顔作成ジオメトリデータ46
     *   顔作成ジオメトリデータ46
     * Nose Ridge - Nose Ridge Depth
     *   Face - Geo Data [46]
     * Default Value  = 128 */
    unsigned char faceGeoData46;

    /* 顔作成ジオメトリデータ47
     *   顔作成ジオメトリデータ47
     * Nose Ridge - Nose Ridge Length
     *   Face - Geo Data [47]
     * Default Value  = 128 */
    unsigned char faceGeoData47;

    /* 顔作成ジオメトリデータ48
     *   顔作成ジオメトリデータ48
     * Nose Ridge - Nose Position
     *   Face - Geo Data [48]
     * Default Value  = 128 */
    unsigned char faceGeoData48;

    /* 顔作成ジオメトリデータ49
     *   顔作成ジオメトリデータ49
     * Nose Ridge - Nose Tip Height
     *   Face - Geo Data [49]
     * Default Value  = 128 */
    unsigned char faceGeoData49;

    /* 顔作成ジオメトリデータ50
     *   顔作成ジオメトリデータ50
     * Nostrils - Nostril Slant
     *   Face - Geo Data [50]
     * Default Value  = 128 */
    unsigned char faceGeoData50;

    /* 顔作成ジオメトリデータ51
     *   顔作成ジオメトリデータ51
     * Nostrils - Nostril Size
     *   Face - Geo Data [51]
     * Default Value  = 128 */
    unsigned char faceGeoData51;

    /* 顔作成ジオメトリデータ52
     *   顔作成ジオメトリデータ52
     * Nostrils - Nostril Width
     *   Face - Geo Data [52]
     * Default Value  = 128 */
    unsigned char faceGeoData52;

    /* 顔作成ジオメトリデータ53
     *   顔作成ジオメトリデータ53
     * Nose Ridge - Nose Protrusion A
     *   Face - Geo Data [53]
     * Default Value  = 128 */
    unsigned char faceGeoData53;

    /* 顔作成ジオメトリデータ54
     *   顔作成ジオメトリデータ54
     * Forehead/Glabella - Nose Bridge Height
     *   Face - Geo Data [54]
     * Default Value  = 128 */
    unsigned char faceGeoData54;

    /* 顔作成ジオメトリデータ55
     *   顔作成ジオメトリデータ55
     * Forehead/Glabella - Bridge Protrusion 1
     *   Face - Geo Data [55]
     * Default Value  = 128 */
    unsigned char faceGeoData55;

    /* 顔作成ジオメトリデータ56
     *   顔作成ジオメトリデータ56
     * Forehead/Glabella - Bridge Protrusion 2
     *   Face - Geo Data [56]
     * Default Value  = 128 */
    unsigned char faceGeoData56;

    /* 顔作成ジオメトリデータ57
     *   顔作成ジオメトリデータ57
     * Forehead/Glabella - Nose Bridge Width
     *   Face - Geo Data [57]
     * Default Value  = 128 */
    unsigned char faceGeoData57;

    /* 顔作成ジオメトリデータ58
     *   顔作成ジオメトリデータ58
     * Nose Ridge - Nose Height
     *   Face - Geo Data [58]
     * Default Value  = 128 */
    unsigned char faceGeoData58;

    /* 顔作成ジオメトリデータ59
     *   顔作成ジオメトリデータ59
     * Nose Ridge - Nose Slant
     *   Face - Geo Data [59]
     * Default Value  = 128 */
    unsigned char faceGeoData59;

    /* 顔作成ジオメトリデータ60
     *   顔作成ジオメトリデータ60
     * Nose Ridge - Nose Protrusion B
     *   Face - Geo Data [60]
     * Default Value  = 128 */
    unsigned char faceGeoData60;

    /* 顔作成テクスチャデータ00
     *   顔作成テクスチャデータ00
     * Face - Texture Data [00]
     *   Face - Texture Data [00]
     * Default Value  = 128 */
    unsigned char faceTexData00;

    /* 顔作成テクスチャデータ01
     *   顔作成テクスチャデータ01
     * Face - Texture Data [01]
     *   Face - Texture Data [01]
     * Default Value  = 128 */
    unsigned char faceTexData01;

    /* 顔作成テクスチャデータ02
     *   顔作成テクスチャデータ02
     * Face - Texture Data [02]
     *   Face - Texture Data [02]
     * Default Value  = 128 */
    unsigned char faceTexData02;

    /* 顔作成テクスチャデータ03
     *   顔作成テクスチャデータ03
     * Face - Texture Data [03]
     *   Face - Texture Data [03]
     * Default Value  = 128 */
    unsigned char faceTexData03;

    /* 顔作成テクスチャデータ04
     *   顔作成テクスチャデータ04
     * Face - Texture Data [04]
     *   Face - Texture Data [04]
     * Default Value  = 128 */
    unsigned char faceTexData04;

    /* 顔作成テクスチャデータ05
     *   顔作成テクスチャデータ05
     * Face - Texture Data [05]
     *   Face - Texture Data [05]
     * Default Value  = 128 */
    unsigned char faceTexData05;

    /* 顔作成テクスチャデータ06
     *   顔作成テクスチャデータ06
     * Face - Texture Data [06]
     *   Face - Texture Data [06]
     * Default Value  = 128 */
    unsigned char faceTexData06;

    /* 顔作成テクスチャデータ07
     *   顔作成テクスチャデータ07
     * Face - Texture Data [07]
     *   Face - Texture Data [07]
     * Default Value  = 128 */
    unsigned char faceTexData07;

    /* 顔作成テクスチャデータ08
     *   顔作成テクスチャデータ08
     * Face - Texture Data [08]
     *   Face - Texture Data [08]
     * Default Value  = 128 */
    unsigned char faceTexData08;

    /* 顔作成テクスチャデータ09
     *   顔作成テクスチャデータ09
     * Face - Texture Data [09]
     *   Face - Texture Data [09]
     * Default Value  = 128 */
    unsigned char faceTexData09;

    /* 顔作成テクスチャデータ10
     *   顔作成テクスチャデータ10
     * Face - Texture Data [10]
     *   Face - Texture Data [10]
     * Default Value  = 128 */
    unsigned char faceTexData10;

    /* 顔作成テクスチャデータ11
     *   顔作成テクスチャデータ11
     * Face - Texture Data [11]
     *   Face - Texture Data [11]
     * Default Value  = 128 */
    unsigned char faceTexData11;

    /* 顔作成テクスチャデータ12
     *   顔作成テクスチャデータ12
     * Face - Texture Data [12]
     *   Face - Texture Data [12]
     * Default Value  = 128 */
    unsigned char faceTexData12;

    /* 顔作成テクスチャデータ13
     *   顔作成テクスチャデータ13
     * Face - Texture Data [13]
     *   Face - Texture Data [13]
     * Default Value  = 128 */
    unsigned char faceTexData13;

    /* 顔作成テクスチャデータ14
     *   顔作成テクスチャデータ14
     * Face - Texture Data [14]
     *   Face - Texture Data [14]
     * Default Value  = 128 */
    unsigned char faceTexData14;

    /* 顔作成テクスチャデータ15
     *   顔作成テクスチャデータ15
     * Face - Texture Data [15]
     *   Face - Texture Data [15]
     * Default Value  = 128 */
    unsigned char faceTexData15;

    /* 顔作成テクスチャデータ16
     *   顔作成テクスチャデータ16
     * Face - Texture Data [16]
     *   Face - Texture Data [16]
     * Default Value  = 128 */
    unsigned char faceTexData16;

    /* 顔作成テクスチャデータ17
     *   顔作成テクスチャデータ17
     * Face - Texture Data [17]
     *   Face - Texture Data [17]
     * Default Value  = 128 */
    unsigned char faceTexData17;

    /* 顔作成テクスチャデータ18
     *   顔作成テクスチャデータ18
     * Face - Texture Data [18]
     *   Face - Texture Data [18]
     * Default Value  = 128 */
    unsigned char faceTexData18;

    /* 顔作成テクスチャデータ19
     *   顔作成テクスチャデータ19
     * Face - Texture Data [19]
     *   Face - Texture Data [19]
     * Default Value  = 128 */
    unsigned char faceTexData19;

    /* 顔作成テクスチャデータ20
     *   顔作成テクスチャデータ20
     * Face - Texture Data [20]
     *   Face - Texture Data [20]
     * Default Value  = 128 */
    unsigned char faceTexData20;

    /* 顔作成テクスチャデータ21
     *   顔作成テクスチャデータ21
     * Face - Texture Data [21]
     *   Face - Texture Data [21]
     * Default Value  = 128 */
    unsigned char faceTexData21;

    /* 顔作成テクスチャデータ22
     *   顔作成テクスチャデータ22
     * Face - Texture Data [22]
     *   Face - Texture Data [22]
     * Default Value  = 128 */
    unsigned char faceTexData22;

    /* 顔作成テクスチャデータ23
     *   顔作成テクスチャデータ23
     * Face - Texture Data [23]
     *   Face - Texture Data [23]
     * Default Value  = 128 */
    unsigned char faceTexData23;

    /* 顔作成テクスチャデータ24
     *   顔作成テクスチャデータ24
     * Face - Texture Data [24]
     *   Face - Texture Data [24]
     * Default Value  = 128 */
    unsigned char faceTexData24;

    /* 顔作成テクスチャデータ25
     *   顔作成テクスチャデータ25
     * Face - Texture Data [25]
     *   Face - Texture Data [25]
     * Default Value  = 128 */
    unsigned char faceTexData25;

    /* 顔作成テクスチャデータ26
     *   顔作成テクスチャデータ26
     * Face - Texture Data [26]
     *   Face - Texture Data [26]
     * Default Value  = 128 */
    unsigned char faceTexData26;

    /* 顔作成テクスチャデータ27
     *   顔作成テクスチャデータ27
     * Face - Texture Data [27]
     *   Face - Texture Data [27]
     * Default Value  = 128 */
    unsigned char faceTexData27;

    /* 顔作成テクスチャデータ28
     *   顔作成テクスチャデータ28
     * Face - Texture Data [28]
     *   Face - Texture Data [28]
     * Default Value  = 128 */
    unsigned char faceTexData28;

    /* 顔作成テクスチャデータ29
     *   顔作成テクスチャデータ29
     * Face - Texture Data [29]
     *   Face - Texture Data [29]
     * Default Value  = 128 */
    unsigned char faceTexData29;

    /* 顔作成テクスチャデータ30
     *   顔作成テクスチャデータ30
     * Face - Texture Data [30]
     *   Face - Texture Data [30]
     * Default Value  = 128 */
    unsigned char faceTexData30;

    /* 顔作成テクスチャデータ31
     *   顔作成テクスチャデータ31
     * Face - Texture Data [31]
     *   Face - Texture Data [31]
     * Default Value  = 128 */
    unsigned char faceTexData31;

    /* 顔作成テクスチャデータ32
     *   顔作成テクスチャデータ32
     * Face - Texture Data [32]
     *   Face - Texture Data [32]
     * Default Value  = 128 */
    unsigned char faceTexData32;

    /* 顔作成テクスチャデータ33
     *   顔作成テクスチャデータ33
     * Face - Texture Data [33]
     *   Face - Texture Data [33]
     * Default Value  = 128 */
    unsigned char faceTexData33;

    /* 顔作成テクスチャデータ34
     *   顔作成テクスチャデータ34
     * Face - Texture Data [34]
     *   Face - Texture Data [34]
     * Default Value  = 128 */
    unsigned char faceTexData34;

    /* 顔作成テクスチャデータ35
     *   顔作成テクスチャデータ35
     * Face - Texture Data [35]
     *   Face - Texture Data [35]
     * Default Value  = 128 */
    unsigned char faceTexData35;

    /* 顔作成ジオメトリ非対称データ00
     *   顔作成ジオメトリ非対称データ00
     * Face - Geo Asym Data [00]
     *   Face - Geo Asym Data [00]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData00;

    /* 顔作成ジオメトリ非対称データ01
     *   顔作成ジオメトリ非対称データ01
     * Face - Geo Asym Data [01]
     *   Face - Geo Asym Data [01]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData01;

    /* 顔作成ジオメトリ非対称データ02
     *   顔作成ジオメトリ非対称データ02
     * Face - Geo Asym Data [02]
     *   Face - Geo Asym Data [02]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData02;

    /* 顔作成ジオメトリ非対称データ03
     *   顔作成ジオメトリ非対称データ03
     * Face - Geo Asym Data [03]
     *   Face - Geo Asym Data [03]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData03;

    /* 顔作成ジオメトリ非対称データ04
     *   顔作成ジオメトリ非対称データ04
     * Face - Geo Asym Data [04]
     *   Face - Geo Asym Data [04]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData04;

    /* 顔作成ジオメトリ非対称データ05
     *   顔作成ジオメトリ非対称データ05
     * Face - Geo Asym Data [05]
     *   Face - Geo Asym Data [05]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData05;

    /* 顔作成ジオメトリ非対称データ06
     *   顔作成ジオメトリ非対称データ06
     * Face - Geo Asym Data [06]
     *   Face - Geo Asym Data [06]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData06;

    /* 顔作成ジオメトリ非対称データ07
     *   顔作成ジオメトリ非対称データ07
     * Face - Geo Asym Data [07]
     *   Face - Geo Asym Data [07]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData07;

    /* 顔作成ジオメトリ非対称データ08
     *   顔作成ジオメトリ非対称データ08
     * Face - Geo Asym Data [08]
     *   Face - Geo Asym Data [08]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData08;

    /* 顔作成ジオメトリ非対称データ09
     *   顔作成ジオメトリ非対称データ09
     * Face - Geo Asym Data [09]
     *   Face - Geo Asym Data [09]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData09;

    /* 顔作成ジオメトリ非対称データ10
     *   顔作成ジオメトリ非対称データ10
     * Face - Geo Asym Data [10]
     *   Face - Geo Asym Data [10]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData10;

    /* 顔作成ジオメトリ非対称データ11
     *   顔作成ジオメトリ非対称データ11
     * Face - Geo Asym Data [11]
     *   Face - Geo Asym Data [11]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData11;

    /* 顔作成ジオメトリ非対称データ12
     *   顔作成ジオメトリ非対称データ12
     * Face - Geo Asym Data [12]
     *   Face - Geo Asym Data [12]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData12;

    /* 顔作成ジオメトリ非対称データ13
     *   顔作成ジオメトリ非対称データ13
     * Face - Geo Asym Data [13]
     *   Face - Geo Asym Data [13]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData13;

    /* 顔作成ジオメトリ非対称データ14
     *   顔作成ジオメトリ非対称データ14
     * Face - Geo Asym Data [14]
     *   Face - Geo Asym Data [14]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData14;

    /* 顔作成ジオメトリ非対称データ15
     *   顔作成ジオメトリ非対称データ15
     * Face - Geo Asym Data [15]
     *   Face - Geo Asym Data [15]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData15;

    /* 顔作成ジオメトリ非対称データ16
     *   顔作成ジオメトリ非対称データ16
     * Face - Geo Asym Data [16]
     *   Face - Geo Asym Data [16]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData16;

    /* 顔作成ジオメトリ非対称データ17
     *   顔作成ジオメトリ非対称データ17
     * Face - Geo Asym Data [17]
     *   Face - Geo Asym Data [17]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData17;

    /* 顔作成ジオメトリ非対称データ18
     *   顔作成ジオメトリ非対称データ18
     * Face - Geo Asym Data [18]
     *   Face - Geo Asym Data [18]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData18;

    /* 顔作成ジオメトリ非対称データ19
     *   顔作成ジオメトリ非対称データ19
     * Face - Geo Asym Data [19]
     *   Face - Geo Asym Data [19]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData19;

    /* 顔作成ジオメトリ非対称データ20
     *   顔作成ジオメトリ非対称データ20
     * Face - Geo Asym Data [20]
     *   Face - Geo Asym Data [20]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData20;

    /* 顔作成ジオメトリ非対称データ21
     *   顔作成ジオメトリ非対称データ21
     * Face - Geo Asym Data [21]
     *   Face - Geo Asym Data [21]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData21;

    /* 顔作成ジオメトリ非対称データ22
     *   顔作成ジオメトリ非対称データ22
     * Face - Geo Asym Data [22]
     *   Face - Geo Asym Data [22]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData22;

    /* 顔作成ジオメトリ非対称データ23
     *   顔作成ジオメトリ非対称データ23
     * Face - Geo Asym Data [23]
     *   Face - Geo Asym Data [23]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData23;

    /* 顔作成ジオメトリ非対称データ24
     *   顔作成ジオメトリ非対称データ24
     * Face - Geo Asym Data [24]
     *   Face - Geo Asym Data [24]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData24;

    /* 顔作成ジオメトリ非対称データ25
     *   顔作成ジオメトリ非対称データ25
     * Face - Geo Asym Data [25]
     *   Face - Geo Asym Data [25]
     * Default Value  = 128 */
    unsigned char faceGeoAsymData25;
} face_param_t;
