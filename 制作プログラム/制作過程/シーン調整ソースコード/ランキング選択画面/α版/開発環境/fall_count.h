//=============================================================================
//
// 落下数カウント描画処理 [fall_count.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _FALL_COUNT_H_
#define _FALL_COUNT_H_

#include "main.h"
#include "fall.h"
#include "scene2D.h"

// マクロ定義
#define FALL_DIGIT_NUM	(3)	// 最大桁数

// 前方宣言
class CNumber;

//==============================================================================
// 落下数カウントクラス
//==============================================================================
class CFallCount : public CFall
{
public:
	CFallCount();
	~CFallCount();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFallCount *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);

	// 数値の設定
	int GetNumber(void) { return m_nFall; }
	void SetNumber(int nFall);

	// 落下数の加算
	void AddFall(int nAdd) { m_nFall += nAdd; }

	// リザルトへの継承
	static int GetFallNum(void) { return m_nFallResult; }

private:
	CNumber *m_apNumber[FALL_DIGIT_NUM];	// ナンバークラスポインタ
	int m_nFall;							// 落下数値
	static int m_nFallResult;				// リザルトへ引き継ぐ値
};
#endif