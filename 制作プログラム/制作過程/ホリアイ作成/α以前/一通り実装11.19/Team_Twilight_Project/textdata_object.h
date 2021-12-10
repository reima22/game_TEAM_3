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
// 配置オブジェクト管理クラス
//==============================================================================
class CTextDataObject : public CTextData
{
public:
	CTextDataObject();
	~CTextDataObject();

	void LoadData(STAGEINFO stage);
	void Unload(void);

	static CTextDataObject *Create(STAGEINFO stage);	// 生成

	char *GetFileName(int nType) { return m_pFileObjectName[nType]; }				// ファイル名の取得
	int GetNumObject(void) { return m_nNumObject; }									// オブジェクト数の取得
	int GetTypeObject(int nIdx) { return m_pType[nIdx]; }							// 種類の取得

	D3DXVECTOR3 GetPosition(int nIdx) { return m_pPos[nIdx]; }						// 位置
	D3DXVECTOR3 GetRotation(int nIdx) { return m_pRot[nIdx]; }						// 角度
	D3DXVECTOR2 GetShadowSize(int nIdx) { return m_pShadowSize[nIdx]; }				// 影のサイズ

	//float GetInfo(int nIdx, OBJECTINFO info) { return m_pObjectInfo[nIdx][info]; }	// 位置・角度の取得
	//float GetShadowWidth(int nIdx) { return m_pShadowWidth[nIdx]; }					// 影の幅
	//float GetShadowDepth(int nIdx) { return m_pShadowDepth[nIdx]; }					// 影の奥行

	bool GetSavePoint(int nIdx) { return m_pSavePoint[nIdx]; }						// 中間地点の可否
	bool GetStartPoint(int nIdx) { return m_pStartPoint[nIdx]; }					// スタート地点の可否
	bool GetGoalPoint(int nIdx) { return m_pGoalPoint[nIdx]; }						// ゴール地点の可否

	int GetStartIdx(void) { return m_nStartPointIdx; }

private:
	int m_nNumFile;					// ファイル名の総数
	char **m_pFileObjectName;		// ファイル名ポインタ
	char **m_pFileObjectNameLoad;	// 読み取り用ファイル名変数

	int *m_pType;					// 種類
	D3DXVECTOR3 *m_pPos;			// 位置
	D3DXVECTOR3 *m_pRot;			// 角度
	D3DXVECTOR2 *m_pShadowSize;		// 影のサイズ

	bool *m_pSavePoint;				// 中間地点の可否
	bool *m_pStartPoint;			// スタート地点の可否
	bool *m_pGoalPoint;				// ゴール地点の可否
	int m_nStartPointIdx;			// スタート地点のインデックス

	int m_nNumObject;				// オブジェクトの総数
};

#endif
