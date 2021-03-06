//==============================================================================
//
// メッシュフィールドの描画〔meshfield.cpp〕
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
// コンストラクタ
//==============================================================================
CMeshfield::CMeshfield()
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CMeshfield::~CMeshfield()
{

}

//==============================================================================
// 初期化処理
//==============================================================================
HRESULT CMeshfield::Init(void)
{
	// ローカル変数宣言
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	WORD *pIdx;

	// デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	CTexture *pTexture = CManager::GetTexture();

	// テキストのデータ
	CTextDataMeshfield *pDataMeshfield;
	pDataMeshfield = CTextData::GetDataMeshfield();

	// データの割り当て
	m_pos = pDataMeshfield->GetPosition(m_nIdx);
	m_rot = pDataMeshfield->GetRotation(m_nIdx);
	m_nWidth = pDataMeshfield->GetWidthPoly(m_nIdx);
	m_nDepth = pDataMeshfield->GetDepthPoly(m_nIdx);
	m_fWidth = pDataMeshfield->GetSize(m_nIdx).x;
	m_fDepth = pDataMeshfield->GetSize(m_nIdx).y;
	
	m_pTexture = pTexture->GetAddress("TEX0");

	// 各変数の計算
	m_nAllPoint = m_nDepth * 2 * (m_nWidth + 2) - 2;				// 総頂点数
	m_nPolygon = m_nWidth * m_nDepth * 2 + (4 * (m_nDepth - 1));	// 総ポリゴン数
	m_nWidthPoint = m_nWidth + 1;
	m_nDepthPoint = m_nDepth + 1;

	m_nIdxPoint = m_nWidthPoint * m_nDepthPoint;					// インデックスバッファでの頂点数

	// 頂点数の動的確保
	//m_posVtx = new D3DXVECTOR3[m_nIdxPoint];

	float fWidthMax = m_fWidth * (float)m_nWidth;
	float fDepthMax = m_fDepth * (float)m_nDepth;

	// 法線を求めるポリゴン数
	m_nNor = m_nWidth * m_nDepth * 2;

	// 法線値動的確保
	m_pNor = new D3DXVECTOR3[m_nNor];

	m_nIdxNor = 0;

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_nIdxPoint,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntPoint = 0;

	for (int nCnt = 0; nCnt < m_nDepthPoint; nCnt++)
	{// 奥行軸
		for (int nCntA = 0; nCntA < m_nWidthPoint; nCntA++)
		{// 横軸
		 // ポリゴンの各頂点座標
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


			//m_posVtx[nCntPoint] = pVtx[0].pos;	// 頂点設定

			// 法線ベクトルの設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 各頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ頂点情報の設定
			pVtx[0].tex = D3DXVECTOR2(1.0f * nCntA, 1.0f * nCnt);

			pVtx++;
			nCntPoint++;
		}
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * m_nAllPoint,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	// インデックスバッファをロックし、番号データへのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntA = 0; nCntA < m_nDepth; nCntA++)
	{
		for (int nCnt = 0; nCnt < m_nWidthPoint + 1; nCnt++, pIdx += 2)
		{
			if (nCnt != 0 && nCnt == m_nWidthPoint && nCntA != m_nDepth - 1)
			{// 右端から折り返す時
				pIdx[0] = pIdx[-1];
				pIdx[1] = pIdx[-2] + 1;
			}
			else if (nCntA == m_nDepth - 1 && nCnt == m_nWidthPoint)
			{// 終了時に無視する
				break;
			}
			else
			{// 通常配置
				pIdx[0] = m_nWidthPoint + (m_nWidthPoint * nCntA) + nCnt;
				pIdx[1] = pIdx[0] - m_nWidthPoint;
			}
		}
	}

	// インデックスバッファをアンロックする
	m_pIdxBuff->Unlock();

	return S_OK;
}

//==============================================================================
// 終了処理
//==============================================================================
void CMeshfield::Uninit(void)
{
	// 頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// テクスチャの開放
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// インデックスバッファの開放
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	// 法線開放
	if (m_pNor != NULL)
	{
		delete[] m_pNor;
		m_pNor = NULL;
	}
}

//==============================================================================
// 更新処理
//==============================================================================
void CMeshfield::Update(void)
{
	// 波形の挙動
	//MeshWave();

	// 法線の計算
	CalcuNormal();
}

//==============================================================================
// 描画処理
//==============================================================================
void CMeshfield::Draw(void)
{
	// ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice;		// デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//// 向きの反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//// 位置を反映
	//D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,	// プリミティブの種類
		0,
		0,
		m_nIdxPoint,			// 頂点数
		0,
		m_nPolygon);			// プリミティブ数
}

//==============================================================================
// フィールドの生成
//==============================================================================
CMeshfield *CMeshfield::Create(int nIdx)
{
	// ローカル変数宣言
	CMeshfield *pMeshField;
	pMeshField = new CMeshfield;

	if (pMeshField != NULL)
	{
		// 変数の設定
		pMeshField->SetIdx(nIdx);

		// 初期化
		pMeshField->Init();
	}

	return pMeshField;
}

//==============================================================================
// 法線計算
//==============================================================================
void CMeshfield::CalcuNormal(void)
{
	// ローカル変数宣言
	VERTEX_3D *pVtx;
	D3DXVECTOR3 vecA = VECTOR3_NULL;
	D3DXVECTOR3 vecB = VECTOR3_NULL;

	int nCntNormal = 0;	// 法線カウント

						// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 各面の法線算出
	for (int nCntDepth = 0; nCntDepth < m_nDepth; nCntDepth++)
	{// 奥行面数
		int nCntOdd = 0;	// 奇数カウント
		int nCntEven = 0;	// 偶数カウント

		for (int nCntWidth = 0; nCntWidth < m_nWidth * 2; nCntWidth++)
		{// 横幅頂点数（三角形ポリゴン数）						
			if (nCntWidth % 2 == 0)
			{
				// 偶数時ベクトル
				vecA =
					pVtx[m_nWidthPoint + (m_nWidthPoint * nCntDepth) - m_nWidthPoint + nCntEven].pos -
					pVtx[m_nWidthPoint + (m_nWidthPoint * nCntDepth) + nCntEven].pos;

				vecB =
					pVtx[m_nWidthPoint + (m_nWidthPoint * nCntDepth) + nCntEven + 1].pos -
					pVtx[m_nWidthPoint + (m_nWidthPoint * nCntDepth) + nCntEven].pos;

				nCntEven++;		// 偶数カウント
			}
			else
			{
				// 奇数時ベクトル
				vecA =
					pVtx[m_nWidthPoint + (m_nWidthPoint * nCntDepth) + nCntOdd - m_nWidth + m_nWidthPoint].pos -
					pVtx[m_nWidthPoint + (m_nWidthPoint * nCntDepth) + nCntOdd - m_nWidth].pos;

				vecB =
					pVtx[m_nWidthPoint + (m_nWidthPoint * nCntDepth) + nCntOdd - m_nWidth - 1].pos -
					pVtx[m_nWidthPoint + (m_nWidthPoint * nCntDepth) + nCntOdd - m_nWidth].pos;

				nCntOdd++;		// 奇数カウント
			}

			// 法線ベクトルの計算
			D3DXVec3Cross(&m_pNor[nCntNormal], &vecA, &vecB);

			// 法線ベクトルの正規化
			D3DXVec3Normalize(&m_pNor[nCntNormal], &m_pNor[nCntNormal]);

			// 現在のカウント
			nCntNormal++;
		}
	}

	// ローカル変数宣言
	int nCntUnder = m_nWidth * 2 * (m_nDepth - 1);	// 下辺開始面法線インデックス
	int nCntLeft = m_nWidth * 2;					// 左辺開始面法線インデックス
	int nCntRight = m_nWidth * 2 - 1;				// 右辺開始面法線インデックス
	int nRight = 1;									// 右辺開始地点インデックス計算用

	int nCntCenterA = 0;							// 内側頂点計算用上側
	int nCntCenterB
		= nCntCenterA + (m_nWidthPoint * 2 - 1);	// 内側頂点計算用下側
	int nCntCenterC = 1;							// 内側頂点計算用折り返しカウント

													// 各頂点の法線算出
	for (int nCntNor = 0; nCntNor < m_nIdxPoint; nCntNor++)
	{
		// 2面法線
		if (nCntNor == 0)
		{// 最初(左上)
			pVtx[nCntNor].nor = m_pNor[0] + m_pNor[1];
		}
		else if (nCntNor == m_nIdxPoint - 1)
		{// 最後(右下)
			pVtx[nCntNor].nor = m_pNor[m_nNor - 1] + m_pNor[m_nNor - 2];
		}

		// 1面法線
		else if (nCntNor == m_nWidth)
		{// 右上
			pVtx[nCntNor].nor = m_pNor[m_nWidth * 2 - 1];
		}
		else if (nCntNor == (m_nWidth + 1) + ((m_nDepth - 1) * (m_nWidth + 1)))
		{// 左下
			pVtx[nCntNor].nor = m_pNor[m_nWidth * 2 * (m_nDepth - 1)];
		}

		// 3面法線
		else if (nCntNor > 0 && nCntNor < m_nWidth)
		{// 上辺中央部
		 // ローカル変数宣言
			int nCntA = nCntNor + (nCntNor - 1);	// 始発となる面インデックス

			pVtx[nCntNor].nor = m_pNor[nCntA] + m_pNor[nCntA + 1] + m_pNor[nCntA + 2];
		}
		else if (nCntNor >(m_nWidth + 1) + ((m_nDepth - 1) * (m_nWidth + 1)) && nCntNor < m_nIdxPoint - 1)
		{// 下辺中央部
			pVtx[nCntNor].nor = m_pNor[nCntUnder] + m_pNor[nCntUnder + 1] + m_pNor[nCntUnder + 2];
			nCntUnder += 2;
		}
		else if (nCntNor % m_nWidthPoint == 0 && nCntNor != 0)
		{// 左辺中央部
			pVtx[nCntNor].nor = m_pNor[nCntLeft] + m_pNor[nCntLeft + 1] + m_pNor[nCntLeft - (m_nWidth * 2)];
			nCntLeft += m_nWidth * 2;
		}
		else if (nCntNor % (m_nWidth + m_nWidthPoint * nRight) == 0 && nCntNor != 0)
		{// 右辺中央部
			pVtx[nCntNor].nor = m_pNor[nCntRight] + m_pNor[nCntRight - 1] + m_pNor[nCntRight + (m_nWidth * 2)];
			nCntRight += m_nWidth * 2;
			nRight++;
		}

		// 例外的頂点(6面法線)
		else
		{// 内側の頂点
			pVtx[nCntNor].nor =
				m_pNor[nCntCenterA] + m_pNor[nCntCenterA + 1] + m_pNor[nCntCenterA + 2] +
				m_pNor[nCntCenterB] + m_pNor[nCntCenterB + 1] + m_pNor[nCntCenterB + 2];

			if (nCntNor % ((m_nWidth - 1) + m_nWidthPoint * nCntCenterC) == 0)
			{// 折り返し地点
				nCntCenterA += 4;
				nCntCenterB += 4;
				nCntCenterC++;
			}
			else
			{// 例外
				nCntCenterA += 2;
				nCntCenterB += 2;
			}
		}

		// ベクトルの正規化
		D3DXVec3Normalize(&pVtx[nCntNor].nor, &pVtx[nCntNor].nor);
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//==============================================================================
// メッシュの波形
//==============================================================================
void CMeshfield::MeshWave(void)
{
	m_nCntWave++;

	// ローカル変数宣言
	VERTEX_3D *pVtx;
	int nIdx = 0;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
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

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}