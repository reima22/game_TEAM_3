
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
#include "sceneBillboard.h"
#include "player.h"
#include "meshfield.h"
#include "object.h"
#include "textdata_object.h"
#include "textdata_meshfield.h"
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
#include "motion_player.h"
#include "bonus.h"
#include "checkpoint_logo.h"

//==============================================================================
// 静的メンバ変数宣言
//==============================================================================
CPause *CGame::m_pPause = NULL;										// ポーズポインタ
CPlayer *CGame::m_pPlayer = NULL;									// プレイヤーポインタ
CObject **CGame::m_pObject = {};									// オブジェクトポインタ
CTerrain *CGame::m_pTerrain = NULL;									// メッシュポインタ
CTimer *CGame::m_pTimer = NULL;										// タイマーポインタ
CFall *CGame::m_pFall = NULL;										// 落下数ポインタ
CMeshfield **CGame::m_pMeshField = {};								// メッシュフィールドクラス
CStartCntdown *CGame::m_pStartCntdown = NULL;						// 開始時カウントダウンポインタ
CFog *CGame::m_pFog = NULL;											// フォグ効果クラス
bool CGame::m_bGameEnd = false;										// ゲーム終了のフラグ
int CGame::m_nClearDirectingCnt = 0;								// ゲーム終了演出カウント
CGame::CLEARPHASE CGame::m_clearPhase = CLEARPHASE_NONE;			// クリアフェイズ
CGame::GAMEOVERPHASE CGame::m_gameoverPhase = GAMEOVERPHASE_NONE;	// ゲームオーバーフェイズ
CBonus *CGame::m_pBonus = NULL;
CCheckpointLogo *CGame::m_pCheckPointLogo = NULL;

//==============================================================================
// コンストラクタ
//==============================================================================
CGame::CGame(int nPriority) : CMode(nPriority)
{
	m_bGameEnd = false;
	m_nClearDirectingCnt = 0;
	m_clearPhase = CLEARPHASE_NONE;
	m_gameoverPhase = GAMEOVERPHASE_NONE;
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
	if (m_pPlayer == NULL)
	{
		m_pPlayer = CPlayer::Create();
	}

	// タイマーの配置
	if (m_pTimer == NULL)
	{
		m_pTimer = CTimer::Create();
	}

	// 落下数カウントの配置
	if (m_pFall == NULL)
	{
		m_pFall = CFall::Create();
	}

	// ボーナスカウントの配置
	if (m_pBonus == NULL)
	{
		m_pBonus = CBonus::Create();
	}

	// チェックポイントロゴ
	if (m_pCheckPointLogo == NULL)
	{
		m_pCheckPointLogo = CCheckpointLogo::Create();
	}

	// 開始時カウントダウンの生成
	if (m_pStartCntdown == NULL)
	{
		m_pStartCntdown = CStartCntdown::Create(SCREEN_CENTER, START_CNT_SIZE);
	}

	// ポーズの生成
	if (m_pPause == NULL)
	{
		m_pPause = CPause::Create();
	}

	//CSceneBillboard::Create(D3DXVECTOR3(0.0f, 50.0f, -2600.0f));

	// リザルトロゴの設定
	CreateLogo();
	
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

	// ボーナスカウントの終了
	if (m_pBonus != NULL)
	{
		m_pBonus->Uninit();
		m_pBonus = NULL;
	}

	// チェックポイントロゴの終了
	if (m_pCheckPointLogo != NULL)
	{
		m_pCheckPointLogo->Uninit();
		m_pCheckPointLogo = NULL;
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
		for (int nCnt = 0; nCnt < m_nNumObject; nCnt++)
		{
			m_pObject[nCnt]->Uninit();
		}

		delete[] m_pObject;
		m_pObject = NULL;
	}

	// メッシュフィールドポインタの開放
	if (m_pMeshField != NULL)
	{
		//for (int nCnt = 0; nCnt < m_nNumMeshfield; nCnt++)
		//{
		//	m_pMeshField[nCnt]->Uninit();
		//}

		delete m_pMeshField;		
		m_pMeshField = NULL;
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

	// リザルトロゴの破棄
	if (m_pResultLogo != NULL)
	{
		m_pResultLogo->Uninit();
		m_pResultLogo = NULL;
	}

	Release();	// インスタンスのデリート
}

//==============================================================================
// ゲームモードの更新処理
//==============================================================================
void CGame::Update(void)
{
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
			// 時間切れでゲームオーバー
			CResult::SetEndState(CResult::ENDSTATE_GAMEOVER);
			m_pPlayer->SetGameOver(true);
			m_bGameEnd = true;
		}
	}

	// フォグポインタの開放
	if (m_pFog != NULL)
	{
		m_pFog->Update();
	}

	// ゲーム終了
	if (m_bGameEnd == true)
	{
		EndGame();
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
	// レンダラーの取得
	CRenderer *pRenderer = CManager::GetRenderer();

	// メッシュデータの取得
	CTextDataMeshfield *pDataMeshfield = CTextData::GetDataMeshfield();
	m_nNumMeshfield = pDataMeshfield->GetNumMesh();

	// 動的確保
	m_pMeshField = new CMeshfield*[m_nNumMeshfield];

	for (int nCntMesh = 0; nCntMesh < m_nNumMeshfield; nCntMesh++)
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

	//CObject::Create(D3DXVECTOR3(0.0f, 100.0f, -2250.0f), VECTOR3_NULL, "data/MODEL/OBJECT/01_scaffold01.x", VECTOR2_NULL, CObject::MOVETYPE_SIDE, 2.0f, CObject::OBJATTRIBUTE_NONE);
	//CObject::Create(D3DXVECTOR3(0.0f, 100.0f, -2400.0f), VECTOR3_NULL, "data/MODEL/OBJECT/01_scaffold01.x", VECTOR2_NULL, CObject::MOVETYPE_DEPTH, 2.0f, CObject::OBJATTRIBUTE_NONE);
	//CObject::Create(D3DXVECTOR3(-150.0f, 200.0f, -2400.0f), VECTOR3_NULL, "data/MODEL/OBJECT/01_scaffold01.x", VECTOR2_NULL,  CObject::MOVETYPE_UPDOWN, 1.0f, CObject::OBJATTRIBUTE_NONE);

	switch (select)
	{
	case CStageSelect::STAGE_SELECT_1:
		
		// BGMの生成
		if (m_pSound != NULL && CManager::GetBGMPlay(CSound::BGMTYPE_GAME) == true)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM002);
		}

		m_pTerrain = CTerrain::Create(CTerrainInfo::TERRAIN_TYPE::TERRAIN_VALLEY);

		if (m_pFog != NULL)
		{
			m_pFog->SetFogCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			pRenderer->SetBSColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		}

		break;

	case CStageSelect::STAGE_SELECT_2:

		// BGMの生成
		if (m_pSound != NULL && CManager::GetBGMPlay(CSound::BGMTYPE_GAME) == true)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM003);
		}

		m_pTerrain = CTerrain::Create(CTerrainInfo::TERRAIN_TYPE::TERRAIN_OCEAN);

		m_pFog->SetFogCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		pRenderer->SetBSColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		break;

	case CStageSelect::STAGE_SELECT_3:
		
		// BGMの生成
		if (m_pSound != NULL && CManager::GetBGMPlay(CSound::BGMTYPE_GAME) == true)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM004);
		}

		m_pTerrain = CTerrain::Create(CTerrainInfo::TERRAIN_TYPE::TERRAIN_LAVA);

		pRenderer->SetBSColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

		break;
	}
}

//==============================================================================
// ゲーム終了演出
//==============================================================================
void CGame::EndGame(void)
{
	// クリア演出カウントの加算
	m_nClearDirectingCnt++;

	switch (CResult::GetEndState())
	{
	case CResult::ENDSTATE_CLEAR:		// クリア時

		GameClear();

		break;

	case CResult::ENDSTATE_GAMEOVER:	// ゲームオーバー時

		GameOver();

		break;
	}
}

//==============================================================================
// ゲームクリア
//==============================================================================
void CGame::GameClear(void)
{
	// フェード情報の取得
	CFade *pFade;
	pFade = CManager::GetFade();

	switch (m_clearPhase)
	{
	case CLEARPHASE_NONE:
		SetClearPhase(CGame::CLEARPHASE_WAIT);
		break;

	case CLEARPHASE_WAIT:
		if (m_nClearDirectingCnt >= CNT_ONE_SECOND)
		{
			m_pSound->Play(CSound::SOUND_LABEL_SE_STAGECLEAR);	// ファンファーレ
			SetClearPhase(CLEARPHASE_PAUSE);
			m_nClearDirectingCnt = 0;
		}
		break;

	case CLEARPHASE_PAUSE:

		m_pPlayer->GetMotionPlayer()->SetMotion(CMotionPlayer::MOTIONTYPE_CLEAR);
		m_pResultLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pResultLogo->BindTexture("G_RESULT_CLEAR");

		if (m_nClearDirectingCnt >= CNT_ONE_SECOND * 6)
		{
			SetClearPhase(CLEARPHASE_FADE);
		}
		break;

	case CLEARPHASE_FADE:

		CResult::SetEndState(CResult::ENDSTATE_CLEAR);
		pFade->SetFade(CFade::FADE_OUT, CMode::MODE_RESULT);

		break;
	}
}

//==============================================================================
// ゲームオーバー
//==============================================================================
void CGame::GameOver(void)
{
	// フェード情報の取得
	CFade *pFade;
	pFade = CManager::GetFade();

	switch (m_gameoverPhase)
	{
	case GAMEOVERPHASE_NONE:
		m_pSound->Stop();
		m_pSound->Play(CSound::SOUND_LABEL_SE_TIMEOVER);
		SetOverPhase(GAMEOVERPHASE_WAIT);
		break;

	case GAMEOVERPHASE_WAIT:
		if (m_nClearDirectingCnt >= CNT_ONE_SECOND * 2)
		{
			SetOverPhase(GAMEOVERPHASE_DIRECTION);
			m_pSound->Play(CSound::SOUND_LABEL_SE_GAMEOVER);
			m_nClearDirectingCnt = 0;
		}
		break;

	case GAMEOVERPHASE_DIRECTION:

		m_pResultLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pResultLogo->BindTexture("G_RESULT_GAMEOVER");

		if (m_nClearDirectingCnt >= CNT_ONE_SECOND * 6)
		{
			SetOverPhase(GAMEOVERPHASE_FADE);
		}
		break;

	case GAMEOVERPHASE_FADE:

		CResult::SetEndState(CResult::ENDSTATE_GAMEOVER);
		pFade->SetFade(CFade::FADE_OUT, CMode::MODE_RESULT);

		break;
	}
}

//==============================================================================
// ゲーム結果のロゴ
//==============================================================================
void CGame::CreateLogo(void)
{
	if (m_pResultLogo == NULL)
	{
		m_pResultLogo = CScene2D::Create();

		m_pResultLogo->SetPosition(LOGO_POS);						// 位置
		m_pResultLogo->SetSize(LOGO_SIZE);							// サイズ
		m_pResultLogo->SetTex(1, 1, 0, 0, 0.0f, 0.0f);				// テクスチャ座標
		m_pResultLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// 色
	}
}