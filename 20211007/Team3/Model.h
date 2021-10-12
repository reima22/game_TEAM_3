#define _CRT_SECURE_NO_WARNINGS
//=============================================================================
//
// ���f���N���X [model.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//*****************************************************************************
// �w�b�_�[�̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// ���f���N���X
//*****************************************************************************
class CModel
{
public:
	CModel();
	~CModel();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFilePath);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetParent(CModel *pModel) { m_pParent = pModel; }
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFilePath);

private:
	LPD3DXMESH m_pMesh;			// ���b�V���ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;	// �}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;			// �}�e���A���̐�
	D3DXMATRIX m_mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_rot;			// ����
	CModel *m_pParent;			// �e���f���ւ̃|�C���^
};
#endif