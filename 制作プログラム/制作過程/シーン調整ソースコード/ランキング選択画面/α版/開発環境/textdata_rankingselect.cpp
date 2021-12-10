//==============================================================================
//
// �e�L�X�g�f�[�^�i�����L���O�j�Ǘ��ktextdata_ranking.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "ranking_score.h"
#include "textdata.h"
#include "textdata_rankingselect.h"
#include "stdio.h"
#include "select.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTextDataRankingSelect::CTextDataRankingSelect()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTextDataRankingSelect::~CTextDataRankingSelect()
{

}

//==============================================================================
// �I���e�L�X�g�̓ǂݍ���
//==============================================================================
void CTextDataRankingSelect::LoadData(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile;
	char aLoadText[TEXT_NUM];
	char *pLoadText = &aLoadText[0];

	// �f�[�^�̓ǂݍ���
	pFile = fopen(m_pFileName[TEXTDATA_RANKINGSELECT], "r");

	if (pFile != NULL)
	{ //�t�@�C���W�J�\

		// �X�N���v�g�ǂݍ��ݏI���܂�
		while (strcmp("END_SCRIPT", pLoadText) != 0)
		{
			// ���ړǂݍ���
			fscanf(pFile, "%s", pLoadText);

			// �I�����u���g���C�v
			if (strcmp("SETSELECT_RETRY", pLoadText) == 0)
			{
				// ���[�J���ϐ��錾
				char aRetry[TEXT_NUM] = {};
				char *pRetry = &aRetry[0];

				while (strcmp("END_SETSELECT_RETRY", pRetry) != 0)
				{
					fscanf(pFile, "%s", &aRetry[0]);

					// �g�p�e�N�X�`��
					if (strcmp("TEXTYPE", pRetry) == 0)
					{
						fscanf(pFile, "%s %d", &aRetry[0], &m_aIdxTex[RANKINGPOLY_RETRY]);
					}

					// �ʒu���
					if (strcmp("POS", pRetry) == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aRetry[0],
							&m_aPos[RANKINGPOLY_RETRY].x,
							&m_aPos[RANKINGPOLY_RETRY].y,
							&m_aPos[RANKINGPOLY_RETRY].z);
					}

					// �T�C�Y���
					if (strcmp("SIZE", pRetry) == 0)
					{
						fscanf(pFile, "%s %f %f", &aRetry[0],
							&m_aSize[RANKINGPOLY_RETRY].x,
							&m_aSize[RANKINGPOLY_RETRY].y);
					}
				}
			}

			// �I�����u�I���v
			if (strcmp("SETSELECT_QUIT", pLoadText) == 0)
			{
				// ���[�J���ϐ��錾
				char aQuit[TEXT_NUM] = {};
				char *pQuit = &aQuit[0];

				while (strcmp("END_SETSELECT_QUIT", pQuit) != 0)
				{
					fscanf(pFile, "%s", &aQuit[0]);

					// �g�p�e�N�X�`��
					if (strcmp("TEXTYPE", pQuit) == 0)
					{
						fscanf(pFile, "%s %d", &aQuit[0], &m_aIdxTex[RANKINGPOLY_QUIT]);
					}

					// �ʒu���
					if (strcmp("POS", pQuit) == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aQuit[0],
							&m_aPos[RANKINGPOLY_QUIT].x,
							&m_aPos[RANKINGPOLY_QUIT].y,
							&m_aPos[RANKINGPOLY_QUIT].z);
					}

					// �T�C�Y���
					if (strcmp("SIZE", pQuit) == 0)
					{
						fscanf(pFile, "%s %f %f", &aQuit[0],
							&m_aSize[RANKINGPOLY_QUIT].x,
							&m_aSize[RANKINGPOLY_QUIT].y);
					}
				}
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{ // �t�@�C���W�J�s��
		return;
	}
}

//==============================================================================
// �I���e�L�X�g�f�[�^�̔j��
//==============================================================================
void CTextDataRankingSelect::Unload(void)
{
	// �l�̔j��
	for (int nCnt = 0; nCnt < RANKINGPOLY_MAX; nCnt++)
	{
		m_aIdxTex[nCnt] = 0;
		m_aPos[nCnt] = {};
		m_aSize[nCnt] = {};
	}
}

//==============================================================================
// �I���f�[�^�̐���
//==============================================================================
CTextDataRankingSelect *CTextDataRankingSelect::Create(void)
{
	// �����L���O�f�[�^�̓ǂݍ���
	CTextDataRankingSelect *pDataRankingSelect;
	pDataRankingSelect = new CTextDataRankingSelect;

	// �f�[�^�̃��[�h
	if (pDataRankingSelect != NULL)
	{
		pDataRankingSelect->LoadData();
	}

	return pDataRankingSelect;
}