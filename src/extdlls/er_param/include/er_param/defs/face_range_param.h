#pragma once

typedef struct er_face_range_param_s {
    /* 顔パーツID
     *   顔パーツID
     * Face - Parts ID
     *   Face part ID */
    float face_partsId;

    /* 肌の色(Ｒ)
     *   肌の色(Ｒ)
     * Skin - Color R
     *   Skin color (R) */
    float skin_color_R;

    /* 肌の色(Ｇ)
     *   肌の色(Ｇ)
     * Skin - Color G
     *   Skin color (G) */
    float skin_color_G;

    /* 肌の色(Ｂ)
     *   肌の色(Ｂ)
     * Skin - Color B
     *   Skin color (B) */
    float skin_color_B;

    /* 肌のつや
     *   肌のつや
     * Skin - Gloss
     *   Shiny skin */
    float skin_gloss;

    /* 毛穴
     *   毛穴
     * Skin - Pores
     *   pores */
    float skin_pores;

    /* 青ひげ
     *   青ひげ
     * Face - Beard
     *   Blue beard */
    float face_beard;

    /* くま
     *   くま
     * Face - Around Eye
     *   Bear */
    float face_aroundEye;

    /* くまの色(R)
     *   くまの色(R)
     * Face - Around Eye Color R
     *   Bear color (R) */
    float face_aroundEyeColor_R;

    /* くまの色(G)
     *   くまの色(G)
     * Face - Around Eye Color G
     *   Bear color (G) */
    float face_aroundEyeColor_G;

    /* くまの色(B)
     *   くまの色(B)
     * Face - Around Eye Color B
     *   Bear color (B) */
    float face_aroundEyeColor_B;

    /* チーク
     *   チーク
     * Face - Cheek
     *   cheek */
    float face_cheek;

    /* チークの色(R)
     *   チークの色(R)
     * Face - Cheek Color R
     *   Teak color (R) */
    float face_cheekColor_R;

    /* チークの色(G)
     *   チークの色(G)
     * Face - Cheek Color G
     *   Teak color (G) */
    float face_cheekColor_G;

    /* チークの色(B)
     *   チークの色(B)
     * Face - Cheek Color B
     *   Teak color (B) */
    float face_cheekColor_B;

    /* アイライン
     *   アイライン
     * Face - Eyeline
     *   Eyeline */
    float face_eyeLine;

    /* アイラインの色(R)
     *   アイラインの色(R)
     * Face - Eyeline Color R
     *   Eyeliner color (R) */
    float face_eyeLineColor_R;

    /* アイラインの色(G)
     *   アイラインの色(G)
     * Face - Eyeline Color G
     *   Eyeliner color (G) */
    float face_eyeLineColor_G;

    /* アイラインの色(B)
     *   アイラインの色(B)
     * Face - Eyeline Color B
     *   Eyeliner color (B) */
    float face_eyeLineColor_B;

    /* アイシャドウ(下)
     *   アイシャドウ(下)
     * Face - Eyeshadow (Down)
     *   Eye shadow (bottom) */
    float face_eyeShadowDown;

    /* アイシャドウ(下)の色(R)
     *   アイシャドウ(下)の色(R)
     * Face - Eyeshadow (Down) Color R
     *   Eyeshadow (bottom) color (R) */
    float face_eyeShadowDownColor_R;

    /* アイシャドウ(下)の色(G)
     *   アイシャドウ(下)の色(G)
     * Face - Eyeshadow (Down) Color G
     *   Eyeshadow (bottom) color (G) */
    float face_eyeShadowDownColor_G;

    /* アイシャドウ(下)の色(B)
     *   アイシャドウ(下)の色(B)
     * Face - Eyeshadow (Down) Color B
     *   Eyeshadow (bottom) color (B) */
    float face_eyeShadowDownColor_B;

    /* アイシャドウ(上)
     *   アイシャドウ(上)
     * Face - Eyeshadow (Up)
     *   Eye shadow (top) */
    float face_eyeShadowUp;

    /* アイシャドウ(上)の色(R)
     *   アイシャドウ(上)の色(R)
     * Face - Eyeshadow (Up) Color R
     *   Eyeshadow (top) color (R) */
    float face_eyeShadowUpColor_R;

    /* アイシャドウ(上)の色(G)
     *   アイシャドウ(上)の色(G)
     * Face - Eyeshadow (Up) Color G
     *   Eyeshadow (top) color (G) */
    float face_eyeShadowUpColor_G;

    /* アイシャドウ(上)の色(B)
     *   アイシャドウ(上)の色(B)
     * Face - Eyeshadow (Up) Color B
     *   Eyeshadow (top) color (B) */
    float face_eyeShadowUpColor_B;

    /* 口紅
     *   口紅
     * Face - Lip
     *   lipstick */
    float face_lip;

    /* 口紅の色(R)
     *   口紅の色(R)
     * Face - Lip Color R
     *   Lipstick color (R) */
    float face_lipColor_R;

    /* 口紅の色(G)
     *   口紅の色(G)
     * Face - Lip Color G
     *   Lipstick color (G) */
    float face_lipColor_G;

    /* 口紅の色(B)
     *   口紅の色(B)
     * Face - Lip Color B
     *   Lipstick color (B) */
    float face_lipColor_B;

    /* 体毛の濃さ
     *   体毛の濃さ
     * Body - Hair
     *   Hair thickness */
    float body_hair;

    /* 体毛の色(R)
     *   体毛の色(R)
     * Body - Hair Color R
     *   Hair color (R) */
    float body_hairColor_R;

    /* 体毛の色(G)
     *   体毛の色(G)
     * Body - Hair Color G
     *   Hair color (G) */
    float body_hairColor_G;

    /* 体毛の色(B)
     *   体毛の色(B)
     * Body - Hair Color B
     *   Hair color (B) */
    float body_hairColor_B;

    /* 眼球パーツID
     *   眼球パーツID
     * Eyes - Parts ID
     *   Eyeball part ID */
    float eye_partsId;

    /* 虹彩の色(Ｒ)
     *   右目の虹彩の色(Ｒ)
     * Right Eye - Iris Color R
     *   Right eye iris color (R) */
    float eyeR_irisColor_R;

    /* 虹彩の色(Ｇ)
     *   右目の虹彩の色(Ｇ)
     * Right Eye - Iris Color G
     *   Right eye iris color (G) */
    float eyeR_irisColor_G;

    /* 虹彩の色(Ｂ)
     *   右目の虹彩の色(Ｂ)
     * Right Eye - Iris Color B
     *   Right eye iris color (B) */
    float eyeR_irisColor_B;

    /* 虹彩の大きさ
     *   右目の虹彩の大きさ
     * Right Eye - Iris Scale
     *   The size of the iris of the right eye */
    float eyeR_irisScale;

    /* 水晶体の濁り
     *   右目の水晶体の濁り
     * Right Eye - Cataract
     *   Cloudiness of the crystalline lens of the right eye */
    float eyeR_cataract;

    /* 水晶体の濁りの色(Ｒ)
     *   右目の水晶体の濁りの色(Ｒ)
     * Right Eye - Cataract Color R
     *   The turbid color of the crystalline lens of the right eye (R) */
    float eyeR_cataractColor_R;

    /* 水晶体の濁りの色(Ｇ)
     *   右目の水晶体の濁りの色(Ｇ)
     * Right Eye - Cataract Color G
     *   The turbid color of the crystalline lens of the right eye (G) */
    float eyeR_cataractColor_G;

    /* 水晶体の濁りの色(Ｂ)
     *   右目の水晶体の濁りの色(Ｂ)
     * Right Eye - Cataract Color B
     *   The turbid color of the crystalline lens of the right eye (B) */
    float eyeR_cataractColor_B;

    /* 白目の色(Ｒ)
     *   右目の白目の色(Ｒ)
     * Right Eye - Sclera Color R
     *   White eye color of the right eye (R) */
    float eyeR_scleraColor_R;

    /* 白目の色(G)
     *   右目の白目の色(G)
     * Right Eye - Sclera Color G
     *   White eye color of the right eye (G) */
    float eyeR_scleraColor_G;

    /* 白目の色(B)
     *   右目の白目の色(B)
     * Right Eye - Sclera Color B
     *   White eye color of the right eye (B) */
    float eyeR_scleraColor_B;

    /* 虹彩の位置
     *   右目の虹彩の位置
     * Right Eye - Iris Distance
     *   Position of the iris of the right eye */
    float eyeR_irisDistance;

    /* 虹彩の色(Ｒ)
     *   左目の虹彩の色(Ｒ)
     * Left Eye - Iris Color R
     *   Left eye iris color (R) */
    float eyeL_irisColor_R;

    /* 虹彩の色(Ｇ)
     *   左目の虹彩の色(Ｇ)
     * Left Eye - Iris Color G
     *   Left eye iris color (G) */
    float eyeL_irisColor_G;

    /* 虹彩の色(Ｂ)
     *   左目の虹彩の色(Ｂ)
     * Left Eye - Iris Color B
     *   Left eye iris color (B) */
    float eyeL_irisColor_B;

    /* 虹彩の大きさ
     *   左目の虹彩の大きさ
     * Left Eye - Iris Scale
     *   The size of the iris of the left eye */
    float eyeL_irisScale;

    /* 水晶体の濁り
     *   左目の水晶体の濁り
     * Left Eye - Cataract
     *   Cloudiness of the crystalline lens of the left eye */
    float eyeL_cataract;

    /* 水晶体の濁りの色(Ｒ)
     *   左目の水晶体の濁りの色(Ｒ)
     * Left Eye - Cataract Color R
     *   The turbid color of the crystalline lens of the left eye (R) */
    float eyeL_cataractColor_R;

    /* 水晶体の濁りの色(Ｇ)
     *   左目の水晶体の濁りの色(Ｇ)
     * Left Eye - Cataract Color G
     *   The turbid color of the crystalline lens of the left eye (G) */
    float eyeL_cataractColor_G;

    /* 水晶体の濁りの色(Ｂ)
     *   左目の水晶体の濁りの色(Ｂ)
     * Left Eye - Cataract Color B
     *   The turbid color of the crystalline lens of the left eye (B) */
    float eyeL_cataractColor_B;

    /* 白目の色(Ｒ)
     *   左目の白目の色(Ｒ)
     * Left Eye - Sclera Color R
     *   White eye color of the left eye (R) */
    float eyeL_scleraColor_R;

    /* 白目の色(G)
     *   左目の白目の色(G)
     * Left Eye - Sclera Color G
     *   White eye color of the left eye (G) */
    float eyeL_scleraColor_G;

    /* 白目の色(B)
     *   左目の白目の色(B)
     * Left Eye - Sclera Color B
     *   White eye color of the left eye (B) */
    float eyeL_scleraColor_B;

    /* 虹彩の位置
     *   左目の虹彩の位置
     * Left Eye - Iris Distance
     *   Position of the iris of the left eye */
    float eyeL_irisDistance;

    /* 髪パーツID
     *   髪パーツID
     * Hair - Parts ID
     *   Hair part ID */
    float hair_partsId;

    /* 髪の色(Ｒ)
     *   髪の色(Ｒ)
     * Hair - Color R
     *   Hair color (R) */
    float hair_color_R;

    /* 髪の色(Ｇ)
     *   髪の色(Ｇ)
     * Hair - Color G
     *   Hair color (G) */
    float hair_color_G;

    /* 髪の色(Ｂ)
     *   髪の色(Ｂ)
     * Hair - Color B
     *   Hair color (B) */
    float hair_color_B;

    /* 光沢
     *   髪の光沢
     * Hair - Shininess
     *   Hair gloss */
    float hair_shininess;

    /* 根元の黒さ
     *   髪の根元の黒さ
     * Hair - Root Black
     *   Blackness at the base of hair */
    float hair_rootBlack;

    /* 白髪の量
     *   髪の白髪の量
     * Hair - White Density
     *   Amount of white hair */
    float hair_whiteDensity;

    /* 髭パーツID
     *   髭パーツID
     * Beard - Parts ID
     *   Beard part ID */
    float beard_partsId;

    /* 髭の色(Ｒ)
     *   髭の色(Ｒ)
     * Beard - Color R
     *   Beard color (R) */
    float beard_color_R;

    /* 髭の色(Ｇ)
     *   髭の色(Ｇ)
     * Beard - Color G
     *   Beard color (G) */
    float beard_color_G;

    /* 髭の色(Ｂ)
     *   髭の色(Ｂ)
     * Beard - Color B
     *   Beard color (B) */
    float beard_color_B;

    /* 光沢
     *   髭の光沢
     * Beard - Shininess
     *   Beard luster */
    float beard_shininess;

    /* 根元の黒さ
     *   髭の根元の黒さ
     * Beard - Root Black
     *   Blackness at the base of the beard */
    float beard_rootBlack;

    /* 白髪の量
     *   髭の白髪の量
     * Beard - White Density
     *   Amount of white hair with a beard */
    float beard_whiteDensity;

    /* 眉パーツID
     *   眉パーツID
     * Eyebrow - Parts ID
     *   Eyebrow part ID */
    float eyebrow_partsId;

    /* 眉の色(Ｒ)
     *   眉の色(Ｒ)
     * Eyebrow - Color R
     *   Eyebrow color (R) */
    float eyebrow_color_R;

    /* 眉の色(Ｇ)
     *   眉の色(Ｇ)
     * Eyebrow - Color G
     *   Eyebrow color (G) */
    float eyebrow_color_G;

    /* 眉の色(Ｂ)
     *   眉の色(Ｂ)
     * Eyebrow - Color B
     *   Eyebrow color (B) */
    float eyebrow_color_B;

    /* 光沢
     *   眉の光沢
     * Eyebrow - Shininess
     *   Glossy eyebrows */
    float eyebrow_shininess;

    /* 根元の黒さ
     *   眉の根元の黒さ
     * Eyebrow - Root Black
     *   Blackness at the base of the eyebrows */
    float eyebrow_rootBlack;

    /* 白髪の量
     *   眉の白髪の量
     * Eyebrow - White Density
     *   Amount of white hair on the eyebrows */
    float eyebrow_whiteDensity;

    /* まつげパーツID
     *   まつげパーツID
     * Eyelash - Parts ID
     *   Eyelash parts ID */
    float eyelash_partsId;

    /* まつげの色(Ｒ)
     *   まつげの色(Ｒ)
     * Eyelash - Color R
     *   Eyelash color (R) */
    float eyelash_color_R;

    /* まつげの色(Ｇ)
     *   まつげの色(Ｇ)
     * Eyelash - Color G
     *   Eyelash color (G) */
    float eyelash_color_G;

    /* まつげの色(Ｂ)
     *   まつげの色(Ｂ)
     * Eyelash - Color B
     *   Eyelash color (B) */
    float eyelash_color_B;

    /* 装飾パーツID
     *   装飾パーツID
     * Accessories - Parts ID
     *   Decorative part ID */
    float accessories_partsId;

    /* 装飾の色(Ｒ)
     *   装飾の色(Ｒ)
     * Accessories - Color R
     *   Decoration color (R) */
    float accessories_color_R;

    /* 装飾の色(Ｇ)
     *   装飾の色(Ｇ)
     * Accessories - Color G
     *   Decoration color (G) */
    float accessories_color_G;

    /* 装飾の色(Ｂ)
     *   装飾の色(Ｂ)
     * Accessories - Color B
     *   Decorative color (B) */
    float accessories_color_B;

    /* デカールパーツID
     *   デカールパーツID
     * Decal - Parts ID
     *   Decal part ID */
    float decal_partsId;

    /* デカール位置(x)
     *   デカール位置(x)
     * Decal - Position X
     *   Decal position (x) */
    float decal_posX;

    /* デカール位置(y)
     *   デカール位置(y)
     * Decal - Position Y
     *   Decal position (y) */
    float decal_posY;

    /* デカール角度
     *   デカール角度
     * Decal - Angle
     *   Decal angle */
    float decal_angle;

    /* デカールスケール
     *   デカールスケール
     * Decal - Scale
     *   Decal scale */
    float decal_scale;

    /* デカールの色(Ｒ)
     *   デカールの色(Ｒ)
     * Decal - Color R
     *   Decal color (R) */
    float decal_color_R;

    /* デカールの色(Ｇ)
     *   デカールの色(Ｇ)
     * Decal - Color G
     *   Decal color (G) */
    float decal_color_G;

    /* デカールの色(Ｂ)
     *   デカールの色(Ｂ)
     * Decal - Color B
     *   Decal color (B) */
    float decal_color_B;

    /* デカールのつや
     *   デカールのつや
     * Decal - Gloss
     *   Decal gloss */
    float decal_gloss;

    /* デカールの反転
     *   デカールの反転
     * Decal - Mirror
     *   Decal reversal */
    float decal_mirror;

    /* キャラ体型頭部スケール
     *   キャラ体型頭部スケール
     * Chr Body Scale - Head
     *   Character body head scale */
    float chrBodyScaleHead;

    /* キャラ体型胸部スケール
     *   キャラ体型胸部スケール
     * Chr Body Scale - Breast
     *   Character body chest scale */
    float chrBodyScaleBreast;

    /* キャラ体型腹部スケール
     *   キャラ体型腹部スケール
     * Chr Body Scale - Abdomen
     *   Character body type abdominal scale */
    float chrBodyScaleAbdomen;

    /* キャラ体型腕部スケール
     *   キャラ体型腕部スケール
     * Chr Body Scale - Arm
     *   Character body type arm scale */
    float chrBodyScaleArm;

    /* キャラ体型脚部スケール
     *   キャラ体型脚部スケール
     * Chr Body Scale - Leg
     *   Character body type leg scale */
    float chrBodyScaleLeg;

    /* 年齢
     *   年齢
     * Age
     *   age */
    float age;

    /* 性別
     *   性別
     * Gender
     *   sex */
    float gender;

    /* 誇張（モデル）
     *   誇張（モデル）
     * Model Geometry
     *   Exaggeration (model) */
    float caricatureGeometry;

    /* 誇張（テクスチャ）
     *   誇張（テクスチャ）
     * Model Texture
     *   Exaggeration (texture) */
    float caricatureTexture;

    /* 顔作成ジオメトリデータ00
     *   顔作成ジオメトリデータ00
     * Face - Geo Data [00]]
     *   Face - Geo Data [00] */
    float faceGeoData00;

    /* 顔作成ジオメトリデータ01
     *   顔作成ジオメトリデータ01
     * Face - Geo Data [01]
     *   Face - Geo Data [01] */
    float faceGeoData01;

    /* 顔作成ジオメトリデータ02
     *   顔作成ジオメトリデータ02
     * Face - Geo Data [02]
     *   Face - Geo Data [02] */
    float faceGeoData02;

    /* 顔作成ジオメトリデータ03
     *   顔作成ジオメトリデータ03
     * Face - Geo Data [03]
     *   Face - Geo Data [03] */
    float faceGeoData03;

    /* 顔作成ジオメトリデータ04
     *   顔作成ジオメトリデータ04
     * Face - Geo Data [04]
     *   Face - Geo Data [04] */
    float faceGeoData04;

    /* 顔作成ジオメトリデータ05
     *   顔作成ジオメトリデータ05
     * Face - Geo Data [05]
     *   Face - Geo Data [05] */
    float faceGeoData05;

    /* 顔作成ジオメトリデータ06
     *   顔作成ジオメトリデータ06
     * Face - Geo Data [06]
     *   Face - Geo Data [06] */
    float faceGeoData06;

    /* 顔作成ジオメトリデータ07
     *   顔作成ジオメトリデータ07
     * Face - Geo Data [07]
     *   Face - Geo Data [07] */
    float faceGeoData07;

    /* 顔作成ジオメトリデータ08
     *   顔作成ジオメトリデータ08
     * Face - Geo Data [08]
     *   Face - Geo Data [08] */
    float faceGeoData08;

    /* 顔作成ジオメトリデータ09
     *   顔作成ジオメトリデータ09
     * Face - Geo Data [09]
     *   Face - Geo Data [09] */
    float faceGeoData09;

    /* 顔作成ジオメトリデータ10
     *   顔作成ジオメトリデータ10
     * Face - Geo Data [10]
     *   Face - Geo Data [10] */
    float faceGeoData10;

    /* 顔作成ジオメトリデータ11
     *   顔作成ジオメトリデータ11
     * Face - Geo Data [11]
     *   Face - Geo Data [11] */
    float faceGeoData11;

    /* 顔作成ジオメトリデータ12
     *   顔作成ジオメトリデータ12
     * Face - Geo Data [12]
     *   Face - Geo Data [12] */
    float faceGeoData12;

    /* 顔作成ジオメトリデータ13
     *   顔作成ジオメトリデータ13
     * Face - Geo Data [13]
     *   Face - Geo Data [13] */
    float faceGeoData13;

    /* 顔作成ジオメトリデータ14
     *   顔作成ジオメトリデータ14
     * Face - Geo Data [14]
     *   Face - Geo Data [14] */
    float faceGeoData14;

    /* 顔作成ジオメトリデータ15
     *   顔作成ジオメトリデータ15
     * Face - Geo Data [15]
     *   Face - Geo Data [15] */
    float faceGeoData15;

    /* 顔作成ジオメトリデータ16
     *   顔作成ジオメトリデータ16
     * Face - Geo Data [16]
     *   Face - Geo Data [16] */
    float faceGeoData16;

    /* 顔作成ジオメトリデータ17
     *   顔作成ジオメトリデータ17
     * Face - Geo Data [17]
     *   Face - Geo Data [17] */
    float faceGeoData17;

    /* 顔作成ジオメトリデータ18
     *   顔作成ジオメトリデータ18
     * Face - Geo Data [18]
     *   Face - Geo Data [18] */
    float faceGeoData18;

    /* 顔作成ジオメトリデータ19
     *   顔作成ジオメトリデータ19
     * Face - Geo Data [19]
     *   Face - Geo Data [19] */
    float faceGeoData19;

    /* 顔作成ジオメトリデータ20
     *   顔作成ジオメトリデータ20
     * Face - Geo Data [20]
     *   Face - Geo Data [20] */
    float faceGeoData20;

    /* 顔作成ジオメトリデータ21
     *   顔作成ジオメトリデータ21
     * Face - Geo Data [21]
     *   Face - Geo Data [21] */
    float faceGeoData21;

    /* 顔作成ジオメトリデータ22
     *   顔作成ジオメトリデータ22
     * Face - Geo Data [22]
     *   Face - Geo Data [22] */
    float faceGeoData22;

    /* 顔作成ジオメトリデータ23
     *   顔作成ジオメトリデータ23
     * Face - Geo Data [23]
     *   Face - Geo Data [23] */
    float faceGeoData23;

    /* 顔作成ジオメトリデータ24
     *   顔作成ジオメトリデータ24
     * Face - Geo Data [24]
     *   Face - Geo Data [24] */
    float faceGeoData24;

    /* 顔作成ジオメトリデータ25
     *   顔作成ジオメトリデータ25
     * Face - Geo Data [25]
     *   Face - Geo Data [25] */
    float faceGeoData25;

    /* 顔作成ジオメトリデータ26
     *   顔作成ジオメトリデータ26
     * Face - Geo Data [26]
     *   Face - Geo Data [26] */
    float faceGeoData26;

    /* 顔作成ジオメトリデータ27
     *   顔作成ジオメトリデータ27
     * Face - Geo Data [27]
     *   Face - Geo Data [27] */
    float faceGeoData27;

    /* 顔作成ジオメトリデータ28
     *   顔作成ジオメトリデータ28
     * Face - Geo Data [28]
     *   Face - Geo Data [28] */
    float faceGeoData28;

    /* 顔作成ジオメトリデータ29
     *   顔作成ジオメトリデータ29
     * Face - Geo Data [29]
     *   Face - Geo Data [29] */
    float faceGeoData29;

    /* 顔作成ジオメトリデータ30
     *   顔作成ジオメトリデータ30
     * Face - Geo Data [30]
     *   Face - Geo Data [30] */
    float faceGeoData30;

    /* 顔作成ジオメトリデータ31
     *   顔作成ジオメトリデータ31
     * Face - Geo Data [31]
     *   Face - Geo Data [31] */
    float faceGeoData31;

    /* 顔作成ジオメトリデータ32
     *   顔作成ジオメトリデータ32
     * Face - Geo Data [32]
     *   Face - Geo Data [32] */
    float faceGeoData32;

    /* 顔作成ジオメトリデータ33
     *   顔作成ジオメトリデータ33
     * Face - Geo Data [33]
     *   Face - Geo Data [33] */
    float faceGeoData33;

    /* 顔作成ジオメトリデータ34
     *   顔作成ジオメトリデータ34
     * Face - Geo Data [34]
     *   Face - Geo Data [34] */
    float faceGeoData34;

    /* 顔作成ジオメトリデータ35
     *   顔作成ジオメトリデータ35
     * Face - Geo Data [35]
     *   Face - Geo Data [35] */
    float faceGeoData35;

    /* 顔作成ジオメトリデータ36
     *   顔作成ジオメトリデータ36
     * Face - Geo Data [36]
     *   Face - Geo Data [36] */
    float faceGeoData36;

    /* 顔作成ジオメトリデータ37
     *   顔作成ジオメトリデータ37
     * Face - Geo Data [37]
     *   Face - Geo Data [37] */
    float faceGeoData37;

    /* 顔作成ジオメトリデータ38
     *   顔作成ジオメトリデータ38
     * Face - Geo Data [38]
     *   Face - Geo Data [38] */
    float faceGeoData38;

    /* 顔作成ジオメトリデータ39
     *   顔作成ジオメトリデータ39
     * Face - Geo Data [39]
     *   Face - Geo Data [39] */
    float faceGeoData39;

    /* 顔作成ジオメトリデータ40
     *   顔作成ジオメトリデータ40
     * Face - Geo Data [40]
     *   Face - Geo Data [40] */
    float faceGeoData40;

    /* 顔作成ジオメトリデータ41
     *   顔作成ジオメトリデータ41
     * Face - Geo Data [41]
     *   Face - Geo Data [41] */
    float faceGeoData41;

    /* 顔作成ジオメトリデータ42
     *   顔作成ジオメトリデータ42
     * Face - Geo Data [42]
     *   Face - Geo Data [42] */
    float faceGeoData42;

    /* 顔作成ジオメトリデータ43
     *   顔作成ジオメトリデータ43
     * Face - Geo Data [43]
     *   Face - Geo Data [43] */
    float faceGeoData43;

    /* 顔作成ジオメトリデータ44
     *   顔作成ジオメトリデータ44
     * Face - Geo Data [44]
     *   Face - Geo Data [44] */
    float faceGeoData44;

    /* 顔作成ジオメトリデータ45
     *   顔作成ジオメトリデータ45
     * Face - Geo Data [45]
     *   Face - Geo Data [45] */
    float faceGeoData45;

    /* 顔作成ジオメトリデータ46
     *   顔作成ジオメトリデータ46
     * Face - Geo Data [46]
     *   Face - Geo Data [46] */
    float faceGeoData46;

    /* 顔作成ジオメトリデータ47
     *   顔作成ジオメトリデータ47
     * Face - Geo Data [47]
     *   Face - Geo Data [47] */
    float faceGeoData47;

    /* 顔作成ジオメトリデータ48
     *   顔作成ジオメトリデータ48
     * Face - Geo Data [48]
     *   Face - Geo Data [48] */
    float faceGeoData48;

    /* 顔作成ジオメトリデータ49
     *   顔作成ジオメトリデータ49
     * Face - Geo Data [49]
     *   Face - Geo Data [49] */
    float faceGeoData49;

    /* 顔作成ジオメトリデータ50
     *   顔作成ジオメトリデータ50
     * Face - Geo Data [50]
     *   Face - Geo Data [50] */
    float faceGeoData50;

    /* 顔作成ジオメトリデータ51
     *   顔作成ジオメトリデータ51
     * Face - Geo Data [51]
     *   Face - Geo Data [51] */
    float faceGeoData51;

    /* 顔作成ジオメトリデータ52
     *   顔作成ジオメトリデータ52
     * Face - Geo Data [52]
     *   Face - Geo Data [52] */
    float faceGeoData52;

    /* 顔作成ジオメトリデータ53
     *   顔作成ジオメトリデータ53
     * Face - Geo Data [53]
     *   Face - Geo Data [53] */
    float faceGeoData53;

    /* 顔作成ジオメトリデータ54
     *   顔作成ジオメトリデータ54
     * Face - Geo Data [54]
     *   Face - Geo Data [54] */
    float faceGeoData54;

    /* 顔作成ジオメトリデータ55
     *   顔作成ジオメトリデータ55
     * Face - Geo Data [55]
     *   Face - Geo Data [55] */
    float faceGeoData55;

    /* 顔作成ジオメトリデータ56
     *   顔作成ジオメトリデータ56
     * Face - Geo Data [56]
     *   Face - Geo Data [56] */
    float faceGeoData56;

    /* 顔作成ジオメトリデータ57
     *   顔作成ジオメトリデータ57
     * Face - Geo Data [57]
     *   Face - Geo Data [57] */
    float faceGeoData57;

    /* 顔作成ジオメトリデータ58
     *   顔作成ジオメトリデータ58
     * Face - Geo Data [58]
     *   Face - Geo Data [58] */
    float faceGeoData58;

    /* 顔作成ジオメトリデータ59
     *   顔作成ジオメトリデータ59
     * Face - Geo Data [59]
     *   Face - Geo Data [59] */
    float faceGeoData59;

    /* 顔作成ジオメトリデータ60
     *   顔作成ジオメトリデータ60
     * Face - Geo Data [60]
     *   Face - Geo Data [60] */
    float faceGeoData60;

    /* 顔作成テクスチャデータ00
     *   顔作成テクスチャデータ00
     * Face - Texture Data [00]
     *   Face - Texture Data [00] */
    float faceTexData00;

    /* 顔作成テクスチャデータ01
     *   顔作成テクスチャデータ01
     * Face - Texture Data [01]
     *   Face - Texture Data [01] */
    float faceTexData01;

    /* 顔作成テクスチャデータ02
     *   顔作成テクスチャデータ02
     * Face - Texture Data [02]
     *   Face - Texture Data [02] */
    float faceTexData02;

    /* 顔作成テクスチャデータ03
     *   顔作成テクスチャデータ03
     * Face - Texture Data [03]
     *   Face - Texture Data [03] */
    float faceTexData03;

    /* 顔作成テクスチャデータ04
     *   顔作成テクスチャデータ04
     * Face - Texture Data [04]
     *   Face - Texture Data [04] */
    float faceTexData04;

    /* 顔作成テクスチャデータ05
     *   顔作成テクスチャデータ05
     * Face - Texture Data [05]
     *   Face - Texture Data [05] */
    float faceTexData05;

    /* 顔作成テクスチャデータ06
     *   顔作成テクスチャデータ06
     * Face - Texture Data [06]
     *   Face - Texture Data [06] */
    float faceTexData06;

    /* 顔作成テクスチャデータ07
     *   顔作成テクスチャデータ07
     * Face - Texture Data [07]
     *   Face - Texture Data [07] */
    float faceTexData07;

    /* 顔作成テクスチャデータ08
     *   顔作成テクスチャデータ08
     * Face - Texture Data [08]
     *   Face - Texture Data [08] */
    float faceTexData08;

    /* 顔作成テクスチャデータ09
     *   顔作成テクスチャデータ09
     * Face - Texture Data [09]
     *   Face - Texture Data [09] */
    float faceTexData09;

    /* 顔作成テクスチャデータ10
     *   顔作成テクスチャデータ10
     * Face - Texture Data [10]
     *   Face - Texture Data [10] */
    float faceTexData10;

    /* 顔作成テクスチャデータ11
     *   顔作成テクスチャデータ11
     * Face - Texture Data [11]
     *   Face - Texture Data [11] */
    float faceTexData11;

    /* 顔作成テクスチャデータ12
     *   顔作成テクスチャデータ12
     * Face - Texture Data [12]
     *   Face - Texture Data [12] */
    float faceTexData12;

    /* 顔作成テクスチャデータ13
     *   顔作成テクスチャデータ13
     * Face - Texture Data [13]
     *   Face - Texture Data [13] */
    float faceTexData13;

    /* 顔作成テクスチャデータ14
     *   顔作成テクスチャデータ14
     * Face - Texture Data [14]
     *   Face - Texture Data [14] */
    float faceTexData14;

    /* 顔作成テクスチャデータ15
     *   顔作成テクスチャデータ15
     * Face - Texture Data [15]
     *   Face - Texture Data [15] */
    float faceTexData15;

    /* 顔作成テクスチャデータ16
     *   顔作成テクスチャデータ16
     * Face - Texture Data [16]
     *   Face - Texture Data [16] */
    float faceTexData16;

    /* 顔作成テクスチャデータ17
     *   顔作成テクスチャデータ17
     * Face - Texture Data [17]
     *   Face - Texture Data [17] */
    float faceTexData17;

    /* 顔作成テクスチャデータ18
     *   顔作成テクスチャデータ18
     * Face - Texture Data [18]
     *   Face - Texture Data [18] */
    float faceTexData18;

    /* 顔作成テクスチャデータ19
     *   顔作成テクスチャデータ19
     * Face - Texture Data [19]
     *   Face - Texture Data [19] */
    float faceTexData19;

    /* 顔作成テクスチャデータ20
     *   顔作成テクスチャデータ20
     * Face - Texture Data [20]
     *   Face - Texture Data [20] */
    float faceTexData20;

    /* 顔作成テクスチャデータ21
     *   顔作成テクスチャデータ21
     * Face - Texture Data [21]
     *   Face - Texture Data [21] */
    float faceTexData21;

    /* 顔作成テクスチャデータ22
     *   顔作成テクスチャデータ22
     * Face - Texture Data [22]
     *   Face - Texture Data [22] */
    float faceTexData22;

    /* 顔作成テクスチャデータ23
     *   顔作成テクスチャデータ23
     * Face - Texture Data [23]
     *   Face - Texture Data [23] */
    float faceTexData23;

    /* 顔作成テクスチャデータ24
     *   顔作成テクスチャデータ24
     * Face - Texture Data [24]
     *   Face - Texture Data [24] */
    float faceTexData24;

    /* 顔作成テクスチャデータ25
     *   顔作成テクスチャデータ25
     * Face - Texture Data [25]
     *   Face - Texture Data [25] */
    float faceTexData25;

    /* 顔作成テクスチャデータ26
     *   顔作成テクスチャデータ26
     * Face - Texture Data [26]
     *   Face - Texture Data [26] */
    float faceTexData26;

    /* 顔作成テクスチャデータ27
     *   顔作成テクスチャデータ27
     * Face - Texture Data [27]
     *   Face - Texture Data [27] */
    float faceTexData27;

    /* 顔作成テクスチャデータ28
     *   顔作成テクスチャデータ28
     * Face - Texture Data [28]
     *   Face - Texture Data [28] */
    float faceTexData28;

    /* 顔作成テクスチャデータ29
     *   顔作成テクスチャデータ29
     * Face - Texture Data [29]
     *   Face - Texture Data [29] */
    float faceTexData29;

    /* 顔作成テクスチャデータ30
     *   顔作成テクスチャデータ30
     * Face - Texture Data [30]
     *   Face - Texture Data [30] */
    float faceTexData30;

    /* 顔作成テクスチャデータ31
     *   顔作成テクスチャデータ31
     * Face - Texture Data [31]
     *   Face - Texture Data [31] */
    float faceTexData31;

    /* 顔作成テクスチャデータ32
     *   顔作成テクスチャデータ32
     * Face - Texture Data [32]
     *   Face - Texture Data [32] */
    float faceTexData32;

    /* 顔作成テクスチャデータ33
     *   顔作成テクスチャデータ33
     * Face - Texture Data [33]
     *   Face - Texture Data [33] */
    float faceTexData33;

    /* 顔作成テクスチャデータ34
     *   顔作成テクスチャデータ34
     * Face - Texture Data [34]
     *   Face - Texture Data [34] */
    float faceTexData34;

    /* 顔作成テクスチャデータ35
     *   顔作成テクスチャデータ35
     * Face - Texture Data [35]
     *   Face - Texture Data [35] */
    float faceTexData35;

    /* 火傷跡
     *   火傷跡
     * Burn Scars
     *   Burn scars */
    float burn_scar;
} er_face_range_param_t;
