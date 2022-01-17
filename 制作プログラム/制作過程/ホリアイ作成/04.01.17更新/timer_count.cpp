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
#include "timer_count.h"
#include "game.h"
#include "ui.h"
#include "timeralert_logo.h"

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
	m_nTimer = TIMER_START;

	// �����̕\������������
	for (int nCntDigit = 0; nCntDigit < TIMER_DIGIT_NUM; nCntDigit++)
	{
		// �i���o�[�N���X�̐���
		m_apNumber[nCntDigit] = CNumber::Create(
			D3DXVECTOR3(pos.x + (nCntDigit * (size.x * 2)), pos.y, 0.0f), size);

		m_apNumber[nCntDigit]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
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

	// ���ʃ^�C�}�[�̍X�V
	m_nTimerResult = m_nTimer;
}

//==============================================================================
// �^�C�}�[�J�E���g�̍X�V����
//==============================================================================
void CTimerCount::Update(void)
{
	if (m_bStartCnt == true && CGame::GetGameEnd() == false)
	{
		// �^�C�}�[����
		TimerDecrease();
	}

	// �^�C�}�[�̐ݒ�
	SetNumber(m_nTimer);

	// �����̍X�V
	for (int nCnt = 0; nCnt < TIMER_DIGIT_NUM; nCnt++)
	{
		m_apNumber[nCnt]->Update();
	}
}

//==============================================================================
// �^�C�}�[�J�E���g�̕`�揈��
//==============================================================================
void CTimerCount::Draw(void)
{
	for (int nCntDigit = 0; nCntDigit < TIMER_DIGIT_NUM; nCntDigit++)
	{
		if (m_apNumber[nCntDigit] != NULL)
		{// NULL�`�F�b�N��ɕ`��
			m_apNumber[nCntDigit]->Draw();
		}
	}
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
	if (pTimerCount != NULL)
	{
		pTimerCount->Init(pos, size);
	}

	return pTimerCount;
}

//==============================================================================
// �^�C�}�[�̌���
//==============================================================================
void CTimerCount::TimerDecrease(void)
{
	// �����J�E���g
	m_nDecereaseCnt++;

	if (m_nDecereaseCnt % CNT_ONE_SECOND == 0 && m_nTimer > 0)
	{
		m_nTimer--;
	}

	CUi *pUi = CGame::GetUi();

	// �c�莞��3���Ōx��
	if (m_nTimer == TIMER_START * 30 / 100)
	{
		m_pSound->Play(CSound::SOUND_LABEL_SE_TIMEWARNING);
		
		pUi->GetAlertLogo()->MoveTypeNext();

		for (int nCnt = 0; nCnt < TIMER_DIGIT_NUM; nCnt++)
		{
			m_apNumber[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}
	}

	// �����F�̕ω�
	if (m_nTimer == (TIMER_START * 30 / 100 - 3))
	{
		for (int nCnt = 0; nCnt < TIMER_DIGIT_NUM; nCnt++)
		{
			m_apNumber[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}

//==============================================================================
// �^�C�}�[���l�ݒ�
//==============================================================================
void CTimerCount::SetNumber(int nTimer)
{
	// �^�C�}�[�̐ݒ�
	m_nTimer = nTimer;

	// ���[�J���ϐ��錾
	int nData = (int)pow(10, (TIMER_DIGIT_NUM - 1));

	// �e���̎Z�o
	for (int nCnt = 0; nCnt < TIMER_DIGIT_NUM; nCnt++)
	{
		int nNumber;
		nNumber = (m_nTimer / nData) % 10;
		nData /= 10;

		// ���̐ݒ�
		m_apNumber[nCnt]->SetNumber(nNumber);
	}
}