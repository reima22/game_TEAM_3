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
#define FOG_START	(620.0f)	// �t�H�O���ʂ̋����J�n�_
#define FOG_END		(1245.0f)	// �t�H�O���ʂ̋����I���_
#define FOG_COL_VALLEY	(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f))		// �k�J�X�e�[�W�̃t�H�O�F
#define FOG_COL_OCEAN	(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f))		// �C�m�X�e�[�W�̃t�H�O�F
#define FOG_COL_LAVA	(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))		// �n��X�e�[�W�̃t�H�O�F

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

	// �����̐ݒ�
	float GetFogStart(void) { return m_fFogStart; }
	float GetFogEnd(void) { return m_fFogEnd; }

	// �t�H�O���ʂ̐F�ݒ�
	void SetFogCol(D3DXCOLOR col) { m_col = col; }

private:
	float m_fFogStart;	// �t�H�O���ʂ̊J�n
	float m_fFogEnd;	// �t�H�O���ʏI���̋����i���S�Ɍ����Ȃ��Ȃ�j
	D3DXCOLOR m_col;	// �F
};
#endif
