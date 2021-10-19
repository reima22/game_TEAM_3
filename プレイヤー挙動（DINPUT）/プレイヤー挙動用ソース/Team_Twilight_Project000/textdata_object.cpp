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

	int nModelCnt = 0;				// モデル数のカウント

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
				}
			}

			// モデルファイル名
			if (strcmp("MODEL_FILENAME", pLoadText) == 0)
			{
				m_pFileObjectName[nModelCnt] = &m_pFileObjectNameLoad[nModelCnt][0];

				// モデル名
				fscanf(pFile, "%s %s", &aLoadText[0], &m_pFileObjectNameLoad[nModelCnt][0]);

				// カウント増加
				nModelCnt++;
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
		delete m_pFileObjectName;
		m_pFileObjectName = NULL;
	}

	// ファイル名読み込みポインタ
	if (m_pFileObjectNameLoad != NULL)
	{
		for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
		{
			delete m_pFileObjectNameLoad[nCnt];
		}

		delete m_pFileObjectNameLoad;
		m_pFileObjectNameLoad = NULL;
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