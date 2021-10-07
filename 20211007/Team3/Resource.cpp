//===================================================================
//ImplementationFile: ResourceManager.cpp
//Author : Yo jitaku
//===================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "Resource.h"
#include "Renderer.h"

//*******************************************************************
//初期化処理
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
//メモリの解放
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
//画像ファイルの読み込む
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
		if (!bReadStart && strcmp(aLine, "#START\n") == 0)//STARTマークを探す
		{
			bReadStart = true;
			continue;
		}
		else if (strcmp(aLine, "#END") == 0 || strcmp(aLine, "#END\n") == 0)//ENDマークを探す
		{
			fclose(pFile);
			break;
		}
		else if (bReadStart)
		{
			sscanf(aLine, "%s%s", aID, aAddress);
			if (FAILED(D3DXCreateTextureFromFile(m_pDevice, aAddress, &pTexture)))//デバイスを使ってリソースを作る
				return E_FAIL;
			m_Texture_Map.insert(unordered_map<string, LPDIRECT3DTEXTURE9>::value_type(aID, pTexture));//mapに付け加える
		}
	}
	return S_OK;
}

//*******************************************************************
//音声ファイルの読み込む
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
//		if (!bReadStart && strcmp(aLine, "#START\n") == 0)//STARTマークを探す
//		{
//			bReadStart = true;
//			continue;
//		}
//		else if (strcmp(aLine, "#END") == 0 || strcmp(aLine, "#END\n") == 0)//ENDマークを探す
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
//			// バッファのクリア
//			memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
//			memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
//			sscanf(aLine, "%s%s", aID, aAddress);
//			// サウンドデータファイルの生成
//			hFile = CreateFile(aAddress, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
//			if (hFile == INVALID_HANDLE_VALUE)
//				return HRESULT_FROM_WIN32(GetLastError());
//			if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
//				return HRESULT_FROM_WIN32(GetLastError());
//			// WAVEファイルのチェック
//			if (FAILED(CheckSoundChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition)))
//				return S_FALSE;
//			if (FAILED(ReadSoundChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition)))
//				return S_FALSE;
//			if (dwFiletype != 'EVAW')
//				return S_FALSE;
//			// フォーマットチェック
//			if (FAILED(CheckSoundChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition)))
//				return S_FALSE;
//			if (FAILED(ReadSoundChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition)))
//				return S_FALSE;
//			// オーディオデータ読み込み
//			if (FAILED(CheckSoundChunk(hFile, 'atad', &pSoundData->m_SizeAudio, &dwChunkPosition)))
//				return S_FALSE;
//			pSoundData->m_pDataAudio = (BYTE*)malloc(pSoundData->m_SizeAudio);
//			if (FAILED(ReadSoundChunkData(hFile, pSoundData->m_pDataAudio, pSoundData->m_SizeAudio, dwChunkPosition)))
//				return S_FALSE;
//			// ソースボイスの生成
//			if (FAILED(pXAudio2->CreateSourceVoice(&pSoundData->m_pSourceVoice, &(wfx.Format))))
//				return S_FALSE;
//
//			// バッファの値設定
//			memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
//			buffer.AudioBytes = pSoundData->m_SizeAudio;
//			buffer.pAudioData = pSoundData->m_pDataAudio;
//			buffer.Flags = XAUDIO2_END_OF_STREAM;
//			buffer.LoopCount = 0;
//
//			// オーディオバッファの登録
//			pSoundData->m_pSourceVoice->SubmitSourceBuffer(&buffer);
//
//			// ファイルをクローズ
//			CloseHandle(hFile);
//
//			m_Sound_Map.insert(unordered_map<string, CSoundData*>::value_type(aID, pSoundData));//mapに付け加える
//		}
//	}
//	return S_OK;
//}

//*******************************************************************
// チャンクのチェック
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
//	{// ファイルポインタを先頭に移動
//		return HRESULT_FROM_WIN32(GetLastError());
//	}
//
//	while (hr == S_OK)
//	{
//		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
//		{// チャンクの読み込み
//			hr = HRESULT_FROM_WIN32(GetLastError());
//		}
//
//		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
//		{// チャンクデータの読み込み
//			hr = HRESULT_FROM_WIN32(GetLastError());
//		}
//
//		switch (dwChunkType)
//		{
//		case 'FFIR':
//			dwRIFFDataSize = dwChunkDataSize;
//			dwChunkDataSize = 4;
//			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
//			{// ファイルタイプの読み込み
//				hr = HRESULT_FROM_WIN32(GetLastError());
//			}
//			break;
//
//		default:
//			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
//			{// ファイルポインタをチャンクデータ分移動
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
// チャンクデータの読み込み
//*******************************************************************
//HRESULT CResourceManager::ReadSoundChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
//{
//	DWORD dwRead;
//
//	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
//	{// ファイルポインタを指定位置まで移動
//		return HRESULT_FROM_WIN32(GetLastError());
//	}
//
//	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
//	{// データの読み込み
//		return HRESULT_FROM_WIN32(GetLastError());
//	}
//
//	return S_OK;
//}

//*******************************************************************
//モードファイルの読み込む
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
		if (!bReadStart && strcmp(aLine, "#START\n") == 0)//STARTマークを探す
		{
			bReadStart = true;
			continue;
		}
		else if (strcmp(aLine, "#END") == 0 || strcmp(aLine, "#END\n") == 0)//ENDマークを探す
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
				&m_pModelData->Xfile_Mesh)))//メッシュを取る
				return E_FAIL;

			//材質について
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
			m_Model_Map.insert(unordered_map<string, CModelData*>::value_type(aID, m_pModelData));//mapに付け加える
		}
	}
	return S_OK;
}

//*******************************************************************
//モーションつけモードの読み込む
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
		if (!bReadStart && strcmp(aLine, "#START\n") == 0)//STARTマークを探す
		{
			bReadStart = true;
			continue;
		}
		else if (strcmp(aLine, "#END") == 0 || strcmp(aLine, "#END\n") == 0)//ENDマークを探す
		{
			fclose(pFile);
			break;
		}
		else if (bReadStart)
		{
			sscanf(aLine, "%s", &aText);
			if (strcmp(aText, "MODEL_NAME") == 0)//モードの名前
			{
				sscanf(aLine, "%s = %s", aText, &aID);
				continue;
			}
			if (strcmp(aText, "PARTS_NUM") == 0)//パーツの総数
			{
				sscanf(aLine, "%s = %d", aText, &m_pModelData->m_nParts);
				continue;
			}
			if (strcmp(aText, "#XFILE") == 0)//パーツのXファイル
			{
				bReadXfile = true;
				continue;
			}
			if (strcmp(aText, "#END_XFILE") == 0)
			{
				bReadXfile = false;
				continue;
			}
			if (strcmp(aText, "#PARTS_SET") == 0)//パーツの初期化情報
			{
				bReadPartsSet = true;
				continue;
			}
			if (strcmp(aText, "#END_PARTS_SET") == 0)
			{
				bReadPartsSet = false;
				continue;
			}
			if (strcmp(aText, "#MOTION_SET") == 0)//パーツのモーション情報
			{
				bReadMotion = true;
				continue;
			}
			if (strcmp(aText, "#END_MOTION_SET") == 0)
			{
				bReadMotion = false;
				m_pModelData->m_Motion_Map.insert(unordered_map<string, CMotionData>::value_type(aMotionName, m_pModelData->m_MotionData));//mapに付け加える
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
					&m_pModelData->m_PartsData.Xfile_Mesh)))//Xファイルの読み込む
					return E_FAIL;
				//材質について
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
				m_pModelData->m_Parts_Map.insert(unordered_map<int, CModelData>::value_type(nCntParts, m_pModelData->m_PartsData));//mapに付け加える
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
	m_PartsModel_Map.insert(unordered_map<string, CModelDataPlus*>::value_type(aID, m_pModelData));//mapに付け加える
	return S_OK;
}