//==============================================================================
//
// �|�[�Y�x�[�X�����kpause_base.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "pause_base.h"
#include "input.h"
#include "textdata.h"
#include "textdata_pause.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CPauseBase::CPauseBase(int nPriority) : CScene(nPriority)
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CPauseBase::~CPauseBase()
{
}

//==============================================================================
// �|�[�Y�x�[�X�̏���������
//==============================================================================
HRESULT CPauseBase::Init(void)
{
	// �e�L�X�g�f�[�^�̎擾
	CTextDataPause *pDataPause;
	pDataPause = CTextData::GetDataPause();

	D3DXVECTOR3 pos = pDataPause->GetPosition(CTextDataPause::PAUSEPOLY_BASE);
	D3DXVECTOR2 size = pDataPause->GetSize(CTextDataPause::PAUSEPOLY_BASE);
	int nTexIdx = pDataPause->GetTexIdx(CTextDataPause::PAUSEPOLY_BASE);

	// 2D�|���S���̐���
	m_pScene2D = CScene2D::Create();

	// ������
	m_pScene2D->SetPosition(pos);
	m_pScene2D->SetSize(size);
	m_pScene2D->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_pScene2D->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	m_pScene2D->BindTextureNum(nTexIdx);

	return S_OK;
}

//==============================================================================
// �|�[�Y�x�[�X�̏I������
//==============================================================================
void CPauseBase::Uninit(void)
{
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}
}

//==============================================================================
// �|�[�Y�x�[�X�̍X�V����
//==============================================================================
void CPauseBase::Update(void)
{
	bool bPause = CPause::GetPause();

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	switch (bPause)
	{
	case true:
		col.a = 1.0f;
		break;

	case false:
		col.a = 0.0f;
		break;
	}

	// �F���̐ݒ�
	m_pScene2D->SetCol(col);
	
	// �X�V
	//m_pScene2D->Update();
}

//==============================================================================
// �|�[�Y�x�[�X�̕`�揈��
//==============================================================================
void CPauseBase::Draw(void)
{
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Draw();
	}
}

//==============================================================================
// �|�[�Y�x�[�X�̐�������
//==============================================================================
CPauseBase *CPauseBase::Create(void)
{
	// �C���X�^���X����
	CPauseBase *pPauseBase;
	pPauseBase = new CPauseBase;

	// ������
	if (pPauseBase != NULL)
	{
		pPauseBase->Init();
	}

	return pPauseBase;
}