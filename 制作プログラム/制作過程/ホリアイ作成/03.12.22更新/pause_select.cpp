//==============================================================================
//
// �|�[�Y�I���������kpause_select.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "pause_select.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"
#include "sound.h"
#include "textdata.h"
#include "textdata_pause.h"

// �ÓI�����o�ϐ��錾
CScene2D *CPauseSelect::m_apScene2D[PAUSE_MAX] = {};
CPauseSelect::PAUSE CPauseSelect::m_pause;				// �I�𒆂̃J�[�\��
D3DXCOLOR CPauseSelect::m_col;							// �I�𒆃J�[�\���̐F

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CPauseSelect::CPauseSelect(int nPriority) : CScene(nPriority)
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CPauseSelect::~CPauseSelect()
{
}

//==============================================================================
// �|�[�Y�x�[�X�̏���������
//==============================================================================
HRESULT CPauseSelect::Init(void)
{
	// �e�L�X�g�f�[�^�̎擾
	CTextDataPause *pDataPause;
	pDataPause = CTextData::GetDataPause();

	for (int nCnt = 0; nCnt < PAUSE_MAX; nCnt++)
	{
		// �f�[�^�̎擾
		D3DXVECTOR3 pos = pDataPause->GetPosition(CTextDataPause::PAUSEPOLY_CONTINUE + nCnt);
		D3DXVECTOR2 size = pDataPause->GetSize(CTextDataPause::PAUSEPOLY_CONTINUE + nCnt);
		int nTexIdx = pDataPause->GetTexIdx(CTextDataPause::PAUSEPOLY_CONTINUE) + nCnt;

		// 2D�|���S���̐���
		m_apScene2D[nCnt] = CScene2D::Create();
		m_apScene2D[nCnt]->SetPosition(pos);
		m_apScene2D[nCnt]->SetSize(size);
		m_apScene2D[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_apScene2D[nCnt]->BindTextureNum(nTexIdx);
	}

	//m_apScene2D[PAUSE_CONTINUE]->BindTextureNum("PAUSE_CONTINUE");
	//m_apScene2D[PAUSE_RETRY]->BindTextureNum("PAUSE_RETRY");
	//m_apScene2D[PAUSE_QUIT]->BindTextureNum("PAUSE_QUIT");

	// ������
	m_pause = PAUSE_CONTINUE;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_bAlphaDown = true;

	return S_OK;
}

//==============================================================================
// �|�[�Y�x�[�X�̏I������
//==============================================================================
void CPauseSelect::Uninit(void)
{
	for (int nCnt = 0; nCnt < PAUSE_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			delete m_apScene2D[nCnt];
			m_apScene2D[nCnt]->Uninit();
			m_apScene2D[nCnt] = NULL;
		}
	}
}

//==============================================================================
// �|�[�Y�x�[�X�̍X�V����
//==============================================================================
void CPauseSelect::Update(void)
{
	// ���[�J���ϐ��錾
	bool bPause = CPause::GetPause();					// �|�[�Y�̎擾
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);	// �F�̐ݒ�
	
	// �|�[�Y��Ԃɉ����ĕω�
	switch (bPause)
	{
	case true:
		col.a = 1.0f;

		// �I�����[�h�̐ݒ�
		SetMode();

		break;

	case false:
		col.a = 0.0f;
		break;
	}

	for (int nCnt = 0; nCnt < PAUSE_MAX; nCnt++)
	{
		// �F��Ԃ̐ݒ�
		m_apScene2D[nCnt]->SetCol(col);
		m_apScene2D[nCnt]->Update();
	}
}

//==============================================================================
// �|�[�Y�x�[�X�̕`�揈��
//==============================================================================
void CPauseSelect::Draw(void)
{
	for (int nCnt = 0; nCnt < PAUSE_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Draw();
		}
	}
}

//==============================================================================
// �|�[�Y�x�[�X�̐�������
//==============================================================================
CPauseSelect *CPauseSelect::Create(void)
{
	// �C���X�^���X����
	CPauseSelect *pPauseSelect;
	pPauseSelect = new CPauseSelect;

	// ������
	pPauseSelect->Init();

	return pPauseSelect;
}

//==============================================================================
// �|�[�Y��Ԃ��Ƃ̐ݒ�
//==============================================================================
void CPauseSelect::SetMode(void)
{
	// �t�F�[�h���̎擾
	CFade *pFade;
	pFade = CManager::GetFade();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	// �J�[�\���̖���
	for (int nCnt = 0; nCnt < PAUSE_MAX; nCnt++)
	{
		if (nCnt == m_pause)
		{// �I��
			if (m_bAlphaDown == true)
			{
				m_col.a -= 0.01f;
				
				// �_�ł̐܂�Ԃ�
				if (m_col.a <= 0.5f)
				{
					m_col.a = 0.5f;
					m_bAlphaDown = false;
				}
			}
			else
			{
				m_col.a += 0.01f;

				// �_�ł̐܂�Ԃ�
				if (m_col.a >= 1.0f)
				{
					m_col.a = 1.0f;

					m_bAlphaDown = true;
				}
			}

			m_apScene2D[nCnt]->SetTex(1, 2, 0, 0, 0.0f, 0.0f);
			m_apScene2D[nCnt]->SetCol(m_col);			
		}
		else
		{// ����ȊO
			m_apScene2D[nCnt]->SetTex(1, 2, 0, 1, 0.0f, 0.0f);
			m_apScene2D[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	// �J�[�\���̈ړ�
	if (keyboard->GetTrigger(CInput::KEYINFO_DOWN) == true || gamepad->GetTrigger(CInput::KEYINFO_DOWN) == true)
	{
		CSound::Play(CSound::SOUND_LABEL_SE_SELECT);
		m_pause = (PAUSE)(m_pause + 1);
	}
	else if (keyboard->GetTrigger(CInput::KEYINFO_UP) == true || gamepad->GetTrigger(CInput::KEYINFO_UP) == true)
	{
		CSound::Play(CSound::SOUND_LABEL_SE_SELECT);
		m_pause = (PAUSE)(m_pause - 1);
	}

	// �J�[�\���̕␳
	if (m_pause < 0)
	{
		m_pause = (PAUSE)(PAUSE_MAX - 1);
	}
	else if (m_pause > (PAUSE_MAX - 1))
	{
		m_pause = PAUSE_CONTINUE;
	}

	// �I�������Ƃ̏���
	if (keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
	{
		// ���ʉ��̍Đ�
		CSound::Play(CSound::SOUND_LABEL_SE_DECIDE);

		switch (m_pause)
		{
		case PAUSE_CONTINUE:
			// �|�[�Y�̉���
			CPause::SetPause();
			break;

		case PAUSE_RETRY:
			// �Q�[���̂�蒼��
			pFade->SetFade(CFade::FADE_OUT,CMode::MODE_GAME);
			break;

		case PAUSE_QUIT:
			// �^�C�g���֖߂�
			pFade->SetFade(CFade::FADE_OUT, CMode::MODE_TITLE);
			CPause::SetPause();
			break;
		}	
	}
}