//=============================================================================
//
// �{�[�i�X���S�`�揈�� [bonus_logo.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _BONUS_LOGO_H_
#define _BONUS_LOGO_H_

#include "main.h"
#include "bonus.h"

//==============================================================================
// ���������S�N���X
//==============================================================================
class CBonusLogo : public CBonus
{
public:
	CBonusLogo();
	~CBonusLogo();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBonusLogo *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);

private:
	CScene2D *m_pScene2D;	// 2D�N���X�|�C���^
};

#endif