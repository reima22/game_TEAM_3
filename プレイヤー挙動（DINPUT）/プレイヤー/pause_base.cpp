//==============================================================================
//
// ポーズベース処理〔pause_base.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "pause_base.h"
#include "input.h"
#include "textdata.h"
#include "textdata_pause.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CPauseBase::CPauseBase(int nPriority) : CScene2D(nPriority)
{
}

//==============================================================================
// デストラクタ
//==============================================================================
CPauseBase::~CPauseBase()
{
}

//==============================================================================
// ポーズベースの初期化処理
//==============================================================================
HRESULT CPauseBase::Init(void)
{
	// テキストデータの取得
	CTextDataPause *pDataPause;
	pDataPause = CTextData::GetDataPause();

	D3DXVECTOR3 pos = pDataPause->GetPosition(CTextDataPause::PAUSEPOLY_BASE);
	D3DXVECTOR2 size = pDataPause->GetSize(CTextDataPause::PAUSEPOLY_BASE);
	int nTexIdx = pDataPause->GetTexIdx(CTextDataPause::PAUSEPOLY_BASE);

	// 初期化
	CScene2D::Init();
	CScene2D::SetPosition(pos);
	CScene2D::SetSize(size.x, size.y);
	CScene2D::SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	CScene2D::SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	CScene2D::BindTexture(nTexIdx);

	return S_OK;
}

//==============================================================================
// ポーズベースの終了処理
//==============================================================================
void CPauseBase::Uninit(void)
{
	CScene2D::Uninit();
}

//==============================================================================
// ポーズベースの更新処理
//==============================================================================
void CPauseBase::Update(void)
{
	bool bPause = CPause::GetPause();

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	switch (bPause)
	{
	case true:
		col.a = 1.0f;
		break;

	case false:
		col.a = 0.0f;
		break;
	}

	CScene2D::SetCol(col);

	CScene2D::Update();
}

//==============================================================================
// ポーズベースの描画処理
//==============================================================================
void CPauseBase::Draw(void)
{
	CScene2D::Draw();
}

//==============================================================================
// ポーズベースの生成処理
//==============================================================================
CPauseBase *CPauseBase::Create(void)
{
	// インスタンス生成
	CPauseBase *pPauseBase;
	pPauseBase = new CPauseBase;

	// 初期化
	pPauseBase->Init();

	return pPauseBase;
}