//==============================================================================
//
// �}�l�[�W���kmanager.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "fade.h"
#include "input.h"
#include "gamepad.h"
#include "sound.h"
#include "textdata.h"
#include "camera.h"
#include "light.h"
#include "debugproc.h"
#include "collision.h"
#include "mode.h"

//==============================================================================
// �ÓI�����o�ϐ�
//==============================================================================
CRenderer *CManager::m_pRenderer = NULL;			// �����_�����O
CInputKeyboard *CManager::m_pInputKeyboard = NULL;	// �L�[�{�[�h
CGamepad *CManager::m_pGamepad = NULL;				// �Q�[���p�b�h
CFade *CManager::m_pFade = NULL;					// �t�F�[�h�|�C���^
CMode *CManager::m_pMode = NULL;					// �Q�[�����[�h�|�C���^
CSound *CManager::m_pSound = NULL;					// �T�E���h�̃|�C���^
CCamera *CManager::m_pCamera = NULL;				// �J�����|�C���^
CLight *CManager::m_pLight = NULL;					// ���C�g�̃|�C���^
CTextData *CManager::m_pTextData = NULL;			// �e�L�X�g�f�[�^�̃|�C���^
CTexture *CManager::m_pTexture = NULL;				// �e�N�X�`���|�C���^
CCollision *CManager::m_pCollision = NULL;			// �����蔻��̃|�C���^
bool CManager::m_bBGM[CSound::BGMTYPE_MAX] =
{
	false,		// �^�C�g��
	false,		// �`���[�g���A��
	false,		// �Q�[��
	false,		// �{�X��
	false,		// ���U���g
	false		// �����L���O
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
		m_pRenderer = CRenderer::Create(hWnd, bWindow);
	}

	// �f�o�b�O�\���̐���
	CDebugProc::Create();

	// �J�����̐���
	if (m_pCamera == NULL)
	{
		m_pCamera = CCamera::Create();
	}

	// ���C�g�̐���
	if (m_pLight == NULL)
	{
		m_pLight = CLight::Create();
	}

	// �t�F�[�h�̏�����
	if (m_pFade == NULL)
	{
		m_pFade = CFade::Create();
	}

	// �T�E���h����
	if (m_pSound == NULL)
	{
		m_pSound = CSound::Create(hWnd);
	}

	// �L�[�{�[�h����
	if (m_pInputKeyboard == NULL)
	{
		m_pInputKeyboard = CInputKeyboard::Create(hInstance, hWnd);
	}

	// �Q�[���p�b�h����
	if (m_pGamepad == NULL)
	{
		m_pGamepad = CGamepad::Create(hInstance, hWnd);
	}

	// �e�L�X�g�f�[�^�̓ǂݍ��݃N���X�̐���
	if (m_pTextData == NULL)
	{
		m_pTextData = CTextData::Create();
	}
	
	// �e�N�X�`���̓ǂݍ���
	if (m_pTexture == NULL)
	{
		m_pTexture = CTexture::Create();
	}

	// �Q�[�����[�h����
	if (m_pMode == NULL)
	{
		m_pMode = CMode::Create();
	}

	// �����蔻��̐���
	if (m_pCollision == NULL)
	{
		m_pCollision = CCollision::Create();
	}


	
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
		m_pInputKeyboard = NULL;
	}

	// �Q�[���p�b�h�̔j��
	if (m_pGamepad != NULL)
	{
		m_pGamepad->Uninit();
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
	if (m_pTexture != NULL)
	{
		m_pTexture->UnloadAll();
		m_pTexture = NULL;
	}

	// �J�����̊J��
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		m_pCamera = NULL;
	}

	// ���C�g�̊J��
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		m_pLight = NULL;
	}

	// �����蔻��̔j��
	if(m_pCollision != NULL)
	{
		m_pCollision = NULL;
	}

	// �S�j��
	CScene::ReleaseAll();

	// �t�F�[�h�̏I��
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		m_pFade = NULL;
	}

	// �Q�[�����[�h�̊J��
	if (m_pMode != NULL)
	{
		m_pMode = NULL;
	}

	// �|�C���^�̊J��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
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
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}

	// ���C�g�̍X�V
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}

	// �t�F�[�h�̍X�V
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void CManager::Draw(void)
{
	// �����_���[�̕`�揈��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}