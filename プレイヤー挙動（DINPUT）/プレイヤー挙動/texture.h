//=============================================================================
//
// テクスチャ管理 [texture.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"

//==============================================================================
// テクスチャ管理クラス
//==============================================================================
class CTexture
{
public:
	// テクスチャの種類
	typedef enum
	{
		TEXTYPE_NONE = 0,			// テクスチャ無し
		TEXTYPE_PLAYER_0,			// プレイヤー服0
		TEXTYPE_PLAYER_1,			// プレイヤー服1
		TEXTURE_OBJECT,

		TEXTYPE_TITLE_BG,			// タイトル背景
		TEXTYPE_TITLE_LOGO,			// タイトルロゴ
		TEXTYPE_TITLE_ENTER,		// タイトルエンターサイン
		TEXTYPE_RESULT_BG,			// リザルト背景
		TEXTYPE_RESULT_LOGO,		// リザルトロゴ
		TEXTYPE_RANKING_BG,			// ランキング背景
		TEXTYPE_RANKING_LOGO,		// ランキングロゴ
		TEXTYPE_RANKING_RANK,		// ランキング順位
		TEXTYPE_RANKING_SCORELOGO,	// ランキング画面のリザルトスコアロゴ
		TEXTYPE_LIFE,				// ライフ
		TEXTYPE_ITEM_0,				// アイテム0(波形)
		TEXTYPE_ITEM_1,				// アイテム1(ミサイル)
		TEXTYPE_ITEM_2,				// アイテム2(逆波形)
		TEXTYPE_ITEM_3,				// アイテム3(回復)
		TEXTYPE_NUMBER,				// ナンバー
		TEXTYPE_EXPLOSION,			// 爆発
		TEXTYPE_EFFECT,				// エフェクト
		TEXTYPE_LINE,				// ボーダーライン
		TEXTYPE_PAUSE_BASE,			// ポーズ画面のベース
		TEXTYPE_PAUSE_CONTINUE,		// ポーズコンテニュー
		TEXTYPE_PAUSE_RETRY,		// ポーズリトライ
		TEXTYPE_PAUSE_QUIT,			// ポーズ終了
		TEXTYPE_TUTORIAL_0,			// チュートリアル0
		TEXTYPE_TUTORIAL_1,			// チュートリアル1
		TEXTYPE_TUTORIAL_2,			// チュートリアル2
		TEXTYPE_MESSAGE_WINDOW,		// メッセージウィンドウ
		TEXTYPE_MESSAGE_TEXT,		// メッセージテキスト
		TEXTYPE_CAUTION,			// 警告画面
		TEXTYPE_WINDOWEFFECT,		// 画面エフェクト
		TEXTYPE_EASY,				// easy
		TEXTYPE_NORMAL,				// normal
		TEXTYPE_HARD,				// hard
		TEXTYPE_METEOR,				// 隕石
		TEXTYPE_PANEL,				// ソーラーパネル
		TEXTYPE_MAX					// 最大数
	}TEXTYPE;

	CTexture();
	~CTexture();

	static HRESULT LoadAll(void);
	static void UnloadAll(void);
	static LPDIRECT3DTEXTURE9 BindTexture(TEXTYPE texType) { return m_pTexture[texType]; }
	
	// 3Dモデルへのテクスチャ割り当て
	static LPDIRECT3DTEXTURE9 BindTex3D(char *pTexFilename);

private:
	static char *m_pFileName[TEXTYPE_MAX];				// 読み込むファイル名パス
	static LPDIRECT3DTEXTURE9 m_pTexture[TEXTYPE_MAX];	// テクスチャへのポインタ
};

#endif
