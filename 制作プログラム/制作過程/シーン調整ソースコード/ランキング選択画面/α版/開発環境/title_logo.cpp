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
		m_pScene2D->BindTexture("TITLE_LOGO");
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

	// �F
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// Enter���������A�ʒu���w��l���E�������ꍇ
	if ((keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) || m_pos.x > T_LOGO_SETPOS.x) &&
		m_bLogoMoveEnd == false)
	{
		// �ړ��l
		m_move = VECTOR3_NULL;

		// �ʒu��^����
		m_pos = T_LOGO_SETPOS;

		// ���n��
		m_pSound->Play(CSound::SOUND_LABEL_SE_SAVEPOINT);

		// �ړ�����
		m_bLogoMoveEnd = true;
	}
	else  if (m_pos.x < T_LOGO_SETPOS.x)
	{// �ʒu���w��l��荶�������ꍇ

	 // �d��
		float fGravity = GRAVITY;

		// �J�E���g�l�����l��������Ă���ꍇ
		if (m_nJumpCnt <= 0)
		{
			// ���x
			m_fSpead = MOVE_SPEED;
		}

		// ���x�ɏd�͂���
		m_fSpead += fGravity;

		// �ʒu���w��l���������ꍇ
		if (m_pos.y > T_LOGO_SETPOS.y)
		{
			// ���x�ɑ��
			m_fSpead = -m_fSpead;

			// �J�E���g���Z
			m_nJumpCnt++;

			// �o�E���h��
			m_pSound->Play(CSound::SOUND_LABEL_SE_JUMP);
		}

		// �ړ��l
		m_move.x += MOVE_TITLE_X;
		m_move.y = m_fSpead + (m_nJumpCnt / 1.2f);
	}

	// �ړ��l���ʒu���W�ɑ���
	m_pos += m_move;

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