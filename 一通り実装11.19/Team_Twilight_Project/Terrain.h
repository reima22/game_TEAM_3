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
#include "textdata_Terrain.h"

class CWave
{
public:
	CWave() :
		m_bWaveLine(false),
		m_DirX(false),
		m_fPower(0),
		m_fFrequency(0),
		m_fSpeed(0) {};
	void SetWave(float power, float fre, float speed, bool bDir);
	bool m_bWaveLine;
	bool m_DirX;
	float m_fPower;
	float m_fFrequency;
	float m_fSpeed;
};
//*******************************************************************
//�n�`�N���X
//*******************************************************************
class CTerrain
{
public:
	CTerrain() :
		m_pDevice(CManager::GetRenderer()->GetDevice()),
		m_pVtxBuff(nullptr),
		m_pIdxBuff(nullptr),
		m_pDataTerrain(nullptr),
		m_pManager(new CManager),
		m_pWave(new CWave),
		m_nVertsPerRow(0),
		m_nVertsPerCol(0),
		m_nNumVertices(0),
		m_nCells(0),
		m_nNumTriangles(0),
		m_nNumIndex(0),
		m_nDrawBlock(0),
		m_nDrawTriRemainder(0),
		m_nCntTime(0),
		m_fTerrainWidth(0),
		m_fTerrainDepth(0),
		m_ValidZoneMin(D3DXVECTOR3(0, 0, 0)),
		m_ValidZoneMax(D3DXVECTOR3(0, 0, 0)) {};
	~CTerrain()
	{
		if (m_pDevice != nullptr)
		{
			m_pDevice->Release();
			m_pDevice = nullptr;
		}
		if (m_pTexture != nullptr)
		{
			m_pTexture->Release();
			m_pTexture = nullptr;
		}
		if (m_pVtxBuff != nullptr)
		{
			m_pVtxBuff->Release();
			m_pVtxBuff = nullptr;
		}
		if (m_pIdxBuff != nullptr)
		{
			m_pIdxBuff->Release();
			m_pIdxBuff = nullptr;
		}
		delete m_pManager;
		m_pManager = nullptr;
		delete m_pWave;
		m_pWave = nullptr;
	}
	static CTerrain *Create(CTerrainInfo::TERRAIN_TYPE nType);				//�n�`�̏�����
	HRESULT Init(CTerrainInfo::TERRAIN_TYPE nType);
	void Update();						//�X�V
	void Draw();						//�n�`�̕`��
	bool FallCollider(CScene* pGameObject);//�����蔻��֐�
	vector<D3DXVECTOR3> vVertexBuffer;				//���_�o�b�t�@�̃R�s�[
	vector<int> vIndexBuffer;						//Index�o�b�t�@�̃R�s�[
	CTerrainInfo::TERRAIN_TYPE GetType(void) { return m_type; }
private:
	void WaveLineUpdate();
	void TerrainMove();
	const int MAX_PRIMITIVE_COUNT = 60000;			//�`��o����ő�l
	const int TERRAIN_HEIGHT = 0;					//�n�`�̍���
	const float TERRAIN_MOVE_SPEED = 0.0005f;		//�摜�ړ����x
	LPDIRECT3DDEVICE9 m_pDevice;					//�f�o�C�X�����
	LPDIRECT3DTEXTURE9 m_pTexture;					//Texture�̃|�C���^�[
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;				//���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;				//Index�o�b�t�@
	CTerrainInfo* m_pDataTerrain;
	CManager* m_pManager;
	CWave* m_pWave;
	int m_nVertsPerRow;					//1�s������̒��_�̐�
	int m_nVertsPerCol;					//1�񂠂���̒��_�̐�
	unsigned int m_nNumVertices;		//���_�̑���
	unsigned int m_nCells;				//�Z����
	unsigned int m_nNumTriangles;		//�`��O�p�`��
	unsigned int m_nNumIndex;			//Index�̔ԍ�
	unsigned int m_nDrawBlock;
	unsigned int m_nDrawTriRemainder;
	unsigned int m_nCntTime;
	float m_fTerrainWidth;				//�n�`�̕�
	float m_fTerrainDepth;				//�n�`�̐[��
	D3DXVECTOR3 m_ValidZoneMin;			//�n�`�͈̔͂̍ŏ��l
	D3DXVECTOR3 m_ValidZoneMax;			//�n�`�͈̔͂̍ő�l
	CTerrainInfo::TERRAIN_TYPE m_type;
};
#endif