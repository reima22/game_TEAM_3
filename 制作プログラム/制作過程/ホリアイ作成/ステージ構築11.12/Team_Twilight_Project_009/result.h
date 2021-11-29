
//=============================================================================
//
// リザルトモード処理 [result.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "scene.h"
#include "mode.h"

// 前方宣言
class CResultLogo;
class CResultScore;
class CResultFallCount;

//==============================================================================
// リザルトモードクラス
//==============================================================================
class CResult : public CMode
{
public:
	// ゲーム終了時のクリア状態
	typedef enum
	{
		ENDSTATE_NONE = 0,
		ENDSTATE_CLEAR,
		ENDSTATE_GAMEOVER,
		ENDSTATE_MAX
	}ENDSTATE;

	CResult(int nPriority = PRIORITY_DEFAULT);
	~CResult();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CResult *Create(void);
	static void SetEndState(ENDSTATE endState);
	static ENDSTATE GetEndState(void) { return m_endState; }

private:
	static CResultLogo *m_pResultLogo;
	static CResultScore *m_pResultScore;
	static CResultFallCount *m_pResultFallCount;

	static ENDSTATE m_endState;	// ゲーム終了時の状態
};

#endif
