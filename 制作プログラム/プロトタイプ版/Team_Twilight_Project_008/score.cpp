//==============================================================================
//
// スコア描画処理〔score.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "score.h"
#include "number.h"
#include "mode.h"

// 静的メンバ変数宣言
int CScore::m_nScore;
float CScore::m_fSizeX;
float CScore::m_fSizeY;
int CScore::m_nResultScore = 0;

//==============================================================================
// コンストラクタ
//==============================================================================
CScore::CScore(int nPriority) : CScene2D(nPriority)
{
	for (int nCnt = 0; nCnt < NUM_MAX; nCnt++)
	{
		// 各ナンバーの初期化
		m_apNumber[nCnt] = NULL;
	}
}

//==============================================================================
// デストラクタ
//==============================================================================
CScore::~CScore()
{
}

//==============================================================================
// スコアの初期化処理
//==============================================================================
HRESULT CScore::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	for (int nCnt = 0; nCnt < NUM_MAX; nCnt++)
	{
		if (m_apNumber[nCnt] == NULL)
		{
			m_apNumber[nCnt] = CNumber::Create(
				D3DXVECTOR3(pos.x + (nCnt * (m_fSizeX * 2)), pos.y, 0.0f), size);
		}
	}

	m_nScore = 0;

	return S_OK;
}

//==============================================================================
// スコアの終了処理
//==============================================================================
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_MAX; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{// NULLチェック後に破棄
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = NULL;
		}
	}

	Release();	// CScoreインスタンスのデリート
}

//==============================================================================
// スコアの更新処理
//==============================================================================
void CScore::Update(void)
{
	CMode::MODE mode = CManager::GetModePoint()->GetMode();

	if (mode == CMode::MODE_GAME)
	{
		// スコアの設定
		SetScore(m_nScore);
	}	
}

//==============================================================================
// スコアの描画処理
//==============================================================================
void CScore::Draw(void)
{
	// ナンバーの描画
	for (int nCnt = 0; nCnt < NUM_MAX; nCnt++)
	{
		if (m_apNumber != NULL)
		{
			m_apNumber[nCnt]->Draw();
		}
	}
}

//==============================================================================
// スコアの生成処理
//==============================================================================
CScore *CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// CScoreのインスタンス生成
	CScore *pScore;
	pScore = new CScore;

	// CScoreの初期化
	pScore->Init(pos,size);

	return pScore;
}

//==============================================================================
// スコア設定
//==============================================================================
void CScore::SetScore(int nScore)
{
	// スコアの設定
	m_nScore = nScore;

	int nData = (int)pow(10, (NUM_MAX - 1));

	for (int nCnt = 0; nCnt < NUM_MAX; nCnt++)
	{
		// 各桁の算出
		int nNumber;
		nNumber = (m_nScore / nData) % 10;
		nData /= 10;

		// 桁の設定
		m_apNumber[nCnt]->SetNumber(nNumber);
	}
}

//==============================================================================
// スコアの加算
//==============================================================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
}

//==============================================================================
// 位置の取得
//==============================================================================
D3DXVECTOR3 CScore::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// サイズの取得
//==============================================================================
D3DXVECTOR3 CScore::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}