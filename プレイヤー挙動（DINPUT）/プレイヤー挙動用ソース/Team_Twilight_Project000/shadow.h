//==============================================================================
//
// �e�̕`��kshadow.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _SHADOW_H_
#define _SHADOW_H_
#include "main.h"
#include "scene.h"

//==============================================================================
// �}�N����`
//==============================================================================
//#define MAX_SHADOW	(128)	// �e�̍ő吔

//==============================================================================
// �e�N���X
//==============================================================================
class CShadow : public CScene
{
public:
	CShadow();
	~CShadow();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CShadow *Create(D3DXVECTOR3 pos,float fWidth,float fDepth);

	void SetPosShadow(D3DXVECTOR3 pos) { m_pos = pos; }

	void SetWidth(float fWidth) { m_fWidth = fWidth; }
	void SetDepth(float fDepth) { m_fDepth = fDepth; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	// �o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_rot;							// �p�x
	float m_fWidth;								// �����T�C�Y
	float m_fDepth;								// ���s���T�C�Y
};

#endif
