//=============================================================================
//
// �`���[�g���A�����[�h���� [tutorial.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "scene.h"
#include "mode.h"

// �O���錾
class CTutorialPage;	// �`���[�g���A���y�[�W�|�C���^

//==============================================================================
// �`���[�g���A�����[�h�N���X
//==============================================================================
class CTutorial : public CMode
{
public:
	CTutorial(int nPriority = PRIORITY_DEFAULT);
	~CTutorial();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTutorial *Create(void);

private:
	static CTutorialPage *m_pTutorialPage;	// �`���[�g���A���y�[�W�|�C���^
};

#endif
