//==============================================================================
//
// UIの下地描画処理〔ui_base.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "ui_base.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CUiBase::CUiBase(int nPriority) : CScene2D(nPriority)
{
}

//==============================================================================
// デストラクタ
//==============================================================================
CUiBase::~CUiBase()
{
}

//==============================================================================
// タイマーの初期化処理
//==============================================================================
HRESULT CUiBase::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size, char *pTypeCheck)
{
	// 初期化
	if (m_pScene2D == NULL)
	{
		m_pScene2D = new CScene2D;
		m_pScene2D->Init();
		m_pScene2D->SetPosition(pos);
		m_pScene2D->SetSize(size);
		m_pScene2D->BindTexture(pTypeCheck);
		m_pScene2D->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	}

	return S_OK;
}

//==============================================================================
//タイマーの終了処理
//==============================================================================
void CUiBase::Uninit(void)
{
	// ポリゴンの破棄
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	Release();
}

//==============================================================================
// タイマーの更新処理
//==============================================================================
void CUiBase::Update(void)
{

}

//==============================================================================
// タイマーの描画処理
//==============================================================================
void CUiBase::Draw(void)
{

}

//==============================================================================
// タイマーの生成処理
//==============================================================================
CUiBase *CUiBase::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, char *pTypeCheck)
{
	// インスタンス生成
	CUiBase *pUiBase;
	pUiBase = new CUiBase;

	// 初期化
	if (pUiBase != NULL)
	{
		pUiBase->Init(pos, size, pTypeCheck);
	}

	return pUiBase;
}