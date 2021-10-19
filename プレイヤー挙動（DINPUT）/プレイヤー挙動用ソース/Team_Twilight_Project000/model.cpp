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

// 静的メンバ変数宣言
//char *CModel::m_pFileName[MODELTYPE_MAX] =
//{
//	{ "data/MODEL/PLAYER/00_body.x" },			// 体
//	{ "data/MODEL/PLAYER/01_head.x" },			// 頭
//	{ "data/MODEL/PLAYER/02_arm_top_R.x" },		// 右上腕
//	{ "data/MODEL/PLAYER/03_arm_under_R.x" },	// 右下腕
//	{ "data/MODEL/PLAYER/04_hand_R.x" },		// 右手
//	{ "data/MODEL/PLAYER/05_arm_top_L.x" },		// 左上腕
//	{ "data/MODEL/PLAYER/06_arm_under_L.x" },	// 左下腕
//	{ "data/MODEL/PLAYER/07_hand_L.x" },		// 左手
//	{ "data/MODEL/PLAYER/08_leg_top_R.x" },		// 右腿
//	{ "data/MODEL/PLAYER/09_leg_under_R.x" },	// 右脛
//	{ "data/MODEL/PLAYER/10_foot_R.x" },		// 右足首
//	{ "data/MODEL/PLAYER/11_leg_top_L.x" },		// 左腿
//	{ "data/MODEL/PLAYER/12_leg_under_L.x" },	// 左脛
//	{ "data/MODEL/PLAYER/13_foot_L.x" },		// 左足首
//};

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

	// テクスチャの設定
	// テクスチャポインタ配列の動的確保(マテリアルの数だけ)
	m_pTexture = new LPDIRECT3DTEXTURE9[m_nNumMat];

	D3DXMATERIAL *pMat;		// マテリアルへのポインタ

	// バッファポインタの取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{// テクスチャあり
		 // テクスチャ情報の割り当て
			m_pTexture[nCntMat] = CTexture::BindTex3D(pMat[nCntMat].pTextureFilename);

			// ファイル名を使用してテクスチャを読み込む
			//D3DXCreateTextureFromFile(
			//	pDevice,
			//	pMat[nCntMat].pTextureFilename,
			//	&m_pTexture[nCntMat]);
		}
		else
		{// テクスチャの割り当てがない
			m_pTexture[nCntMat] = NULL;
		}
	}

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

	// Zテストの更新
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

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

	// 元に戻す
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
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