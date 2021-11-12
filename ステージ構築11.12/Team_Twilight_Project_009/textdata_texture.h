//=============================================================================
//
// テキストデータ（テクスチャ）管理 [textdata_texture.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTDATA_TEXTURE_H_
#define _TEXTDATA_TEXTURE_H_

#include "main.h"
#include "textdata.h"

//==============================================================================
// テキスト管理（テクスチャ）クラス
//==============================================================================
class CTextDataTexture : public CTextData
{
public:
	CTextDataTexture();
	~CTextDataTexture();

	void LoadData(void);
	void Unload(void);

	static CTextDataTexture *Create(void);

	int GetNumTexture(void) { return m_nNumTexture; }
	char *GetFileName(int nIdx) { return m_pFileTextureName[nIdx]; }

	int GetIdxNumber(void) { return m_nIdxNumber; }
	int GetIdxShadow(void) { return m_nIdxShadow; }
	int GetIdxEffect(void) { return m_nIdxEffect; }

private:
	int m_nNumTexture;			// テクスチャの数
	char **m_pFileTextureName;	// ファイル名を格納するポインタ
	int *m_pIdx;				// テクスチャのインデックス
	int m_nIdxNumber;			// 数値テクスチャのインデックス
	int m_nIdxShadow;			// 影テクスチャのインデックス
	int m_nIdxEffect;			// エフェクトのインデックス
};
#endif
