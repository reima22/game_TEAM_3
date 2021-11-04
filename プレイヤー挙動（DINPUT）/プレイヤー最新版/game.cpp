
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

//==============================================================================
// �ÓI�����o�ϐ��錾
//==============================================================================
int CGame::m_nClearDefeat;	// �N���A���錂�j��
int CGame::m_nEndInvasion;	// �N�����E��
bool CGame::m_bGameStart;
int CGame::m_nCntDownEnd = 0;
CPause *CGame::m_pPause = NULL;
CPlayer *CGame::m_pPlayer = NULL;
CObject **CGame::m_pObject = NULL;
CTerrain *CGame::m_pTerrain = NULL;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CGame::CGame()
{
	m_nCntDownEnd = 0;
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
	// �|�[�Y�̐���
	m_pPause = CPause::Create();

	// ���b�V���t�B�[���h�̐���
	//CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 10, 100, 100);

	// ���b�V���t�B�[���h
	m_pTerrain = CTerrain::Create(CTerrainInfo::TERRAIN_TYPE::TERRAIN_LAVA);
	//CMeshField::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 10, 100, 100);

	// 3D�v���C���[�̕\��
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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
						pDataObject->GetShadowDepth(nCnt)));
		}
	}

	// �r���{�[�h�̔z�u
	//CSceneBillboard::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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
		m_pPause = NULL;
	}
	
	// �v���C���[�̏I��
	if (m_pPlayer != NULL)
	{
		m_pPlayer = NULL;
	}

	// �I�u�W�F�N�g�|�C���^�̊J��
	if (m_pObject != NULL)
	{
		delete m_pObject;
		m_pObject = NULL;
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �Q�[�����[�h�̍X�V����
//==============================================================================
void CGame::Update(void)
{
	m_pTerrain->Update();
}

//==============================================================================
// �Q�[�����[�h�̕`�揈��
//==============================================================================
void CGame::Draw(void)
{
	m_pTerrain->Draw();
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