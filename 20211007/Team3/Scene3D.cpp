//=============================================================================
//
// 3Dポリゴン [scene3D.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "Scene3D.h"
#include "Manager.h"
#include "Input.h"

//*****************************************************************************
// ポリゴンクラス (派生元：オブジェクトクラス）
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CScene3D::CScene3D(int nPriority) : CScene(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pVertex = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene3D::~CScene3D()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene3D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// 引数から設定
	SetPos(pos);
	SetRot(rot);
	SetSize(size);

	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロックしてポインタ取得
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVertex, 0);

	// 頂点情報を設定
	// 位置
	m_pVertex[0].pos = D3DXVECTOR3(-size.x, 0.0f, -size.z);
	m_pVertex[1].pos = D3DXVECTOR3(-size.x, 0.0f, size.z);
	m_pVertex[2].pos = D3DXVECTOR3(size.x, 0.0f, -size.z);
	m_pVertex[3].pos = D3DXVECTOR3(size.x, 0.0f, size.z);

	// 法線
	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
		m_pVertex[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 色
	for (int nCntVtx = 0; nCntVtx < 4; nCntVtx++)
		m_pVertex[nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ
	m_pVertex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	m_pVertex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	m_pVertex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	m_pVertex[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// 頂点バッファアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScene3D::Uninit(void)
{
	// 頂点バッファを開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// インスタンス破棄
	this->Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene3D::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CScene3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// Device
	D3DXMATRIX mtxRot, mtxTrans;	// Temporary matrices

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXVECTOR3 rot = GetRot();
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXVECTOR3 pos = GetPos();
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴンの描画
	pDevice->SetTexture(0, m_pTexture);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// テクスチャのバインド
//=============================================================================
void CScene3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void CScene3D::SetTextureUV(D3DXVECTOR2 Vertex_0, D3DXVECTOR2 Vertex_1, D3DXVECTOR2 Vertex_2, D3DXVECTOR2 Vertex_3)
{
	// 頂点バッファをロックしてポインタ取得
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVertex, 0);

	// テクスチャ座標設定
	m_pVertex[0].tex = Vertex_0;
	m_pVertex[1].tex = Vertex_1;
	m_pVertex[2].tex = Vertex_2;
	m_pVertex[3].tex = Vertex_3;

	// 頂点バッファアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// カラーの設定
//=============================================================================
void CScene3D::SetColor(D3DXCOLOR col)
{
	// 頂点バッファをロックしてポインタ取得
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVertex, 0);

	// 色の設定
	m_pVertex[0].col = col;
	m_pVertex[1].col = col;
	m_pVertex[2].col = col;
	m_pVertex[3].col = col;

	// 頂点バッファアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 生成関数
//=============================================================================
CScene3D *CScene3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CScene3D *pScene3D;
	pScene3D = new CScene3D;
	if (pScene3D != NULL)
	{
		pScene3D->Init(pos, rot, size);
	}

	return pScene3D;
}