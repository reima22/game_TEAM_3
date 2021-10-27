//==============================================================================
//
// �}�l�[�W���kmanager.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "manager.h"
#include "scene2D.h"
#include "renderer.h"
#include "texture.h"
#include "title.h"
#include "result.h"
#include "ranking.h"
#include "game.h"
#include "tutorial.h"
#include "fade.h"
#include "input.h"
#include "gamepad.h"
#include "sound.h"
#include "pause.h"
#include "textdata_player.h"
#include "camera.h"
#include "light.h"
#include "debugproc.h"
#include "collision.h"

//==============================================================================
// �ÓI�����o�ϐ�
//==============================================================================
CRenderer *CManager::m_pRenderer = NULL;			// �����_�����O
CInputKeyboard *CManager::m_pInputKeyboard = NULL;	// �L�[�{�[�h
CGamepad *CManager::m_pGamepad = NULL;				// �Q�[���p�b�h
CTitle *CManager::m_pTitle = NULL;					// �^�C�g�����[�h
CTutorial *CManager::m_pTutorial = NULL;			// �`���[�g���A�����[�h
CGame *CManager::m_pGame = NULL;					// �Q�[�����[�h
CResult *CManager::m_pResult = NULL;				// ���U���g���[�h
CRanking *CManager::m_pRanking = NULL;				// �����L���O���[�h
CManager::MODE CManager::m_mode = MODE_GAME;		// ���݂̃Q�[�����[�h
CSound *CManager::m_pSound = NULL;					// �T�E���h�̃|�C���^
CCamera *CManager::m_pCamera = NULL;				// �J�����|�C���^
CLight *CManager::m_pLight;							// ���C�g�̃|�C���^
CTextData *CManager::m_pTextData = NULL;			// �e�L�X�g�f�[�^�̃|�C���^
CTexture *CManager::m_pTexture = NULL;				// �e�N�X�`���|�C���^
CCollision *CManager::m_pCollision = NULL;			// �����蔻��̃|�C���^
bool CManager::m_bBGM[CSound::BGMTYPE_MAX] =
{
	true,		// �^�C�g��
	true,		// �`���[�g���A��
	false,		// �Q�[��
	true,		// �{�X��
	true,		// ���U���g
	true		// �����L���O
};		

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CManager::CManager()
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CManager::~CManager()
{
}

//==============================================================================
// ������
//==============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �C���X�^���X�Ə�����
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
		m_pRenderer->Init(hWnd, bWindow);
	}

	// �f�o�b�O�\���̐���
	CDebugProc::Create();

	// �J�����̐���
	m_pCamera = new CCamera;
	m_pCamera->Init();

	// ���C�g�̐���
	m_pLight = new CLight;
	m_pLight->Init();

	// �t�F�[�h�̏�����
	CFade::Init();

	// �T�E���h����
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	// �L�[�{�[�h����
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	// �Q�[���p�b�h����
	m_pGamepad = new CGamepad;
	m_pGamepad->Init(hInstance, hWnd);

	// �e�L�X�g�f�[�^�̓ǂݍ��݃N���X�̐���
	m_pTextData = CTextData::Create();

	// �e�N�X�`���̓ǂݍ���
	m_pTexture = new CTexture;
	m_pTexture->LoadAll();

	// �I�u�W�F�N�g����
	SetMode(m_mode);

	// �����蔻��̐���
	m_pCollision = CCollision::Create();
	
	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void CManager::Uninit(void)
{
	// �L�[�{�[�h�̔j��
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	// �Q�[���p�b�h�̔j��
	if (m_pGamepad != NULL)
	{
		m_pGamepad->Uninit();
		delete m_pGamepad;
		m_pGamepad = NULL;
	}

	// �T�E���h�I��
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		m_pSound = NULL;
	}
	
	// �e�L�X�g�f�[�^�̔j��
	if (m_pTextData != NULL)
	{
		m_pTextData->UninitAll();
		m_pTextData = NULL;
	}
	
	// �e�N�X�`���̊J��
	m_pTexture->UnloadAll();
	m_pTexture = NULL;

	// �����蔻��̔j��
	if(m_pCollision != NULL)
	{
		m_pCollision = NULL;
	}

	// �S�j��
	CScene::ReleaseAll();

	// �t�F�[�h�̏I��
	CFade::Uninit();

	// �|�C���^�̊J��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void CManager::Update(void)
{
	// �L�[�{�[�h�̍X�V
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	// �Q�[���p�b�h�̍X�V
	if (m_pGamepad != NULL)
	{
		m_pGamepad->Update();
	}

	// �����_���[�̍X�V
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	// �J�����̍X�V
	m_pCamera->Update();

	// �t�F�[�h�̍X�V
	CFade::Update();

	// �Q�[�����[�h�̎擾
	CManager::MODE mode = CManager::GetMode();
}

//==============================================================================
// �`�揈��
//==============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//==============================================================================
// �L�[�{�[�h�̎擾
//==============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//==============================================================================
// �Q�[���p�b�h�̎擾
//==============================================================================
CGamepad *CManager::GetInputGamepad(void)
{
	return m_pGamepad;
}

//==============================================================================
// ���݂̃V�[�����[�h�̐ݒ�
//==============================================================================
void CManager::SetMode(MODE mode)
{
	// ���[�h�̔j��
	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;

	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			m_pTutorial = NULL;
		}
		break;

	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;

	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;

	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pRanking->Uninit();
			m_pRanking = NULL;
		}
		break;

	default:
		break;
	}

	// �I�u�W�F�N�g�j��
	CScene::ReleaseAll();

	CScene::UpdateAll();

	// ���[�h�̐ݒ�
	m_mode = mode;

	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{
			m_pTitle = CTitle::Create();
		}
		break;

	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			m_pTutorial = CTutorial::Create();
		}
		break;

	case MODE_GAME:
		if (m_pGame == NULL)
		{
			m_pGame = CGame::Create();
		}
		break;

	case MODE_RESULT:
		if (m_pResult == NULL)
		{
			m_pResult = CResult::Create();
		}
		break;

	case MODE_RANKING:
		if (m_pRanking == NULL)
		{
			m_pRanking = CRanking::Create();
		}
		break;

	default:
		break;
	}
}