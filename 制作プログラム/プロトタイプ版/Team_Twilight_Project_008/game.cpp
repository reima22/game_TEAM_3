
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
#include "collision.h" 
#include "shadow.h"
#include "Terrain.h"
#include "timer.h"
#include "timer_count.h"
#include "fall.h"
#include "camera.h"

//==============================================================================
// 静的メンバ変数宣言
//==============================================================================
CPause *CGame::m_pPause = NULL;		// ポーズポインタ
CPlayer *CGame::m_pPlayer = NULL;	// プレイヤーポインタ
CObject **CGame::m_pObject = NULL;	// オブジェクトポインタ
CTerrain *CGame::m_pTerrain = NULL;	// メッシュポインタ
CTimer *CGame::m_pTimer = NULL;		// タイマーポインタ
CFall *CGame::m_pFall = NULL;		// 落下数ポインタ

//==============================================================================
// コンストラクタ
//==============================================================================
CGame::CGame()
{

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
	// カメラの位置初期化
	CCamera *pCamera = CManager::GetCamera();
	pCamera->SetInit();

	// ステージ設定
	SetStageObject();
	
	// 3Dプレイヤーの表示
	m_pPlayer = CPlayer::Create();

	// タイマーの配置
	m_pTimer = CTimer::Create();

	// 落下数カウントの配置
	m_pFall = CFall::Create();

	// ポーズの生成
	m_pPause = CPause::Create();

	// ビルボードの配置
	//CSceneBillboard::Create(VECTOR3_NULL);

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
	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		m_pPause = NULL;
	}

	// タイマーの終了
	if (m_pTimer != NULL)
	{
		m_pTimer->Uninit();
		m_pTimer = NULL;
	}

	// 落下カウントの終了
	if (m_pFall != NULL)
	{
		m_pFall->Uninit();
		m_pFall = NULL;
	}
	
	// プレイヤーの終了
	if (m_pPlayer != NULL)
	{
		m_pPlayer->Uninit();
		m_pPlayer = NULL;
	}

	// オブジェクトポインタの開放
	if (m_pObject != NULL)
	{
		delete[] m_pObject;
		m_pObject = NULL;
	}

	Release();	// インスタンスのデリート
}

//==============================================================================
// ゲームモードの更新処理
//==============================================================================
void CGame::Update(void)
{
	// フェード情報の取得
	CFade *pFade;
	pFade = CManager::GetFade();

	// メッシュ地形の更新
	if (m_pTerrain != NULL)
	{
		m_pTerrain->Update();
	}

	// タイマーで切り替え
	if (m_pTimer != NULL)
	{
		if (m_pTimer->GetTimerCnt()->GetNumber() <= 0)
		{
			// 時間切れでゲームやり直し(デバッグ用)
			pFade->SetFade(CFade::FADE_OUT, CMode::MODE_GAME);
		}
	}
}

//==============================================================================
// ゲームモードの描画処理
//==============================================================================
void CGame::Draw(void)
{
	if (m_pTerrain != NULL)
	{
		m_pTerrain->Draw();
	}
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
// ステージオブジェクト設定
//==============================================================================
void CGame::SetStageObject(void)
{
	// メッシュフィールドの生成
	//CMeshField::Create(VECTOR3_NULL, VECTOR3_NULL, 10, 10, 100, 100);

	// メッシュフィールド
	m_pTerrain = CTerrain::Create(CTerrainInfo::TERRAIN_TYPE::TERRAIN_LAVA);

	//CMeshField::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), VECTOR3_NULL, 10, 10, 100, 100);

	// データテキストの取得
	CTextDataObject *pDataObject = CTextData::GetDataObject();

	if (pDataObject != NULL)
	{
		// ステージオブジェクトの配置
		m_nNumObject = pDataObject->GetNumObject();

		// オブジェクト数の動的確保
		m_pObject = new CObject*[m_nNumObject];

		// オブジェクトの生成
		for (int nCnt = 0; nCnt < m_nNumObject; nCnt++)
		{
			m_pObject[nCnt] =
				CObject::Create(
					D3DXVECTOR3(
						pDataObject->GetInfo(nCnt, CTextDataObject::OBJECTINFO_POS_X),
						pDataObject->GetInfo(nCnt, CTextDataObject::OBJECTINFO_POS_Y),
						pDataObject->GetInfo(nCnt, CTextDataObject::OBJECTINFO_POS_Z)),
					D3DXVECTOR3(
						pDataObject->GetInfo(nCnt, CTextDataObject::OBJECTINFO_ROT_X),
						pDataObject->GetInfo(nCnt, CTextDataObject::OBJECTINFO_ROT_Y),
						pDataObject->GetInfo(nCnt, CTextDataObject::OBJECTINFO_ROT_Z)),
					pDataObject->GetTypeObject(nCnt),
					D3DXVECTOR2(
						pDataObject->GetShadowWidth(nCnt),
						pDataObject->GetShadowDepth(nCnt)),
					pDataObject->GetSavePoint(nCnt));
		}
	}
}