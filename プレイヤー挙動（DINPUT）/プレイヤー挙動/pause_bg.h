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

// �}�N����`
#define P_BG_MAX	(2)	// �w�i��

// �O���錾
class CPolygon;

//==============================================================================
// �|�[�Y�N���X
//==============================================================================
class CPauseBg : public CScene2D
{
public:
	CPauseBg(int nPriority = CScene::PRIORITY_PAUSE);
	~CPauseBg();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPauseBg *Create(D3DXVECTOR3 pos);
};
#endif
