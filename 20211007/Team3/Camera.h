//=============================================================================
//
// �J���� [camera.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// �w�b�_�[�̃C���N���[�h
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �J�����N���X
//*****************************************************************************
class CCamera
{
public:
	CCamera();
	~CCamera();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(LPDIRECT3DDEVICE9 pDevice);

private:
	D3DXVECTOR3 m_posV;	// ���_
	D3DXVECTOR3 m_posR;	// �����_
	D3DXVECTOR3 m_vecU;	// ������x�N�g��
	D3DXMATRIX m_mtxProjection;		// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;			// �r���[�}�g���b�N�X
};
#endif

