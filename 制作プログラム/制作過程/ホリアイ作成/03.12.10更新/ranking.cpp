//==============================================================================
//
// �����L���O���[�h�����kranking.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "gamepad.h"
#include "bg.h" 
#include "fade.h"
#include "title.h"
#include "ranking.h"
#include "ranking_logo.h"
#include "ranking_rank.h"
#include "ranking_score.h"
#include "ranking_select.h"
#include "sound.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CRanking::CRanking(int nPriority) : CMode(nPriority)
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CRanking::~CRanking()
{
}

//==============================================================================
// �����L���O��ʂ̏���������
//==============================================================================
HRESULT CRanking::Init()
{
	// �^�C�g������J�ڂ�����
	//m_bFromTitle = CTitle::GetAutoFade();

	// �����J�ڃJ�E���g�̏�����
	m_nAutoFadeCnt = 0;

	// �w�i����
	CBg::Create();

	// �J�ڌ��ɂ�镪��
	if (m_bFromTitle == true)
	{// �^�C�g������̑J��
	 // ���S����
		CRankingLogo::Create(RANK_LOGO_POS_T, RANK_LOGO_SIZE, "RANKING_LOGO");

		// �X�R�A�̐���
		CRankingScore::Create(RANK_SCORE_POS_T);

		// ���ʂ̐���
		CRankingRank::Create();
	}
	else
	{// �ʏ�J��
	 // ���S����
		CRankingLogo::Create(RANK_LOGO_POS, RANK_LOGO_SIZE, "RANKING_LOGO");

		// �X�R�A�̐���
		CRankingScore::Create(RANK_SCORE_POS);

		// ���ʂ̐���
		CRankingRank::Create();

		// �I�����̐���
		CRankingSelect::Create();
	}

	// BGM�Đ�
	if (m_pSound != NULL && CManager::GetBGMPlay(CSound::BGMTYPE_RANKING) == true)
	{
		m_pSound->Play(CSound::SOUND_LABEL_BGM006);
	}

	return S_OK;
}

//==============================================================================
// �����L���O��ʂ̏I������
//==============================================================================
void CRanking::Uninit(void)
{
	// BGM�̒�~
	if (m_pSound != NULL && CManager::GetBGMPlay(CSound::BGMTYPE_RANKING) == true)
	{
		m_pSound->Stop();
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �����L���O��ʂ̍X�V����
//==============================================================================
void CRanking::Update(void)
{

}

//==============================================================================
// �����L���O��ʂ̕`�揈��
//==============================================================================
void CRanking::Draw(void)
{

}

//==============================================================================
// �����L���O���[�h��������
//==============================================================================
CRanking *CRanking::Create()
{
	// �C���X�^���X����
	CRanking *pRanking;
	pRanking = new CRanking;

	// ������
	if (pRanking != NULL)
	{
		pRanking->Init();
	}

	return pRanking;
}