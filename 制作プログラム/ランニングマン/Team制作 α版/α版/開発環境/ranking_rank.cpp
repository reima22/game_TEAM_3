//==============================================================================
//
// �����L���O���ʂ̕`�揈���kranking_rank.cpp�l
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
#include "ranking.h"
#include "ranking_rank.h"
#include "ranking_score.h"

// �ÓI�����o�ϐ��錾
int CRankingRank::m_aRank[RANK_NUM];

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CRankingRank::CRankingRank(int nPriority) : CRanking(nPriority)
{
	// �|���S���̏�����
	for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
	}

	m_pYourScore = NULL;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CRankingRank::~CRankingRank()
{
}

//==============================================================================
// �����L���O���ʂ̏���������
//==============================================================================
HRESULT CRankingRank::Init(void)
{
	// �����J�ڔ���
	//m_bFromTitle = CTitle::GetAutoFade();

	// �|���S��������
	for (int nCntRank = 0; nCntRank < RANK_NUM; nCntRank++)
	{
		if (m_apScene2D[nCntRank] == NULL)
		{
			m_apScene2D[nCntRank] = CScene2D::Create();
			m_apScene2D[nCntRank]->SetPosition(D3DXVECTOR3(RANK_POS.x, RANK_POS.y + (nCntRank * 90.0f), 0.0f));
			m_apScene2D[nCntRank]->SetSize(RANK_SIZE);
			m_apScene2D[nCntRank]->SetTex(1, 5, 0, m_aRank[nCntRank], 0.0f, 0.0f);
			m_apScene2D[nCntRank]->BindTexture("RANKING_RANK");

			// ���ʂ̏�����
			m_aRank[nCntRank] = nCntRank;
		}

		m_aScore[nCntRank] = CRankingScore::GetRankingScore(nCntRank);
	}

	// ���ʂ̐ݒ�
	SetRank();

	// �����J�ڂłȂ��ꍇ�̒ǉ�
	if (m_bFromTitle == false)
	{
		m_pYourScore = CScene2D::Create();
		m_pYourScore->SetPosition(RESULT_SCORE_LOGO_POS);
		m_pYourScore->SetSize(RANK_SIZE);
		m_pYourScore->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
		m_pYourScore->BindTexture("RANKING_YOURSCORE");
	}
	
	return S_OK;
}

//==============================================================================
// �����L���O���ʂ̏I������
//==============================================================================
void CRankingRank::Uninit(void)
{
	// �����L���O���ʕ\�L�̔j��
	for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{// NULL�`�F�b�N��ɔj��
			m_apScene2D[nCnt]->Uninit();
			m_apScene2D[nCnt] = NULL;
		}
	}

	// �u����̃X�R�A�v���S�\�L�̔j��
	if (m_pYourScore != NULL)
	{
		m_pYourScore->Uninit();
		m_pYourScore = NULL;
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// �����L���O���ʂ̍X�V����
//==============================================================================
void CRankingRank::Update(void)
{
	// �����L���O���ʂ̍X�V
	for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Update();
		}
	}

	// �u����̃X�R�A�v���S�̍X�V
	if (m_pYourScore != NULL)
	{
		m_pYourScore->Update();
	}
}

//==============================================================================
// �����L���O���ʂ̕`�揈��
//==============================================================================
void CRankingRank::Draw(void)
{
	// �����L���O���ʂ̕`��
	for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Draw();
		}
	}

	// �u����̃X�R�A�v���S�̕`��
	if (m_pYourScore != NULL)
	{
		m_pYourScore->Draw();
	}
}

//==============================================================================
// �����L���O���ʂ̐�������
//==============================================================================
CRankingRank *CRankingRank::Create(void)
{
	// �C���X�^���X����
	CRankingRank *pRankingRank;
	pRankingRank = new CRankingRank;

	// ������
	if (pRankingRank != NULL)
	{
		pRankingRank->Init();
	}

	return pRankingRank;
}

//==============================================================================
// ���ʂ̐ݒ�
//==============================================================================
void CRankingRank::SetRank(void)
{
	// 1�ʂ������ď��ʂ̕ϓ����`�F�b�N
	for (int nCnt = 1; nCnt < RANK_NUM; nCnt++)
	{
		if (m_aScore[nCnt] == m_aScore[nCnt - 1])
		{// ���O�̏��ʂ̃X�R�A�Ɠ����Ȃ�Ώ��ʂ𑵂���
			m_aRank[nCnt] = m_aRank[nCnt - 1];
		}

		m_apScene2D[nCnt]->SetTex(1, 5, 0, m_aRank[nCnt], 0.0f, 0.0f);
	}
}