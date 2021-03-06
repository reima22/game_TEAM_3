//=============================================================================
//
// オブジェクトクラス [scene.cpp]
// Author: Sota Tomoe
//
//=============================================================================
#include "Scene.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
vector <CScene*> CScene::m_aSceneVc[SCENE_PRIORITY_MAX];
int CScene::m_nNumAll;

//*****************************************************************************
// オブジェクトクラス (基本)
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CScene::CScene(int nPriority)
{
	// コンテナの先頭からこのシーンのポインタを格納
	// 全体数をインクリメント
	// 優先度を記録
	// オブジェクトの種類を無しに設定
	m_aSceneVc[nPriority].push_back(this);
	m_nNumAll++;
	m_nPriority = nPriority;
	m_objType = OBJTYPE_NONE;
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
	for (int nCntPriority = 0; nCntPriority < SCENE_PRIORITY_MAX; nCntPriority++) {
		for (int i = 0; 0 < (signed)m_aSceneVc[nCntPriority].size();) {
			if (m_aSceneVc[nCntPriority][i] != NULL) {
				m_aSceneVc[nCntPriority][i]->Uninit();
			}
		}
	}
}

//=============================================================================
// すべての更新処理
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < SCENE_PRIORITY_MAX; nCntPriority++) {
		for (unsigned int i = 0; i < m_aSceneVc[nCntPriority].size(); i++) {
			if (m_aSceneVc[nCntPriority][i] != NULL) {
				m_aSceneVc[nCntPriority][i]->Update();
			}
		}
	}
}

//=============================================================================
// すべての描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < SCENE_PRIORITY_MAX; nCntPriority++) {
		for (unsigned int i = 0; i < m_aSceneVc[nCntPriority].size(); i++) {
			if (m_aSceneVc[nCntPriority][i] != NULL) {
				m_aSceneVc[nCntPriority][i]->Draw();
			}
		}
	}
}

//=============================================================================
// 開放処理
//=============================================================================
void CScene::Release(void)
{
	for (unsigned int i = 0; i < m_aSceneVc[m_nPriority].size(); i++) {
		if (m_aSceneVc[m_nPriority][i] == this) {
			int nPriority = m_nPriority;
			m_aSceneVc[nPriority].erase(m_aSceneVc[nPriority].begin() + i);
			m_nNumAll--;
			break;
		}
	}
}

//=============================================================================
// シーンのコンテナを取得
//=============================================================================
vector<CScene*> *CScene::GetSceneList(int nPriority)
{
	return &m_aSceneVc[nPriority];
}

//=============================================================================
// 優先度の値設定
//=============================================================================
void CScene::SetPriority(int nPriority)
{
	CScene *pScene = this;
	for (auto itr = m_aSceneVc[m_nPriority].begin(); itr != m_aSceneVc[m_nPriority].end(); itr++) {
		if ((*itr) == this) {
			m_aSceneVc[m_nPriority].erase(itr);
			break;
		}
	}
	m_aSceneVc[nPriority].push_back(this);
	m_nPriority = nPriority;
}