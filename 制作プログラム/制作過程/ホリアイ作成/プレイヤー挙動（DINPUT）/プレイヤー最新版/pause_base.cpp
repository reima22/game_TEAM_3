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
CPauseBase::CPauseBase(int nPriority) : CScene2D(nPriority)
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

	// ������
	CScene2D::Init();
	CScene2D::SetPosition(pos);
	CScene2D::SetSize(size.x, size.y);
	CScene2D::SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	CScene2D::SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	CScene2D::BindTexture(nTexIdx);

	return S_OK;
}

//==============================================================================
// �|�[�Y�x�[�X�̏I������
//==============================================================================
void CPauseBase::Uninit(void)
{
	CScene2D::Uninit();
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

	CScene2D::SetCol(col);

	CScene2D::Update();
}

//==============================================================================
// �|�[�Y�x�[�X�̕`�揈��
//==============================================================================
void CPauseBase::Draw(void)
{
	CScene2D::Draw();
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
	pPauseBase->Init();

	return pPauseBase;
}