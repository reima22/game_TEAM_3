
//=============================================================================
//
// ���U���g���[�h���� [result.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "scene.h"
#include "mode.h"

// �O���錾
class CResultLogo;
class CResultScore;
class CResultFallCount;

//==============================================================================
// ���U���g���[�h�N���X
//==============================================================================
class CResult : public CMode
{
public:
	// �Q�[���I�����̃N���A���
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

	static ENDSTATE m_endState;	// �Q�[���I�����̏��
};

#endif
