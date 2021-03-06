//=============================================================================
//
// ゲーム画面 [game.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// ヘッダーのインクルード
//*****************************************************************************
#include "main.h"
#include "Scene2D.h"
#include "Scene3D.h"
#include "Scene3DModel.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObjectManager;
class CCollision;
class CPlayer;

//*****************************************************************************
// ゲーム画面クラス ( 継承元: オブジェクトクラス [scene] )
//*****************************************************************************
class CGameScene : public CScene
{
public:
	CGameScene();
	~CGameScene();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	static CObjectManager *GetObjectManager(void) { return m_pObjectManager; }
	static CCollision *GetCollision(void) { return m_pCollision; }
	static CPlayer *GetPlayer(void) { return m_pPlayer; }

private:
	CScene3D *m_pScene3D;

	static CObjectManager *m_pObjectManager;
	static CCollision *m_pCollision;
	static CPlayer *m_pPlayer;
};
#endif

