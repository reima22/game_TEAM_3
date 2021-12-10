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
	char aLoadText[TEXT_NUM] = {};
	char *pLoadText = &aLoadText[0];

	int nModelCnt = 0;		// モデル数のカウント

	m_nNumFile = 0;			// ファイル数
	m_nNumObject = 0;		// 配置するオブジェクト数

	// データの読み込み
	pFile = fopen(m_pFileName[TEXTDATA_OBJECT], "r");

	if (pFile != NULL)
	{ //ファイル展開可能

	  // スクリプト読み込み終わりまで
		while (strcmp("END_SCRIPT", pLoadText) != 0)
		{
			// 項目読み込み
			fscanf(pFile, "%s", pLoadText);

			// 読み込むモデル数
			if (strcmp("NUM_MODEL", pLoadText) == 0)
			{
				fscanf(pFile, "%s %d", &aLoadText[0], &m_nNumFile);

				// ファイル数分、動的確保
				m_pFileObjectName = new char*[m_nNumFile];

				m_pFileObjectNameLoad = new char*[m_nNumFile];

				// 2次元配列の確保
				for (int nCnt = 0; nCnt < m_nNumFile; nCnt++)
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

			// 配置情報のカウント
			if (strcmp("OBJECTSET", pLoadText) == 0)
			{
				char aObjectData[TEXT_NUM] = {};
				char *pObjectData = &aObjectData[0];

				while (strcmp("END_OBJECTSET", pObjectData) != 0)
				{
					// 読み込み
					fscanf(pFile, "%s", &aObjectData[0]);
				}

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

	pFile = NULL;

	// 各パラメータの動的確保
	m_pType = new int[m_nNumObject];			// 種類
	m_pObjectInfo = new float*[m_nNumObject];	// 位置・角度
	m_pShadowWidth = new float[m_nNumObject];	// 丸影の幅
	m_pShadowDepth = new float[m_nNumObject];	// 丸影の奥行

	int nCntObject = 0;	// カウント

	// データの読み込み
	pFile = fopen(m_pFileName[TEXTDATA_OBJECT], "r");

	if (pFile != NULL)
	{ //ファイル展開可能

		aLoadText[0] = {};

	  // スクリプト読み込み終わりまで
		while (strcmp("END_SCRIPT", pLoadText) != 0)
		{
			// 項目読み込み
			fscanf(pFile, "%s", pLoadText);

			// 配置情報の読み込み
			if (strcmp("OBJECTSET", pLoadText) == 0)
			{
				char aObjectData[TEXT_NUM] = {};
				char *pObjectData = &aObjectData[0];

				// オブジェクト情報の種類だけ確保
				m_pObjectInfo[nCntObject] = new float[OBJECTINFO_MAX];

				while (strcmp("END_OBJECTSET", pObjectData) != 0)
				{
					// 読み込み
					fscanf(pFile, "%s", &aObjectData[0]);

					// 影のサイズ
					if (strcmp("SHADOW", pObjectData) == 0)
					{
						fscanf(pFile, "%s %f %f", &aObjectData[0], &m_pShadowWidth[nCntObject], &m_pShadowDepth[nCntObject]);
					}

					// 種類
					if (strcmp("TYPE", pObjectData) == 0)
					{
						fscanf(pFile, "%s %d", &aObjectData[0], &m_pType[nCntObject]);
					}

					// 位置
					if (strcmp("POS", pObjectData) == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aObjectData[0],
							&m_pObjectInfo[nCntObject][OBJECTINFO_POS_X],
							&m_pObjectInfo[nCntObject][OBJECTINFO_POS_Y],
							&m_pObjectInfo[nCntObject][OBJECTINFO_POS_Z]);
					}

					// 向き
					if (strcmp("ROT", pObjectData) == 0)
					{
						fscanf(pFile, "%s %f %f %f", &aObjectData[0],
							&m_pObjectInfo[nCntObject][OBJECTINFO_ROT_X],
							&m_pObjectInfo[nCntObject][OBJECTINFO_ROT_Y],
							&m_pObjectInfo[nCntObject][OBJECTINFO_ROT_Z]);
					}
				}

				nCntObject++;		// カウント加算
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
void CTextDataObject::Unload(void)
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
		for (int nCnt = 0; nCnt < m_nNumFile; nCnt++)
		{
			delete[] m_pFileObjectNameLoad[nCnt];
			m_pFileObjectNameLoad[nCnt] = NULL;
		}

		delete[] m_pFileObjectNameLoad;
		m_pFileObjectNameLoad = NULL;
	}

	// 種類の破棄
	//if (m_pType != NULL)
	//{
	//	delete[] m_pType;
	//	m_pType = NULL;
	//}

	// 位置・角度の破棄
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

	//// 影の大きさ
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