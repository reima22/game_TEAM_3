//==============================================================================
//
// �������J�E���g�`�揈���kfall_count.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "number.h"
#include "texture.h"
#include "fall_count.h"
#include "select.h"

// �ÓI�����o�ϐ�
int CFallCount::m_nFallResult = 0;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CFallCount::CFallCount()
{
	for (int nCnt = 0; nCnt < FALL_DIGIT_NUM; nCnt++)
	{
		// �e�i���o�[�̏�����
		m_apNumber[nCnt] = NULL;
	}
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CFallCount::~CFallCount()
{

}

//==============================================================================
// �������J�E���g�̏���������
//==============================================================================
HRESULT CFallCount::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CStageSelect::STAGE_SELECT select = CStageSelect::GetSelectingStage();

	// �������ݒ�
	m_nFall = 0;

	for (int nCntDigit = 0; nCntDigit < FALL_DIGIT_NUM; nCntDigit++)
	{
		m_apNumber[nCntDigit] = CNumber::Create(
			D3DXVECTOR3(pos.x + (nCntDigit * (size.x * 2)), pos.y, 0.0f), size);

		m_apNumber[nCntDigit]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	return S_OK;
}

//==============================================================================
// �������J�E���g�̏I������
//==============================================================================
void CFallCount::Uninit(void)
{
	for (int nCntDigit = 0; nCntDigit < FALL_DIGIT_NUM; nCntDigit++)
	{
		if (m_apNumber[nCntDigit] != NULL)
		{// NULL�`�F�b�N��ɔj��
			m_apNumber[nCntDigit]->Uninit();
			m_apNumber[nCntDigit] = NULL;
		}
	}

	m_nFallResult = m_nFall;
}

//==============================================================================
// �������J�E���g�̍X�V����
//==============================================================================
void CFallCount::Update(void)
{
	SetNumber(m_nFall);
}

//==============================================================================
// �������J�E���g�̕`�揈��
//==============================================================================
void CFallCount::Draw(void)
{
	for (int nCntDigit = 0; nCntDigit < FALL_DIGIT_NUM; nCntDigit++)
	{
		if (m_apNumber[nCntDigit] != NULL)
		{// NULL�`�F�b�N��ɕ`��
			m_apNumber[nCntDigit]->Draw();
		}
	}
}

//==============================================================================
// �������J�E���g�̐�������
//==============================================================================
CFallCount *CFallCount::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// ���[�J���ϐ��錾
	CFallCount *pFallCount;
	pFallCount = new CFallCount;

	// ������
	if (pFallCount != NULL)
	{
		pFallCount->Init(pos, size);
	}

	return pFallCount;
}

//==============================================================================
// ���l�ݒ�
//==============================================================================
void CFallCount::SetNumber(int nFall)
{
	// ���l�ݒ�
	m_nFall = nFall;

	int nData = (int)pow(10, (FALL_DIGIT_NUM - 1));

	for (int nCnt = 0; nCnt < FALL_DIGIT_NUM; nCnt++)
	{
		// �e���̎Z�o
		int nNumber;
		nNumber = (m_nFall / nData) % 10;
		nData /= 10;

		// ���̐ݒ�
		m_apNumber[nCnt]->SetNumber(nNumber);
	}
}