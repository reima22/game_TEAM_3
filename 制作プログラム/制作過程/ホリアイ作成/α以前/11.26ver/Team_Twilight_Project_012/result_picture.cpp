//==============================================================================
//
// ���U���g�ɕ`�悷��}�̏����kresult_picture.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "sound.h"
#include "result.h"
#include "result_picture.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CResultPicture::CResultPicture(int nPriority) : CResult(nPriority)
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CResultPicture::~CResultPicture()
{
}

//==============================================================================
// ���U���g�\���}�̏���������
//==============================================================================
HRESULT CResultPicture::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 size, char *pTypeCheck)
{
	// �|���S������
	if (m_pScene2D == NULL)
	{
		m_pScene2D = CScene2D::Create();
		m_pScene2D->SetPosition(pos);
		m_pScene2D->SetSize(size);
		m_pScene2D->SetCol(COLOR_DEFAULT);
		m_pScene2D->SetTex(1, 1, 0, 0, 0, 0);
		m_pScene2D->BindTexture(pTypeCheck);
	}

	return S_OK;
}

//==============================================================================
// ���U���g�\���}�̏I������
//==============================================================================
void CResultPicture::Uninit(void)
{
	if (m_pScene2D != NULL)
	{// NULL�`�F�b�N��ɔj��
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	Release();	// �C���X�^���X�̃f���[�g
}

//==============================================================================
// ���U���g�\���}�̍X�V����
//==============================================================================
void CResultPicture::Update(void)
{

}

//==============================================================================
// ���U���g�\���}�̕`�揈��
//==============================================================================
void CResultPicture::Draw(void)
{
}

//==============================================================================
// ���U���g�\���}�̐�������
//==============================================================================
CResultPicture *CResultPicture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 size, char *pTypeCheck)
{
	// �C���X�^���X����
	CResultPicture *pResultPicture;
	pResultPicture = new CResultPicture;

	// ������
	if (pResultPicture != NULL)
	{
		pResultPicture->Init(pos, rot, size, pTypeCheck);
	}

	return pResultPicture;
}