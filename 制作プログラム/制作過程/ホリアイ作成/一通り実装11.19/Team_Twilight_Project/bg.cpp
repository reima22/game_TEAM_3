//==============================================================================
//
// �w�i�`�揈���kbg.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "gamepad.h"
#include "game.h"
#include "bg.h"
#include "texture.h"
#include "result.h"
#include "mode.h"

// �ÓI�����o�ϐ��錾
D3DXVECTOR3 CBg::m_pos = SCREEN_CENTER;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CBg::CBg(int nPriority) : CScene2D(nPriority)
{
	m_pScene2D = NULL;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CBg::~CBg()
{
}

//==============================================================================
// �w�i�̏���������
//==============================================================================
HRESULT CBg::Init(void)
{
	// ���[�h�̎擾
	CMode::MODE mode = CManager::GetModePoint()->GetMode();

	if (m_pScene2D == NULL)
	{
		m_pScene2D = CScene2D::Create();
		m_pScene2D->SetPosition(m_pos);
		m_pScene2D->SetSize(D3DXVECTOR2(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
		m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pScene2D->SetTex(1, 1, 0, 0, 0, 0);
		
		switch (mode)
		{
		case CMode::MODE_TITLE:
			
			m_pScene2D->BindTexture("TITLE_BG");

			break;

		case CMode::MODE_SELECT:
			
			m_pScene2D->BindTexture("TEX0");
			
			break;

		//case CMode::MODE_GAME:

		//	break;

		case CMode::MODE_RESULT:
			m_pScene2D->BindTexture("RESULT_BG");
			break;
		}
	}

	return S_OK;
}

//==============================================================================
// �w�i�̏I������
//==============================================================================
void CBg::Uninit(void)
{
	if (m_pScene2D != NULL)
	{// NULL�`�F�b�N��ɔj��
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	Release();	// CBg�C���X�^���X�̃f���[�g
}

//==============================================================================
// �w�i�̍X�V����
//==============================================================================
void CBg::Update(void)
{
	// ���[�h�̎擾
	CMode::MODE mode = CManager::GetModePoint()->GetMode();
}

//==============================================================================
// �w�i�̕`�揈��
//==============================================================================
void CBg::Draw(void)
{
	/*CScene�ɂĎ��s*/
}

//==============================================================================
// �w�i�̐�������
//==============================================================================
CBg *CBg::Create(void)
{
	// CBg�̃C���X�^���X����
	CBg *pBg;
	pBg = new CBg;

	// CBg�̏�����
	pBg->Init();

	return pBg;
}