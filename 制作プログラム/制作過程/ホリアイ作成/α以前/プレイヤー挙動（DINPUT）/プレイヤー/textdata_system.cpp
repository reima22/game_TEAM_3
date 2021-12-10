//==============================================================================
//
// �e�L�X�g�f�[�^�i�v���C���[�j�Ǘ��ktextdata_player.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "textdata.h"
#include "textdata_system.h"
#include "stdio.h"

//==============================================================================
// �ÓI�����o�ϐ��錾
//==============================================================================
int CTextDataSystem::m_aSystemData[SYSTEMDATA_MAX];

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTextDataSystem::CTextDataSystem()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTextDataSystem::~CTextDataSystem()
{

}

//==============================================================================
// �e�L�X�g�̓ǂݍ���
//==============================================================================
void CTextDataSystem::LoadData(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile;
	char aLoadText[TEXT_NUM];
	char *pLoadText = &aLoadText[0];

	// �ϐ��̏�����
	for (int nCnt = 0; nCnt < SYSTEMDATA_MAX; nCnt++)
	{
		m_aSystemData[nCnt] = 0;
	}

	// �f�[�^�̓ǂݍ���
	pFile = fopen(m_pFileName[TEXTDATA_SYSTEM], "r");

	if (pFile != NULL)
	{ //�t�@�C���W�J�\

		while (strcmp("SYSTEMDATA_END", pLoadText) != 0)
		{
			// ���ړǂݍ���
			fscanf(pFile, "%s", pLoadText);

			// ���ڂɑΉ������ϐ��ւ̊i�[
			if (strcmp("DEFEAT_EASY", pLoadText) == 0)
			{// �ړ����x
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aSystemData[SYSTEMDATA_DEFEAT_EASY]);
			}
			else if (strcmp("DEFEAT_NORMAL", pLoadText) == 0)
			{// �ړ����x
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aSystemData[SYSTEMDATA_DEFEAT_NORMAL]);
			}
			else if (strcmp("DEFEAT_HARD", pLoadText) == 0)
			{// �ړ����x
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aSystemData[SYSTEMDATA_DEFEAT_HARD]);
			}
			else if (strcmp("INVASION_EASY", pLoadText) == 0)
			{// �G�����J�E���g��ŏ��l
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aSystemData[SYSTEMDATA_INVASION_EASY]);
			}
			else if (strcmp("INVASION_NORMAL", pLoadText) == 0)
			{// �G�����J�E���g��ŏ��l
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aSystemData[SYSTEMDATA_INVASION_NORMAL]);
			}
			else if (strcmp("INVASION_HARD", pLoadText) == 0)
			{// �G�����J�E���g��ŏ��l
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aSystemData[SYSTEMDATA_INVASION_HARD]);
			}
			else if (strcmp("ITEMSET_COUNT_EASY", pLoadText) == 0)
			{// �G�����J�E���g��ŏ��l
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aSystemData[SYSTEMDATA_HEALITEM_CNT_EASY]);
			}
			else if (strcmp("ITEMSET_COUNT_NORMAL", pLoadText) == 0)
			{// �G�����J�E���g��ŏ��l
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aSystemData[SYSTEMDATA_HEALITEM_CNT_NORMAL]);
			}
			else if (strcmp("ITEMSET_COUNT_HARD", pLoadText) == 0)
			{// �G�����J�E���g��ŏ��l
				fscanf(pFile, "%s %d", &aLoadText[0], &m_aSystemData[SYSTEMDATA_HEALITEM_CNT_HARD]);
			}
		}

		fclose(pFile);
	}
	else
	{ // �t�@�C���W�J�s��
	}
}