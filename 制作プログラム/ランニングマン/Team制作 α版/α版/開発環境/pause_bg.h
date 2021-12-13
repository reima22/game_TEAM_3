//=============================================================================
//
// ポーズ背景処理 [pause_bg.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _PAUSE_BG_H_
#define _PAUSE_BG_H_

#include "main.h"
#include "pause.h"

//==============================================================================
// ポーズクラス
//==============================================================================
class CPauseBg : public CPause
{
public:
	CPauseBg(int nPriority = CScene::PRIORITY_PAUSE);
	~CPauseBg();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPauseBg *Create(D3DXVECTOR3 pos);

private:
	CScene2D *m_pScene2D;	// 2Dポリゴンのポインタ
};
#endif
