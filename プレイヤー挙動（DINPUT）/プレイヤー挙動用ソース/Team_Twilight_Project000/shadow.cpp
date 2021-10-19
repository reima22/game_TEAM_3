//==============================================================================
//
// 影の描画〔shadow.cpp〕
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "shadow.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"

//==============================================================================
// グローバル変数
//==============================================================================
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	// バッファへのポインタ
//LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;			// テクスチャへのポインタ
//Shadow g_aShadow[MAX_SHADOW];						// 影の構造体

// コンストラクタ
CShadow::CShadow() 
{

}

// デストラクタ
CShadow::~CShadow()
{

}

//==============================================================================
// 初期化処理
//==============================================================================
HRESULT CShadow::Init(D3DXVECTOR3 pos)
{
	// ローカル変数宣言
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/shadow000.jpg",
		&m_pTexture);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ポリゴンの各頂点座標
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y, m_pos.z - m_fDepth);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y, m_pos.z + m_fDepth);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y, m_pos.z - m_fDepth);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y, m_pos.z + m_fDepth);

	// 法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 各頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.85f);
	pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.85f);
	pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.85f);
	pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.85f);

	// テクスチャ頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==============================================================================
// 終了処理
//==============================================================================
void CShadow::Uninit(void)
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
}

//==============================================================================
// 更新処理
//==============================================================================
void CShadow::Update(void)
{

}

//==============================================================================
// 描画処理
//==============================================================================
void CShadow::Draw(void)
{
	// ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice;		// デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	// 減算合成の生成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	m_mtxWorld._11 = m_fWidth;
	m_mtxWorld._33 = m_fDepth;

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

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// プリミティブの種類
		0,						// 描画を開始する頂点インデックス
		2);						// 描画するプリミティブ数

	// 通常の合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}


// 影の生成
CShadow *CShadow::Create(D3DXVECTOR3 pos, float fWidth, float fDepth)
{
	// ローカル変数宣言
	CShadow *pShadow;
	pShadow = new CShadow;

	if (pShadow != NULL)
	{
		pShadow->SetWidth(fWidth);
		pShadow->SetDepth(fDepth);
		pShadow->Init(pos);
	}

	return pShadow;
}

//==============================================================================
// 影の設定
//==============================================================================
//int SetShadow(D3DXVECTOR3 pos, float fWidth, float fDepth)
//{
//	// ローカル変数宣言
//	Shadow *pShadow;
//	pShadow = &g_aShadow[0];
//	int nIdx = -1;
//
//	// 影の設定
//	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++, pShadow++)
//	{
//		if (pShadow->bUse == false)
//		{
//			pShadow->pos = pos;			// 位置の設定
//
//			pShadow->fWidth = fWidth;	// 幅の設定
//
//			pShadow->fDepth = fDepth;	// 奥行の設定
//
//			pShadow->bUse = true;		// 使用状態への移行
//
//			nIdx = nCnt;				// インデックスへの代入
//
//			break;
//		}
//	}
//
//	return nIdx;	// nIdx番目として返す
//}

////==============================================================================
//// 影の追従
////==============================================================================
//void SetPositionShadow(int nIdx, D3DXVECTOR3 pos)
//{
//	m_pos = pos;
//}