
//=============================================================================
//
// ビルボードの設定 [sceneBillboard.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _SCENEBILLBOARD_H_
#define _SCENEBILLBOARD_H_

#include "main.h"
#include "scene.h"

//==============================================================================
// ビルボードシーンクラス
//==============================================================================
class CSceneBillboard : public CScene
{
public:
	CSceneBillboard(int nPriority = PRIORITY_DEFAULT);
	~CSceneBillboard();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSceneBillboard *Create(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetRot(void) { return m_rot; }

	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }

private:
	D3DXVECTOR3 m_pos;								// 位置
	D3DXVECTOR3 m_rot;								// 向き
	D3DXVECTOR2 m_size;								// 大きさ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// バッファへのポインタ
	D3DXMATRIX m_mtxWorld;							// ワールドマトリックス
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;	// テクスチャへのポインタ
};
#endif