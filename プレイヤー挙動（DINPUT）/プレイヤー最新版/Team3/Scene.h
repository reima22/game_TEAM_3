//=============================================================================
//
// オブジェクトクラス [scene.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// ヘッダーのインクルード
//*****************************************************************************
#include "main.h"
#include "Renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCENE_PRIORITY_MAX (5)
#define SCENE_PRIORITY_DEFAULT (3)

//*****************************************************************************
// オブジェクトクラス (抽象)
//*****************************************************************************
class CScene
{
public:
	CScene(int nPriority = SCENE_PRIORITY_DEFAULT);
	virtual ~CScene();

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	// SET
	virtual void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	virtual void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	virtual void SetSize(D3DXVECTOR3 size) { m_size = size; }
	void SetPriority(int nPriority);

	// GET
	virtual D3DXVECTOR3 GetPos(void) { return m_pos; }
	virtual D3DXVECTOR3 GetRot(void) { return m_rot; }
	virtual D3DXVECTOR3 GetSize(void) { return m_size; }

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static vector<CScene*> *CScene::GetSceneList(int nPriority);

protected:
	void Release(void);		// Scene2DのUninitから呼ぶからprotected

private:
	D3DXVECTOR3 m_pos;						// 位置
	D3DXVECTOR3 m_rot;						// 向き
	D3DXVECTOR3 m_size;						// サイズ
	int m_nPriority;						// 優先順位の番号

	static vector<CScene*> m_aSceneVc[SCENE_PRIORITY_MAX];	// シーンのリスト
	static int m_nNumAll;									// 全体の生成数
};

#endif
