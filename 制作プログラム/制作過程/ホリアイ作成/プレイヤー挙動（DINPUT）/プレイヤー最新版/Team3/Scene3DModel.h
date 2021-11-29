
//=============================================================================
//
// 3D���f�� [Scene3DModel.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _SCENE_3D_MODEL_H_
#define _SCENE_3D_MODEL_H_

//*****************************************************************************
// �w�b�_�[�̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "Resource.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// ���f���N���X (�h�����F�I�u�W�F�N�g�N���X (scene) �j
//*****************************************************************************
class CScene3DModel : public CScene
{
public:
	CScene3DModel(int nPriority = 3);
	~CScene3DModel();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindModel(string modelName);
	D3DXMATRIX GetMatrix(void) { return m_mtxWorld; }

	static CScene3DModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, string modelName);

private:
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	CResourceManager *m_pResourceManager;
	string m_modelName;
};

#endif