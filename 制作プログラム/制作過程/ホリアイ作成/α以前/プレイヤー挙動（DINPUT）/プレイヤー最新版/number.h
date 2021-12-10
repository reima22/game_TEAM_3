//=============================================================================
//
// ���l�`�揈�� [number.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"
#include "scene.h"

//==============================================================================
// �i���o�[�N���X
//==============================================================================
class CNumber
{
public:
	CNumber();
	~CNumber();
	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNumber(int nNumber);

	static CNumber *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);

	void SetCol(D3DXCOLOR col);
	void SetSize(D3DXVECTOR2 size);

	D3DXVECTOR2 GetSize(void) { return m_size; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// �o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;								// �ʒu
	float m_fLength;								// �Ίp���̒���
	float m_fAngle;									// �Ίp���̊p�x
	D3DXVECTOR2 m_size;								// �T�C�Y
};

#endif