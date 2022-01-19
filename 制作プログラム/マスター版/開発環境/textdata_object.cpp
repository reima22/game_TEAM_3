//==============================================================================
//
// �e�L�X�g�f�[�^�i3D�I�u�W�F�N�g�j�Ǘ��ktextdata_object.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
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
void CTextDataObject::LoadData(STAGEINFO stage)
{
	// ���[�J���ϐ��錾
	FILE *pFile;
	char aLoadText[TEXT_NUM] = {};
	char *pLoadText = &aLoadText[0];

	int nModelCnt = 0;		// ���f�����̃J�E���g
	m_nNumFile = 0;			// �t�@�C����
	m_nNumObject = 0;		// �z�u����I�u�W�F�N�g��

	// �f�[�^�̓ǂݍ���
	pFile = fopen(m_pFileNameObj[stage], "r");

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

	// �ēǂݍ��݊J�n
	pFile = NULL;

	// �e�p�����[�^�̓��I�m��
	m_pType = new int[m_nNumObject];							// ���
	m_pPos = new D3DXVECTOR3[m_nNumObject];						// �ʒu
	m_pRot = new D3DXVECTOR3[m_nNumObject];						// �p�x
	m_pShadowSize = new D3DXVECTOR2[m_nNumObject];				// �e�̃T�C�Y

	m_pObjAttribute = new CObject::OBJATTRIBUTE[m_nNumObject];	// �I�u�W�F�N�g�̎��
	m_pMoveType = new CObject::MOVETYPE[m_nNumObject];			// �ړ��p�^�[��
	m_pMovePower = new float[m_nNumObject];						// �ړ��͂̊���

	for(int nCnt = 0; nCnt < m_nNumObject; nCnt++)
	{// �����͕��̑Ή�
		m_pObjAttribute[nCnt] = (CObject::OBJATTRIBUTE)0;
		m_pMoveType[nCnt] = (CObject::MOVETYPE)0;
		m_pMovePower[nCnt] = 1.0f;
	}

	int nCntObject = 0;	// �J�E���g

	// �f�[�^�̓ǂݍ���
	pFile = fopen(m_pFileNameObj[stage], "r");

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

				while (strcmp("END_OBJECTSET", pObjectData) != 0)
				{
					// �ǂݍ���
					fscanf(pFile, "%s", &aObjectData[0]);

					// �e�̃T�C�Y
					if (strcmp("SHADOW", pObjectData) == 0)
					{
						fscanf(pFile, "%s %f %f", &aObjectData[0], &m_pShadowSize[nCntObject].x, &m_pShadowSize[nCntObject].y);
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
							&m_pPos[nCntObject].x,
							&m_pPos[nCntObject].y,
							&m_pPos[nCntObject].z);
					}

					// ����
					if (strcmp("ROT", pObjectData) == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aObjectData[0],
							&m_pRot[nCntObject].x,
							&m_pRot[nCntObject].y,
							&m_pRot[nCntObject].z);
					}

					// �I�u�W�F�N�g�̑���
					if (strcmp("OBJATTRIBUTE", pObjectData) == 0)
					{
						fscanf(pFile, "%s %d", &aObjectData[0], &m_pObjAttribute[nCntObject]);
					}

					// �ړ��p�^�[��
					if (strcmp("MOVETYPE", pObjectData) == 0)
					{
						fscanf(pFile, "%s %d", &aObjectData[0], &m_pMoveType[nCntObject]);
					}

					// �ړ��͂̒l
					if (strcmp("MOVEPOWER", pObjectData) == 0)
					{
						fscanf(pFile, "%s %f", &aObjectData[0], &m_pMovePower[nCntObject]);

						m_pMovePower[nCntObject] /= 100.0f;
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
	// �t�@�C�����|�C���^�̊J��
	if (m_pFileObjectName != NULL)
	{
		delete[] m_pFileObjectName;
		m_pFileObjectName = NULL;
	}

	// �t�@�C�����ǂݍ��݃|�C���^�̊J��
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

	// ��ނ̊J��
	if (m_pType != NULL)
	{
		delete[] m_pType;
		m_pType = NULL;
	}

	// �ʒu�̊J��
	if (m_pPos != NULL)
	{
		delete[] m_pPos;
		m_pPos = NULL;
	}

	// �p�x�̊J��
	if (m_pRot != NULL)
	{
		delete[] m_pRot;
		m_pRot = NULL;
	}

	// �e�̑傫���̊J��
	if (m_pShadowSize != NULL)
	{
		delete[] m_pShadowSize;
		m_pShadowSize = NULL;
	}

	// �I�u�W�F�N�g�̎�ނ̊J��
	if (m_pObjAttribute != NULL)
	{
		delete[] m_pObjAttribute;
		m_pObjAttribute = NULL;
	}

	// �ړ��p�^�[���̊J��
	if (m_pMoveType != NULL)
	{
		delete[] m_pMoveType;
		m_pMoveType = NULL;
	}

	// �ړ��͂̊����̊J��
	if (m_pMovePower != NULL)
	{
		delete[] m_pMovePower;
		m_pMovePower = NULL;
	}
}

//==============================================================================
// �I�u�W�F�N�g�f�[�^�̐���
//==============================================================================
CTextDataObject *CTextDataObject::Create(STAGEINFO stage)
{
	// �v���C���[�f�[�^�̓ǂݍ���
	CTextDataObject *pDataObject;
	pDataObject = new CTextDataObject;

	// �f�[�^�̃��[�h
	if (pDataObject != NULL)
	{
		pDataObject->LoadData(stage);
	}

	return pDataObject;
}