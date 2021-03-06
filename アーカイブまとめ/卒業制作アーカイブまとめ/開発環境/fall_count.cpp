//==============================================================================
//
// 落下数カウント描画処理〔fall_count.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "fall_count.h"
#include "main.h"
#include "manager.h"
#include "mode.h"
#include "number.h"
#include "renderer.h"
#include "texture.h"

// 静的メンバ変数
int CFallCount::m_nFallResult = 0;

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
	//CStageSelect::STAGE_SELECT select = CStageSelect::GetSelectingStage();

	// 落下数設定
	m_nFall = 0;

	for (int nCntDigit = 0; nCntDigit < FALL_DIGIT_NUM; nCntDigit++)
	{
		m_apNumber[nCntDigit] = CNumber::Create(
			D3DXVECTOR3(pos.x + (nCntDigit * (size.x * 2)), pos.y, 0.0f), size);

		m_apNumber[nCntDigit]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
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

	m_nFallResult = m_nFall;
}

//==============================================================================
// 落下数カウントの更新処理
//==============================================================================
void CFallCount::Update(void)
{
	SetNumber(m_nFall);

	// ゲームモードに限定
	if (CManager::GetModePoint()->GetMode() == CMode::MODE_GAME)
	{
		SizeReturn();
	}

	for (int nCntNum = 0; nCntNum < FALL_DIGIT_NUM; nCntNum++)
	{
		m_apNumber[nCntNum]->Update();
	}
}

//==============================================================================
// 落下数カウントの描画処理
//==============================================================================
void CFallCount::Draw(void)
{
	for (int nCntDigit = 0; nCntDigit < FALL_DIGIT_NUM; nCntDigit++)
	{
		if (m_apNumber[nCntDigit] != NULL)
		{// NULLチェック後に描画
			m_apNumber[nCntDigit]->Draw();
		}
	}
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
		pFallCount->Init(pos,size);
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

//==============================================================================
// 落下カウント増加
//==============================================================================
void CFallCount::AddFall(int nAdd)
{
	// 加算
	m_nFall += nAdd;

	// サイズ拡大
	for (int nCnt = 0; nCnt < FALL_DIGIT_NUM; nCnt++)
	{
		D3DXVECTOR2 size = m_apNumber[nCnt]->GetSize();

		size = FALL_COUNT_SIZE + D3DXVECTOR2(20.0f, 20.0f);

		m_apNumber[nCnt]->SetSize(size);
		m_apNumber[nCnt]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
}

//==============================================================================
// 数字サイズを戻す
//==============================================================================
void CFallCount::SizeReturn(void)
{
	for (int nCnt = 0; nCnt < FALL_DIGIT_NUM; nCnt++)
	{
		D3DXVECTOR2 size = m_apNumber[nCnt]->GetSize();

		if (size.x > FALL_COUNT_SIZE.x)
		{
			size -= D3DXVECTOR2(0.5f, 0.5f);

			m_apNumber[nCnt]->SetSize(size);
		}
		else
		{
			m_apNumber[nCnt]->SetSize(FALL_COUNT_SIZE);
			m_apNumber[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0, 1.0f));
		}
	}
}