
//==============================================================================
//
// �Q�[�����[�h�����kgame.cpp�l
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
// �ÓI�����o�ϐ��錾
//==============================================================================
CPause *CGame::m_pPause = NULL;										// �|�[�Y�|�C���^
CPlayer *CGame::m_pPlayer = NULL;									// �v���C���[�|�C���^
CObject **CGame::m_pObject = {};									// �I�u�W�F�N�g�|�C���^
CTerrain *CGame::m_pTerrain = NULL;									// ���b�V���|�C���^
CTimer *CGame::m_pTimer = NULL;										// �^�C�}�[�|�C���^
CFall *CGame::m_pFall = NULL;										// �������|�C���^
CMeshfield **CGame::m_pMeshField = {};								// ���b�V���t�B�[���h�N���X
CStartCntdown *CGame::m_pStartCntdown = NULL;						// �J�n���J�E���g�_�E���|�C���^
CFog *CGame::m_pFog = NULL;											// �t�H�O���ʃN���X
bool CGame::m_bGameEnd = false;										// �Q�[���I���̃t���O
int CGame::m_nClearDirectingCnt = 0;								// �Q�[���I�����o�J�E���g
CGame::CLEARPHASE CGame::m_clearPhase = CLEARPHASE_NONE;			// �N���A�t�F�C�Y
CGame::GAMEOVERPHASE CGame::m_gameoverPhase = GAMEOVERPHASE_NONE;	// �Q�[���I�[�o�[�t�F�C�Y
CBonus *CGame::m_pBonus = NULL;
CCheckpointLogo *CGame::m_pCheckPointLogo = NULL;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CGame::CGame(int nPriority) : CMode(nPriority)
{
	m_bGameEnd = false;
	m_nClearDirectingCnt = 0;
	m_clearPhase = CLEARPHASE_NONE;
	m_gameoverPhase = GAMEOVERPHASE_NONE;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CGame::~CGame()
{
}

//==============================================================================
// �Q�[�����[�h�̏���������
//==============================================================================
HRESULT CGame::Init(void)
{
	// �J�����̈ʒu������
	CCamera *pCamera = CManager::GetCamera();
	pCamera->SetInit();

	// �X�e�[�W�ݒ�
	SetStageObject();
	
	// 3D�v���C���[�̕\��
	if (m_pPlayer == NULL)
	{
		m_pPlayer = CPlayer::Create();
	}

	// �^�C�}�[�̔z�u
	if (m_pTimer == NULL)
	{
		m_pTimer = CTimer::Create();
	}

	// �������J�E���g�̔z�u
	if (m_pFall == NULL)
	{
		m_pFall = CFall::Create();
	}

	// �{�[�i�X�J�E���g�̔z�u
	if (m_pBonus == NULL)
	{
		m_pBonus = CBonus::Create();
	}

	// �`�F�b�N�|�C���g���S
	if (m_pCheckPointLogo == NULL)
	{
		m_pCheckPointLogo = CCheckpointLogo::Create();
	}

	// �J�n���J�E���g�_�E���̐���
	if (m_pStartCntdown == NULL)
	{
		m_pStartCntdown = CStartCntdown::Create(SCREEN_CENTER, START_CNT_SIZE);
	}

	// �|�[�Y�̐���
	if (m_pPause == NULL)
	{
		m_pPause = CPause::Create();
	}

	//CSceneBillboard::Create(D3DXVECTOR3(0.0f, 50.0f, -2600.0f));

	// ���U���g���S�̐ݒ�
	CreateLogo();
	
	return S_OK;
}

//==============================================================================
// �Q�[�����[�h�̏I������
//==============================================================================
void CGame::Uninit(void)
{
	// BGM�̒�~
	if (m_pSound != NULL && CManager::GetBGMPlay(CSound::BGMTYPE_GAME) == true)
	{
		m_pSound->Stop();
	}

	// �|�[�Y�̏I��
	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		m_pPause = NULL;
	}

	// �^�C�}�[�̏I��
	if (m_pTimer != NULL)
	{
		m_pTimer->Uninit();
		m_pTimer = NULL;
	}

	// �����J�E���g�̏I��
	if (m_pFall != NULL)
	{
		m_pFall->Uninit();
		m_pFall = NULL;
	}

	// �{�[�i�X�J�E���g�̏I��
	if (m_pBonus != NULL)
	{
		m_pBonus->Uninit();
		m_pBonus = NULL;
	}

	// �`�F�b�N�|�C���g���S�̏I��
	if (m_pCheckPointLogo != NULL)
	{
		m_pCheckPointLogo->Uninit();
		m_pCheckPointLogo = NULL;
	}
	
	// �v���C���[�̏I��
	if (m_pPlayer != NULL)
	{
		m_pPlayer->Uninit();
		m_pPlayer = NULL;
	}

	// �J�n���J�E���g�_�E���̐���
	if (m_pStartCntdown != NULL)
	{
		m_pStartCntdown->Uninit();
		m_pStartCntdown = NULL;
	}

	// �I�u�W�F�N�g�|�C���^�̊J��
	if (m_pObject != NULL)
	{
		for (int nCnt = 0; nCnt < m_nNumObject; nCnt++)
		{
			m_pObject[nCnt]->Uninit();
		}

		delete[] m_pObject;
		m_pObject = NULL;
	}

	// ���b�V���t�B�[���h�|�C���^�̊J��
	if (m_pMeshField != NULL)
	{
		//for (int nCnt = 0; nCnt < m_nNumMeshfield; nCnt++)
		//{
		//	m_pMeshField[nCnt]->Uninit();
		//}

		delete m_pMeshField;		
		m_pMeshField = NULL;
	}

	// �t�H�O�|�C���^�̊J��
	if (m_pFog != NULL)
	{
		m_pFog->Uninit();
		m_pFog = NULL;
	}

	// ���S����n�`�̊J��
	if (m_pTerrain != NULL)
	{
		m_pTerrain = NULL;
	}

	// ���U���g���S�̔j��
	if (m_pResultLogo != NULL)
	{
		m_pResultLogo->Uninit();
		m_pResultLogo = NULL;
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �Q�[�����[�h�̍X�V����
//==============================================================================
void CGame::Update(void)
{
	// ���b�V���n�`�̍X�V
	if (m_pTerrain != NULL)
	{
		m_pTerrain->Update();
	}

	// �^�C�}�[�Ő؂�ւ�
	if (m_pTimer != NULL)
	{
		if (m_pTimer->GetTimerCnt()->GetNumber() <= 0)
		{
			// ���Ԑ؂�ŃQ�[���I�[�o�[
			CResult::SetEndState(CResult::ENDSTATE_GAMEOVER);
			m_pPlayer->SetGameOver(true);
			m_bGameEnd = true;
		}
	}

	// �t�H�O�|�C���^�̊J��
	if (m_pFog != NULL)
	{
		m_pFog->Update();
	}

	// �Q�[���I��
	if (m_bGameEnd == true)
	{
		EndGame();
	}
}

//==============================================================================
// �Q�[�����[�h�̕`�揈��
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
// �Q�[�����[�h�̐�������
//==============================================================================
CGame *CGame::Create()
{
	// �C���X�^���X����
	CGame *pGame;
	pGame = new CGame;

	// ������
	if (pGame != NULL)
	{
		pGame->Init();
	}

	return pGame;
}

//==============================================================================
// �X�e�[�W�I�u�W�F�N�g�ݒ�
//==============================================================================
void CGame::SetStageObject(void)
{
	// �����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();

	// ���b�V���f�[�^�̎擾
	CTextDataMeshfield *pDataMeshfield = CTextData::GetDataMeshfield();
	m_nNumMeshfield = pDataMeshfield->GetNumMesh();

	// ���I�m��
	m_pMeshField = new CMeshfield*[m_nNumMeshfield];

	for (int nCntMesh = 0; nCntMesh < m_nNumMeshfield; nCntMesh++)
	{
		// ���b�V���t�B�[���h�̐���
		m_pMeshField[nCntMesh] = CMeshfield::Create(nCntMesh);
	}

	// �t�H�O�̐���
	m_pFog = CFog::Create();

	// �f�[�^�e�L�X�g�̎擾
	CStageSelect::STAGE_SELECT select = CStageSelect::GetSelectingStage();

	// �X�e�[�W�f�[�^�̎擾
	CTextDataObject *pDataObject = CTextData::GetDataObject((CTextDataObject::STAGEINFO)select);

	if (pDataObject != NULL)
	{
		// �X�e�[�W�I�u�W�F�N�g���̎擾
		m_nNumObject = pDataObject->GetNumObject();

		// �I�u�W�F�N�g�̓��I�m��
		m_pObject = new CObject*[m_nNumObject];

		// �e�L�X�g����I�u�W�F�N�g�̐���
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
		
		// BGM�̐���
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

		// BGM�̐���
		if (m_pSound != NULL && CManager::GetBGMPlay(CSound::BGMTYPE_GAME) == true)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM003);
		}

		m_pTerrain = CTerrain::Create(CTerrainInfo::TERRAIN_TYPE::TERRAIN_OCEAN);

		m_pFog->SetFogCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
		pRenderer->SetBSColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		break;

	case CStageSelect::STAGE_SELECT_3:
		
		// BGM�̐���
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
// �Q�[���I�����o
//==============================================================================
void CGame::EndGame(void)
{
	// �N���A���o�J�E���g�̉��Z
	m_nClearDirectingCnt++;

	switch (CResult::GetEndState())
	{
	case CResult::ENDSTATE_CLEAR:		// �N���A��

		GameClear();

		break;

	case CResult::ENDSTATE_GAMEOVER:	// �Q�[���I�[�o�[��

		GameOver();

		break;
	}
}

//==============================================================================
// �Q�[���N���A
//==============================================================================
void CGame::GameClear(void)
{
	// �t�F�[�h���̎擾
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
			m_pSound->Play(CSound::SOUND_LABEL_SE_STAGECLEAR);	// �t�@���t�@�[��
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
// �Q�[���I�[�o�[
//==============================================================================
void CGame::GameOver(void)
{
	// �t�F�[�h���̎擾
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
// �Q�[�����ʂ̃��S
//==============================================================================
void CGame::CreateLogo(void)
{
	if (m_pResultLogo == NULL)
	{
		m_pResultLogo = CScene2D::Create();

		m_pResultLogo->SetPosition(LOGO_POS);						// �ʒu
		m_pResultLogo->SetSize(LOGO_SIZE);							// �T�C�Y
		m_pResultLogo->SetTex(1, 1, 0, 0, 0.0f, 0.0f);				// �e�N�X�`�����W
		m_pResultLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �F
	}
}