//=============================================================================
//
// プレイヤー管理 [player.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene.h"
#include "scene3D.h"

class CModel;
class CShadow;

// マクロ定義
#define KEYNUM_MAX	(10)	// キーの最大数
#define MOVE_MOTION	(0.1f)	// 移動モーションを行う速度
#define RUN_MOTION	(2.0f)	// 走るモーションを行う速度
#define SPEED_DOWN	(0.2f)	// 減衰係数
#define GRAVITY_SCALE	(0.6f)	// 重力
#define WALK_SPEED	(0.5f)	// 歩く
#define RUN_SPEED	(1.0f)	// 走る

//==============================================================================
// プレイヤー管理クラス
//==============================================================================
class CPlayer : public CScene3D
{
public:
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,	// ニュートラル
		MOTIONTYPE_WALK,		// 歩行
		MOTIONTYPE_RUN,			// 走行
		MOTIONTYPE_JUMP,		// ジャンプ
		MOTIONTYPE_STEP,		// 着地
		MOTIONTYPE_CLEAR,		// クリアポーズ
		MOTIONTYPE_MAX
	}MOTIONTYPE;

	// キー要素
	typedef enum
	{
		KEY_POS_X = 0,	// posX
		KEY_POS_Y,		// posY
		KEY_POS_Z,		// posZ
		KEY_ROT_X,		// rotX
		KEY_ROT_Y,		// rotY
		KEY_ROT_Z,		// rotZ
		KEY_MAX
	}KEY;

	CPlayer();
	~CPlayer();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer *Create(D3DXVECTOR3 pos);

	// モーションの更新
	void UpdateMotion(MOTIONTYPE motionType);
	MOTIONTYPE GetMotion(void) { return m_motionType; }						// 取得
	void SetMotion(MOTIONTYPE motionType) { m_motionType = motionType; }	// 設定

	int GetFrameCnt(void) { return m_nFrameCnt; }
	int GetKeyCnt(void) { return m_nKeyCnt; }

	// 位置の取得・設定
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }

	// 向きの取得・設定
	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }

	D3DXVECTOR3 GetRotDest(void) { return m_rotDest; }

	// 移動力の取得
	D3DXVECTOR3 GetMove(void) { return m_move;  }

	// 移動処理
	void MovePlayer(void);

private:
	// モデル情報
	int m_nNumParts;			// パーツ数

	CModel **m_apModel;			// モデルへのポインタ
	int *m_aIndexParent;		// 親モデルのインデックス
	float **m_aOffset;			// 親モデルからのオフセット

	D3DXMATRIX m_mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3 m_pos;			// 位置
	D3DXVECTOR3 m_rot;			// 向き

	D3DXVECTOR3 m_move;			// 移動力
	//D3DXVECTOR3 m_posOld;		// 過去の位置
	D3DXVECTOR3 m_rotDest;		// 過去の向き

	bool m_bJump;				// ジャンプしている
	bool m_bLand;				// 着地している
	int m_nJumpCnt;				// ジャンプボタン長押しカウント

	int m_nDashCnt;				// ダッシュしている時のカウント
	float m_fDashPower;			// ダッシュ力

	// モーション情報
	MOTIONTYPE m_motionType;			// プレイヤーのモーション
	MOTIONTYPE m_motionTypeOld;			// 以前のモーション
	float ***m_aKey[MOTIONTYPE_MAX];	// キー要素
	int m_nNumKey[MOTIONTYPE_MAX];		// キーの数
	bool m_bLoop;						// ループするか
	int *m_pFrame[MOTIONTYPE_MAX];		// フレーム数

	D3DXVECTOR3 *m_posMemo;				// ブレンド保存用位置情報
	D3DXVECTOR3 *m_rotMemo;				// ブレンド保存用向き情報
	bool m_bBlendMotion;				// 

	int m_nKeyCnt;						// キーのカウンタ
	int m_nFrameCnt;					// フレームのカウンタ

	CShadow *m_pShadow;					// 影ポインタ
};
#endif
