//=============================================================================
//
// 2D�|���S���`�揈�� [scene2D.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"
#include "texture.h"

//==============================================================================
// 2D�|���S���N���X
//==============================================================================
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority = PRIORITY_DEFAULT);
	~CScene2D();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScene2D *Create(void);	// 2D�|���S���̐���

	// �ʒu�̎擾�E�ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }

	// �T�C�Y�̎擾�E�ݒ�
	D3DXVECTOR2 GetSize(void) { return m_size; }
	void SetSize(D3DXVECTOR2 size);

	// �p�x�̎擾�E�ݒ�
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }

	// �e�N�X�`���̐ݒ�
	void BindTexture(int nIdx);

	// �e�N�X�`�����W�̐ݒ�
	void SetTex(int nCutX, int nCutY, int nPatternX, int nPatternY, float fTexX, float fTexY);
	
	// �F���̐ݒ�
	void SetCol(D3DXCOLOR col);

private:
	D3DXVECTOR3 m_pos;								// �ʒu
	D3DXVECTOR3 m_rot;								// �p�x
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// �o�b�t�@�ւ̃|�C���^

	float m_fLength;								// �Ίp���̒���
	float m_fAngle;									// �Ίp���̊p�x
	D3DXVECTOR2 m_size;								// �|���S���̃T�C�Y
};

#endif
