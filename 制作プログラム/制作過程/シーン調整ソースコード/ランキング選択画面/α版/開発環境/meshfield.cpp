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
#include "game.h"
#include "player.h"
#include "textdata.h"
#include "textdata_meshfield.h"
#include "texture.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CMeshfield::CMeshfield()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CMeshfield::~CMeshfield()
{

}

//==============================================================================
// ����������
//==============================================================================
HRESULT CMeshfield::Init(void)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	WORD *pIdx;

	// �f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	CTexture *pTexture = CManager::GetTexture();

	// �e�L�X�g�̃f�[�^
	CTextDataMeshfield *pDataMeshfield;
	pDataMeshfield = CTextData::GetDataMeshfield();

	// �f�[�^�̊��蓖��
	m_pos = pDataMeshfield->GetPosition(m_nIdx);
	m_rot = pDataMeshfield->GetRotation(m_nIdx);
	m_nWidth = pDataMeshfield->GetWidthPoly(m_nIdx);
	m_nDepth = pDataMeshfield->GetDepthPoly(m_nIdx);
	m_fWidth = pDataMeshfield->GetSize(m_nIdx).x;
	m_fDepth = pDataMeshfield->GetSize(m_nIdx).y;
	
	m_pTexture = pTexture->GetAddress("TEX0");

	// �e�ϐ��̌v�Z
	m_nAllPoint = m_nDepth * 2 * (m_nWidth + 2) - 2;				// �����_��
	m_nPolygon = m_nWidth * m_nDepth * 2 + (4 * (m_nDepth - 1));	// ���|���S����
	m_nWidthPoint = m_nWidth + 1;
	m_nDepthPoint = m_nDepth + 1;

	m_nIdxPoint = m_nWidthPoint * m_nDepthPoint;					// �C���f�b�N�X�o�b�t�@�ł̒��_��

	// ���_���̓��I�m��
	//m_posVtx = new D3DXVECTOR3[m_nIdxPoint];

	float fWidthMax = m_fWidth * (float)m_nWidth;
	float fDepthMax = m_fDepth * (float)m_nDepth;

	// �@�������߂�|���S����
	m_nNor = m_nWidth * m_nDepth * 2;

	// �@���l���I�m��
	m_pNor = new D3DXVECTOR3[m_nNor];

	m_nIdxNor = 0;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_nIdxPoint,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntPoint = 0;

	for (int nCnt = 0; nCnt < m_nDepthPoint; nCnt++)
	{// ���s��
		for (int nCntA = 0; nCntA < m_nWidthPoint; nCntA++)
		{// ����
		 // �|���S���̊e���_���W
			if (pDataMeshfield->GetPosVtx(m_nIdx, nCntPoint) != VECTOR3_NULL)
			{
				pVtx[0].pos =
					D3DXVECTOR3(
						m_pos.x + pDataMeshfield->GetPosVtx(m_nIdx, nCntPoint).x,
						m_pos.y + pDataMeshfield->GetPosVtx(m_nIdx, nCntPoint).y,
						m_pos.z + pDataMeshfield->GetPosVtx(m_nIdx, nCntPoint).z);
			}
			else
			{
				pVtx[0].pos = D3DXVECTOR3(
				m_pos.x - fWidthMax / 2.0f + (float)nCntA * m_fWidth,
				m_pos.y,
				m_pos.z + fDepthMax / 2.0f - (float)nCnt * m_fDepth);
			}


			//m_posVtx[nCntPoint] = pVtx[0].pos;	// ���_�ݒ�

			// �@���x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// �e���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����_���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(1.0f * nCntA, 1.0f * nCnt);

			pVtx++;
			nCntPoint++;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * m_nAllPoint,
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
void CMeshfield::Uninit(void)
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

	// �@���J��
	if (m_pNor != NULL)
	{
		delete[] m_pNor;
		m_pNor = NULL;
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void CMeshfield::Update(void)
{
	// �g�`�̋���
	//MeshWave();

	// �@���̌v�Z
	CalcuNormal();
}

//==============================================================================
// �`�揈��
//==============================================================================
void CMeshfield::Draw(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// �f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//// �����̔��f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//// �ʒu�𔽉f
	//D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

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
CMeshfield *CMeshfield::Create(int nIdx)
{
	// ���[�J���ϐ��錾
	CMeshfield *pMeshField;
	pMeshField = new CMeshfield;

	if (pMeshField != NULL)
	{
		// �ϐ��̐ݒ�
		pMeshField->SetIdx(nIdx);

		// ������
		pMeshField->Init();
	}

	return pMeshField;
}

//==============================================================================
// �@���v�Z
//==============================================================================
void CMeshfield::CalcuNormal(void)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;
	D3DXVECTOR3 vecA = VECTOR3_NULL;
	D3DXVECTOR3 vecB = VECTOR3_NULL;

	int nCntNormal = 0;	// �@���J�E���g

						// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�ʂ̖@���Z�o
	for (int nCntDepth = 0; nCntDepth < m_nDepth; nCntDepth++)
	{// ���s�ʐ�
		int nCntOdd = 0;	// ��J�E���g
		int nCntEven = 0;	// �����J�E���g

		for (int nCntWidth = 0; nCntWidth < m_nWidth * 2; nCntWidth++)
		{// �������_���i�O�p�`�|���S�����j						
			if (nCntWidth % 2 == 0)
			{
				// �������x�N�g��
				vecA =
					pVtx[m_nWidthPoint + (m_nWidthPoint * nCntDepth) - m_nWidthPoint + nCntEven].pos -
					pVtx[m_nWidthPoint + (m_nWidthPoint * nCntDepth) + nCntEven].pos;

				vecB =
					pVtx[m_nWidthPoint + (m_nWidthPoint * nCntDepth) + nCntEven + 1].pos -
					pVtx[m_nWidthPoint + (m_nWidthPoint * nCntDepth) + nCntEven].pos;

				nCntEven++;		// �����J�E���g
			}
			else
			{
				// ����x�N�g��
				vecA =
					pVtx[m_nWidthPoint + (m_nWidthPoint * nCntDepth) + nCntOdd - m_nWidth + m_nWidthPoint].pos -
					pVtx[m_nWidthPoint + (m_nWidthPoint * nCntDepth) + nCntOdd - m_nWidth].pos;

				vecB =
					pVtx[m_nWidthPoint + (m_nWidthPoint * nCntDepth) + nCntOdd - m_nWidth - 1].pos -
					pVtx[m_nWidthPoint + (m_nWidthPoint * nCntDepth) + nCntOdd - m_nWidth].pos;

				nCntOdd++;		// ��J�E���g
			}

			// �@���x�N�g���̌v�Z
			D3DXVec3Cross(&m_pNor[nCntNormal], &vecA, &vecB);

			// �@���x�N�g���̐��K��
			D3DXVec3Normalize(&m_pNor[nCntNormal], &m_pNor[nCntNormal]);

			// ���݂̃J�E���g
			nCntNormal++;
		}
	}

	// ���[�J���ϐ��錾
	int nCntUnder = m_nWidth * 2 * (m_nDepth - 1);	// ���ӊJ�n�ʖ@���C���f�b�N�X
	int nCntLeft = m_nWidth * 2;					// ���ӊJ�n�ʖ@���C���f�b�N�X
	int nCntRight = m_nWidth * 2 - 1;				// �E�ӊJ�n�ʖ@���C���f�b�N�X
	int nRight = 1;									// �E�ӊJ�n�n�_�C���f�b�N�X�v�Z�p

	int nCntCenterA = 0;							// �������_�v�Z�p�㑤
	int nCntCenterB
		= nCntCenterA + (m_nWidthPoint * 2 - 1);	// �������_�v�Z�p����
	int nCntCenterC = 1;							// �������_�v�Z�p�܂�Ԃ��J�E���g

													// �e���_�̖@���Z�o
	for (int nCntNor = 0; nCntNor < m_nIdxPoint; nCntNor++)
	{
		// 2�ʖ@��
		if (nCntNor == 0)
		{// �ŏ�(����)
			pVtx[nCntNor].nor = m_pNor[0] + m_pNor[1];
		}
		else if (nCntNor == m_nIdxPoint - 1)
		{// �Ō�(�E��)
			pVtx[nCntNor].nor = m_pNor[m_nNor - 1] + m_pNor[m_nNor - 2];
		}

		// 1�ʖ@��
		else if (nCntNor == m_nWidth)
		{// �E��
			pVtx[nCntNor].nor = m_pNor[m_nWidth * 2 - 1];
		}
		else if (nCntNor == (m_nWidth + 1) + ((m_nDepth - 1) * (m_nWidth + 1)))
		{// ����
			pVtx[nCntNor].nor = m_pNor[m_nWidth * 2 * (m_nDepth - 1)];
		}

		// 3�ʖ@��
		else if (nCntNor > 0 && nCntNor < m_nWidth)
		{// ��Ӓ�����
		 // ���[�J���ϐ��錾
			int nCntA = nCntNor + (nCntNor - 1);	// �n���ƂȂ�ʃC���f�b�N�X

			pVtx[nCntNor].nor = m_pNor[nCntA] + m_pNor[nCntA + 1] + m_pNor[nCntA + 2];
		}
		else if (nCntNor >(m_nWidth + 1) + ((m_nDepth - 1) * (m_nWidth + 1)) && nCntNor < m_nIdxPoint - 1)
		{// ���Ӓ�����
			pVtx[nCntNor].nor = m_pNor[nCntUnder] + m_pNor[nCntUnder + 1] + m_pNor[nCntUnder + 2];
			nCntUnder += 2;
		}
		else if (nCntNor % m_nWidthPoint == 0 && nCntNor != 0)
		{// ���Ӓ�����
			pVtx[nCntNor].nor = m_pNor[nCntLeft] + m_pNor[nCntLeft + 1] + m_pNor[nCntLeft - (m_nWidth * 2)];
			nCntLeft += m_nWidth * 2;
		}
		else if (nCntNor % (m_nWidth + m_nWidthPoint * nRight) == 0 && nCntNor != 0)
		{// �E�Ӓ�����
			pVtx[nCntNor].nor = m_pNor[nCntRight] + m_pNor[nCntRight - 1] + m_pNor[nCntRight + (m_nWidth * 2)];
			nCntRight += m_nWidth * 2;
			nRight++;
		}

		// ��O�I���_(6�ʖ@��)
		else
		{// �����̒��_
			pVtx[nCntNor].nor =
				m_pNor[nCntCenterA] + m_pNor[nCntCenterA + 1] + m_pNor[nCntCenterA + 2] +
				m_pNor[nCntCenterB] + m_pNor[nCntCenterB + 1] + m_pNor[nCntCenterB + 2];

			if (nCntNor % ((m_nWidth - 1) + m_nWidthPoint * nCntCenterC) == 0)
			{// �܂�Ԃ��n�_
				nCntCenterA += 4;
				nCntCenterB += 4;
				nCntCenterC++;
			}
			else
			{// ��O
				nCntCenterA += 2;
				nCntCenterB += 2;
			}
		}

		// �x�N�g���̐��K��
		D3DXVec3Normalize(&pVtx[nCntNor].nor, &pVtx[nCntNor].nor);
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==============================================================================
// ���b�V���̔g�`
//==============================================================================
void CMeshfield::MeshWave(void)
{
	m_nCntWave++;

	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;
	int nIdx = 0;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntDepth = 0; nCntDepth < m_nDepthPoint; nCntDepth++)
	{
		for (int nCntWidth = 0; nCntWidth < m_nWidthPoint; nCntWidth++)
		{
			//pVtx[nIdx].pos.y +=
			//	sinf(pVtx[nIdx].pos.x * 0.025f + m_nCntWave * 0.05f) * 1.0f;

			pVtx[nIdx].pos.y +=
				sinf(pVtx[nIdx].pos.z * 0.025f + m_nCntWave * 0.05f) * 1.0f;

			nIdx++;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}