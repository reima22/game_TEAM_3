//==============================================================================
//
// 影の描画〔shadow.h〕
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _SHADOW_H_
#define _SHADOW_H_
#include "main.h"
#include "scene.h"

//==============================================================================
// マクロ定義
//==============================================================================
//#define MAX_SHADOW	(128)	// 影の最大数

//==============================================================================
// 影クラス
//==============================================================================
class CShadow : public CScene
{
public:
	CShadow();
	~CShadow();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CShadow *Create(D3DXVECTOR3 pos,float fWidth,float fDepth);

	void SetPosShadow(D3DXVECTOR3 pos) { m_pos = pos; }

	void SetWidth(float fWidth) { m_fWidth = fWidth; }
	void SetDepth(float fDepth) { m_fDepth = fDepth; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	// バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;		// テクスチャへのポインタ
	D3DXMATRIX m_mtxWorld;						// ワールドマトリックス
	D3DXVECTOR3 m_pos;							// 位置
	D3DXVECTOR3 m_rot;							// 角度
	float m_fWidth;								// 横幅サイズ
	float m_fDepth;								// 奥行きサイズ
};

#endif
