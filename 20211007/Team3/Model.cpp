//=============================================================================
//
// ���f���N���X [model.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "Model.h"
#include "Manager.h"
#include "Renderer.h"

//*****************************************************************************
// ���f���N���X
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModel::CModel()
{
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = 0;
	m_pos = VECTOR3_ZERO;
	m_rot = VECTOR3_ZERO;
	m_pParent = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModel::~CModel()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFilePath)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�擾

	// x�t�@�C������ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(
			aFilePath,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_dwNumMat,
			&m_pMesh)))
		return E_FAIL;

	// �ʒu�A������ݒ�
	m_pos = pos;
	m_rot = rot;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CModel::Uninit(void)
{
	// ���b�V���̔j��
	if (m_pMesh != NULL) {
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// �}�e���A���̔j��
	if (m_pBuffMat != NULL) {
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CModel::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�擾
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				// �}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���̃��f���̐e��ݒ肷��
	D3DXMATRIX mtxParent;	// �e���f���̃}�g���b�N�X
	if (m_pParent != NULL) {
		// �e�����݂���ꍇ�e���f���̃}�g���b�N�X���擾
		mtxParent = m_pParent->GetMtxWorld();
	}
	else {
		// �e�����݂��Ȃ��ꍇ�A���݂̃}�g���b�N�X���擾���� -> ����Draw�̑O��Player��Draw��SetTransform���Ă���̂Ńv���C���[�̃}�g���b�N�X(?)
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}
	// �e�̃}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A����ۑ�
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// �}�e���A�������[�v
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++) {
		// �}�e���A���ݒ�
		pDevice->SetMaterial(&pMat->MatD3D);

		// �e�N�X�`���ݒ�	 ( ���ݐݒ�Ȃ� )
		pDevice->SetTexture(0, NULL);

		// ���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �����֐�
//=============================================================================
CModel *CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFilePath)
{
	CModel *pModel;
	pModel = new CModel;
	if (pModel != NULL)
	{
		pModel->Init(pos, rot, aFilePath);
	}

	return pModel;
}

//=============================================================================
// �e���f����ݒ�
//=============================================================================
