
//=============================================================================
//
// ゲームモード処理 [game.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene.h"
#include "mode.h"

// マクロ定義
#define LOGO_POS	(D3DXVECTOR3(640.0f, 360.0f,0.0f))
#define LOGO_SIZE	(D3DXVECTOR2(480.0f,80.0f))

// 前方宣言
class CSceneX;			// シーンXクラス
class CPlayer;			// プレイヤークラス
class CObject;			// オブジェクトクラス
class CPause;			// ポーズクラス
class CTerrain;			// メッシュ
class CTimer;			// タイマークラス
class CFall;			// 落下数クラス
class CSound;			// サウンドクラス
class CMeshfield;		// メッシュフィールドクラス
class CStartCntdown;	// 開始時カウントダウンクラス
class CFog;				// フォグ効果クラス
class CBonus;			// ボーナスクラス
class CCheckpointLogo;	// チェックポイントロゴクラス

//==============================================================================
// ゲームモードクラス
//==============================================================================
class CGame : public CMode
{
public:
	// フェイズ分割
	typedef enum
	{
		CLEARPHASE_NONE = 0,	// クリア判定なし
		CLEARPHASE_WAIT,		// 待機
		CLEARPHASE_PAUSE,		// クリアポーズ演出
		CLEARPHASE_FADE,		// フェードアウト
		CLEARPHASE_MAX
	}CLEARPHASE;

	typedef enum
	{
		GAMEOVERPHASE_NONE = 0,		// 判定無し
		GAMEOVERPHASE_WAIT,			// 待機
		GAMEOVERPHASE_DIRECTION,	// 演出
		GAMEOVERPHASE_FADE,			// フェードアウト
		GAMEOVERPHASE_MAX
	}GAMEOVERPHASE;

	CGame(int nPriority = PRIORITY_DEFAULT);
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGame *Create(void);

	void SetStageObject(void);

	void EndGame(void);
	void GameClear(void);
	void GameOver(void);

	void CreateLogo(void);

	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CTerrain *GetTerrain(void) { return m_pTerrain; }
	static CTimer *GetTimer(void) { return m_pTimer; }
	static CFall *GetFall(void) { return m_pFall; }
	static CObject *GetPointObject(int nCnt) { return m_pObject[nCnt]; }
	static CMeshfield *GetMeshField(int nIdx) { return m_pMeshField[nIdx]; }	// メッシュフィールドポインタ
	static CStartCntdown *GetStartCntdown(void) { return m_pStartCntdown; }		// 開始時カウントダウンクラス
	static CFog *GetFog(void) { return m_pFog; }								// フォグ取得
	static CBonus *GetBonus(void) { return m_pBonus; }
	static CCheckpointLogo *GetCheckPointLogo(void) { return m_pCheckPointLogo; }


	// ゲーム終了フラグの取得・設定
	static bool GetGameEnd(void) { return m_bGameEnd; }
	static void SetGameEnd(bool bGameEnd) { m_bGameEnd = bGameEnd; }

	// ゲームクリアのフェイズの取得・設定
	static CLEARPHASE GetClearPhase(void) { return m_clearPhase; }
	static void SetClearPhase(CLEARPHASE clearPhase) { m_clearPhase = clearPhase; }

	// ゲームオーバーフェイズの取得・設定
	static GAMEOVERPHASE GetOverPhase(void) { return m_gameoverPhase; }
	static void SetOverPhase(GAMEOVERPHASE overPhase) { m_gameoverPhase = overPhase; }
private:
	int m_nNumObject;						// オブジェクト数
	int m_nNumMeshfield;					// メッシュフィールドの数
	static CPause *m_pPause;				// ポーズのポインタ
	static CPlayer *m_pPlayer;				// プレイヤーのポインタ

	static CTimer *m_pTimer;				// タイマーのポインタ
	static CFall *m_pFall;					// 落下数のポインタ
	static CTerrain *m_pTerrain;			// メッシュ	

	static CObject **m_pObject;				// オブジェクトのポインタ
	static CMeshfield **m_pMeshField;		// オリジナルメッシュ
	static CStartCntdown *m_pStartCntdown;	// 開始時カウントダウンクラス
	static CFog *m_pFog;					// フォグ効果クラス

	static bool m_bGameEnd;					// ゲーム終了のフラグ
	static int m_nClearDirectingCnt;		// クリア演出カウント

	static CLEARPHASE m_clearPhase;			// クリア時のフェイズ分割
	static GAMEOVERPHASE m_gameoverPhase;	// ゲームオーバー時のフェーズ分割

	CScene2D *m_pResultLogo;				// 結果ロゴ

	static CBonus *m_pBonus;				// ボーナスクラスポインタ
	static CCheckpointLogo * m_pCheckPointLogo;	// チェックポイントロゴ
};

#endif