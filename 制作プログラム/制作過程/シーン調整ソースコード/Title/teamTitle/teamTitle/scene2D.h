//--------------------------------------------------------------------------------
//
// ゲーム制作[scene2D.h]
// Author:Tatsuki Matsuda
//
//--------------------------------------------------------------------------------
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "scene.h"

//--------------------------------------------------------------------------------
//マクロ定義
//--------------------------------------------------------------------------------
#define SCREEN_WIDTH		(1280)									//スクリーンの幅
#define SCREEN_HEIGHT		(720)									//スクリーンの高さ
#define SCREEN_GAMEWIDTH	(830)									//ゲーム画面中のスクリーンの幅
#define SCREEN_GAMEHEIGHT	(720)									//ゲーム画面中のスクリーンの高さ
#define SCREEN_CENTER_X		(SCREEN_WIDTH/2)						//スクリーン中心X座標
#define SCREEN_CENTER_Y		(SCREEN_HEIGHT/2)						//スクリーン中心Y座標
#define SCREEN_HEIGHT_TOP	(20)									//スクリーンY座標
#define MAX_TEXTURE			(5)										//テクスチャの最大数
#define MAX_SCENE2D			(2)										//Scene2Dの最大数
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//頂点フォーマット

//--------------------------------------------------------------------------------
//頂点フォーマットに合わせた構造体
//--------------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//1.0で固定
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標

}VERTEX_2D;

//================================================================================
//オブジェクトクラス(2Dポリゴン)
//================================================================================
class CScene2D :public CScene
{
public:

	CScene2D(int nPriority = OBJTYPE_NONE);							//コンストラクタ
	~CScene2D();													//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);				//初期化処理
	void Uninit(void);												//終了処理
	void Update(void);												//更新処理
	void Draw(void);												//描画処理
	
	static CScene2D *Create(D3DXVECTOR3 pos,D3DXVECTOR3 scale);		//ポリゴンの生成

	D3DXVECTOR3 GetPosition(void);									//位置の取得
	void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale);			//位置の設定

	void SetBg(float ScrollBg);										//背景スクロールの設定

	D3DXVECTOR3 GetScale(void) {return m_scale; }					//スケールの取得
	void SetScale(D3DXVECTOR3 scale) { m_scale = scale; }			//スケールの設定

	void SetTex(int nCnt);											//テクスチャ座標更新処理
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);					//テクスチャ割り当て処理

	void SetColor(D3DXCOLOR color);									//カラーの設定

	D3DXVECTOR3 GetMove(void) { return m_move; }					//移動の取得
	void SetMove(D3DXVECTOR3 move) { m_move = move; }				//移動の設定
	
	D3DXVECTOR3 GetRot(void) { return m_rot; }						//回転の取得
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }					//回転の設定

	void Length(void);												//角度処理

private:

	static CScene2D*m_apBullet1[10];				// 画面内にあるプレイヤーの弾数情報のポインタ
	static CScene2D*m_apBullet2[10];				// 画面内にある敵の弾数情報のポインタ
	int nCnt;										// アニメーションパターンNo
	float m_fAngle;									// 角度
	float m_fLength;								// 長さ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;					// テクスチャ
	D3DXVECTOR3 m_pos;								// ポリゴンの位置
	D3DXVECTOR3 m_move;								// 移動
	D3DXVECTOR3 m_scale;							// 大きさ
	D3DXVECTOR3 m_rot;								// 回転

};

#endif

