//==============================================================================
//
// �`�F�b�N�|�C���g���S�`�揈���kcheckpoint_logo.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "checkpoint_logo.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CCheckpointLogo::CCheckpointLogo(int nPriority) : CScene(nPriority)
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CCheckpointLogo::~CCheckpointLogo()
{
}

//==============================================================================
// �`�F�b�N�|�C���g���S�̏���������
//==============================================================================
HRESULT CCheckpointLogo::Init(void)
{
	// ������
	if (m_pScene2D == NULL)
	{
		m_pScene2D = CScene2D::Create();				// ��������
		m_pScene2D->SetPosition(CHECK_POS);				// �ʒu�̐ݒ�
		m_pScene2D->SetSize(CHECK_SIZE);				// �T�C�Y�̐ݒ�
		m_pScene2D->BindTexture("CHECKPOINT_LOGO");		// �e�N�X�`���̐ݒ�
		m_pScene2D->SetTex(1, 1, 0, 0, 0.0f, 0.0f);		// �e�N�X�`���̕����ݒ�
	}

	m_logoMove = LOGOMOVE_NONE;							// �ړ����@

	return S_OK;
}

//==============================================================================
// �`�F�b�N�|�C���g���S�̏I������
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
// �`�F�b�N�|�C���g���S�̍X�V����
//==============================================================================
void CCheckpointLogo::Update(void)
{
	// �ړ�����
	MoveLogo();
}

//==============================================================================
// �`�F�b�N�|�C���g���S�̕`�揈��
//==============================================================================
void CCheckpointLogo::Draw(void)
{

}

//==============================================================================
// �`�F�b�N�|�C���g���S�̐�������
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
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos;	// �ʒu

	// �ʒu�̎擾
	if (m_pScene2D != NULL)
	{
		pos = m_pScene2D->GetPosition();
	}

	// ���S�̈ړ����@
	switch (m_logoMove)
	{
	case LOGOMOVE_NONE:

		pos = CHECK_POS;		// �����ʒu
		
		break;

	case LOGOMOVE_START:

		pos.x -= CHECK_MOVE;	// �ړ�
		
		// �����Œ�~
		if (pos.x <= SCREEN_CENTER.x)
		{
			m_logoMove = LOGOMOVE_STOP;
			pos = SCREEN_CENTER;
		}

		break;

	case LOGOMOVE_STOP:

		m_nCntStop++;	// ��~���J�E���g���Z
		
		if (m_nCntStop > CNT_ONE_SECOND)
		{
			m_logoMove = LOGOMOVE_RESTART;	// �ړ��ĊJ��
			m_nCntStop = 0;					// �J�E���g������
		}

		break;

	case LOGOMOVE_RESTART:

		pos.x -= CHECK_MOVE;			// �ړ��ĊJ

		if (pos.x < -CHECK_SIZE.x)
		{
			m_logoMove = LOGOMOVE_END;	// �����I��
		}

		break;

	case LOGOMOVE_END:

		m_logoMove = LOGOMOVE_NONE;		// �����ʒu�֖߂�

		break;
	}

	// �ʒu�̐ݒ�
	if (m_pScene2D != NULL)
	{
		m_pScene2D->SetPosition(pos);
	}
}