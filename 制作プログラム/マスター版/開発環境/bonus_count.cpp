//==============================================================================
//
// �{�[�i�X�J�E���g�`�揈���kbonus_count.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "number.h"
#include "texture.h"
#include "bonus_count.h"
#include "select.h"
#include "mode.h"

// �ÓI�����o�ϐ�
int CBonusCount::m_nSaveBonus = 0;
int CBonusCount::m_nBonusResult = 0;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CBonusCount::CBonusCount()
{
	for (int nCnt = 0; nCnt < BONUS_DIGIT_NUM; nCnt++)
	{
		// �e�i���o�[�̏�����
		m_apNumber[nCnt] = NULL;
	}
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CBonusCount::~CBonusCount()
{

}

//==============================================================================
// �������J�E���g�̏���������
//==============================================================================
HRESULT CBonusCount::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CStageSelect::STAGE_SELECT select = CStageSelect::GetSelectingStage();

	// �������ݒ�
	m_nBonus = 0;

	for (int nCntDigit = 0; nCntDigit < BONUS_DIGIT_NUM; nCntDigit++)
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
void CBonusCount::Uninit(void)
{
	for (int nCntDigit = 0; nCntDigit < BONUS_DIGIT_NUM; nCntDigit++)
	{
		if (m_apNumber[nCntDigit] != NULL)
		{// NULL�`�F�b�N��ɔj��
			m_apNumber[nCntDigit]->Uninit();
			m_apNumber[nCntDigit] = NULL;
		}
	}

	m_nBonusResult = m_nBonus;
}

//==============================================================================
// �������J�E���g�̍X�V����
//==============================================================================
void CBonusCount::Update(void)
{
	SetNumber(m_nBonus);

	// �Q�[�����[�h�Ɍ���
	if (CManager::GetModePoint()->GetMode() == CMode::MODE_GAME)
	{
		SizeReturn();
	}

	for (int nCntNum = 0; nCntNum < BONUS_DIGIT_NUM; nCntNum++)
	{
		m_apNumber[nCntNum]->Update();
	}
}

//==============================================================================
// �������J�E���g�̕`�揈��
//==============================================================================
void CBonusCount::Draw(void)
{
	for (int nCntDigit = 0; nCntDigit < BONUS_DIGIT_NUM; nCntDigit++)
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
CBonusCount *CBonusCount::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// ���[�J���ϐ��錾
	CBonusCount *pBonusCount;
	pBonusCount = new CBonusCount;

	// ������
	if (pBonusCount != NULL)
	{
		pBonusCount->Init(pos, size);
	}

	return pBonusCount;
}

//==============================================================================
// ���l�ݒ�
//==============================================================================
void CBonusCount::SetNumber(int nBonus)
{
	// ���l�ݒ�
	m_nBonus = nBonus;

	int nData = (int)pow(10, (BONUS_DIGIT_NUM - 1));

	for (int nCnt = 0; nCnt < BONUS_DIGIT_NUM; nCnt++)
	{
		// �e���̎Z�o
		int nNumber;
		nNumber = (m_nBonus / nData) % 10;
		nData /= 10;

		// ���̐ݒ�
		m_apNumber[nCnt]->SetNumber(nNumber);
	}
}

//==============================================================================
// �{�[�i�X�J�E���g����
//==============================================================================
void CBonusCount::AddBonus(int nAdd)
{
	// ���Z
	m_nBonus += nAdd;

	// �T�C�Y�g��
	for (int nCnt = 0; nCnt < BONUS_DIGIT_NUM; nCnt++)
	{
		D3DXVECTOR2 size = m_apNumber[nCnt]->GetSize();

		size = BONUS_COUNT_SIZE + D3DXVECTOR2(20.0f, 20.0f);

		m_apNumber[nCnt]->SetSize(size);
		m_apNumber[nCnt]->SetCol(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	}
}

//==============================================================================
// �����T�C�Y��߂�
//==============================================================================
void CBonusCount::SizeReturn(void)
{
	for (int nCnt = 0; nCnt < BONUS_DIGIT_NUM; nCnt++)
	{
		D3DXVECTOR2 size = m_apNumber[nCnt]->GetSize();

		if (size.x > BONUS_COUNT_SIZE.x)
		{
			size -= D3DXVECTOR2(0.5f, 0.5f);

			m_apNumber[nCnt]->SetSize(size);
		}
		else
		{
			m_apNumber[nCnt]->SetSize(BONUS_COUNT_SIZE);
			m_apNumber[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0, 1.0f));
		}
	}
}