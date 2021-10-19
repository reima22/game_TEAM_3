//=============================================================================
//
// モデル管理 [model.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//==============================================================================
// モデル管理クラス
//==============================================================================
class CModel
{
public:
	// モデルの種類
	typedef enum
	{
		MODELTYPE_PLAYER_BODY = 0,		// プレイヤーのパーツ（体）
		MODELTYPE_PLAYER_HEAD,			// プレイヤーのパーツ（頭）
		MODELTYPE_PLAYER_ARM_TOP_R,		// プレイヤーのパーツ（右上腕）
		MODELTYPE_PLAYER_ARM_UNDER_R,	// プレイヤーのパーツ（右下腕）
		MODELTYPE_PLAYER_HAND_R,		// プレイヤーのパーツ（右手）
		MODELTYPE_PLAYER_ARM_TOP_L,		// プレイヤーのパーツ（左上腕）
		MODELTYPE_PLAYER_ARM_UNDER_L,	// プレイヤーのパーツ（左下腕）
		MODELTYPE_PLAYER_HAND_L,		// プレイヤーのパーツ（左手）
		MODELTYPE_PLAYER_LEG_TOP_R,		// プレイヤーのパーツ（右腿）
		MODELTYPE_PLAYER_LEG_UNDER_R,	// プレイヤーのパーツ（右脛）
		MODELTYPE_PLAYER_FOOT_R,		// プレイヤーのパーツ（右足首）
		MODELTYPE_PLAYER_LEG_TOP_L,		// プレイヤーのパーツ（左腿）
		MODELTYPE_PLAYER_LEG_UNDER_L,	// プレイヤーのパーツ（左脛）
		MODELTYPE_PLAYER_FOOT_L,		// プレイヤーのパーツ（左足首）
		MODELTYPE_MAX					// 最大数
	}MODELTYPE;

	CModel();
	~CModel();
	HRESULT Init(char *pFileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CModel *Create(char *pFileName,D3DXVECTOR3 pos,D3DXVECTOR3 rot);

	void SetParent(CModel *pModel) { m_pParent = pModel; }	// 親ポインタの設定
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }		// マトリックスの取得

	// 位置の設定
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

	// 角度の設定
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRotation(void) { return m_rot; }

	// モデルファイル名取得
	//static char *GetFileName(int nType) { return m_pFileName[nType]; }

private:
	LPD3DXMESH m_pMesh;				// メッシュポインタ
	LPD3DXBUFFER m_pBuffMat;		// マテリアルバッファ
	DWORD m_nNumMat;				// マテリアル数

	D3DXMATRIX m_mtxWorld;			// ワールドマトリックス
	D3DXVECTOR3 m_pos;				// 位置
	D3DXVECTOR3 m_rot;				// 向き
	CModel *m_pParent;				// 親モデルへのポインタ

	LPDIRECT3DTEXTURE9 *m_pTexture;	// テクスチャダブルポインタ

	//static char *m_pFileName[MODELTYPE_MAX];	// 読み込むファイル名パス
};

#endif