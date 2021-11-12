//=============================================================================
//
// 3Dオブジェクト管理 [object.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "scene.h"
#include "scene3D.h"

class CModel;
class CShadow;

//==============================================================================
// オブジェクト管理クラス
//==============================================================================
class CObject : public CScene3D
{
public:
	CObject();
	~CObject();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, D3DXVECTOR2 shadowSize, bool bSavePoint);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }

	D3DXVECTOR3 GetRotation(void) { return m_rot; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }

	// 種類の取得・設定
	int GetType(void) { return m_nType; }
	void SetType(int nType) { m_nType = nType; }

	void SetShadowSize(D3DXVECTOR2 shadowSize) { m_shadowSize = shadowSize; }

	CModel *GetModel(void) { return m_pModel; }

	// 中間地点可否の取得・設定
	bool GetSavePoint(void) { return m_bSavePoint; }
	void SetSavePoint(bool bSavePoint) { m_bSavePoint = bSavePoint; }

private:
	D3DXMATRIX m_mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3 m_pos;			// 位置
	D3DXVECTOR3 m_rot;			// 向き
	int m_nType;				// 種類
	bool m_bSavePoint;			// 中間地点であるか

	char *m_pFileName;			// ファイル名のポインタ
	CModel *m_pModel;			// モデルポインタ
	CShadow *m_pShadow;			// 影ポインタ

	D3DXVECTOR2 m_shadowSize;	// 影の大きさ
};
#endif

