//==============================================================================
//
// �e�L�X�g�f�[�^�i�e�N�X�`���j�Ǘ��ktextdata_texture.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "textdata.h"
#include "textdata_texture.h"
#include "stdio.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTextDataTexture::CTextDataTexture()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTextDataTexture::~CTextDataTexture()
{

}

//==============================================================================
// �e�L�X�g�̓ǂݍ���
//==============================================================================
void CTextDataTexture::LoadData(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile;
	char aLoadText[TEXT_NUM];
	char *pLoadText = &aLoadText[0];
	int nTexCnt = 0;
	m_nNumTexture = 0;

	// �f�[�^�̓ǂݍ���
	pFile = fopen(m_pFileName[TEXTDATA_TEXTURE], "r");

	if (pFile != NULL)
	{ //�t�@�C���W�J�\

	  // �X�N���v�g�ǂݍ��ݏI���܂�
		while (strcmp("END_SCRIPT", pLoadText) != 0)
		{
			// ���ړǂݍ���
			fscanf(pFile, "%s", pLoadText);

			// �e�N�X�`����
			if (strcmp("NUM_TEXTURE", pLoadText) == 0)
			{
				fscanf(pFile, "%s %d", &aLoadText[0], &m_nNumTexture);

				// �e�N�X�`�������A���I�m��
				m_pFileTextureName = new char*[m_nNumTexture];
				m_pTypeCheck = new char*[m_nNumTexture];
				m_pIdx = new int[m_nNumTexture];

				// 2�����z��̊m��
				for (int nCnt = 0; nCnt < m_nNumTexture; nCnt++)
				{
					m_pFileTextureName[nCnt] = new char[TEXT_NUM];
					m_pTypeCheck[nCnt] = new char[TEXT_NUM];
				}
			}

			// �t�@�C����
			if (strcmp("TEXTURE_FILENAME", pLoadText) == 0)
			{
				// �t�@�C����
				fscanf(pFile, "%s %s", &aLoadText[0], &m_pFileTextureName[nTexCnt][0]);

				// ���ʗp������
				fscanf(pFile, "%s", &m_pTypeCheck[nTexCnt][0]);

				// �C���f�b�N�X�̊��蓖��
				m_pIdx[nTexCnt] = nTexCnt;

				// �J�E���g����
				nTexCnt++;
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
// �e�N�X�`���f�[�^�̔j��
//==============================================================================
void CTextDataTexture::Unload(void)
{
	
	for (int nCnt = 0; nCnt < m_nNumTexture; nCnt++)
	{
		// �e�L�X�g�f�[�^�̔j��
		if ((char*)m_pFileTextureName[nCnt] != NULL)
		{
			delete[] (char*)m_pFileTextureName[nCnt];
			m_pFileTextureName[nCnt] = NULL;
		}

		// ��ގ��ʗp�ϐ��̊J��
		if ((char*)m_pTypeCheck[nCnt] != NULL)
		{
			delete[](char*)m_pTypeCheck[nCnt];
			m_pTypeCheck[nCnt] = NULL;
		}
	}

	// �e�N�X�`���t�@�C�����̊J��
	delete[] m_pFileTextureName;
	m_pFileTextureName = NULL;

	// �e�N�X�`���t�@�C�����̊J��
	delete[] m_pTypeCheck;
	m_pTypeCheck = NULL;
}

//==============================================================================
// �e�N�X�`���f�[�^�̐���
//==============================================================================
CTextDataTexture *CTextDataTexture::Create(void)
{
	// �v���C���[�f�[�^�̓ǂݍ���
	CTextDataTexture *pDataTexture;
	pDataTexture = new CTextDataTexture;

	// �f�[�^�̃��[�h
	if (pDataTexture != NULL)
	{
		pDataTexture->LoadData();
	}

	return pDataTexture;
}