
//==============================================================================
//
// �`���[�g���A�����[�h�����ktutorial.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "gamepad.h"
#include "tutorial.h"
#include "bg.h" 
#include "fade.h"
#include "tutorial_page.h"
#include "sound.h"

// �ÓI�����o�ϐ��錾
CTutorialPage *CTutorial::m_pTutorialPage = NULL;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTutorial::CTutorial(int nPriority) : CMode(nPriority)
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTutorial::~CTutorial()
{
}

//==============================================================================
// �^�C�g����ʂ̏���������
//==============================================================================
HRESULT CTutorial::Init(void)
{
	// �`���[�g���A���y�[�W�̐���
	m_pTutorialPage = CTutorialPage::Create(SCREEN_CENTER);

	//// BGM�Đ�
	//if (CManager::GetBGMPlay(CSound::BGMTYPE_TUTORIAL) == true)
	//{
	//	CSound::Play(CSound::SOUND_LABEL_BGM006);
	//}
	return S_OK;
}

//==============================================================================
// �^�C�g����ʂ̏I������
//==============================================================================
void CTutorial::Uninit(void)
{
	// BGM�̒�~
	//CSound::Stop();

	// �`���[�g���A���y�[�W�̔j��
	if (m_pTutorialPage != NULL)
	{
		m_pTutorialPage->Uninit();
		m_pTutorialPage = NULL;
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �^�C�g����ʂ̍X�V����
//==============================================================================
void CTutorial::Update(void)
{
	// �t�F�[�h���̎擾
	CFade *pFade;
	pFade = CManager::GetFade();
	CFade::FADE fade = pFade->GetFade();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	int nPageCnt = m_pTutorialPage->GetPageCnt();

	if (keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
	{
		if (fade == CFade::FADE_NONE && nPageCnt <= 0)
		{
			CSound::Play(CSound::SOUND_LABEL_SE_DECIDE);			// �T�E���h�Đ�
			pFade->SetFade(CFade::FADE_OUT, CMode::MODE_GAME);	// �V�[���J��
		}
		else if (fade == CFade::FADE_IN)
		{
			// �t�F�[�h�C���̃J�b�g
			pFade->FadeInCancel();
		}
	}
}

//==============================================================================
// �^�C�g����ʂ̕`�揈��
//==============================================================================
void CTutorial::Draw(void)
{

}

//==============================================================================
// �^�C�g�����[�h��������
//==============================================================================
CTutorial *CTutorial::Create()
{
	// �C���X�^���X����
	CTutorial *pTutorial;
	pTutorial = new CTutorial;

	// ������
	pTutorial->Init();

	return pTutorial;
}