//--------------------------------------------------------------------------------
//
// ゲーム制作[logo.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _LOGO_H_
#define _LOGO_H_

#include "scene2D.h"

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------
#define MAX_GAMELOGO			(2)									//	ゲーム内で使われるロゴの最大数
#define MAX_LOGO				(5)									//	ロゴの最大数
#define TIME_COLOR				(50)								//	色変化時間
#define MOVE_SPEED				(15.0f)								//	速度値
#define GRAVITY					(0.4f)								//	重力値

#define POS_TITLE_Y				(230.0f)							//	タイトル　	Y軸の位置
#define POS_TITLE_X				(630.0f)							//	タイトル　	X軸の位置
#define MOVE_TITLE_Y			(0.0f)								//	タイトル　	Y軸の移動値
#define MOVE_TITLE_X			(0.014f)							//	タイトル　	X軸の移動値

#define POS_START_Y				(550.0f)							//	START　		Y軸の位置
#define POS_START_X				(640.0f)							//	START　		X軸の位置
#define MOVE_START_Y			(-8.0f)								//	START　		Y軸の移動値
#define MOVE_START_X			(0.0f)								//	START　		X軸の移動値

//================================================================================
//オブジェクトクラス(ロゴ)
//================================================================================
class CLogo :public CScene
{
public:

	//弾判定分け
	typedef enum
	{
		LOGOTYPE_NONE = 0,
		LOGOTYPE_START,												//	スタート
		LOGOTYPE_TITLENAME,											//	タイトル名
		LOGOTYPE_MAX						    

	}LOGOTYPE;

	CLogo(int nPriority = OBJTYPE_LOGO);							//	コンストラクタ
	~CLogo();														//	デストラクタ

	static CLogo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,
		LOGOTYPE logoType);											//	ロゴの生成

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//	初期化処理
	void Uninit(void);												//	終了処理
	void Update(void);												//	更新処理
	void Draw(void);												//	描画処理

	static HRESULT Load(void);										//	読み込み処理
	static void Unload(void);										//	破棄処理

	LOGOTYPE GetInfoType(void) { return m_LogoType; }				//	ロゴタイプ情報の呼び出し
	void SetInfoType(LOGOTYPE logoType) {m_LogoType = logoType;}	//	ロゴタイプ情報の取得

private:

	LOGOTYPE m_LogoType;											//  ロゴタイプ

	bool m_bEnter;													//  エンターを押したかどうか
	bool m_bTutorial;												//  チュートリアル画面に移動するかどうか
	bool m_bJump;													//  ジャンプ判定
		
	int m_nCntColor;												//	待機点滅カウント
	int m_nTimeColor;												//	決定点滅カウント
	int m_nTimer;													//	タイマー
	int m_nJumpCnt;													//	ジャンプカウント
	int m_nAppearanceCnt;											//	出現カウント

	float m_fSpd;													//  移動速度

	D3DXVECTOR3 m_scale;											//	大きさ
	D3DXVECTOR3 m_move;												//	移動値
	D3DXCOLOR	m_Color;											//	色
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_LOGO];				//	テクスチャ
	CScene2D*m_apScene2D[5];										//	CScene2Dのポインタ
};
#endif
