//==============================================================================
//
// �^�C�g�����S�`�揈���ktitle_logo.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "sound.h"
#include "title_logo.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"

// �ÓI�����o�ϐ��錾
bool CTitleLogo::m_bLogoMoveEnd;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTitleLogo::CTitleLogo(int nPriority) : CScene2D(nPriority)
{
	// �|���S���̏�����
	m_pScene2D = NULL;

	m_bLogoMoveEnd = false;
	m_nMoveCnt = 0;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTitleLogo::~CTitleLogo()
{
}

//==============================================================================
// �^�C�g�����S�̏���������
//==============================================================================
HRESULT CTitleLogo::Init(D3DXVECTOR3 pos)
{
	m_pos = pos;

	if (m_pScene2D == NULL)
	{
		m_pScene2D = CScene2D::Create();
		m_pScene2D->SetPosition(pos);
		m_pScene2D->SetSize(T_LOGO_SIZE);
		m_pScene2D->SetTex(1, 1, 0, 0, 0, 0);
		m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pScene2D->BindTexture(4);
	}

	return S_OK;
}

//==============================================================================
// �^�C�g�����S�̏I������
//==============================================================================
void CTitleLogo::Uninit(void)
{
	if (m_pScene2D != NULL)
	{// NULL�`�F�b�N��ɔj��
		delete m_pScene2D;
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �^�C�g�����S�̍X�V����
//==============================================================================
void CTitleLogo::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();
	
	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	// ���肪true�̏ꍇ
	if (m_bEnter == true && keyboard->GetTrigger(CInput::KEYINFO_OK) == true)
	{
		// �����true�ɕς���
		m_bTutorial = true;

		////SE
		//pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BUTTON);
	}
	else if (m_bEnter == false)
	{// ���肪false�̏ꍇ

	 // �G���^�[�L�[���������ꍇ
		if (keyboard->GetTrigger(CInput::KEYINFO_OK) == true)
		{
			// �����true�ɕς���
			m_bEnter = true;

			// �J�E���g�̒l��0�ɂ���
			m_nTimeColor = 0;

		}
	}

	// ���肪�ǂ����true�̏ꍇ
	if (m_bEnter == true && m_bTutorial == true)
	{
		// �J�E���g���Z
		m_nTimeColor++;

		// �J�E���g��5�Ŋ����0�ɂȂ�ꍇ
		if (m_nTimeColor % 5 == 0)
		{
			// �F
			m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			// �F
			m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		}

		// �J�E���g��50�𒴂����ꍇ
		if (m_nTimeColor >= COLOR_CNT)
		{
			// �t�F�[�h
			pFade->SetFade(CFade::FADE_OUT, CMode::MODE_GAME);

			// �����false�ɕς���
			m_bEnter = false;

			// �����false�ɕς���
			m_bTutorial = false;

			// �^�C�}�[��0�ɂ���
			m_nTimer = 0;
		}
	}

	// �ʒu�������������ʒu�ɂ��邩���肪false�̏ꍇ
	if (m_pos.y > POS_START_Y && m_bEnter == false)
	{
		// �ړ��l
		m_move.y = MOVE_START_Y;

		// �F
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	}
	else
	{
		// �ʒu��^����
		m_pos.y = POS_START_Y;

		// �ړ��l
		m_move.y = 0.0f;

		// �����true�ɕς���
		m_bEnter = true;

		//�ҋ@�_�ŃJ�E���g
		m_nCntColor++;
	}

	// ���肪true�ł͂Ȃ��ꍇ
	if (m_bTutorial != true)
	{
		// �J�E���g���w��l���Ⴂ�ꍇ�ꍇ
		if (m_nCntColor <= 50)
		{
			// �F
			m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, (1.0f / ((float)m_nCntColor *0.75f)));
		}

		if (m_nCntColor > 50 && m_nCntColor <= 100)
		{// �J�E���g���w��l�͈͓̔��̏ꍇ

		 // �F
			m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, (0.0001f * ((float)m_nCntColor * 100.0f)));
		}
		else if (m_nCntColor > 150)
		{ //�J�E���g���w��l�𒴂��Ă���ꍇ

		  //�J�E���g��0�ɂ���
			m_nCntColor = 0;
		}
	}

	m_pScene2D->SetPosition(m_pos);
}

//==============================================================================
// �^�C�g�����S�̕`�揈��
//==============================================================================
void CTitleLogo::Draw(void)
{

}

//==============================================================================
// �^�C�g�����S�̐�������
//==============================================================================
CTitleLogo *CTitleLogo::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CTitleLogo *pTitleLogo;
	pTitleLogo = new CTitleLogo;

	// ������
	pTitleLogo->Init(pos);

	return pTitleLogo;
}