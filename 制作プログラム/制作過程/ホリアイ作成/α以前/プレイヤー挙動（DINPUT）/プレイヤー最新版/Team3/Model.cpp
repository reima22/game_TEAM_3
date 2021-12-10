//=============================================================================
//
// モデルクラス [model.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "Model.h"
#include "Manager.h"
#include "Renderer.h"

//*****************************************************************************
// モデルクラス
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CModel::CModel()
{
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = 0;
	m_pos = VECTOR3_ZERO;
	m_rot = VECTOR3_ZERO;
	m_pParent = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CModel::~CModel()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFilePath)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイス取得

	// xファイルから読み込み
	if (FAILED(D3DXLoadMeshFromX(
			aFilePath,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_dwNumMat,
			&m_pMesh)))
		return E_FAIL;

	// 位置、向きを設定
	m_pos = pos;
	m_rot = rot;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CModel::Uninit(void)
{
	// メッシュの破棄
	if (m_pMesh != NULL) {
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// マテリアルの破棄
	if (m_pBuffMat != NULL) {
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CModel::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイス取得
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	D3DMATERIAL9 matDef;			// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;				// マテリアルデータへのポインタ

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// このモデルの親を設定する
	D3DXMATRIX mtxParent;	// 親モデルのマトリックス
	if (m_pParent != NULL) {
		// 親が存在する場合親モデルのマトリックスを取得
		mtxParent = m_pParent->GetMtxWorld();
	}
	else {
		// 親が存在しない場合、現在のマトリックスを取得する -> このDrawの前にPlayerのDrawでSetTransformしているのでプレイヤーのマトリックス(?)
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}
	// 親のマトリックスと掛け合わせる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを保存
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// マテリアル数ループ
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++) {
		// マテリアル設定
		pDevice->SetMaterial(&pMat->MatD3D);

		// テクスチャ設定	 ( 現在設定なし )
		pDevice->SetTexture(0, NULL);

		// モデルパーツの描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// 生成関数
//=============================================================================
CModel *CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFilePath)
{
	CModel *pModel;
	pModel = new CModel;
	if (pModel != NULL)
	{
		pModel->Init(pos, rot, aFilePath);
	}

	return pModel;
}

//=============================================================================
// 親モデルを設定
//=============================================================================
