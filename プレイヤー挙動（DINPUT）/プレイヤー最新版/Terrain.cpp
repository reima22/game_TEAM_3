//===================================================================
//SourceFile: Terrain.cpp
//Author : Yo jitaku
//===================================================================
#include "Terrain.h"
#include "scene.h"
#include "scene3D.h"
#include "texture.h"

//*******************************************************************
//�������̉��
//*******************************************************************
void CTerrain::Uninit()
{
	if (m_pDevice != nullptr)
	{
		m_pDevice->Release();
		m_pDevice = nullptr;
	}
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}
	delete m_pManager;
	m_pManager = nullptr;
}

//*******************************************************************
//������
//*******************************************************************
HRESULT CTerrain::Init()
{
	WORD* pIdx;										//Index�o�b�t�@
	VERTEX_3D *pVtx;								//���_�o�b�t�@

	float fStartX = -m_fTerrainWidth / 2.0f;		  //x���W�̎n�_
	float fStartZ = -m_fTerrainDepth / 2.0f;		  //z���W�̎n�_
	float fCoordU = 0.0f;
	float fCoordV = 0.0f;
	if (m_nVertsPerRow != m_nVertsPerCol)
	{
		if (m_nVertsPerRow > m_nVertsPerCol)
		{
			fCoordU = 1.0f / (float)m_nVertsPerCol;     //�e�N�X�`���[��U���W
			fCoordV = 1.0f / (float)m_nVertsPerCol;     //�e�N�X�`���[��V���W
		}
		else
		{
			fCoordU = 1.0f / (float)m_nVertsPerRow;     //�e�N�X�`���[��U���W
			fCoordV = 1.0f / (float)m_nVertsPerRow;     //�e�N�X�`���[��V���W
		}
	}
	else
	{
		fCoordU = 1.0f / (float)m_nVertsPerRow;     //�e�N�X�`���[��U���W
		fCoordV = 1.0f / (float)m_nVertsPerCol;     //�e�N�X�`���[��V���W
	}


	//���_�o�b�t�@�ɂ���
	if (FAILED(m_pDevice->CreateVertexBuffer(
		m_nNumVertices * sizeof(VERTEX_3D),
		D3DUSAGE_WRITEONLY, 
		FVF_VERTEX_3D, 
		D3DPOOL_MANAGED, 
		&m_pVtxBuff, NULL)))
		return E_FAIL;

	// �o�b�t�@���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nIndex = 0;

	for (int nCntRow = 0; nCntRow < m_nVertsPerCol; nCntRow++)//Z���_�̏���
	{
		for (int nCntCol = 0; nCntCol < m_nVertsPerRow; nCntCol++)//X���_�̏���
		{
			pVtx[nIndex].pos = D3DXVECTOR3(
				(fStartZ + nCntRow * m_fCellSpacing),
				(float)TERRAIN_HEIGHT,
				(fStartX + nCntCol * m_fCellSpacing));
			pVtx[nIndex].nor = D3DXVECTOR3(0.f, 1.f, 0.f);
			pVtx[nIndex].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
			pVtx[nIndex].tex = D3DXVECTOR2(nCntCol * fCoordU, nCntRow * fCoordV);
			vVertexBuffer.push_back(pVtx[nIndex].pos);
			nIndex++;
		}
	}

	// �o�b�t�@�A�����b�N
	m_pVtxBuff->Unlock();

	//index�o�b�t�@�ɂ���
	if (FAILED(m_pDevice->CreateIndexBuffer
	(sizeof(WORD) * m_nNumIndex,							//�`��K�v�̍Œ�̒��_��(�d���̒��_������) (���_����2�~�s���~(��+1)+2�~(�s��-1)) -> 2(xy+2x-1)
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL)))
		return E_FAIL;

	// �C���f�b�N�X�o�b�t�@���b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	nIndex = 0;
	
	for (int row = 0; row < m_nCellsPerCol; row++)			//�Z����(�s)
	{
		for (int col = 0; col < m_nCellsPerRow; col++)		//�Z����(��)
		{
			//����`��K�v�̋�`(�Z��)(=��O�p�`=�l���_�o�b�t�@=�Z��Index�o�b�t�@)
			pIdx[nIndex] = row * m_nVertsPerRow + col;
			pIdx[nIndex + 1] = row * m_nVertsPerRow + col + 1;
			pIdx[nIndex + 2] = (row + 1) * m_nVertsPerRow + col + 1;
			pIdx[nIndex + 3] = (row + 1) * m_nVertsPerRow + col;
			pIdx[nIndex + 4] = row * m_nVertsPerRow + col;
			pIdx[nIndex + 5] = (row + 1) * m_nVertsPerRow + col + 1;
			for (int nCnt = 0; nCnt < 6; nCnt++)
				vIndexBuffer.push_back(pIdx[nIndex + nCnt]);
			nIndex += 6;
		}
	}

	// �C���f�b�N�X�o�b�t�@�A�����b�N
	m_pIdxBuff->Unlock();
	return S_OK;
}

void CTerrain::Update()
{
	VERTEX_3D *pVtx;												//���_�o�b�t�@

	// �o�b�t�@���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���[�J���ϐ��錾
	int nIndex = 0;
	
	for (int nCntRow = 0; nCntRow < m_nVertsPerCol; nCntRow++)		//Z���_�̏���
	{
		for (int nCntCol = 0; nCntCol < m_nVertsPerRow; nCntCol++)	//X���_�̏���
		{
			pVtx[nIndex].tex.x += TERRAIN_MOVE_SPEED;
			nIndex++;
		}
	}

	// �o�b�t�@�A�����b�N
	m_pVtxBuff->Unlock();
}

//*******************************************************************
//�`��
//*******************************************************************
void CTerrain::Draw()
{
	D3DXMATRIX MtxWorld;
	D3DXMATRIX MtxRot, MtxTrans;	// Temporary matrices

	D3DXMatrixIdentity(&MtxWorld);									 //�P�ʍs��
	D3DXMatrixRotationYawPitchRoll(&MtxRot, 0, 0, 0);
	D3DXMatrixMultiply(&MtxWorld, &MtxWorld, &MtxRot);
	D3DXMatrixTranslation(&MtxTrans, 0, 0, 0);
	D3DXMatrixMultiply(&MtxWorld, &MtxWorld, &MtxTrans);

	m_pDevice->SetTransform(D3DTS_WORLD, &MtxWorld);				 //���E�}�g���b�N�X
	m_pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	m_pDevice->SetIndices(m_pIdxBuff);								 //Index�o�b�t�@������
	m_pDevice->SetFVF(FVF_VERTEX_3D);

	CTexture *pTexture = CManager::GetTexture();

	m_pDevice->SetTexture(0, pTexture->GetAddress(31));

	m_pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		0,
		0,
		m_nNumVertices,
		0,
		m_nNumTriangles);								//List���[�h�Ń��b�V����`��
}

bool CTerrain::FallCollider(CScene* pGameObject)
{
	if (pGameObject->GetPosition().y <= TERRAIN_HEIGHT)
	{
		return true;
	}
	else
	{
		return false;
	}
}
