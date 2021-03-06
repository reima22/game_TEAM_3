//==============================================================================
//
// モデル管理〔model.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "model.h"
#include "textdata_player.h"
#include "texture.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CModel::CModel()
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CModel::~CModel()
{

}

//==============================================================================
// 3Dモデル描画の初期化処理
//==============================================================================
HRESULT CModel::Init(char *pFileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャポインタの取得
	CTexture *pTexture;
	pTexture = CManager::GetTexture();

	// Xファイルの読み込み
	D3DXLoadMeshFromX(
		pFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	// 親ポインタ
	m_pParent = NULL;

	// 位置・角度設定
	m_pos = pos;
	m_rot = rot;

	m_vtxMin = VTX_MIN;
	m_vtxMax = VTX_MAX;

	// テクスチャの設定
	m_pTexture = new LPDIRECT3DTEXTURE9[m_nNumMat];	// テクスチャポインタ配列の動的確保(マテリアルの数だけ)

	int nNumVtx;			// 頂点数
	DWORD sizeFVF;			// 頂点フォーマットのサイズ 
	BYTE *pVtxBuff;			// 頂点バッファへのポインタ
	D3DXMATERIAL *pMat;		// マテリアルへのポインタ

	// バッファポインタの取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// オブジェクトごとの設定
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{// テクスチャあり
			// テクスチャ情報の割り当て
			m_pTexture[nCntMat] = pTexture->GetAddress3D(pMat[nCntMat].pTextureFilename);
		}
		else
		{// テクスチャの割り当てがない
			m_pTexture[nCntMat] = NULL;
		}

		// 頂点数を取得
		nNumVtx = m_pMesh->GetNumVertices();

		// 頂点フォーマットのサイズの取得
		sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

		// 頂点バッファをロック
		m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		// 頂点座標の比較
		for (int nCntVtx = 0; nCntVtx < (int)nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// 頂点座標の代入

			// 各座標の最大値の比較
			if (m_vtxMax.x < vtx.x)
			{
				m_vtxMax.x = vtx.x;
			}
			if (m_vtxMax.y < vtx.y)
			{
				m_vtxMax.y = vtx.y;
			}
			if (m_vtxMax.z < vtx.z)
			{
				m_vtxMax.z = vtx.z;
			}

			// 各座標の最小値の比較
			if (m_vtxMin.x > vtx.x)
			{
				m_vtxMin.x = vtx.x;
			}
			if (m_vtxMin.y > vtx.y)
			{
				m_vtxMin.y = vtx.y;
			}
			if (m_vtxMin.z > vtx.z)
			{
				m_vtxMin.z = vtx.z;
			}

			pVtxBuff += sizeFVF;	// 頂点フォーマットのサイズ分ポインタを進める
		}

		// 頂点バッファをアンロック
		m_pMesh->UnlockVertexBuffer();
	}

	// 当たり判定用設定
	SetCollisionInfo();

	return S_OK;
}

//==============================================================================
// 3Dモデル描画の終了処理
//==============================================================================
void CModel::Uninit(void)
{
	// メッシュポインタの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// マテリアルバッファの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	// テクスチャの開放
	if (m_pTexture != NULL)
	{
		delete[] m_pTexture;
		m_pTexture = NULL;
	}
}

//==============================================================================
// 3Dモデル描画の更新処理
//==============================================================================
void CModel::Update(void)
{

}

//==============================================================================
// 3Dモデルの描画処理
//==============================================================================
void CModel::Draw(void)
{
	// ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;										// 計算用マトリックス
	D3DMATERIAL9 matDef;												// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;													// マテリアルデータへのポインタ
	D3DXMATRIX mtxParent;												// 親のマトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != NULL)
	{// 親マトリックスが存在しない
		// 親マトリックスの取得
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{
		// 現在のプレイヤーマトリックスを取得する
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	// 親のマトリックスと掛け合わせる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャの設定
		if (m_pTexture[nCntMat] != NULL)
		{
			pDevice->SetTexture(0, m_pTexture[nCntMat]);
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}

		// モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//==============================================================================
// 生成処理
//==============================================================================
CModel *CModel::Create(char *pFileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ローカル変数宣言
	CModel *pModel;
	pModel = new CModel;	// インスタンス生成

	// 初期化
	if (pModel != NULL)
	{
		pModel->Init(pFileName, pos, rot);
	}

	return pModel;
}

//==============================================================================
// 当たり判定用設定
//==============================================================================
void CModel::SetCollisionInfo(void)
{
	// 頂点位置
	m_aPosVtx[0] = D3DXVECTOR3(m_pos.x + m_vtxMin.x, m_pos.y, m_pos.z + m_vtxMin.z);
	m_aPosVtx[1] = D3DXVECTOR3(m_pos.x + m_vtxMin.x, m_pos.y, m_pos.z + m_vtxMax.z);
	m_aPosVtx[2] = D3DXVECTOR3(m_pos.x + m_vtxMax.x, m_pos.y, m_pos.z + m_vtxMax.z);
	m_aPosVtx[3] = D3DXVECTOR3(m_pos.x + m_vtxMax.x ,m_pos.y, m_pos.z + m_vtxMin.z);

	// 4方向ベクトル
	m_aVecVtx[0] = m_aPosVtx[1] - m_aPosVtx[0];
	m_aVecVtx[1] = m_aPosVtx[2] - m_aPosVtx[1];
	m_aVecVtx[2] = m_aPosVtx[3] - m_aPosVtx[2];
	m_aVecVtx[3] = m_aPosVtx[0] - m_aPosVtx[3];
}

//==============================================================================
// 影のサイズ設定
//==============================================================================
D3DXVECTOR2 CModel::SetShadowSize(void)
{
	// ローカル変数宣言
	float fSize = m_vtxMax.x;	// 最大値のX座標を代入

	// 各サイズの比較(最大となる値を指定)
	if (fSize < m_vtxMax.z)
	{
		fSize = m_vtxMax.z;
	}
	if (fSize < -m_vtxMin.x)
	{
		fSize = -m_vtxMin.x;
	}
	if (fSize < -m_vtxMin.z)
	{
		fSize = -m_vtxMin.z;
	}

	// 値の設定
	m_shadowSize = D3DXVECTOR2(fSize, fSize);

	return m_shadowSize;
}