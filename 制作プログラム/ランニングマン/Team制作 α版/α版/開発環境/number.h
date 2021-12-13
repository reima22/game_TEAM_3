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
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ���l�ݒ�
	void SetNumber(int nNumber);

	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);

	// �F�̐ݒ�
	void SetCol(D3DXCOLOR col);

	// �ʒu�̎擾�E�ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }

	// �T�C�Y�̎擾�E�ݒ�
	D3DXVECTOR2 GetSize(void) { return m_size; }
	void SetSize(D3DXVECTOR2 size);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// �o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;								// �ʒu
	D3DXVECTOR2 m_size;								// �T�C�Y
	float m_fLength;								// �Ίp���̒���
	float m_fAngle;									// �Ίp���̊p�x
};

#endif