//==============================================================================
//
// リザルトロゴの描画処理〔result_logo.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "sound.h"
#include "result.h"
#include "result_logo.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CResultLogo::CResultLogo(int nPriority) : CResult(nPriority)
{
	// ポリゴンの初期化
	m_pPolygon = NULL;
}

//==============================================================================
// デストラクタ
//==============================================================================
CResultLogo::~CResultLogo()
{
}

//==============================================================================
// リザルトロゴの初期化処理
//==============================================================================
HRESULT CResultLogo::Init(D3DXVECTOR3 pos)
{
	// メンバ変数の初期化
	m_pos = pos;

	// 終了状態の取得
	CResult::ENDSTATE state = CResult::GetEndState();

	if (m_pPolygon == NULL)
	{
		m_pPolygon = CPolygon::Create(D3DXVECTOR3(pos.x, pos.y, 0.0f),
			R_LOGO_SIZEX, R_LOGO_SIZEY,
			7);

		if (state == CResult::ENDSTATE_CLEAR)
		{
			m_pPolygon->SetTex(1, 2, 0, 0, 0.0f, 0.0f);
		}
		else
		{
			m_pPolygon->SetTex(1, 2, 0, 1, 0.0f, 0.0f);
		}
	}

	return S_OK;
}

//==============================================================================
// リザルトロゴの終了処理
//==============================================================================
void CResultLogo::Uninit(void)
{
	if (m_pPolygon != NULL)
	{// NULLチェック後に破棄
		m_pPolygon->Uninit();
		m_pPolygon = NULL;
	}

	Release();	// インスタンスのデリート
}

//==============================================================================
// リザルトロゴの更新処理
//==============================================================================
void CResultLogo::Update(void)
{
	
}

//==============================================================================
// リザルトロゴの描画処理
//==============================================================================
void CResultLogo::Draw(void)
{
	// リザルトロゴの描画
	if (m_pPolygon != NULL)
	{
		m_pPolygon->Draw();
	}
}

//==============================================================================
// リザルトロゴの生成処理
//==============================================================================
CResultLogo *CResultLogo::Create(D3DXVECTOR3 pos)
{
	// インスタンス生成
	CResultLogo *pResultLogo;
	pResultLogo = new CResultLogo;

	// 初期化
	pResultLogo->Init(pos);

	return pResultLogo;
}