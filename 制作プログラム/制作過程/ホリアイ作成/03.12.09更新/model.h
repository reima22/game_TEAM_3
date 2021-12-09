//=============================================================================
//
// ���f���Ǘ� [model.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
#include "scene3D.h"

// �}�N����`
#define VTX_MIN	(D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f))		// �����_�ŏ��l
#define	VTX_MAX	(D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f))	// �����_�ő�l
#define COLLISION_NUM	(4)	// �l���ʂ̓����蔻�萔

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

	// �����蔻��p�ݒ�
	void SetCollisionInfo(void);

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

	// 4�Ӎŏ��l�̎擾
	D3DXVECTOR3 GetVtxMin(void) { return m_vtxMin; }

	// 4�Ӎő�l�̎擾
	D3DXVECTOR3 GetVtxMax(void) { return m_vtxMax; }

	// 4���_�̎擾
	D3DXVECTOR3 GetPosVtx(int nIdx) { return m_aPosVtx[nIdx]; }

	// 4�����x�N�g���̎擾
	D3DXVECTOR3 GetVecVtx(int nIdx) { return m_aVecVtx[nIdx]; }

	// �ړ��͂̎擾�E�ݒ�
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

	// �ߋ��̈ʒu�̎擾�E�ݒ�
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	void SetPosOld(D3DXVECTOR3 pos) { m_posOld = pos; }

private:
	LPD3DXMESH m_pMesh;						// ���b�V���|�C���^
	LPD3DXBUFFER m_pBuffMat;				// �}�e���A���o�b�t�@
	DWORD m_nNumMat;						// �}�e���A����

	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;						// �ʒu
	D3DXVECTOR3 m_rot;						// ����
	D3DXVECTOR3 m_posOld;					// �ߋ��̈ʒu
	D3DXVECTOR3 m_move;						// �ړ���
	CModel *m_pParent;						// �e���f���ւ̃|�C���^

	LPDIRECT3DTEXTURE9 *m_pTexture;			// �e�N�X�`���_�u���|�C���^

	D3DXVECTOR3 m_vtxMin;					// ���f���̑傫���̋�ԍ��W�ŏ��l
	D3DXVECTOR3 m_vtxMax;					// ���f���̑傫���̋�ԍ��W�ő�l

	D3DXVECTOR2 m_shadowSize;				// �e�̃T�C�Y

	float m_aAngle[COLLISION_NUM];			// 4���_�ւ̊p�x
	D3DXVECTOR3 m_aPosVtx[COLLISION_NUM];	// ���_�ʒu
	D3DXVECTOR3 m_aVecVtx[COLLISION_NUM];	// 4�Ӄx�N�g��
};

#endif