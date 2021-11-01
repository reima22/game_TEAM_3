#define _CRT_SECURE_NO_WARNINGS
//=============================================================================
//
// オブジェクト管理 [ObjectManager.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "ObjectManager.h"
#include "Scaffold.h"
#include "Manager.h"

//*****************************************************************************
// オブジェクト管理クラス
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CObjectManager::CObjectManager()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CObjectManager::~CObjectManager()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CObjectManager::Init(void)
{
	// ファイル読み込み
	Read();

	// 読み込んだ情報を元に足場生成
	for (int nCnt = 0; nCnt < (signed)m_scaffoldInfo.size(); nCnt++) {
		CScaffold::Create(
			m_scaffoldInfo[nCnt].pos,
			D3DXToRadian(m_scaffoldInfo[nCnt].rot));
	}

	// 同様にモデル生成
	for (int nCnt = 0; nCnt < (signed)m_modelInfo.size(); nCnt++) {
		CScene3DModel::Create(
			m_modelInfo[nCnt].pos,
			D3DXToRadian(m_modelInfo[nCnt].rot),
			m_modelInfo[nCnt].aModelName);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CObjectManager::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CObjectManager::Update(void)
{

}

//=============================================================================
// ファイル読み込み
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
		
		// ローカルで使うための関数用クラス
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

		// ファイルの最後まで読み込みループ
		while (int nReturn = fscanf(pFile, "%s", &aReadStr[0]) != EOF)
		{
			if (bStart)
			{
				// 足場の情報読み込み
				if (strcmp(&aReadStr[0], "SCAFFOLD") == 0) {
					SCAFFOLD_INFO scaffoldInfo;

					while (fscanf(pFile, "%s", &aReadStr[0]) != EOF) {
						if (strcmp(&aReadStr[0], "POS") == 0) {
							scaffoldInfo.pos = Local::ScanVector3(pFile);	// 位置
						}
						else if (strcmp(&aReadStr[0], "ROT") == 0) {
							scaffoldInfo.rot = Local::ScanVector3(pFile);	// 向き
						}
						else if (strcmp(&aReadStr[0], "TYPE") == 0) {
							fscanf(pFile, "%s", &aReadStr[0]);
							if (strcmp(&aReadStr[0], "=") == 0) {
								// 種類を読み込む
								fscanf(pFile, "%d", &scaffoldInfo.nType);	// 種類
							}
						}
						else if (strcmp(&aReadStr[0], "END_SCAFFOLD") == 0) {
							// 完了時に情報を格納
							m_scaffoldInfo.push_back(scaffoldInfo);
							break;
						}
					}
				}
				// モデル情報の読み込み
				else if (strcmp(&aReadStr[0], "MODELSET") == 0) {
					MODEL_INFO modelInfo;

					while (fscanf(pFile, "%s", &aReadStr[0]) != EOF) {
						if (strcmp(&aReadStr[0], "POS") == 0) {
							modelInfo.pos = Local::ScanVector3(pFile);	// 位置
						}
						else if (strcmp(&aReadStr[0], "ROT") == 0) {
							modelInfo.rot = Local::ScanVector3(pFile);	// 向き
						}
						else if (strcmp(&aReadStr[0], "NAME") == 0) {
							fscanf(pFile, "%s", &aReadStr[0]);
							if (strcmp(&aReadStr[0], "=") == 0) {
								fscanf(pFile, "%s", modelInfo.aModelName);	// モデルの名前
							}
						}
						else if (strcmp(&aReadStr[0], "END_MODELSET") == 0) {
							m_modelInfo.push_back(modelInfo);
							break;
						}
					}
				}

			}

			// #start文字列を見つける
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