//=============================================================================
//
// メイン処理 [tutorial.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "sound.h"
#include "fade.h"
#include "tutorial.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
CBg*CTutorial::m_pBg = NULL;							// 背景変数

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CTutorial::CTutorial()
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CTutorial::~CTutorial()
{

}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CTutorial::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{

	//初期化の呼び出し
	//CScene::Init(pos, scale);

	//背景テクスチャのロード
	CBg::Load();

	//背景クラスの生成
	m_pBg = CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_GAMEHEIGHT + 50, 0));

	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CTutorial::Uninit(void)
{
	//背景テクスチャのアンロード
	CBg::Unload();

	Release();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CTutorial::Update(void)
{
	CInputKeyBoard *pKeyBoard;
	pKeyBoard = CManager::GetInputKeyBoard();

	////サウンドのポインタ
	//CSound *pSound = CManager::GetSound();

	if (pKeyBoard->GetTrigger(DIK_RETURN) == true)
	{
	/*	pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON);
*/
		CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TITLE);
	}
}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CTutorial::Draw(void)
{

}


//*****************************************************************************
// 背景情報処理
//*****************************************************************************
CBg*CTutorial::GetBg(void)
{
	return m_pBg;
}
