//=============================================================================
//
// ���C�g�̐ݒ� [light.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

// �}�N����`
#define LIGHT_NUM	(3)

//==============================================================================
// ���C�g�N���X
//==============================================================================
class CLight
{
public:
	CLight();
	~CLight();
	void Init(void);
	void Uninit(void);
	void Update(void);

	static CLight *Create(void);

private:
	D3DLIGHT9 m_aLight[LIGHT_NUM];	// ���C�g���
};
#endif