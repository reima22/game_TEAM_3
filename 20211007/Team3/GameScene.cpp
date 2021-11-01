//=============================================================================
//
// ゲーム画面 [game.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "Gamescene.h"
#include "Input.h"
#include "Manager.h"
#include "ObjectManager.h"
#include "Collision.h"
#include "Player.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CObjectManager *CGameScene::m_pObjectManager = NULL;
CCollision *CGameScene::m_pCollision = NULL;
CPlayer *CGameScene::m_pPlayer = NULL;

//*****************************************************************************
// ゲーム画面クラス ( 継承元: オブジェクトクラス [scene] )
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CGameScene::CGameScene()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CGameScene::~CGameScene()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CGameScene::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// モデル管理クラス生成
	m_pObjectManager = new CObjectManager;
	if (FAILED(m_pObjectManager->Init())) {
		return E_FAIL;
	}

	// 当たり判定クラス生成
	m_pCollision = new CCollision;
	if (FAILED(m_pCollision->Init())) {
		return E_FAIL;
	}

	// 床ポリ
	m_pScene3D = CScene3D::Create(VECTOR3_ZERO, VECTOR3_ZERO, D3DXVECTOR3(1000.0f, 0.0f, 1000.0f), "TexTest01");
	m_pScene3D->SetTextureUV(
		D3DXVECTOR2(0.0f, 10.0f),
		D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2(10.0f, 10.0f),
		D3DXVECTOR2(10.0f, 0.0f));

	// テストプレイヤー
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0, 10, 0), VECTOR3_ZERO);
	
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CGameScene::Uninit(void)
{
	m_pPlayer = NULL;

	// 当たり判定クラス破棄
	m_pCollision->Uninit();
	delete m_pCollision;
	m_pCollision = NULL;

	// 足場管理クラス破棄
	m_pObjectManager->Uninit();
	delete m_pObjectManager;
	m_pObjectManager = NULL;

	// このオブジェクトの開放
	this->Release();
}

//=============================================================================
// 更新
//=============================================================================
void CGameScene::Update(void)
{
	// 足場管理クラス更新
	m_pObjectManager->Update();

	// 当たり判定更新
	m_pCollision->Update();

	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();
	if (pKeyboard->GetTrigger(DIK_B))
	{

	}
}

//=============================================================================
// 描画
//=============================================================================
void CGameScene::Draw(void)
{

}
