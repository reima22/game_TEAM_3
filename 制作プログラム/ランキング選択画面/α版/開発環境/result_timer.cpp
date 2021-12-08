//==============================================================================
//
// ���U���g�^�C�}�[�`�揈���kresult_fallcount.cpp�l
// Author : Mare Horiai
//
//==============================================================================
//#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "sound.h"
#include "title.h"
#include "fade.h"
#include "result_timer.h"
#include "timer_count.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CResultTimer::CResultTimer(int nPriority) : CResult(nPriority)
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CResultTimer::~CResultTimer()
{
}

//==============================================================================
// ���U���g�^�C�}�[�̏���������
//==============================================================================
HRESULT CResultTimer::Init(void)
{
	// �����J�E���g�̐���
	m_pTimerCount = CTimerCount::Create(RESULT_TIMER_POS, RESULT_TIMER_SIZE);

	m_nTimer = m_pTimerCount->GetTimerNum();
	m_pTimerCount->SetNumber(m_nTimer);

	return S_OK;
}

//==============================================================================
// ���U���g�^�C�}�[�̏I������
//==============================================================================
void CResultTimer::Uninit(void)
{
	if (m_pTimerCount != NULL)
	{
		m_pTimerCount->Uninit();
		m_pTimerCount = NULL;
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// ���U���g�^�C�}�[�̍X�V����
//==============================================================================
void CResultTimer::Update(void)
{
	if (m_pTimerCount != NULL)
	{
		m_pTimerCount->SetNumber(m_nTimer);

		m_pTimerCount->Update();
	}
}

//==============================================================================
// ���U���g�^�C�}�[�̕`�揈��
//==============================================================================
void CResultTimer::Draw(void)
{
	if (m_pTimerCount != NULL)
	{
		m_pTimerCount->Draw();
	}
}

//==============================================================================
// ���U���g�^�C�}�[�̐�������
//==============================================================================
CResultTimer *CResultTimer::Create(void)
{
	// �C���X�^���X����
	CResultTimer *pResultTimer;
	pResultTimer = new CResultTimer;

	// ������
	if (pResultTimer != NULL)
	{
		pResultTimer->Init();
	}

	return pResultTimer;
}