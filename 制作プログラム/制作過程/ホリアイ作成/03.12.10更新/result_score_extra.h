//=============================================================================
//
// 他リザルトスコア描画処理 [result_score_extra.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RESULT_SCORE_EXTRA_H_
#define _RESULT_SCORE_EXTRA_H_

#include "main.h"
#include "scene.h"
#include "result.h"
#include "ranking.h"
#include "score.h"

// マクロ定義
#define EXSCORE_TIMER_POS		(D3DXVECTOR3(580.0f, 450.0f, 0.0f))	// タイマー計算数列

#define EXSCORE_TIMERCALCU_POS	(D3DXVECTOR3(850.0f, 450.0f, 0.0f))	// タイマー計算結果数列

#define EXSCORE_COUNT_POS		(D3DXVECTOR3(580.0f, 650.0f, 0.0f))	// カウント計算数列

#define EXSCORE_COUNTCALCU_POS	(D3DXVECTOR3(850.0f, 650.0f, 0.0f))	// カウント計算結果数列

#define EXSCORE_SIZE			(D3DXVECTOR2(20.0f, 30.0f))			// 数値一桁のサイズ
#define EXSCORE_DIGIT			(4)									// 桁数
#define EXSCORE_TIMER			(1000)								// タイマー計算基準数値
#define EXSCORE_COUNT			(1000)								// カウント計算基準数値

#define EXSCORE_CALCU_SIZE		(D3DXVECTOR2(25.0f, 40.0f))			// 計算結果数値一桁のサイズ
#define EXSCORE_CALCU_DIGIT		(8)									// 計算結果桁数

//==============================================================================
// 他リザルトスコア描画クラス
//==============================================================================
class CResultScoreEx : public CResult
{
public:
	CResultScoreEx(int nPriority = PRIORITY_UI);
	~CResultScoreEx();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nDigit, int nScore);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CResultScoreEx *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nDigit, int nScore);

	int GetScoreEx(void) { return m_nScoreEx; }
	void SetScoreEx(int nScore);

	// 色の設定
	void SetCol(D3DXCOLOR col);

	// 数値のシャッフル
	void ShffleNum(int nType);

private:
	CNumber **m_pNumber;	// 数字クラス
	int m_nDigit;			// 桁数
	int m_nScoreEx;			// スコア値
	int m_nShfflCnt;		// シャッフルカウント
};
#endif
