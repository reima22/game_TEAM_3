//=============================================================================
//
// ���C�g [light.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "Light.h"
#include "manager.h"

//*****************************************************************************
// �J�����N���X
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLight::CLight()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLight::~CLight()
{

}

//=============================================================================
// ������
//=============================================================================
void CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X
	D3DXVECTOR3 vecDir;	// �ݒ�p�����x�N�g��

						// ���C�g���N���A����
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	m_light.Type = D3DLIGHT_DIRECTIONAL;	// ���s����

											// ���C�g�̊g�U����ݒ�
	m_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(-0.2f, -0.8f, -0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_light.Direction = vecDir;

	// ���C�g��ݒ肷��
	pDevice->SetLight(0, &m_light);

	// ���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);

}

//=============================================================================
// �I��
//=============================================================================
void CLight::Uninit(void)
{

}

//=============================================================================
// �X�V
//=============================================================================
void CLight::Update(void)
{

}