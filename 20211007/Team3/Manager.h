//=============================================================================
//
// マネージャ [manager.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// ヘッダのインクルード
//*****************************************************************************
#include "main.h"
#include "renderer.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CInputKeyboard;
class CInputMouse;
class CCamera;
class CLight;
class CGameScene;
class CResourceManager;
class CStageSelect;
class CFade;

//*****************************************************************************
// マネージャクラス
//*****************************************************************************
class CManager
{
public:
	typedef enum {	// MODE
		MODE_SELECT = 0,
		MODE_GAME,

		MODE_MAX,
	} MODE;

	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static MODE GetMode(void) { return m_mode; }
	static void SetMode(MODE mode);

	// GETTER,SETTER
	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CLight *GetLight(void) { return m_pLight; }
	static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }
	static CInputMouse *GetInputMouse(void) { return m_pInputMouse; }
	static CResourceManager *GetResourceManager(void) { return m_pResourceManager; }
	static CGameScene *GetGame(void) { return m_pGameScene; }
	static CStageSelect *GetStageSelect(void) { return m_pStage; }
	static CFade *GetFade(void) { return m_pFade; }

private:
	static MODE m_mode;

	static CRenderer *m_pRenderer;
	static CCamera *m_pCamera;
	static CLight *m_pLight;
	static CInputKeyboard *m_pInputKeyboard;
	static CInputMouse *m_pInputMouse;
	static CResourceManager *m_pResourceManager;
	static CGameScene *m_pGameScene;
	static CStageSelect *m_pStage;
	static CFade *m_pFade;
};

#endif


