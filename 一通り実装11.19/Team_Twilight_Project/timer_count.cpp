//==============================================================================
//
// �^�C�}�[�J�E���g�`�揈���ktimer_count.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "number.h"
#include "texture.h"
#include "timer_count.h"

// �ÓI�����o�ϐ��錾
int CTimerCount::m_nTimerResult = 0;	// ���U���g�ֈ����p���l

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTimerCount::CTimerCount()
{
	for (int nCnt = 0; nCnt < TIMER_DIGIT_NUM; nCnt++)
	{
		// �e�i���o�[NULL��
		m_apNumber[nCnt] = NULL;
	}
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTimerCount::~CTimerCount()
{

}

//==============================================================================
// �^�C�}�[�J�E���g�̏���������
//==============================================================================
HRESULT CTimerCount::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// �^�C�}�[�ݒ�
	m_nTimer = 60;

	// �����̕\������������
	for (int nCntDigit = 0; nCntDigit < TIMER_DIGIT_NUM; nCntDigit++)
	{
		m_apNumber[nCntDigit] = CNumber::Create(
			D3DXVECTOR3(pos.x + (nCntDigit * (size.x * 2)), pos.y, 0.0f), size);
	}

	return S_OK;
}

//==============================================================================
// �^�C�}�[�J�E���g�̏I������
//==============================================================================
void CTimerCount::Uninit(void)
{
	for (int nCntDigit = 0; nCntDigit < TIMER_DIGIT_NUM; nCntDigit++)
	{
		if (m_apNumber[nCntDigit] != NULL)
		{// NULL�`�F�b�N��ɔj��
			m_apNumber[nCntDigit]->Uninit();
			m_apNumber[nCntDigit] = NULL;
		}
	}

	m_nTimerResult = m_nTimer;
}

//==============================================================================
// �^�C�}�[�J�E���g�̍X�V����
//==============================================================================
void CTimerCount::Update(void)
{
	if (m_bStartCnt == true)
	{
		// �^�C�}�[����
		TimerDecrease();
	}

	// �^�C�}�[�̐ݒ�
	SetNumber(m_nTimer);
}

//==============================================================================
// �^�C�}�[�J�E���g�̕`�揈��
//==============================================================================
void CTimerCount::Draw(void)
{

}

//==============================================================================
// �^�C�}�[�J�E���g�̐�������
//==============================================================================
CTimerCount *CTimerCount::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// �C���X�^���X����
	CTimerCount *pTimerCount;
	pTimerCount = new CTimerCount;

	// ������
	pTimerCount->Init(pos, size);

	return pTimerCount;
}

//==============================================================================
// �^�C�}�[�̌���
//==============================================================================
void CTimerCount::TimerDecrease(void)
{
	// �����J�E���g
	m_nDecereaseCnt++;

	if (m_nDecereaseCnt % 60 == 0 && m_nTimer > 0)
	{
		m_nTimer--;
	}
}

//==============================================================================
// �^�C�}�[���l�ݒ�
//==============================================================================
void CTimerCount::SetNumber(int nTimer)
{
	// �X�R�A�̐ݒ�
	m_nTimer = nTimer;

	int nData = (int)pow(10, (TIMER_DIGIT_NUM - 1));

	for (int nCnt = 0; nCnt < TIMER_DIGIT_NUM; nCnt++)
	{
		// �e���̎Z�o
		int nNumber;
		nNumber = (m_nTimer / nData) % 10;
		nData /= 10;

		// ���̐ݒ�
		m_apNumber[nCnt]->SetNumber(nNumber);
	}
}