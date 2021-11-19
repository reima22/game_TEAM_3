//=============================================================================
//
// �t�H�O���ʕ`�揈�� [fog.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _FOG_H_
#define _FOG_H_

#include "main.h"

// �}�N����`
#define FOG_START	(620.0f)
#define FOG_END		(1245.0f)

//==============================================================================
// �t�H�O�d�݃N���X
//==============================================================================
class CFog
{
public:
	CFog();
	~CFog();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFog *Create(void);

	float GetFogStart(void) { return m_fFogStart; }
	float GetFogEnd(void) { return m_fFogEnd; }

private:
	float m_fFogStart = 0.0f;		// �t�H�O�̊J�n
	float m_fFogEnd = 0.0f;		// �t�H�O�I���̋����i���S�Ɍ����Ȃ��Ȃ�j
	D3DXCOLOR m_col;			// �F
};
#endif
