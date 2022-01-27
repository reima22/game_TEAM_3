//==============================================================================
//
// ボーナスUI処理〔bonus.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "bonus.h"
#include "bonus_count.h"
#include "bonus_logo.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "ui_base.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CBonus::CBonus(int nPriority) : CScene(nPriority)
{
}

//==============================================================================
// デストラクタ
//==============================================================================
CBonus::~CBonus()
{
}

//==============================================================================
// ボーナスの初期化処理
//==============================================================================
HRESULT CBonus::Init(void)
{
	// UIベースの生成
	CUiBase::Create(BONUS_UIBASE_POS, BONUS_UIBASE_SIZE, "BLOCK_TEX");

	// ボーナスカウント生成
	m_pBonusCount = CBonusCount::Create(BONUS_COUNT_POS, BONUS_COUNT_SIZE);

	// ボーナスロゴ生成
	m_pBonusLogo = CBonusLogo::Create(BONUS_LOGO_POS, BONUS_LOGO_SIZE);

	return S_OK;
}

//==============================================================================
// ボーナスの終了処理
//==============================================================================
void CBonus::Uninit(void)
{
	// カウントの破棄
	if (m_pBonusCount != NULL)
	{
		m_pBonusCount->Uninit();
		m_pBonusCount = NULL;
	}

	// ロゴの破棄
	if (m_pBonusLogo != NULL)
	{
		m_pBonusLogo->Uninit();
		m_pBonusLogo = NULL;
	}
}

//==============================================================================
// ボーナスの更新処理
//==============================================================================
void CBonus::Update(void)
{

}

//==============================================================================
// ボーナスの描画処理
//==============================================================================
void CBonus::Draw(void)
{

}

//==============================================================================
// ボーナスの生成処理
//==============================================================================
CBonus *CBonus::Create(void)
{
	// インスタンス生成
	CBonus *pBonus;
	pBonus = new CBonus;

	// 初期化
	if (pBonus != NULL)
	{
		pBonus->Init();
	}

	return pBonus;
}