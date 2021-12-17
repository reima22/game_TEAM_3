//=============================================================================
//
// �|�[�Y���� [pause.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"
#include "scene.h"
#include "manager.h"

// �}�N����`
#define PAUSE_POS	(SCREEN_CENTER)

// �O���錾
class CPolygon;

//==============================================================================
// �|�[�Y�N���X
//==============================================================================
class CPause : public CScene
{
public:
	CPause(int nPriority = PRIORITY_PAUSE);
	~CPause();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPause *Create(void);
	static void SetPause(void);
	static bool GetPause(void) { return m_bPause; }

private:
	static bool m_bPause;	// �|�[�Y�̏��
};

#endif