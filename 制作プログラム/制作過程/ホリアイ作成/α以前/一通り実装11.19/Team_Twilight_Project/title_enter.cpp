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
#include "input.h"
#include "gamepad.h"
#include "fade.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTitleEnter::CTitleEnter(int nPriority) : CScene2D(nPriority)
{
	// �|���S���̏�����
	m_pScene2D = NULL;
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
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	if (m_pScene2D == NULL)
	{
		m_pScene2D = CScene2D::Create();
		m_pScene2D->SetPosition(pos);
		m_pScene2D->SetSize(T_ENTER_SIZE);
		m_pScene2D->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
		m_pScene2D->SetCol(m_col);
		m_pScene2D->BindTexture("TITLE_ENTER");
	}

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
	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	// �^�C�}�[
	m_nTimer++;

	// ���肪true�̏ꍇ
	if (m_bEnter == true && (keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true) &&
		m_bNextScene == false)
	{
		// �����true�ɕς���
		m_bNextScene = true;

		// SE
		m_pSound->Play(CSound::SOUND_LABEL_SE_TITLEENTER);
	}
	else if (m_bEnter == false)
	{// ���肪false�̏ꍇ

		 // �G���^�[�L�[���������ꍇ
		if (keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
		{
			// �����true�ɕς���
			m_bEnter = true;

			// �J�E���g�̒l��0�ɂ���
			m_nTimeColor = 0;
		}
	}

	// ���肪�ǂ����true�̏ꍇ
	if (m_bEnter == true && m_bNextScene == true)
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
		if (m_nTimeColor >= TIME_COLOR)
		{
			// �t�F�[�h
			pFade->SetFade(CFade::FADE_OUT, CMode::MODE_SELECT);

			//// �����false�ɕς���
			//m_bEnter = false;
			//// �����false�ɕς���
			//m_bNextScene = false;
			//// �^�C�}�[��0�ɂ���
			//m_nTimer = 0;
		}
	}

	// �ʒu�������������ʒu�ɂ��邩���肪false�̏ꍇ
	if (m_pos.y > T_ENTER_SETPOS.y && m_bEnter == false)
	{
		// �ړ��l
		m_move.y = MOVE_START_Y;

		// �F
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		// �ʒu��^����
		m_pos = T_ENTER_SETPOS;

		// �ړ��l
		m_move.y = 0.0f;

		// �����true�ɕς���
		m_bEnter = true;

		//�ҋ@�_�ŃJ�E���g
		m_nCntColor++;
	}

	// ���肪true�ł͂Ȃ��ꍇ
	if (m_bNextScene != true)
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

	m_pos += m_move;

	// �ʒu�ݒ�
	m_pScene2D->SetPosition(m_pos);
	
	// �F�̐ݒ�
	m_pScene2D->SetCol(m_col);
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