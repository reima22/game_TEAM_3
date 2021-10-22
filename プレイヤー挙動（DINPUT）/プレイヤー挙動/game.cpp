
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
#include "object.h"
#include "textdata_object.h"

//==============================================================================
// 静的メンバ変数宣言
//==============================================================================
int CGame::m_nClearDefeat;	// クリアする撃破数
int CGame::m_nEndInvasion;	// 侵入限界数
CCharacter *CGame::m_pCharaPlayer = NULL;	// プレイヤーキャラのポインタ
bool CGame::m_bGameStart;
int CGame::m_nCntDownEnd = 0;
CPlayer *CGame::m_pPlayer = NULL;
CObject **CGame::m_pObject = NULL;

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
HRESULT CGame::Init(void)
{
	//CTextDataObject *pDataObject = CTextData::GetDataObject();

	//// ステージオブジェクトの配置
	//m_nNumObject = pDataObject->GetNumObject();

	//// オブジェクト数の動的確保
	//m_pObject = new CObject*[m_nNumObject];

	//// オブジェクトの生成
	//for (int nCnt = 0; nCnt < m_nNumObject; nCnt++)
	//{
	//	m_pObject[nCnt] = 
	//		CObject::Create(
	//			pDataObject->GetPosObject(nCnt),
	//			pDataObject->GetRotObject(nCnt),
	//			pDataObject->GetTypeObject(nCnt));
	//}

	// ポーズの生成
	CPause::Create();

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

	// オブジェクトポインタの開放
	if (m_pObject != NULL)
	{
		delete m_pObject;
		m_pObject = NULL;
	}

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

	// 初期化
	pGame->Init();

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