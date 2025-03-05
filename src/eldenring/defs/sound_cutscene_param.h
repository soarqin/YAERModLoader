#pragma once

typedef struct er_sound_cutscene_param_s {
    /* NT版出力から外すか
     *   ○をつけたパラメータをNT版パッケージでは除外します
     * Disable Param - Network Test
     *   Parameters marked with  are excluded in the NT version package. */
    unsigned char disableParam_NT:1;

    /* パッケージ出力用リザーブ1
     *   パッケージ出力用リザーブ1 */
    char disableParamReserve1:7;

    /* パッケージ出力用リザーブ2
     *   パッケージ出力用リザーブ2 */
    char disableParamReserve2[3];

    /* カットシーン中のリバーブタイプ
     *   カットシーン中に適応するリバーブタイプを指定します
     * Reverb Type
     *   Specifies the reverb type to apply during the cutscene */
    unsigned char ReverbType;

    char pad0[3];

    /* カットシーン開始時通常BGM挙動
     *   カットシーン開始時通常BGM挙動を指定します
     * BGM Behavior Type On Start
     *   Specifies normal BGM behavior at the start of cutscenes */
    short BgmBehaviorTypeOnStart;

    /* カットシーン開始時ワンショットBGM挙動
     *   カットシーン開始時ワンショットBGM挙動を指定します
     * One-shot BGM Behavior Type On Start
     *   Specifies the one-shot BGM behavior at the start of the cutscene */
    short OneShotBgmBehaviorOnStart;

    /* カットシーン終了時にポストするSEID（カテゴリ：p)指定(-1:ポストしない)
     *   カットシーン終了時にポストするSEID（カテゴリ：p)指定(-1:ポストしない)
     * Post Play SE ID
     *   SEID (category: p) specification to post at the end of the cutscene (-1: do not post)
     * Default Value  = -1 */
    int PostPlaySeId;

    /* カットシーン終了時にポストするSEID_スキップ時（カテゴリ：p)指定(-1:ポストしない)
     *   カットシーン終了時にポストするSEID_スキップ時用（カテゴリ：p)指定(-1:ポストしない)
     * Post Play SE ID for Skip
     *   SEID_ for skipping to post at the end of the cutscene (category: p) specified (-1: not posted)
     * Default Value  = -1 */
    int PostPlaySeIdForSkip;

    /* 入場直後ミュート解除するカットシーン描画時間[秒](0より小さい：描画時間で解除しない)
     *   入場直後のミュート解除するカットシーン描画時間[秒](0より小さい：描画時間で解除しない)
     * Enter Map Mute Stop Time on Draw Cutscene
     *   Cutscene drawing time to unmute immediately after entering [seconds] (less than 0: not canceled in drawing time)
     * Default Value  = -1 */
    float EnterMapMuteStopTimeOnDrawCutscene;

    unsigned char unknown_0x18;

    unsigned char unknown_0x19;

    unsigned char unknown_0x1a;

    unsigned char unknown_0x1b;

    /* リザーブ
     *   リザーブ */
    char reserved[4];

    char reserved2[4];
} er_sound_cutscene_param_t;
