//==============================================================================
//
// テキストデータ（3Dオブジェクト）管理〔textdata_object.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "textdata.h"
#include "textdata_object.h"
#include "stdio.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CTextDataObject::CTextDataObject()
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CTextDataObject::~CTextDataObject()
{

}

//==============================================================================
// テキストの読み込み
//==============================================================================
void CTextDataObject::LoadData(void)
{
	// ローカル変数宣言
	FILE *pFile;
	char aLoadText[TEXT_NUM];
	char *pLoadText = &aLoadText[0];

	int nModelCnt = 0;		// モデル数のカウント

	m_nNumObject = 0;		// オブジェクト数
	m_nNumObjectIn = 1;		// 動的確保する数

	// 各パラメータの動的確保
	m_pPos = new D3DXVECTOR3[m_nNumObjectIn];
	m_pRot = new D3DXVECTOR3[m_nNumObjectIn];
	m_pType = new int[m_nNumObjectIn];

	// データの読み込み
	pFile = fopen(m_pFileName[TEXTDATA_OBJECT], "r");

	if (pFile != NULL)
	{ //ファイル展開可能

	  // スクリプト読み込み終わりまで
		while (strcmp("END_SCRIPT", pLoadText) != 0)
		{
			// 項目読み込み
			fscanf(pFile, "%s", pLoadText);

			// モデル数
			if (strcmp("NUM_MODEL", pLoadText) == 0)
			{
				fscanf(pFile, "%s %d", &aLoadText[0], &m_nNumModel);

				// モデル数分、動的確保
				m_pFileObjectName = new char*[m_nNumModel];

				m_pFileObjectNameLoad = new char*[m_nNumModel];

				// 2次元配列の確保
				for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
				{
					m_pFileObjectNameLoad[nCnt] = new char[TEXT_NUM];

					m_pFileObjectName[nCnt] = &m_pFileObjectNameLoad[nCnt][0];
				}
			}

			// モデルファイル名
			if (strcmp("MODEL_FILENAME", pLoadText) == 0)
			{
				// モデル名
				fscanf(pFile, "%s %s", &aLoadText[0], &m_pFileObjectNameLoad[nModelCnt][0]);

				// カウント増加
				nModelCnt++;
			}

			// モデル情報の読み込み
			if (strcmp("OBJECTSET", pLoadText) == 0)
			{
				char aObjectData[TEXT_NUM] = {};
				char *pObjectData = &aObjectData[0];

				while (strcmp("END_OBJECTSET", pObjectData) != 0)
				{
					// 読み込み
					fscanf(pFile, "%s", &aObjectData[0]);

					// 種類
					if (strcmp("TYPE", pObjectData) == 0)
					{
						fscanf(pFile, "%s %d", &aObjectData[0], &m_pType[m_nNumObject]);
					}

					// 位置
					if (strcmp("POS", pObjectData) == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aObjectData[0], 
							&m_pPos[m_nNumObject].x,
							&m_pPos[m_nNumObject].y,
							&m_pPos[m_nNumObject].z);
					}

					// 向き
					if (strcmp("ROT", pObjectData) == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aObjectData[0],
							&m_pRot[m_nNumObject].x,
							&m_pRot[m_nNumObject].y,
							&m_pRot[m_nNumObject].z);
					}
				}

				m_nNumObjectIn++;	// 確保数の加算
				m_nNumObject++;		// オブジェクト数の加算
			}
		}

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{ // ファイル展開不可
		return;
	}
}

//==============================================================================
// データの破棄
//==============================================================================
void CTextDataObject::Uninit(void)
{
	// ファイル名ポインタ
	if (m_pFileObjectName != NULL)
	{
		delete[] m_pFileObjectName;
		m_pFileObjectName = NULL;
	}

	// ファイル名読み込みポインタの破棄
	if (m_pFileObjectNameLoad != NULL)
	{
		for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
		{
			delete[] m_pFileObjectNameLoad[nCnt];
		}

		delete[] m_pFileObjectNameLoad;
		m_pFileObjectNameLoad = NULL;
	}

	// 種類の破棄
	if (m_pType != NULL)
	{
		delete m_pType;
		m_pType = NULL;
	}

	// 位置の破棄
	if (m_pPos != NULL)
	{
		delete m_pPos;
		m_pPos = NULL;
	}

	// 向きの破棄
	if (m_pRot != NULL)
	{
		delete m_pRot;
		m_pRot = NULL;
	}
}

//==============================================================================
// オブジェクトデータの生成
//==============================================================================
CTextDataObject *CTextDataObject::Create(void)
{
	// プレイヤーデータの読み込み
	CTextDataObject *pDataObject;
	pDataObject = new CTextDataObject;

	// データのロード
	if (pDataObject != NULL)
	{
		pDataObject->LoadData();
	}

	return pDataObject;
}