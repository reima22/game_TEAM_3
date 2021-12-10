//=============================================================================
//
// カメラの設定 [camera.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

#define CAMERA_TURN	(D3DX_PI / 100.0f)	// カメラ旋回速度
#define CAMERA_SPDOWN	(0.1f)			// カメラの減衰係数

//==============================================================================
// カメラクラス
//==============================================================================
class CCamera
{
public:
	CCamera();
	~CCamera();
	void Init(void);
	void Uninit(void);
	void Update(void);

	static CCamera *Create(void);

	void SetCamera(void);
	D3DXVECTOR3 GetRotation(void) { return m_rot; }	// 向きの取得

	void SetInit(void);

private:
	D3DXMATRIX m_mtxView;		// ビューマトリックス
	D3DXMATRIX m_mtxProjection;	// プロジェクションマトリックス
	D3DXVECTOR3 m_posV;			// 視点
	D3DXVECTOR3 m_posR;			// 注視点
	D3DXVECTOR3 m_vecU;			// 上方向ベクトル
	D3DXVECTOR3 m_rot;			// 向き
	float m_fLength;			// 距離
	float m_fFront;				// 前方距離
	float m_fHeightR;			// 注視点位置
	float m_fHeightV;			// 視点位置

	D3DXVECTOR3 m_posVDest;		// 目的の視点
	D3DXVECTOR3 m_posRDest;		// 目的の注視点
};
#endif