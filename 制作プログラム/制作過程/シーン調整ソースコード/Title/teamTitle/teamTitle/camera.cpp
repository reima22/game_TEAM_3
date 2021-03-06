//-------------------------------------------------------------------------------
//
// ゲーム制作[camera.cpp]
// Author:Tatsuki Matsuda
//
//-------------------------------------------------------------------------------
#include"camera.h"		//ゲーム画面
#include"manager.h"

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
CCamera::CCamera()
{

}
//*****************************************************************************
// デストラクタ
//*****************************************************************************
CCamera::~CCamera()
{

}

//*****************************************************************************
// 初期化処理
//*****************************************************************************
void CCamera::InitCamera(void)
{
	//カメラの位置
	m_apCamera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_apCamera.posV = D3DXVECTOR3(0.0f, MAX_POSV_Y, MAX_POSV_Z);
	m_apCamera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_apCamera.posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//g_aCamera.posR.x = g_aCamera.posV.x +- sinf();
}

//-------------------------------------------------------------------------------
//終了処理
//-------------------------------------------------------------------------------
void CCamera::UninitCamera(void)
{
}

//-------------------------------------------------------------------------------
//更新処理
//-------------------------------------------------------------------------------
void CCamera::UpdateCamera(void)
{
}


//-------------------------------------------------------------------------------
//設定処理
//-------------------------------------------------------------------------------
void CCamera::SetCamera(void)
{
	//デバイスの設定
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_apCamera.mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_apCamera.mtxProjection, D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 1000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_apCamera.mtxProjection);

	//ビューマトリックスを作成
	D3DXMatrixLookAtLH(&m_apCamera.mtxView, &m_apCamera.posV,
		&m_apCamera.posR, &m_apCamera.posU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_apCamera.mtxView);
}