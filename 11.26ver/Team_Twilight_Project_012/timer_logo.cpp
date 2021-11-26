//==============================================================================
//
// �^�C�}�[���S�`�揈���ktimer_logo.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "number.h"
#include "texture.h"
//#include "timer_count.h"
#include "timer_logo.h"
#include "select.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTimerLogo::CTimerLogo(int nPriority) : CTimer(nPriority)
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTimerLogo::~CTimerLogo()
{

}

//==============================================================================
// �^�C�}�[���S�̏���������
//==============================================================================
HRESULT CTimerLogo::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	//CStageSelect::STAGE_SELECT select = CStageSelect::GetSelectingStage();

	// 2D�|���S���𐶐�
	m_pScene2D = CScene2D::Create();

	if (m_pScene2D != NULL)
	{
		// �ʒu�ݒ�
		m_pScene2D->SetPosition(pos);

		// �T�C�Y�ݒ�
		m_pScene2D->SetSize(size);

		// �e�N�X�`���ݒ�
		m_pScene2D->BindTexture("TIMER_LOGO");

		m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		
		m_pScene2D->SetTex(1, 1, 0, 0, 0, 0);
	}

	return S_OK;
}

//==============================================================================
// �^�C�}�[���S�̏I������
//==============================================================================
void CTimerLogo::Uninit(void)
{
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}
}

//==============================================================================
// �^�C�}�[���S�̍X�V����
//==============================================================================
void CTimerLogo::Update(void)
{

}

//==============================================================================
// �^�C�}�[���S�̕`�揈��
//==============================================================================
void CTimerLogo::Draw(void)
{

}

//==============================================================================
// �^�C�}�[���S�̐�������
//==============================================================================
CTimerLogo *CTimerLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// CNumber�̃C���X�^���X����
	CTimerLogo *pTimerLogo;
	pTimerLogo = new CTimerLogo;

	// CNumber�̏�����
	if (pTimerLogo != NULL)
	{
		pTimerLogo->Init(pos, size);
	}

	return pTimerLogo;
}