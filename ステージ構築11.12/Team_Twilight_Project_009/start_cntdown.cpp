//==============================================================================
//
// 開始時カウントダウン描画処理〔start_cntdown.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "start_cntdown.h"
#include "game.h"
#include "timer.h"
#include "timer_count.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CStartCntdown::CStartCntdown(int nPriority) : CScene2D(nPriority)
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CStartCntdown::~CStartCntdown()
{

}

//==============================================================================
// 開始時カウントダウンの初期化処理
//==============================================================================
HRESULT CStartCntdown::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// タイマー設定
	m_nCntDown = 44;

	// フラグ初期化
	m_bStartCntdown = false;
	m_nDecereaseCnt = 0;

	//// テクスチャ設定
	//CTexture *pTexture;
	//pTexture = CManager::GetTexture();

	//// テクスチャ設定
	//for (int nCntTex = 0; nCntTex < CNTDOWM_MAX; nCntTex++)
	//{
	//	m_pTexture[nCntTex] = pTexture->GetAddress( + nCntTex);
	//}

	// ポリゴンの設定
	if (m_pScene2D == NULL)
	{
		m_pScene2D = CScene2D::Create();						// 生成
		m_pScene2D->SetPosition(pos);							// 位置
		m_pScene2D->SetSize(size);								// サイズ
		m_pScene2D->SetTex(1, 1, 0, 0, 0, 0);					// テクスチャ座標
		m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// 色の設定
		m_pScene2D->BindTexture(m_nCntDown);					// テクスチャ設定
	}

	return S_OK;
}

//==============================================================================
// 開始時カウントダウンの終了処理
//==============================================================================
void CStartCntdown::Uninit(void)
{
	// 2Dポリゴンの破棄
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}
}

//==============================================================================
// 開始時カウントダウンの更新処理
//==============================================================================
void CStartCntdown::Update(void)
{
	// タイマーカウント
	CTimer *pTimer;
	pTimer = CGame::GetTimer();

	// サウンド
	m_pSound = CManager::GetSound();

	if (m_bStartCntdown == true)
	{
		if (m_nDecereaseCnt == 0)
		{
			m_pSound->Play(CSound::SOUND_LABEL_SE_CNTDOWN);
			m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		m_nDecereaseCnt++;

		if (m_nDecereaseCnt % 60 == 0 && m_nDecereaseCnt != 0)
		{
			m_nCntDown--;
			m_pScene2D->BindTexture(m_nCntDown);	// テクスチャ設定
		}

		if (m_nDecereaseCnt >= 240)
		{
			// カウントダウンの開始
			pTimer->GetTimerCnt()->SetStartCnt(true);
			m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}
}

//==============================================================================
// 開始時カウントダウンの描画処理
//==============================================================================
void CStartCntdown::Draw(void)
{

}

//==============================================================================
// 開始時カウントダウンの生成処理
//==============================================================================
CStartCntdown *CStartCntdown::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// インスタンス生成
	CStartCntdown *pStartCntdown;
	pStartCntdown = new CStartCntdown;

	// 初期化
	pStartCntdown->Init(pos, size);

	return pStartCntdown;
}

//==============================================================================
// タイマーの減少
//==============================================================================
//void CTimerCount::TimerDecrease(void)
//{
//	// 減少カウント
//	m_nDecereaseCnt++;
//
//	if (m_nDecereaseCnt % 60 == 0 && m_nTimer > 0)
//	{
//		m_nTimer--;
//	}
//}