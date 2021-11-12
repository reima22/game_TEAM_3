//=============================================================================
//
// メイン処理 [bg.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "logo.h"
#include "scene2D.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"
#include "renderer.h"
#include "dinput_keyboard.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
LPDIRECT3DTEXTURE9 CLogo::m_apTexture[MAX_LOGO] = {};			// テクスチャ

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CLogo::CLogo(int nPriority) :CScene(nPriority)
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CLogo::~CLogo()
{

}

//*****************************************************************************
// 生成処理
//*****************************************************************************
CLogo *CLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, LOGOTYPE LogoType)
{
	// 動的確保
	CLogo* pLogo;
	pLogo = new CLogo;

	// 初期の呼び出し
	pLogo->Init(pos, scale);

	// ロゴ情報の呼び出し
	pLogo->SetInfoType(LogoType);

	// 値を返す
	return pLogo;
}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
HRESULT CLogo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// 大きさ
	m_scale = scale;

	// 移動値
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Enterを押したかどうか
	m_bEnter = false;

	// チュートリアル画面に移動したかどうか
	m_bTutorial = false;

	// ジャンプ判定
	m_bJump = false;

	// 決定点滅時間
	m_nTimeColor = 0;

	// 待機点滅カウント
	m_nCntColor = 0;

	// タイマー
	m_nTimer = 0;

	// ジャンプカウント
	m_nJumpCnt = 0;

	// 出現カウント
	m_nAppearanceCnt = 0;

	// 移動速度
	m_fSpd = 0.0f;

	// 種類
	SetObjType(OBJTYPE_LOGO);

	// 背景の切り替え
	switch (CManager::GetMode())
	{
		// タイトル画面だった場合
		case CManager::MODE_TITLE:

			for (int nCnt = 0; nCnt <3; nCnt++)
			{
				if (m_apScene2D[nCnt] == NULL)
				{
					m_apScene2D[nCnt] = new CScene2D;
					m_apScene2D[nCnt]->Init(pos,scale);
					m_apScene2D[nCnt]->BindTexture(m_apTexture[m_LogoType]);
				}
			}

		break;
	}

	// 値を返す
	return S_OK;
}

//*****************************************************************************
// 終了処理
//*****************************************************************************
void CLogo::Uninit(void)
{

	// 背景の切り替え
	switch (CManager::GetMode())
	{
		// タイトル画面だった場合
	case CManager::MODE_TITLE:

		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			if (m_apScene2D[nCnt] == NULL)
			{
				m_apScene2D[nCnt] = new CScene2D;
				m_apScene2D[nCnt]->Uninit();
				m_apScene2D[nCnt]->BindTexture(m_apTexture[m_LogoType]);
			}
		}

		break;

	}

	Release();
}

//*****************************************************************************
// 更新処理
//*****************************************************************************
void CLogo::Update(void)
{
	// 入力情報
	CInputKeyBoard *pKeyBoard;
	pKeyBoard = CManager::GetInputKeyBoard();

	//// サウンドのポインタ
	//CSound *pSound = CManager::GetSound();

	// 位置の取得
	D3DXVECTOR3 pos;
	pos = m_apScene2D[0]->GetPosition();

	// 背景の切り替え
	switch (CManager::GetMode())
	{
		// タイトル画面だった場合
	case CManager::MODE_TITLE:

		// タイマー
		m_nTimer++;


			// ロゴタイプがSTATEの場合
			if (m_LogoType == LOGOTYPE_START)
			{

				// テクスチャ
				m_apScene2D[0]->BindTexture(m_apTexture[0]);

				// 判定がtrueの場合
				if (m_bEnter == true && pKeyBoard->GetTrigger(DIK_RETURN) == true)
				{
					// 判定をtrueに変える
					m_bTutorial = true;

					////SE
					//pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON);
				}
				else if (m_bEnter == false)
				{// 判定がfalseの場合

					// エンターキーを押した場合
					if (pKeyBoard->GetTrigger(DIK_RETURN) == true)
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
						m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					}
					else
					{
						// 色
						m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
					}

					// カウントが50を超えた場合
					if (m_nTimeColor >= TIME_COLOR)
					{
						// フェード
						CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TITLE);

						// 判定をfalseに変える
						m_bEnter = false;

						// 判定をfalseに変える
						m_bTutorial = false;

						// タイマーを0にする
						m_nTimer = 0;
					}
				}

				// 位置が一定よりも高い位置にあるかつ判定がfalseの場合
				if (pos.y > POS_START_Y && m_bEnter == false)
				{
					// 移動値
					m_move.y = MOVE_START_Y;

					// 色
					m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
				}
				else
				{
					// 位置を与える
					pos.y = POS_START_Y;

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
						m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, (1.0f / ((float)m_nCntColor *0.75f)));
					}
					
					if (m_nCntColor > 50 && m_nCntColor <= 100)
					{// カウントが指定値の範囲内の場合

						// 色
						m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, (0.0001f * ((float)m_nCntColor * 100.0f)));
					}
					else if (m_nCntColor > 150)
					{ //カウントが指定値を超えている場合

						//カウントを0にする
						m_nCntColor = 0;
					}
				}

			}

		// ロゴタイプがTITLENAMEの場合
		if (m_LogoType == LOGOTYPE_TITLENAME)
		{
			// テクスチャ
			m_apScene2D[0]->BindTexture(m_apTexture[1]);

			// 色
			m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// Enterを押すか、位置が指定値より右だった場合
			if (pKeyBoard->GetTrigger(DIK_RETURN) == true || pos.x > POS_TITLE_X)
			{
				// 移動値
				m_move.x = 0.0f;
				m_move.y = 0.0f;

				// 位置を与える
				pos.x = POS_TITLE_X;
				pos.y = POS_TITLE_Y;

				//	カウント
				m_nAppearanceCnt = 1;
				
			}
			else  if(pos.x < POS_TITLE_X)
			{// 位置が指定値より左だった場合

				// 重力
				float fGravity = GRAVITY;
				
				// カウント値が一定値を下回っている場合
				if (m_nJumpCnt <= 0)
				{
					// 速度
					m_fSpd = MOVE_SPEED;
				}

				// 速度に重力を代入
				m_fSpd += fGravity;

				// 位置が指定値よりも高い場合
				if (pos.y > POS_TITLE_Y)
				{
					// 速度に代入
					m_fSpd = -m_fSpd;

					// カウント加算
					m_nJumpCnt++;
				}	

				// 移動値
				m_move.x += MOVE_TITLE_X;
				m_move.y = m_fSpd + (m_nJumpCnt / 1.2f);
			}
		}

		break;
	}

	// 移動値を位置座標に足す
	pos += m_move;

	// 位置情報を与える
	m_apScene2D[0]->SetPosition(pos, m_scale);

	// 色
	m_apScene2D[0]->SetColor(m_Color);

}

//*****************************************************************************
// 描画処理
//*****************************************************************************
void CLogo::Draw(void)
{
}

//*****************************************************************************
// テクスチャ読み込み処理
//*****************************************************************************
HRESULT CLogo::Load(void)
{
	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\TitleLogo02.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\TitleLogo01.png", &m_apTexture[1]);

	return S_OK;
}

//*****************************************************************************
// テクスチャ破棄処理
//*****************************************************************************
void CLogo::Unload(void)
{
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < MAX_LOGO; nCnt++)
	{
		//テクスチャの開放
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}