//==============================================================================
//
// �^�C�}�[�����ktimer.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
//#include "number.h"
//#include "texture.h"
#include "timer.h"
#include "timer_count.h"
#include "timer_logo.h"
#include "ui_base.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTimer::CTimer(int nPriority) : CScene(nPriority)
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTimer::~CTimer()
{
}

//==============================================================================
// �^�C�}�[�̏���������
//==============================================================================
HRESULT CTimer::Init(void)
{
	// �^�C�}�[�֘A�̐���
	m_pUiBase = CUiBase::Create(TIMER_UIBASE_POS, TIMER_UIBASE_SIZE, "BLOCK_TEX");

	m_pTimerCount = CTimerCount::Create(TIMER_COUNT_POS, TIMER_COUNT_SIZE);

	m_pTimerLogo = CTimerLogo::Create(TIMER_LOGO_POS, TIMER_LOGO_SIZE);

	return S_OK;
}

//==============================================================================
//�^�C�}�[�̏I������
//==============================================================================
void CTimer::Uninit(void)
{
	// UI�x�[�X�̔j��
	if (m_pUiBase != NULL)
	{
		m_pUiBase->Uninit();
		m_pUiBase = NULL;
	}

	// �J�E���g�̔j��
	if (m_pTimerCount != NULL)
	{
		m_pTimerCount->Uninit();
		m_pTimerCount = NULL;
	}

	// ���S�̔j��
	if (m_pTimerLogo != NULL)
	{
		m_pTimerLogo->Uninit();
		m_pTimerLogo = NULL;
	}
}

//==============================================================================
// �^�C�}�[�̍X�V����
//==============================================================================
void CTimer::Update(void)
{

}

//==============================================================================
// �^�C�}�[�̕`�揈��
//==============================================================================
void CTimer::Draw(void)
{

}

//==============================================================================
// �^�C�}�[�̐�������
//==============================================================================
CTimer *CTimer::Create(void)
{
	// CNumber�̃C���X�^���X����
	CTimer *pTimer;
	pTimer = new CTimer;

	// CNumber�̏�����
	if (pTimer != NULL)
	{
		pTimer->Init();
	}

	return pTimer;
}