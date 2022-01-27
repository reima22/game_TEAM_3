//==============================================================================
//
// �e�L�X�g�f�[�^�i�����L���O�j�Ǘ��ktextdata_ranking.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "ranking_score.h"
#include "select.h"
#include "textdata.h"
#include "textdata_ranking.h"
#include "stdio.h"

//==============================================================================
// �ÓI�����o�ϐ��錾
//==============================================================================
int CTextDataRanking::m_aRankingData[RANK_NUM];

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTextDataRanking::CTextDataRanking()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTextDataRanking::~CTextDataRanking()
{

}

//==============================================================================
// �e�L�X�g�̓ǂݍ���
//==============================================================================
void CTextDataRanking::LoadData(void)
{
	// �X�e�[�W�Z���N�g�̏��
	CStageSelect::STAGE_SELECT select = CStageSelect::GetSelectingStage();

	// ���[�J���ϐ��錾
	FILE *pFile;

	// �f�[�^�̓ǂݍ���
	pFile = fopen(m_pFileNameRanking[select], "r");

	if (pFile != NULL)
	{ //�t�@�C���W�J�\
		for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
		{
			fscanf(pFile, "%d", &m_aRankingData[nCnt]);
		}

		fclose(pFile);
	}
	else
	{ // �t�@�C���W�J�s��
	}
}

//==============================================================================
// �e�L�X�g�̏�������
//==============================================================================
void CTextDataRanking::SaveData(void)
{
	// �V�K�����L���O�f�[�^�̎擾
	for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
	{
		m_aRankingData[nCnt] = CRankingScore::GetRankingScore(nCnt);
	}

	// �X�e�[�W�Z���N�g�̏��
	CStageSelect::STAGE_SELECT select = CStageSelect::GetSelectingStage();

	// ���[�J���ϐ��錾
	FILE *pFile;

	// �t�@�C���̓W�J
	pFile = fopen(m_pFileNameRanking[select], "w");

	if (pFile != NULL)
	{ // �t�@�C���W�J�\
		for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
		{
			fprintf(pFile, "%d\n", m_aRankingData[nCnt]);
		}

		fclose(pFile);
	}
	else
	{ // �t�@�C���W�J�s��
	}
}