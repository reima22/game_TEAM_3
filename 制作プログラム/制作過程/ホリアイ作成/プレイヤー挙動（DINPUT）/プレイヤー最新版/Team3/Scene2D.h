//=============================================================================
//
// 2D�|���S�� [scene2D.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _SCENE_2D_H_
#define _SCENE_2D_H_

//*****************************************************************************
// �w�b�_�[�̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCENE2D_WIDTH_DEFAULT (200)		// �|���S���̕� (�f�t�H)
#define SCENE2D_HEIGHT_DEFAULT (200)	// �|���S���̍��� (�f�t�H)

//*****************************************************************************
// �|���S���N���X (�h�����F�I�u�W�F�N�g�N���X (scene) �j
//*****************************************************************************
class CScene2D : public CScene
{
public:
	// 2D�̒��_�t�H�[�}�b�g
	typedef struct
	{
		D3DXVECTOR3 pos;	// ���_���W
		float rhw;			// 1.0�Œ�
		D3DCOLOR col;		// ���_�J���[
		D3DXVECTOR2 tex;	// �e�N�X�`�����W
	} VERTEX_2D;

	CScene2D(int nPriority = 3);
	~CScene2D();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTextureUV(D3DXVECTOR2 Vertex_0, D3DXVECTOR2 Vertex_1, D3DXVECTOR2 Vertex_2, D3DXVECTOR2 Vertex_3);
	void SetColor(D3DXCOLOR col);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	VERTEX_2D *m_pVertex;					// 2D�|���S���̃|�C���^

};

#endif