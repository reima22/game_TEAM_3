//==============================================================================
//
// �`���[�g���A���y�[�W�`�揈���ktutorial_page.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "sound.h"
#include "tutorial_page.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"

// �ÓI�����o�ϐ�
D3DXCOLOR CTutorialPage::m_col[TUTORIAL_PAGE_MAX];

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTutorialPage::CTutorialPage(int nPriority) : CScene2D(nPriority)
{
	// �|���S���̏�����
	for (int nCnt = 0; nCnt < TUTORIAL_PAGE_MAX; nCnt++)
	{
		m_pScene2D[nCnt] = NULL;
		m_col[nCnt] = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	}

	m_nPageCnt = TUTORIAL_PAGE_MAX;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTutorialPage::~CTutorialPage()
{
}

//==============================================================================
// �`���[�g���A���y�[�W�̏���������
//==============================================================================
HRESULT CTutorialPage::Init(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < TUTORIAL_PAGE_MAX; nCnt++)
	{
		if (m_pScene2D[nCnt] == NULL)
		{
			m_pScene2D[nCnt] = CScene2D::Create();

			m_pScene2D[nCnt]->SetPosition(pos);
			m_pScene2D[nCnt]->SetSize(SCREEN_SIZE);
			//m_pScene2D[nCnt]->BindTexture(21 - nCnt);
			m_pScene2D[nCnt]->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
		}
	}

	return S_OK;
}

//==============================================================================
// �`���[�g���A���y�[�W�̏I������
//==============================================================================
void CTutorialPage::Uninit(void)
{
	// �y�[�W�̔j��
	for (int nCnt = 0; nCnt < TUTORIAL_PAGE_MAX; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{// NULL�`�F�b�N��ɔj��
			m_pScene2D[nCnt]->Uninit();
			m_pScene2D[nCnt] = NULL;
		}
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �`���[�g���A���y�[�W�̍X�V����
//==============================================================================
void CTutorialPage::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	// �t�F�[�h�̎擾
	CFade::FADE fade = CManager::GetFade()->GetFade();

	// ���[�J���ϐ��錾
	D3DXCOLOR col[TUTORIAL_PAGE_MAX];

	 // �t�F�[�h�̏��
	if (fade != CFade::FADE_IN)
	{
		if (keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
		{
			m_nPageCnt--;
			if (m_nPageCnt > 0)
			{
				m_col[m_nPageCnt].a = 0.0f;
			}			
		}
		if (m_nPageCnt < TUTORIAL_PAGE_MAX)
		{
			if (keyboard->GetTrigger(CInput::KEYINFO_TUTO_BACK) == true || gamepad->GetTrigger(CInput::KEYINFO_TUTO_BACK) == true)
			{
				m_col[m_nPageCnt].a = 1.0f;
				m_nPageCnt++;
			}
		}		
	}


	// �F�̐ݒ�
	for (int nCnt = 0; nCnt < TUTORIAL_PAGE_MAX; nCnt++)
	{
		m_pScene2D[nCnt]->SetCol(m_col[nCnt]);
	}
}

//==============================================================================
// �`���[�g���A���y�[�W�̕`�揈��
//==============================================================================
void CTutorialPage::Draw(void)
{
	for (int nCnt = 0; nCnt < TUTORIAL_PAGE_MAX; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt]->Draw();
		}
	}
}

//==============================================================================
// �`���[�g���A���y�[�W�̐�������
//==============================================================================
CTutorialPage *CTutorialPage::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CTutorialPage *pTutorialPage;
	pTutorialPage = new CTutorialPage;

	// ������
	if (pTutorialPage != NULL)
	{
		pTutorialPage->Init(pos);
	}

	return pTutorialPage;
}