//==============================================================================
//
// ビルボード描画処理〔sceneBillboard.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene3D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "texture.h"
#include "fade.h"
#include "effect.h"

int CEffect::m_nNum = 0;
//==============================================================================
// コンストラクタ
//==============================================================================
CEffect::CEffect(int nPriority) : CScene(nPriority)
{
	//m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nIdx = m_nNum;
	m_nNum++;
}

//==============================================================================
// デストラクタ
//==============================================================================
CEffect::~CEffect()
{

}

//==============================================================================
// ビルボードの初期化処理
//==============================================================================
HRESULT CEffect::Init(void)
{
	// ローカル変数宣言
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

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
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	// 法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// 各頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// テクスチャ頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	// エフェクト情報の設定
	SetEffect();

	return S_OK;
}

//==============================================================================
// ポリゴン描画の終了処理
//==============================================================================
void CEffect::Uninit(void)
{
	// 頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// テクスチャの開放
	//if (m_pTexture != NULL)
	//{
	//	m_pTexture->Release();
	//	m_pTexture = NULL;
	//}

	m_nNum--;

	Release();
}

//==============================================================================
// ポリゴン描画の更新処理
//==============================================================================
void CEffect::Update(void)
{  
	// 頂点情報の設定
	SetVertex();

	// エフェクトの挙動
	EffectMove();
}

//==============================================================================
// ポリゴン描画の描画処理
//==============================================================================
void CEffect::Draw(void)
{
	// ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice;	// デバイスのポインタ
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans;	// 計算用マトリックス

	// デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	// ライトをオフにする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Zテストの更新
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// 加算合成によるアルファブレンディング
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// ビューマトリックスの取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

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

	// 通常のアルファブレンディング
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// 元に戻す
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ライトをオンにする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==============================================================================
// ビルボードの生成
//==============================================================================
CEffect *CEffect::Create(void)
{
	// ローカル変数宣言
	CEffect *pEffect;
	pEffect = new CEffect;

	// 初期化
	if (pEffect != NULL)
	{
		pEffect->Init();
	}

	// 返し値
	return pEffect;
}

//==============================================================================
// エフェクトの設定
//==============================================================================
void CEffect::SetEffect(void)
{
	// ローカル変数宣言
	CTexture *pTexture = CManager::GetTexture();

	switch (m_effectType)
	{
	case EFFECTTYPE_SANDSMOKE:	// 砂煙

		m_pTexture = pTexture->GetAddress("EFFECT");
		SetColor(D3DXCOLOR(0.34f, 0.47f, 0.21f, 1.0f));

		break;
	}
}

//==============================================================================
// 頂点情報の設定
//==============================================================================
void CEffect::SetVertex(void)
{
	// ローカル変数宣言
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ポリゴンの各頂点座標
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(-m_size.x, +m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(+m_size.x, -m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_size.x, +m_size.y, 0.0f);

	// 各頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//==============================================================================
// エフェクトの挙動
//==============================================================================
void CEffect::EffectMove(void)
{
	switch (m_effectType)
	{
	case EFFECTTYPE_SANDSMOKE:
		m_move = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
		m_size += D3DXVECTOR2(0.5f, 0.5f);
		m_fAlphaDown = 0.01f;

		break;
	}

	// 透明度の低下
	m_col.a -= m_fAlphaDown;

	m_pos += m_move;
}

//==============================================================================
// テクスチャの情報設定
//==============================================================================
void CEffect::SetTexture(char *pText)
{
	// ローカル変数宣言
	CTexture *pTexture = CManager::GetTexture();

	// テクスチャの割り当て
	m_pTexture = pTexture->GetAddress(pText);
}


/*砂煙エフェクト*/

//==============================================================================
// コンストラクタ
//==============================================================================
CEffectSand::CEffectSand()
{
	//m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//==============================================================================
// デストラクタ
//==============================================================================
CEffectSand::~CEffectSand()
{

}

//==============================================================================
// ビルボードの初期化処理
//==============================================================================
HRESULT CEffectSand::Init(D3DXVECTOR3 pos)
{
	if (m_pEffect == NULL)
	{
		m_pEffect = CEffect::Create();
		m_pEffect->SetPosition(pos);
		m_pEffect->SetMove(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
		m_pEffect->SetSize(D3DXVECTOR2(1.0f, 1.0f));
		m_pEffect->SetColor(D3DXCOLOR(0.34f, 0.23f, 0.13f, 1.0f));
		m_pEffect->SetTexture("EFFECT");
		m_pEffect->SetType(EFFECTTYPE_SANDSMOKE);
		m_pEffect->SetAlphaDown(0.01f);
	}

	return S_OK;
}

//==============================================================================
// ポリゴン描画の終了処理
//==============================================================================
void CEffectSand::Uninit(void)
{
	if (m_pEffect != NULL)
	{
		m_pEffect->Uninit();
		m_pEffect = NULL;
	}

	Release();
}

//==============================================================================
// ポリゴン描画の更新処理
//==============================================================================
void CEffectSand::Update(void)
{
	if (m_pEffect != NULL)
	{
		// 破棄条件
		if (m_pEffect->GetColor().a <= 0.0f)
		{
			Uninit();
			return;
		}
	}
}

//==============================================================================
// ポリゴン描画の描画処理
//==============================================================================
void CEffectSand::Draw(void)
{
}

//==============================================================================
// エフェクトの生成
//==============================================================================
CEffectSand *CEffectSand::Create(D3DXVECTOR3 pos)
{
	// ローカル変数宣言
	CEffectSand *pEffectSand;
	pEffectSand = new CEffectSand;

	// 初期化
	if (pEffectSand != NULL)
	{
		pEffectSand->Init(pos);
	}

	// 返し値
	return pEffectSand;
}