//=============================================================================
//
// オブジェクトクラス [scene.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "scene.h"


//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
list<CScene*> CScene::m_apScene[SCENE_PRIORITY_MAX];
int CScene::m_nNumAll;

//*****************************************************************************
// オブジェクトクラス (基本)
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CScene::CScene(int nPriority)
{
	// 指定された優先度の場所に
	// 空いている場所にCSceneのポインタを格納
	// 個数をインクリメント
	// IDを記録
	m_apScene[nPriority].push_front(this);
	m_nNumAll++;
	m_nPriority = nPriority;

	//for (int nCntScene = 0; nCntScene < SCENE_MAX; nCntScene++)
	//{
	//	if (m_apScene[nPriority][nCntScene] == NULL)
	//	{
	//		m_apScene[nPriority][nCntScene] = this;
	//		m_nNumAll++;
	//		m_nID = nCntScene;
	//		m_nPriority = nPriority;

	//		break;
	//	}
	//}
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScene::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CScene::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CScene::Draw(void)
{

}

//=============================================================================
// すべての終了処理
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < SCENE_PRIORITY_MAX; nCntPriority++)
	{
		for (auto itr = m_apScene[nCntPriority].begin(); itr != m_apScene[nCntPriority].end(); itr++) {
			if ((*itr) != NULL)
				(*itr)->Uninit();
		}
	}

	//for (int nCntPriority = 0; nCntPriority < SCENE_PRIORITY_MAX; nCntPriority++)
	//{
	//	for (int nCntScene = 0; nCntScene < SCENE_MAX; nCntScene++)
	//	{
	//		if (m_apScene[nCntPriority][nCntScene] != NULL)
	//		{
	//			m_apScene[nCntPriority][nCntScene]->Uninit();
	//		}
	//	}
	//}
}

//=============================================================================
// すべての更新処理
//=============================================================================
void CScene::UpdateAll(void)
{

	for (int nCntPriority = 0; nCntPriority < SCENE_PRIORITY_MAX; nCntPriority++)
	{
		for (auto itr = m_apScene[nCntPriority].begin(); itr != m_apScene[nCntPriority].end(); itr++) {
			if ((*itr) != NULL)
				(*itr)->Update();
		}
	}

	//for (int nCntPriority = 0; nCntPriority < SCENE_PRIORITY_MAX; nCntPriority++)
	//{
	//	for (int nCntScene = 0; nCntScene < SCENE_MAX; nCntScene++)
	//	{
	//		if (m_apScene[nCntPriority][nCntScene] != NULL)
	//		{
	//			m_apScene[nCntPriority][nCntScene]->Update();
	//		}
	//	}
	//}
}

//=============================================================================
// すべての描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < SCENE_PRIORITY_MAX; nCntPriority++)
	{
		for (auto itr = m_apScene[nCntPriority].begin(); itr != m_apScene[nCntPriority].end(); itr++) {
			if ((*itr) != NULL)
				(*itr)->Draw();
		}
	}
}

//=============================================================================
// 開放処理
//=============================================================================
void CScene::Release(void)
{
	auto itr = next(m_apScene[m_nPriority].begin(), m_nID);
	if ((*itr) != NULL)
	{
		delete (*itr);
		(*itr) = NULL;
		m_nNumAll--;
	}
}

//=============================================================================
// オブジェクトが入ったポインタを取得
//=============================================================================
CScene *CScene::GetScene(int nPriority, int nScene)
{
	auto itr = next(&m_apScene[nPriority], nScene);
	return (CScene*)(itr);

	//return m_apScene[nPriority][nScene];
}

//=============================================================================
// オブジェクトのポインタ格納
//=============================================================================
void CScene::SetScene(int nPriority, int nScene, CScene *obj)
{
	auto itr = m_apScene[nPriority].begin();
	advance(itr, nScene);
	if ((*itr) == NULL)
		m_apScene[nPriority].emplace(itr, obj);
	

	//if (m_apScene[nPriority][nScene] == NULL)
	//{ 
	//	m_apScene[nPriority][nScene] = obj;
	//}
}

//=============================================================================
// 優先度の値設定
//=============================================================================
void CScene::SetPriority(int nPriority)
{
	//for (int nCntScene = 0; nCntScene < SCENE_MAX; nCntScene++)
	//{
	//	if (m_apScene[nPriority][nCntScene] == NULL)
	//	{
	//		m_apScene[nPriority][nCntScene] = this;	// 新しい場所にポインタ保存
	//		m_apScene[m_nPriority][m_nID] = NULL;	// 元の場所を空に
	//		m_nID = nCntScene;						// 新しいID設定
	//		m_nPriority = nPriority;				// 新しい優先度設定
	//		m_nNumAll++;							// 減った数を戻す
	//	}
	//}
}