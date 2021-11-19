//=============================================================================
//
// フォグ効果描画処理 [fog.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _FOG_H_
#define _FOG_H_

#include "main.h"

// マクロ定義
#define FOG_START	(620.0f)
#define FOG_END		(1245.0f)

//==============================================================================
// フォグ硬貨クラス
//==============================================================================
class CFog
{
public:
	CFog();
	~CFog();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFog *Create(void);

	float GetFogStart(void) { return m_fFogStart; }
	float GetFogEnd(void) { return m_fFogEnd; }

private:
	float m_fFogStart = 0.0f;		// フォグの開始
	float m_fFogEnd = 0.0f;		// フォグ終了の距離（完全に見えなくなる）
	D3DXCOLOR m_col;			// 色
};
#endif
