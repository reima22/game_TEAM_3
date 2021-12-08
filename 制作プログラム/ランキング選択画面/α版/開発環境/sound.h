//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

class CSound
{
public:
	CSound();
	~CSound();
	//サウンドファイル
	typedef enum
	{
		SOUND_LABEL_BGM000,				// BGM0
		SOUND_LABEL_BGM001,				// BGM1
		SOUND_LABEL_BGM002,				// BGM2
		SOUND_LABEL_BGM003,				// BGM3
		SOUND_LABEL_BGM004,				// BGM4
		SOUND_LABEL_BGM005,				// BGM5
		SOUND_LABEL_SE_JUMP,			// ジャンプ音
		SOUND_LABEL_SE_SELECT,			// セレクト音
		SOUND_LABEL_SE_DECIDE,			// 決定音
		SOUND_LABEL_SE_DIVE00,			// ダイブ音0
		SOUND_LABEL_SE_DIVE01,			// ダイブ音1
		SOUND_LABEL_SE_DIVE02,			// ダイブ音2
		SOUND_LABEL_SE_SAVEPOINT,		// 中間地点着地音
		SOUND_LABEL_SE_CNTDOWN,			// カウントダウン音
		SOUND_LABEL_SE_COUNT,			// 数値カウント音
		SOUND_LABEL_SE_TITLEENTER,		// タイトルエンター
		SOUND_LABEL_SE_SELECTCURSOR,	// ステージセレクトのカーソル音
		SOUND_LABEL_SE_SELECTSTAGE,		// ステージセレクト音
		SOUND_LABEL_MAX
	}SOUND_LABEL;

	// BGMの種類
	typedef enum
	{
		BGMTYPE_TITLE = 0,		// タイトル
		BGMTYPE_STAGESELECT,	// ステージセレクト
		BGMTYPE_GAME,			// ゲーム
		BGMTYPE_RESULT,			// リザルト
		BGMTYPE_RANKING,		// ランキング
		BGMTYPE_MAX
	}BGMTYPE;

	static HRESULT Init(HWND hWnd);
	static void Uninit(void);
	static HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	static void Stop(void);

	// 生成処理
	static CSound *Create(HWND hWnd);

private:
	// パラメータ構造体
	typedef struct
	{
		char *pFilename;
		int nCntLoop;
	}PARAM;

	static HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	static HRESULT ReadChunk(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	static IXAudio2 *m_pXAudio2;

	static PARAM m_aParam[SOUND_LABEL_MAX];

	static IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];						// オーディオデータサイズ
};
#endif
