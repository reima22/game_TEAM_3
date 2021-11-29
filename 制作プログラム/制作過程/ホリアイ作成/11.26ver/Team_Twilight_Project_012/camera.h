//=============================================================================
//
// �J�����̐ݒ� [camera.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

#define CAMERA_TURN			(D3DX_PI / 100.0f)	// �J�������񑬓x
#define CAMERA_SPDOWN		(0.1f)				// �J�����̌����W��
#define CAMERA_LENGTH		(400.0f)			// ���_�E�����_�Ԃ̋���
#define CAMERA_FORNT		(15.0f)				// �L�������ʂɒ����_��u���L�����Ƃ̋���
#define CAMERA_HEIGHT_R		(0.0f)				// �����_�̍���
#define CAMERA_HEIGHT_V		(-100.0f)			// ���_�̍���
#define CAMERA_LIMIT_MIN	(10.0f)				// �J�����̕`�悷���O���E
#define CAMERA_LIMIT_MAX	(3000.0f)			// �J�����̕`�悷�鉜���E

//==============================================================================
// �J�����N���X
//==============================================================================
class CCamera
{
public:
	CCamera();
	~CCamera();
	void Init(void);
	void Uninit(void);
	void Update(void);

	static CCamera *Create(void);

	void SetCamera(void);
	D3DXVECTOR3 GetRotation(void) { return m_rot; }	// �����̎擾

	void SetInit(void);

private:
	D3DXMATRIX m_mtxView;		// �r���[�}�g���b�N�X
	D3DXMATRIX m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXVECTOR3 m_posV;			// ���_
	D3DXVECTOR3 m_posR;			// �����_
	D3DXVECTOR3 m_vecU;			// ������x�N�g��
	D3DXVECTOR3 m_rot;			// ����
	float m_fLength;			// ����
	float m_fFront;				// �O������
	float m_fHeightR;			// �����_�ʒu
	float m_fHeightV;			// ���_�ʒu

	D3DXVECTOR3 m_posVDest;		// �ړI�̎��_
	D3DXVECTOR3 m_posRDest;		// �ړI�̒����_
};
#endif