//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************************************
// �w�b�_�[�̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene2D.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FADE_SPEED (0.02f)

//*****************************************************************************
// �t�F�[�h�N���X
//*****************************************************************************
class CFade
{
public:
	// �t�F�[�h�̏��
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,

		FADE_MAX,
	} FADE;

	CFade();
	~CFade();
	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void FadeIN(void);
	void FadeOUT(CManager::MODE modeNext);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	CScene2D::VERTEX_2D *m_pVertex;			// 2D�|���S���̃|�C���^
	float m_fAlpha;							// �����x
	CManager::MODE m_modeNext;				// ���̃��[�h
	FADE m_fadeState;						// �t�F�[�h�̏��
};

#endif
