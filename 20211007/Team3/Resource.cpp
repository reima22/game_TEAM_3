//===================================================================
//ImplementationFile: ResourceManager.cpp
//Author : Yo jitaku
//===================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "Resource.h"
#include "Renderer.h"

//*******************************************************************
//����������
//*******************************************************************
HRESULT CResourceManager::Init()
{
	m_pRender = CRenderer::GetInstance();
	m_pDevice = m_pRender->GetDevice();

	if (FAILED(TextureLoader("Data/Txt/Texture.txt"))) return E_FAIL;
	//if (FAILED(SoundLoader("Data/Txt/Sound.txt"))) return E_FAIL;
	if (FAILED(ModelLoader("Data/Txt/Model.txt"))) return E_FAIL;
	if (FAILED(ModelLoaderPlus("Data/Txt/PlayerModel.txt"))) return E_FAIL;
	return S_OK;
}

//*******************************************************************
//�������̉��
//*******************************************************************
HRESULT CResourceManager::Uninit()
{
	//for (auto count : m_Sound_Map)
	//	delete count.second;
	for (auto count : m_Model_Map)
		delete count.second;
	for (auto count : m_PartsModel_Map)
		delete count.second;
	//m_Sound_Map.clear();
	m_Model_Map.clear();
	m_PartsModel_Map.clear();
	return S_OK;
}

//*******************************************************************
//�摜�t�@�C���̓ǂݍ���
//*******************************************************************
HRESULT CResourceManager::TextureLoader(string filename)
{
	LPDIRECT3DTEXTURE9 pTexture = nullptr;
	FILE *pFile = fopen(filename.data(), "r");
	if (pFile == NULL)
		return E_FAIL;

	bool bReadStart = false;
	char aLine[128];
	char aID[128];
	char aAddress[128];
	while (fgets(aLine, 128, pFile) != NULL)
	{
		if (!bReadStart && strcmp(aLine, "#START\n") == 0)//START�}�[�N��T��
		{
			bReadStart = true;
			continue;
		}
		else if (strcmp(aLine, "#END") == 0 || strcmp(aLine, "#END\n") == 0)//END�}�[�N��T��
		{
			fclose(pFile);
			break;
		}
		else if (bReadStart)
		{
			sscanf(aLine, "%s%s", aID, aAddress);
			if (FAILED(D3DXCreateTextureFromFile(m_pDevice, aAddress, &pTexture)))//�f�o�C�X���g���ă��\�[�X�����
				return E_FAIL;
			m_Texture_Map.insert(unordered_map<string, LPDIRECT3DTEXTURE9>::value_type(aID, pTexture));//map�ɕt��������
		}
	}
	return S_OK;
}

//*******************************************************************
//�����t�@�C���̓ǂݍ���
//*******************************************************************
//HRESULT CResourceManager::SoundLoader(string filename)
//{
//	CSound* pSound = CSound::GetInstance();
//	IXAudio2* pXAudio2 = pSound->GetXAudio2();
//
//	FILE *pFile = fopen(filename.data(), "r");
//	if (pFile == NULL)
//		return E_FAIL;
//
//	bool bReadStart = false;
//	char aLine[128];
//	char aID[128];
//	char aAddress[128];
//	while (fgets(aLine, 128, pFile) != NULL)
//	{
//		if (!bReadStart && strcmp(aLine, "#START\n") == 0)//START�}�[�N��T��
//		{
//			bReadStart = true;
//			continue;
//		}
//		else if (strcmp(aLine, "#END") == 0 || strcmp(aLine, "#END\n") == 0)//END�}�[�N��T��
//		{
//			fclose(pFile);
//			break;
//		}
//		else if (bReadStart)
//		{
//			HANDLE hFile;
//			DWORD dwChunkSize = 0;
//			DWORD dwChunkPosition = 0;
//			DWORD dwFiletype;
//			WAVEFORMATEXTENSIBLE wfx;
//			XAUDIO2_BUFFER buffer;
//			CSoundData* pSoundData = new CSoundData;
//			// �o�b�t�@�̃N���A
//			memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
//			memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
//			sscanf(aLine, "%s%s", aID, aAddress);
//			// �T�E���h�f�[�^�t�@�C���̐���
//			hFile = CreateFile(aAddress, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
//			if (hFile == INVALID_HANDLE_VALUE)
//				return HRESULT_FROM_WIN32(GetLastError());
//			if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
//				return HRESULT_FROM_WIN32(GetLastError());
//			// WAVE�t�@�C���̃`�F�b�N
//			if (FAILED(CheckSoundChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition)))
//				return S_FALSE;
//			if (FAILED(ReadSoundChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition)))
//				return S_FALSE;
//			if (dwFiletype != 'EVAW')
//				return S_FALSE;
//			// �t�H�[�}�b�g�`�F�b�N
//			if (FAILED(CheckSoundChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition)))
//				return S_FALSE;
//			if (FAILED(ReadSoundChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition)))
//				return S_FALSE;
//			// �I�[�f�B�I�f�[�^�ǂݍ���
//			if (FAILED(CheckSoundChunk(hFile, 'atad', &pSoundData->m_SizeAudio, &dwChunkPosition)))
//				return S_FALSE;
//			pSoundData->m_pDataAudio = (BYTE*)malloc(pSoundData->m_SizeAudio);
//			if (FAILED(ReadSoundChunkData(hFile, pSoundData->m_pDataAudio, pSoundData->m_SizeAudio, dwChunkPosition)))
//				return S_FALSE;
//			// �\�[�X�{�C�X�̐���
//			if (FAILED(pXAudio2->CreateSourceVoice(&pSoundData->m_pSourceVoice, &(wfx.Format))))
//				return S_FALSE;
//
//			// �o�b�t�@�̒l�ݒ�
//			memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
//			buffer.AudioBytes = pSoundData->m_SizeAudio;
//			buffer.pAudioData = pSoundData->m_pDataAudio;
//			buffer.Flags = XAUDIO2_END_OF_STREAM;
//			buffer.LoopCount = 0;
//
//			// �I�[�f�B�I�o�b�t�@�̓o�^
//			pSoundData->m_pSourceVoice->SubmitSourceBuffer(&buffer);
//
//			// �t�@�C�����N���[�Y
//			CloseHandle(hFile);
//
//			m_Sound_Map.insert(unordered_map<string, CSoundData*>::value_type(aID, pSoundData));//map�ɕt��������
//		}
//	}
//	return S_OK;
//}

//*******************************************************************
// �`�����N�̃`�F�b�N
//*******************************************************************
//HRESULT CResourceManager::CheckSoundChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
//{
//	HRESULT hr = S_OK;
//	DWORD dwRead;
//	DWORD dwChunkType;
//	DWORD dwChunkDataSize;
//	DWORD dwRIFFDataSize = 0;
//	DWORD dwFileType;
//	DWORD dwBytesRead = 0;
//	DWORD dwOffset = 0;
//
//	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
//	{// �t�@�C���|�C���^��擪�Ɉړ�
//		return HRESULT_FROM_WIN32(GetLastError());
//	}
//
//	while (hr == S_OK)
//	{
//		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
//		{// �`�����N�̓ǂݍ���
//			hr = HRESULT_FROM_WIN32(GetLastError());
//		}
//
//		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
//		{// �`�����N�f�[�^�̓ǂݍ���
//			hr = HRESULT_FROM_WIN32(GetLastError());
//		}
//
//		switch (dwChunkType)
//		{
//		case 'FFIR':
//			dwRIFFDataSize = dwChunkDataSize;
//			dwChunkDataSize = 4;
//			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
//			{// �t�@�C���^�C�v�̓ǂݍ���
//				hr = HRESULT_FROM_WIN32(GetLastError());
//			}
//			break;
//
//		default:
//			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
//			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
//				return HRESULT_FROM_WIN32(GetLastError());
//			}
//		}
//
//		dwOffset += sizeof(DWORD) * 2;
//		if (dwChunkType == format)
//		{
//			*pChunkSize = dwChunkDataSize;
//			*pChunkDataPosition = dwOffset;
//
//			return S_OK;
//		}
//
//		dwOffset += dwChunkDataSize;
//		if (dwBytesRead >= dwRIFFDataSize)
//		{
//			return S_FALSE;
//		}
//	}
//
//	return S_OK;
//}

//*******************************************************************
// �`�����N�f�[�^�̓ǂݍ���
//*******************************************************************
//HRESULT CResourceManager::ReadSoundChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
//{
//	DWORD dwRead;
//
//	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
//	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
//		return HRESULT_FROM_WIN32(GetLastError());
//	}
//
//	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
//	{// �f�[�^�̓ǂݍ���
//		return HRESULT_FROM_WIN32(GetLastError());
//	}
//
//	return S_OK;
//}

//*******************************************************************
//���[�h�t�@�C���̓ǂݍ���
//*******************************************************************
HRESULT CResourceManager::ModelLoader(string filename)
{
	LPDIRECT3DTEXTURE9 pTexture = nullptr;
	FILE *pFile = fopen(filename.data(), "r");
	if (pFile == NULL)
		return E_FAIL;

	bool bReadStart = false;
	char aLine[128];
	char aID[128];
	char aAddress[128];
	while (fgets(aLine, 128, pFile) != NULL)
	{
		if (!bReadStart && strcmp(aLine, "#START\n") == 0)//START�}�[�N��T��
		{
			bReadStart = true;
			continue;
		}
		else if (strcmp(aLine, "#END") == 0 || strcmp(aLine, "#END\n") == 0)//END�}�[�N��T��
		{
			fclose(pFile);
			break;
		}
		else if (bReadStart)
		{
			sscanf(aLine, "%s%s", aID, aAddress);
			CModelData* m_pModelData = new CModelData;
			if (FAILED(D3DXLoadMeshFromX(
				aAddress,
				D3DXMESH_SYSTEMMEM,
				m_pDevice,
				NULL,
				&m_pModelData->Xfile_Materials,
				NULL,
				&m_pModelData->Xfile_MaterialNum,
				&m_pModelData->Xfile_Mesh)))//���b�V�������
				return E_FAIL;

			//�ގ��ɂ���
			D3DXMATERIAL* pMaterials = (D3DXMATERIAL*)m_pModelData->Xfile_Materials->GetBufferPointer();
			for (DWORD nCnt = 0; nCnt < (int)m_pModelData->Xfile_MaterialNum; nCnt++)
			{
				if (pMaterials[nCnt].pTextureFilename != NULL)
				{
					char* file_name = pMaterials[nCnt].pTextureFilename;
					LPDIRECT3DTEXTURE9 texture = NULL;
					D3DXCreateTextureFromFileA(m_pDevice,
						file_name,
						&m_pModelData->g_Textures[nCnt]);
				}
				else
					m_pModelData->g_Textures[nCnt] = nullptr;
			}
			m_Model_Map.insert(unordered_map<string, CModelData*>::value_type(aID, m_pModelData));//map�ɕt��������
		}
	}
	return S_OK;
}

//*******************************************************************
//���[�V���������[�h�̓ǂݍ���
//*******************************************************************
HRESULT CResourceManager::ModelLoaderPlus(string filename)
{
	LPDIRECT3DTEXTURE9 pTexture = nullptr;
	FILE *pFile = fopen(filename.data(), "r");
	if (pFile == NULL)
		return E_FAIL;

	int nModelParts = 0;
	int nCntParts = 0;
	int nIndex = 0;
	int nLoop = 0;
	bool bReadStart = false;
	bool bReadXfile = false;
	bool bReadPartsSet = false;
	bool bReadMotion = false;
	bool bReadKey = false;
	char aLine[128];
	char aID[128];
	char aText[128];
	char aAddress[128];
	char aMotionName[128];
	CModelDataPlus* m_pModelData = new CModelDataPlus;
	while (fgets(aLine, 128, pFile) != NULL)
	{
		if (!bReadStart && strcmp(aLine, "#START\n") == 0)//START�}�[�N��T��
		{
			bReadStart = true;
			continue;
		}
		else if (strcmp(aLine, "#END") == 0 || strcmp(aLine, "#END\n") == 0)//END�}�[�N��T��
		{
			fclose(pFile);
			break;
		}
		else if (bReadStart)
		{
			sscanf(aLine, "%s", &aText);
			if (strcmp(aText, "MODEL_NAME") == 0)//���[�h�̖��O
			{
				sscanf(aLine, "%s = %s", aText, &aID);
				continue;
			}
			if (strcmp(aText, "PARTS_NUM") == 0)//�p�[�c�̑���
			{
				sscanf(aLine, "%s = %d", aText, &m_pModelData->m_nParts);
				continue;
			}
			if (strcmp(aText, "#XFILE") == 0)//�p�[�c��X�t�@�C��
			{
				bReadXfile = true;
				continue;
			}
			if (strcmp(aText, "#END_XFILE") == 0)
			{
				bReadXfile = false;
				continue;
			}
			if (strcmp(aText, "#PARTS_SET") == 0)//�p�[�c�̏��������
			{
				bReadPartsSet = true;
				continue;
			}
			if (strcmp(aText, "#END_PARTS_SET") == 0)
			{
				bReadPartsSet = false;
				continue;
			}
			if (strcmp(aText, "#MOTION_SET") == 0)//�p�[�c�̃��[�V�������
			{
				bReadMotion = true;
				continue;
			}
			if (strcmp(aText, "#END_MOTION_SET") == 0)
			{
				bReadMotion = false;
				m_pModelData->m_Motion_Map.insert(unordered_map<string, CMotionData>::value_type(aMotionName, m_pModelData->m_MotionData));//map�ɕt��������
				continue;
			}

			//Xfile
			if (bReadXfile)
			{
				sscanf(aLine, "%s%s", &m_pModelData->m_PartsData.m_sName, aAddress);
				if (FAILED(D3DXLoadMeshFromX(
					aAddress,
					D3DXMESH_SYSTEMMEM,
					m_pDevice,
					NULL,
					&m_pModelData->m_PartsData.Xfile_Materials,
					NULL,
					&m_pModelData->m_PartsData.Xfile_MaterialNum,
					&m_pModelData->m_PartsData.Xfile_Mesh)))//X�t�@�C���̓ǂݍ���
					return E_FAIL;
				//�ގ��ɂ���
				D3DXMATERIAL* pMaterials = (D3DXMATERIAL*)m_pModelData->m_PartsData.Xfile_Materials->GetBufferPointer();
				for (DWORD nCnt = 0; nCnt < (int)m_pModelData->m_PartsData.Xfile_MaterialNum; nCnt++)
				{
					if (pMaterials[nCnt].pTextureFilename != NULL)
					{
						char* file_name = pMaterials[nCnt].pTextureFilename;
						LPDIRECT3DTEXTURE9 texture = NULL;
						D3DXCreateTextureFromFileA(m_pDevice,
							file_name,
							&m_pModelData->m_PartsData.g_Textures[nCnt]);
					}
					else
						m_pModelData->m_PartsData.g_Textures[nCnt] = nullptr;
				}
				m_pModelData->m_Parts_Map.insert(unordered_map<int, CModelData>::value_type(nCntParts, m_pModelData->m_PartsData));//map�ɕt��������
				nCntParts++;
			}

			//Parts Set
			if (bReadPartsSet)
			{
				if (strcmp(aText, "INDEX") == 0)
				{
					sscanf(aLine, "%s = %d", aText, &nIndex);
				}
				if (strcmp(aText, "PARENT") == 0)
				{
					sscanf(aLine, "%s = %d", aText, &m_pModelData->m_Parts_Map[nIndex].m_nPartParent);
				}
				if (strcmp(aText, "POS") == 0)
				{
					sscanf(aLine, "%s = %f %f %f",
						aText,
						&m_pModelData->m_Parts_Map[nIndex].m_nPartPos.x,
						&m_pModelData->m_Parts_Map[nIndex].m_nPartPos.y,
						&m_pModelData->m_Parts_Map[nIndex].m_nPartPos.z);
				}
				if (strcmp(aText, "ROT") == 0)
				{
					sscanf(aLine, "%s = %f %f %f",
						aText,
						&m_pModelData->m_Parts_Map[nIndex].m_nPartRot.x,
						&m_pModelData->m_Parts_Map[nIndex].m_nPartRot.y,
						&m_pModelData->m_Parts_Map[nIndex].m_nPartRot.z);
				}
			}

			//Motion Set
			if (bReadMotion)
			{
				if (strcmp(aText, "MOTION_NAME") == 0)
				{
					sscanf(aLine, "%s = %s", aText, &aMotionName);
				}
				if (strcmp(aText, "LOOP") == 0)
				{
					sscanf(aLine, "%s = %d", aText, &nLoop);
					if (nLoop == 0)
						m_pModelData->m_MotionData.m_bLoop = false;
					else if (nLoop == 1)
						m_pModelData->m_MotionData.m_bLoop = true;
				}
				if (strcmp(aText, "KEY_NUM") == 0)
				{
					sscanf(aLine, "%s = %d", aText, &m_pModelData->m_MotionData.m_nMaxKey);
				}
				if (strcmp(aText, "#KEY_SET") == 0)
				{
					bReadKey = true;
					continue;
				}
				if (strcmp(aText, "#END_KEY_SET") == 0)
				{
					bReadKey = false;
					continue;
				}
				if (bReadKey)
				{
					if (strcmp(aText, "KEY_INDEX") == 0)
					{
						sscanf(aLine, "%s = %d", aText, &m_pModelData->m_MotionData.m_nNumKey);
					}
					if (strcmp(aText, "FRAME_SPEED") == 0)
					{
						sscanf(aLine, "%s = %d", aText, &m_pModelData->m_MotionData.m_aKeyInfo[m_pModelData->m_MotionData.m_nNumKey].nFrameSpeed);
					}
					if (strcmp(aText, "PARTS_INDEX") == 0)
					{
						sscanf(aLine, "%s = %d", aText, &nIndex);
					}
					if (strcmp(aText, "POS") == 0)
					{
						sscanf(aLine, "%s = %f %f %f",
							aText,
							&m_pModelData->m_MotionData.m_aKeyInfo[m_pModelData->m_MotionData.m_nNumKey].akey[nIndex].fPosX,
							&m_pModelData->m_MotionData.m_aKeyInfo[m_pModelData->m_MotionData.m_nNumKey].akey[nIndex].fPosY,
							&m_pModelData->m_MotionData.m_aKeyInfo[m_pModelData->m_MotionData.m_nNumKey].akey[nIndex].fPosZ);
					}
					if (strcmp(aText, "ROT") == 0)
					{
						sscanf(aLine, "%s = %f %f %f",
							aText,
							&m_pModelData->m_MotionData.m_aKeyInfo[m_pModelData->m_MotionData.m_nNumKey].akey[nIndex].fRotX,
							&m_pModelData->m_MotionData.m_aKeyInfo[m_pModelData->m_MotionData.m_nNumKey].akey[nIndex].fRotY,
							&m_pModelData->m_MotionData.m_aKeyInfo[m_pModelData->m_MotionData.m_nNumKey].akey[nIndex].fRotZ);
					}
				}
			}
		}
	}
	m_PartsModel_Map.insert(unordered_map<string, CModelDataPlus*>::value_type(aID, m_pModelData));//map�ɕt��������
	return S_OK;
}