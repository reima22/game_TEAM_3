
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

//==============================================================================
// ゲームモードクラス
//==============================================================================
class CGame : public CMode
{
public:
	CGame(int nPriority = PRIORITY_DEFAULT);
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGame *Create(void);

	void SetStageObject(void);

	static CPlayer *GetPlayer(void) { return m_pPlayer; }
	static CTerrain *GetTerrain(void) { return m_pTerrain; }
	static CTimer *GetTimer(void) { return m_pTimer; }
	static CFall *GetFall(void) { return m_pFall; }
	static CObject *GetPointObject(int nCnt) { return m_pObject[nCnt]; }
	static CMeshfield *GetMeshField(int nIdx) { return m_pMeshField[nIdx]; }	// メッシュフィールドポインタ
	static CStartCntdown *GetStartCntdown(void) { return m_pStartCntdown; }		// 開始時カウントダウンクラス
	static CFog *GetFog(void) { return m_pFog; }								// フォグ取得

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
};

#endif