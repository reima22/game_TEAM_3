//==============================================================================
//
// ���U���g�̗����J�E���g�`�揈���kresult_fallcount.cpp�l
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
#include "result_fallcount.h"
#include "fall_count.h"


//==============================================================================
// �R���X�g���N�^
//==============================================================================
CResultFallCount::CResultFallCount(int nPriority) : CResult(nPriority)
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CResultFallCount::~CResultFallCount()
{
}

//==============================================================================
// ���U���g�̗����J�E���g�̏���������
//==============================================================================
HRESULT CResultFallCount::Init(void)
{
	// �����J�E���g�̐���
	m_pFallCount = CFallCount::Create(RESULT_FC_POS, RESULT_FC_SIZE);

	m_nFall = m_pFallCount->GetFallNum();
	m_pFallCount->SetNumber(m_nFall);

	return S_OK;
}

//==============================================================================
// ���U���g�̗����J�E���g�̏I������
//==============================================================================
void CResultFallCount::Uninit(void)
{
	if (m_pFallCount != NULL)
	{
		m_pFallCount->Uninit();
		m_pFallCount = NULL;
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// ���U���g�̗����J�E���g�̍X�V����
//==============================================================================
void CResultFallCount::Update(void)
{
	if (m_pFallCount != NULL)
	{
		m_pFallCount->SetNumber(m_nFall);

		m_pFallCount->Update();
	}
}

//==============================================================================
// ���U���g�̗����J�E���g�̕`�揈��
//==============================================================================
void CResultFallCount::Draw(void)
{
	if (m_pFallCount != NULL)
	{
		m_pFallCount->Draw();
	}
}

//==============================================================================
// ���U���g�̗����J�E���g�̐�������
//==============================================================================
CResultFallCount *CResultFallCount::Create(void)
{
	// �C���X�^���X����
	CResultFallCount *pResultFallCount;
	pResultFallCount = new CResultFallCount;

	// ������
	pResultFallCount->Init();

	return pResultFallCount;
}