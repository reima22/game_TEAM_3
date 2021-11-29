////=============================================================================
////
//// テキストデータ（サウンド）管理 [textdata_sound.h]
//// Author : Mare Horiai
////
////============================================================================= 
//#ifndef _TEXTDATA_SOUND_H_
//#define _TEXTDATA_SOUND_H_
//
//#include "main.h"
//#include "textdata.h"
//
////==============================================================================
//// テキスト管理（サウンド）クラス
////==============================================================================
//class CTextDataSound : public CTextData
//{
//public:
//	CTextDataSound();
//	~CTextDataSound();
//
//	void LoadData(void);
//	void Unload(void);
//
//	static CTextDataSound *Create(void);
//
//	//int GetNumTexture(void) { return m_nNumTexture; }
//	char *GetFileName(int nIdx) { return m_pFileTextureName[nIdx]; }
//
//private:
//	int m_nNumSound;			// テクスチャの数
//	char **m_pFileTextureName;	// ファイル名を格納するポインタ
//	int *m_pIdx;				// テクスチャのインデックス
//	bool *m_pLoop;				// ループするか
//};
//#endif