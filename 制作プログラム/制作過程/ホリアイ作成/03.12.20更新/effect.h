
//=============================================================================
//
// エフェクトの設定 [effect.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "scene.h"
//#include "sceneBillboard.h"

//==============================================================================
// エフェクトクラス
//==============================================================================
class CEffect : public CScene
{
public:
	typedef enum
	{
		EFFECTTYPE_NORMAL = 0,		// 通常
		EFFECTTYPE_SANDSMOKE,		// 砂煙
		EFFECTTYPE_PARTICLE,		// パーティクルエフェクト
		EFFECTTYPE_MAX
	}EFFECTTYPE;

	CEffect(int nPriority = PRIORITY_EFFECT);
	~CEffect();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEffect *Create(void);

	void SetEffect(void);
	void SetVertex(void);
	void EffectMove(void);

	// 位置の取得・設定
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }

	// 角度の取得・設定
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }

	// 色の取得・設定
	D3DXCOLOR GetColor(void) { return m_col; }
	void SetColor(D3DXCOLOR col) { m_col = col; }

	// サイズの取得・設定
	D3DXVECTOR2 GetSize(void) { return m_size; }
	void SetSize(D3DXVECTOR2 size) { m_size = size; }

	// 透明度低下値の設定
	float GetAlphaDown(void) { return m_fAlphaDown; }
	void SetAlphaDown(float fAlphaDown) { m_fAlphaDown = fAlphaDown; }

	// 移動力取得・設定
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

	// テクスチャの設定
	void SetTexture(char *pText);

	// 種類の設定
	void SetType(EFFECTTYPE effectType) { m_effectType = effectType; }

private:
	D3DXVECTOR3 m_pos;								// 位置
	D3DXVECTOR3 m_rot;								// 向き
	D3DXVECTOR2 m_size;								// 大きさ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// バッファへのポインタ
	D3DXMATRIX m_mtxWorld;							// ワールドマトリックス
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;			// テクスチャへのポインタ

	D3DXVECTOR3 m_move;								// 移動力
	D3DXCOLOR m_col;								// 色
	EFFECTTYPE m_effectType;						// エフェクトの種類
	float m_fAlphaDown;								// エフェクトの透明度低下の値
	float m_fRadius;								// エフェクト半径
	
	static int m_nNum;
	int m_nIdx;
};

//==============================================================================
// 砂煙エフェクト
//==============================================================================
class CEffectSand : public CEffect
{
public:
	CEffectSand();
	~CEffectSand();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEffectSand *Create(D3DXVECTOR3 pos);

private:
	CEffect *m_pEffect;
};

#endif