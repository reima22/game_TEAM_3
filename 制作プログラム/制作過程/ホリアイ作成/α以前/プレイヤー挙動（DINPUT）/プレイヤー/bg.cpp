//==============================================================================
//
// 背景描画処理〔bg.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "gamepad.h"
#include "game.h"
#include "bg.h"
#include "texture.h"
#include "result.h"

// 静的メンバ変数宣言
D3DXVECTOR3 CBg::m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

//==============================================================================
// コンストラクタ
//==============================================================================
CBg::CBg(int nPriority) : CScene(nPriority)
{
	// CScene2Dの初期化
	for (int nCnt = 0; nCnt < BG_MAX; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
		m_fTexX[nCnt] = 0.0f;
		m_fTexY[nCnt] = 0.0f;
	}
}

//==============================================================================
// デストラクタ
//==============================================================================
CBg::~CBg()
{
}

//==============================================================================
// 背景の初期化処理
//==============================================================================
HRESULT CBg::Init(void)
{



	return S_OK;
}

//==============================================================================
// 背景の終了処理
//==============================================================================
void CBg::Uninit(void)
{
	for (int nCnt = 0; nCnt < BG_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{// NULLチェック後に破棄
			m_apScene2D[nCnt]->Uninit();
			m_apScene2D[nCnt] = NULL;
		}
	}

	Release();	// CBgインスタンスのデリート
}

//==============================================================================
// 背景の更新処理
//==============================================================================
void CBg::Update(void)
{
	// モードの取得
	CManager::MODE mode = CManager::GetMode();

	// ゲームモードのスクロール
	if (mode == CManager::MODE_GAME)
	{
		// 背景テクスチャ座標の更新
		m_fTexY[0] -= 0.001f;
		m_fTexY[1] -= 0.003f;
		m_fTexY[2] -= 0.005f;

		// キーボードの取得
		CInputKeyboard *keyboard = CManager::GetInputKeyboard();

		// ゲームパッドの取得
		CGamepad *gamepad = CManager::GetInputGamepad();

		// 操作にともなう背景テクスチャ移動処理
		if (keyboard->GetPress(CInput::KEYINFO_UP) == true || gamepad->GetPress(CInput::KEYINFO_UP) == true)
		{
			m_fTexY[0] -= 0.0005f;
			m_fTexY[1] -= 0.001f;
			m_fTexY[2] -= 0.003f;
		}
		if (keyboard->GetPress(CInput::KEYINFO_DOWN) == true || gamepad->GetPress(CInput::KEYINFO_DOWN) == true)
		{
			m_fTexY[0] += 0.0005f;
			m_fTexY[1] += 0.001f;
			m_fTexY[2] += 0.003f;
		}
		if (keyboard->GetPress(CInput::KEYINFO_LEFT) == true || gamepad->GetPress(CInput::KEYINFO_LEFT) == true)
		{
			m_fTexX[0] -= 0.0005f;
			m_fTexX[1] -= 0.001f;
			m_fTexX[2] -= 0.003f;
		}
		if (keyboard->GetPress(CInput::KEYINFO_RIGHT) == true || gamepad->GetPress(CInput::KEYINFO_RIGHT) == true)
		{
			m_fTexX[0] += 0.0005f;
			m_fTexX[1] += 0.001f;
			m_fTexX[2] += 0.003f;
		}

		// 背景テクスチャの設定
		for (int nCnt = 0; nCnt < BG_MAX; nCnt++)
		{
			m_apScene2D[nCnt]->SetTex(1,1,0, 0, m_fTexX[nCnt], m_fTexY[nCnt]);

			// テクスチャ座標移動の補正
			if (m_fTexY[nCnt] > 1.0f)
			{
				m_fTexY[nCnt] -= 1.0f;
			}
			if (m_fTexY[nCnt] < 0.0f)
			{
				m_fTexY[nCnt] += 1.0f;
			}

			if (m_fTexX[nCnt] > 1.0f)
			{
				m_fTexX[nCnt] -= 1.0f;
			}
			if (m_fTexX[nCnt] < 0.0f)
			{
				m_fTexX[nCnt] += 1.0f;
			}
		}
	}
}

//==============================================================================
// 背景の描画処理
//==============================================================================
void CBg::Draw(void)
{
	/*CSceneにて実行*/
}

//==============================================================================
// 背景の生成処理
//==============================================================================
CBg *CBg::Create(void)
{
	// CBgのインスタンス生成
	CBg *pBg;
	pBg = new CBg;

	// CBgの初期化
	pBg->Init();

	return pBg;
}

//==============================================================================
// 位置の取得
//==============================================================================
D3DXVECTOR3 CBg::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// サイズの取得
//==============================================================================
D3DXVECTOR3 CBg::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}