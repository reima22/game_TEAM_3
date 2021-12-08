//===================================================================
//SourceFile: Terrain.cpp
//Author : Yo jitaku
//===================================================================
#include "Terrain.h"
#include "scene.h"
#include "scene3D.h"
#include "texture.h"
#include "textdata_Terrain.h"

//==============================================================================
// ��������
//==============================================================================
CTerrain *CTerrain::Create(CTerrainInfo::TERRAIN_TYPE nType)
{
	// ���[�J���ϐ��錾
	CTerrain *pTerrain = new CTerrain;

	// ������
	if (pTerrain != NULL)
		pTerrain->Init(nType);

	return pTerrain;
}

//*******************************************************************
//������
//*******************************************************************
HRESULT CTerrain::Init(CTerrainInfo::TERRAIN_TYPE nType)
{
	// �n�`�f�[�^�̎擾
	CTextDataTerrain* pTerrain = CTextDataTerrain::GetDataTerrain();
	m_type = nType;
	int nTypeID = nType;
	m_pDataTerrain = pTerrain->GetTerrain(nTypeID);
	m_nVertsPerRow = m_pDataTerrain->m_nCellsPerRow + 1;
	m_nVertsPerCol = m_pDataTerrain->m_nCellsPerCol + 1;
	m_nNumVertices = m_nVertsPerRow * m_nVertsPerCol;
	m_nCells = m_pDataTerrain->m_nCellsPerRow * m_pDataTerrain->m_nCellsPerCol;
	m_nNumTriangles = m_nCells * 2;
	m_nNumIndex = m_nCells * 6;
	m_fTerrainWidth = m_pDataTerrain->m_nCellsPerRow * m_pDataTerrain->m_fCellSpacing;
	m_fTerrainDepth = m_pDataTerrain->m_nCellsPerCol * m_pDataTerrain->m_fCellSpacing;

	if (nTypeID == CTerrainInfo::TERRAIN_VALLEY)
	{

	}
	else if (nTypeID == CTerrainInfo::TERRAIN_OCEAN)
		m_pWave->SetWaterSurface(m_pDataTerrain->m_W_fPower,
			m_pDataTerrain->m_W_fFrequency,
			m_pDataTerrain->m_W_fSpeed);
	else if (nTypeID == CTerrainInfo::TERRAIN_LAVA)
		m_pWave->SetWaveLine(m_pDataTerrain->m_W_fPower,
			m_pDataTerrain->m_W_fFrequency,
			m_pDataTerrain->m_W_fSpeed,
			m_pDataTerrain->m_W_dirX);

	WORD* pIdx;										//Index�o�b�t�@
	VERTEX_3D *pVtx;								//���_�o�b�t�@
	float fStartX = -m_fTerrainWidth / 2.0f;		  //x���W�̎n�_
	float fStartZ = -m_fTerrainDepth / 2.0f;		  //z���W�̎n�_
	float fCoordU = 0.0f;
	float fCoordV = 0.0f;

	m_ValidZoneMin.x = fStartX;
	m_ValidZoneMin.z = fStartZ;
	m_ValidZoneMax.x = -fStartX;
	m_ValidZoneMax.z = -fStartZ;

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
				(fStartZ + nCntRow * m_pDataTerrain->m_fCellSpacing),
				(float)TERRAIN_HEIGHT,
				(fStartX + nCntCol * m_pDataTerrain->m_fCellSpacing));
			pVtx[nIndex].nor = D3DXVECTOR3(0.f, 1.f, 0.f);
			if (nTypeID == CTerrainInfo::TERRAIN_OCEAN)
			{
				pVtx[nIndex].col = D3DXCOLOR(0.f, 1.f - nCntCol * fCoordU, 1.f, 1.f);
				pVtx[nIndex].tex = D3DXVECTOR2(nCntCol * fCoordU, nCntRow * fCoordV);
				pVtx[nIndex].tex *= 4.0f;
			}
			else
			{
				pVtx[nIndex].col = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
				pVtx[nIndex].tex = D3DXVECTOR2(nCntCol * fCoordU, nCntRow * fCoordV);
			}
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

	for (int row = 0; row < m_pDataTerrain->m_nCellsPerCol; row++)			//�Z����(�s)
	{
		for (int col = 0; col < m_pDataTerrain->m_nCellsPerRow; col++)		//�Z����(��)
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
	m_nCntTime++;
	//TerrainMove();

	if (m_pWave->m_bWaveLine)
		WaveLineUpdate();
	else if (m_pWave->m_bWaterSurface)
		WaterSurfaceUpdate();
}

//*******************************************************************
//�`��
//*******************************************************************
void CTerrain::Draw()
{
	//CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);
	D3DXMATRIX MtxWorld;
	D3DXMATRIX MtxRot, MtxTrans;	// Temporary matrices

	D3DXMatrixIdentity(&MtxWorld);									 //�P�ʍs��
	D3DXMatrixRotationYawPitchRoll(&MtxRot, m_pDataTerrain->m_Rot.x, m_pDataTerrain->m_Rot.y, m_pDataTerrain->m_Rot.z);
	D3DXMatrixMultiply(&MtxWorld, &MtxWorld, &MtxRot);
	D3DXMatrixTranslation(&MtxTrans, m_pDataTerrain->m_Pos.x, m_pDataTerrain->m_Pos.y, m_pDataTerrain->m_Pos.z);
	D3DXMatrixMultiply(&MtxWorld, &MtxWorld, &MtxTrans);

	m_pDevice->SetTransform(D3DTS_WORLD, &MtxWorld);				 //���E�}�g���b�N�X
	m_pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	m_pDevice->SetIndices(m_pIdxBuff);								 //Index�o�b�t�@������
	m_pDevice->SetFVF(FVF_VERTEX_3D);

	m_pDevice->SetTexture(0, m_pDataTerrain->m_pTexture);
	//m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);	//���C���[�t���[�����[�h
	m_pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		0,
		0,
		m_nNumVertices,
		0,
		m_nNumTriangles);											//List���[�h�Ń��b�V����`��
																	//m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);		//SOLID���[�h�ɖ߂�
}

bool CTerrain::FallCollider(CScene* pGameObject)
{
	if (pGameObject->GetPosition().x < m_ValidZoneMax.z &&
		pGameObject->GetPosition().z < m_ValidZoneMax.x &&
		pGameObject->GetPosition().x > m_ValidZoneMin.z &&
		pGameObject->GetPosition().z > m_ValidZoneMin.x)
	{
		if (pGameObject->GetPosition().y <= m_pDataTerrain->m_Pos.y)
			return true;
		else
			return false;
	}
	return false;
}

void CWave::SetWaveLine(float power, float fre, float speed, bool bDir)
{
	m_fPower = power;
	m_fFrequency = fre;
	m_fSpeed = speed;
	m_DirX = bDir;
	m_bWaveLine = true;
}

void CWave::SetWaterSurface(float power, float fre, float speed)
{
	m_fPower = power;
	m_fFrequency = fre;
	m_fSpeed = speed;
	m_bWaterSurface = true;
}

void CTerrain::WaveLineUpdate()
{
	VERTEX_3D *pVtx;												//���_�o�b�t�@

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);						// �o�b�t�@���b�N

																	// ���[�J���ϐ��錾
	int nIndex = 0;

	for (int nCntRow = 0; nCntRow < m_nVertsPerCol; nCntRow++)		//Z���_�̏���
	{
		for (int nCntCol = 0; nCntCol < m_nVertsPerRow; nCntCol++)	//X���_�̏���
		{
			if (m_pWave->m_DirX)
				pVtx[nIndex].pos.y +=
				sinf(pVtx[nIndex].pos.x * m_pWave->m_fFrequency +
					m_nCntTime * m_pWave->m_fSpeed) * m_pWave->m_fPower;
			else
				pVtx[nIndex].pos.y +=
				sinf(pVtx[nIndex].pos.z * m_pWave->m_fFrequency +
					m_nCntTime * m_pWave->m_fSpeed) * m_pWave->m_fPower;
			nIndex++;
		}
	}
	// �o�b�t�@�A�����b�N
	m_pVtxBuff->Unlock();
}

void CTerrain::TerrainMove()
{
	VERTEX_3D *pVtx;												//���_�o�b�t�@
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);						// �o�b�t�@���b�N
	int nIndex = 0;													// ���[�J���ϐ��錾
	for (int nCntRow = 0; nCntRow < m_nVertsPerCol; nCntRow++)		//Z���_�̏���
	{
		for (int nCntCol = 0; nCntCol < m_nVertsPerRow; nCntCol++)	//X���_�̏���
		{
			pVtx[nIndex].tex.x += TERRAIN_MOVE_SPEED;
			nIndex++;
		}
	}
	m_pWave->m_fStartPosY += TERRAIN_MOVE_SPEED;
	// �o�b�t�@�A�����b�N
	m_pVtxBuff->Unlock();
}

void CTerrain::WaterSurfaceUpdate()
{
	VERTEX_3D *pVtx;												//���_�o�b�t�@
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);						// �o�b�t�@���b�N
	int nIndex = 0;													// ���[�J���ϐ��錾
	for (int nCntRow = 0; nCntRow < m_nVertsPerCol; nCntRow++)		//Z���_�̏���
	{
		for (int nCntCol = 0; nCntCol < m_nVertsPerRow; nCntCol++)	//X���_�̏���
		{
			//abs(m_pWave->m_fStartPosY) * 2.0f / m_fTerrainDepth
			D3DXVECTOR2 dv = D3DXVECTOR2(m_pWave->m_fStartPosY, pVtx[nIndex].tex.y) - pVtx[nIndex].tex;
			//D3DXVECTOR2 dv = D3DXVECTOR2(0, 0) - pVtx[nIndex].tex;

			float fDis = sqrtf(dv.x * dv.x + dv.y * dv.y);
			float fPower = (m_pWave->m_fPower / m_pWave->EffectRange) * ((m_pWave->EffectRange - fDis) > 0.0f ? (m_pWave->EffectRange - fDis) : 0.0f);
			float fsinFactor = sinf(fDis * m_pWave->m_fFrequency - m_nCntTime *  m_pWave->m_fSpeed) * 0.01f * fPower;
			D3DXVECTOR2 dv1;
			D3DXVec2Normalize(&dv1, &dv);
			D3DXVECTOR2 offset = dv1 * fsinFactor;
			pVtx[nIndex].tex.x += offset.x;
			nIndex++;
		}
	}
	// �o�b�t�@�A�����b�N
	m_pVtxBuff->Unlock();
}