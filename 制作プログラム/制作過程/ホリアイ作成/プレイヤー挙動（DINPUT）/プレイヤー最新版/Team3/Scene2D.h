//=============================================================================
//
// 2Dポリゴン [scene2D.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _SCENE_2D_H_
#define _SCENE_2D_H_

//*****************************************************************************
// ヘッダーのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCENE2D_WIDTH_DEFAULT (200)		// ポリゴンの幅 (デフォ)
#define SCENE2D_HEIGHT_DEFAULT (200)	// ポリゴンの高さ (デフォ)

//*****************************************************************************
// ポリゴンクラス (派生元：オブジェクトクラス (scene) ）
//*****************************************************************************
class CScene2D : public CScene
{
public:
	// 2Dの頂点フォーマット
	typedef struct
	{
		D3DXVECTOR3 pos;	// 頂点座標
		float rhw;			// 1.0固定
		D3DCOLOR col;		// 頂点カラー
		D3DXVECTOR2 tex;	// テクスチャ座標
	} VERTEX_2D;

	CScene2D(int nPriority = 3);
	~CScene2D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTextureUV(D3DXVECTOR2 Vertex_0, D3DXVECTOR2 Vertex_1, D3DXVECTOR2 Vertex_2, D3DXVECTOR2 Vertex_3);
	void SetColor(D3DXCOLOR col);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	VERTEX_2D *m_pVertex;					// 2Dポリゴンのポインタ

};

#endif