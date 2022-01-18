//=============================================================================
//
// ���C������ [title.cpp]
// Author : Tatsuki Matsuda 
//
//=============================================================================
#include "fade.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "sound.h"
#include "title.h"
#include "title_enter.h"
#include "title_logo.h"
#include "title_runningman.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
CBg*CTitle::m_pBg = NULL;								// �w�i�ϐ�
CTitleLogo *CTitle::m_pTitleLogo = NULL;				// ���S�|�C���^
CTitleEnter *CTitle::m_pTitleEnter = NULL;				// �G���^�[�T�C���|�C���^
CTitleRunningMan *CTitle::m_pTitleRunningMan = NULL;	// �w�i�A�j���[�V�����|�C���^

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
CTitle::CTitle()
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CTitle::~CTitle()
{

}

//*****************************************************************************
// ����������
//*****************************************************************************
HRESULT CTitle::Init(void)
{
	// �w�i�N���X�̐���
	m_pBg = CBg::Create();

	// �����j���O�}��
	m_pTitleRunningMan = CTitleRunningMan::Create(T_RUNNINGMAN_POS);

	// �^�C�g�����S
	m_pTitleLogo = CTitleLogo::Create(T_LOGO_POS);

	// �G���^�[�T�C��
	m_pTitleEnter = CTitleEnter::Create(T_ENTER_POS);


	// BGM�̍Đ�
	if (m_pSound != NULL && CManager::GetBGMPlay(CSound::BGMTYPE_TITLE) == true)
	{
		m_pSound->Play(CSound::SOUND_LABEL_BGM000);
	}

	return S_OK;
}

//*****************************************************************************
// �I������
//*****************************************************************************
void CTitle::Uninit(void)
{
	// BGM�̒�~
	if (m_pSound != NULL && CManager::GetBGMPlay(CSound::BGMTYPE_TITLE) == true)
	{
		m_pSound->Stop();
	}

	// �^�C�g�����S
	if (m_pTitleLogo != NULL)
	{
		m_pTitleLogo->Uninit();
		m_pTitleLogo = NULL;
	}

	// �G���^�[�T�C��
	if (m_pTitleEnter != NULL)
	{
		m_pTitleEnter->Uninit();
		m_pTitleEnter = NULL;
	}

	// �G���^�[�T�C��
	if (m_pTitleRunningMan != NULL)
	{
		m_pTitleRunningMan->Uninit();
		m_pTitleRunningMan = NULL;
	}

	Release();
}

//*****************************************************************************
// �X�V����
//*****************************************************************************
void CTitle::Update(void)
{

}

//*****************************************************************************
// �`�揈��
//*****************************************************************************
void CTitle::Draw(void)
{

}

//*****************************************************************************
// ��������
//*****************************************************************************
CTitle *CTitle::Create(void)
{
	CTitle *pTitle;
	pTitle = new CTitle;

	if (pTitle != NULL)
	{
		pTitle->Init();
	}

	return pTitle;
}

//*****************************************************************************
// �w�i��񏈗�
//*****************************************************************************
CBg*CTitle::GetBg(void)
{
	return m_pBg;
}