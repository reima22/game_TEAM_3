//==============================================================================
//
// UI�̕`�揈���kui.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "ui.h"
#include "timer.h"
#include "fall.h"
#include "bonus.h"
#include "start_cntdown.h"
#include "checkpoint_logo.h"
#include "timeralert_logo.h"

//==============================================================================
// �ÓI�����o�ϐ�
//==============================================================================
CTimer *CUi::m_pTimer = NULL;
CFall *CUi::m_pFall = NULL;
CBonus *CUi::m_pBonus = NULL;
CStartCntdown *CUi::m_pStartCntdown = NULL;
CCheckpointLogo *CUi::m_pCheckPointLogo = NULL;
CAlertLogo * CUi::m_pAlertLogo = NULL;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CUi::CUi(int nPriority) : CScene(nPriority)
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CUi::~CUi()
{
}

//==============================================================================
// �^�C�}�[�̏���������
//==============================================================================
HRESULT CUi::Init(void)
{
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

	// �J�n���J�E���g�_�E���̐���
	if (m_pStartCntdown == NULL)
	{
		m_pStartCntdown = CStartCntdown::Create();
	}

	// �`�F�b�N�|�C���g���S
	if (m_pCheckPointLogo == NULL)
	{
		m_pCheckPointLogo = CCheckpointLogo::Create();
	}

	// �^�C�}�[�A���[�g���S
	if (m_pAlertLogo == NULL)
	{
		m_pAlertLogo = CAlertLogo::Create();
	}

	return S_OK;
}

//==============================================================================
// UI�̏I������
//==============================================================================
void CUi::Uninit(void)
{
	// �^�C�}�[�J�E���g
	if (m_pTimer != NULL)
	{
		m_pTimer->Uninit();
		m_pTimer = NULL;
	}

	// �������J�E���g
	if (m_pFall != NULL)
	{
		m_pFall->Uninit();
		m_pFall = NULL;
	}

	// �{�[�i�X�J�E���g
	if (m_pBonus != NULL)
	{
		m_pBonus->Uninit();
		m_pBonus = NULL;
	}

	// �X�^�[�g���J�E���g�_�E��
	if (m_pStartCntdown != NULL)
	{
		m_pStartCntdown->Uninit();
		m_pStartCntdown = NULL;
	}

	// �`�F�b�N�|�C���g���S
	if (m_pCheckPointLogo != NULL)
	{
		m_pCheckPointLogo->Uninit();
		m_pCheckPointLogo = NULL;
	}

	// �^�C�}�[�A���[�g���S
	if (m_pAlertLogo != NULL)
	{
		m_pAlertLogo->Uninit();
		m_pAlertLogo = NULL;
	}

	Release();
}

//==============================================================================
// UI�̍X�V����
//==============================================================================
void CUi::Update(void)
{

}

//==============================================================================
// UI�̕`�揈��
//==============================================================================
void CUi::Draw(void)
{

}

//==============================================================================
// UI�̐�������
//==============================================================================
CUi *CUi::Create(void)
{
	// �C���X�^���X����
	CUi *pUi;
	pUi = new CUi;

	// ������
	if (pUi != NULL)
	{
		pUi->Init();
	}

	return pUi;
}