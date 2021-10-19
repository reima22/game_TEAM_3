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

//==============================================================================
// マクロ定義
//==============================================================================
//#define WIDTHNUM	(10)		// 列数(幅)
//#define DEPTHNUM	(10)		// 行数(奥行)
//#define WIDTH		(100.0f)	// 幅の大きさ
//#define DEPTH		(100.0f)	// 奥行の大きさ
#define POINT_MAX	(65535)		// 頂点数の最大
#define IDX_MAX		(65535)		// インデックスバッファの最大確保数
#define FIELD_MAX	(32)		// フィールドの最大数

//==============================================================================
// グローバル変数
//==============================================================================
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;	// バッファへのポインタ
//LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshfield = NULL;	// インデックスバッファへのポインタ
//LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;		// テクスチャへのポインタ
//D3DXVECTOR3 g_posMeshfield;							// 位置
//D3DXVECTOR3 g_rotMeshfield;							// 向き
//D3DXMATRIX g_mtxWorldMeshfield;						// ワールドマトリックス
//int g_nAllPoint;									// 総頂点数
//int g_nPolygon;										// ポリゴン数
//int g_nIdxPoint;									// インデックスバッファの必要な確保数
//float g_fWidth = WIDTH;								// 横幅の端
//float g_fDepth = DEPTH;								// 奥行の端
//int g_nWidth = WIDTHNUM + 1;						// 横幅の頂点数
//int g_nDepth = DEPTHNUM + 1;						// 奥行の頂点数

//==============================================================================
// コンストラクタ
//==============================================================================
CMeshField::CMeshField() 
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CMeshField::~CMeshField()
{

}


//==============================================================================
// 初期化処理
//==============================================================================
HRESULT CMeshField::Init(D3DXVECTOR3 pos)
{
	// ローカル変数宣言
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	WORD *pIdx;

	// デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/field000.jpg",
		&m_pTexture);

	// 変数の初期化
	m_pos = pos;
	//g_rotMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nAllPoint = m_nDepth * 2 * (m_nWidth + 2) - 2;				// 総頂点数
	m_nPolygon = m_nWidth * m_nDepth * 2 + (4 * (m_nDepth - 1));	// 総ポリゴン数
	m_nWidthPoint = m_nWidth + 1;
	m_nDepthPoint = m_nDepth + 1;
	
	m_nIdxPoint = m_nWidthPoint * m_nDepthPoint;					// インデックスバッファでの頂点数
	
																	
	float fWidthMax = m_fWidth * (float)m_nWidth;
	float fDepthMax = m_fDepth * (float)m_nDepth;

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_nIdxPoint/* * FIELD_MAX*/,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_nDepthPoint; nCnt++)
	{// 奥行軸
		for (int nCntA = 0; nCntA < m_nWidthPoint; nCntA++)
		{// 横軸
		 // ポリゴンの各頂点座標
			pVtx[0].pos = D3DXVECTOR3(
				-fWidthMax / 2.0f + (float)nCntA * m_fWidth,
				m_pos.y,
				fDepthMax / 2.0f - (float)nCnt * m_fDepth);

			//pVtx[0].pos = D3DXVECTOR3(-g_fWidth + (float)nCntA * fWidthPart, g_posMeshfield.y, g_fDepth - (float)nCnt * fDepthPart);

			// 法線ベクトルの設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 各頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ頂点情報の設定
			pVtx[0].tex = D3DXVECTOR2(1.0f * nCntA, 1.0f * nCnt);

			pVtx++;
		}
	}

	// ポリゴンの各頂点座標
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

	// 法線ベクトルの設定
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

	// 各頂点カラーの設定
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

	// テクスチャ頂点情報の設定
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

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * m_nAllPoint /** FIELD_MAX*/,
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
void CMeshField::Uninit(void)
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
}

//==============================================================================
// 更新処理
//==============================================================================
void CMeshField::Update(void)
{
	
}

//==============================================================================
// 描画処理
//==============================================================================
void CMeshField::Draw(void)
{
	// ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice;		// デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//for (int nCnt = 0; nCnt < FIELD_MAX; nCnt++, pField++)
	//{
	//	if (pField->bUse == true)
	//	{
	//		// ワールドマトリックスの初期化
	//		D3DXMatrixIdentity(&pField->mtxWorld);
	//		// 向きの反映
	//		D3DXMatrixRotationYawPitchRoll(&mtxRot, pField->rot.y, pField->rot.x, pField->rot.z);
	//		D3DXMatrixMultiply(&pField->mtxWorld, &pField->mtxWorld, &mtxRot);
	//		// 位置を反映
	//		D3DXMatrixTranslation(&mtxTrans, pField->pos.x, pField->pos.y, pField->pos.z);
	//		D3DXMatrixMultiply(&pField->mtxWorld, &pField->mtxWorld, &mtxTrans);
	//		// ワールドマトリックスの設定
	//		pDevice->SetTransform(D3DTS_WORLD, &pField->mtxWorld);
	//		// 頂点バッファをデータストリームに設定
	//		pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));
	//		// インデックスバッファをデータストリームに設定
	//		pDevice->SetIndices(g_pIdxBuffMeshfield);
	//		// 頂点フォーマットの設定
	//		pDevice->SetFVF(FVF_VERTEX_3D);
	//		// テクスチャの設定
	//		pDevice->SetTexture(0, g_pTextureMeshfield);
	//		// ポリゴンの描画
	//		pDevice->DrawIndexedPrimitive(
	//			D3DPT_TRIANGLESTRIP,	// プリミティブの種類
	//			0,
	//			0,
	//			pField->nIdxPoint,			// 頂点数
	//			0,
	//			pField->nPolygon);			// プリミティブ数
	//	}
	//}

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

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
CMeshField *CMeshField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nWidth, int nDepth, float fWidth, float fDepth)
{
	// ローカル変数宣言
	CMeshField *pMeshField;
	pMeshField = new CMeshField;

	if (pMeshField != NULL)
	{
		// 変数の設定
		pMeshField->SetRotation(rot);
		pMeshField->SetWidthNum(nWidth);
		pMeshField->SetDepthNum(nDepth);
		pMeshField->SetWidthSize(fWidth);
		pMeshField->SetDepthSize(fDepth);

		pMeshField->Init(pos);
	}

	return pMeshField;
}