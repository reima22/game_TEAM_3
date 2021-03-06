//=============================================================================
//
// 開始時カウントダウン描画処理 [start_cntdown.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _START_CNTDOWN_H_
#define _START_CNTDOWN_H_

#include "main.h"
#include "scene2D.h"

// 前方宣言
//class CScene2D;

//==============================================================================
// 開始時カウントダウンクラス
//==============================================================================
class CStartCntdown : public CScene2D
{
public:
	typedef enum
	{
		CNTDOWN_GO = 0,	// テクスチャ「GO」
		CNTDOWN_ONE,	// テクスチャ「1」
		CNTDOWN_TWO,	// テクスチャ「2」
		CNTDOWN_THREE,	// テクスチャ「3」
		CNTDOWM_MAX
	}CNTDOWN;

	CStartCntdown(int nPriority = PRIORITY_UI);
	~CStartCntdown();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CStartCntdown *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);

	//void TimerDecrease(void);		// タイマー減少

	// タイマー数値の取得・設定
	//int GetNumber(void) { return m_nTimer; }
	//void SetNumber(int nTimer);

	// タイマーカウント開始フラグ設定
	bool GetStartCntdown(void) { return m_bStartCntdown; }
	void SetStartCntdown(bool bStartCntdown) { m_bStartCntdown = bStartCntdown; }

private:
	CScene2D *m_pScene2D;							// 2Dポリゴンクラスポインタ
	//LPDIRECT3DTEXTURE9 m_pTexture[CNTDOWM_MAX];	// カウントテクスチャ
	int m_nCntDown;									// タイマー数値
	int m_nDecereaseCnt;							// 減少カウンター
	CNTDOWN m_cntDown;								// 現在のカウント
	bool m_bStartCntdown;							// カウント開始のフラグ
};

#endif
