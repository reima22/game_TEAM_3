//==============================================================================
//
// タイマーロゴ描画処理〔timer_logo.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "number.h"
#include "texture.h"
#include "fall_logo.h"
#include "select.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CFallLogo::CFallLogo()
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CFallLogo::~CFallLogo()
{

}

//==============================================================================
// タイマーロゴの初期化処理
//==============================================================================
HRESULT CFallLogo::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CStageSelect::STAGE_SELECT select = CStageSelect::GetSelectingStage();

	// 2Dポリゴンを生成
	m_pScene2D = CScene2D::Create();

	if (m_pScene2D != NULL)
	{
		// 位置設定
		m_pScene2D->SetPosition(pos);

		// サイズ設定
		m_pScene2D->SetSize(size);

		// テクスチャ設定
		m_pScene2D->BindTexture("FALL_LOGO");

		if (select == CStageSelect::STAGE_SELECT_2)
		{
			m_pScene2D->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		}
		else
		{
			m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		m_pScene2D->SetTex(1, 1, 0, 0, 0, 0);
	}

	return S_OK;
}

//==============================================================================
// タイマーロゴの終了処理
//==============================================================================
void CFallLogo::Uninit(void)
{
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}
}

//==============================================================================
// タイマーロゴの更新処理
//==============================================================================
void CFallLogo::Update(void)
{

}

//==============================================================================
// タイマーロゴの描画処理
//==============================================================================
void CFallLogo::Draw(void)
{

}

//==============================================================================
// タイマーロゴの生成処理
//==============================================================================
CFallLogo *CFallLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// ローカル変数宣言
	CFallLogo *pFallLogo;
	pFallLogo = new CFallLogo;

	// 初期化
	if (pFallLogo != NULL)
	{
		pFallLogo->Init(pos, size);
	}

	return pFallLogo;
}