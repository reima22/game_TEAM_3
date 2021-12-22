//==============================================================================
//
// �|�[�Y�����kpause.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "pause.h"
#include "pause_bg.h"
#include "pause_base.h"
#include "pause_select.h"
#include "input.h"
#include "gamepad.h"
#include "sound.h"
#include "fade.h"

#include "game.h"

// �ÓI�����o�ϐ�
bool CPause::m_bPause;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CPause::CPause(int nPriority) : CScene(nPriority)
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CPause::~CPause()
{

}

//==============================================================================
// �|�[�Y�̏���������
//==============================================================================
HRESULT CPause::Init(void)
{
	// �|�[�Y�̏�����
	m_bPause = false;

	// �w�i�̐���
	CPauseBg::Create();

	// �x�[�X�̐���
	CPauseBase::Create();

	// �I�����̐���
	CPauseSelect::Create();

	return S_OK;
}

//==============================================================================
// �|�[�Y�̏I������
//==============================================================================
void CPause::Uninit(void)
{
	
}

//==============================================================================
// �|�[�Y�̍X�V����
//==============================================================================
void CPause::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	// �t�F�[�h���̎擾
	CFade::FADE fade = CManager::GetFade()->GetFade();

	// �t�F�[�h���A�Q�[���I�����o�������A��������
	if (fade == CFade::FADE_NONE && CGame::GetGameEnd() == false)
	{
		if (keyboard->GetTrigger(CInput::KEYINFO_PAUSE) == true || gamepad->GetTrigger(CInput::KEYINFO_PAUSE) == true)
		{
			CSound::Play(CSound::SOUND_LABEL_SE_DECIDE);
			SetPause();
		}
	}
}

//==============================================================================
// �|�[�Y�̕`�揈��
//==============================================================================
void CPause::Draw(void)
{
	
}

//==============================================================================
// �|�[�Y�̐�������
//==============================================================================
CPause *CPause::Create()
{
	// �C���X�^���X����
	CPause *pPause;
	pPause = new CPause;

	// ������
	pPause->Init();

	return pPause;
}

//==============================================================================
// �|�[�Y�̐؂�ւ�
//==============================================================================
void CPause::SetPause(void)
{
	// �I����Ԃ̏�����
	CPauseSelect::SetPause(CPauseSelect::PAUSE_CONTINUE);

	// �|�[�Y�̃I���I�t
	m_bPause = !m_bPause;
}