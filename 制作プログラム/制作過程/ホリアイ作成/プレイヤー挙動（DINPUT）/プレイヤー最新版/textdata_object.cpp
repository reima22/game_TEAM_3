//==============================================================================
//
// �e�L�X�g�f�[�^�i3D�I�u�W�F�N�g�j�Ǘ��ktextdata_object.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "textdata.h"
#include "textdata_object.h"
#include "stdio.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTextDataObject::CTextDataObject()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTextDataObject::~CTextDataObject()
{

}

//==============================================================================
// �e�L�X�g�̓ǂݍ���
//==============================================================================
void CTextDataObject::LoadData(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile;
	char aLoadText[TEXT_NUM] = {};
	char *pLoadText = &aLoadText[0];

	int nModelCnt = 0;		// ���f�����̃J�E���g

	m_nNumFile = 0;			// �t�@�C����
	m_nNumObject = 0;		// �z�u����I�u�W�F�N�g��

	// �f�[�^�̓ǂݍ���
	pFile = fopen(m_pFileName[TEXTDATA_OBJECT], "r");

	if (pFile != NULL)
	{ //�t�@�C���W�J�\

	  // �X�N���v�g�ǂݍ��ݏI���܂�
		while (strcmp("END_SCRIPT", pLoadText) != 0)
		{
			// ���ړǂݍ���
			fscanf(pFile, "%s", pLoadText);

			// �ǂݍ��ރ��f����
			if (strcmp("NUM_MODEL", pLoadText) == 0)
			{
				fscanf(pFile, "%s %d", &aLoadText[0], &m_nNumFile);

				// �t�@�C�������A���I�m��
				m_pFileObjectName = new char*[m_nNumFile];

				m_pFileObjectNameLoad = new char*[m_nNumFile];

				// 2�����z��̊m��
				for (int nCnt = 0; nCnt < m_nNumFile; nCnt++)
				{
					m_pFileObjectNameLoad[nCnt] = new char[TEXT_NUM];

					m_pFileObjectName[nCnt] = &m_pFileObjectNameLoad[nCnt][0];
				}
			}

			// ���f���t�@�C����
			if (strcmp("MODEL_FILENAME", pLoadText) == 0)
			{
				// ���f����
				fscanf(pFile, "%s %s", &aLoadText[0], &m_pFileObjectNameLoad[nModelCnt][0]);

				// �J�E���g����
				nModelCnt++;
			}

			// �z�u���̃J�E���g
			if (strcmp("OBJECTSET", pLoadText) == 0)
			{
				char aObjectData[TEXT_NUM] = {};
				char *pObjectData = &aObjectData[0];

				while (strcmp("END_OBJECTSET", pObjectData) != 0)
				{
					// �ǂݍ���
					fscanf(pFile, "%s", &aObjectData[0]);
				}

				m_nNumObject++;		// �I�u�W�F�N�g���̉��Z
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{ // �t�@�C���W�J�s��
		return;
	}

	pFile = NULL;

	// �e�p�����[�^�̓��I�m��
	m_pType = new int[m_nNumObject];			// ���
	m_pObjectInfo = new float*[m_nNumObject];	// �ʒu�E�p�x
	m_pShadowWidth = new float[m_nNumObject];	// �ۉe�̕�
	m_pShadowDepth = new float[m_nNumObject];	// �ۉe�̉��s

	int nCntObject = 0;	// �J�E���g

	// �f�[�^�̓ǂݍ���
	pFile = fopen(m_pFileName[TEXTDATA_OBJECT], "r");

	if (pFile != NULL)
	{ //�t�@�C���W�J�\

		aLoadText[0] = {};

	  // �X�N���v�g�ǂݍ��ݏI���܂�
		while (strcmp("END_SCRIPT", pLoadText) != 0)
		{
			// ���ړǂݍ���
			fscanf(pFile, "%s", pLoadText);

			// �z�u���̓ǂݍ���
			if (strcmp("OBJECTSET", pLoadText) == 0)
			{
				char aObjectData[TEXT_NUM] = {};
				char *pObjectData = &aObjectData[0];

				// �I�u�W�F�N�g���̎�ނ����m��
				m_pObjectInfo[nCntObject] = new float[OBJECTINFO_MAX];

				while (strcmp("END_OBJECTSET", pObjectData) != 0)
				{
					// �ǂݍ���
					fscanf(pFile, "%s", &aObjectData[0]);

					// �e�̃T�C�Y
					if (strcmp("SHADOW", pObjectData) == 0)
					{
						fscanf(pFile, "%s %f %f", &aObjectData[0], &m_pShadowWidth[nCntObject], &m_pShadowDepth[nCntObject]);
					}

					// ���
					if (strcmp("TYPE", pObjectData) == 0)
					{
						fscanf(pFile, "%s %d", &aObjectData[0], &m_pType[nCntObject]);
					}

					// �ʒu
					if (strcmp("POS", pObjectData) == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aObjectData[0],
							&m_pObjectInfo[nCntObject][OBJECTINFO_POS_X],
							&m_pObjectInfo[nCntObject][OBJECTINFO_POS_Y],
							&m_pObjectInfo[nCntObject][OBJECTINFO_POS_Z]);
					}

					// ����
					if (strcmp("ROT", pObjectData) == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aObjectData[0],
							&m_pObjectInfo[nCntObject][OBJECTINFO_ROT_X],
							&m_pObjectInfo[nCntObject][OBJECTINFO_ROT_Y],
							&m_pObjectInfo[nCntObject][OBJECTINFO_ROT_Z]);
					}
				}

				nCntObject++;		// �J�E���g���Z
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
// �f�[�^�̔j��
//==============================================================================
void CTextDataObject::Unload(void)
{
	// �t�@�C�����|�C���^
	if (m_pFileObjectName != NULL)
	{
		delete[] m_pFileObjectName;
		m_pFileObjectName = NULL;
	}

	// �t�@�C�����ǂݍ��݃|�C���^�̔j��
	if (m_pFileObjectNameLoad != NULL)
	{
		for (int nCnt = 0; nCnt < m_nNumFile; nCnt++)
		{
			delete[] m_pFileObjectNameLoad[nCnt];
			m_pFileObjectNameLoad[nCnt] = NULL;
		}

		delete[] m_pFileObjectNameLoad;
		m_pFileObjectNameLoad = NULL;
	}

	// ��ނ̔j��
	//if (m_pType != NULL)
	//{
	//	delete[] m_pType;
	//	m_pType = NULL;
	//}

	// �ʒu�E�p�x�̔j��
	//if (m_pObjectInfo != NULL)
	//{
	//	for (int nCnt = 0; nCnt < m_nNumObject; nCnt++)
	//	{
	//		delete[] m_pObjectInfo[nCnt];
	//		m_pObjectInfo[nCnt] = NULL;
	//	}

	//	delete[] m_pObjectInfo;
	//	m_pObjectInfo = NULL;
	//}

	//// �e�̑傫��
	//if (m_pShadowWidth != NULL)
	//{
	//	delete[] m_pShadowWidth;
	//	m_pShadowWidth = NULL;
	//}
	//if (m_pShadowDepth != NULL)
	//{
	//	delete[] m_pShadowDepth;
	//	m_pShadowDepth = NULL;
	//}
}

//==============================================================================
// �I�u�W�F�N�g�f�[�^�̐���
//==============================================================================
CTextDataObject *CTextDataObject::Create(void)
{
	// �v���C���[�f�[�^�̓ǂݍ���
	CTextDataObject *pDataObject;
	pDataObject = new CTextDataObject;

	// �f�[�^�̃��[�h
	if (pDataObject != NULL)
	{
		pDataObject->LoadData();
	}

	return pDataObject;
}