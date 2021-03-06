//==============================================================================
//
// 落下数カウント描画処理〔fall_count.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "number.h"
#include "texture.h"
#include "fall_count.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CFallCount::CFallCount()
{
	for (int nCnt = 0; nCnt < FALL_DIGIT_NUM; nCnt++)
	{
		// 各ナンバーの初期化
		m_apNumber[nCnt] = NULL;
	}
}

//==============================================================================
// デストラクタ
//==============================================================================
CFallCount::~CFallCount()
{

}

//==============================================================================
// 落下数カウントの初期化処理
//==============================================================================
HRESULT CFallCount::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// 落下数設定
	m_nFall = 0;

	for (int nCntDigit = 0; nCntDigit < FALL_DIGIT_NUM; nCntDigit++)
	{
		m_apNumber[nCntDigit] = CNumber::Create(
			D3DXVECTOR3(pos.x + (nCntDigit * (size.x * 2)), pos.y, 0.0f), size);
	}

	return S_OK;
}

//==============================================================================
// 落下数カウントの終了処理
//==============================================================================
void CFallCount::Uninit(void)
{
	for (int nCntDigit = 0; nCntDigit < FALL_DIGIT_NUM; nCntDigit++)
	{
		if (m_apNumber[nCntDigit] != NULL)
		{// NULLチェック後に破棄
			m_apNumber[nCntDigit]->Uninit();
			m_apNumber[nCntDigit] = NULL;
		}
	}
}

//==============================================================================
// 落下数カウントの更新処理
//==============================================================================
void CFallCount::Update(void)
{
	SetNumber(m_nFall);
}

//==============================================================================
// 落下数カウントの描画処理
//==============================================================================
void CFallCount::Draw(void)
{

}

//==============================================================================
// 落下数カウントの生成処理
//==============================================================================
CFallCount *CFallCount::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// ローカル変数宣言
	CFallCount *pFallCount;
	pFallCount = new CFallCount;

	// 初期化
	if (pFallCount != NULL)
	{
		pFallCount->Init(pos, size);
	}

	return pFallCount;
}

//==============================================================================
// 数値設定
//==============================================================================
void CFallCount::SetNumber(int nFall)
{
	// 数値設定
	m_nFall = nFall;

	int nData = (int)pow(10, (FALL_DIGIT_NUM - 1));

	for (int nCnt = 0; nCnt < FALL_DIGIT_NUM; nCnt++)
	{
		// 各桁の算出
		int nNumber;
		nNumber = (m_nFall / nData) % 10;
		nData /= 10;

		// 桁の設定
		m_apNumber[nCnt]->SetNumber(nNumber);
	}
}