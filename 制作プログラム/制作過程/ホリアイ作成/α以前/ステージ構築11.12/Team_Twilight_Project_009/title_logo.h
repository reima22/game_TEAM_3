//=============================================================================
//
// タイトルロゴ描画処理 [title_logo.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

// マクロ定義
#define T_LOGO_POS		(D3DXVECTOR3(300.0f, -1000.0f, 0.0f))	// ロゴの位置
#define T_LOGO_SIZE		(D3DXVECTOR2(900.0f / 2.0f, 450.0f / 2.0f))
#define COLOR_CNT		(50)
#define POS_START_Y		(550.0f)								//	START,Y軸の位置
#define MOVE_START_Y	(-8.0f)							//	START,Y軸の移動値


// 前方宣言
//class CPolygon;

//==============================================================================
// UIクラス
//==============================================================================
class CTitleLogo : public CScene2D
{
public:
	CTitleLogo(int nPriority = PRIORITY_UI);
	~CTitleLogo();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTitleLogo *Create(D3DXVECTOR3 pos);

	static bool GetLogoState(void) { return m_bLogoMoveEnd; }

private:
	CScene2D *m_pScene2D;		// 2Dポリゴンクラスポインタ

	D3DXVECTOR3 m_pos;			// 位置
	D3DXVECTOR3 m_move;			// 移動力
	D3DXCOLOR m_col;			// 色

	bool m_bEnter;
	bool m_bTutorial;
	int m_nTimer;
	int m_nTimeColor;
	int m_nCntColor;

	int m_nMoveCnt;				// ロゴ移動のカウント
	static bool m_bLogoMoveEnd;	// ロゴ移動の終了
};
#endif
