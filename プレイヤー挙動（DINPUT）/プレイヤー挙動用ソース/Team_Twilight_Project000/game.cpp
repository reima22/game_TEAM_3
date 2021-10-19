
//==============================================================================
//
// ゲームモード処理〔game.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "sound.h"
#include "fade.h"
#include "result.h"
#include "pause.h"
#include "textdata_system.h"
#include "result_logo.h"
#include "sceneX.h"
#include "sceneBillboard.h"
#include "player.h"
#include "meshfield.h"

//==============================================================================
// 静的メンバ変数宣言
//==============================================================================
int CGame::m_nClearDefeat;	// クリアする撃破数
int CGame::m_nEndInvasion;	// 侵入限界数
CCharacter *CGame::m_pCharaPlayer = NULL;	// プレイヤーキャラのポインタ
bool CGame::m_bGameStart;
int CGame::m_nCntDownEnd = 0;
CPlayer *CGame::m_pPlayer = NULL;

//CSceneX *CGame::m_pSceneX = NULL;

//==============================================================================
// コンストラクタ
//==============================================================================
CGame::CGame()
{
	m_nCntDownEnd = 0;
}

//==============================================================================
// デストラクタ
//==============================================================================
CGame::~CGame()
{
}

//==============================================================================
// ゲームモードの初期化処理
//==============================================================================
HRESULT CGame::Init(D3DXVECTOR3 pos)
{
	// 背景生成
	//CBg::Create();

	// 警告画面の生成
	//CCaution::Create(SCREEN_CENTER);

	// メインUI生成
	//CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 675.0f, 0.0f));

	// ボーダーラインの生成
	//CLine::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 620.0f, 0.0f));

	// プレイヤー生成
	//m_pCharaPlayer = CPlayer::Create(PLAYER_POS,
	//	CScene::OBJTYPE_PLAYER,
	//	PLAYERX, PLAYERY);

	// 残機数の生成
	//CStock::Create(STOCK_POS);

	// 撃破数の生成
	//CDefeat::Create(DEFEAT_POS);

	//// 侵入数の生成
	//CInvasion::Create(INVASION_POS);

	// スコアの生成
	//CScore::Create(SCORE_POS, 10.0f, 20.0f);

	// ライフの生成
	//CLife::Create(LIFE_POS);

	// ポーズの生成
	CPause::Create();

	// メッセージ生成
	//CMessage::Create(SCREEN_CENTER);

	// メッシュフィールドの生成
	CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 10, 100, 100);

	// 3Dプレイヤーの表示
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ビルボードの配置
	//CSceneBillboard::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// BGMの生成
	if (CManager::GetBGMPlay(CSound::BGMTYPE_GAME) == true)
	{ 
		//CSound::Play(CSound::SOUND_LABEL_BGM001);
	}
	
	return S_OK;
}

//==============================================================================
// ゲームモードの終了処理
//==============================================================================
void CGame::Uninit(void)
{
	// BGMの停止
	CSound::Stop();

	// ポーズの終了
	CPause::Uninit();

	Release();	// インスタンスのデリート
}

//==============================================================================
// ゲームモードの更新処理
//==============================================================================
void CGame::Update(void)
{


}

//==============================================================================
// ゲームモードの描画処理
//==============================================================================
void CGame::Draw(void)
{
	CPause::Draw();
}

//==============================================================================
// ゲームモードの生成処理
//==============================================================================
CGame *CGame::Create()
{
	// インスタンス生成
	CGame *pGame;
	pGame = new CGame;
	D3DXVECTOR3 pos;

	// 初期化
	pGame->Init(pos);

	return pGame;
}

//==============================================================================
// 位置の取得
//==============================================================================
D3DXVECTOR3 CGame::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// サイズの取得
//==============================================================================
D3DXVECTOR3 CGame::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}