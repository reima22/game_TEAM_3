//==============================================================================
//
// �^�C�}�[�A���[�g���S�`�揈���ktimeralert_logo.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "timeralert_logo.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CAlertLogo::CAlertLogo(int nPriority) : CScene2D(nPriority)
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CAlertLogo::~CAlertLogo()
{
}

//==============================================================================
// �^�C�}�[�̏���������
//==============================================================================
HRESULT CAlertLogo::Init(void)
{
	// ������
	if (m_pScene2D == NULL)
	{
		m_pScene2D = new CScene2D;
		m_pScene2D->Init();
		m_pos = ALERT_POS;
		m_pScene2D->SetPosition(m_pos);
		m_pScene2D->SetSize(ALERT_SIZE);
		m_pScene2D->BindTexture("TIMERALERT_LOGO");
		m_pScene2D->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	}

	m_alertLogoMove = ALERTLOGOMOVE_NONE;

	return S_OK;
}

//==============================================================================
//�^�C�}�[�̏I������
//==============================================================================
void CAlertLogo::Uninit(void)
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
void CAlertLogo::Update(void)
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
void CAlertLogo::Draw(void)
{

}

//==============================================================================
// �^�C�}�[�̐�������
//==============================================================================
CAlertLogo *CAlertLogo::Create(void)
{
	// �C���X�^���X����
	CAlertLogo *pAlertLogo;
	pAlertLogo = new CAlertLogo;

	// ������
	if (pAlertLogo != NULL)
	{
		pAlertLogo->Init();
	}

	return pAlertLogo;
}

//==============================================================================
// �`�F�b�N�|�C���g���S�ړ�����
//==============================================================================
void CAlertLogo::MoveLogo(void)
{
	switch (m_alertLogoMove)
	{
	case ALERTLOGOMOVE_NONE:
		m_pos = ALERT_POS;
		break;

	case ALERTLOGOMOVE_START:
		m_pos.x -= 20.0f;
		if (m_pos.x <= SCREEN_CENTER.x)
		{
			m_alertLogoMove = ALERTLOGOMOVE_STOP;
			m_pos = SCREEN_CENTER;
		}
		break;

	case ALERTLOGOMOVE_STOP:
		m_nCntStop++;

		if (m_nCntStop > CNT_ONE_SECOND)
		{
			m_alertLogoMove = ALERTLOGOMOVE_RESTART;
			m_nCntStop = 0;
		}

		break;

	case ALERTLOGOMOVE_RESTART:
		m_pos.x -= 20.0f;

		if (m_pos.x < -ALERT_SIZE.x)
		{
			m_alertLogoMove = ALERTLOGOMOVE_END;
		}

		break;

	case ALERTLOGOMOVE_END:

		m_alertLogoMove = ALERTLOGOMOVE_NONE;

		break;
	}
}