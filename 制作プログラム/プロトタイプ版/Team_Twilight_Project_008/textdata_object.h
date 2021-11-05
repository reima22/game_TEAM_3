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
	typedef enum
	{
		OBJECTINFO_POS_X = 0,	// 位置X座標
		OBJECTINFO_POS_Y,		// 位置Y座標
		OBJECTINFO_POS_Z,		// 位置Z座標
		OBJECTINFO_ROT_X,		// 角度X座標
		OBJECTINFO_ROT_Y,		// 角度Y座標
		OBJECTINFO_ROT_Z,		// 角度Z座標
		OBJECTINFO_MAX			
	}OBJECTINFO;

	CTextDataObject();
	~CTextDataObject();

	void LoadData(void);
	void Unload(void);

	static CTextDataObject *Create(void);	// 生成

	char *GetFileName(int nType) { return m_pFileObjectName[nType]; }				// ファイル名の取得
	int GetNumObject(void) { return m_nNumObject; }									// オブジェクト数の取得
	int GetTypeObject(int nIdx) { return m_pType[nIdx]; }							// 種類の取得
	float GetInfo(int nIdx, OBJECTINFO info) { return m_pObjectInfo[nIdx][info]; }	// 位置・角度の取得
	float GetShadowWidth(int nIdx) { return m_pShadowWidth[nIdx]; }					// 影の幅
	float GetShadowDepth(int nIdx) { return m_pShadowDepth[nIdx]; }					// 影の奥行
	bool GetSavePoint(int nIdx) { return m_pSavePoint[nIdx]; }						// 中間地点の可否

private:
	int m_nNumFile;					// ファイル名の総数
	char **m_pFileObjectName;		// ファイル名ポインタ
	char **m_pFileObjectNameLoad;	// 読み取り用ファイル名変数

	int *m_pType;					// 種類

	float **m_pObjectInfo;			// オブジェクトの位置・角度情報

	float *m_pShadowWidth;			// 影の幅
	float *m_pShadowDepth;			// 影の奥行

	bool *m_pSavePoint;				// 中間地点の可否

	int m_nNumObject;				// オブジェクトの総数
};

#endif
