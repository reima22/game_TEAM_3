//==============================================================================
//
// 落下数UI処理〔fall.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "fall.h"
#include "fall_count.h"
#include "fall_logo.h"
#include "ui_base.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CFall::CFall(int nPriority) : CScene(nPriority)
{
}

//==============================================================================
// デストラクタ
//==============================================================================
CFall::~CFall()
{
}

//==============================================================================
// 落下数の初期化処理
//==============================================================================
HRESULT CFall::Init(void)
{
	// UIベースの生成
	CUiBase::Create(FALL_UIBASE_POS, FALL_UIBASE_SIZE, "BLOCK_TEX");

	// 落下数カウント生成
	m_pFallCount = CFallCount::Create(FALL_COUNT_POS, FALL_COUNT_SIZE);

	// 落下数ロゴ生成
	m_pFallLogo = CFallLogo::Create(FALL_LOGO_POS, FALL_LOGO_SIZE);

	return S_OK;
}

//==============================================================================
// 落下数の終了処理
//==============================================================================
void CFall::Uninit(void)
{
	// カウントの破棄
	if (m_pFallCount != NULL)
	{
		m_pFallCount->Uninit();
		m_pFallCount = NULL;
	}

	// ロゴの破棄
	if (m_pFallLogo != NULL)
	{
		m_pFallLogo->Uninit();
		m_pFallLogo = NULL;
	}
}

//==============================================================================
// 落下数の更新処理
//==============================================================================
void CFall::Update(void)
{

}

//==============================================================================
// 落下数の描画処理
//==============================================================================
void CFall::Draw(void)
{

}

//==============================================================================
// 落下数の生成処理
//==============================================================================
CFall *CFall::Create(void)
{
	// インスタンス生成
	CFall *pFall;
	pFall = new CFall;

	// 初期化
	if (pFall != NULL)
	{
		pFall->Init();
	}

	return pFall;
}