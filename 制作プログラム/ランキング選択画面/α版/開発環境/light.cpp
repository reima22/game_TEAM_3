//==============================================================================
//
// ���C�g�̐ݒ�klight.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "light.h"
#include "manager.h"
#include "renderer.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CLight::CLight()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CLight::~CLight()
{

}

//==============================================================================
// ����������
//==============================================================================
void CLight::Init(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	D3DXVECTOR3 vecDir;

	// �f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCnt = 0; nCnt < LIGHT_NUM; nCnt++)
	{
		// ���C�g���N���A����
		ZeroMemory(&m_aLight[nCnt], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		m_aLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		// ���C�g�̊g�U����ݒ�
		m_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���C�g�̕�����ݒ�
		if (nCnt == 0)
		{
			vecDir = D3DXVECTOR3(1.0f, -0.0f, -0.0f);
			//vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
		}
		else if (nCnt == 1)
		{
			vecDir = D3DXVECTOR3(0.5f, -1.0f, 0.8f);
			//vecDir = D3DXVECTOR3(-0.2f, -0.8f, 0.4f);
		}
		else if (nCnt == 2)
		{
			vecDir = D3DXVECTOR3(0.5f, -0.0f, 0.0f);
			//vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		}

		D3DXVec3Normalize(&vecDir, &vecDir);		// ���K������
		m_aLight[nCnt].Direction = vecDir;

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCnt, &m_aLight[nCnt]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCnt, TRUE);
	}
}

//==============================================================================
// �I������
//==============================================================================
void CLight::Uninit(void)
{

}

//==============================================================================
// �X�V����
//==============================================================================
void CLight::Update(void)
{

}

//==============================================================================
// ��������
//==============================================================================
CLight *CLight::Create(void)
{
	// ���[�J���ϐ��錾
	CLight *pLight;
	pLight = new CLight;

	// ������
	if (pLight != NULL)
	{
		pLight->Init();
	}

	return pLight;
}