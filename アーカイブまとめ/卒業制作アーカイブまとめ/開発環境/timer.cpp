//==============================================================================
//
// タイマー処理〔timer.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "timer.h"
#include "timer_count.h"
#include "timer_logo.h"
#include "ui_base.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CTimer::CTimer(int nPriority) : CScene(nPriority)
{
}

//==============================================================================
// デストラクタ
//==============================================================================
CTimer::~CTimer()
{
}

//==============================================================================
// タイマーの初期化処理
//==============================================================================
HRESULT CTimer::Init(void)
{
	// タイマー関連の生成
	m_pUiBase = CUiBase::Create(TIMER_UIBASE_POS, TIMER_UIBASE_SIZE, "BLOCK_TEX");

	m_pTimerCount = CTimerCount::Create(TIMER_COUNT_POS, TIMER_COUNT_SIZE);

	m_pTimerLogo = CTimerLogo::Create(TIMER_LOGO_POS, TIMER_LOGO_SIZE);

	return S_OK;
}

//==============================================================================
//タイマーの終了処理
//==============================================================================
void CTimer::Uninit(void)
{
	// UIベースの破棄
	if (m_pUiBase != NULL)
	{
		m_pUiBase->Uninit();
		m_pUiBase = NULL;
	}

	// カウントの破棄
	if (m_pTimerCount != NULL)
	{
		m_pTimerCount->Uninit();
		m_pTimerCount = NULL;
	}

	// ロゴの破棄
	if (m_pTimerLogo != NULL)
	{
		m_pTimerLogo->Uninit();
		m_pTimerLogo = NULL;
	}
}

//==============================================================================
// タイマーの更新処理
//==============================================================================
void CTimer::Update(void)
{

}

//==============================================================================
// タイマーの描画処理
//==============================================================================
void CTimer::Draw(void)
{

}

//==============================================================================
// タイマーの生成処理
//==============================================================================
CTimer *CTimer::Create(void)
{
	// CNumberのインスタンス生成
	CTimer *pTimer;
	pTimer = new CTimer;

	// CNumberの初期化
	if (pTimer != NULL)
	{
		pTimer->Init();
	}

	return pTimer;
}