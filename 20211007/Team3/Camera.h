//=============================================================================
//
// カメラ [camera.h]
// Author: Sota Tomoe
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// ヘッダーのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// カメラクラス
//*****************************************************************************
class CCamera
{
public:
	CCamera();
	~CCamera();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(LPDIRECT3DDEVICE9 pDevice);

private:
	D3DXVECTOR3 m_posV;	// 視点
	D3DXVECTOR3 m_posR;	// 注視点
	D3DXVECTOR3 m_vecU;	// 上方向ベクトル
	D3DXVECTOR3 m_rot;	// 向き
	D3DXMATRIX m_mtxProjection;		// プロジェクションマトリックス
	D3DXMATRIX m_mtxView;			// ビューマトリックス
	float m_fCamDist;	// 注視点から視点までの距離

	void MoveR(float fAngDeg);
};
#endif

