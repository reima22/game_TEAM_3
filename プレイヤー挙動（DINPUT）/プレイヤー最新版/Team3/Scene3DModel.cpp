//=============================================================================
//
// 3Dモデル [Scene3DModel.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "Scene3DModel.h"
#include "Manager.h"
#include "Input.h"
#include "Resource.h"

//*****************************************************************************
// モデルクラス (派生元：オブジェクトクラス）
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CScene3DModel::CScene3DModel(int nPriority) : CScene(nPriority)
{
	m_pTexture = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene3DModel::~CScene3DModel()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene3DModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// 引数から設定
	SetPos(pos);
	SetRot(rot);
	SetSize(VECTOR3_ZERO);

	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// get resource manager
	m_pResourceManager = CManager::GetResourceManager();


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScene3DModel::Uninit(void)
{

	// インスタンス破棄
	this->Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene3DModel::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CScene3DModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// Device
	D3DXMATRIX mtxRot, mtxTrans;	// Temporary matrices
	D3DMATERIAL9 matDef;			// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;				// temp mat

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

	//現在のマテリアルを保存
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	CModelData *pModel = m_pResourceManager->m_Model_Map[m_modelName];	// モデルのデータ
	pMat = (D3DXMATERIAL*)pModel->Xfile_Materials->GetBufferPointer();	// マテリアルデータへのポインタ

	for (DWORD nCntMat = 0; nCntMat < (int)pModel->Xfile_MaterialNum; nCntMat++)
	{
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		pDevice->SetTexture(0, pModel->g_Textures[nCntMat]);
		pModel->Xfile_Mesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// モデルのバインド
//=============================================================================
void CScene3DModel::BindModel(string modelName)
{
	m_modelName = modelName;
}

//=============================================================================
// 生成関数
//=============================================================================
CScene3DModel *CScene3DModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, string modelName)
{
	CScene3DModel *pScene3DModel;
	pScene3DModel = new CScene3DModel;
	if (pScene3DModel != NULL)
	{
		pScene3DModel->Init(pos, rot, VECTOR3_ZERO);
		pScene3DModel->BindModel(modelName);
	}

	return pScene3DModel;
}