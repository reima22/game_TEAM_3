//=============================================================================
//
// マネージャ [manager.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "sound.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CRenderer;		// レンダラークラス
class CInputKeyboard;	// キーボードクラス
class CGamepad;			// ゲームパッドクラス
class CFade;			// フェードクラス
class CMode;			// ゲームモードクラス
class CCamera;			// カメラクラス
class CLight;			// ライトクラス
class CTextData;		// テキストデータクラス
class CTexture;			// テクスチャクラス
class CCollision;		// 当たり判定クラス

//=============================================================================
// マネージャクラス
//=============================================================================
class CManager
{
public:
	CManager();
	 ~CManager();
	HRESULT Init(HINSTANCE hInstance,HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// クラスの取得
	static CRenderer *GetRenderer(void) { return m_pRenderer; };
	static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }
	static CGamepad *GetInputGamepad(void) { return m_pGamepad; }

	// フェードポインタの取得
	static CFade *GetFade(void) { return m_pFade; }

	// モードクラスポインタの取得
	static CMode *GetModePoint(void) { return m_pMode; }

	// 音ポインタの取得
	static CSound *GetSound(void) { return m_pSound; }

	// BGMの再生設定
	static bool GetBGMPlay(CSound::BGMTYPE type) { return m_bBGM[type]; }

	// カメラポインタの取得
	static CCamera *GetCamera(void) { return m_pCamera; }
	
	// テクスチャポインタの取得
	static CTexture *GetTexture(void) { return m_pTexture; }

	// 当たり判定の取得
	static CCollision *GetCollision(void) { return m_pCollision; }

private:
	static CRenderer* m_pRenderer;				// レンダリングクラス
	static CInputKeyboard *m_pInputKeyboard;	// キーボードクラス
	static CGamepad *m_pGamepad;				// ゲームパッドクラス

	//static CTitle *m_pTitle;					// タイトルポインタ
	//static CTutorial *m_pTutorial;				// チュートリアルポインタ
	//static CGame *m_pGame;						// ゲームポインタ
	//static CResult *m_pResult;					// リザルトポインタ
	//static CRanking *m_pRanking;				// ランキングポインタ
	//static MODE m_mode;							// シーンモード

	static CFade *m_pFade;						// フェードクラスポインタ
	static CMode *m_pMode;						// ゲームモード管理ポインタ

	static CSound *m_pSound;					// サウンドのポインタ

	static CCamera *m_pCamera;					// カメラのポインタ
	static CLight *m_pLight;					// ライトのポインタ

	static CTextData *m_pTextData;				// テキストデータクラスのポインタ
	static CTexture *m_pTexture;				// テクスチャクラスのポインタ
	static CCollision *m_pCollision;			// 当たり判定クラスのポインタ

	static bool m_bBGM[CSound::BGMTYPE_MAX];	// BGMのオンオフ
};

#endif