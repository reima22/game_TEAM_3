//==============================================================================
//
// ���b�V���t�B�[���h�̕`��kmeshfield.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "meshfield.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"

//==============================================================================
// �}�N����`
//==============================================================================
//#define WIDTHNUM	(10)		// ��(��)
//#define DEPTHNUM	(10)		// �s��(���s)
//#define WIDTH		(100.0f)	// ���̑傫��
//#define DEPTH		(100.0f)	// ���s�̑傫��
#define POINT_MAX	(65535)		// ���_���̍ő�
#define IDX_MAX		(65535)		// �C���f�b�N�X�o�b�t�@�̍ő�m�ې�
#define FIELD_MAX	(32)		// �t�B�[���h�̍ő吔

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;	// �o�b�t�@�ւ̃|�C���^
//LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshfield = NULL;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
//LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;		// �e�N�X�`���ւ̃|�C���^
//D3DXVECTOR3 g_posMeshfield;							// �ʒu
//D3DXVECTOR3 g_rotMeshfield;							// ����
//D3DXMATRIX g_mtxWorldMeshfield;						// ���[���h�}�g���b�N�X
//int g_nAllPoint;									// �����_��
//int g_nPolygon;										// �|���S����
//int g_nIdxPoint;									// �C���f�b�N�X�o�b�t�@�̕K�v�Ȋm�ې�
//float g_fWidth = WIDTH;								// �����̒[
//float g_fDepth = DEPTH;								// ���s�̒[
//int g_nWidth = WIDTHNUM + 1;						// �����̒��_��
//int g_nDepth = DEPTHNUM + 1;						// ���s�̒��_��

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CMeshField::CMeshField() 
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CMeshField::~CMeshField()
{

}


//==============================================================================
// ����������
//==============================================================================
HRESULT CMeshField::Init(D3DXVECTOR3 pos)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	WORD *pIdx;

	// �f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/field000.jpg",
		&m_pTexture);

	// �ϐ��̏�����
	m_pos = pos;
	//g_rotMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nAllPoint = m_nDepth * 2 * (m_nWidth + 2) - 2;				// �����_��
	m_nPolygon = m_nWidth * m_nDepth * 2 + (4 * (m_nDepth - 1));	// ���|���S����
	m_nWidthPoint = m_nWidth + 1;
	m_nDepthPoint = m_nDepth + 1;
	
	m_nIdxPoint = m_nWidthPoint * m_nDepthPoint;					// �C���f�b�N�X�o�b�t�@�ł̒��_��
	
																	
	float fWidthMax = m_fWidth * (float)m_nWidth;
	float fDepthMax = m_fDepth * (float)m_nDepth;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_nIdxPoint/* * FIELD_MAX*/,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_nDepthPoint; nCnt++)
	{// ���s��
		for (int nCntA = 0; nCntA < m_nWidthPoint; nCntA++)
		{// ����
		 // �|���S���̊e���_���W
			pVtx[0].pos = D3DXVECTOR3(
				-fWidthMax / 2.0f + (float)nCntA * m_fWidth,
				m_pos.y,
				fDepthMax / 2.0f - (float)nCnt * m_fDepth);

			//pVtx[0].pos = D3DXVECTOR3(-g_fWidth + (float)nCntA * fWidthPart, g_posMeshfield.y, g_fDepth - (float)nCnt * fDepthPart);

			// �@���x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// �e���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����_���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(1.0f * nCntA, 1.0f * nCnt);

			pVtx++;
		}
	}

	// �|���S���̊e���_���W
	//pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
	//pVtx[2].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
	//pVtx[3].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
	//pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	//pVtx[6].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
	//pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
	//pVtx[8].pos = D3DXVECTOR3(100.0f, 0.0f, -100.0f);
	//pVtx[9].pos = D3DXVECTOR3(g_posMeshfield.x - 100.0f, 0.0f, 0.0f);
	//pVtx[0].pos = D3DXVECTOR3(g_posMeshfield.x - 100.0f, 0.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_posMeshfield.x - 100.0f, 0.0f, g_posMeshfield.z + 100.0f);
	//pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, g_posMeshfield.z + 100.0f);
	//pVtx[4].pos = D3DXVECTOR3(g_posMeshfield.x + 100.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(g_posMeshfield.x + 100.0f, 0.0f, g_posMeshfield.z + 100.0f);
	//pVtx[6].pos = D3DXVECTOR3(g_posMeshfield.x + 100.0f, 0.0f, g_posMeshfield.z + 100.0f);
	//pVtx[7].pos = D3DXVECTOR3(g_posMeshfield.x - 100.0f, 0.0f, g_posMeshfield.z - 100.0f);
	//pVtx[8].pos = D3DXVECTOR3(g_posMeshfield.x - 100.0f, 0.0f, g_posMeshfield.z - 100.0f);
	//pVtx[9].pos = D3DXVECTOR3(g_posMeshfield.x - 100.0f, 0.0f, 0.0f);
	//pVtx[10].pos = D3DXVECTOR3(0.0f, 0.0f, g_posMeshfield.z - 100.0f);
	//pVtx[11].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[12].pos = D3DXVECTOR3(g_posMeshfield.x + 100.0f, 0.0f, g_posMeshfield.z - 100.0f);
	//pVtx[13].pos = D3DXVECTOR3(g_posMeshfield.x + 100.0f, 0.0f, 0.0f);

	// �@���x�N�g���̐ݒ�
	//pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[9].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[10].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[11].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[12].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[13].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// �e���_�J���[�̐ݒ�
	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����_���̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(2.0f, 0.0f);
	//pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[5].tex = D3DXVECTOR2(2.0f, 1.0f);
	//pVtx[6].tex = D3DXVECTOR2(0.0f, 2.0f);
	//pVtx[7].tex = D3DXVECTOR2(1.0f, 2.0f);
	//pVtx[8].tex = D3DXVECTOR2(2.0f, 2.0f);
	//pVtx[9].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[10].tex = D3DXVECTOR2(1.0f, 2.0f);
	//pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[12].tex = D3DXVECTOR2(2.0f, 2.0f);
	//pVtx[13].tex = D3DXVECTOR2(2.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * m_nAllPoint /** FIELD_MAX*/,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntA = 0; nCntA < m_nDepth; nCntA++)
	{
		for (int nCnt = 0; nCnt < m_nWidthPoint + 1; nCnt++, pIdx += 2)
		{
			if (nCnt != 0 && nCnt == m_nWidthPoint && nCntA != m_nDepth - 1)
			{// �E�[����܂�Ԃ���
				pIdx[0] = pIdx[-1];
				pIdx[1] = pIdx[-2] + 1;
			}
			else if (nCntA == m_nDepth - 1 && nCnt == m_nWidthPoint)
			{// �I�����ɖ�������
				break;
			}
			else
			{// �ʏ�z�u
				pIdx[0] = m_nWidthPoint + (m_nWidthPoint * nCntA) + nCnt;
				pIdx[1] = pIdx[0] - m_nWidthPoint;
			}
		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void CMeshField::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void CMeshField::Update(void)
{
	
}

//==============================================================================
// �`�揈��
//==============================================================================
void CMeshField::Draw(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// �f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//for (int nCnt = 0; nCnt < FIELD_MAX; nCnt++, pField++)
	//{
	//	if (pField->bUse == true)
	//	{
	//		// ���[���h�}�g���b�N�X�̏�����
	//		D3DXMatrixIdentity(&pField->mtxWorld);
	//		// �����̔��f
	//		D3DXMatrixRotationYawPitchRoll(&mtxRot, pField->rot.y, pField->rot.x, pField->rot.z);
	//		D3DXMatrixMultiply(&pField->mtxWorld, &pField->mtxWorld, &mtxRot);
	//		// �ʒu�𔽉f
	//		D3DXMatrixTranslation(&mtxTrans, pField->pos.x, pField->pos.y, pField->pos.z);
	//		D3DXMatrixMultiply(&pField->mtxWorld, &pField->mtxWorld, &mtxTrans);
	//		// ���[���h�}�g���b�N�X�̐ݒ�
	//		pDevice->SetTransform(D3DTS_WORLD, &pField->mtxWorld);
	//		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	//		pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));
	//		// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	//		pDevice->SetIndices(g_pIdxBuffMeshfield);
	//		// ���_�t�H�[�}�b�g�̐ݒ�
	//		pDevice->SetFVF(FVF_VERTEX_3D);
	//		// �e�N�X�`���̐ݒ�
	//		pDevice->SetTexture(0, g_pTextureMeshfield);
	//		// �|���S���̕`��
	//		pDevice->DrawIndexedPrimitive(
	//			D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
	//			0,
	//			0,
	//			pField->nIdxPoint,			// ���_��
	//			0,
	//			pField->nPolygon);			// �v���~�e�B�u��
	//	}
	//}

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,
		0,
		m_nIdxPoint,			// ���_��
		0,
		m_nPolygon);			// �v���~�e�B�u��
}

//==============================================================================
// �t�B�[���h�̐���
//==============================================================================
CMeshField *CMeshField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nWidth, int nDepth, float fWidth, float fDepth)
{
	// ���[�J���ϐ��錾
	CMeshField *pMeshField;
	pMeshField = new CMeshField;

	if (pMeshField != NULL)
	{
		// �ϐ��̐ݒ�
		pMeshField->SetRotation(rot);
		pMeshField->SetWidthNum(nWidth);
		pMeshField->SetDepthNum(nDepth);
		pMeshField->SetWidthSize(fWidth);
		pMeshField->SetDepthSize(fDepth);

		pMeshField->Init(pos);
	}

	return pMeshField;
}