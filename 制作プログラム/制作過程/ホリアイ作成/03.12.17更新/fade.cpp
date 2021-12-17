//==============================================================================
//
// �t�F�[�h�����kfade.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "fade.h"
#include "polygon.h"
#include "input.h"
#include "gamepad.h"

// �ÓI�����o�ϐ�
CPolygon *CFade::m_pPolygon = NULL;
CFade::FADE CFade::m_fade = FADE_IN;
CMode::MODE CFade::m_modeNext;
D3DXCOLOR CFade::m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CFade::CFade()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CFade::~CFade()
{

}

//==============================================================================
// �t�F�[�h�̏���������
//==============================================================================
HRESULT CFade::Init(void)
{
	if (m_pPolygon == NULL)
	{
		m_pPolygon = 
			CPolygon::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
			0);

		m_pPolygon->SetCol(m_col);
	}

	return S_OK;
}

//==============================================================================
// �t�F�[�h�̏I������
//==============================================================================
void CFade::Uninit(void)
{
	if (m_pPolygon != NULL)
	{// NULL�`�F�b�N��ɔj��
		m_pPolygon->Uninit();
		m_pPolygon = NULL;
	}
}

//==============================================================================
// �t�F�[�h�̍X�V����
//==============================================================================
void CFade::Update(void)
{
	// ���[�J���ϐ��錾
	CMode *pMode;
	pMode = CManager::GetModePoint();

	CMode::MODE mode;
	mode = pMode->GetMode();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	if (m_fade == FADE_IN)
	{
		// �����x�̒ቺ
		m_col.a -= 0.01f;

		if (m_col.a <= 0.0f)
		{// �t�F�[�h�C���������L�[���͂ŒZ�k
			if (mode != CMode::MODE_GAME && (keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true))
			{
				m_col.a = 0.0f;
				m_fade = FADE_NONE;
			}
			else
			{
				m_col.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}
	}
	else if (m_fade == FADE_OUT)
	{
		m_col.a += 0.01f;

		if (m_col.a >= 1.0f)
		{
			m_col.a = 1.0f;
			m_fade = FADE_IN;
			pMode->SetMode(m_modeNext);
		}
	}

	// �F�̐ݒ�
	m_pPolygon->SetCol(m_col);
}

//==============================================================================
// �t�F�[�h�̕`�揈��
//==============================================================================
void CFade::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �t�H�O�𖳌���
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	if (m_pPolygon != NULL)
	{
		m_pPolygon->Draw();
	}

	// �t�H�O��L����
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}

//==============================================================================
// �t�F�[�h�̐�������
//==============================================================================
CFade *CFade::Create()
{
	// �C���X�^���X����
	CFade *pFade;
	pFade = new CFade;

	// ������
	if (pFade != NULL)
	{
		pFade->Init();
	}

	return pFade;
}

//==============================================================================
// �t�F�[�h�̐ݒ�
//==============================================================================
void CFade::SetFade(FADE fade, CMode::MODE modeNext)
{
	m_fade = fade;
	m_modeNext = modeNext;
}

//==============================================================================
// �t�F�[�h�C���̃J�b�g
//==============================================================================
void CFade::FadeInCancel(void)
{
	// �����x�̕ύX
	m_col.a = 0.0f;

	// �t�F�[�h���[�h�̐؂�ւ�
	m_fade = FADE_NONE;
}