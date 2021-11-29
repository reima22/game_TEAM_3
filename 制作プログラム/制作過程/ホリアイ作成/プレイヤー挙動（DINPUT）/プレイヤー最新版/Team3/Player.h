#define _CRT_SECURE_NO_WARNINGS
//=============================================================================
//
// プレイヤークラス [player.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// ヘッダーのインクルード
//*****************************************************************************
#include "main.h"
#include "Scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_MODEL_COUNT (10)

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CModel;

//*****************************************************************************
// モデルクラス (派生元：オブジェクトクラス (scene) ）
//*****************************************************************************
class CPlayer : public CScene
{
public:
	CPlayer(int nPriority = 3);
	~CPlayer();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	CModel *m_apModel[PLAYER_MODEL_COUNT];	// モデルへのポインタ
	int m_nIndexParent[PLAYER_MODEL_COUNT];	// 親モデルのINDEX
	float m_aOffset[PLAYER_MODEL_COUNT][6];	// 親モデルからのオフセット
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
	char m_aFilePath[PLAYER_MODEL_COUNT][128];
};

#endif