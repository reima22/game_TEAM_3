//==============================================================================
//
// �J�n���J�E���g�_�E���`�揈���kstart_cntdown.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "game.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "start_cntdown.h"
#include "texture.h"
#include "timer.h"
#include "timer_count.h"
#include "ui.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CStartCntdown::CStartCntdown(int nPriority) : CScene(nPriority)
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CStartCntdown::~CStartCntdown()
{

}

//==============================================================================
// �J�n���J�E���g�_�E���̏���������
//==============================================================================
HRESULT CStartCntdown::Init(void)
{
	// �^�C�}�[�ݒ�
	m_nCntDown = COUNT_DOWN_NUM;

	// �t���O������
	m_bStartCntdown = false;
	m_bCntDowning = false;
	m_nDecereaseCnt = 0;

	// �|���S���̐ݒ�
	if (m_pScene2D == NULL)
	{
		m_pScene2D = CScene2D::Create();						// ����
		m_pScene2D->SetPosition(SCREEN_CENTER);					// �ʒu
		m_pScene2D->SetSize(START_CNT_SIZE);					// �T�C�Y
		m_pScene2D->SetTex(1, 1, 0, 0, 0.0f, 0.0f);				// �e�N�X�`�����W
		m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �F�̐ݒ�
	}

	return S_OK;
}

//==============================================================================
// �J�n���J�E���g�_�E���̏I������
//==============================================================================
void CStartCntdown::Uninit(void)
{
	// 2D�|���S���̔j��
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}
}

//==============================================================================
// �J�n���J�E���g�_�E���̍X�V����
//==============================================================================
void CStartCntdown::Update(void)
{
	// UI���|�C���^
	CUi *pUi = CGame::GetUi();

	// �J�E���g�_�E���J�n
	if (m_bStartCntdown == true)
	{
		if (m_nDecereaseCnt == 0)
		{
			m_pSound->Play(CSound::SOUND_LABEL_SE_CNTDOWN);			// �J�E���g�_�E����
			m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// �\��
			m_bCntDowning = true;									// �J�E���g�_�E�����J�n
		}

		// �J�E���g
		m_nDecereaseCnt++;

		// �J�E���g�_�E��
		if (m_nDecereaseCnt % CNT_ONE_SECOND == 0 && m_nDecereaseCnt != 0)
		{
			m_nCntDown--;
		}

		// �^�C�}�[�i�s�ƃQ�[���J�n
		if (m_nDecereaseCnt >= CNT_ONE_SECOND * CNTDOWN_MAX)
		{
			// �J�E���g�_�E���̊J�n
			pUi->GetTimer()->GetTimerCnt()->SetStartCnt(true);		// �X�^�[�g�J�E���g
			m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �\���̏���
			m_bCntDowning = false;
		}
	}

	// �e�N�X�`���̐ݒ�
	switch (m_nCntDown)
	{
	case 0:
		m_pScene2D->BindTexture("GO");		// �e�N�X�`���ݒ�
		break;

	case 1:
		m_pScene2D->BindTexture("ONE");		// �e�N�X�`���ݒ�
		break;

	case 2:
		m_pScene2D->BindTexture("TWO");		// �e�N�X�`���ݒ�
		break;

	case 3:
		m_pScene2D->BindTexture("THREE");	// �e�N�X�`���ݒ�
		break;
	}
}

//==============================================================================
// �J�n���J�E���g�_�E���̕`�揈��
//==============================================================================
void CStartCntdown::Draw(void)
{

}

//==============================================================================
// �J�n���J�E���g�_�E���̐�������
//==============================================================================
CStartCntdown *CStartCntdown::Create(void)
{
	// �C���X�^���X����
	CStartCntdown *pStartCntdown;
	pStartCntdown = new CStartCntdown;

	// ������
	if (pStartCntdown != NULL)
	{
		pStartCntdown->Init();
	}

	return pStartCntdown;
}