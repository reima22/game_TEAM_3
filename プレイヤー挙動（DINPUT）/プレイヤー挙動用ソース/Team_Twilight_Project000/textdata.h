//=============================================================================
//
// テキストデータ管理 [textdata.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTDATA_H_
#define _TEXTDATA_H_

#include "main.h"

// マクロ定義
#define TEXT_NUM	(128)	// テキストデータバイト数

// 前方宣言
class CTextDataPlayer;
class CTextDataObject;


//==============================================================================
// テキスト管理クラス
//==============================================================================
class CTextData
{
public:
	// テキストデータの種類
	typedef enum
	{
		TEXTDATA_RANKING = 0,	// ランキングのデータ
		TEXTDATA_SYSTEM,		// ゲームルールデータ
		TEXTDATA_PLAYER,		// プレイヤーのデータ
		TEXTDATA_OBJECT,		// 3Dオブジェクトデータ
		TEXTDATA_MAX
	}TEXTDATA;

	CTextData();
	~CTextData();

	static void LoadTextAll(void);
	static CTextDataPlayer *GetDataPlayer(void) { return m_pDataPlayer; }

protected:
	static char *m_pFileName[TEXTDATA_MAX];	// 読み込むファイル名パス
	static CTextDataPlayer *m_pDataPlayer;	// プレイヤーデータ
	static CTextDataObject *m_pDataObject;	// オブジェクトデータ
};

#endif