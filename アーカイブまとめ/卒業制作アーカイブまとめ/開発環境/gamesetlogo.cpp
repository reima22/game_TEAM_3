//==============================================================================
//
// ゲーム結果ロゴ処理〔gamesetlogo.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "game.h"
#include "gamesetlogo.h"
#include "main.h"
#include "manager.h"
#include "player.h"
#include "renderer.h"
#include "scene2D.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CGamesetLogo::CGamesetLogo(int nPriority) : CScene(nPriority)
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CGamesetLogo::~CGamesetLogo()
{

}

//==============================================================================
// ゲーム結果ロゴの初期化処理
//==============================================================================
HRESULT CGamesetLogo::Init(void)
{
	// プレイヤー情報
	CPlayer *pPlayer = CGame::GetPlayer();

	if (m_pScene2D == NULL)
	{		
		m_pScene2D = CScene2D::Create();						// 2Dポリゴンを生成	
		m_pScene2D->SetPosition(LOGO_POS);						// 位置設定
		m_pScene2D->SetSize(LOGO_SIZE);							// サイズ設定
		m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// 色の設定
		m_pScene2D->SetTex(1, 1, 0, 0, 0.0f, 0.0f);				// テクスチャの分割情報

		// テクスチャ設定
		if (pPlayer->GetGameClear() == true)
		{
			m_pScene2D->BindTexture("G_RESULT_CLEAR");
		}
		else
		{
			m_pScene2D->BindTexture("G_RESULT_GAMEOVER");
		}
	}

	return S_OK;
}

//==============================================================================
// ゲーム結果ロゴの終了処理
//==============================================================================
void CGamesetLogo::Uninit(void)
{
	// 2Dポリゴンの破棄
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}
}

//==============================================================================
// ゲーム結果ロゴの更新処理
//==============================================================================
void CGamesetLogo::Update(void)
{

}

//==============================================================================
// ゲーム結果ロゴの描画処理
//==============================================================================
void CGamesetLogo::Draw(void)
{

}

//==============================================================================
// ゲーム結果ロゴの生成処理
//==============================================================================
CGamesetLogo *CGamesetLogo::Create(void)
{
	// インスタンス生成
	CGamesetLogo *pGamesetLogo;
	pGamesetLogo = new CGamesetLogo;

	// ロゴの初期化
	if (pGamesetLogo != NULL)
	{
		pGamesetLogo->Init();
	}

	return pGamesetLogo;
}