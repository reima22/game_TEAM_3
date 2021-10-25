//=============================================================================
//
// ���� [Scaffold.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "Scaffold.h"

//*****************************************************************************
// ����N���X
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScaffold::CScaffold()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScaffold::~CScaffold()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScaffold::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	if (FAILED(CScene3DModel::Init(pos, rot, size))) {
		return E_FAIL;
	}

	BindModel("SCAFFOLD1");
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScaffold::Uninit(void)
{
	CScene3DModel::Uninit();


}

//=============================================================================
// �X�V����
//=============================================================================
void CScaffold::Update(void)
{
	CScene3DModel::Update();


}

//=============================================================================
// �`�揈��
//=============================================================================
void CScaffold::Draw(void)
{
	CScene3DModel::Draw();
}

//=============================================================================
// �����֐�
//=============================================================================
CScaffold *CScaffold::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CScaffold *pScaffold;
	pScaffold = new CScaffold;
	if (pScaffold != NULL)
	{
		pScaffold->Init(pos, rot, VECTOR3_ZERO);
	}

	return pScaffold;
}