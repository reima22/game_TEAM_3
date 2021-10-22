//=============================================================================
//
// テキストデータ（3Dオブジェクト）管理 [textdata_object.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTDATA_OBJECT_H_
#define _TEXTDATA_OBJECT_H_

#include "main.h"
#include "textdata.h"

//==============================================================================
// テキスト管理（system）クラス
//==============================================================================
class CTextDataObject : public CTextData
{
public:
	CTextDataObject();
	~CTextDataObject();

	void LoadData(void);
	void Uninit(void);

	static CTextDataObject *Create(void);	// 生成

	char *GetFileName(int nType) { return m_pFileObjectName[nType]; }	// ファイル名の取得
	int GetNumObject(void) { return m_nNumObject; }						// オブジェクト数の取得
	int GetTypeObject(int nIdx) { return m_pType[nIdx]; }				// 種類の取得
	D3DXVECTOR3 GetPosObject(int nIdx) { return m_pPos[nIdx]; }			// 位置の取得
	D3DXVECTOR3 GetRotObject(int nIdx) { return m_pRot[nIdx]; }			// 向きの取得

private:
	int m_nNumModel;				// モデルの総数
	char **m_pFileObjectName;		// ファイル名ポインタ
	char **m_pFileObjectNameLoad;	// 読み取り用ファイル名変数

	int *m_pType;					// 種類
	D3DXVECTOR3 *m_pPos;			// 位置
	D3DXVECTOR3 *m_pRot;			// 角度
	int m_nNumObject;				// オブジェクトの総数
	int m_nNumObjectIn;				// オブジェクト確保数
};

#endif
