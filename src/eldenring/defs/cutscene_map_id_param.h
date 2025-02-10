#pragma once

typedef struct cutscene_map_id_param_s {
    /* NT版出力から外すか
     *   ○をつけたパラメータをNT版パッケージでは除外します
     * Disable Param - Network Test
     *   Parameters marked with  are excluded in the NT version package. */
    unsigned char disableParam_NT:1;

    /* デバッグパラメータか
     *   ○をつけたパラメータは全パッケージから除外します（デバッグ用なので）
     * Disable Param - Debug
     *   Parameters marked with a circle are excluded from all packages (because they are for debugging). */
    unsigned char disableParam_Debug:1;

    /* パッケージ出力用リザーブ1
     *   パッケージ出力用リザーブ1 */
    char disableParamReserve1:6;

    /* パッケージ出力用リザーブ2
     *   パッケージ出力用リザーブ2 */
    char disableParamReserve2[3];

    /* 再生を行なうマップ番号
     *   再生を行なうマップ番号を8桁の数字で入力して下さい。カットシーンで基準としているマップの番号になります。正しいマップ番号を指定しないと再生位置がずれます。
     * Play Map ID
     *   Please enter the map number to be played back as an 8-digit number. This is the map number used as the reference in the cutscene. If you do not specify the correct map number, the playback position will shift. */
    unsigned int PlayMapId;

    /* 表示に必要なマップ番号１
     *   表示に必要なマップ番号を8桁の数字で入力して下さい。このパラメータは、ゲスト側がカットシーンを再生可能か判断するためのリストとして利用します。必要ない場合は、0もしくは未記入で良いです。
     * Require Map ID 0
     *   Please enter the map number required for display as an 8-digit number. This parameter is used by the guest as a list to determine if the cutscene can be played. If you don't need it, you can leave it as 0 or blank. */
    unsigned int RequireMapId0;

    /* 表示に必要なマップ番号２
     *   表示に必要なマップ番号を8桁の数字で入力して下さい。このパラメータは、ゲスト側がカットシーンを再生可能か判断するためのリストとして利用します。必要ない場合は、0もしくは未記入で良いです。
     * Require Map ID 1
     *   Please enter the map number required for display as an 8-digit number. This parameter is used by the guest as a list to determine if the cutscene can be played. If you don't need it, you can leave it as 0 or blank. */
    unsigned int RequireMapId1;

    /* 表示に必要なマップ番号３
     *   表示に必要なマップ番号を8桁の数字で入力して下さい。このパラメータは、ゲスト側がカットシーンを再生可能か判断するためのリストとして利用します。必要ない場合は、0もしくは未記入で良いです。
     * Require Map ID 2
     *   Please enter the map number required for display as an 8-digit number. This parameter is used by the guest as a list to determine if the cutscene can be played. If you don't need it, you can leave it as 0 or blank. */
    unsigned int RequireMapId2;

    /* 読み込み中カメラ位置算出用ヒットパーツID
     *   読み込み中カメラ位置算出用ヒットパーツID
     * Hit Part ID for Reference Camera
     *   Hit part ID for calculating camera position during loading
     * Default Value  = -1 */
    int RefCamPosHitPartsID;

    int unknown_0x18;

    /* 予備 */
    char reserved_2[8];

    /* 表示不可能時待機時間[秒]
     *   マルチにおいてゲスト側が再生できない状態の時に表示されるロード画面プログレスバーの進捗表示に使われる秒数です。【GR】SEQ22843 【カットシーン】カットシーン再生時に表示に必要なマップ番号を読み込んでいないプレイヤーは画面暗転する対応
     * Client Load View - Progress Bar Time
     *   The number of seconds used to display the progress of the loading screen progress bar that is displayed when the guest side cannot play in the multi. [GR] SEQ22843 [Cutscene] Players who have not read the map number required for display during cutscene playback will see the screen go dark. */
    unsigned short ClientDisableViewTimeForProgress;

    char reserved[2];

    /* 読み込み待ちヒットパーツ0
     *   読み込み待ちヒットパーツ0
     * Hit Parts [0]
     *   Hit parts waiting to be read 0
     * Default Value  = -1 */
    int HitParts_0;

    /* 読み込み待ちヒットパーツ1
     *   読み込み待ちヒットパーツ1
     * Hit Parts [1]
     *   Hit parts waiting to be read 1
     * Default Value  = -1 */
    int HitParts_1;
} cutscene_map_id_param_t;
