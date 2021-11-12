//=============================================================================
//
// メイン処理 [title.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "fade.h"
#include "sound.h"
#include "title.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "title_logo.h"
#include "title_enter.h"
//#include "dinput_keyboard.h"
#include "sceneX.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CBg*CTitle::m_pBg = NULL;							// 背景変数
CTitleLogo *CTitle::m_pTitleLogo = NULL;
CTitleEnter *CTitle::m_pTitleEnter = NULL;
//CLogo*CTitle::m_pLogo[2] = {};						// ロゴ変数


//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CTitle::CTitle()
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CTitle::~CTitle()
{

}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CTitle::Init(void)
{
	//背景テクスチャのロード
	//CBg::Load();

	//ロゴテクスチャのロード
	//CLogo::Load();

	//CSceneX::Create(D3DXVECTOR3(0.0f,0.0f,0.0f));

	//背景クラスの生成
	m_pBg = CBg::Create();

	// タイトルロゴ
	m_pTitleLogo = CTitleLogo::Create(T_LOGO_POS);

	// エンターサイン
	m_pTitleEnter = CTitleEnter::Create(T_ENTER_POS);

	//ロゴクラスの生成
	//m_pLogo[0] = CLogo::Create(D3DXVECTOR3(POS_START_X, 3100, 0), D3DXVECTOR3(800, 150, 0), m_pLogo[0]->LOGOTYPE_START);
	//m_pLogo[1] = CLogo::Create(D3DXVECTOR3(300, -1000, 0), D3DXVECTOR3(900, 450, 0), m_pLogo[0]->LOGOTYPE_TITLENAME);

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CTitle::Uninit(void)
{
	//背景テクスチャのアンロード
	//CBg::Unload();

	//ロゴテクスチャのロード
	//CLogo::Unload();

	// タイトルロゴ
	if (m_pTitleLogo != NULL)
	{
		m_pTitleLogo->Uninit();
		m_pTitleLogo = NULL;
	}

	// エンターサイン
	if (m_pTitleEnter != NULL)
	{
		m_pTitleEnter->Uninit();
		m_pTitleEnter = NULL;
	}


	Release();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CTitle::Update(void)
{

}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CTitle::Draw(void)
{

}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CTitle *CTitle::Create(void)
{
	CTitle *pTitle;
	pTitle = new CTitle;

	if (pTitle != NULL)
	{
		pTitle->Init();
	}

	return pTitle;
}

//*****************************************************************************
// 背景情報処理
//*****************************************************************************
CBg*CTitle::GetBg(void)
{
	return m_pBg;
}

//*****************************************************************************
// ロゴ情報処理
//*****************************************************************************
//CLogo*CTitle::GetLogo(void)
//{
//	return m_pLogo[2];
//}

