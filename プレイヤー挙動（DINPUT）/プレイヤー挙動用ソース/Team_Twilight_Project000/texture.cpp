//==============================================================================
//
// テクスチャ管理〔texture.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

// 静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CTexture::m_pTexture[TEXTYPE_MAX] = {};
char *CTexture::m_pFileName[TEXTYPE_MAX] = 
{
	{""},										// テクスチャ無し
	{ "data\\TEXTURE\\player_cloth00.jpg" },	// プレイヤーテクスチャ
	{ "data\\TEXTURE\\player_cloth01.jpg" },	// プレイヤーテクスチャ
	{ "data\\TEXTURE\\title_bg.png" },			// タイトル背景
	{ "data\\TEXTURE\\title000.png" },			// タイトルロゴ
	{ "data\\TEXTURE\\press_enter.png" },		// タイトルエンターサイン
	{ "data\\TEXTURE\\result_bg.png" },			// リザルト背景
	{ "data\\TEXTURE\\result_logo000.png" },	// リザルトロゴ
	{ "data\\TEXTURE\\ranking_bg.png" },		// ランキング背景
	{ "data\\TEXTURE\\ranking_logo.png" },		// ランキングロゴ	
	{ "data\\TEXTURE\\ranking_rank.png" },		// ランキング順位
	{ "data\\TEXTURE\\yourscore.png" },			// ランキング画面のリザルトスコアロゴ
	{ "data\\TEXTURE\\life000.png" },			// ライフ
	{ "data\\TEXTURE\\item000.png" },			// アイテム0(波形弾)
	{ "data\\TEXTURE\\item001.png" },			// アイテム1(ミサイル)
	{ "data\\TEXTURE\\item002.png" },			// アイテム2(逆波形弾)
	{ "data\\TEXTURE\\item003.png" },			// アイテム3(回復)
	{ "data\\TEXTURE\\number000.png" },		// ナンバー
	{ "data\\TEXTURE\\explosion000.png" },	// 爆発
	{ "data\\TEXTURE\\effect000.jpg" },		// エフェクト
	{ "data\\TEXTURE\\safetyline000.png" },	// ボーダーライン
	{ "data\\TEXTURE\\pause_BS.png" },		// ポーズベース
	{ "data\\TEXTURE\\continue_logo.png" },	// ポーズコンテニュー
	{ "data\\TEXTURE\\retry_logo.png" },		// ポーズリトライ
	{ "data\\TEXTURE\\quit_logo.png" },		// ポーズ終了 
	{ "data\\TEXTURE\\tutorial00.jpg" },		// チュートリアル0 
	{ "data\\TEXTURE\\tutorial01.jpg" },		// チュートリアル1
	{ "data\\TEXTURE\\tutorial02.jpg" },		// チュートリアル2
	{ "data\\TEXTURE\\message_window.png" },	// メッセージウィンドウ
	{ "data\\TEXTURE\\message_text.png" },	// メッセージテキスト
	{ "data\\TEXTURE\\warning.png" },			// 警告画面
	{ "data\\TEXTURE\\window_effect.png" },	// 画面エフェクト
	{ "data\\TEXTURE\\easy.png" },			// easy
	{ "data\\TEXTURE\\normal.png" },			// normal
	{ "data\\TEXTURE\\hard.png" },			// hard
	{ "data\\TEXTURE\\meteor.jpg"},			// 隕石モデルのテクスチャ
	{ "data\\TEXTURE\\panel.jpg" },			// パネルモデルのテクスチャ
};

//==============================================================================
// コンストラクタ
//==============================================================================
CTexture::CTexture()
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CTexture::~CTexture()
{

}

//==============================================================================
// テクスチャデータの全読み込み
//==============================================================================
HRESULT CTexture::LoadAll(void)
{	
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCnt = 1; nCnt < TEXTYPE_MAX; nCnt++)
	{
		// テクスチャの読み込み
		D3DXCreateTextureFromFile(
			pDevice,
			m_pFileName[nCnt],
			&m_pTexture[nCnt]);
	}

	return S_OK;
}

//==============================================================================
// テクスチャデータの全破棄
//==============================================================================
void CTexture::UnloadAll(void)
{
	for (int nCnt = 0; nCnt < TEXTYPE_MAX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}

		if (m_pFileName[nCnt] != NULL)
		{
			m_pFileName[nCnt] = NULL;
		}
	}
}

//==============================================================================
// 3Dモデルへの割り当て
//==============================================================================
LPDIRECT3DTEXTURE9 CTexture::BindTex3D(char *pTexFilename)
{
	for (int nCntTex = 0; nCntTex < TEXTYPE_MAX; nCntTex++)
	{
		// 該当するテクスチャの割出し
		if (strcmp(m_pFileName[nCntTex] ,pTexFilename) == 0)
		{
			// テクスチャ情報を返す
			return m_pTexture[nCntTex];
		}
	}

	return NULL;
}