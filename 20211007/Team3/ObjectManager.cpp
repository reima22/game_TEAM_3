#define _CRT_SECURE_NO_WARNINGS
//=============================================================================
//
// �I�u�W�F�N�g�Ǘ� [ObjectManager.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "ObjectManager.h"
#include "Scaffold.h"
#include "Manager.h"

//*****************************************************************************
// �I�u�W�F�N�g�Ǘ��N���X
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObjectManager::CObjectManager()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObjectManager::~CObjectManager()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CObjectManager::Init(void)
{
	// �t�@�C���ǂݍ���
	Read();

	// �ǂݍ��񂾏������ɑ��ꐶ��
	for (int nCnt = 0; nCnt < (signed)m_scaffoldInfo.size(); nCnt++) {
		CScaffold::Create(
			m_scaffoldInfo[nCnt].pos,
			D3DXToRadian(m_scaffoldInfo[nCnt].rot));
	}

	// ���l�Ƀ��f������
	for (int nCnt = 0; nCnt < (signed)m_modelInfo.size(); nCnt++) {
		CScene3DModel::Create(
			m_modelInfo[nCnt].pos,
			D3DXToRadian(m_modelInfo[nCnt].rot),
			m_modelInfo[nCnt].aModelName);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CObjectManager::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CObjectManager::Update(void)
{

}

//=============================================================================
// �t�@�C���ǂݍ���
//=============================================================================
HRESULT CObjectManager::Read(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	FILE *pFile;

	pFile = fopen("Data/Text/ObjectManager.txt", "r");
	if (pFile != NULL)
	{//	File open succeeded
		bool bStart = false;
		char aReadStr[128];
		
		// ���[�J���Ŏg�����߂̊֐��p�N���X
		class Local {
		public:
			static D3DXVECTOR3 ScanVector3(FILE *pFile) {
				D3DXVECTOR3 vec;
				char aStr[128];
				fscanf(pFile, "%s", &aStr[0]);
				if (strcmp(&aStr[0], "=") == 0) {
					fscanf(pFile, "%f", &vec.x);
					fscanf(pFile, "%f", &vec.y);
					fscanf(pFile, "%f", &vec.z);
				}
				return vec;
			}
		};

		// �t�@�C���̍Ō�܂œǂݍ��݃��[�v
		while (int nReturn = fscanf(pFile, "%s", &aReadStr[0]) != EOF)
		{
			if (bStart)
			{
				// ����̏��ǂݍ���
				if (strcmp(&aReadStr[0], "SCAFFOLD") == 0) {
					SCAFFOLD_INFO scaffoldInfo;

					while (fscanf(pFile, "%s", &aReadStr[0]) != EOF) {
						if (strcmp(&aReadStr[0], "POS") == 0) {
							scaffoldInfo.pos = Local::ScanVector3(pFile);	// �ʒu
						}
						else if (strcmp(&aReadStr[0], "ROT") == 0) {
							scaffoldInfo.rot = Local::ScanVector3(pFile);	// ����
						}
						else if (strcmp(&aReadStr[0], "TYPE") == 0) {
							fscanf(pFile, "%s", &aReadStr[0]);
							if (strcmp(&aReadStr[0], "=") == 0) {
								// ��ނ�ǂݍ���
								fscanf(pFile, "%d", &scaffoldInfo.nType);	// ���
							}
						}
						else if (strcmp(&aReadStr[0], "END_SCAFFOLD") == 0) {
							// �������ɏ����i�[
							m_scaffoldInfo.push_back(scaffoldInfo);
							break;
						}
					}
				}
				// ���f�����̓ǂݍ���
				else if (strcmp(&aReadStr[0], "MODELSET") == 0) {
					MODEL_INFO modelInfo;

					while (fscanf(pFile, "%s", &aReadStr[0]) != EOF) {
						if (strcmp(&aReadStr[0], "POS") == 0) {
							modelInfo.pos = Local::ScanVector3(pFile);	// �ʒu
						}
						else if (strcmp(&aReadStr[0], "ROT") == 0) {
							modelInfo.rot = Local::ScanVector3(pFile);	// ����
						}
						else if (strcmp(&aReadStr[0], "NAME") == 0) {
							fscanf(pFile, "%s", &aReadStr[0]);
							if (strcmp(&aReadStr[0], "=") == 0) {
								fscanf(pFile, "%s", modelInfo.aModelName);	// ���f���̖��O
							}
						}
						else if (strcmp(&aReadStr[0], "END_MODELSET") == 0) {
							m_modelInfo.push_back(modelInfo);
							break;
						}
					}
				}

			}

			// #start�������������
			if (strcmp(&aReadStr[0], "#start") == 0)
				bStart = true;
			else if (strcmp(&aReadStr[0], "#end") == 0)
				break;
		}
		fclose(pFile);
	}
	else return E_FAIL;

	return S_OK;
}