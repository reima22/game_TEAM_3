//=============================================================================
//
// ポーズベース処理 [pause_base.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _PAUSE_BASE_H_
#define _PAUSE_BASE_H_

#include "main.h"
#include "pause.h"

//==============================================================================
// ポーズベースクラス
//==============================================================================
class CPauseBase : public CScene2D
{
public:
	CPauseBase(int nPriority = CScene::PRIORITY_PAUSE);
	~CPauseBase();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPauseBase *Create(void);
};
#endif
