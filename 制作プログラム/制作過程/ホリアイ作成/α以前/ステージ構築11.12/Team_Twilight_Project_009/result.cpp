
//==============================================================================
//
// ���U���g���[�h�����kresult.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "gamepad.h"
#include "result.h"
#include "bg.h"
#include "fade.h"
#include "result_logo.h"
#include "result_score.h"
#include "result_fallcount.h"
#include "sound.h"
#include "mode.h"

// �ÓI�����o�ϐ��錾
CResultLogo *CResult::m_pResultLogo = NULL;
CResultScore *CResult::m_pResultScore = NULL;
CResultFallCount *CResult::m_pResultFallCount = NULL;
CResult::ENDSTATE CResult::m_endState;	// �Q�[���I�����̏��

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CResult::CResult(int nPriority) : CMode(nPriority)
{
	
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CResult::~CResult()
{

}

//==============================================================================
// ���U���g��ʂ̏���������
//==============================================================================
HRESULT CResult::Init(void)
{
	// �w�i�̐���
	//CBg::Create();

	// ���S�̐���
	m_pResultLogo = CResultLogo::Create(R_LOGO_POS);

	// ���U���g�X�R�A�̐���
	m_pResultScore = CResultScore::Create(RESULT_SCORE_POS);

	// ���U���g�̗����J�E���g����
	m_pResultFallCount = CResultFallCount::Create();

	// BGM�̍Đ�
	CSound *pSound = CManager::GetSound();

	if (pSound != NULL && CManager::GetBGMPlay(CSound::BGMTYPE_RESULT) == true)
	{
		//pSound->Play(CSound::SOUND_LABEL_BGM002);
	}

	return S_OK;
}

//==============================================================================
// ���U���g��ʂ̏I������
//==============================================================================
void CResult::Uninit(void)
{
	// BGM�̒�~
	CSound::Stop();

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// ���U���g��ʂ̍X�V����
//==============================================================================
void CResult::Update(void)
{
	// �t�F�[�h���̎擾
	CFade *pFade;
	pFade = CManager::GetFade();
	CFade::FADE fade = pFade->GetFade();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	// �V�[���J��
	if (keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
	{
		if (fade == CFade::FADE_NONE && CResultScore::GetShuffleCnt() > 150)
		{
			pFade->SetFade(CFade::FADE_OUT, CMode::MODE_RANKING);
		}
		else if (fade == CFade::FADE_IN)
		{// �t�F�[�h�C���̃J�b�g
			pFade->FadeInCancel();
		}

		if (CResultScore::GetShuffleCnt() < 150 && fade == CFade::FADE_NONE)
		{// �J�E���g�̒Z�k
			CResultScore::SetShuffleCnt(150);
		}
	}
}

//==============================================================================
// ���U���g��ʂ̕`�揈��
//==============================================================================
void CResult::Draw(void)
{

}


//==============================================================================
// ���U���g���[�h�̐�������
//==============================================================================
CResult *CResult::Create()
{
	// �C���X�^���X����
	CResult *pResult;
	pResult = new CResult;

	// ������
	pResult->Init();

	return pResult;
}

//==============================================================================
// �Q�[���I�����̏�Ԑݒ�
//==============================================================================
void CResult::SetEndState(ENDSTATE endState)
{
	m_endState = endState;
}