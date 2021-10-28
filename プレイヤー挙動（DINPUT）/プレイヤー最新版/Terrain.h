//===================================================================
//HeaderFile: Terrain.h
//Author : Yo jitaku
//===================================================================
#ifndef _Terrain_H_
#define _Terrain_H_
#include "main.h"
#include "Renderer.h"
#include "Manager.h"
#include "Scene.h"
//#include "Resource.h"

//*******************************************************************
//地形クラス
//*******************************************************************
class CTerrain
{
public:
	CTerrain(int nRows, int nCols, float fSpace) :
		m_pDevice(CManager::GetRenderer()->GetDevice()),
		m_pTexture(nullptr),
		m_pVtxBuff(nullptr),
		m_pIdxBuff(nullptr),
		m_pManager(new CManager),
		m_nCellsPerRow(nRows),
		m_nCellsPerCol(nCols),
		m_nVertsPerRow(m_nCellsPerRow + 1),
		m_nVertsPerCol(m_nCellsPerCol + 1),
		m_nNumVertices(m_nVertsPerRow * m_nVertsPerCol),
		m_nCells(m_nCellsPerRow * m_nCellsPerCol),
		m_nNumTriangles(m_nCells * 2),
		m_nNumIndex(m_nCells * 6),
		m_nDrawBlock(m_nNumTriangles / MAX_PRIMITIVE_COUNT),
		m_nDrawTriRemainder(m_nNumIndex % MAX_PRIMITIVE_COUNT),
		m_fTerrainWidth(nRows * fSpace),
		m_fTerrainDepth(nCols * fSpace),
		m_fCellSpacing(fSpace) {
		Init();
	}
	HRESULT Init();						//地形の初期化
	void Uninit();						//解放
	void Update();						//更新
	void Draw();						//地形の描画
	bool FallCollider(CScene* pGameObject);//当たり判定関数

	int GetCellsPer() {					//一行があるセルの値			
		return m_nCellsPerRow;
	}
	float GetCellSpacing() {			//セルの幅広
		return m_fCellSpacing;
	}
	float GetTerrainWidth() {			//地形の幅広
		return m_fTerrainWidth;
	}

	vector<D3DXVECTOR3> vVertexBuffer;				//頂点バッファのコピー
	vector<int> vIndexBuffer;						//Indexバッファのコピー

private:
	const int MAX_PRIMITIVE_COUNT = 60000;			//描画出来る最大値
	const int TERRAIN_HEIGHT = 0;					//地形の高さ
	const float TERRAIN_MOVE_SPEED = 0.0005f;		//画像移動速度
	LPDIRECT3DDEVICE9 m_pDevice;					//デバイスを取る
	LPDIRECT3DTEXTURE9 m_pTexture;					//Textureのポインター
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;				//頂点バッファ
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;				//Indexバッファ
	CManager* m_pManager;
	const int m_nCellsPerRow;					//1行あたりのセル数
	const int m_nCellsPerCol;					//1列あたりのセル数
	const int m_nVertsPerRow;					//1行あたりの頂点の数
	const int m_nVertsPerCol;					//1列あたりの頂点の数
	const unsigned int m_nNumVertices;		//頂点の総数
	const unsigned int m_nCells;				//セル数
	const unsigned int m_nNumTriangles;		//描画三角形数
	const unsigned int m_nNumIndex;			//Indexの番号
	const unsigned int m_nDrawBlock;
	const unsigned int m_nDrawTriRemainder;
	const float m_fTerrainWidth;				//地形の幅
	const float m_fTerrainDepth;				//地形の深さ
	const float m_fCellSpacing;				//セルの間隔
};
#endif