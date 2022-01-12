//==============================================================================
//
// �`�F�b�N�|�C���g���S�`�揈���kcheckpoint_logo.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "checkpoint_logo.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CCheckpointLogo::CCheckpointLogo(int nPriority) : CScene2D(nPriority)
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CCheckpointLogo::~CCheckpointLogo()
{
}

//==============================================================================
// �^�C�}�[�̏���������
//==============================================================================
HRESULT CCheckpointLogo::Init(void)
{
	// ������
	if (m_pScene2D == NULL)
	{
		m_pScene2D = new CScene2D;
		m_pScene2D->Init();
		m_pos = CHECK_POS;
		m_pScene2D->SetPosition(m_pos);
		m_pScene2D->SetSize(CHECK_SIZE);
		m_pScene2D->BindTexture("CHECKPOINT_LOGO");
		m_pScene2D->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	}

	m_logoMove = LOGOMOVE_NONE;

	return S_OK;
}

//==============================================================================
//�^�C�}�[�̏I������
//==============================================================================
void CCheckpointLogo::Uninit(void)
{
	// �|���S���̔j��
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	Release();
}

//==============================================================================
// �^�C�}�[�̍X�V����
//==============================================================================
void CCheckpointLogo::Update(void)
{
	// �ړ�����
	MoveLogo();

	if (m_pScene2D != NULL)
	{
		m_pScene2D->SetPosition(m_pos);
	}
}

//==============================================================================
// �^�C�}�[�̕`�揈��
//==============================================================================
void CCheckpointLogo::Draw(void)
{

}

//==============================================================================
// �^�C�}�[�̐�������
//==============================================================================
CCheckpointLogo *CCheckpointLogo::Create(void)
{
	// �C���X�^���X����
	CCheckpointLogo *pCheckpointLogo;
	pCheckpointLogo = new CCheckpointLogo;

	// ������
	if (pCheckpointLogo != NULL)
	{
		pCheckpointLogo->Init();
	}

	return pCheckpointLogo;
}

//==============================================================================
// �`�F�b�N�|�C���g���S�ړ�����
//==============================================================================
void CCheckpointLogo::MoveLogo(void)
{
	switch (m_logoMove)
	{
	case LOGOMOVE_NONE:
		m_pos = CHECK_POS;
		break;

	case LOGOMOVE_START:
		m_pos.x -= 20.0f;
		if (m_pos.x <= SCREEN_CENTER.x)
		{
			m_logoMove = LOGOMOVE_STOP;
			m_pos = SCREEN_CENTER;
		}
		break;

	case LOGOMOVE_STOP:
		m_nCntStop++;
		
		if (m_nCntStop > CNT_ONE_SECOND)
		{
			m_logoMove = LOGOMOVE_RESTART;
			m_nCntStop = 0;
		}

		break;

	case LOGOMOVE_RESTART:
		m_pos.x -= 20.0f;

		if (m_pos.x < -CHECK_SIZE.x)
		{
			m_logoMove = LOGOMOVE_END;
		}

		break;

	case LOGOMOVE_END:

		m_logoMove = LOGOMOVE_NONE;

		break;
	}
}