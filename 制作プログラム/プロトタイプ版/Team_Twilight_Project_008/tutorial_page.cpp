//==============================================================================
//
// チュートリアルページ描画処理〔tutorial_page.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "sound.h"
#include "tutorial_page.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"

// 静的メンバ変数
D3DXCOLOR CTutorialPage::m_col[TUTORIAL_PAGE_MAX];

//==============================================================================
// コンストラクタ
//==============================================================================
CTutorialPage::CTutorialPage(int nPriority) : CScene2D(nPriority)
{
	// ポリゴンの初期化
	for (int nCnt = 0; nCnt < TUTORIAL_PAGE_MAX; nCnt++)
	{
		m_pScene2D[nCnt] = NULL;
		m_col[nCnt] = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	}

	m_nPageCnt = TUTORIAL_PAGE_MAX;
}

//==============================================================================
// デストラクタ
//==============================================================================
CTutorialPage::~CTutorialPage()
{
}

//==============================================================================
// チュートリアルページの初期化処理
//==============================================================================
HRESULT CTutorialPage::Init(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < TUTORIAL_PAGE_MAX; nCnt++)
	{
		if (m_pScene2D[nCnt] == NULL)
		{
			m_pScene2D[nCnt] = CScene2D::Create();

			m_pScene2D[nCnt]->SetPosition(pos);
			m_pScene2D[nCnt]->SetSize(SCREEN_SIZE);
			m_pScene2D[nCnt]->BindTexture(21 - nCnt);
			m_pScene2D[nCnt]->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
		}
	}

	return S_OK;
}

//==============================================================================
// チュートリアルページの終了処理
//==============================================================================
void CTutorialPage::Uninit(void)
{
	// ページの破棄
	for (int nCnt = 0; nCnt < TUTORIAL_PAGE_MAX; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{// NULLチェック後に破棄
			m_pScene2D[nCnt]->Uninit();
			m_pScene2D[nCnt] = NULL;
		}
	}

	Release();	// インスタンスのデリート
}

//==============================================================================
// チュートリアルページの更新処理
//==============================================================================
void CTutorialPage::Update(void)
{
	// キーボードの取得
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// ゲームパッドの取得
	CGamepad *gamepad = CManager::GetInputGamepad();

	// フェードの取得
	CFade::FADE fade = CManager::GetFade()->GetFade();

	// ローカル変数宣言
	D3DXCOLOR col[TUTORIAL_PAGE_MAX];

	 // フェードの状態
	if (fade != CFade::FADE_IN)
	{
		if (keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
		{
			m_nPageCnt--;
			if (m_nPageCnt > 0)
			{
				m_col[m_nPageCnt].a = 0.0f;
			}			
		}
		if (m_nPageCnt < TUTORIAL_PAGE_MAX)
		{
			if (keyboard->GetTrigger(CInput::KEYINFO_TUTO_BACK) == true || gamepad->GetTrigger(CInput::KEYINFO_TUTO_BACK) == true)
			{
				m_col[m_nPageCnt].a = 1.0f;
				m_nPageCnt++;
			}
		}		
	}


	// 色の設定
	for (int nCnt = 0; nCnt < TUTORIAL_PAGE_MAX; nCnt++)
	{
		m_pScene2D[nCnt]->SetCol(m_col[nCnt]);
	}
}

//==============================================================================
// チュートリアルページの描画処理
//==============================================================================
void CTutorialPage::Draw(void)
{
	for (int nCnt = 0; nCnt < TUTORIAL_PAGE_MAX; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt]->Draw();
		}
	}
}

//==============================================================================
// チュートリアルページの生成処理
//==============================================================================
CTutorialPage *CTutorialPage::Create(D3DXVECTOR3 pos)
{
	// インスタンス生成
	CTutorialPage *pTutorialPage;
	pTutorialPage = new CTutorialPage;

	// 初期化
	if (pTutorialPage != NULL)
	{
		pTutorialPage->Init(pos);
	}

	return pTutorialPage;
}