//==============================================================================
//
// メッシュフィールドの描画〔meshfield.h〕
// AUTHOR : MARE HORIAI
//
//==============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
#include "main.h"
#include "scene.h"

// メッシュフィールドクラス
class CMeshField : public CScene
{
public:
	CMeshField();
	~CMeshField();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMeshField *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nWidth, int nDepth, float fWidth, float fDepth);

	// 値の設定
	void SetPostion(D3DXVECTOR3 pos) { m_pos = pos; }		// 位置
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }		// 角度
	void SetWidthNum(int nWidth) { m_nWidth = nWidth; }		// 幅の面の数
	void SetDepthNum(int nDepth) { m_nDepth = nDepth; }		// 奥行の面の数
	void SetWidthSize(float fWidth) { m_fWidth = fWidth; }	// 1枚当たりの幅
	void SetDepthSize(float fDepth) { m_fDepth = fDepth; }	// 1枚当たりの奥行

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	// バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	// インデックスバッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;		// テクスチャへのポインタ
	D3DXVECTOR3 m_pos;							// 位置
	D3DXVECTOR3 m_rot;							// 角度
	D3DXMATRIX m_mtxWorld;						// ワールドマトリックス
	int m_nAllPoint;							// 総頂点数
	int m_nPolygon;								// ポリゴン数
	int m_nIdxPoint;							// インデックスバッファの必要な確保数
	float m_fWidth;								// ポリゴン一つあたりの幅
	float m_fDepth;								// ポリゴン一つあたりの奥行
	int m_nWidth;								// 横幅の面の数
	int m_nDepth;								// 奥行の面の数

	int m_nWidthPoint;							// 横幅の頂点数
	int m_nDepthPoint;							// 奥行の頂点数

	float m_fWidthMax;							// 横幅の最大サイズ
	float m_fDepthMax;							// 奥行の最大サイズ
};

#endif
