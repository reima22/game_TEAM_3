//==============================================================================
//
// ���U���g�̃{�[�i�X�J�E���g�`�揈���kresult_bonuscount.cpp�l
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
#include "bonus_count.h"
#include "result_bonuscount.h"
#include "fall_count.h"


//==============================================================================
// �R���X�g���N�^
//==============================================================================
CResultBonus::CResultBonus(int nPriority) : CResult(nPriority)
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CResultBonus::~CResultBonus()
{
}

//==============================================================================
// ���U���g�̗����J�E���g�̏���������
//==============================================================================
HRESULT CResultBonus::Init(void)
{
	// �����J�E���g�̐���
	m_pBonusCount = CBonusCount::Create(RESULT_BONUS_POS, RESULT_BONUS_SIZE);

	m_nBonus = m_pBonusCount->GetBonusNum();
	m_pBonusCount->SetNumber(m_nBonus);

	return S_OK;
}

//==============================================================================
// ���U���g�̗����J�E���g�̏I������
//==============================================================================
void CResultBonus::Uninit(void)
{
	if (m_pBonusCount != NULL)
	{
		m_pBonusCount->Uninit();
		m_pBonusCount = NULL;
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// ���U���g�̗����J�E���g�̍X�V����
//==============================================================================
void CResultBonus::Update(void)
{
	if (m_pBonusCount != NULL)
	{
		m_pBonusCount->SetNumber(m_nBonus);

		m_pBonusCount->Update();
	}
}

//==============================================================================
// ���U���g�̃{�[�i�X�J�E���g�̕`�揈��
//==============================================================================
void CResultBonus::Draw(void)
{
	if (m_pBonusCount != NULL)
	{
		m_pBonusCount->Draw();
	}
}

//==============================================================================
// ���U���g�̃{�[�i�X�J�E���g�̐�������
//==============================================================================
CResultBonus *CResultBonus::Create(void)
{
	// �C���X�^���X����
	CResultBonus *pResultBonus;
	pResultBonus = new CResultBonus;

	// ������
	if (pResultBonus != NULL)
	{
		pResultBonus->Init();
	}

	return pResultBonus;
}