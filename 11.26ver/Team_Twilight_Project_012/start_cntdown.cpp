//==============================================================================
//
// �J�n���J�E���g�_�E���`�揈���kstart_cntdown.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "start_cntdown.h"
#include "game.h"
#include "timer.h"
#include "timer_count.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CStartCntdown::CStartCntdown(int nPriority) : CScene2D(nPriority)
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
HRESULT CStartCntdown::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// �^�C�}�[�ݒ�
	m_nCntDown = 3;

	// �t���O������
	m_bStartCntdown = false;
	m_bCntDowning = false;
	m_nDecereaseCnt = 0;

	// �|���S���̐ݒ�
	if (m_pScene2D == NULL)
	{
		m_pScene2D = CScene2D::Create();						// ����
		m_pScene2D->SetPosition(pos);							// �ʒu
		m_pScene2D->SetSize(size);								// �T�C�Y
		m_pScene2D->SetTex(1, 1, 0, 0, 0, 0);					// �e�N�X�`�����W
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
	// �^�C�}�[�J�E���g
	CTimer *pTimer;
	pTimer = CGame::GetTimer();

	// �T�E���h
	m_pSound = CManager::GetSound();

	if (m_bStartCntdown == true)
	{
		if (m_nDecereaseCnt == 0)
		{
			m_pSound->Play(CSound::SOUND_LABEL_SE_CNTDOWN);
			m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_bCntDowning = true;
		}

		m_nDecereaseCnt++;

		if (m_nDecereaseCnt % CNT_ONE_SECOND == 0 && m_nDecereaseCnt != 0)
		{
			m_nCntDown--;
		}

		if (m_nDecereaseCnt >= CNT_ONE_SECOND * CNTDOWN_MAX)
		{
			// �J�E���g�_�E���̊J�n
			pTimer->GetTimerCnt()->SetStartCnt(true);
			m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_bCntDowning = false;
		}
	}

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
CStartCntdown *CStartCntdown::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// �C���X�^���X����
	CStartCntdown *pStartCntdown;
	pStartCntdown = new CStartCntdown;

	// ������
	pStartCntdown->Init(pos, size);

	return pStartCntdown;
}