//=============================================================================
//
// 3D���f�� [Scene3DModel.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "Scene3DModel.h"
#include "Manager.h"
#include "Input.h"
#include "Resource.h"

//*****************************************************************************
// ���f���N���X (�h�����F�I�u�W�F�N�g�N���X�j
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene3DModel::CScene3DModel(int nPriority) : CScene(nPriority)
{
	m_pTexture = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene3DModel::~CScene3DModel()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene3DModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// ��������ݒ�
	SetPos(pos);
	SetRot(rot);
	SetSize(VECTOR3_ZERO);

	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// get resource manager
	m_pResourceManager = CManager::GetResourceManager();


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene3DModel::Uninit(void)
{

	// �C���X�^���X�j��
	this->Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene3DModel::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene3DModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// Device
	D3DXMATRIX mtxRot, mtxTrans;	// Temporary matrices
	D3DMATERIAL9 matDef;			// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				// temp mat

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXVECTOR3 rot = GetRot();
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXVECTOR3 pos = GetPos();
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A����ۑ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	CModelData *pModel = m_pResourceManager->m_Model_Map[m_modelName];	// ���f���̃f�[�^
	pMat = (D3DXMATERIAL*)pModel->Xfile_Materials->GetBufferPointer();	// �}�e���A���f�[�^�ւ̃|�C���^

	for (DWORD nCntMat = 0; nCntMat < (int)pModel->Xfile_MaterialNum; nCntMat++)
	{
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		pDevice->SetTexture(0, pModel->g_Textures[nCntMat]);
		pModel->Xfile_Mesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// ���f���̃o�C���h
//=============================================================================
void CScene3DModel::BindModel(string modelName)
{
	m_modelName = modelName;
}

//=============================================================================
// �����֐�
//=============================================================================
CScene3DModel *CScene3DModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, string modelName)
{
	CScene3DModel *pScene3DModel;
	pScene3DModel = new CScene3DModel;
	if (pScene3DModel != NULL)
	{
		pScene3DModel->Init(pos, rot, VECTOR3_ZERO);
		pScene3DModel->BindModel(modelName);
	}

	return pScene3DModel;
}