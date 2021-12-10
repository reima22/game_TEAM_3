//==============================================================================
//
// �Q�[�����[�h�Ǘ��kmode.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "manager.h"
#include "mode.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "select.h"

//==============================================================================
// �ÓI�����o�ϐ�
//==============================================================================
CTitle *CMode::m_pTitle = NULL;					// �^�C�g�����[�h
CTutorial *CMode::m_pTutorial = NULL;			// �`���[�g���A�����[�h
CGame *CMode::m_pGame = NULL;					// �Q�[�����[�h
CResult *CMode::m_pResult = NULL;				// ���U���g���[�h
CRanking *CMode::m_pRanking = NULL;				// �����L���O���[�h
CStageSelect *CMode::m_pStageSelect = NULL;		// �X�e�[�W�Z���N�g���[�h
CMode::MODE CMode::m_mode = MODE_TITLE;			// ���݂̃Q�[�����[�h

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CMode::CMode(int nPriority) : CScene(nPriority)
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CMode::~CMode()
{

}

//==============================================================================
// ������
//==============================================================================
HRESULT CMode::Init(void)
{
	return S_OK;
}

//==============================================================================
// �I��
//==============================================================================
void CMode::Uninit(void)
{

}

//==============================================================================
// �X�V
//==============================================================================
void CMode::Update(void)
{

}

//==============================================================================
// �`��
//==============================================================================
void CMode::Draw(void)
{

}

//==============================================================================
// ��������
//==============================================================================
CMode *CMode::Create(void)
{
	// ���[�J���ϐ��錾
	CMode *pMode;
	pMode = new CMode;

	// ���[�h�̐ݒ�
	if (pMode != NULL)
	{
		pMode->SetMode(m_mode);
	}

	return pMode;
}

//==============================================================================
// ���݂̃V�[�����[�h�̐ݒ�
//==============================================================================
void CMode::SetMode(MODE mode)
{
	// ���[�h�̔j��
	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;

	case MODE_SELECT:
		if (m_pStageSelect != NULL)
		{
			m_pStageSelect->Uninit();
			m_pStageSelect = NULL;
		}
		break;

	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			m_pTutorial = NULL;
		}
		break;

	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;

	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;

	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pRanking->Uninit();
			m_pRanking = NULL;
		}
		break;

	default:
		break;
	}

	// �I�u�W�F�N�g�j��
	CScene::ReleaseAll();

	CScene::UpdateAll();

	// ���[�h�̐ݒ�
	m_mode = mode;

	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{
			m_pTitle = CTitle::Create();
		}
		break;

	case MODE_SELECT:
		if (m_pStageSelect == NULL)
		{
			m_pStageSelect = CStageSelect::Create();
		}
		break;

	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			m_pTutorial = CTutorial::Create();
		}
		break;

	case MODE_GAME:
		if (m_pGame == NULL)
		{
			m_pGame = CGame::Create();
		}
		break;

	case MODE_RESULT:
		if (m_pResult == NULL)
		{
			m_pResult = CResult::Create();
		}
		break;

	case MODE_RANKING:
		if (m_pRanking == NULL)
		{
			m_pRanking = CRanking::Create();
		}
		break;

	default:
		break;
	}
}