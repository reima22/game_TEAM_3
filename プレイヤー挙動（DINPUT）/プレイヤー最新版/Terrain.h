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
//�n�`�N���X
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
	HRESULT Init();						//�n�`�̏�����
	void Uninit();						//���
	void Update();						//�X�V
	void Draw();						//�n�`�̕`��
	bool FallCollider(CScene* pGameObject);//�����蔻��֐�

	int GetCellsPer() {					//��s������Z���̒l			
		return m_nCellsPerRow;
	}
	float GetCellSpacing() {			//�Z���̕��L
		return m_fCellSpacing;
	}
	float GetTerrainWidth() {			//�n�`�̕��L
		return m_fTerrainWidth;
	}

	vector<D3DXVECTOR3> vVertexBuffer;				//���_�o�b�t�@�̃R�s�[
	vector<int> vIndexBuffer;						//Index�o�b�t�@�̃R�s�[

private:
	const int MAX_PRIMITIVE_COUNT = 60000;			//�`��o����ő�l
	const int TERRAIN_HEIGHT = 0;					//�n�`�̍���
	const float TERRAIN_MOVE_SPEED = 0.0005f;		//�摜�ړ����x
	LPDIRECT3DDEVICE9 m_pDevice;					//�f�o�C�X�����
	LPDIRECT3DTEXTURE9 m_pTexture;					//Texture�̃|�C���^�[
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;				//���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;				//Index�o�b�t�@
	CManager* m_pManager;
	const int m_nCellsPerRow;					//1�s������̃Z����
	const int m_nCellsPerCol;					//1�񂠂���̃Z����
	const int m_nVertsPerRow;					//1�s������̒��_�̐�
	const int m_nVertsPerCol;					//1�񂠂���̒��_�̐�
	const unsigned int m_nNumVertices;		//���_�̑���
	const unsigned int m_nCells;				//�Z����
	const unsigned int m_nNumTriangles;		//�`��O�p�`��
	const unsigned int m_nNumIndex;			//Index�̔ԍ�
	const unsigned int m_nDrawBlock;
	const unsigned int m_nDrawTriRemainder;
	const float m_fTerrainWidth;				//�n�`�̕�
	const float m_fTerrainDepth;				//�n�`�̐[��
	const float m_fCellSpacing;				//�Z���̊Ԋu
};
#endif