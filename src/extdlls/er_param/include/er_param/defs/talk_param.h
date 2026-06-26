#pragma once

typedef struct er_talk_param_s {
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

    /* PC性別が男：メッセージID
     *   PC性別が男：メッセージを指定->メニュー
     * Male - Message ID
     *   PC Gender is Male: Specify Message-> Menu
     * Default Value  = -1 */
    int msgId;

    /* PC性別が男：ボイスID
     *   PC性別が男：ボイスを指定->サウンド
     * Male - Voice ID
     *   PC Gender is Male: Specify Voice-> Sound
     * Default Value  = -1 */
    int voiceId;

    /* 特殊効果ID0
     *   特殊効果を指定->キャラ
     * SpEffect ID [0]
     *   Specify special effects-> Character
     * Default Value  = -1 */
    int spEffectId0;

    /* モーションID0
     *   モーションを指定->キャラ
     * Motion ID [0]
     *   Specify motion-> Character
     * Default Value  = -1 */
    int motionId0;

    /* 特殊効果ID1
     *   特殊効果を指定->キャラ
     * SpEffect ID [1]
     *   Specify special effects-> Character
     * Default Value  = -1 */
    int spEffectId1;

    /* モーションID1
     *   モーションを指定->キャラ
     * Motion ID [1]
     *   Specify motion-> Character
     * Default Value  = -1 */
    int motionId1;

    /* 復帰位置
     *   復帰する会話の相対位置->会話
     * Return Position
     *   Relative position of returning conversation-> Conversation
     * Default Value  = -1 */
    int returnPos;

    /* リアクションID
     *   復帰時の会話指定->会話
     * Reaction ID
     *   Conversation specification when returning-> Conversation
     * Default Value  = -1 */
    int reactionId;

    /* イベントID
     *   イベントID->イベント
     * Event ID
     *   Event ID-> Event
     * Default Value  = -1 */
    int eventId;

    /* PC性別が女：メッセージ
     *   PC性別が女：メッセージを指定->メニュー
     * Female - Message ID
     *   PC Gender is Female: Specify Message-> Menu
     * Default Value  = -1 */
    int msgId_female;

    /* PC性別が女：ボイスID
     *   PC性別が女：ボイスを指定->サウンド
     * Female - Voice ID
     *   PC Gender is Female: Specify Voice-> Sound
     * Default Value  = -1 */
    int voiceId_female;

    /* 話者：口パク開始時間
     *   話者：口パク開始時間。-1で口パク無し
     * Lip Sync Start
     *   Speaker: Lip-sync start time. -1 with no lip-sync
     * Default Value  = -1 */
    short lipSyncStart;

    /* 話者：口パク継続時間
     *   話者：口パク継続時間。-1で口パクずっと継続
     * Lip Sync Time
     *   Speaker: Lip-sync duration. Lip-sync at -1 continues forever
     * Default Value  = -1 */
    short lipSyncTime;

    /* パディング */
    char pad2[4];

    /* ボイス再生タイムアウト時間
     *   ボイス再生タイムアウト時間。-1の場合は「共通_ゲームシステムパラメータ」の「NPC会話ボイス再生タイムアウト時間」でタイムアウト処理を行う。
     * Voice Playback Timeout
     *   Voice playback timeout period. In case of -1, time-out processing is performed in NPC conversation voice playback timeout time of Common_Game system parameter.
     * Default Value  = -1 */
    float timeout;

    /* 話者：字幕芝居アニメID
     *   話者：会話中のアニメーションID
     * Talk Animation ID
     *   Speaker: Animation ID during conversation
     * Default Value  = -1 */
    int talkAnimationId;

    /* 強制的に字幕を表示するか
     *   強制的に字幕を表示するか。オプションで字幕オフでも字幕を表示する
     * Force Subtitle Display
     *   Do you want to force the display of subtitles? Display subtitles even when subtitles are turned off as an option */
    unsigned char isForceDisp:1;

    /* パディング */
    char pad3:7;

    /* パディング
     *   パディング */
    char pad1[31];
} er_talk_param_t;
