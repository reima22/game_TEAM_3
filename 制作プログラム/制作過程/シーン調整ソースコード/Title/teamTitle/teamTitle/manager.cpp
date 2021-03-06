//=============================================================================
//
// メイン処理 [manager.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include <windows.h>
#include <time.h>
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "fade.h"
#include "tutorial.h"
#include "title.h"
#include "input.h"
#include "dinput_keyboard.h"
#include "sound.h"
#include "light.h"
#include "camera.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CManager::Mode CManager::m_Mode= CManager::MODE_TITLE;	// モード変数
CTitle*CManager::m_pTitle= NULL;						// タイトルモード変数
CTutorial*CManager::m_pTutorial = NULL;					// チュートリアルモード変数
CRenderer*CManager::m_pRenderer = NULL;					// レンダラー変数
CInputKeyBoard*CManager::m_pInputKeyBoard = NULL;		// 入力変数
CFade*CManager::m_pFade = NULL;							// フェード変数
CSound*CManager::m_pSound = NULL;						// BGM
CCamera*CManager::m_pCamera = NULL;						// カメラ変数
CLight*CManager::m_pLight = NULL;						// ライト変数

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CManager::CManager()
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CManager::~CManager()
{

}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//レンダリングクラスの生成
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	//キーボードクラスの生成
	m_pInputKeyBoard = new CInputKeyBoard;
	m_pInputKeyBoard->Init(hInstance, hWnd);

	// 乱数系列の変更
	srand((unsigned)time(NULL));
	
	SetMode(m_Mode);

	CFade::Init();

	//音楽クラスの生成
	m_pSound = new CSound;
	m_pSound->InitSound(hWnd);

	//カメラの生成
	m_pCamera = new CCamera;
	m_pCamera->InitCamera();

	//ライトの生成
	m_pLight = new CLight;
	m_pLight->InitLight();

	return S_OK;

}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CManager::Uninit()
{
	//全てのオブジェクトの破棄
	CScene::ReleaseAll();

	//キーボードの破棄
	if (m_pInputKeyBoard != NULL)
	{
		m_pInputKeyBoard->Uninit();
		delete m_pInputKeyBoard;
		m_pInputKeyBoard = NULL;
	}

	//レンダリングの破棄
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	if (m_pSound != NULL)
	{
		m_pSound->UninitSound();
		delete m_pSound;
		m_pSound = NULL;
	}

	//フェードの破棄
	CFade::Uninit();

}


//*****************************************************************************
// 更新処理
//*****************************************************************************
void CManager::Update()
{
	//キーボードの更新
	if (m_pInputKeyBoard != NULL)
	{
		m_pInputKeyBoard->Update();
	}

	//rendererの更新
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	CScene::UpdateAll();

	CFade::Update();
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CManager::Draw()
{
	//rendererの描画チェック
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
// Rendererクラスの値
//=============================================================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// キーボードクラスの値
//=============================================================================
CInputKeyBoard * CManager::GetInputKeyBoard(void)
{
	return m_pInputKeyBoard;
}

//-------------------------------------------------------------------------------
//モードの設定
//-------------------------------------------------------------------------------
void CManager::SetMode(Mode mode)
{

	switch (m_Mode)
	{

	case MODE_TITLE:
		//タイトルの終了処理
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;

	case MODE_TUTORIAL:
		//タイトルの終了処理
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			m_pTutorial = NULL;
		}
		break;

	}

	CScene::ReleaseAll();

	m_Mode = mode;

	switch (m_Mode)
	{

	case MODE_TITLE:

		//タイトルの初期化処理
		m_pTitle = new CTitle;
		m_pTitle->Init(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
		break;

	case MODE_TUTORIAL:

		//タイトルの初期化処理
		m_pTutorial = new CTutorial;
		m_pTutorial->Init(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
		break;

	}
}