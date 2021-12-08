//==============================================================================
//
// �e�L�X�g�f�[�^�i�|�[�Y�j�Ǘ��ktextdata_pause.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "textdata.h"
#include "textdata_pause.h"
#include "stdio.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTextDataPause::CTextDataPause()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTextDataPause::~CTextDataPause()
{

}

//==============================================================================
// �e�L�X�g�̓ǂݍ���
//==============================================================================
void CTextDataPause::LoadData(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile;
	char aLoadText[TEXT_NUM];
	char *pLoadText = &aLoadText[0];

	// �f�[�^�̓ǂݍ���
	pFile = fopen(m_pFileName[TEXTDATA_PAUSE], "r");

	if (pFile != NULL)
	{ //�t�@�C���W�J�\

	  // �X�N���v�g�ǂݍ��ݏI���܂�
		while (strcmp("END_SCRIPT", pLoadText) != 0)
		{
			// ���ړǂݍ���
			fscanf(pFile, "%s", pLoadText);

			// �|�[�Y�E�B���h�E
			if (strcmp("SETBASE", pLoadText) == 0)
			{
				// ���[�J���ϐ��錾
				char aBase[TEXT_NUM] = {};
				char *pBase = &aBase[0];

				while (strcmp("END_SETBASE", pBase) != 0)
				{
					fscanf(pFile, "%s", &aBase[0]);

					// �g�p�e�N�X�`��
					if (strcmp("TEXTYPE", pBase) == 0)
					{
						fscanf(pFile, "%s %d", &aBase[0], &m_aIdxTex[PAUSEPOLY_BASE]);
					}

					// �ʒu���
					if (strcmp("POS", pBase) == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aBase[0],
							&m_aPos[PAUSEPOLY_BASE].x,
							&m_aPos[PAUSEPOLY_BASE].y,
							&m_aPos[PAUSEPOLY_BASE].z);
					}

					// �T�C�Y���
					if (strcmp("SIZE", pBase) == 0)
					{
						fscanf(pFile, "%s %f %f", &aBase[0],
							&m_aSize[PAUSEPOLY_BASE].x,
							&m_aSize[PAUSEPOLY_BASE].y);
					}
				}			
			}

			// �I�����u�R���e�j���[�v
			if (strcmp("SETSELECT_CONTINUE", pLoadText) == 0)
			{
				// ���[�J���ϐ��錾
				char aContinue[TEXT_NUM] = {};
				char *pContinue = &aContinue[0];

				while (strcmp("END_SETSELECT_CONTINUE", pContinue) != 0)
				{
					fscanf(pFile, "%s", &aContinue[0]);

					// �g�p�e�N�X�`��
					if (strcmp("TEXTYPE", pContinue) == 0)
					{
						fscanf(pFile, "%s %d", &aContinue[0], &m_aIdxTex[PAUSEPOLY_CONTINUE]);
					}

					// �ʒu���
					if (strcmp("POS", pContinue) == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aContinue[0],
							&m_aPos[PAUSEPOLY_CONTINUE].x,
							&m_aPos[PAUSEPOLY_CONTINUE].y,
							&m_aPos[PAUSEPOLY_CONTINUE].z);
					}

					// �T�C�Y���
					if (strcmp("SIZE", pContinue) == 0)
					{
						fscanf(pFile, "%s %f %f", &aContinue[0],
							&m_aSize[PAUSEPOLY_CONTINUE].x,
							&m_aSize[PAUSEPOLY_CONTINUE].y);
					}
				}			
			}

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
						fscanf(pFile, "%s %d", &aRetry[0], &m_aIdxTex[PAUSEPOLY_RETRY]);
					}

					// �ʒu���
					if (strcmp("POS", pRetry) == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aRetry[0],
							&m_aPos[PAUSEPOLY_RETRY].x,
							&m_aPos[PAUSEPOLY_RETRY].y,
							&m_aPos[PAUSEPOLY_RETRY].z);
					}

					// �T�C�Y���
					if (strcmp("SIZE", pRetry) == 0)
					{
						fscanf(pFile, "%s %f %f", &aRetry[0],
							&m_aSize[PAUSEPOLY_RETRY].x,
							&m_aSize[PAUSEPOLY_RETRY].y);
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
						fscanf(pFile, "%s %d", &aQuit[0], &m_aIdxTex[PAUSEPOLY_QUIT]);
					}

					// �ʒu���
					if (strcmp("POS", pQuit) == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aQuit[0],
							&m_aPos[PAUSEPOLY_QUIT].x,
							&m_aPos[PAUSEPOLY_QUIT].y,
							&m_aPos[PAUSEPOLY_QUIT].z);
					}

					// �T�C�Y���
					if (strcmp("SIZE", pQuit) == 0)
					{
						fscanf(pFile, "%s %f %f", &aQuit[0],
							&m_aSize[PAUSEPOLY_QUIT].x,
							&m_aSize[PAUSEPOLY_QUIT].y);
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
// �|�[�Y�f�[�^�̔j��
//==============================================================================
void CTextDataPause::Unload(void)
{
	// �l�̔j��
	for (int nCnt = 0; nCnt < PAUSEPOLY_MAX; nCnt++)
	{
		m_aIdxTex[nCnt] = 0;
		m_aPos[nCnt] = {};
		m_aSize[nCnt] = {};
	}
}

//==============================================================================
// �|�[�Y�f�[�^�̐���
//==============================================================================
CTextDataPause *CTextDataPause::Create(void)
{
	// �v���C���[�f�[�^�̓ǂݍ���
	CTextDataPause *pDataPause;
	pDataPause = new CTextDataPause;

	// �f�[�^�̃��[�h
	if (pDataPause != NULL)
	{
		pDataPause->LoadData();
	}

	return pDataPause;
}