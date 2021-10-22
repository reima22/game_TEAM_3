
//=============================================================================
//
// ゲームモード処理 [game.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene.h"

// マクロ定義
#define LIFE_POS		(D3DXVECTOR3(40.0f, 40.0f, 0.0f))		// ライフ配置開始位置
#define SCORE_POS		(D3DXVECTOR3(1100.0f, 690.0f, 0.0f))	// スコア配置開始位置
#define DEFEAT_POS		(D3DXVECTOR3(730.0f, 690.0f, 0.0f))		// 撃破数の配置位置
#define INVASION_POS	(D3DXVECTOR3(870.0f, 690.0f, 0.0f))		// 侵入数の配置位置
#define STOCK_POS		(D3DXVECTOR3(600.0f, 680.0f, 0.0f))		// 残機数の配置位置
#define RESULT_GAMEEND	(D3DXVECTOR3(640.0f, 200.0f, 0.0f))		// ゲーム結果の描写

// 前方宣言
class CCharacter;
class CSceneX;
class CPlayer;
class CObject;

//==============================================================================
// ゲームモードクラス
//==============================================================================
class CGame : public CScene
{
public:
	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetSize(void);

	static CGame *Create(void);
	static CCharacter *GetChara(void) { return m_pCharaPlayer; }
	static int GetEndInvasion(void) { return m_nEndInvasion; }
	static bool GetStartGame(void) { return m_bGameStart; }

	static CPlayer *GetPlayer(void) { return m_pPlayer; }

private:
	static int m_nClearDefeat;				// ゲームクリアの撃破数
	static int m_nEndInvasion;				// ゲーム終了する侵入数
	static CCharacter *m_pCharaPlayer;		// プレイヤーキャラのポインタ
	static bool m_bGameStart;				// ゲームの開始判定

	static int m_nCntDownEnd;				// ゲーム終了までのカウント
	bool m_bSetLogo;
	
	static CPlayer *m_pPlayer;				// プレイヤーのポインタ

	static CObject **m_pObject;				// オブジェクトのポインタ
	int m_nNumObject;						// オブジェクト数
};

#endif