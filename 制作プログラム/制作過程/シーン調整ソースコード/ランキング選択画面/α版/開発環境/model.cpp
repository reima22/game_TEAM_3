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

	// �e�N�X�`���|�C���^�̎擾
	CTexture *pTexture;
	pTexture = CManager::GetTexture();

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

	m_vtxMin = VTX_MIN;
	m_vtxMax = VTX_MAX;

	// �e�N�X�`���̐ݒ�
	m_pTexture = new LPDIRECT3DTEXTURE9[m_nNumMat];	// �e�N�X�`���|�C���^�z��̓��I�m��(�}�e���A���̐�����)

	int nNumVtx;			// ���_��
	DWORD sizeFVF;			// ���_�t�H�[�}�b�g�̃T�C�Y 
	BYTE *pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATERIAL *pMat;		// �}�e���A���ւ̃|�C���^

	// �o�b�t�@�|�C���^�̎擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// �I�u�W�F�N�g���Ƃ̐ݒ�
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{// �e�N�X�`������
			// �e�N�X�`�����̊��蓖��
			m_pTexture[nCntMat] = pTexture->GetAddress3D(pMat[nCntMat].pTextureFilename);
		}
		else
		{// �e�N�X�`���̊��蓖�Ă��Ȃ�
			m_pTexture[nCntMat] = NULL;
		}

		// ���_�����擾
		nNumVtx = m_pMesh->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
		sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

		// ���_�o�b�t�@�����b�N
		m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		// ���_���W�̔�r
		for (int nCntVtx = 0; nCntVtx < (int)nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��

			// �e���W�̍ő�l�̔�r
			if (m_vtxMax.x < vtx.x)
			{
				m_vtxMax.x = vtx.x;
			}
			if (m_vtxMax.y < vtx.y)
			{
				m_vtxMax.y = vtx.y;
			}
			if (m_vtxMax.z < vtx.z)
			{
				m_vtxMax.z = vtx.z;
			}

			// �e���W�̍ŏ��l�̔�r
			if (m_vtxMin.x > vtx.x)
			{
				m_vtxMin.x = vtx.x;
			}
			if (m_vtxMin.y > vtx.y)
			{
				m_vtxMin.y = vtx.y;
			}
			if (m_vtxMin.z > vtx.z)
			{
				m_vtxMin.z = vtx.z;
			}

			pVtxBuff += sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}

		// ���_�o�b�t�@���A�����b�N
		m_pMesh->UnlockVertexBuffer();
	}

	// �����蔻��p�ݒ�
	SetCollisionInfo();

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

	// �e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		delete[] m_pTexture;
		m_pTexture = NULL;
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
	
	//pDevice->SetRenderState(D3DRS_FILLMODE, 2);

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

	//pDevice->SetRenderState(D3DRS_FILLMODE, 0);
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

//==============================================================================
// �����蔻����ݒ�
//==============================================================================
void CModel::SetCollisionInfo(void)
{
	// ���[�J���ϐ��錾
	float aLength[COLLISION_NUM];
	float aAngle[COLLISION_NUM];

	// �Ίp��
	aLength[0] = sqrtf(m_vtxMin.x * m_vtxMin.x + m_vtxMin.z * m_vtxMin.z);
	aLength[1] = sqrtf(m_vtxMin.x * m_vtxMin.x + m_vtxMax.z * m_vtxMax.z);
	aLength[2] = sqrtf(m_vtxMax.x * m_vtxMax.x + m_vtxMax.z * m_vtxMax.z);
	aLength[3] = sqrtf(m_vtxMax.x * m_vtxMax.x + m_vtxMin.z * m_vtxMin.z);

	// �Ίp���ւ̊p�x
	aAngle[0] = atan2f(m_vtxMin.x, m_vtxMin.z);
	aAngle[1] = atan2f(m_vtxMin.x, m_vtxMax.z);
	aAngle[2] = atan2f(m_vtxMax.x, m_vtxMax.z);
	aAngle[3] = atan2f(m_vtxMax.x, m_vtxMin.z);

	// ���_�ʒu
	for (int nCnt = 0; nCnt < COLLISION_NUM; nCnt++)
	{
		m_aPosVtx[nCnt] = D3DXVECTOR3(
			sinf(aAngle[nCnt] + m_rot.y) * aLength[nCnt],
			m_pos.y,
			cosf(aAngle[nCnt] + m_rot.y) * aLength[nCnt]);
	}

	// ���_��񃊃Z�b�g
	m_vtxMin.x = VTX_MIN.x;
	m_vtxMin.z = VTX_MIN.z;
	m_vtxMax.x = VTX_MAX.x;
	m_vtxMax.z = VTX_MAX.z;

	// ���_���̕ύX
	for (int nCnt = 0; nCnt < COLLISION_NUM; nCnt++)
	{
		if (m_aPosVtx[nCnt].x < m_vtxMin.x)
		{
			m_vtxMin.x = m_aPosVtx[nCnt].x;
		}

		if (m_aPosVtx[nCnt].z < m_vtxMin.z)
		{
			m_vtxMin.z = m_aPosVtx[nCnt].z;
		}

		if (m_aPosVtx[nCnt].x > m_vtxMax.x)
		{
			m_vtxMax.x = m_aPosVtx[nCnt].x;
		}

		if (m_aPosVtx[nCnt].z > m_vtxMax.z)
		{
			m_vtxMax.z = m_aPosVtx[nCnt].z;
		}
	}

	// 4���_�̍Đݒ�
	m_aPosVtx[0] = D3DXVECTOR3(m_pos.x + m_vtxMin.x, m_pos.y, m_pos.z + m_vtxMin.z);
	m_aPosVtx[1] = D3DXVECTOR3(m_pos.x + m_vtxMin.x, m_pos.y, m_pos.z + m_vtxMax.z);
	m_aPosVtx[2] = D3DXVECTOR3(m_pos.x + m_vtxMax.x, m_pos.y, m_pos.z + m_vtxMax.z);
	m_aPosVtx[3] = D3DXVECTOR3(m_pos.x + m_vtxMax.x, m_pos.y, m_pos.z + m_vtxMin.z);

	// 4�����x�N�g��
	m_aVecVtx[0] = m_aPosVtx[1] - m_aPosVtx[0];
	m_aVecVtx[1] = m_aPosVtx[2] - m_aPosVtx[1];
	m_aVecVtx[2] = m_aPosVtx[3] - m_aPosVtx[2];
	m_aVecVtx[3] = m_aPosVtx[0] - m_aPosVtx[3];
}

//==============================================================================
// �e�̃T�C�Y�ݒ�
//==============================================================================
D3DXVECTOR2 CModel::SetShadowSize(void)
{
	// ���[�J���ϐ��錾
	float fSize = m_vtxMax.x;	// �ő�l��X���W����

	// �e�T�C�Y�̔�r(�ő�ƂȂ�l���w��)
	if (fSize < m_vtxMax.z)
	{
		fSize = m_vtxMax.z;
	}
	if (fSize < -m_vtxMin.x)
	{
		fSize = -m_vtxMin.x;
	}
	if (fSize < -m_vtxMin.z)
	{
		fSize = -m_vtxMin.z;
	}

	// �l�̐ݒ�
	m_shadowSize = D3DXVECTOR2(fSize, fSize);

	return m_shadowSize;
}