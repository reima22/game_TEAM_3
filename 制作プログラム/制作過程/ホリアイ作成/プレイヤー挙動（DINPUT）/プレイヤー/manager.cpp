//==============================================================================
//
// マネージャ〔manager.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "manager.h"
#include "scene2D.h"
#include "renderer.h"
#include "texture.h"
#include "title.h"
#include "result.h"
#include "ranking.h"
#include "game.h"
#include "tutorial.h"
#include "fade.h"
#include "input.h"
#include "gamepad.h"
#include "sound.h"
#include "pause.h"
#include "textdata_player.h"
#include "camera.h"
#include "light.h"
#include "debugproc.h"
#include "collision.h"

//==============================================================================
// 静的メンバ変数
//==============================================================================
CRenderer *CManager::m_pRenderer = NULL;			// レンダリング
CInputKeyboard *CManager::m_pInputKeyboard = NULL;	// キーボード
CGamepad *CManager::m_pGamepad = NULL;				// ゲームパッド
CTitle *CManager::m_pTitle = NULL;					// タイトルモード
CTutorial *CManager::m_pTutorial = NULL;			// チュートリアルモード
CGame *CManager::m_pGame = NULL;					// ゲームモード
CResult *CManager::m_pResult = NULL;				// リザルトモード
CRanking *CManager::m_pRanking = NULL;				// ランキングモード
CManager::MODE CManager::m_mode = MODE_GAME;		// 現在のゲームモード
CSound *CManager::m_pSound = NULL;					// サウンドのポインタ
CCamera *CManager::m_pCamera = NULL;				// カメラポインタ
CLight *CManager::m_pLight;							// ライトのポインタ
CTextData *CManager::m_pTextData = NULL;			// テキストデータのポインタ
CTexture *CManager::m_pTexture = NULL;				// テクスチャポインタ
CCollision *CManager::m_pCollision = NULL;			// 当たり判定のポインタ
bool CManager::m_bBGM[CSound::BGMTYPE_MAX] =
{
	true,		// タイトル
	true,		// チュートリアル
	false,		// ゲーム
	true,		// ボス戦
	true,		// リザルト
	true		// ランキング
};		

//==============================================================================
// コンストラクタ
//==============================================================================
CManager::CManager()
{
}

//==============================================================================
// デストラクタ
//==============================================================================
CManager::~CManager()
{
}

//==============================================================================
// 初期化
//==============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// インスタンスと初期化
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
		m_pRenderer->Init(hWnd, bWindow);
	}

	// デバッグ表示の生成
	CDebugProc::Create();

	// カメラの生成
	m_pCamera = new CCamera;
	m_pCamera->Init();

	// ライトの生成
	m_pLight = new CLight;
	m_pLight->Init();

	// フェードの初期化
	CFade::Init();

	// サウンド生成
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	// キーボード生成
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	// ゲームパッド生成
	m_pGamepad = new CGamepad;
	m_pGamepad->Init(hInstance, hWnd);

	// テキストデータの読み込みクラスの生成
	m_pTextData = CTextData::Create();

	// テクスチャの読み込み
	m_pTexture = new CTexture;
	m_pTexture->LoadAll();

	// オブジェクト生成
	SetMode(m_mode);

	// 当たり判定の生成
	m_pCollision = CCollision::Create();
	
	return S_OK;
}

//==============================================================================
// 終了処理
//==============================================================================
void CManager::Uninit(void)
{
	// キーボードの破棄
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	// ゲームパッドの破棄
	if (m_pGamepad != NULL)
	{
		m_pGamepad->Uninit();
		delete m_pGamepad;
		m_pGamepad = NULL;
	}

	// サウンド終了
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		m_pSound = NULL;
	}
	
	// テキストデータの破棄
	if (m_pTextData != NULL)
	{
		m_pTextData->UninitAll();
		m_pTextData = NULL;
	}
	
	// テクスチャの開放
	m_pTexture->UnloadAll();
	m_pTexture = NULL;

	// 当たり判定の破棄
	if(m_pCollision != NULL)
	{
		m_pCollision = NULL;
	}

	// 全破棄
	CScene::ReleaseAll();

	// フェードの終了
	CFade::Uninit();

	// ポインタの開放
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//==============================================================================
// 更新処理
//==============================================================================
void CManager::Update(void)
{
	// キーボードの更新
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	// ゲームパッドの更新
	if (m_pGamepad != NULL)
	{
		m_pGamepad->Update();
	}

	// レンダラーの更新
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	// カメラの更新
	m_pCamera->Update();

	// フェードの更新
	CFade::Update();

	// ゲームモードの取得
	CManager::MODE mode = CManager::GetMode();
}

//==============================================================================
// 描画処理
//==============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//==============================================================================
// キーボードの取得
//==============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//==============================================================================
// ゲームパッドの取得
//==============================================================================
CGamepad *CManager::GetInputGamepad(void)
{
	return m_pGamepad;
}

//==============================================================================
// 現在のシーンモードの設定
//==============================================================================
void CManager::SetMode(MODE mode)
{
	// モードの破棄
	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;

	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			m_pTutorial = NULL;
		}
		break;

	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;

	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;

	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pRanking->Uninit();
			m_pRanking = NULL;
		}
		break;

	default:
		break;
	}

	// オブジェクト破棄
	CScene::ReleaseAll();

	CScene::UpdateAll();

	// モードの設定
	m_mode = mode;

	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{
			m_pTitle = CTitle::Create();
		}
		break;

	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			m_pTutorial = CTutorial::Create();
		}
		break;

	case MODE_GAME:
		if (m_pGame == NULL)
		{
			m_pGame = CGame::Create();
		}
		break;

	case MODE_RESULT:
		if (m_pResult == NULL)
		{
			m_pResult = CResult::Create();
		}
		break;

	case MODE_RANKING:
		if (m_pRanking == NULL)
		{
			m_pRanking = CRanking::Create();
		}
		break;

	default:
		break;
	}
}