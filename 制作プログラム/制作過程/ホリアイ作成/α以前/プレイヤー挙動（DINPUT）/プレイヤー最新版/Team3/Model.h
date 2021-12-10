#define _CRT_SECURE_NO_WARNINGS
//=============================================================================
//
// モデルクラス [model.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//*****************************************************************************
// ヘッダーのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// モデルクラス
//*****************************************************************************
class CModel
{
public:
	CModel();
	~CModel();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFilePath);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetParent(CModel *pModel) { m_pParent = pModel; }
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFilePath);

private:
	LPD3DXMESH m_pMesh;			// メッシュへのポインタ
	LPD3DXBUFFER m_pBuffMat;	// マテリアルへのポインタ
	DWORD m_dwNumMat;			// マテリアルの数
	D3DXMATRIX m_mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3 m_pos;			// 位置
	D3DXVECTOR3 m_rot;			// 向き
	CModel *m_pParent;			// 親モデルへのポインタ
};
#endif