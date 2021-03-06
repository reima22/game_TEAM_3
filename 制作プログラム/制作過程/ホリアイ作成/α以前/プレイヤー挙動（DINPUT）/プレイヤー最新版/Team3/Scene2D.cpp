//=============================================================================
//
// 2Dポリゴン [scene2D.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "scene2D.h"
#include "manager.h"
#include "input.h"

//*****************************************************************************
// ポリゴンクラス (派生元：オブジェクトクラス）
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CScene2D::CScene2D(int nPriority) : CScene(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pVertex = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene2D::~CScene2D()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// 引数から設定
	SetPos(pos);
	SetRot(rot);
	SetSize(size);

	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロックしてポインタ取得
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVertex, 0);

	// 頂点情報を設定
	// 位置
	m_pVertex[0].pos = D3DXVECTOR3(-size.x + pos.x, size.y + pos.y, 0.0f);
	m_pVertex[1].pos = D3DXVECTOR3(-size.x + pos.x, -size.y + pos.y, 0.0f);
	m_pVertex[2].pos = D3DXVECTOR3(size.x + pos.x, size.y + pos.y, 0.0f);
	m_pVertex[3].pos = D3DXVECTOR3(size.x + pos.x, -size.y + pos.y, 0.0f);

	// rhw
	m_pVertex[0].rhw = 1.0f;
	m_pVertex[1].rhw = 1.0f;
	m_pVertex[2].rhw = 1.0f;
	m_pVertex[3].rhw = 1.0f;

	// 色
	m_pVertex[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pVertex[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pVertex[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pVertex[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

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
void CScene2D::Uninit(void)
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
void CScene2D::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CScene2D::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	pDevice->SetTexture(0, m_pTexture);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// テクスチャのバインド
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void CScene2D::SetTextureUV(D3DXVECTOR2 Vertex_0, D3DXVECTOR2 Vertex_1, D3DXVECTOR2 Vertex_2, D3DXVECTOR2 Vertex_3)
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
void CScene2D::SetColor(D3DXCOLOR col)
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
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CScene2D *pScene2D;
	pScene2D = new CScene2D;
	if (pScene2D != NULL)
	{
		pScene2D->Init(pos, rot, size);
	}

	return pScene2D;
}