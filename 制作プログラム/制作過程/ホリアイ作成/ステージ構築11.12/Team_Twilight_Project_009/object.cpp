//==============================================================================
//
// 3Dオブジェクト管理〔object.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "object.h"
#include "model.h"
#include "input.h"
#include "gamepad.h"
#include "shadow.h"
#include "textdata_object.h"
#include "player.h"
#include "game.h"
#include "collision.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CObject::CObject()
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CObject::~CObject()
{

}

//==============================================================================
// 3Dオブジェクトの初期化処理
//==============================================================================
HRESULT CObject::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// オブジェクトタイプ
	SetObjType(OBJTYPE_OBJECT);

	// 読み取りデータポインタ
	CTextDataObject *pDataObject = CTextData::GetDataObject();

	// データの取得
	m_pos = pDataObject->GetPosition(m_nIdx);
	m_rot = pDataObject->GetRotation(m_nIdx);
	m_nType = pDataObject->GetTypeObject(m_nIdx);
	m_shadowSize = pDataObject->GetShadowSize(m_nIdx);
	m_bSavePoint = pDataObject->GetSavePoint(m_nIdx);
	m_bStartPoint = pDataObject->GetStartPoint(m_nIdx);
	m_bGoalPoint = pDataObject->GetGoalPoint(m_nIdx);

	m_pFileName = pDataObject->GetFileName(m_nType);

	// モデルの生成
	m_pModel = CModel::Create(m_pFileName, m_pos, m_rot);

	// 影の生成
	if (m_shadowSize == VECTOR2_NULL)
	{
		m_pShadow = CShadow::Create(m_shadowSize);
	}
	else
	{
		m_pShadow = NULL;
	}

	return S_OK;
}

//==============================================================================
// 3Dオブジェクトの終了処理
//==============================================================================
void CObject::Uninit(void)
{
	// モデル情報の破棄
	if (m_pModel != NULL)
	{
		delete m_pModel;
		m_pModel = NULL;
	}
}

//==============================================================================
// 3Dオブジェクトの更新処理
//==============================================================================
void CObject::Update(void)
{	
	// 影の追従
	if (m_pShadow != NULL)
	{
		m_pShadow->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y + 1.0f, m_pos.z));
	}
}

//==============================================================================
// 3Dオブジェクトの描画処理
//==============================================================================
void CObject::Draw(void)
{
	// ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;										// 計算用マトリックス
	D3DMATERIAL9 matDef;												// 現在のマテリアル保存用

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

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// モデルの描画
	if (m_pModel != NULL)
	{
		m_pModel->Draw();
	}
}

//==============================================================================
// 生成処理
//==============================================================================
//CObject *CObject::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,int nType, D3DXVECTOR2 shadowSize, bool bSavePoint, bool bGoalPoint)
//{
//	// ローカル変数宣言
//	CObject *pObject;
//	pObject = new CObject;	// インスタンス
//
//	// 初期化
//	if (pObject != NULL)
//	{
//		// 情報の設定
//		pObject->SetPosition(pos);
//		pObject->SetRotation(rot);
//		pObject->SetType(nType);
//		pObject->SetShadowSize(shadowSize);
//		pObject->SetSavePoint(bSavePoint);
//		pObject->SetGoalPoint(bGoalPoint);
//
//		pObject->Init();
//	}
//
//	return pObject;
//}

CObject *CObject::Create(int nIdx)
{
	// ローカル変数宣言
	CObject *pObject;
	pObject = new CObject;	// インスタンス

							// 初期化
	if (pObject != NULL)
	{
		// 情報の設定
		pObject->SetIdx(nIdx);

		pObject->Init();
	}

	return pObject;
}