
//=============================================================================
//
// 3Dポリゴン [scene3D.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _SCENE_3D_H_
#define _SCENE_3D_H_

//*****************************************************************************
// ヘッダーのインクルード
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// ポリゴンクラス (派生元：オブジェクトクラス (scene) ）
//*****************************************************************************
class CScene3D : public CScene
{
public:
	// 3Dの頂点フォーマット
	typedef struct
	{
		D3DXVECTOR3 pos;	// 頂点座標
		D3DXVECTOR3 nor;	// 法線ベクトル
		D3DCOLOR col;		// 頂点カラー
		D3DXVECTOR2 tex;	// テクスチャ座標
	} VERTEX_3D;

	CScene3D(int nPriority = 3);
	~CScene3D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTextureUV(D3DXVECTOR2 Vertex_0, D3DXVECTOR2 Vertex_1, D3DXVECTOR2 Vertex_2, D3DXVECTOR2 Vertex_3);
	void SetColor(D3DXCOLOR col);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	static CScene3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

private:
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	VERTEX_3D *m_pVertex;					// 3Dポリゴンのポインタ

};

#endif