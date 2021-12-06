
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
//#include "textdata_system.h"
//#include "result_logo.h"
//#include "sceneX.h"
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

//==============================================================================
// �ÓI�����o�ϐ��錾
//==============================================================================
CPause *CGame::m_pPause = NULL;					// �|�[�Y�|�C���^
CPlayer *CGame::m_pPlayer = NULL;				// �v���C���[�|�C���^
CObject **CGame::m_pObject = {};				// �I�u�W�F�N�g�|�C���^
CTerrain *CGame::m_pTerrain = NULL;				// ���b�V���|�C���^
CTimer *CGame::m_pTimer = NULL;					// �^�C�}�[�|�C���^
CFall *CGame::m_pFall = NULL;					// �������|�C���^
CMeshfield **CGame::m_pMeshField = {};			// ���b�V���t�B�[���h�N���X
CStartCntdown *CGame::m_pStartCntdown = NULL;	// �J�n���J�E���g�_�E���|�C���^
CFog *CGame::m_pFog = NULL;						// �t�H�O���ʃN���X

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CGame::CGame(int nPriority) : CMode(nPriority)
{
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
	m_pPlayer = CPlayer::Create();

	// �^�C�}�[�̔z�u
	m_pTimer = CTimer::Create();

	// �������J�E���g�̔z�u
	m_pFall = CFall::Create();

	// �J�n���J�E���g�_�E���̐���
	m_pStartCntdown = CStartCntdown::Create(SCREEN_CENTER, START_CNT_SIZE);

	// �|�[�Y�̐���
	m_pPause = CPause::Create();

	// �r���{�[�h�̔z�u
	//CSceneBillboard::Create(VECTOR3_NULL);
	
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
		delete[] m_pObject;
		m_pObject = NULL;
	}

	// ���b�V���t�B�[���h�|�C���^�̊J��
	if (m_pMeshField != NULL)
	{
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

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �Q�[�����[�h�̍X�V����
//==============================================================================
void CGame::Update(void)
{
	// �t�F�[�h���̎擾
	CFade *pFade;
	pFade = CManager::GetFade();

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
			pFade->SetFade(CFade::FADE_OUT, CMode::MODE_RESULT);
		}
	}

	// �t�H�O�|�C���^�̊J��
	if (m_pFog != NULL)
	{
		m_pFog->Update();
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
			CRenderer::SetBSColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
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
		CRenderer::SetBSColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		break;

	case CStageSelect::STAGE_SELECT_3:
		
		// BGM�̐���
		if (m_pSound != NULL && CManager::GetBGMPlay(CSound::BGMTYPE_GAME) == true)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM004);
		}

		m_pTerrain = CTerrain::Create(CTerrainInfo::TERRAIN_TYPE::TERRAIN_LAVA);

		break;
	}
}