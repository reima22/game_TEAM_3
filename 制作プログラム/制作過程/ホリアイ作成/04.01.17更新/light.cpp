//==============================================================================
//
// ライトの設定〔light.cpp〕
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "light.h"
#include "manager.h"
#include "renderer.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CLight::CLight()
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CLight::~CLight()
{

}

//==============================================================================
// 初期化処理
//==============================================================================
void CLight::Init(void)
{
	// ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	D3DXVECTOR3 vecDir;

	// デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCnt = 0; nCnt < LIGHT_NUM; nCnt++)
	{
		// ライトをクリアする
		ZeroMemory(&m_aLight[nCnt], sizeof(D3DLIGHT9));

		// ライトの種類を設定
		m_aLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		// ライトの拡散光を設定
		m_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ライトの方向を設定
		if (nCnt == 0)
		{
			vecDir = D3DXVECTOR3(1.0f, -0.0f, -0.0f);
			//vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
		}
		else if (nCnt == 1)
		{
			vecDir = D3DXVECTOR3(0.5f, -1.0f, 0.8f);
			//vecDir = D3DXVECTOR3(-0.2f, -0.8f, 0.4f);
		}
		else if (nCnt == 2)
		{
			vecDir = D3DXVECTOR3(0.5f, -0.0f, 0.0f);
			//vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		}

		D3DXVec3Normalize(&vecDir, &vecDir);		// 正規化する
		m_aLight[nCnt].Direction = vecDir;

		// ライトを設定する
		pDevice->SetLight(nCnt, &m_aLight[nCnt]);

		// ライトを有効にする
		pDevice->LightEnable(nCnt, TRUE);
	}
}

//==============================================================================
// 終了処理
//==============================================================================
void CLight::Uninit(void)
{

}

//==============================================================================
// 更新処理
//==============================================================================
void CLight::Update(void)
{

}

//==============================================================================
// 生成処理
//==============================================================================
CLight *CLight::Create(void)
{
	// ローカル変数宣言
	CLight *pLight;
	pLight = new CLight;

	// 初期化
	if (pLight != NULL)
	{
		pLight->Init();
	}

	return pLight;
}