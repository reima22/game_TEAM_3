//==============================================================================
//
// タイマーカウント描画処理〔timer_count.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "number.h"
#include "texture.h"
#include "timer_count.h"

// 静的メンバ変数宣言
int CTimerCount::m_nTimerResult = 0;	// リザルトへ引き継ぐ値

//==============================================================================
// コンストラクタ
//==============================================================================
CTimerCount::CTimerCount()
{
	for (int nCnt = 0; nCnt < TIMER_DIGIT_NUM; nCnt++)
	{
		// 各ナンバーNULL化
		m_apNumber[nCnt] = NULL;
	}
}

//==============================================================================
// デストラクタ
//==============================================================================
CTimerCount::~CTimerCount()
{

}

//==============================================================================
// タイマーカウントの初期化処理
//==============================================================================
HRESULT CTimerCount::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// タイマー設定
	m_nTimer = 60;

	// 数字の表示処理初期化
	for (int nCntDigit = 0; nCntDigit < TIMER_DIGIT_NUM; nCntDigit++)
	{
		m_apNumber[nCntDigit] = CNumber::Create(
			D3DXVECTOR3(pos.x + (nCntDigit * (size.x * 2)), pos.y, 0.0f), size);
	}

	return S_OK;
}

//==============================================================================
// タイマーカウントの終了処理
//==============================================================================
void CTimerCount::Uninit(void)
{
	for (int nCntDigit = 0; nCntDigit < TIMER_DIGIT_NUM; nCntDigit++)
	{
		if (m_apNumber[nCntDigit] != NULL)
		{// NULLチェック後に破棄
			m_apNumber[nCntDigit]->Uninit();
			m_apNumber[nCntDigit] = NULL;
		}
	}

	m_nTimerResult = m_nTimer;
}

//==============================================================================
// タイマーカウントの更新処理
//==============================================================================
void CTimerCount::Update(void)
{
	if (m_bStartCnt == true)
	{
		// タイマー減少
		TimerDecrease();
	}

	// タイマーの設定
	SetNumber(m_nTimer);
}

//==============================================================================
// タイマーカウントの描画処理
//==============================================================================
void CTimerCount::Draw(void)
{

}

//==============================================================================
// タイマーカウントの生成処理
//==============================================================================
CTimerCount *CTimerCount::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// インスタンス生成
	CTimerCount *pTimerCount;
	pTimerCount = new CTimerCount;

	// 初期化
	pTimerCount->Init(pos, size);

	return pTimerCount;
}

//==============================================================================
// タイマーの減少
//==============================================================================
void CTimerCount::TimerDecrease(void)
{
	// 減少カウント
	m_nDecereaseCnt++;

	if (m_nDecereaseCnt % 60 == 0 && m_nTimer > 0)
	{
		m_nTimer--;
	}
}

//==============================================================================
// タイマー数値設定
//==============================================================================
void CTimerCount::SetNumber(int nTimer)
{
	// スコアの設定
	m_nTimer = nTimer;

	int nData = (int)pow(10, (TIMER_DIGIT_NUM - 1));

	for (int nCnt = 0; nCnt < TIMER_DIGIT_NUM; nCnt++)
	{
		// 各桁の算出
		int nNumber;
		nNumber = (m_nTimer / nData) % 10;
		nData /= 10;

		// 桁の設定
		m_apNumber[nCnt]->SetNumber(nNumber);
	}
}