//=============================================================================
//
// マネージャ [manager.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "Manager.h"
#include "Camera.h"
#include "Light.h"
#include "Renderer.h"
#include "Resource.h"
#include "GameScene.h"
#include "select.h"
#include "Input.h"
#include "fade.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CManager::MODE CManager::m_mode;
CRenderer *CManager::m_pRenderer = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputMouse *CManager::m_pInputMouse = NULL;
CResourceManager *CManager::m_pResourceManager = NULL;
CGameScene *CManager::m_pGameScene = NULL;
CStageSelect *CManager::m_pStage = NULL;
CFade *CManager::m_pFade = NULL;

//*****************************************************************************
// マネージャクラス
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// レンダラの生成、初期化
	m_pRenderer = new CRenderer;
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return E_FAIL;
	}

	// カメラの生成、初期化
	m_pCamera = new CCamera;
	if (m_pCamera != NULL)
	{
		m_pCamera->Init();
	}

	// ライトの生成、初期化
	m_pLight = new CLight;
	if (m_pLight != NULL)
	{
		m_pLight->Init();
	}

	// キーボードクラスの生成、初期化
	m_pInputKeyboard = new CInputKeyboard;
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// マウスクラスの生成、初期化
	m_pInputMouse = new CInputMouse;
	if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// リソースマネージャの生成、初期化
	m_pResourceManager = new CResourceManager;
	if (FAILED(m_pResourceManager->Init()))
	{
		return E_FAIL;
	}

	// フェードクラス生成
	m_pFade = new CFade;
	if (FAILED(m_pFade->Init())) {
		return E_FAIL;
	}

	m_pFade->FadeIN();
	SetMode(MODE_SELECT);


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	// オブジェクトをすべて破棄
	CScene::ReleaseAll();

	// フェード破棄
	if (m_pFade != NULL) {
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}

	// リソースマネージャ破棄
	if (m_pResourceManager != NULL)
	{
		m_pResourceManager->Uninit();
		delete m_pResourceManager;
		m_pResourceManager = NULL;
	}

	// マウスの破棄
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	// キーボードの破棄
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	// ライトの破棄
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	// カメラの破棄
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	// レンダラの破棄
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	// カメラの更新呼び出し
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}

	// キーボードの更新呼び出し
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	// マウスの更新呼び出し
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Update();
	}

	// ライトの更新呼び出し
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}

	// レンダラの更新呼び出し
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	// フェードの更新
	if (m_pFade != NULL) {
		m_pFade->Update();
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	// レンダラの描画呼び出し
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
// モードの設定
//=============================================================================
void CManager::SetMode(MODE mode)
{
	// 現在モードの破棄
	switch (m_mode)
	{
	case MODE_SELECT:
		if (m_pStage != NULL)
		{
			m_pStage->Uninit();
			m_pStage = NULL;
		}
		break;

	case MODE_GAME:
		if (m_pGameScene != NULL)
		{
			m_pGameScene->Uninit();
			m_pGameScene = NULL;
		}
		break;

	default:
		break;
	}

	// 全オブジェクトの開放
	CScene::ReleaseAll();

	// 指定モードの生成
	m_mode = mode;
	switch (mode)
	{
	case MODE_SELECT:
		m_pStage = new CStageSelect;
		if (m_pStage != NULL)
		{
			m_pStage->Init(VECTOR3_ZERO, VECTOR3_ZERO, VECTOR3_ZERO);
		}
		break;

	case MODE_GAME:
		m_pGameScene = new CGameScene;
		if (m_pGameScene != NULL)
		{
			m_pGameScene->Init(VECTOR3_ZERO, VECTOR3_ZERO, VECTOR3_ZERO);
		}
		break;
	default:
		break;
	}
}