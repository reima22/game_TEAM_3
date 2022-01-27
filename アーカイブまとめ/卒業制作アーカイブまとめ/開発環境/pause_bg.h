//=============================================================================
//
// �|�[�Y�w�i���� [pause_bg.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _PAUSE_BG_H_
#define _PAUSE_BG_H_

#include "main.h"
#include "pause.h"

//==============================================================================
// �|�[�Y�N���X
//==============================================================================
class CPauseBg : public CScene
{
public:
	CPauseBg(int nPriority = CScene::PRIORITY_PAUSE);
	~CPauseBg();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPauseBg *Create(void);

private:
	CScene2D *m_pScene2D;	// 2D�|���S���̃|�C���^
};
#endif
