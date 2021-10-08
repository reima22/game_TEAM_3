//=============================================================================
//
// �J���� [camera.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "Camera.h"
#include "Input.h"
#include "Manager.h"

//*****************************************************************************
// �J�����N���X
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// ������
//=============================================================================
void CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 50.0f, -1.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = VECTOR3_ZERO;

	m_fCamDist = CAMERA_DISTANCE;
	m_fCamSpd = CAMERA_SPEED;
}

//=============================================================================
// �I��
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
// �X�V
//=============================================================================
void CCamera::Update(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();

	// inputs
	if (pKeyboard->GetPress(DIK_W))
	{
		if (pKeyboard->GetPress(DIK_D))
			MoveR(45.0f);
		else if (pKeyboard->GetPress(DIK_A))
			MoveR(-45.0f);
		else
			MoveR(0.0f);
	}
	else if (pKeyboard->GetPress(DIK_S))
	{
		if (pKeyboard->GetPress(DIK_D))
			MoveR(135.0f);
		else if (pKeyboard->GetPress(DIK_A))
			MoveR(-135.0f);
		else
			MoveR(-180.0f);
	}
	else if (pKeyboard->GetPress(DIK_A))
		MoveR(-90.0f);
	else if (pKeyboard->GetPress(DIK_D))
		MoveR(90.0f);
	if (pKeyboard->GetPress(DIK_SPACE))
		m_posR.y += m_fCamSpd;
	else if (pKeyboard->GetPress(DIK_LCONTROL))
		m_posR.y -= m_fCamSpd;



	CInputMouse *pMouse = CManager::GetInputMouse();

	D3DXVECTOR2 mouseVel = pMouse->GetVelocity() / 300;
	m_rot.y += mouseVel.x;
	m_rot.z += mouseVel.y;

	if (m_rot.z > 1.2f) m_rot.z = 1.2f;
	if (m_rot.z < -1.2f) m_rot.z = -1.2f;

	m_posV.x = m_posR.x + sinf(m_rot.y) * cosf(m_rot.z) * m_fCamDist;
	m_posV.z = m_posR.z + cosf(m_rot.y) * cosf(m_rot.z) * m_fCamDist;
	m_posV.y = m_posR.y + (m_rot.z) * m_fCamDist;
}

//=============================================================================
// �J������ݒ�
//=============================================================================
void CCamera::SetCamera(LPDIRECT3DDEVICE9 pDevice)
{
	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�𐶐�
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 1000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X�̐���
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

void CCamera::MoveR(float fAngDeg)
{
	m_posR.x += sinf(m_rot.y + D3DX_PI + D3DXToRadian(fAngDeg)) * m_fCamSpd;
	m_posR.z += cosf(m_rot.y + D3DX_PI + D3DXToRadian(fAngDeg)) * m_fCamSpd;
}