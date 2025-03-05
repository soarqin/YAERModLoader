#pragma once

typedef struct er_throw_param_s {
    /* 投げ側キャラID
     *   投げ側キャラID
     * Attacker - Character ID
     *   Throwing side character ID */
    int AtkChrId;

    /* 受け側キャラID
     *   受け側キャラID
     * Defender - Character ID
     *   Recipient character ID */
    int DefChrId;

    /* 有効距離[m]
     *   この値より近い距離じゃないと投げない[m]
     * Max Throw Distance
     *   Do not throw unless the distance is closer than this value [m] */
    float Dist;

    /* 自分の向きと相手の向きの角度差範囲min
     *   投げ側と受け側の角度差(Y軸)がこの角度より大きくないと投げない
     * Height Angle Difference - Min
     *   If the angle difference (Y-axis) between the throwing side and the receiving side is not larger than this angle, it will not be thrown. */
    float DiffAngMin;

    /* 自分の向きと相手の向きの角度差範囲max
     *   投げ側と受け側の角度差(Y軸)がこの角度より小さくないと投げない
     * Height Angle Difference - Max
     *   If the angle difference (Y-axis) between the throwing side and the receiving side is smaller than this angle, it will not be thrown. */
    float DiffAngMax;

    /* 高さ範囲上[m]
     *   投げ側から受け側のY軸の相対距離がこの値より小さくないと投げない
     * Upper Height Range
     *   Do not throw unless the relative distance of the Y axis from the throwing side to the receiving side is smaller than this value
     * Default Value  = 0.2 */
    float upperYRange;

    /* 高さ範囲下[m]
     *   投げ側から受け側のY軸の相対距離がこの値より小さくないと投げない
     * Lower Height Range
     *   Do not throw unless the relative distance of the Y axis from the throwing side to the receiving side is smaller than this value
     * Default Value  = 0.2 */
    float lowerYRange;

    /* 自分の向きと自分から相手への方向の角度差
     *   自分の正面のベクトルと、自分から相手への方向のベクトルの角度差。この値より大きいと投げない
     * Angle Difference - To Defender
     *   The angle difference between the vector in front of you and the vector in the direction from you to the other party. If it is larger than this value, it will not be thrown
     * Default Value  = 60 */
    float diffAngMyToDef;

    /* 投げタイプID
     *   投げの種類を特定するID(攻撃パラメタと紐付け)
     * Throw Type ID
     *   ID that identifies the type of throw (association with attack parameter) */
    int throwTypeId;

    /* 投げ側アニメID
     *   攻撃アニメIDを設定(EzStateと紐付け)
     * Attacker - Animation ID
     *   Set attack animation ID (linked to EzState) */
    int atkAnimId;

    /* 受け側アニメID
     *   ダメージアニメIDを設定(EzStateと紐付け)
     * Defender - Animation ID
     *   Set damage animation ID (linked to EzState) */
    int defAnimId;

    /* 投げ抜けHP
     *   投げ抜けに耐えられる値
     * Self Escape - HP
     *   Value that can withstand throwing through */
    unsigned short escHp;

    /* 自力投げ抜けサイクル時間[ms]
     *   自力投げ抜けのサイクル時間[ms]
     * Self Escape - Cycle Time
     *   Cycle time for self-throwing [ms] */
    unsigned short selfEscCycleTime;

    /* スフィアキャスト半径比率_上[1/100Rate]
     *   スフィアキャストの上側半径の比率[80->0.8]
     * Sphere Cast - Radius Rate Top
     *   Ratio of upper radius of sphere cast [80-> 0.8]
     * Default Value  = 80 */
    unsigned short sphereCastRadiusRateTop;

    /* スフィアキャスト半径比率_下[1/100Rate]
     *   スフィアキャストの下側半径の比率[80->0.8]
     * Sphere Cast - Radius Rate Low
     *   Spherecast lower radius ratio [80-> 0.8]
     * Default Value  = 80 */
    unsigned short sphereCastRadiusRateLow;

    /* 操作タイプ
     *   操作タイプ
     * Operation Type
     *   Operation type
     * Default Value  = 1 */
    unsigned char PadType;

    /* 投げ側の投げ可能状態タイプ
     *   投げ側の投げが可能な状態タイプを設定してください
     * Attack Enable State
     *   Please set the state type that can be thrown on the throwing side */
    unsigned char AtkEnableState;

    /* 投げ追従方式
     *   投げ実行中、吸着ダミポリ所持キャラにどのように追従するか。※追従期間はTAEアクションでコントロール
     * Throw Following Type
     *   How to follow the character possessed by Adsorbed Damipoli while throwing. * Follow-up period is controlled by TAE action */
    unsigned char throwFollowingType;

    /* pad
     *   pad */
    char pad2[1];

    /* 投げ種別
     *   投げの種別
     * Throw Type
     *   Type of throw */
    unsigned char throwType;

    /* 自力投げ抜けサイクル回数
     *   自力投げ抜けのサイクル回数
     * Self Escape - Cycle Count
     *   Number of self-throwing cycles */
    unsigned char selfEscCycleCnt;

    /* 投げ発生時のダミポリ所持キャラの向き
     *   投げ発生時のダミポリ所持キャラの向き
     * Character Throw - Dummy Poly Direction Type
     *   Direction of Damipoli possession character when throwing occurs */
    unsigned char dmyHasChrDirType;

    /* 投げ側が旋回するか？
     *   投げ側が旋回するか？
     * Throw can Side Turn
     *   Does the throwing side turn? */
    unsigned char isTurnAtker:1;

    /* 武器カテゴリチェックをスキップするか？
     *   攻撃側の武器カテゴリチェックをスキップするか？
     * Skip Attacker Weapon Category Check
     *   Do you want to skip the attacker's weapon category check? */
    unsigned char isSkipWepCate:1;

    /* スフィアキャストをスキップするか？
     *   スフィアキャストをスキップするか？
     * Skip Sphere Cast
     *   Do you want to skip the sphere cast? */
    unsigned char isSkipSphereCast:1;

    /* 投げ吸着時、平地相当の位置関係に戻すか
     *   ◯にすると投げ位置合わせの場所が「平地相当の位置関係に戻した吸着ダミポリの位置」になる
     * Enable Correct Position for Throw Adjustment
     *   If it is set to , the location of the throwing position will be the position of the adsorption Damipoli that has returned to the positional relationship equivalent to the flat ground.
     * Default Value  = 1 */
    unsigned char isEnableCorrectPos_forThrowAdjust:1;

    /* 投げ追従解除時の落下を防止するか？
     *   追従解除時に段差から落下しないよう、壁抜け防止と同じ処理を落下防止壁に対しても行うか？
     * Enable Throw Following Fall Assist
     *   Is the same treatment as the wall removal prevention applied to the fall prevention wall so that it does not fall from the step when the follow-up is released?
     * Default Value  = 1 */
    unsigned char isEnableThrowFollowingFallAssist:1;

    /* 投げ追従中の壁めり込みを抑制するか？
     *   追従中壁にめり込んだり段差から落下しそうな見た目にならないよう、ヒットや落下防止壁に接触したときに吸着ダミポリ所持キャラごと戻す処理を行うか？
     * Enable Throw Following Feedback
     *   Do you want to return the character with the Adsorbed Damipoli when it comes in contact with a hit or fall prevention wall so that it does not look like it will get stuck in the middle wall or fall from a step?
     * Default Value  = 1 */
    unsigned char isEnableThrowFollowingFeedback:1;

    /* pad
     *   pad */
    char pad0:2;

    /* 投げ側 吸着ダミポリID
     *   投げ側のどこに受け側を吸着させるか？
     * Attacker - Absorb Dummy ID
     *   Where on the throwing side should the receiving side be attracted? */
    short atkSorbDmyId;

    /* 受け側 吸着ダミポリID
     *   受け側のどこに投げ側を吸着させるか？
     * Defender - Absorb Dummy ID
     *   Where on the receiving side should the throwing side be adsorbed? */
    short defSorbDmyId;

    /* 有効距離(投げ開始)[m]
     *   この値より近い距離じゃないと投げない[m]　バックスタブ開始時の投げに使われる
     * Backstab - Max Throw Distance 
     *   Only throw at a distance closer than this value [m] Used for throwing at the start of the Backstab */
    float Dist_start;

    /* 自分の向きと相手の向きの角度差範囲min(投げ開始)
     *   投げ側と受け側の角度差(Y軸)がこの角度より大きくないと投げない　バックスタブ開始時の投げに使われる
     * Backstab - Height Angle Difference - Min
     *   If the angle difference (Y-axis) between the throwing side and the receiving side is not larger than this angle, it will not be thrown. It is used for throwing at the start of the Backstab. */
    float DiffAngMin_start;

    /* 自分の向きと相手の向きの角度差範囲max(投げ開始)
     *   投げ側と受け側の角度差(Y軸)がこの角度より小さくないと投げない　バックスタブ開始時の投げに使われる
     * Backstab - Height Angle Difference - Max
     *   The angle difference (Y-axis) between the throwing side and the receiving side must be smaller than this angle to throw. Used for throwing at the start of the Backstab. */
    float DiffAngMax_start;

    /* 高さ範囲上(投げ開始)[m]
     *   投げ側から受け側のY軸の相対距離がこの値より小さくないと投げない　バックスタブ開始時の投げに使われる
     * Backstab - Upper Height Range
     *   It will not be thrown unless the relative distance of the Y axis from the throwing side to the receiving side is smaller than this value. It is used for throwing at the start of the Backstab. */
    float upperYRange_start;

    /* 高さ範囲下(投げ開始)[m]
     *   投げ側から受け側のY軸の相対距離がこの値より小さくないと投げない　バックスタブ開始時の投げに使われる
     * Backstab - Lower Height Range
     *   It will not be thrown unless the relative distance of the Y axis from the throwing side to the receiving side is smaller than this value. It is used for throwing at the start of the Backstab. */
    float lowerYRange_start;

    /* 自分の向きと自分から相手への方向の角度差(投げ開始)
     *   自分の正面のベクトルと、自分から相手への方向のベクトルの角度差。この値より大きいと投げない　バックスタブ開始時の投げに使われる
     * Backstab - Angle Difference - To Defender
     *   The angle difference between the vector in front of you and the vector in the direction from you to the other party. If it is larger than this value, it will not be thrown. It will be used for throwing at the start of the Backstab. */
    float diffAngMyToDef_start;

    /* 投げ側の投げ範囲判定基準ダミポリId
     *   投げ側が、投げ範囲を計算するときに自分の位置と見なすダミポリ。-1ならカプセル原点
     * Attacker - Throwing Range Judgment - Dummy Poly ID
     *   Damipoli that the thrower considers to be his position when calculating the throw range. If -1, the capsule origin
     * Default Value  = -1 */
    int judgeRangeBasePosDmyId1;

    /* 投られ側の投げ範囲判定基準ダミポリId
     *   投げられ側が、投げ範囲を計算するときに自分の位置と見なすダミポリ。-1ならカプセル原点
     * Defender - Throwing Range Judgment - Dummy Poly ID
     *   Damipoli that the thrower considers to be his position when calculating the throw range. If -1, the capsule origin
     * Default Value  = -1 */
    int judgeRangeBasePosDmyId2;

    /* 吸着時モデル位置補間時間[s]
     *   カプセルが吸着ダミポリに吸着したあと、キャラモデルが投げアニメデータ通りの位置に補間移動する時間（0を設定した場合はモデル位置の補間が行われず、吸着直後からアニメデータ通りの位置関係で再生開始される）
     * Absorb Model Position Interpolation Time
     *   After the capsule is adsorbed on Damipoli, the time it takes for the character model to interpolate and move to the position according to the throwing animation data (when 0 is set, the model position is not interpolated and playback starts immediately after adsorption with the positional relationship according to the animation data. Will be)
     * Default Value  = 0.5 */
    float adsrobModelPosInterpolationTime;

    /* 追従終了時モデル位置補間時間[s]
     *   追従終了時モデル位置補間時間
     * Throw Following End Easing Time
     *   Model position interpolation time at the end of tracking
     * Default Value  = 0.5 */
    float throwFollowingEndEasingTime;

    /* pad
     *   pad */
    char pad1[24];
} er_throw_param_t;
