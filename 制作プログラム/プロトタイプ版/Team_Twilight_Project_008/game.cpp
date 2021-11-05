
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
// �ÓI�����o�ϐ��錾
//==============================================================================
CPause *CGame::m_pPause = NULL;		// �|�[�Y�|�C���^
CPlayer *CGame::m_pPlayer = NULL;	// �v���C���[�|�C���^
CObject **CGame::m_pObject = NULL;	// �I�u�W�F�N�g�|�C���^
CTerrain *CGame::m_pTerrain = NULL;	// ���b�V���|�C���^
CTimer *CGame::m_pTimer = NULL;		// �^�C�}�[�|�C���^
CFall *CGame::m_pFall = NULL;		// �������|�C���^

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CGame::CGame()
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

	// �|�[�Y�̐���
	m_pPause = CPause::Create();

	// �r���{�[�h�̔z�u
	//CSceneBillboard::Create(VECTOR3_NULL);

	// BGM�̐���
	if (CManager::GetBGMPlay(CSound::BGMTYPE_GAME) == true)
	{ 
		//CSound::Play(CSound::SOUND_LABEL_BGM001);
	}
	
	return S_OK;
}

//==============================================================================
// �Q�[�����[�h�̏I������
//==============================================================================
void CGame::Uninit(void)
{
	// BGM�̒�~
	CSound::Stop();

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

	// �I�u�W�F�N�g�|�C���^�̊J��
	if (m_pObject != NULL)
	{
		delete[] m_pObject;
		m_pObject = NULL;
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
			// ���Ԑ؂�ŃQ�[����蒼��(�f�o�b�O�p)
			pFade->SetFade(CFade::FADE_OUT, CMode::MODE_GAME);
		}
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
	pGame->Init();

	return pGame;
}

//==============================================================================
// �X�e�[�W�I�u�W�F�N�g�ݒ�
//==============================================================================
void CGame::SetStageObject(void)
{
	// ���b�V���t�B�[���h�̐���
	//CMeshField::Create(VECTOR3_NULL, VECTOR3_NULL, 10, 10, 100, 100);

	// ���b�V���t�B�[���h
	m_pTerrain = CTerrain::Create(CTerrainInfo::TERRAIN_TYPE::TERRAIN_LAVA);

	//CMeshField::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), VECTOR3_NULL, 10, 10, 100, 100);

	// �f�[�^�e�L�X�g�̎擾
	CTextDataObject *pDataObject = CTextData::GetDataObject();

	if (pDataObject != NULL)
	{
		// �X�e�[�W�I�u�W�F�N�g�̔z�u
		m_nNumObject = pDataObject->GetNumObject();

		// �I�u�W�F�N�g���̓��I�m��
		m_pObject = new CObject*[m_nNumObject];

		// �I�u�W�F�N�g�̐���
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