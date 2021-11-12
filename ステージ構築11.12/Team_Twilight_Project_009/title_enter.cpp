//==============================================================================
//
// �G���^�[�T�C���`�揈���ktitle_enter.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "sound.h"
#include "title.h"
#include "title_logo.h"
#include "title_enter.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTitleEnter::CTitleEnter(int nPriority) : CScene2D(nPriority)
{
	// �|���S���̏�����
	m_pScene2D = NULL;

	m_nAnimCnt = 0;
	m_nBlinkCnt = 0;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTitleEnter::~CTitleEnter()
{
}

//==============================================================================
// �G���^�[�T�C���̏���������
//==============================================================================
HRESULT CTitleEnter::Init(D3DXVECTOR3 pos)
{
	// �����o�[�ϐ�������
	m_pos = pos;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	if (m_pScene2D == NULL)
	{
		m_pScene2D = CScene2D::Create();
	}

	m_pScene2D->SetPosition(pos);
	m_pScene2D->SetSize(T_ENTER_SIZE);
	m_pScene2D->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	m_pScene2D->BindTexture(5);

	return S_OK;
}

//==============================================================================
// �G���^�[�T�C���̏I������
//==============================================================================
void CTitleEnter::Uninit(void)
{
	if (m_pScene2D != NULL)
	{// NULL�`�F�b�N��ɔj��
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �G���^�[�T�C���̍X�V����
//==============================================================================
void CTitleEnter::Update(void)
{
	// ���[�J���ϐ��錾
	bool bEndLogo = CTitleLogo::GetLogoState();
	
	// �G���^�[�T�C���_��
	if (bEndLogo == true)
	{
		m_nAnimCnt++;

		//if (bDifficult == false)
		{// �X�^�[�g����
			if (m_nAnimCnt % 60 == 0)
			{
				m_col.a = 0.0f;
			}
			else if (m_nAnimCnt % 30 == 0 && m_nAnimCnt % 60 != 0)
			{
				m_col.a = 1.0f;
			}
		}


		//else
		//{// �J�n��
		//	//if (CTitleDifficulty::GetSelect() == false)
		//	{
		//		m_nBlinkCnt++;

		//		if (m_nAnimCnt % 2 == 0)
		//		{
		//			m_col.a = 0.0f;
		//		}
		//		else
		//		{
		//			m_col.a = 1.0f;
		//		}

		//		if (m_nBlinkCnt >= 90)
		//		{
		//			//CTitleDifficulty::SetSelect(true);
		//		}
		//	}
		//	//else
		//	{
		//		//m_col.a = 0.0f;
		//	}
		//}
	}

	// �F�̐ݒ�
	//m_pScene2D->SetCol(m_col);
}

//==============================================================================
// �G���^�[�T�C���̕`�揈��
//==============================================================================
void CTitleEnter::Draw(void)
{

}

//==============================================================================
// �G���^�[�T�C���̐�������
//==============================================================================
CTitleEnter *CTitleEnter::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CTitleEnter *pTitleEnter;
	pTitleEnter = new CTitleEnter;

	// ������
	if (pTitleEnter != NULL)
	{
		pTitleEnter->Init(pos);
	}

	return pTitleEnter;
}