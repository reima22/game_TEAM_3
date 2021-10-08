
//=============================================================================
//
// 3D�|���S�� [scene3D.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _SCENE_3D_H_
#define _SCENE_3D_H_

//*****************************************************************************
// �w�b�_�[�̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �|���S���N���X (�h�����F�I�u�W�F�N�g�N���X (scene) �j
//*****************************************************************************
class CScene3D : public CScene
{
public:
	// 3D�̒��_�t�H�[�}�b�g
	typedef struct
	{
		D3DXVECTOR3 pos;	// ���_���W
		D3DXVECTOR3 nor;	// �@���x�N�g��
		D3DCOLOR col;		// ���_�J���[
		D3DXVECTOR2 tex;	// �e�N�X�`�����W
	} VERTEX_3D;

	CScene3D(int nPriority = 3);
	~CScene3D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTextureUV(D3DXVECTOR2 Vertex_0, D3DXVECTOR2 Vertex_1, D3DXVECTOR2 Vertex_2, D3DXVECTOR2 Vertex_3);
	void SetColor(D3DXCOLOR col);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	static CScene3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

private:
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	VERTEX_3D *m_pVertex;					// 3D�|���S���̃|�C���^

};

#endif