//===================================================================
//SourceFile: Terrain.cpp
//Author : Yo jitaku
//===================================================================
#include "Terrain.h"
#include "scene.h"
#include "scene3D.h"
#include "texture.h"

//*******************************************************************
//メモリの解放
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
//初期化
//*******************************************************************
HRESULT CTerrain::Init()
{
	WORD* pIdx;										//Indexバッファ
	VERTEX_3D *pVtx;								//頂点バッファ

	float fStartX = -m_fTerrainWidth / 2.0f;		  //x座標の始点
	float fStartZ = -m_fTerrainDepth / 2.0f;		  //z座標の始点
	float fCoordU = 0.0f;
	float fCoordV = 0.0f;
	if (m_nVertsPerRow != m_nVertsPerCol)
	{
		if (m_nVertsPerRow > m_nVertsPerCol)
		{
			fCoordU = 1.0f / (float)m_nVertsPerCol;     //テクスチャーのU座標
			fCoordV = 1.0f / (float)m_nVertsPerCol;     //テクスチャーのV座標
		}
		else
		{
			fCoordU = 1.0f / (float)m_nVertsPerRow;     //テクスチャーのU座標
			fCoordV = 1.0f / (float)m_nVertsPerRow;     //テクスチャーのV座標
		}
	}
	else
	{
		fCoordU = 1.0f / (float)m_nVertsPerRow;     //テクスチャーのU座標
		fCoordV = 1.0f / (float)m_nVertsPerCol;     //テクスチャーのV座標
	}


	//頂点バッファについて
	if (FAILED(m_pDevice->CreateVertexBuffer(
		m_nNumVertices * sizeof(VERTEX_3D),
		D3DUSAGE_WRITEONLY, 
		FVF_VERTEX_3D, 
		D3DPOOL_MANAGED, 
		&m_pVtxBuff, NULL)))
		return E_FAIL;

	// バッファロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nIndex = 0;

	for (int nCntRow = 0; nCntRow < m_nVertsPerCol; nCntRow++)//Z頂点の巡り
	{
		for (int nCntCol = 0; nCntCol < m_nVertsPerRow; nCntCol++)//X頂点の巡り
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

	// バッファアンロック
	m_pVtxBuff->Unlock();

	//indexバッファについて
	if (FAILED(m_pDevice->CreateIndexBuffer
	(sizeof(WORD) * m_nNumIndex,							//描画必要の最低の頂点数(重複の頂点がある) (頂点数＝2×行数×(列数+1)+2×(行数-1)) -> 2(xy+2x-1)
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL)))
		return E_FAIL;

	// インデックスバッファロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	nIndex = 0;
	
	for (int row = 0; row < m_nCellsPerCol; row++)			//セル数(行)
	{
		for (int col = 0; col < m_nCellsPerRow; col++)		//セル数(列)
		{
			//毎回描画必要の矩形(セル)(=二つ三角形=四つ頂点バッファ=六つIndexバッファ)
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

	// インデックスバッファアンロック
	m_pIdxBuff->Unlock();
	return S_OK;
}

void CTerrain::Update()
{
	VERTEX_3D *pVtx;												//頂点バッファ

	// バッファロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ローカル変数宣言
	int nIndex = 0;
	
	for (int nCntRow = 0; nCntRow < m_nVertsPerCol; nCntRow++)		//Z頂点の巡り
	{
		for (int nCntCol = 0; nCntCol < m_nVertsPerRow; nCntCol++)	//X頂点の巡り
		{
			pVtx[nIndex].tex.x += TERRAIN_MOVE_SPEED;
			nIndex++;
		}
	}

	// バッファアンロック
	m_pVtxBuff->Unlock();
}

//*******************************************************************
//描画
//*******************************************************************
void CTerrain::Draw()
{
	D3DXMATRIX MtxWorld;
	D3DXMATRIX MtxRot, MtxTrans;	// Temporary matrices

	D3DXMatrixIdentity(&MtxWorld);									 //単位行列
	D3DXMatrixRotationYawPitchRoll(&MtxRot, 0, 0, 0);
	D3DXMatrixMultiply(&MtxWorld, &MtxWorld, &MtxRot);
	D3DXMatrixTranslation(&MtxTrans, 0, 0, 0);
	D3DXMatrixMultiply(&MtxWorld, &MtxWorld, &MtxTrans);

	m_pDevice->SetTransform(D3DTS_WORLD, &MtxWorld);				 //世界マトリックス
	m_pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	m_pDevice->SetIndices(m_pIdxBuff);								 //Indexバッファあげる
	m_pDevice->SetFVF(FVF_VERTEX_3D);

	CTexture *pTexture = CManager::GetTexture();

	m_pDevice->SetTexture(0, pTexture->GetAddress(31));

	m_pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		0,
		0,
		m_nNumVertices,
		0,
		m_nNumTriangles);								//Listモードでメッシュを描画
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
