//==============================================================================
//
// �J�����̐ݒ�kcamera.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "gamepad.h"
#include "game.h"
#include "player.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CCamera::CCamera()
{

}

//==============================================================================
// �f�B�X�g���N�^
//==============================================================================
CCamera::~CCamera()
{

}

//==============================================================================
// ����������
//==============================================================================
void CCamera::Init(void)
{
	SetInit();
}

//==============================================================================
// �I������
//==============================================================================
void CCamera::Uninit(void)
{

}

//==============================================================================
// �X�V����
//==============================================================================
void CCamera::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CGamepad *gamepad = CManager::GetInputGamepad();

	//���_�̈ړ�(���E)(Z,C�L�[)
	if (keyboard->GetPress(CInput::KEYINFO_TURN_LEFT) == true || gamepad->GetPress(CInput::KEYINFO_TURN_LEFT) == true)
	{
		m_rot.y += CAMERA_TURN;

		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2.0f;
		}

		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fLength;
		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fLength;
	}
	if (keyboard->GetPress(CInput::KEYINFO_TURN_RIGHT) == true || gamepad->GetPress(CInput::KEYINFO_TURN_RIGHT) == true)
	{
		m_rot.y -= CAMERA_TURN;

		if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2.0f;
		}

		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fLength;
		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fLength;
	}

	if (keyboard->GetPress(CInput::KEYINFO_CAMERA_UP) == true)
	{
		m_fHeightV += 2.0f;
	}

	if (keyboard->GetPress(CInput::KEYINFO_CAMERA_DOWN) == true)
	{
		m_fHeightV -= 2.0f;
	}

	// �v���C���[�̎擾
	CPlayer *pPlayer;
	pPlayer = CGame::GetPlayer();

	D3DXVECTOR3 posPlayer = VECTOR3_NULL;
	D3DXVECTOR3 rotDestPlayer = VECTOR3_NULL;
	
	if (pPlayer != NULL)
	{
		posPlayer = pPlayer->GetPosition();
		rotDestPlayer = pPlayer->GetRotDest();
	}

	// �ړI�̒����_
	m_posRDest.x = posPlayer.x - m_fFront * sinf(rotDestPlayer.y);
	m_posRDest.z = posPlayer.z - m_fFront * cosf(rotDestPlayer.y);
	m_posRDest.y = posPlayer.y + m_fHeightR;

	// �ړI�̎��_
	m_posVDest.x = posPlayer.x - sinf(m_rot.y) * m_fLength;
	m_posVDest.z = posPlayer.z - cosf(m_rot.y) * m_fLength;
	m_posVDest.y = posPlayer.y + cosf(m_rot.x) * (m_fLength + m_fHeightV);

	// �����_�̈ʒu�X�V
	m_posR.x += (m_posRDest.x - m_posR.x) * CAMERA_SPDOWN;
	m_posR.z += (m_posRDest.z - m_posR.z) * CAMERA_SPDOWN;
	m_posR.y += (m_posRDest.y - m_posR.y) * CAMERA_SPDOWN;

	// ���_�̈ʒu�X�V
	m_posV.x += (m_posVDest.x - m_posV.x) * CAMERA_SPDOWN;
	m_posV.z += (m_posVDest.z - m_posV.z) * CAMERA_SPDOWN;
	m_posV.y += (m_posVDest.y - m_posV.y) * CAMERA_SPDOWN;
}

//==============================================================================
// �J�����̐���
//==============================================================================
CCamera *CCamera::Create(void)
{
	// ���[�J���ϐ��錾
	CCamera *pCamera;
	pCamera = new CCamera;

	// ������
	if (pCamera != NULL)
	{
		pCamera->Init();
	}

	return pCamera;
}

//==============================================================================
// �J�����̐ݒ菈��
//==============================================================================
void CCamera::SetCamera(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(
		&m_mtxProjection,
		D3DXToRadian(45.0f),		// ��p�̐ݒ�
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		// ��ʔ䗦�̐ݒ�
		10.0f,											// ��O���E�̕`�拗��
		3000.0f);										// �����E�̕`�拗��

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(
		&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//==============================================================================
// �J�����̈ʒu������
//==============================================================================
void CCamera::SetInit(void)
{
	// �ϐ��ݒ�
	m_posV = VECTOR3_NULL;						// �J�������_�̈ʒu
	m_posR = VECTOR3_NULL;						// �����_�ʒu
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// ������x�N�g��
	m_rot = VECTOR3_NULL;						// �J�����̊p�x
	m_fLength = 400.0f;							// ���_�E�����_�̋���
	m_fFront = 15.0f;							// �v���C���[�̑O��
	m_fHeightR = 0.0f;							// �����_�̍���
	m_fHeightV = 60.0f;							// ���_�̍���
}