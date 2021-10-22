//=============================================================================
//
// ���f���Ǘ� [model.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

// �}�N����`
#define VTX_MIN	(D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f))		// �����_�ŏ��l
#define	VTX_MAX	(D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f))	// �����_�ő�l

//==============================================================================
// ���f���Ǘ��N���X
//==============================================================================
class CModel
{
public:

	CModel();
	~CModel();
	HRESULT Init(char *pFileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CModel *Create(char *pFileName,D3DXVECTOR3 pos,D3DXVECTOR3 rot);

	void SetParent(CModel *pModel) { m_pParent = pModel; }	// �e�|�C���^�̐ݒ�
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }		// �}�g���b�N�X�̎擾

	// �ʒu�̐ݒ�
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

	// �p�x�̐ݒ�
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }

	// �e�̃T�C�Y�ݒ�
	D3DXVECTOR2 SetShadowSize(void);	

private:
	LPD3DXMESH m_pMesh;				// ���b�V���|�C���^
	LPD3DXBUFFER m_pBuffMat;		// �}�e���A���o�b�t�@
	DWORD m_nNumMat;				// �}�e���A����

	D3DXMATRIX m_mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;				// �ʒu
	D3DXVECTOR3 m_rot;				// ����
	CModel *m_pParent;				// �e���f���ւ̃|�C���^

	LPDIRECT3DTEXTURE9 *m_pTexture;	// �e�N�X�`���_�u���|�C���^

	D3DXVECTOR3 m_vtxMin;			// ���f���̑傫���̋�ԍ��W�ŏ��l
	D3DXVECTOR3 m_vtxMax;			// ���f���̑傫���̋�ԍ��W�ő�l

	D3DXVECTOR2 m_shadowSize;		// �e�̃T�C�Y
};

#endif