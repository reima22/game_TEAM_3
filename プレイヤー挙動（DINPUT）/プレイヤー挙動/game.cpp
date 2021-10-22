
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

//==============================================================================
// �ÓI�����o�ϐ��錾
//==============================================================================
int CGame::m_nClearDefeat;	// �N���A���錂�j��
int CGame::m_nEndInvasion;	// �N�����E��
CCharacter *CGame::m_pCharaPlayer = NULL;	// �v���C���[�L�����̃|�C���^
bool CGame::m_bGameStart;
int CGame::m_nCntDownEnd = 0;
CPlayer *CGame::m_pPlayer = NULL;
CObject **CGame::m_pObject = NULL;

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
	//CTextDataObject *pDataObject = CTextData::GetDataObject();

	//// �X�e�[�W�I�u�W�F�N�g�̔z�u
	//m_nNumObject = pDataObject->GetNumObject();

	//// �I�u�W�F�N�g���̓��I�m��
	//m_pObject = new CObject*[m_nNumObject];

	//// �I�u�W�F�N�g�̐���
	//for (int nCnt = 0; nCnt < m_nNumObject; nCnt++)
	//{
	//	m_pObject[nCnt] = 
	//		CObject::Create(
	//			pDataObject->GetPosObject(nCnt),
	//			pDataObject->GetRotObject(nCnt),
	//			pDataObject->GetTypeObject(nCnt));
	//}

	// �|�[�Y�̐���
	CPause::Create();

	// ���b�V���t�B�[���h�̐���
	CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 10, 100, 100);

	// 3D�v���C���[�̕\��
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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
	CPause::Uninit();

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


}

//==============================================================================
// �Q�[�����[�h�̕`�揈��
//==============================================================================
void CGame::Draw(void)
{
	CPause::Draw();
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
// �ʒu�̎擾
//==============================================================================
D3DXVECTOR3 CGame::GetPosition(void)
{
	D3DXVECTOR3 pos;
	return pos;
}

//==============================================================================
// �T�C�Y�̎擾
//==============================================================================
D3DXVECTOR3 CGame::GetSize(void)
{
	D3DXVECTOR3 size;
	return size;
}