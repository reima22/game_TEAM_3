//==============================================================================
//
// �t�H�O���ʕ`�揈���kfog.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "camera.h"
#include "fog.h"
#include "input.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CFog::CFog()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CFog::~CFog()
{
}

//==============================================================================
// �t�H�O���ʂ̏���������
//==============================================================================
HRESULT CFog::Init(void)
{
	// �����o�[�ϐ�������
	m_fFogStart = FOG_START;
	m_fFogEnd = FOG_END;

	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ���F

	return S_OK;
}

//==============================================================================
// �t�H�O���ʂ̏I������
//==============================================================================
void CFog::Uninit(void)
{

}

//==============================================================================
// �t�H�O���ʂ̍X�V����
//==============================================================================
void CFog::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// �t�H�O�̑���
	// �J�n�_
	if (keyboard->GetPress(CInput::KEYINFO_FOGSTART_PLUS) == true)
	{
		m_fFogStart += 5.0f;
	}

	if (keyboard->GetPress(CInput::KEYINFO_FOGSTART_MINUS) == true)
	{
		m_fFogStart -= 5.0f;
	}

	// ���s�I��
	if (keyboard->GetPress(CInput::KEYINFO_FOGEND_PLUS) == true)
	{
		m_fFogEnd += 5.0f;
	}

	if (keyboard->GetPress(CInput::KEYINFO_FOGEND_MINUS) == true)
	{
		m_fFogEnd -= 5.0f;
	}
}

//==============================================================================
// �t�H�O���ʂ̕`�揈��
//==============================================================================
void CFog::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = CManager::GetRenderer()->GetDevice();

	// �t�H�O��L����
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	// �t�H�O�̐F�w��
	pDevice->SetRenderState(D3DRS_FOGCOLOR, m_col);

	// �o�[�e�b�N�X�t�H�O�̎g�p(���`����)
	pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);

	pDevice->SetRenderState(D3DRS_FOGSTART, *((LPDWORD)(&m_fFogStart)));	
	pDevice->SetRenderState(D3DRS_FOGEND, *((LPDWORD)(&m_fFogEnd)));		

	// �t�H�O�𖳌���
	//pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
}

//==============================================================================
// �t�H�O���ʂ̐�������
//==============================================================================
CFog *CFog::Create(void)
{
	// �C���X�^���X����
	CFog *pFog;
	pFog = new CFog;

	// ������
	if (pFog != NULL)
	{
		pFog->Init();
	}

	return pFog;
}