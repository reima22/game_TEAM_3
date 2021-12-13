
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
//#include "textdata_system.h"
//#include "result_logo.h"
//#include "sceneX.h"
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
#include "start_cntdown.h"
#include "fog.h"
#include "select.h"

//==============================================================================
// 静的メンバ変数宣言
//==============================================================================
CPause *CGame::m_pPause = NULL;					// ポーズポインタ
CPlayer *CGame::m_pPlayer = NULL;				// プレイヤーポインタ
CObject **CGame::m_pObject = NULL;				// オブジェクトポインタ
CTerrain *CGame::m_pTerrain = NULL;				// メッシュポインタ
CTimer *CGame::m_pTimer = NULL;					// タイマーポインタ
CFall *CGame::m_pFall = NULL;					// 落下数ポインタ
CMeshfield **CGame::m_pMeshField = NULL;		// メッシュフィールドクラス
CStartCntdown *CGame::m_pStartCntdown = NULL;	// 開始時カウントダウンポインタ
CFog *CGame::m_pFog = NULL;						// フォグ効果クラス

//==============================================================================
// コンストラクタ
//==============================================================================
CGame::CGame(int nPriority) : CMode(nPriority)
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

	// 開始時カウントダウンの生成
	m_pStartCntdown = CStartCntdown::Create(SCREEN_CENTER, START_CNT_SIZE);

	// ポーズの生成
	m_pPause = CPause::Create();

	// ビルボードの配置
	//CSceneBillboard::Create(VECTOR3_NULL);
	
	return S_OK;
}

//==============================================================================
// ゲームモードの終了処理
//==============================================================================
void CGame::Uninit(void)
{
	// BGMの停止
	if (m_pSound != NULL && CManager::GetBGMPlay(CSound::BGMTYPE_GAME) == true)
	{
		m_pSound->Stop();
	}

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

	// 開始時カウントダウンの生成
	if (m_pStartCntdown != NULL)
	{
		m_pStartCntdown->Uninit();
		m_pStartCntdown = NULL;
	}


	// オブジェクトポインタの開放
	if (m_pObject != NULL)
	{
		delete[] m_pObject;
		m_pObject = NULL;
	}

	// フォグポインタの開放
	if (m_pFog != NULL)
	{
		m_pFog->Uninit();
		m_pFog = NULL;
	}

	// 死亡判定地形の開放
	if (m_pTerrain != NULL)
	{
		m_pTerrain = NULL;
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

	if (m_pTerrain != NULL)
	{
		m_pTerrain->Update();
	}

	// タイマーで切り替え
	if (m_pTimer != NULL)
	{
		if (m_pTimer->GetTimerCnt()->GetNumber() <= 0)
		{
			// 時間切れでゲームオーバー
			pFade->SetFade(CFade::FADE_OUT, CMode::MODE_RESULT);
		}
	}

	// フォグポインタの開放
	if (m_pFog != NULL)
	{
		m_pFog->Update();
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

	if (m_pFog != NULL)
	{
		m_pFog->Draw();
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
	if (pGame != NULL)
	{
		pGame->Init();
	}

	return pGame;
}

//==============================================================================
// ステージオブジェクト設定
//==============================================================================
void CGame::SetStageObject(void)
{
	// ローカル変数宣言
	int nNumMesh = 1;

	// 動的確保
	m_pMeshField = new CMeshfield*[nNumMesh];

	for (int nCntMesh = 0; nCntMesh < nNumMesh; nCntMesh++)
	{
		// メッシュフィールドの生成
		m_pMeshField[nCntMesh] = CMeshfield::Create(nCntMesh);
	}

	// フォグの生成
	m_pFog = CFog::Create();

	// データテキストの取得
	CStageSelect::STAGE_SELECT select = CStageSelect::GetSelectingStage();

	// ステージデータの取得
	CTextDataObject *pDataObject = CTextData::GetDataObject((CTextDataObject::STAGEINFO)select);

	if (pDataObject != NULL)
	{
		// ステージオブジェクト数の取得
		m_nNumObject = pDataObject->GetNumObject();

		// オブジェクトの動的確保
		m_pObject = new CObject*[m_nNumObject];

		// テキストからオブジェクトの生成
		for (int nCnt = 0; nCnt < m_nNumObject; nCnt++)
		{
			m_pObject[nCnt] = CObject::CreateFromData(nCnt);
		}
	}

	switch (select)
	{
	case CStageSelect::STAGE_SELECT_1:
		
		// BGMの生成
		if (m_pSound != NULL && CManager::GetBGMPlay(CSound::BGMTYPE_GAME) == true)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM002);
		}

		m_pTerrain = CTerrain::Create(CTerrainInfo::TERRAIN_TYPE::TERRAIN_VALLEY);

		m_pFog->SetFogCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		break;

	case CStageSelect::STAGE_SELECT_2:

		// BGMの生成
		if (m_pSound != NULL && CManager::GetBGMPlay(CSound::BGMTYPE_GAME) == true)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM003);
		}

		m_pTerrain = CTerrain::Create(CTerrainInfo::TERRAIN_TYPE::TERRAIN_OCEAN);

		m_pFog->SetFogCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		break;

	case CStageSelect::STAGE_SELECT_3:
		
		// BGMの生成
		if (m_pSound != NULL && CManager::GetBGMPlay(CSound::BGMTYPE_GAME) == true)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM004);
		}

		m_pTerrain = CTerrain::Create(CTerrainInfo::TERRAIN_TYPE::TERRAIN_LAVA);

		break;
	}
}