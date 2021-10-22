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
	char aLoadText[TEXT_NUM];
	char *pLoadText = &aLoadText[0];

	int nModelCnt = 0;		// ���f�����̃J�E���g

	m_nNumObject = 0;		// �I�u�W�F�N�g��
	m_nNumObjectIn = 1;		// ���I�m�ۂ��鐔

	// �e�p�����[�^�̓��I�m��
	m_pPos = new D3DXVECTOR3[m_nNumObjectIn];
	m_pRot = new D3DXVECTOR3[m_nNumObjectIn];
	m_pType = new int[m_nNumObjectIn];

	// �f�[�^�̓ǂݍ���
	pFile = fopen(m_pFileName[TEXTDATA_OBJECT], "r");

	if (pFile != NULL)
	{ //�t�@�C���W�J�\

	  // �X�N���v�g�ǂݍ��ݏI���܂�
		while (strcmp("END_SCRIPT", pLoadText) != 0)
		{
			// ���ړǂݍ���
			fscanf(pFile, "%s", pLoadText);

			// ���f����
			if (strcmp("NUM_MODEL", pLoadText) == 0)
			{
				fscanf(pFile, "%s %d", &aLoadText[0], &m_nNumModel);

				// ���f�������A���I�m��
				m_pFileObjectName = new char*[m_nNumModel];

				m_pFileObjectNameLoad = new char*[m_nNumModel];

				// 2�����z��̊m��
				for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
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

			// ���f�����̓ǂݍ���
			if (strcmp("OBJECTSET", pLoadText) == 0)
			{
				char aObjectData[TEXT_NUM] = {};
				char *pObjectData = &aObjectData[0];

				while (strcmp("END_OBJECTSET", pObjectData) != 0)
				{
					// �ǂݍ���
					fscanf(pFile, "%s", &aObjectData[0]);

					// ���
					if (strcmp("TYPE", pObjectData) == 0)
					{
						fscanf(pFile, "%s %d", &aObjectData[0], &m_pType[m_nNumObject]);
					}

					// �ʒu
					if (strcmp("POS", pObjectData) == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aObjectData[0], 
							&m_pPos[m_nNumObject].x,
							&m_pPos[m_nNumObject].y,
							&m_pPos[m_nNumObject].z);
					}

					// ����
					if (strcmp("ROT", pObjectData) == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aObjectData[0],
							&m_pRot[m_nNumObject].x,
							&m_pRot[m_nNumObject].y,
							&m_pRot[m_nNumObject].z);
					}
				}

				m_nNumObjectIn++;	// �m�ې��̉��Z
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
}

//==============================================================================
// �f�[�^�̔j��
//==============================================================================
void CTextDataObject::Uninit(void)
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
		for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
		{
			delete[] m_pFileObjectNameLoad[nCnt];
		}

		delete[] m_pFileObjectNameLoad;
		m_pFileObjectNameLoad = NULL;
	}

	// ��ނ̔j��
	if (m_pType != NULL)
	{
		delete m_pType;
		m_pType = NULL;
	}

	// �ʒu�̔j��
	if (m_pPos != NULL)
	{
		delete m_pPos;
		m_pPos = NULL;
	}

	// �����̔j��
	if (m_pRot != NULL)
	{
		delete m_pRot;
		m_pRot = NULL;
	}
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