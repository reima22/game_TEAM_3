//==============================================================================
//
// タイトルロゴ描画処理〔title_logo.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "sound.h"
#include "title_logo.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"

// 静的メンバ変数宣言
bool CTitleLogo::m_bLogoMoveEnd;

//==============================================================================
// コンストラクタ
//==============================================================================
CTitleLogo::CTitleLogo(int nPriority) : CScene2D(nPriority)
{
	// ポリゴンの初期化
	m_pScene2D = NULL;

	m_bLogoMoveEnd = false;
	m_nMoveCnt = 0;
}

//==============================================================================
// デストラクタ
//==============================================================================
CTitleLogo::~CTitleLogo()
{
}

//==============================================================================
// タイトルロゴの初期化処理
//==============================================================================
HRESULT CTitleLogo::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;

	if (m_pScene2D == NULL)
	{
		m_pScene2D = CScene2D::Create();
		m_pScene2D->SetPosition(pos);
		m_pScene2D->SetSize(T_LOGO_SIZE);
		m_pScene2D->SetTex(1, 1, 0, 0, 0, 0);
		m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pScene2D->BindTexture(4);
	}

	return S_OK;
}

//==============================================================================
// タイトルロゴの終了処理
//==============================================================================
void CTitleLogo::Uninit(void)
{
	if (m_pScene2D != NULL)
	{// NULLチェック後に破棄
		delete m_pScene2D;
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	Release();	// インスタンスのデリート
}

//==============================================================================
// タイトルロゴの更新処理
//==============================================================================
void CTitleLogo::Update(void)
{
	// キーボードの取得
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();
	
	// ゲームパッドの取得
	CGamepad *gamepad = CManager::GetInputGamepad();

	// フェードの取得
	CFade *pFade = CManager::GetFade();

	// 判定がtrueの場合
	if (m_bEnter == true && keyboard->GetTrigger(CInput::KEYINFO_OK) == true)
	{
		// 判定をtrueに変える
		m_bTutorial = true;

		////SE
		//pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON);
	}
	else if (m_bEnter == false)
	{// 判定がfalseの場合

	 // エンターキーを押した場合
		if (keyboard->GetTrigger(CInput::KEYINFO_OK) == true)
		{
			// 判定をtrueに変える
			m_bEnter = true;

			// カウントの値を0にする
			m_nTimeColor = 0;

		}
	}

	// 判定がどちらもtrueの場合
	if (m_bEnter == true && m_bTutorial == true)
	{
		// カウント加算
		m_nTimeColor++;

		// カウントが5で割ると0になる場合
		if (m_nTimeColor % 5 == 0)
		{
			// 色
			m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			// 色
			m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		}

		// カウントが50を超えた場合
		if (m_nTimeColor >= COLOR_CNT)
		{
			// フェード
			pFade->SetFade(CFade::FADE_OUT, CMode::MODE_GAME);

			// 判定をfalseに変える
			m_bEnter = false;

			// 判定をfalseに変える
			m_bTutorial = false;

			// タイマーを0にする
			m_nTimer = 0;
		}
	}

	// 位置が一定よりも高い位置にあるかつ判定がfalseの場合
	if (m_pos.y > POS_START_Y && m_bEnter == false)
	{
		// 移動値
		m_move.y = MOVE_START_Y;

		// 色
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	}
	else
	{
		// 位置を与える
		m_pos.y = POS_START_Y;

		// 移動値
		m_move.y = 0.0f;

		// 判定をtrueに変える
		m_bEnter = true;

		//待機点滅カウント
		m_nCntColor++;
	}

	// 判定がtrueではない場合
	if (m_bTutorial != true)
	{
		// カウントが指定値より低い場合場合
		if (m_nCntColor <= 50)
		{
			// 色
			m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, (1.0f / ((float)m_nCntColor *0.75f)));
		}

		if (m_nCntColor > 50 && m_nCntColor <= 100)
		{// カウントが指定値の範囲内の場合

		 // 色
			m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, (0.0001f * ((float)m_nCntColor * 100.0f)));
		}
		else if (m_nCntColor > 150)
		{ //カウントが指定値を超えている場合

		  //カウントを0にする
			m_nCntColor = 0;
		}
	}

	m_pScene2D->SetPosition(m_pos);
}

//==============================================================================
// タイトルロゴの描画処理
//==============================================================================
void CTitleLogo::Draw(void)
{

}

//==============================================================================
// タイトルロゴの生成処理
//==============================================================================
CTitleLogo *CTitleLogo::Create(D3DXVECTOR3 pos)
{
	// インスタンス生成
	CTitleLogo *pTitleLogo;
	pTitleLogo = new CTitleLogo;

	// 初期化
	pTitleLogo->Init(pos);

	return pTitleLogo;
}