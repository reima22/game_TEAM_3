//==============================================================================
//
// ���f���Ǘ��kmodel.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "model.h"
#include "textdata_player.h"
#include "texture.h"

// �ÓI�����o�ϐ��錾
//char *CModel::m_pFileName[MODELTYPE_MAX] =
//{
//	{ "data/MODEL/PLAYER/00_body.x" },			// ��
//	{ "data/MODEL/PLAYER/01_head.x" },			// ��
//	{ "data/MODEL/PLAYER/02_arm_top_R.x" },		// �E��r
//	{ "data/MODEL/PLAYER/03_arm_under_R.x" },	// �E���r
//	{ "data/MODEL/PLAYER/04_hand_R.x" },		// �E��
//	{ "data/MODEL/PLAYER/05_arm_top_L.x" },		// ����r
//	{ "data/MODEL/PLAYER/06_arm_under_L.x" },	// �����r
//	{ "data/MODEL/PLAYER/07_hand_L.x" },		// ����
//	{ "data/MODEL/PLAYER/08_leg_top_R.x" },		// �E��
//	{ "data/MODEL/PLAYER/09_leg_under_R.x" },	// �E��
//	{ "data/MODEL/PLAYER/10_foot_R.x" },		// �E����
//	{ "data/MODEL/PLAYER/11_leg_top_L.x" },		// ����
//	{ "data/MODEL/PLAYER/12_leg_under_L.x" },	// ����
//	{ "data/MODEL/PLAYER/13_foot_L.x" },		// ������
//};

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CModel::CModel()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CModel::~CModel()
{

}

//==============================================================================
// 3D���f���`��̏���������
//==============================================================================
HRESULT CModel::Init(char *pFileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(
		pFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	// �e�|�C���^
	m_pParent = NULL;

	// �ʒu�E�p�x�ݒ�
	m_pos = pos;
	m_rot = rot;

	// �e�N�X�`���̐ݒ�
	// �e�N�X�`���|�C���^�z��̓��I�m��(�}�e���A���̐�����)
	m_pTexture = new LPDIRECT3DTEXTURE9[m_nNumMat];

	D3DXMATERIAL *pMat;		// �}�e���A���ւ̃|�C���^

	// �o�b�t�@�|�C���^�̎擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{// �e�N�X�`������
		 // �e�N�X�`�����̊��蓖��
			m_pTexture[nCntMat] = CTexture::BindTex3D(pMat[nCntMat].pTextureFilename);

			// �t�@�C�������g�p���ăe�N�X�`����ǂݍ���
			//D3DXCreateTextureFromFile(
			//	pDevice,
			//	pMat[nCntMat].pTextureFilename,
			//	&m_pTexture[nCntMat]);
		}
		else
		{// �e�N�X�`���̊��蓖�Ă��Ȃ�
			m_pTexture[nCntMat] = NULL;
		}
	}

	return S_OK;
}

//==============================================================================
// 3D���f���`��̏I������
//==============================================================================
void CModel::Uninit(void)
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
}

//==============================================================================
// 3D���f���`��̍X�V����
//==============================================================================
void CModel::Update(void)
{

}

//==============================================================================
// 3D���f���̕`�揈��
//==============================================================================
void CModel::Draw(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;										// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;												// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;													// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxParent;												// �e�̃}�g���b�N�X

	// Z�e�X�g�̍X�V
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != NULL)
	{// �e�}�g���b�N�X�����݂��Ȃ�
		// �e�}�g���b�N�X�̎擾
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{
		// ���݂̃v���C���[�}�g���b�N�X���擾����
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	// �e�̃}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		if (m_pTexture[nCntMat] != NULL)
		{
			pDevice->SetTexture(0, m_pTexture[nCntMat]);
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}

		// ���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	// ���ɖ߂�
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//==============================================================================
// ��������
//==============================================================================
CModel *CModel::Create(char *pFileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���[�J���ϐ��錾
	CModel *pModel;
	pModel = new CModel;	// �C���X�^���X����

	// ������
	if (pModel != NULL)
	{
		pModel->Init(pFileName, pos, rot);
	}

	return pModel;
}