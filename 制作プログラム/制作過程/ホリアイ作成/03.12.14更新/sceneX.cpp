//==============================================================================
//
// 3D���f��X�`�揈���ksceneX.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene3D.h"
#include "renderer.h"
#include "manager.h"
#include "sceneX.h"
#include "texture.h"
#include "model.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CSceneX::CSceneX()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CSceneX::~CSceneX()
{

}

//==============================================================================
// 3D���f���`��̏���������
//==============================================================================
HRESULT CSceneX::Init(D3DXVECTOR3 pos)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���|�C���^�̎擾
	CTexture *pTexture;
	pTexture = CManager::GetTexture();

	m_pScene3D = CScene3D::Create();

	// �����ݒ�
	m_pScene3D->SetPosition3D(pos);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(
		"data/MODEL/shadowS.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	// �e�N�X�`���|�C���^�z��̓��I�m��(�}�e���A���̐�����)
	//m_pTexture = new LPDIRECT3DTEXTURE9[m_nNumMat];

	//D3DXMATERIAL *pMat;		// �}�e���A���ւ̃|�C���^

	//// �o�b�t�@�|�C���^�̎擾
	//pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	//{
	//	if (pMat[nCntMat].pTextureFilename != NULL)
	//	{// �e�N�X�`������
	//		// �e�N�X�`�����̊��蓖��
	//		m_pTexture[nCntMat] = pTexture->GetAddress3D(pMat[nCntMat].pTextureFilename);

	//		// �t�@�C�������g�p���ăe�N�X�`����ǂݍ���
	//		D3DXCreateTextureFromFile(
	//			pDevice,
	//			pMat[nCntMat].pTextureFilename,
	//			&m_pTexture[nCntMat]);
	//	}
	//	else
	//	{// �e�N�X�`���̊��蓖�Ă��Ȃ�
	//		m_pTexture[nCntMat] = NULL;
	//	}
	//}

	return S_OK;
}

//==============================================================================
// 3D���f���`��̏I������
//==============================================================================
void CSceneX::Uninit(void)
{
	// ���b�V���|�C���^�̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// �}�e���A���o�b�t�@�̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		delete[] m_pTexture;
		m_pTexture = NULL;
	}

	CScene3D::Uninit();
}

//==============================================================================
// 3D���f���`��̍X�V����
//==============================================================================
void CSceneX::Update(void)
{
	D3DXVECTOR3 pos = CScene3D::GetPosition();

	m_pScene3D->SetPosition(pos);
}

//==============================================================================
// 3D���f���`��̕`�揈��
//==============================================================================
void CSceneX::Draw(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;										// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;												// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;													// �}�e���A���f�[�^�ւ̃|�C���^

	// �ʒu�ƌ���
	D3DXVECTOR3 pos = m_pScene3D->GetPosition();
	D3DXVECTOR3 rot = m_pScene3D->GetRotation();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		//pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		// ���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//==============================================================================
// ��������
//==============================================================================
CSceneX *CSceneX::Create(D3DXVECTOR3 pos)
{
	// ���[�J���ϐ��錾
	CSceneX *pSceneX;
	pSceneX = new CSceneX;	// �V�[��X�̃C���X�^���X

	// ������
	if (pSceneX != NULL)
	{
		pSceneX->Init(pos);
	}

	return pSceneX;
}

// �ʒu�̔��f