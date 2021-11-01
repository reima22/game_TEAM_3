//=============================================================================
//
// �}�l�[�W�� [manager.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "Manager.h"
#include "Camera.h"
#include "Light.h"
#include "Renderer.h"
#include "Resource.h"
#include "GameScene.h"
#include "select.h"
#include "Input.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CRenderer *CManager::m_pRenderer = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputMouse *CManager::m_pInputMouse = NULL;
CResourceManager *CManager::m_pResourceManager = NULL;
CGameScene *CManager::m_pGameScene = NULL;
CStageSelect *CManager::m_pStage = NULL;

//*****************************************************************************
// �}�l�[�W���N���X
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �����_���̐����A������
	m_pRenderer = new CRenderer;
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return E_FAIL;
	}

	// �J�����̐����A������
	m_pCamera = new CCamera;
	if (m_pCamera != NULL)
	{
		m_pCamera->Init();
	}

	// ���C�g�̐����A������
	m_pLight = new CLight;
	if (m_pLight != NULL)
	{
		m_pLight->Init();
	}

	// �L�[�{�[�h�N���X�̐����A������
	m_pInputKeyboard = new CInputKeyboard;
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// �}�E�X�N���X�̐����A������
	m_pInputMouse = new CInputMouse;
	if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	// ���\�[�X�}�l�[�W���̐����A������
	m_pResourceManager = new CResourceManager;
	if (FAILED(m_pResourceManager->Init()))
	{
		return E_FAIL;
	}

	// �Ƃ肠�����Q�[���V�[���u���Ƃ�
	//m_pGameScene = new CGameScene;
	//if (FAILED(m_pGameScene->Init(VECTOR3_ZERO, VECTOR3_ZERO, VECTOR3_ZERO)))
	//{
	//	return E_FAIL;
	//}

	m_pStage = new CStageSelect;
	if (FAILED(m_pStage->Init(VECTOR3_ZERO, VECTOR3_ZERO, VECTOR3_ZERO))) {
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	// �I�u�W�F�N�g�����ׂĔj��
	CScene::ReleaseAll();

	// ���\�[�X�}�l�[�W���j��
	if (m_pResourceManager != NULL)
	{
		m_pResourceManager->Uninit();
		delete m_pResourceManager;
		m_pResourceManager = NULL;
	}

	// �}�E�X�̔j��
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	// �L�[�{�[�h�̔j��
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	// ���C�g�̔j��
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	// �J�����̔j��
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	// �����_���̔j��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	// �J�����̍X�V�Ăяo��
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}

	// �L�[�{�[�h�̍X�V�Ăяo��
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	// �}�E�X�̍X�V�Ăяo��
	if (m_pInputMouse != NULL)
	{
		m_pInputMouse->Update();
	}

	// ���C�g�̍X�V�Ăяo��
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}

	// �����_���̍X�V�Ăяo��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	// �����_���̕`��Ăяo��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}