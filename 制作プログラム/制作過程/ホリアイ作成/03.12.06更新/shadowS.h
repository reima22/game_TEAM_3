//=============================================================================
//
// �e���f���̐ݒ� [shadowS.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _SHADOWS_H_
#define _SHADOWS_H_

#include "main.h"
#include "scene3D.h"
#include "sceneX.h"

//==============================================================================
// �e���f���N���X
//==============================================================================
class CShadowS : public CSceneX
{
public:
	CShadowS();
	~CShadowS();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CShadowS *Create(D3DXVECTOR3 pos);

	void SetPosition(D3DXVECTOR3 pos);

private:
	//D3DXVECTOR3 m_pos;				// �ʒu
	//D3DXVECTOR3 m_rot;				// �p�x
	LPD3DXMESH m_pMesh;				// ���b�V���|�C���^
	LPD3DXBUFFER m_pBuffMat;		// �}�e���A���o�b�t�@
	DWORD m_nNumMat;				// �}�e���A����
	//D3DXMATRIX m_mtxWorld;			// ���[���h�}�g���b�N�X

	// 2D�|���S��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// �o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_posPolygon;						// �|���S���̈ʒu
	D3DXVECTOR2 m_sizePolygon;						// �|���S���̑傫��
};	
#endif