//===================================================================
//HeaderFile: Collider3D.h
//Author : Yo jitaku
//===================================================================
#ifndef _COLLIDER3D_H_
#define _COLLIDER3D_H_
#include "main.h"
#include "PhysicsBase.h"
#include "stdlib.h"
#define HITBOX_VERTEX_NUM 8							//ボックスの頂点数
#define HITBOX_FACE_NUM 6							//ボックスの面数
#define HITBOX_INDEX_NUM (HITBOX_FACE_NUM * 6)		//描画必要のIndex数
#define HITBOX_DRAW_TRI_NUM (HITBOX_FACE_NUM * 2)	//実際に描画するの三角形面数
#define AXIS_NUM 3									//三次元軸数
typedef struct
{
	D3DXVECTOR3 BoxSizeMin;						//判定ボックス頂点座標の最小値
	D3DXVECTOR3 BoxSizeMax;						//判定ボックス頂点座標の最大値
	D3DXVECTOR3 BoxSize;						//判定ボックスのサイズ
	D3DXVECTOR3 BoxPos;							//判定ボックスの中心座標
	D3DXVECTOR3 Rot;							//判定ボックスの角度
	D3DXVECTOR3 BoxVtx[HITBOX_VERTEX_NUM];		//ボックスの頂点座標
	D3DXVECTOR3 Model_Offset;					//ボックスの中心座標とｘファイル中心のOFFSET(同じではない場合、有効)
	D3DXVECTOR3 Axis_Vector[AXIS_NUM];			//ボックス分離軸の方向ベクトル
	float Axis_VectorLength[AXIS_NUM];			//ボックス分離軸の長さ
}BOX;

class CHitBox :public CPhysics
{
public:
	HRESULT Init();								//初期化
	void SetHitBox(LPD3DXMESH pMesh);			//ボックス生成
	virtual void PhysicsUpdate();				//更新
	virtual void GraphicsDraw();				//描画
	void DrawHitBox();							//
	bool SAT_func(CHitBox* pTarget);			//当たり判定関数
private:
	D3DXVECTOR3 GetVector(int nNum) {			// 指定軸番号の方向ベクトルを取得	
		return m_Box.Axis_Vector[nNum];
	}

	FLOAT GetVecLength(int nNum) {				// 指定軸方向の長さを取得
		return m_Box.Axis_VectorLength[nNum];
	}
	D3DXVECTOR3 GetPos() {						// 位置を取得
		return m_Box.BoxPos;
	}
	D3DXVECTOR3 GetTriangleNor(					//平面の方向ベクトルを取る関数
		D3DXVECTOR3 pos1,
		D3DXVECTOR3 pos2,
		D3DXVECTOR3 pos3);
	float GetAxisProjectionlength(				//ボックスA分離軸の上でボックスB分離軸の投影長さ
		D3DXVECTOR3* Unit_Vec,
		D3DXVECTOR3* Box_x,
		D3DXVECTOR3* Box_y,
		D3DXVECTOR3* Box_z = 0);
	void SetSAT();								//分離軸の設置
	void SetIndex();							//Indexバッファの設置
	void SetVertex();							//頂点バッファの設置
	BOX m_Box;
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;			//Indexバッファ
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;			//頂点バッファ
	LPDIRECT3DDEVICE9 m_pDevice;				//デバイスを取る
	CRenderer *m_pRenderer;						//レンダリングのポインター
	bool m_DrawHitBox;							//描画を有効するのマーク
};
#endif